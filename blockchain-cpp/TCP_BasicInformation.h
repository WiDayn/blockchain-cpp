/*****************************************************************//**
 * \file   TCP_BasicInformation.h
 * \author WiDAYN
 * \date   25 March 2022
 *********************************************************************/
#pragma once
class TCP_BasicInformation
{
public:
	char sendAddress[20];
	int blockHeight;

	TCP_BasicInformation() {};

	TCP_BasicInformation(char* sendAddress);
};

