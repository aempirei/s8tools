#include <stdio.h>
#include <stdlib.h>
#include <s8.h>

int main() {
	char x[2];

	while(s8_bank_next(x, 2, stdin))
		for(size_t k = 0; k < (unsigned char)x[0]; k++)
			putchar(x[1]);

	exit(EXIT_SUCCESS);
}
