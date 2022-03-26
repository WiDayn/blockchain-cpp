/*****************************************************************//**
 * \file   TransactionOutput.h
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#pragma once
#include <string>
using namespace std;

class TransactionOutput
{
public:
	string id;
	string reciepient;
	float value;
	string parentTransactionId;

	TransactionOutput() {};

	TransactionOutput(string reciepient, float value, string parentTransactionId);

	bool isMine(string publicKey);

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& id;
		ar& reciepient;
		ar& value;
		ar& parentTransactionId;
	}
};

