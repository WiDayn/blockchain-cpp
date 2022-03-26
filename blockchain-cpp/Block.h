/*****************************************************************//**
 * \file   Block.h
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#pragma once
#include <string>
#include <time.h>
#include "TransactionInput.h"
#include "TransactionOutput.h"
#include "Transaction.h"

using namespace std;


class Block
{
public:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& data;
		ar& timeStrap;
		ar& nonce;
		ar& hash;
		ar& previousHash;
		ar& merkleRoot;
		ar& transactions;
	}

	string hash; // 本身的Hash
	string previousHash; // 前一个区块的Hash
	string merkleRoot;
	vector<Transaction> transactions;

	Block() {};

	Block(string previousHash);
	~Block();

	string calculateHash();

	string mineBlock(int difficulty);

	bool addTransaction(Transaction transaction, map<string, TransactionOutput>& UTXOs);

private:
	string data; // 需要储存的信息
	long timeStrap; // 创造的时间
	int nonce;
};
