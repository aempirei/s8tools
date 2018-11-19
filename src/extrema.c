#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef int filter_t[3];

int is_maxima(const filter_t zs) { return zs[1] > zs[0] && zs[1] > zs[2]; }
int is_minima(const filter_t zs) { return zs[1] < zs[0] && zs[1] < zs[2]; }

int value_of(const filter_t zs) {
	return is_maxima(zs) ? 1 : is_minima(zs) ? -1 : 0;
}

int slide(filter_t zs, int ch) {
	zs[0] = zs[1];
	zs[1] = zs[2];
	zs[2] = ch;
	return value_of(zs);
}

typedef int cast_function(int);

int to_s(int ch) {
	return (signed char)ch;
}

int to_u(int ch) {
	return (unsigned char)ch;
}

int main(int argc, char **argv) {
	const char signedness = argc == 2 ? argv[1][0] : 's';
	cast_function *cast_fn = signedness == 's' ? to_s : signedness == 'u' ? to_u : NULL;
	int ch;
	if(cast_fn == NULL) {
		fprintf(stderr, "unexpected signedness specification '%c'\n", signedness);
		exit(EXIT_FAILURE);
	}
	filter_t zs = { 0, cast_fn(getchar()), cast_fn(getchar()) };
	putchar(0);
	while((ch = getchar()) != EOF)
		putchar(slide(zs, cast_fn(ch)));
	putchar(0);
	exit(EXIT_SUCCESS);
}
