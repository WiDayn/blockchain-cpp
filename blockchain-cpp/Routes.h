/*****************************************************************//**
 * \file   Routes.h
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#pragma once
#include <WTypesbase.h>
#include "TCP_Head.h"
class Routes
{
public:
	Routes() {};

	static void HandleBuf(char* ip, TCP_Head head, char* buf);
};

