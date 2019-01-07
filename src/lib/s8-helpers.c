#include <s8-helpers.h>

#define POW2(N)		(1<<(N))
#define BITMASK(N)	(POW2(N)-1)
#define MSB		(3)
#define LSB		(8-(MSB))
#define LSB_MASK	BITMASK(LSB)
#define MSB_MASK	(BITMASK(MSB)<<LSB)
#define LINEAR_MAX	(MSB_MASK-1)
#define IS_LINEAR(X)	((X) <= LINEAR_MAX)
#define EXPONENT(X)	((X) & LSB_MASK)
#define EXP_PART(X)	POW2(EXPONENT(X))

#define HALF_MAX_BIT    (sizeof(unsigned long) * 4)

static int highest_bit(unsigned long n) {
        int bit = -1;
        for(int k = HALF_MAX_BIT; k > 0; k>>=1) {
                if(n >> k) {
                        bit += k;
                        n >>= k;
                }
        }
        return bit + n;
}

DECL_FROM(ll8,x) {
	return IS_LINEAR(x) ? x : (LINEAR_MAX + EXP_PART(x));
}

DECL_TO(ll8,y) {
	return IS_LINEAR(y) ? y : (MSB_MASK | (highest_bit(y - LINEAR_MAX) & LSB_MASK));
}

DECL_FROM(5b2,x) {
	return x;
}

DECL_TO(5b2,y) {
	return y;
}
