#pragma once
#include <openssl/evp.h>
#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <stdexcept>
#include <cstddef>
#include <iostream>
#include <string>
#include <map>
#include "Transaction.h"
#include "TransactionOutput.h"
class Wallet {
public:
	EVP_PKEY* pkey = NULL;
	unsigned char* publicKeyChar;
	unsigned char* privateKeyChar;

	// 只记录属于当前钱包的交易
	map<string, TransactionOutput> UTXOs;

	Wallet();

	int generateKeyPair();

	float getBalance(map<string, TransactionOutput> UTXOs);

	Transaction sendFunds(unsigned char* recipient, float value, map<string, TransactionOutput> UTXOs);

	static EC_GROUP* getDefaultEcGroup();
};
