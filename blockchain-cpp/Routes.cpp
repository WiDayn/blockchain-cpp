/*****************************************************************//**
 * \file   Routes.cpp
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#include "Routes.h"
#include <WTypesbase.h>
#include <stdio.h>
#include "PingHandler.h"



void Routes::HandleBuf(char* ip, TCP_Head head, char* buf)
{
	if (strcmp(head.type, "Ping") == 0) {
		PingHandler handler = PingHandler(buf);
	}
}
