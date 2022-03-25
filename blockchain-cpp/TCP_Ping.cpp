#include "TCP_Ping.h"
#include <vcruntime_string.h>
#include <string.h>
#include "TCP_Client.h"
#include "TCP_Head.h"

TCP_Ping::TCP_Ping()
{
}

TCP_Ping::TCP_Ping(char* requestAddress, char* callBackAddress, int callBackPort)
{
	for (int i = 0; i < strlen(requestAddress); i++) {
		this->requestAddress[i] = requestAddress[i];
	}
	this->requestAddress[strlen(requestAddress)] = '\0';
	for (int i = 0; i < strlen(requestAddress); i++) {
		this->callBackAddress[i] = callBackAddress[i];
	}
	this->callBackAddress[strlen(callBackAddress)] = '\0';
	this->callBackPort = callBackPort;
}

bool TCP_Ping::send(const char* address, int port)
{
	TCP_Client con = TCP_Client(address);
	con.createConnection();
	TCP_Ping ping = TCP_Ping((char*)address, (char*)address, port);
	TCP_Head head = TCP_Head("Ping", sizeof(TCP_Ping));
	char* package = (char*)malloc(sizeof(char) * (sizeof(TCP_Head) + sizeof(TCP_Ping)));
	memcpy(package, &head, sizeof(TCP_Head));
	memcpy(package + sizeof(TCP_Head), &ping, sizeof(TCP_Ping));
	con.sendMessage(package, sizeof(char) * (sizeof(TCP_Head) + sizeof(TCP_Ping)));
	return true;
}