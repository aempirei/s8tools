#ifndef _S8_HELPERS_H
#define _S8_HELPERS_H 1

#include <stdbool.h>

unsigned char to_ullcomp(long);
unsigned char to_sllcomp(long);
signed char to_sclip(long);
unsigned char to_uclip(long);

long from_ullcomp(unsigned char);
long from_sllcomp(unsigned char);
long from_sclip(signed char);
long from_uclip(unsigned char);

#endif
