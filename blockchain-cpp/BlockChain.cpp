#include "BlockChain.h"
#include "StringUtil.h"
#include "Block.h"

void BlockChain::addBlock(Block block) {
	blockChain.push_back(block);
	int siz = blockChain.size();
	StringUtil::printfSuccess("Trying to Mine block " + to_string(siz) + "...\n");
	blockChain[siz - 1].mineBlock(difficulty);
}

bool BlockChain::isChainValid() {
	for (int i = 1; i < blockChain.size(); i++) {
		Block currentBlock = blockChain[i];
		Block previousBlock = blockChain[static_cast<std::vector<Block, std::allocator<Block>>::size_type>(i) - 1];
		// 检验自己的hash是否正确
		if (currentBlock.hash != currentBlock.calculateHash()) {
			StringUtil::printfError("Current Hashes not equal");
			return false;
		}
		// 检验与前一个块的hash是否正确
		if (previousBlock.hash != currentBlock.previousHash) {
			StringUtil::printfError("Previous Hashes not equal");
			return false;
		}
		return true;
	}
}