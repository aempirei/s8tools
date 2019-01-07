#ifndef _S8_HELPERS_H
#define _S8_HELPERS_H 1

#include <stdbool.h>

#define DECL_FROM(X,...)	unsigned long from_##X(unsigned char __VA_ARGS__)
#define DECL_TO(X,...)		unsigned char to_##X(unsigned long __VA_ARGS__)

#define DECL_PAIR(X) DECL_TO(X);DECL_FROM(X)

DECL_PAIR(ll8);
DECL_PAIR(5b2);
DECL_PAIR(nop);

#endif
