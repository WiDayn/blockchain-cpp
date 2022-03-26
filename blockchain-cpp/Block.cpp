/*****************************************************************//**
 * \file   Block.cpp
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#include "Block.h"
#include "StringUtil.h"
#include "Transaction.h"

Block::Block(string previousHash)
{
	this->data = data;
	this->previousHash = previousHash;
	this->timeStrap = time(0);
	this->hash = calculateHash();
}

Block::~Block()
{
}

string Block::calculateHash() {
	return StringUtil::sha256(previousHash + StringUtil::longToString(timeStrap) + to_string(nonce) + merkleRoot + data);
}

string Block::mineBlock(int difficulty) {
	merkleRoot = StringUtil::getMerkleRoot(transactions);
	string target = "";
	for (int i = 1; i <= difficulty; i++) {
		target.append("0");
	}
	while (hash.substr(0, difficulty) != target) {
		nonce++;
		hash = calculateHash();
	}

	StringUtil::printfSuccess("Block Mined!!! : " + hash + "\n");
	return hash;
}

bool Block::addTransaction(Transaction transaction, map<string, TransactionOutput>& UTXOs)
{
	if (transaction.sender == "NULL") return false;
	if ((previousHash != "0")) {
		if ((transaction.processTransaction(UTXOs) != true)) {
			StringUtil::printfError("#Transaction failed to process. Discarded.");
			return false;
		}
	}
	transactions.push_back(transaction);
	StringUtil::printfSuccess("#Transaction Successfully added to Block");
	return true;
}
