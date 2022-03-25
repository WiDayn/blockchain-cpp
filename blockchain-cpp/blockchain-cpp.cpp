/*****************************************************************//**
 * \file   blockchain-cpp.cpp
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#define stdin  (__acrt_iob_func(0))
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
#include <thread>
#include <map>
#include "Wallet.h"
#include "Transaction.h"
#include "BlockChain.h"
#include "Block.h"
#include "StringUtil.h"
#include "TransactionOutput.h"
#include "TCP_Server.h"
#include "TCP_Client.h"
#include "TCP_Head.h"
#pragma warning(disable : 4996)
#pragma comment(lib,"ws2_32.lib")
FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }

void runServer() {
	TCP_Server server = TCP_Server();
}

void runClient() {
	TCP_Client con = TCP_Client("127.0.0.1");
	con.createConnection();
	char data[] = "123";
	TCP_Head head = TCP_Head("Ping", sizeof(data));
	char* package = (char*)malloc(sizeof(char) * (sizeof(TCP_Head) + sizeof(data)));
	memcpy(package, &head, sizeof(TCP_Head));
	memcpy(package + sizeof(TCP_Head), data, sizeof(data));

	printf("%lld", strlen(package));
	for (int i = 0; i < strlen(package); i++) {
		printf("%c", package[i]);
	}
	con.sendMessage(package, sizeof(char) * (sizeof(TCP_Head) + sizeof(data)));
}

int main()
{
	thread Server(runServer);
	Server.detach();
	while (1) {
		thread Client1(runClient);
		Client1.detach();
		Sleep(1000000);
	}

	Wallet walletA = Wallet();
	Wallet walletB = Wallet();
	Wallet coinbase = Wallet();
	map<string, TransactionOutput> UTXOs;
	BlockChain blockChain = BlockChain();
	blockChain.genesisTransaction.sender = coinbase.publicKeyChar;
	blockChain.genesisTransaction.reciepient = walletA.publicKeyChar;
	blockChain.genesisTransaction.transactionId = "0";
	blockChain.genesisTransaction.value = 100;
	blockChain.genesisTransaction.generateSignature(coinbase.privateKeyChar);
	blockChain.genesisTransaction.outputs.push_back(TransactionOutput(blockChain.genesisTransaction.reciepient, blockChain.genesisTransaction.value, blockChain.genesisTransaction.transactionId));
	UTXOs.insert(pair<string, TransactionOutput>(blockChain.genesisTransaction.outputs[0].id, blockChain.genesisTransaction.outputs[0]));

	StringUtil::printfInformation("Creating and Mining Genesis block... ");
	Block genesis = Block("0");
	genesis.addTransaction(blockChain.genesisTransaction, UTXOs);
	blockChain.addBlock(genesis);

	Block block1 = Block(genesis.hash);
	StringUtil::printfSuccess("\nWalletA's balance is: " + to_string(walletA.getBalance(UTXOs)));
	StringUtil::printfSuccess("\nWalletA is Attempting to send funds (40) to WalletB...");
	block1.addTransaction(walletA.sendFunds(walletB.publicKeyChar, 40, UTXOs), UTXOs);
	blockChain.addBlock(block1);
	StringUtil::printfSuccess("\nWalletA's balance is: " + to_string(walletA.getBalance(UTXOs)));
	StringUtil::printfSuccess("WalletB's balance is: " + to_string(walletB.getBalance(UTXOs)));
	StringUtil::printfSuccess("WalletB's balance is: " + to_string(coinbase.getBalance(UTXOs)));

	Block block2 = Block(block1.hash);
	StringUtil::printfSuccess("\nWalletA Attempting to send more funds (1000) than it has...");
	block2.addTransaction(walletA.sendFunds(walletB.publicKeyChar, 1000, UTXOs), UTXOs);
	blockChain.addBlock(block2);
	StringUtil::printfSuccess("\nWalletA's balance is: " + to_string(walletA.getBalance(UTXOs)));
	StringUtil::printfSuccess("WalletB's balance is: " + to_string(walletB.getBalance(UTXOs)));

	Block block3 = Block(block2.hash);
	StringUtil::printfSuccess("\nWalletB is Attempting to send funds (20) to WalletA...");
	block3.addTransaction(walletB.sendFunds(walletA.publicKeyChar, 20, UTXOs), UTXOs);
	StringUtil::printfSuccess("\nWalletA's balance is: " + to_string(walletA.getBalance(UTXOs)));
	StringUtil::printfSuccess("WalletB's balance is: " + to_string(walletB.getBalance(UTXOs)));

	blockChain.isChainValid();
}