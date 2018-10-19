#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {

	int ch;
	int pch = getchar();
	size_t run = 1;

	while((ch = getchar()) != EOF) {
		if(ch != pch) {
			putchar(run);
			putchar(pch);
			pch = ch;
			run = 0;
		}
		run++;
		if(run == UCHAR_MAX) {
			putchar(run);
			putchar(pch);
			run = 0;
		}
	}

	if(pch != EOF) {
		putchar(run);
		putchar(pch);
	}

	exit(EXIT_SUCCESS);
}
