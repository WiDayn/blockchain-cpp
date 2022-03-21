#pragma once
#include <string>
#include <time.h>
#include "StringUtil.h"
using namespace std;

class Block
{
public:
	string hash; // 本身的Hash
	string previousHash; // 前一个区块的Hash

	Block(string data, string previousHas);
	~Block();

	string calculateHash();

	void mineBlock(int difficulty);


private:
	string data; // 需要储存的信息
	long timeStrap; // 创造的时间
	int nonce;
};

Block::Block(string data, string previousHash)
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
	return StringUtil::sha256(previousHash + StringUtil::longToString(timeStrap) + to_string(nonce) + data);
}

void Block::mineBlock(int difficulty) {
	string target = "";
	for (int i = 1; i <= difficulty; i++) {
		target.append("0");
	}
	while (hash.substr(0, difficulty) != target) {
		nonce++;
		hash = calculateHash();
	}

	StringUtil::printfGreen("Block Mined!!! : " + hash + "\n");
}