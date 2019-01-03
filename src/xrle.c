#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <s8-helpers.h>

size_t runout(unsigned long run, int ch) {

	if(run == 0)
		return 0;

	unsigned char ll8 = to_ll8(run);
	unsigned long done = from_ll8(ll8);

	putchar(ll8);
	putchar(ch);

	assert(done <= run);

	return done + runout(run - done, ch);
}

int main() {

	int ch;
	int pch = getchar();
	unsigned long run = 1;

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
