#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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
		} else if(abs(ch) > abs(state))
			state = ch;
		putchar(state);
	}
	return 0;
}
