#include <limits.h>
#include <stdint.h>
#include <s8-helpers.h>

#define HALF_MAX_BIT    (sizeof(uint32_t) * 4)

static int highest_bit(uint32_t n) {
        int bit = -1;
        for(int k = HALF_MAX_BIT; k > 0; k>>=1) {
                if(n >> k) {
                        bit += k;
                        n >>= k;
                }
        }
        return bit + n;
}

unsigned char to_ullcomp(long x) {
	const int hibits = 3;
	const int lobits = 5;
	const int himask = ((1 << hibits) - 1) << lobits;
	const int lomask = ((1 << lobits) - 1);
	const int linear_max = himask - 1;
	if(x <= 0)
		return 0;
	if(x <= linear_max)
		return x;
	return himask | (highest_bit(x - linear_max) & lomask);
}
unsigned char to_sllcomp(long x) {
	const int hibits = 2;
	const int lobits = 5;
	const int himask = ((1 << hibits) - 1) << lobits;
	const int lomask = ((1 << lobits) - 1);
	const int signbit = (1 << 7);
	const int linear_max = himask - 1;
	unsigned char y;
	if(x == 0)
		return 0;
	if(x < 0) {
		x = -x;
		y = signbit;
	} else {
		y = 0;
	}
	if(x <= linear_max)
		return y | linear_max;
	return y | himask | (highest_bit(x - linear_max) & lomask);
}
signed char to_sclip(long x) {
	return (x < SCHAR_MIN) ? SCHAR_MIN : (x > SCHAR_MAX) ? SCHAR_MAX : x;
}
unsigned char to_uclip(long x) {
	return (x < 0) ? 0 : (x > UCHAR_MAX) ? UCHAR_MAX : x;
}

long from_ullcomp(unsigned char x) {
	const int hibits = 3;
	const int lobits = 5;
	const int himask = ((1 << hibits) - 1) << lobits;
	const int lomask = ((1 << lobits) - 1);
	const int linear_max = himask - 1;
	return ((x & himask) == himask) ? (linear_max + (1 << (x & lomask))) : x;
}
long from_sllcomp(unsigned char x) {
	const int hibits = 2;
	const int lobits = 5;
	const int himask = ((1 << hibits) - 1) << lobits;
	const int lomask = ((1 << lobits) - 1);
	const int signbit = (1 << 7);
	const int linear_max = himask - 1;
	int sign = (x & signbit) ? -1 : 1;
	x &= ~signbit;
	return sign * (((x & himask) == himask) ? (linear_max + (1 << (x & lomask))) : x);
}
long from_sclip(signed char x) {
	return x;
}
long from_uclip(unsigned char x) {
	return x;
}
