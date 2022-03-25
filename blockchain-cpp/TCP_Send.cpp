/*****************************************************************//**
 * \file   TCP_Send.cpp
 * \author WiDAYN
 * \date   25 March 2022
 *********************************************************************/
#include "TCP_Send.h"
#include "TCP_Client.h"
#include "TCP_Ping.h"
#include "TCP_Head.h"

void TCP_Send::SendPing(const char* address, int port)
{
	TCP_Client con = TCP_Client(address);
	con.createConnection();

	TCP_Ping ping = TCP_Ping((char*)address, (char*)address, port);
	TCP_Head head = TCP_Head("Ping", sizeof(TCP_Ping));
	char* package = (char*)malloc(sizeof(char) * (sizeof(TCP_Head) + sizeof(TCP_Ping)));
	memcpy(package, &head, sizeof(TCP_Head));
	memcpy(package + sizeof(TCP_Head), &ping, sizeof(TCP_Ping));
	con.sendMessage(package, sizeof(char) * (sizeof(TCP_Head) + sizeof(TCP_Ping)));
}

void TCP_Send::SendBasicInformation(const char* address, int port)
{
	TCP_Client con = TCP_Client(address);
	con.createConnection();

	TCP_Ping ping = TCP_Ping((char*)"127.0.0.1", (char*)"127.0.0.1", port);
	TCP_Head head = TCP_Head("Ping", sizeof(TCP_Ping));
	char* package = (char*)malloc(sizeof(char) * (sizeof(TCP_Head) + sizeof(TCP_Ping)));
	memcpy(package, &head, sizeof(TCP_Head));
	memcpy(package + sizeof(TCP_Head), &ping, sizeof(TCP_Ping));
	con.sendMessage(package, sizeof(char) * (sizeof(TCP_Head) + sizeof(TCP_Ping)));
}