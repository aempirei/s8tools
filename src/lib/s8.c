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
#include <libgen.h>
#include <stdarg.h>
#include <time.h>
#include <s8.h>

struct s8_io_key_list;

typedef struct s8_io_key_list *s8_io_key_list_ptr_t;
typedef s8_io_key_list_ptr_t *s8_io_key_list_t;

struct s8_io_key_list {
	char *key;
	FILE *fp;
	s8_io_key_list_ptr_t next;
};

static s8_io_key_list_ptr_t s8_io_key_list_find(s8_io_key_list_ptr_t node, const char *key) {
	return (node == NULL) ? NULL : (strcmp(node->key, key) == 0) ? node : s8_io_key_list_find(node->next, key);
}

static s8_io_key_list_ptr_t s8_io_key_list_new(const char *key, FILE *fp, s8_io_key_list_ptr_t next) {
	s8_io_key_list_ptr_t node = malloc(sizeof(struct s8_io_key_list));
	node->key = strdup(key);
	node->fp = fp;
	node->next = next;
	return node;
}

static s8_io_key_list_ptr_t s8_io_key_list_unshift(s8_io_key_list_t list, const char *key, FILE *fp) {
	return *list = s8_io_key_list_new(key, fp, *list);
}

static bool s8_io_key_list_empty(s8_io_key_list_ptr_t head) {
	return head == NULL;
}

static s8_io_key_list_ptr_t s8_io_key_list_drop(s8_io_key_list_ptr_t head) {
	s8_io_key_list_ptr_t next = head->next;
	free(head->key);
	free(head);
	return next;
}

static bool s8_io_key_list_delete(s8_io_key_list_t list, s8_io_key_list_ptr_t node) {
	s8_io_key_list_ptr_t next = s8_io_key_list_drop(node);
	while(*list != NULL && *list != node)
		list = &((*list)->next);
	if(*list == node) {
		*list = next;
		return true;
	}
	return false;
}

static inline void s8_io_key_list_shift(s8_io_key_list_t list) {
	*list = s8_io_key_list_drop(*list);
}

static inline void s8_io_key_list_clear(s8_io_key_list_t list) {
	while(!s8_io_key_list_empty(*list))
		s8_io_key_list_shift(list);
}

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

static bool strany(const char *s, ...) {
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

static bool delay() {
	struct timespec req, rem = { 0, 1000000 };
	do req = rem;
	while(nanosleep(&req, &rem) == -1 && errno == EINTR);
	return true;
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
	if(strany(key, "-", ".", "0", NULL))
		return NULL;
	snprintf(p, sz, "%s%s", s8_io_basename(), key);
	return p;
}

bool s8_io_ready(const char *key, char mode) {
	struct stat sb;
	char filename[NAME_MAX];
	if(strany(key, "-", ".", "0", NULL)) {
		return true;
	} else if(mode == 'w') {
		return true;
	} else if(mode == 'r') {
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

static s8_io_key_list_ptr_t head = NULL;

FILE *s8_io_open(const char *key, char mode) {
	s8_io_key_list_ptr_t node;

	const char mode_s[2] = { mode };
	struct stat sb;
	char filename[NAME_MAX];

	if((node = s8_io_key_list_find(head, key)))
		return node->fp;

	if(strcmp(key, "-") == 0)
		return s8_io_key_list_unshift(&head, key, fdopen(dup(mode != 'w' ? mode != 'r' ? STDERR_FILENO : STDIN_FILENO : STDOUT_FILENO), mode_s))->fp;

	if(strcmp(key, ".") == 0)
		return s8_io_key_list_unshift(&head, key, fopen("/dev/null", mode_s))->fp;

	if(strcmp(key, "0") == 0)
		return s8_io_key_list_unshift(&head, key, fopen("/dev/zero", mode_s))->fp;

	s8_io_filename_r(filename, sizeof(filename), key);
	if(mkfifo(filename, 0700) == -1 && errno != EEXIST)
		return NULL;
	if(stat(filename, &sb) == -1)
		return NULL;
	if((sb.st_mode & S_IFMT) != S_IFIFO) {
		errno = ENOSTR;
		return NULL;
	}
	return s8_io_key_list_unshift(&head, key, fopen(filename, mode_s))->fp;
}

int s8_io_close(FILE *f, const char *key, char mode) {

	s8_io_key_list_ptr_t node = s8_io_key_list_find(head, key);

	if(node == NULL)
		return 0;

	if(s8_io_key_list_delete(&head, node) == false) {
		fprintf(stderr, "key list delete failed for node with expected key %s\n", key);
		exit(EXIT_FAILURE);
	}

	if(mode == 'r') {
		char filename[NAME_MAX];
		if(s8_io_filename_r(filename, sizeof(filename), key) != NULL)
			unlink(filename);
	}
	return fclose(f);
}

int s8_io_close_all(FILE *f[], char *keys[], size_t n, char mode) {
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


int s8_io_open_all(FILE *f[], char *keys[], size_t n, char mode) {

	int e;
	bool opened[n];
	bool finished;

	for(size_t k = 0; k < n; k++)
		opened[k] = false;

	do {
		finished = true;
		for(size_t k = 0; k < n; k++) {
			if(!opened[k] && s8_io_ready(keys[k], mode)) {
				if((f[k] = s8_io_open(keys[k], mode)) == NULL) {
					e = errno;
					for(size_t j = 0; j < n; j++)
						if(opened[j])
							s8_io_close(f[j], keys[j], mode);
					errno = e;
					return -1;
				}
				opened[k] = true;
			}
			if(!opened[k])
				finished = false;
		}
	} while(!finished && delay());

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
		s[k] = strtol(coefs[k], NULL, 0);
	return true;
}

long int s8_bank_apply(const char *f, const char *g, int d, size_t n) {
	long int x = 0;
	for(size_t k = 0; k < n; k++)
		x += f[k] * g[k];
	return x / d;
}

bool s8_io_castable(enum s8_type a, enum s8_type b) {
	if(a == b || b == s8_type_any)
		return true;
	switch(a) {
		case s8_type_zero:
			return true;
		case s8_type_bool:
			if(b == s8_type_sign)
				return true;
		case s8_type_sign:
			if(b == s8_type_7bit)
				return true;
		case s8_type_7bit:
			if(b == s8_type_signed || b == s8_type_unsigned)
				return true;
	}
	return false;
}

bool s8_io_type_append(char *sig, size_t size, enum s8_type type) {
	size_t len = strlen(sig);
	char *p = sig + len;
	if(len + 1 == size) {
		errno = ENOBUFS;
		return false;
	}
	*p++ = type;
	*p = '\0';
	return true;
}

bool s8_io_typesig_w(char *prog, char *typesig, FILE *f) {
	return getenv("S8_TYPEINFO") == NULL || fprintf(f, "%s %d :%s\n", basename(prog), getpid(), typesig) == 3;
}

bool s8_io_typesig_r(char *prog, size_t prog_sz, int *id, char *typesig, size_t typesig_sz, FILE *f) {

	char *typeinfo = getenv("S8_TYPEINFO");
	char *p = typesig;
	char fmt[32];

	if(typeinfo == NULL)
		return true;

	snprintf(fmt, sizeof(fmt), "%%%lu[_a-z] %%d :", prog_sz);

	if(fscanf(f, fmt, prog, id) != 2) 
		return false;

	if(fgets(typesig, typesig_sz - 1, f))
		p = strpbrk(typesig, "\r\n");

	if(p)
		*p = '\0';

	return true;
}
