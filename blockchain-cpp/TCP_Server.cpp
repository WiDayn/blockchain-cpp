/*****************************************************************//**
 * \file   TCP_Server.cpp
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#include<thread>
#include "TCP_Server.h"
#include "Routes.h"
#include "TCP_Head.h"

void receiveTCP(SOCKET clientSocket, SOCKADDR_IN client, BlockChain& blockChain) {
	if (clientSocket == -1) {
		StringUtil::printfError("accept ");
		return;
	}
	char ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &client.sin_addr, ip, sizeof(ip));
	TCP_Head head = TCP_Head();
	memset(&head, 0, sizeof(head));
	char buf[100];
	memset(buf, 0, sizeof(buf));
	int ret_rcv = recv(clientSocket, buf, sizeof(TCP_Head), NULL);
	if (ret_rcv == SOCKET_ERROR) {
		StringUtil::printfError("Receive error");
		return;
	}
	memcpy(&head, buf, sizeof(TCP_Head));
	if (head.length <= 0) {
		StringUtil::printfError("TCP包错误");
		return;
	}
	int Rlen = 0;
	long long len = head.length;
	char* data = (char*)malloc(sizeof(char) * len);
	while (len > 0) {
		memset(buf, 0, sizeof(buf));
		ret_rcv = recv(clientSocket, buf, sizeof(buf), NULL);
		if (ret_rcv == SOCKET_ERROR) {
			StringUtil::printfError("Receive error");
			return;
		}
		memcpy(data + Rlen, buf, min(len, sizeof(buf)));
		len -= sizeof(buf);
		Rlen += sizeof(buf);
	}
	Routes::HandleBuf(ip, head, data, blockChain);
	closesocket(clientSocket);
	return;
}

TCP_Server::TCP_Server(int PORT, BlockChain& blockChain) {
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = PF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int fd_bind = bind(serverSocket, (struct sockaddr*)&addr, sizeof(addr));
	if (fd_bind == -1) {
		StringUtil::printfError("Bind port error");
		return;
	}
	int fd_listen = listen(serverSocket, 0);
	if (fd_listen == -1) {
		StringUtil::printfError("Listen error");
		return;
	}
	while (1) {
		memset(&client, 0, sizeof(client));
		int len = sizeof(client);
		SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&client, &len);
		// 开一个子线程去处理请求，自己继续监听
		thread Handler(receiveTCP, clientSocket, client, ref(blockChain));
		Handler.detach();
	}
	closesocket(serverSocket);
	WSACleanup();
}