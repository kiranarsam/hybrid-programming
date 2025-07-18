#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void * thread_fn_callback(void *arg)
{
  int th_id = *(int *)arg;
  free(arg);

  int rc = 0;
  while(rc != th_id) {
    printf("Thread %d doing some work\n", th_id);
    sleep(1);
    rc++;
  }

  int *result = (int *)calloc(1, sizeof(int));
  *result = th_id * th_id;

  return (void *)result;
}

void thread_create(pthread_t *pthread_handle, int th_id)
{
  pthread_attr_t attr;

  int *_th_id = (int *)calloc(1, sizeof(int));
  *_th_id = th_id;

  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  int rc = pthread_create(pthread_handle, &attr, thread_fn_callback, (void *)_th_id);

  if( rc != 0) {
    printf("Unable to create thread, reason = %d\n", rc);
    exit(0);
  }
}


pthread_t pthread2;
pthread_t pthread3;

int main(int argc, char **argv)
{
  void *thread_result2;
  void *thread_result3;

  thread_create(&pthread2, 2); // change to 10  and understand the behavior
  thread_create(&pthread3, 10); // change to 2 and understand the behavior

  printf("Main fn blocked on pthread join for thread with th_id = 2\n");
  pthread_join(pthread2, &thread_result2);

  if(thread_result2) {
    printf("Return result from thread 2 = %d\n", *(int *)thread_result2);
    free(thread_result2);
    thread_result2 = NULL;
  }

  printf("Main fn blocked on pthread join for thread with th_id = 3\n");
  pthread_join(pthread3, &thread_result3);

  if(thread_result3) {
    printf("Return result from thread 3 = %d\n", *(int *)thread_result3);
    free(thread_result3);
    thread_result3 = NULL;
  }

  return 0;
}
