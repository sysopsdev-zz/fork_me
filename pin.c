#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
 
int get_pin() {
  srand(getpid() + getppid());
  int secret = 1000 + rand() % 9000;
  return secret;
}
 
int main(void) {
  int fd[2];
  pipe(fd);
  pid_t pid = fork();
 
  if(pid > 0) {
    close(0);
    close(fd[1]);
    dup(fd[0]);
 
    int secret_number;
    size_t read_bytes = read(fd[0], &secret_number, sizeof(secret_number));
 
    printf("Waiting for PIN...\n");
    wait(NULL);
    printf("Bytes read: %ld\n", read_bytes);
    printf("PIN: %d\n", secret_number);
  }
  else if(pid == 0) {
    close(1);
    close(fd[0]);
    dup(fd[1]);
 
    int secret = get_pin();
    write(fd[1], &secret, sizeof(secret));
    exit(0);
  }
 
  return 0;
}
