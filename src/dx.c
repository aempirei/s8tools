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
