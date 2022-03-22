#include "StringUtil.h"
#include <iostream>
#include <openssl/bio.h>
#include <openssl/pem.h>

string StringUtil::sha256(const string str)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		ss << hex << setw(2) << setfill('0') << (int)hash[i];
	}
	return ss.str();
}

string StringUtil::longToString(long int t)
{
	std::string result;
	stringstream ss;
	ss << t;
	ss >> result;
	return result;
}

string StringUtil::publicKeyToString(EVP_PKEY* key)
{
	BIO* publicBIO = BIO_new(BIO_s_mem());
	PEM_write_bio_PUBKEY(publicBIO, key);

	int publicKeyLen = BIO_pending(publicBIO);
	unsigned char* publicKeyChar = (unsigned char*)malloc(publicKeyLen);
	BIO_read(publicBIO, publicKeyChar, publicKeyLen);
	string strKey;
	strKey.append(reinterpret_cast<const char*>(publicKeyChar));
	return strKey;
}

string StringUtil::privateKeyToString(EVP_PKEY* key)
{
	BIO* privateBIO = BIO_new(BIO_s_mem());
	PEM_write_bio_PrivateKey(privateBIO, key, NULL, NULL, 0, 0, NULL);
	int privateKeyLen = BIO_pending(privateBIO);
	unsigned char* privateKeyChar = (unsigned char*)malloc(privateKeyLen);
	BIO_read(privateBIO, privateKeyChar, privateKeyLen);
	string strKey;
	strKey.append(reinterpret_cast<const char*>(privateKeyChar));
	return strKey;
}

void StringUtil::printfGreen(string s)
{
	cout << "\033[0m\033[1;32m" << s << "\033[0m";
}

void StringUtil::printfRed(string s)
{
	cout << "\033[0m\033[1;31m" << s << "\033[0m";
}