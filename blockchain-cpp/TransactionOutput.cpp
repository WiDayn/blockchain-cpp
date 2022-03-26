/*****************************************************************//**
 * \file   TransactionOutput.cpp
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#include "TransactionOutput.h"
#include "StringUtil.h"

TransactionOutput::TransactionOutput(string reciepient, float value, string parentTransactionId)
{
	this->reciepient = reciepient;
	this->value = value;
	this->parentTransactionId = parentTransactionId;
	this->id = StringUtil::sha256(reciepient + to_string(value) + parentTransactionId);
}

bool TransactionOutput::isMine(string publicKey)
{
	return (publicKey == reciepient);
}
