#include <stdio.h>
#include <s8.h>

int s8_bank_init(char *s, int n, FILE *f) {
	*s = 0;
	for(int i = 1; i < n; i++)
		s[i] = fgetc(f);
	return !feof(f);
}

int s8_bank_shift(char *s, int n, FILE *f) {
	int i;
	for(i = 1; i < n; i++)
		s[i - 1] = s[i];
	s[i - 1] = fgetc(f);
	return !feof(f);
}
