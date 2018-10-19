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

int main() {
	char x[3];
	if(s8_bank_init(x, 3, stdin)) {
		putchar(x[1]);
		while(s8_bank_shift(x, 3, stdin)) {
			if(x[1] == 0)
				x[1] = ((int)x[0] + x[2]) / 2;
			putchar(x[1]);
		}
		putchar(x[1]);
	}
	exit(EXIT_SUCCESS);
}
