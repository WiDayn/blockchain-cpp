#pragma once
#include <string>
#include <time.h>
#include "StringUtil.h"
using namespace std;

class Block
{
public:
	string hash; // �����Hash
	string previousHash; // ǰһ�������Hash

	Block(string data, string previousHas);
	~Block();

	string calculateHash();

	void mineBlock(int difficulty);


private:
	string data; // ��Ҫ�������Ϣ
	long timeStrap; // �����ʱ��
	int nonce;
};
