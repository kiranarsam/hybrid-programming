#include <pthread.h>
#include "queue.h"

Queue *Q;

static const char *prod1 = "TP1";
// static const char *prod2 = "TP2";
static const char *cons1 = "TC1";
// static const char *cons2 = "TC2";

static int getInteger()
{
  static int value = 0;
  value++;
  return value;
}

static void *prod_fn(void *arg)
{
  char *thread_name = (char *)arg;
  int count = 0;

  while(count < 10) {
    pthread_mutex_lock(&Q->mutex);

    if(isQueueFull(Q)) {
      pthread_cond_wait(&Q->cond_var, &Q->mutex);
    }

    if(!isQueueFull(Q)) {
      int value = getInteger();
      enqueue(Q, (void *)value);
    }

    pthread_cond_signal(&Q->cond_var);

    pthread_mutex_unlock(&Q->mutex);
    count++;
    sleep(1);
  }

  return NULL;
}

static void *cons_fn(void *arg)
{
  char *thread_name = (char *)arg;
  int count = 0;
  while(count < 10) {
    pthread_mutex_lock(&Q->mutex);

    if(isQueueEmpty(Q)) {
      pthread_cond_wait(&Q->cond_var, &Q->mutex);
    }

    if(!isQueueEmpty(Q)) {
      int value = (int)dequeue(Q);
      printf("Thread: %s, Consumer dequeued: %d\n", thread_name, value);
    }

    pthread_cond_signal(&Q->cond_var);

    pthread_mutex_unlock(&Q->mutex);
    count++;
  }

  return NULL;
}

int main(int argc, char **argv)
{
  Q = createQueue();
  pthread_attr_t attr;

  pthread_attr_init(&attr);

  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  pthread_t prod_t1;
  pthread_t cons_t1;

  pthread_create(&prod_t1, &attr, prod_fn, (void *)prod1);
  pthread_create(&cons_t1, &attr, cons_fn, (void *)cons1);

  pthread_join(prod_t1, NULL);
  pthread_join(cons_t1, NULL);

  if(Q) {
    free(Q);
  }

  printf("Main thread finished\n");
  pthread_exit(0);

  return 0;
}