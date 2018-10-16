#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <s8.h>

static inline const char *nulltoempty(const char *s) {
	return s ? s : "";
}

const char *s8_io_basename() {
	static char s[NAME_MAX] = "/tmp/s8-fifo.";
	static bool done = false;
	if(!done) {
		snprintf(s, sizeof(s), "/tmp/s8-fifo.%s", nulltoempty(getenv("S8_PREFIX")));
		done = true;
	}
	return s;
}

const char *s8_io_filename(char *p, size_t sz, const char *key) {
	snprintf(p, sz, "%s%s", s8_io_basename(), key);
	return p;
}

FILE *s8_io_open(const char *key, const char *mode) {
	struct stat sb;
	char filename[NAME_MAX];
	s8_io_filename(filename, sizeof(filename), key);
	if(mkfifo(filename, 0700) == -1 && errno != EEXIST)
		return NULL;
	if(stat(filename, &sb) == -1)
		return NULL;
	if((sb.st_mode & S_IFMT) != S_IFIFO) {
		errno = ENOSTR;
		return NULL;
	}
	return fopen(filename, mode);
}

int s8_io_close(FILE *f, const char *key, const char *mode) {
	int n = fclose(f);
	if(strcmp(mode, "r") == 0) {
		char filename[NAME_MAX];
		s8_io_filename(filename, sizeof(filename), key);
		n = unlink(filename);
	}
	return n;
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
