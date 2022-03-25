#include "TCP_Head.h"
#include <vcruntime_string.h>

TCP_Head::TCP_Head(const char* type, long long length)
{
	memcpy(this->type, type, sizeof(type));
	this->length = length;
}
