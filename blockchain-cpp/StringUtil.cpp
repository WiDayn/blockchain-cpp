#include "StringUtil.h"
#include <iostream>
#include <vector>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include "Wallet.h"
using namespace std;

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

unsigned char* StringUtil::publicKeyToUnsignedChar(EVP_PKEY* key)
{
	BIO* publicBIO = BIO_new(BIO_s_mem());
	PEM_write_bio_PUBKEY(publicBIO, key);

	int publicKeyLen = BIO_pending(publicBIO);
	unsigned char* publicKeyChar = (unsigned char*)malloc(publicKeyLen);
	BIO_read(publicBIO, publicKeyChar, publicKeyLen);
	publicKeyChar[publicKeyLen] = '\0';
	return publicKeyChar;
}

unsigned char* StringUtil::privateKeyToUnsignedChar(EVP_PKEY* key)
{
	BIO* privateBIO = BIO_new(BIO_s_mem());
	PEM_write_bio_PrivateKey(privateBIO, key, NULL, NULL, 0, 0, NULL);
	int privateKeyLen = BIO_pending(privateBIO);
	unsigned char* privateKeyChar = (unsigned char*)malloc(privateKeyLen);
	BIO_read(privateBIO, privateKeyChar, privateKeyLen);
	privateKeyChar[privateKeyLen] = '\0';
	return privateKeyChar;
}

string StringUtil::unsignedCharToString(unsigned char* input)
{
	string str;
	str.append(reinterpret_cast<const char*>(input));
	return str;
}

unsigned char* StringUtil::sign(EVP_PKEY* key, string message) {
	unsigned char* signature = NULL;
	size_t signatureLength;
	if (sign(key, message.c_str(), strlen(message.c_str()), &signature, &signatureLength)) {
		return signature;
	}
}

bool StringUtil::sign(EVP_PKEY* key, const char* message, size_t messageLength, unsigned char** signature, size_t* signatureLength)
{
	EVP_MD_CTX* signCTX = NULL;

	if (!(signCTX = EVP_MD_CTX_create())) {
		return false;
	}

	if (EVP_DigestSignInit(signCTX, NULL, EVP_sha256(), NULL, key) <= 0) {
		return false;
	}

	if (EVP_DigestSignUpdate(signCTX, message, messageLength) <= 0) {
		return false;
	}

	if (EVP_DigestSignFinal(signCTX, NULL, signatureLength) <= 0) {
		return false;
	}

	if (!(*signature = (unsigned char*)OPENSSL_malloc(sizeof(unsigned char) * (*signatureLength)))) {
		return 0;
	}

	if (EVP_DigestSignFinal(signCTX, *signature, signatureLength) <= 0) {
		return false;
	}

	EVP_MD_CTX_free(signCTX);

	return true;
}


unsigned char* StringUtil::sign(unsigned char* privateKey, string message) {
	BIO* bio;
	if ((bio = BIO_new_mem_buf(privateKey, -1)) == NULL) {
		StringUtil::printfRed("BIO_new_mem_buf failed!");
	};

	EVP_PKEY* key = PEM_read_bio_PrivateKey(bio, NULL, NULL, NULL);
	unsigned char* publicKeyChar = StringUtil::publicKeyToUnsignedChar(key);
	if (key == NULL) {
		StringUtil::printfRed("PEM_read_bio_PUBKEY failed!");
	}
	BIO_flush(bio);
	return sign(key, message);
}

bool StringUtil::verifySign(EVP_PKEY* publicKey, string data, unsigned char* signature) {
	EVP_MD_CTX* mdctx = NULL;
	int ret = 0;
	size_t valtmplen = EVP_PKEY_size(publicKey);

	/* Create the Message Digest Context */
	if (!(mdctx = EVP_MD_CTX_create())) {
		return false;
	}

	if (1 != EVP_DigestVerifyInit(mdctx, NULL, EVP_sha256(), NULL, publicKey)) {
		return false;
	}

	if (1 != EVP_DigestVerifyUpdate(mdctx, data.c_str(), strlen(data.c_str()))) {
		return false;
	}

	if (1 == EVP_DigestVerifyFinal(mdctx, signature, valtmplen))
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool StringUtil::verifySign(unsigned char* publicKey, string data, unsigned char* signature)
{
	BIO* bio;
	if ((bio = BIO_new_mem_buf(publicKey, -1)) == NULL) {
		StringUtil::printfRed("BIO_new_mem_buf failed!");
	};

	EVP_PKEY* key = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
	unsigned char* publicKeyChar = StringUtil::publicKeyToUnsignedChar(key);
	if (key == NULL) {
		StringUtil::printfRed("PEM_read_bio_PUBKEY failed!");
	}
	BIO_flush(bio);
	return verifySign(key, data, signature);
}

void StringUtil::printfGreen(string s)
{
	cout << "\033[0m\033[1;32m" << s << "\033[0m" << endl;
}

void StringUtil::printfRed(string s)
{
	cout << "\033[0m\033[1;31m" << s << "\033[0m" << endl;
}