#include "TransactionOutput.h"
#include "StringUtil.h"

TransactionOutput::TransactionOutput(unsigned char* reciepient, float value, string parentTransactionId)
{
	this->reciepient = reciepient;
	this->value = value;
	this->parentTransactionId = parentTransactionId;
	this->id = StringUtil::sha256(StringUtil::unsignedCharToString(reciepient) + to_string(value) + parentTransactionId);
}

bool TransactionOutput::isMine(unsigned char* publicKey)
{
	return (publicKey == reciepient);
}
 