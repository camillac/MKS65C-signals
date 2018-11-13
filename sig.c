#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>


static void sighandler(int signo){
  if (signo == SIGINT){
    printf("KILL ME\n");
    char * errmsg = "EXITED B/C SIGINT\n";
    int file = open("sigint.txt", O_CREAT | O_WRONLY | O_APPEND);
    write(file, errmsg, sizeof(char) * 19);
    close(file);
    exit(0);
  }
  if (signo == SIGUSR1){
    printf("parent pid: %d\n", getppid());
  }
}

int main(){
  signal(SIGUSR1, sighandler);
  signal(SIGINT, sighandler);

  while (1){
    printf("pid: %d\n", getpid());
    sleep(1);
  }
}
