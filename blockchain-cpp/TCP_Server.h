/*****************************************************************//**
 * \file   TCP_Server.h
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <Ws2tcpip.h>
#include <Winsock2.h>
#include "StringUtil.h"
#include "BlockChain.h"

class TCP_Server
{
public:
	WSADATA wsaData;
	SOCKET serverSocket;
	SOCKADDR_IN addr;
	SOCKADDR_IN client;
	int PORT;

	TCP_Server(int PORT, BlockChain& blockChain);
};

