#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	int ch;
	int p = 0;
	while((ch = getchar()) != EOF) {
		ch = (char)ch;
		putchar(abs(ch) > abs(p) ? ch : p);
		p = ch;
	}
	return 0;
}
