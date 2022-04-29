#include "alloc.h"
#include <stdio.h>

int main() {
	int *val = alloc(sizeof(int));
	*val = 69;
	int *val2 = alloc(2*sizeof(int));
	val2[0] = 1;
	val2[1] = 2;
	val2 = reallocate(val2, 3*sizeof(int));	
	val2[2] = 3;
	printf("%i %i\n", *val, val2[2]);
	return 0;
}
