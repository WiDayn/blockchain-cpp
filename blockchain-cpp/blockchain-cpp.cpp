﻿// gcc -Wall ecdsapubkey.c -o ecdsapubkey -lcrypto
#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))
#include <stdio.h>
#include <stdlib.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/bn.h>
#include <openssl/evp.h>
#include <openssl/dsa.h>
#include <memory>
#include "Wallet.h"
#pragma warning(disable : 4996)
#pragma comment(lib,"ws2_32.lib")
FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }

int main()
{
    Wallet mywallet = Wallet();
}