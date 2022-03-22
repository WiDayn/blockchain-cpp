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
	EVP_PKEY* sender;
	EVP_PKEY* reciepient;
	float value;

	vector<TransactionInput> inputs;
	vector<TransactionOutput> outputs;

	Transaction(EVP_PKEY* from, EVP_PKEY* to, float value, vector<TransactionInput> input);

	string calulateHash();
private:
	int sequence;
};

