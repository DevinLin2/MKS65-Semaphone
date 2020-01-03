#include "control.h"

int main(){
  struct sembuf s;
  s.sem_num = 0;
  s.sem_op = 0;
  int semd = semget(KEY, 1, 0);
  int shmd = shmget(KEY, 1, 0);
  int fd = open("story.txt", O_WRONLY | O_APPEND);
  char *prev = shmat(shmd, 0, 0);
  printf("Your last addition: %s\n", prev);
  char user_input[1000];
  printf("Your next addition: ");
  fgets(user_input, 1000, stdin);
  write(fd, user_input, strlen(user_input));
  close(fd);
  strcpy(prev, user_input);
  s.sem_op = 1;
  shmdt(prev);
  semop(semd, &s, 1);
  return 0;
}
