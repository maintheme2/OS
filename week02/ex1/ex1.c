#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>

int main() {
	int integer = INT_MAX;
	unsigned short u_short = USHRT_MAX;
	signed long s_long = LONG_MAX;
	float floating = FLT_MAX;
	double dbl = DBL_MAX;

	printf("INT: %ld %d\n", sizeof(integer), integer);
	printf("SHORT: %ld %d\n", sizeof(u_short), u_short);
	printf("LONG: %ld %ld\n", sizeof(s_long), s_long);
	printf("FLOAT: %ld %f\n", sizeof(floating), floating);
	printf("DOUBLE: %ld %f\n", sizeof(dbl), dbl);
}
