#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <s8.h>

int clip(int x) {
	return x > INT8_MAX ? INT8_MAX : x < INT8_MIN ? INT8_MIN : x;
}

int main() {
	char x[2];
	if(s8_bank_init(x, sizeof(x), stdin))
		while(s8_bank_shift(x, sizeof(x), stdin))
			putchar(clip(x[1] - x[0]));
	return 0;
}
