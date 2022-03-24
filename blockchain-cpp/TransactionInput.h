/*****************************************************************//**
 * \file   TransactionInput.h
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
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

