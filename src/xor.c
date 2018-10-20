#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <s8.h>

int main(int argc, char **argv) {

	const size_t N = argc - 1;
	FILE *fs[N];
	char s[N];

	if(s8_io_open_all(fs, &argv[1], N, "r") == -1) {
		perror("s8_io_open_all()");
		exit(EXIT_FAILURE);
	}

	while(s8_bank_parallel_next(s, N, fs)) {
		int xor = s[0];
		for(size_t k = 1; k < N; k++)
			xor ^= s[k];
		putchar(xor);
	}

	if(s8_io_close_all(fs, argv+1, N, "r") == -1) {
		perror("s8_io_close_all()");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
