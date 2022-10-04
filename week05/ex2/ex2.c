#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <unistd.h>

typedef struct Thread{
    pid_t id;
    int i;
    char* message;
}thread_t;

// pthread_mutex_t mutex;

void* display_message(void* arg) {
    // pthread_mutex_lock(&mutex);
    thread_t* thread = (thread_t*)arg;
    thread->id = syscall(SYS_gettid);
    printf("Thread %d (id: %d) prints message: %s\n", thread->i, thread->id, thread->message);
    printf("Thread %d exits\n", thread->i);
    // pthread_mutex_unlock(&mutex);
}

int 
main(int argc, char const *argv[]) {
    // pthread_mutex_init(&mutex, NULL);
    int n = atoi(argv[1]);
    pthread_t threads[n];
    thread_t custom_threads[n];
    for (size_t i = 0; i < n; i++) {
        custom_threads[i].i = i;
        custom_threads[i].message = malloc(256);
        sprintf(custom_threads[i].message, "Hello from thread %d", i);
        if (pthread_create(&threads[i], NULL, display_message, (void*)&custom_threads[i]) != 0) {
            perror("Failed to create a thread");
        } else {
            printf("Thread %d is created\n", custom_threads[i].i);
        }
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join a thread");
        }
    }
    // pthread_mutex_destroy(&mutex);

    return 0;
}
