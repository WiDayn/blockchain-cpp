/*****************************************************************//**
 * \file   StringUtil.cpp
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#include "StringUtil.h"
#include <iostream>
#include <vector>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include "Wallet.h"
#include <wtypes.h>
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

string StringUtil::WcharToString(wchar_t* wchar)
{
	string szDst;
	wchar_t* wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte的运用
	char* psText; // psText为char*的临时数组，作为赋值给std::string的中间变量
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte的再次运用
	szDst = psText;// std::string赋值
	delete[]psText;// psText的清除
	return szDst;
}

unsigned char* StringUtil::publicKeyToUnsignedChar(EVP_PKEY* key)
{
	BIO* publicBIO = BIO_new(BIO_s_mem());
	PEM_write_bio_PUBKEY(publicBIO, key);

	int publicKeyLen = BIO_pending(publicBIO);
	unsigned char* publicKeyChar = (unsigned char*)malloc(publicKeyLen + 1);
	BIO_read(publicBIO, publicKeyChar, publicKeyLen);
	publicKeyChar[publicKeyLen] = '\0';
	return publicKeyChar;
}

string StringUtil::publicKeyToString(EVP_PKEY* key)
{
	BIO* publicBIO = BIO_new(BIO_s_mem());
	PEM_write_bio_PUBKEY(publicBIO, key);

	int publicKeyLen = BIO_pending(publicBIO);
	unsigned char* publicKeyChar = (unsigned char*)malloc(publicKeyLen + 1);
	BIO_read(publicBIO, publicKeyChar, publicKeyLen);
	publicKeyChar[publicKeyLen] = '\0';
	return StringUtil::unsignedCharToString(publicKeyChar);
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

string StringUtil::privateKeyToString(EVP_PKEY* key)
{
	BIO* privateBIO = BIO_new(BIO_s_mem());
	PEM_write_bio_PrivateKey(privateBIO, key, NULL, NULL, 0, 0, NULL);
	int privateKeyLen = BIO_pending(privateBIO);
	unsigned char* privateKeyChar = (unsigned char*)malloc(privateKeyLen);
	BIO_read(privateBIO, privateKeyChar, privateKeyLen);
	privateKeyChar[privateKeyLen] = '\0';
	return StringUtil::unsignedCharToString(privateKeyChar);
}

string StringUtil::unsignedCharToString(unsigned char* input)
{
	string str;
	str.append(reinterpret_cast<const char*>(input));
	return str;
}

string StringUtil::sign(EVP_PKEY* key, string message, size_t* signatureLength) {
	string signature;
	if (sign(key, message, message.length(), signature, signatureLength)) {
		return signature;
	}
}

size_t StringUtil::sign(EVP_PKEY* key, string message, size_t messageLength, string& signature, size_t* signatureLength)
{
	EVP_MD_CTX* signCTX = NULL;

	if (!(signCTX = EVP_MD_CTX_create())) {
		return false;
	}

	if (EVP_DigestSignInit(signCTX, NULL, EVP_sha256(), NULL, key) != 1) {
		return false;
	}

	if (EVP_DigestSignUpdate(signCTX, message.c_str(), messageLength) != 1) {
		return false;
	}

	if (EVP_DigestSignFinal(signCTX, NULL, signatureLength) != 1) {
		return false;
	}
	unsigned char* bufSignature = NULL;
	if (!(bufSignature = (unsigned char*)OPENSSL_malloc(sizeof(unsigned char) * (*signatureLength + 1)))) {
		return 0;
	}

	if (EVP_DigestSignFinal(signCTX, bufSignature, signatureLength) != 1) {
		return false;
	}

	EVP_MD_CTX_free(signCTX);

	//强制转换
	for (int i = 0; i < *signatureLength; i++) {
		signature += ((char)bufSignature[i]);
	}
	return *signatureLength;
}


string StringUtil::sign(string privateKey, string message, size_t* signatureLength) {
	BIO* bio;
	if ((bio = BIO_new_mem_buf((unsigned char*)privateKey.c_str(), -1)) == NULL) {
		StringUtil::printfError("BIO_new_mem_buf failed!");
	};
	EVP_PKEY* key = PEM_read_bio_PrivateKey(bio, NULL, NULL, NULL);
	string publicKeyChar = StringUtil::publicKeyToString(key);
	if (key == NULL) {
		StringUtil::printfError("PEM_read_bio_PUBKEY failed!");
	}
	BIO_flush(bio);
	return sign(key, message, signatureLength);
}

bool StringUtil::verifySign(EVP_PKEY* publicKey, string data, string signature, size_t* signatureLength) {
	EVP_MD_CTX* mdctx = NULL;
	int ret = 0;

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

	if (1 == EVP_DigestVerifyFinal(mdctx, (unsigned char*)signature.c_str(), *signatureLength))
	{
		return true;
	}
	else
	{
		return false;
	}

}

string StringUtil::getMerkleRoot(vector<Transaction> transactions)
{
	int n = transactions.size();
	vector<string> previousTreeLayer;
	for (Transaction t : transactions) {
		previousTreeLayer.push_back(t.transactionId);
	}
	vector<string> treeLayer = previousTreeLayer;
	while (n > 1) {
		// 合并交易的sha，汇总为一个
		treeLayer = vector<string>();
		for (int i = 1; i < previousTreeLayer.size(); i++) {
			treeLayer.push_back(StringUtil::sha256(previousTreeLayer[i - 1] + previousTreeLayer[i]));
		}
		n = treeLayer.size();
		previousTreeLayer = treeLayer;
	}
	string merkleRoot = (treeLayer.size() == 1) ? treeLayer[0] : "";
	return merkleRoot;
}

bool StringUtil::verifySign(string publicKey, string data, string signature, size_t* signatureLength)
{
	BIO* bio;
	if ((bio = BIO_new_mem_buf(publicKey.c_str(), -1)) == NULL) {
		StringUtil::printfError("BIO_new_mem_buf failed!");
	};

	EVP_PKEY* key = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
	;	if (key == NULL) {
		StringUtil::printfError("PEM_read_bio_PUBKEY failed!");
	}
	BIO_flush(bio);
	return verifySign(key, data, signature, signatureLength);
}

void StringUtil::printfSuccess(string s)
{
	cout << "\033[0m\033[1;32m" << s << "\033[0m" << endl;
}

void StringUtil::printfError(string s)
{
	cout << "\033[0m\033[1;31m" << s << "\033[0m" << endl;
}

void StringUtil::printfInformation(string s)
{
	cout << "\033[0;34m" << s << "\033[0m" << endl;
}