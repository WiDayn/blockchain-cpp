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
	friend class boost::serialization::access;
	template<typename Archive>
	void serialize(Archive& ar, const unsigned int file_version)
	{
		ar& blockChain;
		ar& difficulty;
		ar& genesisTransaction;
	}

	vector<Block> blockChain;
	int difficulty = 4;
	Transaction genesisTransaction;

	void addBlock(Block& block);

	bool isChainValid();

	Block getTop();
};