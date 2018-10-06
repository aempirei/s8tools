#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	int ch;
	int n = 0;
	while((ch = getchar()) != EOF)
		if(++n & 1)
		putchar(ch);
	return 0;
}
