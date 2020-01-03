#include "control.h"

int main(int argc, char *argv[]) {
  if(strcmp(argv[1], "-c") == 0) {
    create_semaphore();
  }
  else if(strcmp(argv[1], "-r") == 0) {
    remove_semaphore();
  }
  else if(strcmp(argv[1], "-v") == 0) {
    view_story();
  }
  else{
    printf("Please enter a valid tag such as -c, -r, or -v\n");
  }
  return 0;
}

void create_semaphore() {
  int semd;
  int ctrl_get, ctrl_set;
  semd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  if(semd < 0) {
    semd = semget(KEY, 1, 0);
    ctrl_get = semctl(semd, 0, GETVAL, 0);
  }
  else{
    union semun s;
    s.val = 1;
    ctrl_set = semctl(semd, 0, SETVAL, s);
  }
  printf("Semaphore created\n");
  int shmd = shmget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  printf("Shared memory created\n");
  int fd = open("story.txt", O_CREAT | O_TRUNC, 0644);
  if (fd < 0) {
    printf("error %d: %s\n", errno, strerror(errno));
    return;
  }
  printf("File created\nSuccess!\n");
  close(fd);
}


void remove_semaphore() {
  view_story();
  int shmd = shmget(KEY, 1, 0);
  int semd = semget(KEY, 1, 0);
  shmctl(shmd, IPC_RMID, 0);
  printf("Shared memory removed\n");
  semctl(semd, IPC_RMID, 0);
  printf("Semaphore removed\n");
  int del = remove("story.txt");
  if (del < 0) {
    printf("error %d: %s\n", errno, strerror(errno));
    return;
  }
  printf("File removed\nSuccess!\n");
}

void view_story() {
  int fd = open("story.txt", O_RDONLY);
  if (fd < 0) {
    printf("error %d: %s", errno, strerror(errno));
    return;
  }
  char reader[1000];
  int r = read(fd, reader, 1000);
  if (r < 0) {
    printf("error %d: %s", errno, strerror(errno));
    return;
  }
  printf("The story so far:\n%s\n", reader);
  close(fd);
}
