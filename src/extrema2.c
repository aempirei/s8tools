#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>

bool is_maxima(int a, int b, int c) { return b > a && b > c; }
bool is_minima(int a, int b, int c) { return b < a && b < c; }

int is_extrema(int a, int b, int c) { return is_maxima(a,b,c) ? 1 : is_minima(a,b,c) ? -1 : 0; }

typedef int cast_function(int);

#define XXEOF (EOF * 0x1000)

int to_s(int ch) {
	return (ch == EOF) ? XXEOF : (signed char)ch;
}

int to_u(int ch) {
	return (ch == EOF) ? XXEOF : (unsigned char)ch;
}

int fgetcstar(size_t *count, FILE *stream) {

	size_t n = 1;
	int ch;
	int dh;

	if((ch = fgetc(stream)) == EOF)
		return EOF;

	while(ch == (dh = fgetc(stream)))
		n++;
	
	if(dh != EOF && ungetc(dh, stream) == EOF)
		return EOF;

	*count = n;

	return ch;
}

int getcstar(size_t *count) {
	return fgetcstar(count,stdin);
}

int fputcstar(int c, size_t N, FILE *stream) {
	for(size_t n = 0; n < N; n++) 
		if(fputc(c, stream) == EOF)
			return EOF;
	return c;
}

int putcstar(int c, size_t b) {
	return fputcstar(c,b,stdout);
}

int main(int argc, char **argv) {
	const char signedness = argc == 2 ? argv[1][0] : 's';
	cast_function *cast_fn = signedness == 's' ? to_s : signedness == 'u' ? to_u : NULL;
	int a,b,c,d;
	size_t B,C,D;

	if(cast_fn == NULL) {
		fprintf(stderr, "unexpected signedness specification '%c'\n", signedness);
		exit(EXIT_FAILURE);
	}

	b = cast_fn(getcstar(&B));
	c = cast_fn(getcstar(&C));

	putcstar(0,B);

	while((d = cast_fn(getcstar(&D))) != XXEOF) {

		a = b;
		b = c; B = C;
		c = d; C = D;

		int x = is_extrema(a,b,c);

		size_t L = (B - 1) / 2;
		size_t R = (B - 1) - L;

		putcstar(0,L);
		putchar(x);
		putcstar(0,R);
	}

	if(errno) {
		perror("getcstar()");
		exit(EXIT_FAILURE);
	}

	putcstar(0,C);

	exit(EXIT_SUCCESS);
}
