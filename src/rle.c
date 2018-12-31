#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

size_t runout(size_t run, int ch) {
	if(run == 0) {
		/* nop */
	} else if(run <= UCHAR_MAX) {
		putchar(run);
		putchar(ch);
	} else {
		putchar(UCHAR_MAX);
		putchar(ch);
		runout(run - UCHAR_MAX, ch);
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
