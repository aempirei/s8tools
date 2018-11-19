#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <s8.h>

static inline int ifarg(size_t n, size_t argc, char **argv, int retval, int min, int max) {
	if(argc > n)
		retval = strtol(argv[n], NULL, 0);
	return retval < min ? min : retval > max ? max : retval;
}

int main(int argc, char **argv) {
	size_t cons = ifarg(1, argc, argv, 1, 1, 65535);
	size_t shift = ifarg(2, argc, argv, 1, 1, 65535);
	size_t n = 0;
	char x[cons];
	if(s8_bank_init(x, cons, stdin)) {
		while(s8_bank_shift(x, cons, stdin)) {
			if(n++ == 0)
				for(size_t k = 0; k < cons; k++)
					putchar(x[k]);
			n %= shift;
		}
	}
	exit(EXIT_SUCCESS);
}
