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
#include <boost/serialization/access.hpp>

using namespace std;

class Transaction
{
public:
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& transactionId;
		ar& sender;
		ar& reciepient;
		ar& value;
		ar& signature;
		ar& signatureLength;
		ar& inputs;
		ar& outputs;
		ar& minimumTransaction;
		ar& sequence;
	}

	string transactionId;
	string sender;
	string reciepient;
	float value;

	string signature;
	size_t signatureLength;

	vector<TransactionInput> inputs;
	vector<TransactionOutput> outputs;

	float minimumTransaction;

	Transaction() {};

	Transaction(string from);
	Transaction(string from, string to, float value, vector<TransactionInput> input, float minimumTransaction);
	Transaction(string from, string to, float value, vector<TransactionInput> input);

	friend class boost::serialization::access;

	string calulateHash();

	void generateSignature(string privateKey);

	bool verifiySignature();

	bool processTransaction(map<string, TransactionOutput>& UTXOs);

	float getInputsValue();

	float getOutputsValue();

private:
	int sequence;
};

