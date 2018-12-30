#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MSB 3
#define LSB (8 - (MSB))
#define LSB_MASK ((1 << (LSB)) - 1)

const unsigned char msb = MSB;
const unsigned char lsb = LSB;

const unsigned char lsb_mask = LSB_MASK;
const unsigned char msb_mask = (~0) ^ LSB_MASK;

size_t runout(size_t run, int ch) {
	if(run == 0) {
		/* nop */
	} else if(run < msb_mask) {
		putchar(run);
		putchar(ch);
	} else {
		size_t expart = run - (msb_mask - 1);
		int ex = -1;
		while(expart) {
			expart >>= 1;
			ex++;
		}
		if(ex > lsb_mask)
			ex = lsb_mask;
		size_t rundone = (msb_mask - 1) + (1 << ex);
		putchar(msb_mask | ex);
		putchar(ch);
		runout(run - rundone, ch);
	}
	return run;
}

int main() {

	int ch;
	int pch = getchar();
	size_t run = 1;

	while((ch = getchar()) != EOF) {
		if(ch != pch) {
			runout(run, pch);
			pch = ch;
			run = 0;
		}
		run++;
	}

	if(pch != EOF)
		runout(run, pch);

	exit(EXIT_SUCCESS);
}
