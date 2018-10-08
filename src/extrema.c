#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
 typedef int filter_t[3];

int is_maxima(const filter_t filter) { return filter[1] > filter[0] && filter[1] > filter[2]; }
int is_minima(const filter_t filter) { return filter[1] < filter[0] && filter[1] < filter[2]; }
int is_extrema(const filter_t filter) { return is_maxima(filter) || is_minima(filter); }

int value_of(const filter_t filter) {	
	return filter[1];
}

int slide_distinct(int filter[3], int x) {
	int y = filter[0];
	if(x != filter[2]) {
		filter[0] = filter[1];
		filter[1] = filter[2];
		filter[2] = x;
	}
	return y;
}

int main() {
	int ch;
	int filter[3] = { 0 };
	while((ch = getchar()) != EOF) {
		slide_distinct(filter, (char)ch);
		putchar(is_extrema(filter) ? value_of(filter) : 0);
	}
	return 0;
}
