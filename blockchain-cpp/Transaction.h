/*****************************************************************//**
 * \file   Transaction.h
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#pragma once
#include <openssl/ossl_typ.h>
#include <string>
#include <vector>
#include <openssl/err.h>
#include <map>
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
	size_t signatureLength;

	vector<TransactionInput> inputs;
	vector<TransactionOutput> outputs;

	float minimumTransaction;

	Transaction() {};

	Transaction(unsigned char* from);
	Transaction(unsigned char* from, unsigned char* to, float value, vector<TransactionInput> input, float minimumTransaction);
	Transaction(unsigned char* from, unsigned char* to, float value, vector<TransactionInput> input);

	string calulateHash();

	void generateSignature(unsigned char* privateKey);

	bool verifiySignature();

	bool processTransaction(map<string, TransactionOutput>& UTXOs);

	float getInputsValue();

	float getOutputsValue();

private:
	int sequence;
};

