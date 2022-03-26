#include "SaveChain.h"
#include "StringUtil.h"
#include < fstream >
#include <boost/archive/binary_iarchive.hpp> //���������л�
#include <boost/archive/binary_oarchive.hpp> //���������л�
#include <boost/serialization/vector.hpp> //���л�STL����Ҫ����
#include<boost/serialization/map.hpp> //���л�STL����Ҫ����

bool SaveChain::save(BlockChain& blockChain, ini_t* config)
{
	const char* file = ini_get(config, "file", "blockchain");
	//д��
	ofstream ss(file, ios::binary);
	if (ss.is_open()) {
		boost::archive::binary_oarchive oa(ss);
		oa << blockChain;
		ss.close();
		return true;
	}
	else {
		StringUtil::printfError("��ʧ��");
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
