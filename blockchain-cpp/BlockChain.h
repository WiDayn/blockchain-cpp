#include<vector>
#include "Block.h"

#pragma once

class BlockChain {
public:
	vector<Block> blockChain;
	static const int difficulty = 4;

	void addBlock();

	bool isChainValid();
};