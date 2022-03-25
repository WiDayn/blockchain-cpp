#include "TCP_Ping.h"
#include <vcruntime_string.h>
#include <string.h>

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
