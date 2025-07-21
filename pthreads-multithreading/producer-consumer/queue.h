#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 5

typedef struct Queue_
{
  void *data[MAX_QUEUE_SIZE];
  unsigned int front;
  unsigned int rear;
  unsigned int count;
  pthread_mutex_t mutex;
  pthread_cond_t cond_var;
} Queue;

Queue* createQueue()
{
  Queue *que = (Queue *)calloc(1, sizeof(Queue));
  que->front = 0;
  que->rear = 0;
  que->count = 0;
  pthread_mutex_init(&que->mutex, NULL);
  pthread_cond_init(&que->cond_var, NULL);

  return que;
}

bool isQueueEmpty(Queue *que)
{
  if(que->count == 0)
    return true;
  return false;
}

bool isQueueFull(Queue *que)
{
  if(que->count == MAX_QUEUE_SIZE)
    return true;
  return false;
}

bool enqueue(Queue *que, void *ptr)
{
  if(!que || !ptr) return false;

  if(isQueueFull(que)) {
    printf("Queue is full\n");
    return false;
  }

  if(isQueueEmpty(que))
  {
    que->data[que->rear] = ptr;
    que->count++;
    return true;
  }

  if(que->rear == MAX_QUEUE_SIZE -1) {
    que->rear = 0;
  }
  else {
    que->rear++;
  }

  que->data[que->rear] = ptr;
  que->count++;
  return true;
}

void *dequeue(Queue *que)
{
  void *data = NULL;
  if(!que) return NULL;

  if(isQueueEmpty(que)) {
    return NULL;
  }

  data = que->data[que->front];
  que->data[que->front] = NULL;
  que->count--;

  if(que->front == que->rear) {
    que->front = que->rear = que->count = 0;
  }
  else if(que->front == MAX_QUEUE_SIZE - 1) {
    que->front = 0;
  }
  else {
    que->front++;
  }

  return data;
}

void printQueue(Queue *que)
{
  if(!que) return;
  printf("que->front: %d, que->rear: %d, que->count: %d\n",
    que->front, que->rear, que->count);
  int idx = 0;
  for(idx = 0; idx < MAX_QUEUE_SIZE; idx++) {
    if(!que->data[idx]) {
      continue;
    }
    printf("Index: %d, Data: %p\n", idx, que->data[idx]);
  }
}

#define QUEUE_COUNT(que) ((que)->count)

#endif