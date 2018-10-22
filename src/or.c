#include <stdio.h>
#include <stdlib.h>

#define S8_ASSIGNMENT_OPERATOR |=

#include <s8.h>

int main(int argc, char **argv) {
	exit((argc < 3 ? serial_mode : parallel_mode)(argc, argv));
}
