#include <stdio.h>
#include <windows.h>

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
  int param = *(int *)lpParameter;

  printf("I am ThreadProc=%d Hello!\n", param);
  while (TRUE)
  {
    printf("ThreadProc=%d in while!\n", param);
    Sleep(1000);
  }
}

int main()
{
  HANDLE mHandle[2];
  DWORD mArg[2], mId[2];

  printf("I am main! Hello!\n");
  for (int i = 0; i < 2; i++)
  {
    mArg[i] = i;
    mHandle[i] = CreateThread(NULL, 0, ThreadProc, mArg + i, 0, mId + i);
  }

  HANDLE hProcess = GetCurrentProcess();
  DWORD procPriority = GetPriorityClass(hProcess);
  printf("Current Process Priority Class: 0x%X\n", procPriority);
  SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);
  printf("Current Process Priority Class: 0x%X\n", GetPriorityClass(hProcess));

  int tPriority0 = GetThreadPriority(mHandle[0]);
  printf("Thread 0 Priority: %d\n", tPriority0);
  int tPriority1 = GetThreadPriority(mHandle[1]);
  printf("Thread 1 Priority: %d\n", tPriority1);
  SetThreadPriority(mHandle[0], THREAD_PRIORITY_LOWEST);
  SetThreadPriority(mHandle[1], THREAD_PRIORITY_HIGHEST);
  printf("Thread 0 Priority: %d\n", GetThreadPriority(mHandle[0]));
  printf("Thread 1 Priority: %d\n", GetThreadPriority(mHandle[1]));

  BOOL boostState;
  GetProcessPriorityBoost(hProcess, &boostState);
  printf("Process Boost is: %d\n", boostState);
  SetProcessPriorityBoost(hProcess, TRUE);
  GetProcessPriorityBoost(hProcess, &boostState);
  printf("Process Boost is: %d\n", boostState);

  GetThreadPriorityBoost(mHandle[0], &boostState);
  printf("Thread 0 Boost is: %d\n", boostState);
  SetThreadPriorityBoost(mHandle[0], FALSE);
  GetThreadPriorityBoost(mHandle[0], &boostState);
  printf("Thread 0 Boost is: %d\n", boostState);

  printf("SUSPEND Thread 1 for 5 seconds...\n");
  SuspendThread(mHandle[1]);
  Sleep(5000);
  printf("RESUME Thread 1...\n");
  ResumeThread(mHandle[1]);

  Sleep(10000);
  CloseHandle(mHandle[0]);
  CloseHandle(mHandle[1]);
  // ExitProcess(0);
  TerminateProcess(GetCurrentProcess(), 0);
}
