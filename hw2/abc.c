#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void loop(){
  while(1);
}

void *p1(){
	while(1){
		write(2,"A",1);
  		sched_yield();
	}
}

void *p2(){
	while(1){
		write(2,"B",1);
  		sched_yield();
	}
}

void *p3(){
	while(1){
		write(2,"C",1);
  		sched_yield();
	}
}

void main(){
  int pid1, pid2, pid3;
  pthread_t t1,t2, t3;
  void *thread_result;

  if (!(pid1 = fork())){
    loop();
  }

  if (!(pid2 = fork())){
    loop();
  }

  if (!(pid3 = fork())){
    loop();
  }

  pthread_create(&t1, NULL, p1, NULL);
  pthread_create(&t2, NULL, p2, NULL);
  pthread_create(&t3, NULL, p3, NULL);
  
  pthread_join(t1, &thread_result);
  pthread_join(t2, &thread_result);
  pthread_join(t3, &thread_result);

  int status;
  waitpid(pid1, &status, 0);
  waitpid(pid2, &status, 0);
  waitpid(pid3, &status, 0);
  printf("main exiting\n");
  exit(0);
}