#pragma once
#include <iomanip>
#include <sstream>
#include <string>
#include <openssl/sha.h>
#pragma warning(disable : 4996)
using namespace std;

class StringUtil {
public:
	static string sha256(const string str);
	static string longToString(long int t);
	static void printfGreen(string s);
	static void printfRed(string s);
};

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

void StringUtil::printfGreen(string s)
{
	cout << "\033[0m\033[1;32m" << s << "\033[0m";
}

void StringUtil::printfRed(string s)
{
	cout << "\033[0m\033[1;31m" << s << "\033[0m";
}