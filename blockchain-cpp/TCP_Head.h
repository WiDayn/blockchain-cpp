/*****************************************************************//**
 * \file   TCP_Head.h
 * \author WiDAYN
 * \date   24 March 2022
 *********************************************************************/
#pragma once

class TCP_Head {
public:
	char type[8];
	long long length;

	TCP_Head() {};

	TCP_Head(const char* type, long long length);
};
