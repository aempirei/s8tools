#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	int ch;
	int maxima = 0;
	while((ch = getchar()) != EOF) {
		ch = (char)ch;
		if(maxima > 0)
			maxima--;
		if(ch > maxima)
			maxima = ch;
		putchar(maxima);
	}
	return 0;
}
