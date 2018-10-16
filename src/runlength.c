#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

enum slope { up, down, flat, unknown };

int print_run(int rl, enum slope s) {
	return printf("%d %s\n", rl, (s == up) ? "up" : (s == down) ? "down" : (s == flat) ? "flat" : "unknown");
}

int main() {

	enum slope prev_slope = unknown;
	enum slope curr_slope;
	int prev_ch;
	int curr_ch;
	int runlength = 0;

	if((prev_ch = getchar()) == EOF)
		return 0;

	prev_ch = (char)prev_ch;

	while((curr_ch = getchar()) != EOF) {
		curr_ch = (char)curr_ch;
		curr_slope = (curr_ch > prev_ch) ? up : (curr_ch < prev_ch) ? down : flat;
		if(curr_slope != prev_slope && curr_slope != flat) {
			print_run(runlength, prev_slope);
			runlength = 0;
			prev_slope = curr_slope;
		}
		runlength++;
		prev_ch = curr_ch;
	}
	print_run(runlength, curr_slope);
	return 0;
}
