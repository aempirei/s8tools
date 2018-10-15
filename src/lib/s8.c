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
	static char s[32];
	static bool done = false;
	if(!done) {
		snprintf(s, sizeof(s), "/tmp/s8-%d", getppid());
		done = true;
	};
	return s;
}

int s8_context_init() {
	if(access(s8_context_dirname(), F_OK) == -1) {
		if(errno == ENOENT) {
			if(mkdir(s8_context_dirname(), 0700) == -1 && errno != EEXIST)
				return -1;
		} else
			return -1;
	}
	return 0;
}

int s8_context_nextid() {
	struct dirent *de;
	DIR *d;
	int fd;
	int id = 0;

	if((d = opendir(s8_context_dirname())) == NULL)
		return -1;
	
	if((fd = dirfd(d)) != -1)
		while(flock(fd, LOCK_EX) == -1 && errno == EINTR)
			;

	errno = 0;
	while((de = readdir(d)) != NULL)
		if(strcmp(de->d_name, ".") && strcmp(de->d_name, ".."))
			id++;
	if(errno)
		id = -1;

	closedir(d);
	return id;
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
