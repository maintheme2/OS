#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int is_prime(int n)
{
    if (n <= 1)
        return 0;
    for (int d = 2; d * d <= n; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

int primes_count_in_interval(int start, int finish)
{
    int ret = 0;
    for (int i = start; i < finish; i++)
        if (is_prime(i) != 0)
            ret++;
    return ret;
}

// The structure that will be passed to the threads, corresponding to an 
// interval to count the number of primes in.
typedef struct prime_counter_request
{
    int start;
    int finish;
} prime_counter_request;

void *prime_counter(void *arg)
{
    prime_counter_request* args = arg;
    int* counter = malloc(sizeof(int));
    *counter = primes_count_in_interval(args->start, args->finish);
    return (void*) counter;
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]), n_threads = atoi(argv[2]);
    int segment_size = n / n_threads + (n % n_threads == 0 ? 0 : 1);

    pthread_t *threads = malloc(n_threads * sizeof(pthread_t));

    prime_counter_request *requests = malloc(n_threads * sizeof(prime_counter_request));

    void **results = malloc(n_threads * sizeof(void *));

    for (int i = 0; i < n_threads; i++)
    {   
        requests[i].start = segment_size * i;
        if (segment_size * (i + 1) <= n) {
            requests[i].finish = segment_size * (i + 1);
        } else {
            requests[i].finish = n;
        }
        if (pthread_create(threads + i, NULL, &prime_counter, (void*)&requests[i]) != 0) {
            return 1;
        }
    /*
        Complete this loop. You shall spawn <n_threads> threads, each of which computes the 
        number of primes in a segment of length <segment_size>. The union of those intervals 
        shall correspond to the interval [1, n).
        First, initialize the value of requests[i] with a simple mathematical 
        computation. Be careful not to overrun the last interval.
        Second, spawn a thread that takes requests[i] as an argument. 
        Be careful how you pass the arguments.
    */
    }

    for (int i = 0; i < n_threads; i++)
    {
        if (pthread_join(threads[i], &results[i]) != 0) {
            return 2;
        }
    /*
        TODO
        Join the results of threads into the results array.
    */
    }

    int total_result = 0;
    for (int i = 0; i < n_threads; i++)
        total_result += *(int *)results[i];

    free(threads);
    free(requests);
    free(results);
    
    /*
    TODO
    Free the allocated memory.
    */

    printf("%d\n", total_result);

    exit(EXIT_SUCCESS);
}