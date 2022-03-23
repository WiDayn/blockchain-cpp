#include "BlockChain.h"
#include "StringUtil.h"
#include "Block.h"

void BlockChain::addBlock(Block& block) {
	blockChain.push_back(block);
	int siz = blockChain.size();
	StringUtil::printfSuccess("Trying to Mine block " + to_string(siz) + "...\n");
	block.hash = blockChain[siz - 1].mineBlock(difficulty);
}

bool BlockChain::isChainValid() {
	string hashTarget = "";
	map<string, TransactionOutput> tempUTXOs;
	for (int i = 0; i < difficulty; i++) {
		hashTarget.append("0");
	}
	tempUTXOs.insert(pair<string, TransactionOutput>(genesisTransaction.outputs[0].id, genesisTransaction.outputs[0]));

	for (int i = 1; i < blockChain.size(); i++) {
		Block currentBlock = blockChain[i];
		Block previousBlock = blockChain[i-1];
		
		// 当前块的hash不正确
		if (!(currentBlock.hash == currentBlock.calculateHash())) {
			StringUtil::printfError("#Current Hashes not equal");
		}
		// 前一个块hash不正确
		if (!(previousBlock.hash == currentBlock.previousHash)) {
			StringUtil::printfError("#Previous Hashes not equal");
			return false;
		}
		// hash问题未被解决
		if (!(currentBlock.hash.substr(0, difficulty - 1) != hashTarget)) {
			StringUtil::printfError("#This block hasn't been mined");
			return false;
		}

		TransactionOutput tempOutput;
		for (int t = 0; t < currentBlock.transactions.size(); t++) {
			Transaction currentTransaction = currentBlock.transactions[t];
			
			// 签名错误
			if (!currentTransaction.verifiySignature()) {
				StringUtil::printfError("#Signature on Transaction(" + to_string(t) + ") is Invalid");
				return false;
			}
			// 账单输入输出不匹配
			if (currentTransaction.getInputsValue() != currentTransaction.getOutputsValue()) {
				StringUtil::printfError("#Inputs are note equal to outputs on Transaction(" + to_string(t) + ")");
				return false;
			}

			for (TransactionInput i : currentTransaction.inputs) {
				tempOutput = tempUTXOs[i.TransactionOutputId];

				if (!sizeof(tempOutput.reciepient)) {
					StringUtil::printfError("#Referenced input on Transaction(" + to_string(t) + ") is Missing");
					return false;
				}

				if (i.UTXO.value != tempOutput.value) {
					StringUtil::printfError("#Referenced input Transaction(" + to_string(t) + ") value is Invalid");
					return false;
				}

				tempUTXOs.erase(i.TransactionOutputId);
			}

			for (TransactionOutput o : currentTransaction.outputs) {
				tempUTXOs.insert(pair<string, TransactionOutput>(o.id, o));
			}

			if (currentTransaction.outputs[0].reciepient != currentTransaction.reciepient) {
				StringUtil::printfError("#Transaction(" + to_string(t) + ") output reciepient is not who it should be");
				return false;
			}
			if (currentTransaction.outputs[1].reciepient != currentTransaction.sender) {
				StringUtil::printfError("#Transaction(" + to_string(t) + ") output 'change' is not sender.");
				return false;
			}
		}
	}
	StringUtil::printfSuccess("Blockchain is valid");
	return true;
}