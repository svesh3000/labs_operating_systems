#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
  int pid, ppid;
  pid = getpid();
  ppid = getppid();
  printf("SON PARAM: pid=%i ppid=%i \n", pid, ppid);

  system("ps -ef > file_2a");
  sleep(5);
}
