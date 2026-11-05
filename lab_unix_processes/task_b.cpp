#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void * produce(void * arg);

void * produce(void * arg)
{
  pthread_t tid;
  size_t count = 0;
  while (true)
  {
    printf("Hello I am Thread %d, ", *(int *)arg);
    tid = pthread_self();
    printf("Inside tid=%ld, ", tid);
    count++;
    printf("Count=%ld\n", count);
    sleep(5);
  }
}

int main()
{
  const int MAXTHREADS = 2;
  int count[MAXTHREADS];
  pthread_t tid_produce[MAXTHREADS];
  for (size_t i = 0; i < MAXTHREADS; i++)
  {
    count[i] = i;
    if (!pthread_create(&tid_produce[i], NULL, produce, &count[i]))
    {
      printf("tid %ld\n", tid_produce[i]);
    }
    else
    {
      printf("Can not create pthread!\n");
    }
  }

  for (size_t i = 0; i < MAXTHREADS; i++)
  {
    pthread_join(tid_produce[i], NULL);
    printf("count[%zu]=%d\n", i, count[i]);
  }
}
