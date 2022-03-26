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
	template<class TransactionInput>
	void serialize(TransactionInput& ar, const unsigned int version)
	{
		ar& TransactionOutputId;
		ar& UTXO;
	}

	string TransactionOutputId;
	TransactionOutput UTXO;

	TransactionInput() {};

	TransactionInput(string transationOutputId);
};