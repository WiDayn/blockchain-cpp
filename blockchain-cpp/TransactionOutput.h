#pragma once
#include <string>
using namespace std;

class TransactionOutput
{
public:
	string id;
	unsigned char* reciepient;
	float value;
	string parentTransactionId;

	TransactionOutput() {};

	TransactionOutput(unsigned char* reciepient, float value, string parentTransactionId);

	bool isMine(unsigned char* publicKey);
};

