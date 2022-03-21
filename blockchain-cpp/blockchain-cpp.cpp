#include <iostream>
#include "Block.h"
#include "BlockChain.h"
using namespace std;



int main() {
	BlockChain bk = BlockChain();
	while (1) {
		bk.addBlock(); //不断加入新的Block
	}
	return 0;
}