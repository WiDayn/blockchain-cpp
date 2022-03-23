#include <openssl/evp.h>
#include<openssl/pem.h>
#include <iostream>
#include "Transaction.h"
#include "StringUtil.h"


Transaction::Transaction(unsigned char* from, unsigned char* to, float value, vector<TransactionInput> inputs, float minimumTransaction)
{
	this->sender = from;
	this->reciepient = to;
	this->value = value;
	this->inputs = inputs;
	this->minimumTransaction = minimumTransaction;
	signatureLength = NULL;
}

Transaction::Transaction(unsigned char* from, unsigned char* to, float value, vector<TransactionInput> input)
{
	this->sender = from;
	this->reciepient = to;
	this->value = value;
	this->inputs = input;
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

bool Transaction::processTransaction(map<string, TransactionOutput>& UTXOs)
{
	if (!verifiySignature()) {
		StringUtil::printfError("#Transaction Signature failed to verify");
	}

	for (int i = 0; i < inputs.size(); i++) {
		inputs[i].UTXO = UTXOs[inputs[i].TransactionOutputId];
	}

	if (getInputsValue() < minimumTransaction) {
		StringUtil::printfError("#Transaction Inputs to small: " + to_string(getInputsValue()));
		return false;
	}

	float leftOver = getInputsValue() - value;
	transactionId = calulateHash();

	outputs.push_back(TransactionOutput(reciepient, value, transactionId));
	outputs.push_back(TransactionOutput(sender, leftOver, transactionId));

	for (TransactionOutput o : outputs) {
		UTXOs.insert(pair<string, TransactionOutput>(o.id, o));
	}

	for (TransactionInput i : inputs) {
		if (i.UTXO.id.empty()) continue;
		UTXOs.erase(i.UTXO.id);
	}

	return true;
}

float Transaction::getInputsValue()
{
	float total = 0;
	for (TransactionInput i : inputs) {
		if (!i.UTXO.id.empty()) {
			total += i.UTXO.value;
		}
	}
	return total;
}

float Transaction::getOutputsValue()
{
	float total = 0;
	for (TransactionOutput o : outputs) {
		total += o.value;
	}
	return total;
}
