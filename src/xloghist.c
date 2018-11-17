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
static inline long int max(long int a, long int b) {
	return a > b ? a : b;
}
static inline long int between(long int a, long int x, long int b) {
	return min(max(a,x),b);
}

static inline double logi2(double x) {
	return log2(x+1)-1;
}

int main() {
	long h[UCHAR_MAX + 1] = { 0 };
	int ch;
	while((ch = getchar()) != EOF)
		h[ch]++;
	for(ch = 0; ch <= UCHAR_MAX; ch++)
		putchar(between(0, rint(ch * logi2(h[ch])), UCHAR_MAX));
	exit(EXIT_SUCCESS);
}
