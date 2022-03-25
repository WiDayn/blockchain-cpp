#pragma once
class TCP_Send
{
public:
	const char* address;

	TCP_Send() {};

	static void SendPing(const char* address, int port);

	static void SendBasicInformation(const char* address, int port);
};

