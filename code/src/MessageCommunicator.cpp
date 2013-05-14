#include "MessageCommunicator.h"
#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstdlib>
#include <sys/select.h>
#include <unistd.h>

using namespace std;

MessageCommunicator::MessageCommunicator() 
{ }

int MessageCommunicator::sendMessage(int socket, const void *msg, size_t msgSize)
{
	size_t networkMsgSize = htons(msgSize); // convert to network format

	// send the size of the message
	if (send(socket, &networkMsgSize, sizeof(uint16_t), 0) < 0) {
		perror("NETWORK: message size send failed");
		exit(-1);
	}

	// send the message
	if (send(socket, msg, msgSize, 0) < 0) {
		perror("NETWORK: message send failed");
		exit(-1);
	}

	return msgSize;
}

int MessageCommunicator::recvMessage(int socket, void *msg, size_t msgSize)
{
	// receive the size of the message
	if (recv(socket, &msgSize, sizeof(uint16_t), 0) < 0) {
		perror("NETWORK: message size receive failed");
		exit(-1);
	}
	msgSize = ntohs(msgSize);

	// receive the message
	if (recv(socket, msg, msgSize, 0) < 0) {
		perror("NETWORK: message received failed");
		exit(-1);
	}

	return msgSize;
}
