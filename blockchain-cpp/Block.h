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
	string hash; // �����Hash
	string previousHash; // ǰһ�������Hash
	string merkleRoot;
	vector<Transaction> transactions;

	Block(string previousHash);
	~Block();

	string calculateHash();

	string mineBlock(int difficulty);

	bool addTransaction(Transaction transaction, map<string, TransactionOutput>& UTXOs);

private:
	string data; // ��Ҫ�������Ϣ
	long timeStrap; // �����ʱ��
	int nonce;
};
