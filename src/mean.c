#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {

	size_t n;

	FILE **fpn;

	int *cn;

	if(argc == 1) {
		fprintf(stderr, "\nusage: %s file...\n\n", *argv);
		exit(EXIT_FAILURE);
	}

	n = argc - 1;

	fpn = malloc(sizeof(*fpn) * n);
	cn = malloc(sizeof(*cn) * n);

	for(size_t k = 0; k < n; k++) {
		fpn[k] = fopen(argv[k + 1], "r");
		if(fpn[k] == NULL) {
			fprintf(stderr, "failed to open %s for reading: %s\n", argv[k + 1], strerror(errno));
			exit(EXIT_FAILURE);
		}
	}

	for(;;) {

			size_t closed = 0;

			long sum = 0;

			for(size_t k = 0; k < n; k++) {

					cn[k] = fgetc(fpn[k]);

					if(cn[k] == EOF) {
							fclose(fpn[k]);
							closed++;
					}

					sum += cn[k];
			}

			if(closed > 0) {
					if(closed != n) {
							fprintf(stderr, "error: unequal sized input");
							exit(EXIT_FAILURE);
					}

					break;
			}

			putchar(sum / n);
	}

	free(cn);
	free(fpn);

	exit(EXIT_SUCCESS);
}
