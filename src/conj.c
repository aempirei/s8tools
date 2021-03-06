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
#include <s8-inline-helpers.h>

static inline int f(char x) {
	return (int)rint(sqrt(16384 - (int)x * x));
}

static inline int g(int y, int dy) {
	return (sign(dy) >= 0 ? 1 : -1) * f(y);
}

int main(int argc, char **argv) {
	char x[3];
	char mode = (argc == 2) ? argv[1][0] : '+';
	int z = mode == '+' ? 1 : mode == '-' ? -1 : 0;

	if(s8_bank_init(x, 3, stdin)) {

		putchar(clip(g(x[1], z * dx(x+1,2))));

		while(s8_bank_shift(x, 3, stdin))
			putchar(clip(g(x[1], z * dx(x,3))));

		putchar(clip(g(x[1], z * dx(x,2))));
	}

	exit(EXIT_SUCCESS);
}
