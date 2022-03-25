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

#pragma comment(lib,"ws2_32.lib")		//º”‘ÿ“¿¿µ

#define PORT 8888

class TCP_Server
{
public:
	WSADATA wsaData;
	SOCKET serverSocket;
	SOCKADDR_IN addr;
	SOCKADDR_IN client;

	TCP_Server();
};

