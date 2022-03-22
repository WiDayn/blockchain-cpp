#include "BlockChain.h"

void BlockChain::addBlock() {
	int siz = blockChain.size();
	if (siz) {
		blockChain.push_back(Block("Hi im the " + to_string(blockChain.size()) + "block", blockChain[siz - 1].hash));
	}
	else {
		blockChain.push_back(Block("Hi im the " + to_string(blockChain.size()) + "block", "0"));
	}
	StringUtil::printfGreen("Trying to Mine block " + to_string(siz) + "...\n");
	blockChain[siz].mineBlock(difficulty);
}

bool BlockChain::isChainValid() {
	for (int i = 1; i < blockChain.size(); i++) {
		Block currentBlock = blockChain[i];
		Block previousBlock = blockChain[i - 1];
		// 检验自己的hash是否正确
		if (currentBlock.hash != currentBlock.calculateHash()) {
			StringUtil::printfRed("Current Hashes not equal");
			return false;
		}
		// 检验与前一个块的hash是否正确
		if (previousBlock.hash != currentBlock.previousHash) {
			StringUtil::printfRed("Previous Hashes not equal");
			return false;
		}
		return true;
	}
}