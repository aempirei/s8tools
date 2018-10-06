#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	int ch;
	int minima = 0;
	while((ch = getchar()) != EOF) {
		ch = (char)ch;
		if(minima < 0)
			minima++;
		if(ch < minima)
			minima = ch;
		putchar(minima);
	}
	return 0;
}
