#include <stdio.h>
#include <stdlib.h>
#include <s8.h>
#include <s8-basic-function.h>
#if defined(FOLD) && defined(FINAL)
int main(int argc, char **argv) {
	return fold_function(argc, argv, FOLD, FINAL);
}
#else
#error "FOLD macro must be defined and have type <binary_function_t *>"
#endif
