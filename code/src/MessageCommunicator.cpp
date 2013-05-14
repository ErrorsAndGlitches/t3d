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
	msgSize = htons(msgSize); // convert to network format

	// send the size of the message
	if (send(socket, &msgSize, sizeof(uint16_t), 0) < 0) {
		cout << "NETWORK: message size send failed" << endl;
		exit(-1);
	}

	// send the message
	if (send(socket, msg, msgSize, 0) < 0) {
		cout << "NETWORK: message send failed" << endl;
		exit(-1);
	}

	return msgSize;
}

int MessageCommunicator::recvMessage(int socket, void *msg, size_t msgSize)
{
	// receive the size of the message
	if (recv(socket, &msgSize, sizeof(uint16_t), 0) < 0) {
		cout << "NETWORK: message size receive failed" << endl;
		exit(-1);
	}
	msgSize = ntohs(msgSize);

	// receive the message
	if (recv(socket, msg, msgSize, 0) < 0) {
		cout << "NETWORK: message receive failed" << endl;
		exit(-1);
	}

	return msgSize;
}
