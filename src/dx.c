#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <s8.h>

static inline int clip(long int x) {
	return x < CHAR_MIN ? CHAR_MIN : x > CHAR_MAX ? CHAR_MAX : x;
}

static inline dx(const char *x, size_t n) {
	return clip((x[n-1] - x[0]) / (n - 1));
}

int main() {
	char x[3];

	if(s8_bank_init(x, 3, stdin)) {

		putchar(dx(x + 1, 2));

		while(s8_bank_shift(x, 3, stdin))
			putchar(dx(x, 3));

		putchar(dx(x, 2));
	}

	exit(EXIT_SUCCESS);
}
