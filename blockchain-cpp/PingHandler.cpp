/*****************************************************************//**
 * \file   PingHandler.cpp
 * \author WiDAYN
 * \date   25 March 2022
 *********************************************************************/
#include "PingHandler.h"
#include "TCP_Ping.h"
#include <vcruntime_string.h>
#include <stdio.h>
#include <string.h>

PingHandler::PingHandler(char* buf)
{
	TCP_Ping ping;
	memset(&ping, 0, sizeof(ping));
	printf("%d", strlen(buf));
	memcpy(&ping, buf, sizeof(TCP_Ping));
}
