#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int is_maxima(const int filter[3]) {
	return filter[1] > filter[0] && filter[1] > filter[2];
}

int is(const int filter[3]) {
	return filter[1];
}

int pushift(int filter[3], int x) {
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
	int maxima = INT8_MIN;
	int filter[3] = { INT8_MIN, INT8_MIN, INT8_MIN };
	while((ch = getchar()) != EOF) {
		pushift(filter, (char)ch);
		if(is_maxima(filter))
			maxima = is(filter);
		putchar(maxima);
	}
	return 0;
}
