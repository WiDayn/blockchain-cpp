﻿#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))
#include <stdio.h>
#include <stdlib.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/bn.h>
#include <openssl/evp.h>
#include <openssl/dsa.h>
#include <memory>
#include <map>
#include "Wallet.h"
#include "Transaction.h"
#include "BlockChain.h"
#include "Block.h"
#include "StringUtil.h"
#include "TransactionOutput.h"
#pragma warning(disable : 4996)
#pragma comment(lib,"ws2_32.lib")
FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }

int main()
{
	Wallet walletA = Wallet();
	Wallet walletB = Wallet();
	Wallet coinbase = Wallet();
	map<string, TransactionOutput> UTXOs;
	BlockChain blockChain = BlockChain();

	Transaction genesisTransaction;
	genesisTransaction.sender = coinbase.publicKeyChar;
	genesisTransaction.reciepient = walletA.publicKeyChar;
	genesisTransaction.transactionId = "0";
	genesisTransaction.value = 100;
	genesisTransaction.generateSignature(coinbase.privateKeyChar);
	genesisTransaction.outputs.push_back(TransactionOutput(genesisTransaction.reciepient, genesisTransaction.value, genesisTransaction.transactionId));
	UTXOs.insert(pair<string, TransactionOutput>(genesisTransaction.outputs[0].id, genesisTransaction.outputs[0]));

	StringUtil::printfInformation("Creating and Mining Genesis block... ");
	Block genesis = Block("0");
	genesis.addTransaction(genesisTransaction, UTXOs);
	blockChain.addBlock(genesis);

	StringUtil::printfInformation("walletA Balance: " + to_string(walletA.getBalance(UTXOs)));
}