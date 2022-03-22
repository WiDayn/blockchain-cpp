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
