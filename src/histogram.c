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

static long max(long *xs, size_t N) {
	long x = LONG_MIN;
	for(size_t n = 0; n < N; n++)
		if(xs[n] > x)
			x = xs[n];
	return x;
}

static void normalize(long *xs, size_t N) {
	long x = max(xs, UCHAR_MAX + 1);
	for(size_t n = 0; n < N; n++) {
		if(xs[n] != 0) {
			xs[n] -= 1;
			xs[n] *= UCHAR_MAX - 1;
			xs[n] /= x - 1;
			xs[n] += 1;
		}
	}
}

int main() {
	long h[UCHAR_MAX + 1] = { 0 };
	int ch;
	while((ch = getchar()) != EOF)
		h[ch]++;
	normalize(h, UCHAR_MAX + 1);
	for(ch = 0; ch <= UCHAR_MAX; ch++)
		putchar(h[ch]);
	exit(EXIT_SUCCESS);
}
