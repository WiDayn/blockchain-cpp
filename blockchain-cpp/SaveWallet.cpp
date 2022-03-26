/*****************************************************************//**
 * \file   SaveWallet.cpp
 * \author WiDAYN
 * \date   26 March 2022
 *********************************************************************/
#include "SaveWallet.h"
#include "StringUtil.h"
#include <fstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include<boost/serialization/map.hpp>

bool SaveWallet::save(Wallet& wallet, ini_t* config)
{
	const char* file = ini_get(config, "file", "wallet");
	//–¥»Î
	ofstream ss(file, ios::binary);
	if (ss.is_open()) {
		boost::archive::binary_oarchive oa(ss);
		oa << wallet;
		ss.close();
		StringUtil::printfSuccess("Saved wallet");
		return true;
	}
	else {
		StringUtil::printfError("¥Úø™ ß∞‹");
		return false;
	}
	return true;
}

bool SaveWallet::load(Wallet& wallet, ini_t* config)
{
	const char* file = ini_get(config, "file", "wallet");
	ifstream is(file, std::ios::binary);
	if (is.is_open()) {
		boost::archive::binary_iarchive ia(is);
		ia >> wallet;
		StringUtil::printfSuccess("Loaded wallet");
	}
	else {
		wallet.generateKeyPair();
		save(wallet, config);
	}
	is.close();
	return true;
}
