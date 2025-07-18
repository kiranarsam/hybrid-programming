#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static void * thread_fn_callback(void *arg)
{
  char *input = (char *)arg;
  while(1) {
    printf("From Thread: %s\n", input);
    sleep(1);
  }
}

void thread_create()
{
  pthread_t pthread;

  static char* thread_input = "Thread nummber 1";

  int rc = pthread_create(&pthread,
                          NULL,
                          thread_fn_callback,
                          (void *)thread_input);
  if(rc != 0) {
    printf("Unable to create a thread, reason = %d\n", rc);
    exit(0);
  }
}

int main(int argc, char **argv)
{

  thread_create();
  printf("Main thread paused\n");
  pause();
  return 0;
}