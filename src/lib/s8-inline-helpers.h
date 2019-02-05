#ifndef _S8_INLINE_HELPERS_H
#define _S8_INLINE_HELPERS_H 1

#include <limits.h>

static inline int clip(int x) {
	        return x < CHAR_MIN ? CHAR_MIN : x > CHAR_MAX ? CHAR_MAX : x;
}
 
static inline int dx(const char *x, size_t n) {
	        return clip(((int)x[n-1] - x[0]) / (int)(n - 1));
}

static inline int sign(int x) {
	        return x > 0 ? 1 : x < 0 ? -1 : 0;
}
 
#endif
