#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <s8.h>

const char *s8_context_dirname() {
	static char s[NAME_MAX];
	static bool done = false;
	if(!done) {
		snprintf(s, sizeof(s), "/tmp/s8-%d", getppid());
		done = true;
	};
	return s;
}

const char *s8_context_filename(char *p, size_t sz, const char *key) {
	snprintf(p, sz, "%s-%s", s8_context_dirname(), key);
	return p;
}

FILE *s8_writer(const char *key) {
	char filename[NAME_MAX];
	s8_context_filename(filename, sizeof(filename), key);
	if(mkfifo(filename, 0700) == -1)
		return NULL;
	return fopen(filename, "w");
}

FILE *s8_reader(const char *key) {
	char filename[NAME_MAX];
	s8_context_filename(filename, sizeof(filename), key);
	return fopen(filename, "r");
}

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
