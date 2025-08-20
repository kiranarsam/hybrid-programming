
/**
 * Enable:
 * #define _GNU_SOURCE
 * or
 * gcc sample.cpp -o sample -lpthread -D_GNU_SOURCE
 */

#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>

static void * helloFunction(void *arg)
{
  printf("From helloFunction thread context\n");
  sleep(10);
  return NULL;
}

int main(int argc, char **argv) {
    printf("Executing main thread\n");
    pthread_t thread;
    pthread_create(&thread, NULL, helloFunction, NULL);

    // Measure execution time of pthread_getaffinity_np
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    cpu_set_t cpu_set;
    pthread_getaffinity_np(thread, sizeof(cpu_set), &cpu_set);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("pthread_getaffinity_np took %ld ns\n", (end.tv_nsec - start.tv_nsec));

    // Measure execution time of pthread_setaffinity_np
    clock_gettime(CLOCK_MONOTONIC, &start);
    CPU_ZERO(&cpu_set);
    CPU_SET(1, &cpu_set);
    pthread_setaffinity_np(thread, sizeof(cpu_set), &cpu_set);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("pthread_setaffinity_np took %ld ns\n", (end.tv_nsec - start.tv_nsec));

    printf("Waiting for child thread\n");
    pthread_join(thread, NULL);
    printf("Exiting main thread\n");

    return 0;
}
