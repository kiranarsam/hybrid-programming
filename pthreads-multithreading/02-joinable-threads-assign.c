#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void thread_create(pthread_t *pthread_handle, int th_id);

void * thread_fn_callback(void *arg)
{
  int th_id = *(int *)arg;
  free(arg);

  printf("%d\n", th_id);

  if(th_id < 1)
  {
    return (void *)1;
  }

  pthread_t thread;
  thread_create(&thread, th_id-1);
  pthread_join(thread, NULL);

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

int main(int argc, char **argv)
{
  void *thread_result2;
  int max = 5;

  thread_create(&pthread2, max);

  printf("Main fn blocked on pthread join for thread with th_id = 2\n");
  pthread_join(pthread2, NULL);

  return 0;
}
