/*****************************************************************//**
 * \file   BlockChain.h
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#pragma once
#include<vector>
#include<map>
#include "Block.h"
#include "Transaction.h"

class BlockChain {
public:
	vector<Block> blockChain;
	static const int difficulty = 4;
	Transaction genesisTransaction;

	void addBlock(Block& block);

	bool isChainValid();
};