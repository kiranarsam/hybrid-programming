#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /* For working with POSIX threads*/
#include <unistd.h>  /* For pause() and sleep() */
#include <errno.h>	 /* For using Global variable errno */
#include <assert.h>
#include <stdatomic.h>
#include <signal.h>
#include <stdbool.h>

// Initialize the mutex and condition variable
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
bool terminate_app = false;

int arr[] = { 1, 2, 3, 4, 5};

void print_array()
{
	int i = 0;
	int arr_size = sizeof(arr)/sizeof(arr[0]);

	for( ; i < arr_size -1; i++){

		printf("%d ", arr[i]);
	}
	printf("%d\n", arr[i]);
}

/* A thread callback fn must have following prototypes
 * void *(*thread_fn)(void *)
 * */
static void * thread_fn_callback_sum(void *arg)
{
	int i;
	int sum;

	int arr_size = sizeof(arr)/sizeof(arr[0]);

	do {
		sum = 0;
		i = 0;
    sleep(1); // adding sleep time for log, to check proper synchronization
    pthread_mutex_lock(&mutex);

		while(i < arr_size) {
			sum += arr[i];
			i++;
		}
		printf("sum = %d\n", sum);
		print_array();
		assert(sum == 15);

    pthread_mutex_unlock(&mutex);

	} while(!terminate_app);
}

static void * thread_fn_callback_swap(void *arg)
{
	int temp;
	int arr_size = sizeof(arr)/sizeof(arr[0]);

	do {
    sleep(1); // adding sleep time for log, to check proper synchronization
    pthread_mutex_lock(&mutex);

		temp = arr[0];
		arr[0] = arr[arr_size -1];
		arr[arr_size-1] = temp;
		printf("swap :\n");
		print_array();

    pthread_mutex_unlock(&mutex);

	} while(!terminate_app);
}

void sum_thread_create()
{
	/* opaque object, dont bother about its internal members */
	pthread_t pthread1;

	int rc = pthread_create(&pthread1, NULL, thread_fn_callback_sum, NULL);
	if(rc != 0) {
		printf("Error occurred, thread could not be created, errno = %d\n", rc);
		exit(0);
	}
}

void swap_thread_create()
{
	/* opaque object, dont bother about its internal members */
	pthread_t pthread2;

	int rc = pthread_create(&pthread2, NULL, thread_fn_callback_swap, NULL);
	if(rc != 0) {
		printf("Error occurred, thread could not be created, errno = %d\n", rc);
		exit(0);
	}
}

void signalHandler(int _signal)
{
	if (_signal == SIGINT || _signal == SIGTERM)
	{
		terminate_app = true;
		printf("Application exited\n");
	}
}

int main(int argc, char **argv)
{
	sum_thread_create();
	swap_thread_create();

  // register signal to terminate the application gracefully
	signal(SIGINT, signalHandler);
  signal(SIGTERM, signalHandler);

	// Instead of mutex and cond variable, use pause() and signal handler
	// Suspending execution ...
	pause();
	/*  Allow main thread to exit, while other threads would keep running */
	pthread_exit(0);
	return 0;
}