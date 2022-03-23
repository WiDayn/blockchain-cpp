#pragma once
#include<string>
#include "TransactionOutput.h"
using namespace std;

class TransactionInput
{
public:
	string TransactionOutputId;
	TransactionOutput UTXO;
	TransactionInput(string transationOutputId);
};

