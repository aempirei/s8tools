#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <s8.h>

typedef struct range {
	size_t first;
	size_t length;
	char *xs;
} range_t;

bool parse_range(range_t *r, const char *s, size_t rate) {

	double first, last;
	int n;
	const char *p;
	char mode;

	if(rate <= 0)
		goto einval_error;

	p = s;

	if(sscanf(p, " %lf %n", &first, &n) == 0)
		goto einval_error;

	p += n;

	mode = *p++;

	if(mode != 0x0)
		if(sscanf(p, " %lf ", &last) == 0)
			goto einval_error;

	switch(mode) {

		case '-':                break;
		case '+': last += first; break;
		case 0x0: last  = first; break;

		default: goto einval_error;
	}

	if(first < 0.0 || last < 0.0 || last < first)
		goto einval_error;

	r->first = (size_t)rint(first * rate);
	r->length = (size_t)rint((last - first) * rate);

	if(rate == 1 || r->length == 0)
		r->length++;

	r->xs = malloc(r->length);
	if(r->xs == NULL)
		return false;

	memset(r->xs, 0, r->length);

	return true;

einval_error:
	errno = EINVAL;
	return false;
}

bool in_range(range_t *r, size_t n) {
	return n >= r->first && n < (r->first + r->length);
}

char range_assign_byte(range_t *r, size_t n, char ch) {
	return ( r->xs[n - r->first] = ch );
}

int main(int argc, char **argv) {
	unsigned int rate = (argc > 1) ? strtoul(argv[1], NULL, 0) : 1;
	size_t ranges = argc - 2;
	range_t range[ranges];
	size_t k, n;
	int ch;

	for(n = 0; n < ranges; n++) {
		if(!parse_range(range + n, argv[n + 2], rate)) {
			fprintf(stderr, "failed to parse range \"%s\" at argument #%lu: %s\n", argv[n + 2], n + 2, strerror(errno));
			exit(EXIT_FAILURE);
		}
	}

	k = 0;

	while((ch = getchar()) != EOF) {

		for(n = 0; n < ranges; n++)
			if(in_range(range+n,k))
				range_assign_byte(range+n,k,ch);

		k++;
	}

	for(n = 0; n < ranges; n++)
		for(k = 0; k < range[n].length; k++)
			putchar(range[n].xs[k]);

	exit(EXIT_SUCCESS);
}
