#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	char x[2] = { 0, getchar() };
	int ch;

	if(!feof(stdin)) while((ch = getchar()) != EOF) {
		x[1] = x[2];
		x[2] = (char)ch;
		ch = x[2] - x[1];
		if(ch > INT8_MAX)
			ch = INT8_MAX;
		if(ch < INT8_MIN)
			ch = INT8_MIN;
		putchar(ch);
	}
	return 0;
}
