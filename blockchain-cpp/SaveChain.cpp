#include "SaveChain.h"
#include "StringUtil.h"
#include < fstream >
#include <boost/archive/binary_iarchive.hpp> //二进制序列化
#include <boost/archive/binary_oarchive.hpp> //二进制序列化
#include <boost/serialization/vector.hpp> //序列化STL容器要导入
#include<boost/serialization/map.hpp> //序列化STL容器要导入

bool SaveChain::save(BlockChain& blockChain, ini_t* config)
{
	const char* file = ini_get(config, "file", "blockchain");
	//写入
	ofstream ss(file, ios::binary);
	if (ss.is_open()) {
		boost::archive::binary_oarchive oa(ss);
		oa << blockChain;
		ss.close();
		return true;
	}
	else {
		StringUtil::printfError("打开失败");
		return false;
	}
	return true;
}

bool SaveChain::load(BlockChain& blockChain, ini_t* config) {
	const char* file = ini_get(config, "file", "blockchain");
	ifstream is(file, std::ios::binary);
	if (is.is_open()) {
		boost::archive::binary_iarchive ia(is);
		ia >> blockChain;
	}
	is.close();
	return true;
}
