#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
  int pid, ppid, status;
  pid = getpid();
  ppid = getppid();

  printf("FATHER PARAM: pid=%i ppid=%i\n", pid, ppid);

  if (fork() == 0)
  {
    execl("./son_2a_2", "son", NULL);
    perror("execl failed");
    exit(1);
  }
}
