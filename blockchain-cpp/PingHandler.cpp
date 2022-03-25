/*****************************************************************//**
 * \file   PingHandler.cpp
 * \author WiDAYN
 * \date   25 March 2022
 *********************************************************************/
#include "PingHandler.h"
#include "TCP_Ping.h"
#include "TCP_Head.h"
#include "TCP_BasicInformation.h"
#include <vcruntime_string.h>
#include <stdio.h>
#include <string.h>

PingHandler::PingHandler(char* ip, TCP_Head head, char* buf, BlockChain& blockChain)
{
	/*
		PingHandler会向请求方提供的地址返回本节点的基本情况
	*/
	TCP_Ping ping;
	memset(&ping, 0, sizeof(ping));
	memcpy(&ping, buf, sizeof(TCP_Ping));
	TCP_BasicInformation pingback = TCP_BasicInformation(ping.callBackAddress, ping.callBackPort, blockChain);
	pingback.send(ping.callBackAddress, ping.callBackPort);

}
