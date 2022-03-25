/*****************************************************************//**
 * \file   TCP_Send.cpp
 * \author WiDAYN
 * \date   25 March 2022
 *********************************************************************/
#include "TCP_Send.h"
#include "TCP_Client.h"
#include "TCP_Ping.h"
#include "TCP_Head.h"

void TCP_Send::SendPing(const char* address)
{
	TCP_Client con = TCP_Client(address);
	con.createConnection();

	char* data = (char*)malloc(sizeof(char) * sizeof(TCP_Ping));
	TCP_Ping k = TCP_Ping((char*)"127.0.0.1", (char*)"127.0.0.1", 8888);
	int sendSiz = sizeof(k);
	printf("%d", sizeof(TCP_Ping));
	memcpy(data, &k, sizeof(TCP_Ping));
	TCP_Head head = TCP_Head("Ping", sizeof(TCP_Ping));
	char* package = (char*)malloc(sizeof(char) * (sizeof(TCP_Head) + sizeof(TCP_Ping)));
	memcpy(package, &head, sizeof(TCP_Head));
	memcpy(package + sizeof(TCP_Head), data, sizeof(TCP_Ping));
	con.sendMessage(package, sizeof(char) * (sizeof(TCP_Head) + sizeof(TCP_Ping)));
}
