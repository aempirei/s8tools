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
	long h[UCHAR_MAX + 1] = { 0 };
	int ch;
	while((ch = getchar()) != EOF)
		h[ch]++;
	for(ch = 0; ch <= UCHAR_MAX; ch++)
		putchar(min((int)rint(ch*log2(1+h[ch])), UCHAR_MAX));
	exit(EXIT_SUCCESS);
}
