#pragma once
#include <openssl/evp.h>
#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <stdexcept>
#include <cstddef>
#include <iostream>
#include "StringUtil.h"

class Wallet {
public:
	EVP_PKEY* pkey = NULL;
	unsigned char* publicKeyChar;
	unsigned char* privateKeyChar;

	Wallet();

	int generateKeyPair();
	static EC_GROUP* getDefaultEcGroup();
};
