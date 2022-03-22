#include "Transaction.h"
#include "StringUtil.h"

Transaction::Transaction(EVP_PKEY* from, EVP_PKEY* to, float value, vector<TransactionInput> inputs)
{
	this->sender = from;
	this->reciepient = to;
	this->value = value;
	this->inputs = inputs;
}

string Transaction::calulateHash()
{
	sequence++;
	
	return StringUtil::sha256(
		StringUtil::publicKeyToString(sender) + StringUtil::publicKeyToString(reciepient) + to_string(value) + to_string(sequence)
	);
}
