#pragma once
class TCP_Ping
{
public:
	char requestAddress[20];
	char callBackAddress[20];
	int callBackPort;

	TCP_Ping();

	TCP_Ping(char* requestAddress, char* callBackAddress, int callBackPort);

	bool send(const char* address, int port);
};