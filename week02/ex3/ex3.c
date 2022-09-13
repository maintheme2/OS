#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

size_t
to_decimal(size_t value, short base) {
    // convert int to str
    size_t length = snprintf(NULL, 0,"%ld", value);
    char* value_str = calloc(length + 1, sizeof(char));
    sprintf(value_str, "%ld", value);

    size_t len = strlen(value_str);
    size_t decimal_value = 0; // result
    size_t counter = len; // iterator 

    int i = 0;
    while (counter != 0)
        decimal_value += (value_str[i++] - '0') * pow((double)base, (double)--counter); 

    return decimal_value;
}

size_t
convert(size_t value, short src, short trgt) {
    if ((src < 2) || (trgt < 2) || (src > 10) || (trgt  > 10)) {
        printf("cannot convert!\nExit code: ");
        return -1;
    }
    if (src == trgt) return value;

    // convert int to str
    size_t length = snprintf(NULL, 0,"%ld", value);
    char* value_str = calloc(length + 1, sizeof(char));
    sprintf(value_str, "%ld", value);
    
    for (size_t i = 0; i < strlen(value_str); i++) {
        if ((value_str[i] - '0') >= src) {
            printf("cannot convert!\nExit code: ");
            return -1;
        }
    }

    value = to_decimal(value, src);
    if (trgt == 10) return value;

    char* result = calloc(1, sizeof(char*));
    int i = 0;
    while(value > 0) {
        result[i++] = (value % trgt + '0');
        value /= trgt;
    }

    for (size_t i = 0; i < strlen(result)/2; i++) {
        char temp = result[i];
        result[i] = result[strlen(result) - i - 1];
        result[strlen(result) - i - 1] = temp;
    }

    return atol(result);
}

int
main(int argc, char** argv) {
    size_t value;
    short s,t;
    scanf("%ld", &value);
    scanf("%hi", &s);
    scanf("%hi", &t);
    size_t result = convert(value, s, t);
    printf("%ld", result);
    return 0;
}