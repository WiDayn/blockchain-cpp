/*****************************************************************//**
 * \file   TCP_BasicInformation.h
 * \author WiDAYN
 * \date   25 March 2022
 *********************************************************************/
#pragma once
#include "BlockChain.h"
#include "TCP_Client.h"

class TCP_BasicInformation
{
public:
	char sendAddress[20];
	int port;
	int blockHeight;

	TCP_BasicInformation() {};

	TCP_BasicInformation(char* sendAddress, int port, BlockChain blockChain);

	bool send(const char* address, int port);
};