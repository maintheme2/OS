#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
    struct rusage r_usage;
    for (int i = 0; i < 10; i++) {
        void *ptr = malloc(10 * 1024 * 1024);
        memset(ptr, 0, 10 * 1024 * 1024);
        getrusage(RUSAGE_SELF, &r_usage);
        printf("Memory utilization: %ld\n", r_usage.ru_maxrss);
        sleep(1);
    }
    return 0;
}