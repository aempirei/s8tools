#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

static inline long int min(long int a, long int b) {
	return a < b ? a : b;
}

int main() {
	unsigned long int h[UCHAR_MAX + 1] = { 0 };
	int ch;
	while((ch = getchar()) != EOF)
		h[ch]++;
	for(size_t k = 0; k <= UCHAR_MAX; k++) {
		putchar(min((int)rint(8*log2(1+h[ch])), UCHAR_MAX));
		putchar(k);
	}
	exit(EXIT_SUCCESS);
}
