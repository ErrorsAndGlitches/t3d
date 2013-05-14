#include "MessageTranslator.h"
#include <arpa/inet.h>

MessageTranslator::MessageTranslator() 
{
}

void MessageTranslator::encode(TetrisNetworkMessage *tetMsg)
{
	// convert the message header
	tetMsg->msgInfo.magic = htonl(tetMsg->msgInfo.magic);
	tetMsg->msgInfo.msgType = htons(tetMsg->msgInfo.msgType);

	// convert fields based on message type
	if (HOST == tetMsg->msgInfo.msgType) {
		tetMsg->ipAddr = htonl(tetMsg->ipAddr);
		tetMsg->portNum = htons(tetMsg->portNum);
	}
	else if (NEW_SUPER_BLOCK == tetMsg->msgInfo.msgType || 
					 ACTION == tetMsg->msgInfo.msgType) {
		tetMsg->action = htons(tetMsg->action);
		tetMsg->sbType = htons(tetMsg->sbType);
	}
}

void MessageTranslator::decode(TetrisNetworkMessage *tetMsg)
{
	// convert the message header
	tetMsg->msgInfo.magic = htonl(tetMsg->msgInfo.magic);
	tetMsg->msgInfo.msgType = htons(tetMsg->msgInfo.msgType);

	// convert fields based on message type
	if (HOST == tetMsg->msgInfo.msgType) {
		tetMsg->ipAddr = ntohl(tetMsg->ipAddr);
		tetMsg->portNum = ntohs(tetMsg->portNum);
	}
	else if (NEW_SUPER_BLOCK == tetMsg->msgInfo.msgType || 
					 ACTION == tetMsg->msgInfo.msgType) {
		tetMsg->action = ntohs(tetMsg->action);
		tetMsg->sbType = ntohs(tetMsg->sbType);
	}
}
