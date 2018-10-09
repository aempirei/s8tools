#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef int filter_t[3];

int is_maxima(const filter_t zs) { return zs[1] > zs[0] && zs[1] > zs[2]; }
int is_minima(const filter_t zs) { return zs[1] < zs[0] && zs[1] < zs[2]; }
int is_extrema(const filter_t zs) { return is_maxima(zs) || is_minima(zs); }

int value_of(const filter_t zs) {
	return zs[1];
}

int slide_distinct(filter_t zs, int x) {
	int y = zs[0];
	if(x != zs[2]) {
		zs[0] = zs[1];
		zs[1] = zs[2];
		zs[2] = x;
	}
	return y;
}

int main() {
	int ch;
	filter_t zs = { 0 };
	while((ch = getchar()) != EOF) {
		slide_distinct(zs, (char)ch);
		putchar(is_extrema(zs) ? value_of(zs) : 0);
	}
	return 0;
}
