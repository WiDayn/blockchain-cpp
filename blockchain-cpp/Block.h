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
	string hash; // 本身的Hash
	string previousHash; // 前一个区块的Hash
	string merkleRoot;
	vector<Transaction> transactions;

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
