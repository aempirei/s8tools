#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <s8.h>

void output(double Sxx, double Sx, int N) {
	double d = Sxx / N;
	double e = Sx / N;
	double f = d - e * e;
	int x = (int)ceil(sqrt(f));
	putchar(x < UCHAR_MAX ? x : UCHAR_MAX);
	putchar(N < UCHAR_MAX ? N : UCHAR_MAX);
}

int main(int argc, char **argv) {

	FILE *f = s8_io_open(argc == 1 ? "0" : argv[1], 'r');

	int N = 0;
	long Sx = 0, Sxx = 0;

	int ch, control;

	while((ch = getchar()) != EOF && (control = fgetc(f)) != EOF) {
		ch = (char)ch;
		N++;
		Sxx += ch * ch;
		Sx += ch;
		if(control) {
			output(Sxx, Sx, N);
			N = Sx = Sxx = 0;
		}
	}
	output(Sxx, Sx, N);

	exit(EXIT_SUCCESS);
}
