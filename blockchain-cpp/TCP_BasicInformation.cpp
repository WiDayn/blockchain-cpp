/*****************************************************************//**
 * \file   TCP_BasicInformation.cpp
 * \author WiDAYN
 * \date   25 March 2022
 *********************************************************************/
#include <string.h>
#include "TCP_BasicInformation.h"
#include "TCP_Ping.h"
#include "TCP_Head.h"

TCP_BasicInformation::TCP_BasicInformation(char* sendAddress, int port, BlockChain blockChain) {
	for (int i = 0; i < strlen(sendAddress); i++) {
		this->sendAddress[i] = sendAddress[i];
	}
	this->sendAddress[strlen(sendAddress)] = '\0';
	this->blockHeight = blockChain.blockChain.size();
	this->port = port;
}

bool TCP_BasicInformation::send(const char* address, int port)
{
	TCP_Client con = TCP_Client(address);
	con.createConnection();
	TCP_BasicInformation pingBack = TCP_BasicInformation();
	pingBack.blockHeight = blockHeight;
	memcpy(pingBack.sendAddress, sendAddress, sizeof(sendAddress));
	pingBack.port = port;
	TCP_Head head = TCP_Head("PingBack", sizeof(TCP_BasicInformation));
	char* package = (char*)malloc(sizeof(char) * (sizeof(TCP_Head) + sizeof(TCP_BasicInformation)));
	memcpy(package, &head, sizeof(TCP_Head));
	memcpy(package + sizeof(TCP_Head), &pingBack, sizeof(TCP_BasicInformation));
	con.sendMessage(package, sizeof(char) * (sizeof(TCP_Head) + sizeof(TCP_BasicInformation)));
	return false;
}
