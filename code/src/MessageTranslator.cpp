#include "MessageTranslator.h"
#include <arpa/inet.h>
#include 	<iostream>

using namespace std;

MessageTranslator::MessageTranslator() 
{
}

void MessageTranslator::encode(TetrisNetworkMessage *tetMsg)
{
	// convert fields based on message type
	if (HOST == tetMsg->msgInfo.msgType) {
		tetMsg->ipAddr = htonl(tetMsg->ipAddr);
		tetMsg->portNum = htons(tetMsg->portNum);
	}
	else if (ACTION == tetMsg->msgInfo.msgType) {
		tetMsg->action = htons(tetMsg->action);
		tetMsg->sbType = htons(tetMsg->sbType);
	}

	// convert the message header (do this second because we need the message
	// type to decide the correct structure to convert
	tetMsg->msgInfo.magic = htonl(tetMsg->msgInfo.magic);
	tetMsg->msgInfo.msgType = htons(tetMsg->msgInfo.msgType);
}

void MessageTranslator::decode(TetrisNetworkMessage *tetMsg)
{
	// convert the message header
	tetMsg->msgInfo.magic = ntohl(tetMsg->msgInfo.magic);
	tetMsg->msgInfo.msgType = ntohs(tetMsg->msgInfo.msgType);

	// convert fields based on message type
	if (HOST == tetMsg->msgInfo.msgType) {
		tetMsg->ipAddr = ntohl(tetMsg->ipAddr);
		tetMsg->portNum = ntohs(tetMsg->portNum);
	}
	else if (ACTION == tetMsg->msgInfo.msgType) {
		tetMsg->action = ntohs(tetMsg->action);
		tetMsg->sbType = ntohs(tetMsg->sbType);
	}
}
