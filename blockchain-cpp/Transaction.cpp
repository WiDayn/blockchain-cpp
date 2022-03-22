#include "Transaction.h"
#include "StringUtil.h"
#include <openssl/evp.h>
#include<openssl/pem.h>
#include <iostream>

Transaction::Transaction(unsigned char* from, unsigned char* to, float value, vector<TransactionInput> inputs)
{
	this->sender = from;
	this->reciepient = to;
	this->value = value;
	this->inputs = inputs;
	signatureLength = NULL;
}

string Transaction::calulateHash()
{
	sequence++;
	
	return StringUtil::sha256(
		StringUtil::unsignedCharToString(sender) + StringUtil::unsignedCharToString(reciepient) + to_string(value) + to_string(sequence)
	);
}

void Transaction::generateSignature(unsigned char* privateKey)
{
    string data = StringUtil::unsignedCharToString(sender) + StringUtil::unsignedCharToString(reciepient) + to_string(value);
	signature = StringUtil::sign(privateKey, data, &signatureLength);
}

bool Transaction::verifiySignature()
{
	string data = StringUtil::unsignedCharToString(sender) + StringUtil::unsignedCharToString(reciepient) + to_string(value);
    return StringUtil::verifySign(sender, data, signature, &signatureLength);
}
