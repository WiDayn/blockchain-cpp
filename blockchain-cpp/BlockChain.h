#pragma once
#include<vector>
#include<map>
#include "Block.h"
#include "Transaction.h"

class BlockChain {
public:
	vector<Block> blockChain;
	static const int difficulty = 4;

	void addBlock(Block block);

	bool isChainValid();

	void addTransaction(Transaction genesisTransaction,  map <string, TransactionOutput> UTXOs);
};