/*****************************************************************//**
 * \file   SaveWallet.h
 * \author WiDAYN
 * \date   26 March 2022
 *********************************************************************/
#pragma once
#include "Wallet.h"
#include "ini.h"

class SaveWallet
{
public:
	static bool save(Wallet& wallet, ini_t* config);
	static bool load(Wallet& wallet, ini_t* config);
};