#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void loop(){
  while(1);
}

void *p1(){
  printf("thread-1 starting\n");
  loop();
}

void *p2(){
  printf("thread-2 starting\n");
  loop();
}

void main(){
  int pid1, pid2;
  pthread_t t1,t2;
  void *thread_result;

  printf("main starting\n");

  if (!(pid1 = fork())){
    printf("child-1 starting\n");
    loop();
    exit(0);
  }

  if (!(pid2 = fork())){
    printf("child-2 starting\n");
    loop();
    exit(0);
  }

  pthread_create(&t1, NULL, p1, NULL);
  pthread_create(&t2, NULL, p2, NULL);
  
  pthread_join(t1, &thread_result);
  pthread_join(t2, &thread_result);

  int status;
  waitpid(pid1, &status, 0);
  waitpid(pid2, &status, 0);
  printf("main exiting\n");
  exit(0);
}
