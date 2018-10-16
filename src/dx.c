#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <s8.h>

static inline int clip(int x) {
	return x > CHAR_MAX ? CHAR_MAX : x < CHAR_MIN ? CHAR_MIN : x;
}

int main() {
	char x[2];
	if(s8_bank_init(x, sizeof(x), stdin))
		while(s8_bank_shift(x, sizeof(x), stdin))
			putchar(clip(x[1] - x[0]));
	exit(EXIT_SUCCESS);
}
