#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <signal.h>

bool terminate_app = false;

#define N_SLAVES	5

pthread_t slaves[N_SLAVES];

void memory_cleanup_handler(void *arg)
{
	printf("%s invoked...\n", __FUNCTION__);
	free(arg);
}

void file_cleanup_handler(void *arg)
{
	printf("%s invoked...\n", __FUNCTION__);
	fclose((FILE *)arg);
}

void * write_into_file(void *arg)
{
	char file_name[64];
	char string_to_write[64];
	int len;
	int count = 0;

	int *thread_id = (int  *)arg;

  pthread_cleanup_push(memory_cleanup_handler, arg);

  /* Mark the thread eligible for cancellation */
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE /* PTHREAD_CANCEL_DISABLE */, 0);

	/* Mode of cancellation */
	pthread_setcanceltype( PTHREAD_CANCEL_ASYNCHRONOUS, 0);
  // if PTHREAD_CANCEL_DEFERRED, it defers until pthread_testcancel() called

	sprintf(file_name, "thread_%d.txt", *thread_id);

	FILE *fptr = fopen(file_name, "w");

	if(!fptr){
		printf("Error : Could not open log file %s, errno = %d\n", file_name, errno);
		return 0;
	}

  pthread_cleanup_push(file_cleanup_handler, fptr);

	while(!terminate_app) {
		len = sprintf(string_to_write, "%d : I am thread %d\n", count++, *thread_id);
		fwrite(string_to_write, sizeof(char), len, fptr);
		fflush(fptr);
		sleep(1);
    // pthread_testcancel(); // cancellation type should be: PTHREAD_CANCEL_DEFERRED
	}

  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);
	return 0;
}

void signalHandler(int _signal)
{
	if (_signal == SIGINT || _signal == SIGTERM)
	{
		terminate_app = true;
    for(int i = 0; i < N_SLAVES; i++)
      pthread_cancel(slaves[i]);
		printf("Application exited\n");
	}
}

int main(int argc, char **argv)
{
	int i;
	int *thread_id = 0;

	for( i = 0; i < N_SLAVES; i++){
	  thread_id = calloc(1, sizeof(*thread_id));
		*thread_id = i;
		pthread_create(&slaves[i], 0, write_into_file, thread_id);
	}

  // register signal to terminate the application gracefully
	signal(SIGINT, signalHandler);
  signal(SIGTERM, signalHandler);

	/* main menu */
	int choice;
	int thread_num;

	while(!terminate_app)
  {
		printf("1. Cancel the thread\n");
		scanf("%d", &choice);

    if(terminate_app) break;

    printf("Enter slave thread id [0-%d] :", N_SLAVES -1);
		scanf("%d", &thread_num);

    if(terminate_app) break;

    if(thread_num < 0 || thread_num >= N_SLAVES) {
			printf("Invalid Thread id\n");
      signalHandler(SIGTERM);
      break;
		}
		printf("\n");
		switch(choice) {
			case 1:
        pthread_cancel(slaves[thread_num]);
				break;
			default:
				continue;
		}
	}

  for( i = 0; i < N_SLAVES; i++)
  {
		pthread_join(slaves[i], NULL);
	}

  pthread_exit(0);
  // Instead of mutex and cond variable, use pause() and signal handler
	// Suspending execution ...
	// pause();

	return 0;
}