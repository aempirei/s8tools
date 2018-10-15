#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int clip(int x) {
	return x > INT8_MAX ? INT8_MAX : x < INT8_MIN ? INT8_MIN : x;
}

int main() {

	char x[2] = { 0, getchar() };
	int ch;

	while((ch = getchar()) != EOF) {
		x[0] = x[1];
		x[1] = ch;
		putchar(clip(x[1] - x[0]));
	}
	return 0;
}
