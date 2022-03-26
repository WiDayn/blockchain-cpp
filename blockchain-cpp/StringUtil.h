/*****************************************************************//**
 * \file   StringUtil.h
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#pragma once
#include <iomanip>
#include <sstream>
#include <string>
#include <openssl/sha.h>
#include <openssl/ossl_typ.h>
#include <vector>
#include "Transaction.h"
using namespace std;

class StringUtil {
public:
	static string sha256(string str);
	static string longToString(long int t);
	static string unsignedCharToString(unsigned char* input);
	static string WcharToString(wchar_t* wchar);
	static unsigned char* publicKeyToUnsignedChar(EVP_PKEY* key);
	static string publicKeyToString(EVP_PKEY* key);
	static unsigned char* privateKeyToUnsignedChar(EVP_PKEY* key);
	static string privateKeyToString(EVP_PKEY* key);
	static void printfSuccess(string s);
	static void printfError(string s);
	static void printfInformation(string s);
	static size_t sign(EVP_PKEY* key, string message, size_t messageLength, string& signature, size_t* signatureLength);
	static string sign(string privateKey, string message, size_t* signatureLength);
	static string sign(EVP_PKEY* privateKey, string message, size_t* signatureLength);
	static bool verifySign(string publicKey, string data, string signature, size_t* signatureLength);
	static bool verifySign(EVP_PKEY* publicKey, string data, string signature, size_t* signatureLength);
	static string getMerkleRoot(vector<Transaction> transactions);
};
