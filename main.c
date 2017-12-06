#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY 24602

int main(int argc, char *argv[]) {
  int len;
  for (len = 0; argv[len]; len++) {
    //printf("%s\n", argv[len]);
  }

  if (len < 2)
    return 0;
  
  char *first_arg = argv[1];
  if (strcmp(first_arg, "-v") == 0) {
    int sd = semget(KEY, 1, 0644);
    if (sd == -1) {
      printf("Semaphore not created\n");
      return 0;
    }
    printf("%d\n", semctl(sd, 0, GETVAL));
    return 0;
  } else if (strcmp(first_arg, "-r") == 0) {
    int sd = semget(KEY, 1, 0644);
    if (semctl(sd, 0, IPC_RMID) == -1)
      printf("Error removing semaphore\n");
    return 0;
  }
  
  if (len < 3)
    return 0;

  if (strcmp(first_arg, "-c") == 0) {
    int sd = semget(KEY, 1, IPC_CREAT | 0644);
    int val = (int) strtol(argv[2], NULL, 10);
    semctl(sd, 0, SETVAL, val);
  }
  //int sd = semget(KEY, 1, IPC_CREAT | 0644);
  //semctl(sd, 0, SETVAL, 4);
  //semctl(sd, 0, GETVAL);
  //semctl(sd, 0, IPC_RMID);

  return 0;
}
