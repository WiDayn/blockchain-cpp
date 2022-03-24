/*****************************************************************//**
 * \file   TCP_Server.cpp
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#include "TCP_Server.h"

TCP_Server::TCP_Server() {
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = PF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int fd_bind = bind(serverSocket, (struct sockaddr*)&addr, sizeof(addr));
	if (fd_bind == -1) {
		StringUtil::printfError("bind ");
		return;
	}
	int fd_listen = listen(serverSocket, 0);
	if (fd_listen == -1) {
		StringUtil::printfError("listen ");
		return;
	}
	memset(&client, 0, sizeof(client));
	int len = sizeof(client);
	SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&client, &len);
	if (clientSocket == -1) {
		StringUtil::printfError("accept ");
		return;
	}
	else {
		char IPdotdec[20];
		inet_ntop(AF_INET, (void*)&client.sin_addr, IPdotdec, 16);
		StringUtil::printfSuccess(IPdotdec);
	}
	WCHAR ip[16] = TEXT("0");
	char buf[100];
	memset(buf, 0, sizeof(buf));
	int ret_rcv = recv(clientSocket, buf, sizeof(buf), NULL);
	if (ret_rcv == SOCKET_ERROR) {
		StringUtil::printfError("recv ");
		return;
	}
	else {
		InetNtop(AF_INET, &client.sin_addr, ip, 100);
		printf("%s:%s\n", ip, buf);
	}
	//¹Ø±ÕsocketÌ×½Ó×Ö
	closesocket(clientSocket);
	closesocket(serverSocket);
	//ÖÕÖ¹Á´½Ó¿â
	WSACleanup();
}