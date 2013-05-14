#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ifaddrs.h>
#include <net/if.h>

#include "NetworkInterface.h"

#define MAGIC 0x743364 // t3d in hex
#define MULTICAST_GROUP "225.0.0.32"
#define MULTICAST_PORT 50000
#define GAME_PORT "50005"

#define MAXPENDING 5

#define FAILURE_TEST(x, msg) if((x)) { perror(msg); exit(-1); }

//#define Debug
#ifdef Debug
#  define LOGGER(x) cerr << x << endl;
#else
#  define LOGGER(x)
#endif

using namespace std;

NetworkInterface::NetworkInterface() 
{
	msgBuffer.msgInfo.magic = MAGIC;
}

void NetworkInterface::hostGame()
{
	// create a TCP socket for the client to connect to
	int serverSock = setupTCPServerSocket(GAME_PORT);	
	FAILURE_TEST(serverSock < 0, "setupTCPServerSocket() failed: don't read next thing");

	// get the information associated with the socket to provide the client
	struct sockaddr_in tcpAddr = { 0 };
	socklen_t addrLen = sizeof(tcpAddr);
	FAILURE_TEST(getsockname(serverSock, (struct sockaddr *) &tcpAddr, &addrLen) < 0, "getsockname() failed");

	// create a host message
	msgBuffer.msgInfo.msgType = MessageTranslator::HOST;
	msgBuffer.ipAddr = tcpAddr.sin_addr.s_addr;
	msgBuffer.portNum = tcpAddr.sin_port;

	// only encode the message type because the rest (ip and port) are already in
	// network byte order
	msgBuffer.msgInfo.msgType = htons(msgBuffer.msgInfo.msgType);

	// send out messages on the multicasting channel
	int multiCastSocket = socket(AF_INET, SOCK_DGRAM, 0);
	FAILURE_TEST(multiCastSocket < 0, "socket() failed");

	// convert the address from text to binary
	uint8_t buf[sizeof(struct in_addr)];
	FAILURE_TEST(inet_pton(AF_INET, MULTICAST_GROUP, buf) < 0, "inet_pton() failed");

	// create the socket address
	struct sockaddr_in multiAddr = { 0 };
	multiAddr.sin_family = AF_INET;
	multiAddr.sin_addr = *((struct in_addr *) buf);
	multiAddr.sin_port = htons(MULTICAST_PORT);
	
	// repeatedly send out host message until a client accepts on our listening port
	char printAddr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &msgBuffer.ipAddr, printAddr, INET_ADDRSTRLEN);
	while (1) {
		LOGGER("Sending address: " << printAddr );
		LOGGER("Sending port: " << ntohs(msgBuffer.portNum));
		sendto(multiCastSocket, &msgBuffer, sizeof(msgBuffer), 0, 
					 (struct sockaddr *) &multiAddr, sizeof(multiAddr));
		sleep(1);

		if (dataAvailable(serverSock)) {
			break; 
		}
	}
	close(multiCastSocket);
	LOGGER("Recieved a multicast message from a clien");

	// accept the client connection
	socklen_t oppAddrLen = sizeof(oppAddr);
	FAILURE_TEST((sock = accept(serverSock, (struct sockaddr *) &oppAddr, &oppAddrLen)) < 0, "accept() failed");
	LOGGER("Accepted the connection from the client");

	// initiate start of game handshake
	msgBuffer.msgInfo.msgType = MessageTranslator::MessageType::START_GAME;
	MessageTranslator::encode(&msgBuffer);
	MessageCommunicator::sendMessage(sock, &msgBuffer, sizeof(msgBuffer));

	// get the message and make sure that the message is start
	MessageCommunicator::recvMessage(sock, &msgBuffer, sizeof(msgBuffer));
	MessageTranslator::decode(&msgBuffer);
	FAILURE_TEST(MessageTranslator::MessageType::START_GAME != msgBuffer.msgInfo.msgType, 
							 "Expected a START_GAME message");

	// now the game may begin sending action commands back and forth
	cout << "Starting game" << endl;
}

void NetworkInterface::joinGame()
{
	// create a UDP socket
	int multiCastSocket = socket(AF_INET, SOCK_DGRAM, 0);
	FAILURE_TEST(multiCastSocket < 0, "socket() failed");

	// bind to port
	struct sockaddr_in addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(MULTICAST_PORT);
	FAILURE_TEST(bind(multiCastSocket, (struct sockaddr *) &addr, sizeof(addr)) < 0,
							 "bind() failed");
	
	// convert the address from text to binary
	uint8_t buf[sizeof(struct in_addr)];
	FAILURE_TEST(inet_pton(AF_INET, MULTICAST_GROUP, buf) < 0, "inet_pton() failed");

	// add to multicast group
	struct ip_mreq mreq = { 0 };
	mreq.imr_multiaddr = *((struct in_addr *) buf);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	FAILURE_TEST(setsockopt(multiCastSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0,
							 "setsockopt() failed");

	// get a message from a server: recvfrom blocks
	struct sockaddr_in hostAddr = { 0 };
	socklen_t hostAddrLen = sizeof(hostAddr);
	LOGGER("Waiting for a host packet...");
	recvfrom(multiCastSocket, (struct sockaddr *) &msgBuffer, sizeof(msgBuffer), 0, 
					 (struct sockaddr *) &hostAddr, &hostAddrLen);
	LOGGER("Received a host packet");

	// only decode the message type because we want the ip address and port in
	// network byte order
	msgBuffer.msgInfo.msgType = ntohs(msgBuffer.msgInfo.msgType);

	// check to make sure the message is a host message
	FAILURE_TEST(MessageTranslator::MessageType::HOST != msgBuffer.msgInfo.msgType,
							 "Expected a HOST message from the host");

	// create a TCP socket and connect to the address sent by the host
	struct sockaddr_in hostTcpAddr = { 0 };
	hostTcpAddr.sin_family = AF_INET;
	hostTcpAddr.sin_addr.s_addr = msgBuffer.ipAddr;
	hostTcpAddr.sin_port = msgBuffer.portNum;

	char printAddr[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &msgBuffer.ipAddr, printAddr, INET_ADDRSTRLEN);
	LOGGER("Trying to connect to address: " << printAddr);
	LOGGER("Trying to connect to port: " << ntohs(msgBuffer.portNum));

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	FAILURE_TEST(connect(sock, (struct sockaddr *) &hostTcpAddr, sizeof(hostTcpAddr)) < 0, 
							 "connect() failed");

	// receive a start game message
	fd_set sockset;	
	FD_ZERO(&sockset);
	FD_SET(sock, &sockset);

	// get the message and make sure that the message is start
	MessageCommunicator::recvMessage(sock, &msgBuffer, sizeof(msgBuffer));
	MessageTranslator::decode(&msgBuffer);
	FAILURE_TEST(MessageTranslator::MessageType::START_GAME != msgBuffer.msgInfo.msgType, 
							 "Expected a START_GAME message");

	// send a start message back
	msgBuffer.msgInfo.msgType = MessageTranslator::MessageType::START_GAME;
	MessageTranslator::encode(&msgBuffer);
	MessageCommunicator::sendMessage(sock, &msgBuffer, sizeof(msgBuffer));

	// now the game may begin sending action commands back and forth
	cout << "Starting game" << endl;
}

void NetworkInterface::endGame()
{
	close(sock);
}

void NetworkInterface::sendPlayerAction(const PlayerCommand::Action action)
{
	msgBuffer.msgInfo.msgType = MessageTranslator::MessageType::ACTION;
	msgBuffer.action = action;

	MessageTranslator::encode(&msgBuffer);
	MessageCommunicator::sendMessage(sock, &msgBuffer, sizeof(msgBuffer));
}

void NetworkInterface::sendNewSuperBlock(const SuperBlock::SuperBlockType sbType)
{
	msgBuffer.msgInfo.msgType = MessageTranslator::MessageType::ACTION;
	msgBuffer.action = PlayerCommand::Action::TEST_NEW_BLOCK;
	msgBuffer.sbType = sbType;

	MessageTranslator::encode(&msgBuffer);
	MessageCommunicator::sendMessage(sock, &msgBuffer, sizeof(msgBuffer));
}

PlayerCommand::Action NetworkInterface::getPlayerAction()
{
	if (dataAvailable(sock)) {
		MessageCommunicator::recvMessage(sock, &msgBuffer, sizeof(msgBuffer));
		MessageTranslator::decode(&msgBuffer);
		return PlayerCommand::Action(msgBuffer.action);
	}
	else {
		return PlayerCommand::Action::ACTION_COUNT;
	}
}

SuperBlock::SuperBlockType NetworkInterface::getNewSuperBlockType() const
{
	return SuperBlock::SuperBlockType(msgBuffer.sbType);
}

int NetworkInterface::setupTCPServerSocket(const char *service) 
{
	// get a list of interface addresses
	struct ifaddrs *myaddrs, *ifa;
	FAILURE_TEST(getifaddrs(&myaddrs) != 0, "getifaddrs() failed");

	int servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	FAILURE_TEST(servSock < 0, "socket() failed");

	for (ifa = myaddrs; ifa != NULL; ifa = ifa->ifa_next) {
		if (!ifa->ifa_addr) { continue; }
		if (!(ifa->ifa_flags & IFF_UP)) { continue; }
		if (AF_INET != ifa->ifa_addr->sa_family) { continue; }

		struct sockaddr_in *ifaAddr = (struct sockaddr_in *) ifa->ifa_addr;

		char printAddr[INET_ADDRSTRLEN];
		if (inet_ntop(AF_INET, &ifaAddr->sin_addr.s_addr, printAddr, INET_ADDRSTRLEN)) {
			LOGGER("inet_ntop was successful");
			LOGGER("Address: " << printAddr);
			LOGGER("Port: " << ntohs(ifaAddr->sin_port));

			// don't want loop back address
			if (strncmp(printAddr, "127", 3) != 0) {
				// try to bind and listen on the interface
				if ((bind(servSock, ifa->ifa_addr, sizeof(struct sockaddr_in)) == 0)  && 
						 (listen(servSock, MAXPENDING) == 0)) {
					LOGGER("Successfully listening for client connections");
					break; // bind and listen successful
				}

				close(servSock);
				servSock = -1; // try next address
			}
		}
		else {
			LOGGER("inet_ntop was not successful");
			perror("inet() failed");
		}
	}

	freeifaddrs(myaddrs);
	return servSock;
}

bool NetworkInterface::dataAvailable(int socketNum)
{
	static fd_set sockset;
	static timeval noBlockTimeVal = { 0 , 0 };
	FD_ZERO(&sockset);
	FD_SET(socketNum, &sockset);

	int result = select(socketNum + 1, &sockset, NULL, NULL, &noBlockTimeVal);
	FAILURE_TEST(result < 0, "select() failed");
	if (1 == result && FD_ISSET(socketNum, &sockset)) {
		return true;
	}
	else {
		return false;
	}
}
