/*****************************************************************//**
 * \file   TCP_BasicInformation.cpp
 * \author WiDAYN
 * \date   25 March 2022
 *********************************************************************/
#include "TCP_BasicInformation.h"
#include <string.h>

TCP_BasicInformation::TCP_BasicInformation(char* sendAddress) {
	for (int i = 0; i < strlen(sendAddress); i++) {
		this->sendAddress[i] = sendAddress[i];
	}
	this->sendAddress[strlen(sendAddress)] = '\0';
}
