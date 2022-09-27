#include <stdio.h>
#include <stdlib.h>

void* 
aggregate(void* base, size_t size, int n, void* initial_value, void* (*opr)(const void*, const void*));

void*
add_int(const void* a, const void* b) {
    int* sum = malloc(sizeof(int));
    *sum = *((int*)a) + *((int*)b);
    return sum;
}

void* 
add_double(const void* a, const void* b) {
    double* sum = malloc(sizeof(double));
    *sum = *((double*)a) + *((double*)b);
    return sum;
}

void* 
mul_int(const void* a, const void* b) {
    int* mul = malloc(sizeof(int));
    *mul = *((int*)a) * *((int*)b);
    return mul;
}

void* 
mul_double(const void* a, const void* b) {
    double* mul = malloc(sizeof(double));
    *mul = *((double*)a) * *((double*)b);
    return mul;
}

void* 
mean_int(const void* a, const void* b) {
    int* mean = (int*) malloc(sizeof(int));
    *mean = (*((int*)a) + *((int*)b)) / 2;
    return mean;
}

void* 
mean_double(const void* a, const void* b) {
    double* mean = malloc(sizeof(double));
    *mean = (*((double*)a) + *((double*)b)) / 2;
    return mean;
}

void* 
aggregate(void* base, size_t size, int n, void* initial_value, void* (*opr)(const void*, const void*)) {

	void* output;

	if (size == sizeof(int)) { // base is a pointer to an integer
        output = malloc(sizeof(int));
	    base = (int*) base;
        initial_value = (int*) initial_value;
        output = initial_value;

        for (short i = 0; i < 5; i++) {
            output = opr(output, base + i * size);
        }
	} else { // base is a pointer to a double
        output = malloc(sizeof(double));
	    base = (double*) base;
        initial_value = (double*) initial_value;
        output = initial_value;

        for (short i = 0; i < 5; i++) {
            output = opr(output, base + i * size);
        }
	}
	return output;
}

int 
main() {
    int* ints = malloc(sizeof(int) * 5);
    double* doubles = malloc(sizeof(double) * 5);
        
    for (short i = 0; i < 5; i++) {
        *(ints + i) = (int)i;
        *(doubles + i) = (double)i;
    }

	// Addition
    int* result_1a = aggregate(ints, sizeof(int), 5, (void*)(0), add_int);
    printf("%d\n", *result_1a);
    
	double* result_2a = aggregate(doubles, sizeof(double), 5, (void*)(0.0), add_double);
    printf("%f\n", *result_2a);
                
	// Multiplication
    int* result_1m = aggregate(ints, sizeof(int), 5, (void*)(1), mul_int);
    printf("%d\n", *result_1m);

	double* result_2m = aggregate(doubles, sizeof(double), 5, (void*)(1.0), mul_double);
    printf("%f\n", *result_2m);
    
	// Mean
    int* result_1mean = aggregate(ints, sizeof(int), 5, (void*)(0), mean_int);
    printf("%d\n", *result_1mean);

	double* result_2mean = aggregate(doubles, sizeof(double), 5, (void*)(0.0), mean_double);
    printf("%f\n", *result_2mean);

    // free the pointers
    free(result_1a);
    free(result_2a);
    free(result_1m);
    free(result_2m);
    free(result_1mean);
    free(result_2mean);
    free(ints);
    free(doubles);
}
