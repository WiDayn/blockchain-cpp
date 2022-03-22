#pragma once
#include <iomanip>
#include <sstream>
#include <string>
#include <openssl/sha.h>
#include <openssl/ossl_typ.h>
using namespace std;

class StringUtil {
public:
	static string sha256(const string str);
	static string longToString(long int t);
	static string unsignedCharToString(unsigned char* input);
	static unsigned char* publicKeyToUnsignedChar(EVP_PKEY* key);
	static unsigned char* privateKeyToUnsignedChar(EVP_PKEY* key);
	static void printfGreen(string s);
	static void printfRed(string s);
	static bool sign(EVP_PKEY* key, const char* message, size_t messageLength, unsigned char** signature, size_t* signatureLength);
	static unsigned char* sign(unsigned char* privateKey, string message);
	static unsigned char* sign(EVP_PKEY* privateKey, string message);
	static bool verifySign(unsigned char* publicKey, string data, unsigned char* signature);
	static bool verifySign(EVP_PKEY* publicKey, string data, unsigned char* signature);
};
