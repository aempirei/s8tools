#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <s8.h>

int main(int argc, char **argv) {

	const size_t N = argc - 1;
	FILE *f[N];
	int ch;
	size_t k = 0;

	if(s8_io_open_all(f, argv + 1, N, 'w') == -1) {
		perror("s8_io_open_all()");
		exit(EXIT_FAILURE);
	}

	while((ch = getchar()) != EOF) {
		fputc(ch, f[k++]);
		k %= N;
	}

	if(s8_io_close_all(f, argv + 1, N, 'w') == -1) {
		perror("s8_io_close_all()");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
