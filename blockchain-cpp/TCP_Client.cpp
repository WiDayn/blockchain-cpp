/*****************************************************************//**
 * \file   TCP_Client.cpp
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#include "TCP_Client.h"

TCP_Client::TCP_Client(const char* address)
{
	WSADATA wsaData;
	this->address = address;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	fd_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (fd_socket == -1) {
		StringUtil::printfError("Socket error");
	}
}

TCP_Client::~TCP_Client()
{
	closeConnection();
}

bool TCP_Client::createConnection() {
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = PF_INET;
	addr.sin_port = htons(PORT);
	struct in_addr s;
	inet_pton(AF_INET, address, (void*)&s);
	addr.sin_addr.s_addr = s.s_addr;

	int fd_connect = connect(fd_socket, (struct sockaddr*)&addr, sizeof(addr));
	if (fd_connect == -1) {
		StringUtil::printfError("connect ");
		return false;
	}
	else {
		StringUtil::printfSuccess("连接服务器成功\n");
		return true;
	}
}

bool TCP_Client::sendMessage(const char* s, int len) {
	//发送消息
	int ret_send = send(fd_socket, s, len, NULL);
	if (ret_send == SOCKET_ERROR) {
		StringUtil::printfError("send ");
		return false;
	}
	else {
		StringUtil::printfSuccess("发送消息成功\n");
	}
	return true;
}

bool TCP_Client::closeConnection() {
	//关闭socket套接字
	closesocket(fd_socket);
	//终止链接库
	WSACleanup();
	return true;
}