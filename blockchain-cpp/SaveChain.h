/*****************************************************************//**
 * \file   SaveChain.h
 * \author WiDAYN
 * \date   25 March 2022
 *********************************************************************/
#pragma once
#include "BlockChain.h"
#include "ini.h"

class SaveChain
{
public:
	static bool save(BlockChain& blockChain, ini_t* config);
	static bool load(BlockChain& blockChain, ini_t* config);
};
