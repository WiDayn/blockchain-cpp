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
	static string publicKeyToString(EVP_PKEY* key);
	static string privateKeyToString(EVP_PKEY* key);
	static void printfGreen(string s);
	static void printfRed(string s);
};
