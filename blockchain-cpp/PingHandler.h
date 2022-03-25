/*****************************************************************//**
 * \file   PingHandler.h
 * \author WiDAYN
 * \date   25 March 2022
 *********************************************************************/
#pragma once
#include "BlockChain.h"
#include "TCP_Head.h"

class PingHandler
{
public:
	PingHandler(char* ip, TCP_Head head, char* buf, BlockChain& blockChain);
};
