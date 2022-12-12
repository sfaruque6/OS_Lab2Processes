#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>


int  main(void) {
  int num_child = 2;
  int  pid[num_child];
  int max_loop = 30;
  int max_sleep_time = 10;
  int i, j;

  for (i=0; i<num_child; i++) {
    pid[i] = fork();
    if (pid[i] < 0) {
      printf("Fail!\n");
    } else if (pid[i] == 0) {
      int cpid = getpid();
      int ppid = getppid();
      srand(cpid);
      int rand_loop = 1 + rand() % max_loop;
      for (j=0; j<rand_loop; j++) {
        int rand_time = 1 + rand() % max_sleep_time;
        printf("child <%d> will sleep\n", cpid);
        sleep(rand_time);
        printf("child <%d> has rose\n  -> where is my parent [%d]?\n", cpid, ppid);
      }
      exit(0);
    }
  }
  for (i=0; i < num_child; i++) {
    int status;
    int cpid = wait(&status);
  }
  return 0;
}