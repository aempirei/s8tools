#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int sign(int x) {
	return (x > 0) ? 1 : (x < 0) ? -1 : 0;
}

int main() {
	int ch;
	int state = 0;
	while((ch = getchar()) != EOF) {
		ch = (char)ch;
		if(ch == 0) {
			if(state > 0)
				state--;
			else if(state < 0)
				state++;
		} else if(sign(ch) != sign(state))
			state = ch;
		putchar(state);
	}
	return 0;
}
