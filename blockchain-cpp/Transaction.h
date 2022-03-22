#pragma once
#pragma once
#include <openssl/ossl_typ.h>
#include <string>
#include <vector>
#include <openssl/err.h>
#include "TransactionInput.h"
#include "TransactionOutput.h"

using namespace std;

class Transaction
{
public:
	string transactionId;
	unsigned char* sender;
	unsigned char* reciepient;
	float value;
	unsigned char* signature;

	vector<TransactionInput> inputs;
	vector<TransactionOutput> outputs;

	Transaction(unsigned char* from, unsigned char* to, float value, vector<TransactionInput> input);

	string calulateHash();

	void generateSignature(unsigned char* privateKey);

	bool verifiySignature();

private:
	int sequence;
};

