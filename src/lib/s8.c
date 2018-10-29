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
#include <stdarg.h>
#include <s8.h>

static inline const char *nulltoempty(const char *s) {
	return s ? s : "";

}

static inline bool strnotany(const char *s, ...) {
	va_list ap;
	bool retval = true;
	const char *t;
	va_start(ap, s);
	while((t = va_arg(ap, const char *)) != NULL)
		if(retval)
			retval = (strcmp(s, t) != 0);
	va_end(ap);
	return retval;
}

static inline bool strany(const char *s, ...) {
	va_list ap;
	bool retval = false;
	const char *t;
	va_start(ap, s);
	while((t = va_arg(ap, const char *)) != NULL)
		if(!retval)
			retval = (strcmp(s, t) == 0);
	va_end(ap);
	return retval;
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

const char *s8_io_filename(const char *key) {
	static char s[NAME_MAX];
	return s8_io_filename_r(s, sizeof(s), key);
}

const char *s8_io_filename_r(char *p, size_t sz, const char *key) {
	snprintf(p, sz, "%s%s", s8_io_basename(), key);
	return p;
}

bool s8_io_ready(const char *key, const char *mode) {
	struct stat sb;
	char filename[NAME_MAX];
	if(strcmp(mode, "w") == 0) {
		return true;
	} else if(strcmp(mode, "r") == 0) {
		if(strany(key, "-", ".", "0", NULL))
			return true;
		s8_io_filename_r(filename, sizeof(filename), key);
		if(stat(filename, &sb) == -1)
			return false;
		if((sb.st_mode & S_IFMT) != S_IFIFO) {
			errno = ENOSTR;
			return false;
		}
		return true;
	} else {
		return false;
	}
}

FILE *s8_io_open(const char *key, const char *mode) {
	struct stat sb;
	char filename[NAME_MAX];

	if(strcmp(key, "-") == 0)
		return fdopen(dup(strcmp(mode, "w") ? strcmp(mode, "r") ? STDERR_FILENO : STDIN_FILENO : STDOUT_FILENO), mode);

	if(strcmp(key, ".") == 0)
		return fopen("/dev/null", mode);

	if(strcmp(key, "0") == 0)
		return fopen("/dev/zero", mode);

	s8_io_filename_r(filename, sizeof(filename), key);
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
	if(strcmp(mode, "r") == 0) {
		char filename[NAME_MAX];
		s8_io_filename_r(filename, sizeof(filename), key);
		unlink(filename);
	}
	return fclose(f);
}

int s8_io_close_all(FILE *f[], char *keys[], size_t n, const char *mode) {
	int retval = 0;
	int e = 0;
	for(size_t k = 0; k < n; k++) {
		if(s8_io_close(f[k], keys[k], mode) == -1) {
			retval = -1;
			e = errno;
		}
	}
	errno = e;
	return retval;
}


int s8_io_open_all(FILE *f[], char *keys[], size_t n, const char *mode) {
	int e;
	for(size_t k = 0; k < n; k++) {
		if((f[k] = s8_io_open(keys[k], mode)) == NULL) {
			e = errno;
			if(k > 0)
				s8_io_close_all(f, keys, k-1, mode);
			errno = e;
			return -1;
		}
	}
	return 0;
}

bool s8_bank_init(char *s, size_t n, FILE *f) {
	*s = 0;
	for(size_t i = 1; i < n; i++)
		s[i] = fgetc(f);
	return !feof(f);
}

bool s8_bank_shift(char *s, size_t n, FILE *f) {
	int ch;
	for(size_t i = 1; i < n; i++)
		s[i - 1] = s[i];
	s[n - 1] = ch = fgetc(f);
	return (ch != EOF);
}

bool s8_bank_parallel_next(char *s, size_t n, FILE *fs[]) {
	for(size_t k = 0; k < n; k++) {
		int ch = fgetc(fs[k]);
		if(ch == EOF)
			return false;
		s[k] = ch;
	}
	return true;
}

bool s8_bank_serial_next(char *s, size_t n, FILE *f) {
	for(size_t k = 0; k < n; k++) {
		int ch = fgetc(f);
		if(ch == EOF)
			return false;
		s[k] = ch;
	}
	return true;
}

bool s8_bank_defun(char *s, int *d, char **coefs, size_t n) {
	if(n < 2 || s == NULL || d == NULL || coefs == NULL)
		return false;
	*d = atoi(coefs[--n]);
	for(size_t k = 0; k < n; k++)
		s[k] = atoi(coefs[k]);
	return true;
}

long int s8_bank_apply(const char *f, const char *g, int d, size_t n) {
	long int x = 0;
	for(size_t k = 0; k < n; k++)
		x += f[k] * g[k];
	return x / d;
}
