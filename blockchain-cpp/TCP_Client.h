/*****************************************************************//**
 * \file   TCP_Client.h
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#include <Winsock2.h>
#include <WS2tcpip.h>
#include "StringUtil.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define PORT 8888
#define IP "127.0.0.1"

class TCP_Client {
private:
	WSADATA wsaData;
	SOCKET fd_socket;
	SOCKADDR_IN addr;

public:
	int err = 0;  //0: no error 1:winsock load error   2:failed to create socket  3:failed to connect
	int state = 0;
	TCP_Client();

	bool createConnection();

	bool sendMessage(const char* s);

	bool closeConnection();
};
