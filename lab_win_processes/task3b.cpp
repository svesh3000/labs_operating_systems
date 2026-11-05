#include <iostream>
#include <limits>
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

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void changePriorityProcess()
{
  HANDLE hProcess = GetCurrentProcess();
  DWORD procPriority = GetPriorityClass(hProcess);
  printf("Current Process Priority Class: 0x%X\n", procPriority);

  printf("Input priority >> ");
  int priority;
  if (!(std::cin >> priority)) {
    printf("Error: invalid number!\n");
    clearInput();
    return;
  }
  SetPriorityClass(hProcess, priority);
  printf("Current Process Priority Class: 0x%X\n", GetPriorityClass(hProcess));
}

void changePriorityThread(HANDLE *mHandle)
{
  printf("For which Thread: 0 or 1 (input number) >> ");
  int num;
  if (!(std::cin >> num)) {
    printf("Error: invalid number!\n");
    clearInput();
    return;
  }

  if (num < 0 || num > 1) {
      printf("Error: thread must be 0 or 1!\n");
      return;
  }

  int tPriority = GetThreadPriority(mHandle[num]);
  printf("Thread Priority: %d\n", tPriority);

  printf("Input priority >> ");
  int priority;
  if (!(std::cin >> priority)) {
    printf("Error: invalid number!\n");
    clearInput();
    return;
  }

  SetThreadPriority(mHandle[num], priority);
  printf("Thread Priority: %d\n", GetThreadPriority(mHandle[num]));
}

void changeProcessPriorityBoost()
{
  HANDLE hProcess = GetCurrentProcess();
  BOOL boostState;
  GetProcessPriorityBoost(hProcess, &boostState);
  printf("Process Boost is: %d\n", boostState);

  printf("Input 1 to activate or 0 to disable >> ");
  bool flag = true;
  if (!(std::cin >> flag)) {
    printf("Error: invalid number!\n");
    clearInput();
    return;
  }
  SetProcessPriorityBoost(hProcess, flag);
  GetProcessPriorityBoost(hProcess, &boostState);
  printf("Process Boost is: %d\n", boostState);
}

void changeThreadPriorityBoost(HANDLE *mHandle)
{
  printf("For which Thread: 0 or 1 (input number) >> ");
  int num;
  if (!(std::cin >> num)) {
    printf("Error: invalid number!\n");
    clearInput();
    return;
  }

  if (num < 0 || num > 1) {
      printf("Error: thread must be 0 or 1!\n");
      return;
  }

  BOOL boostState;
  GetThreadPriorityBoost(mHandle[num], &boostState);
  printf("Thread Boost is: %d\n", boostState);

  printf("Input 1 to activate or 0 to disable >> ");
  bool flag = true;
  if (!(std::cin >> flag)) {
    printf("Error: invalid number!\n");
    clearInput();
    return;
  }
  SetThreadPriorityBoost(mHandle[num], flag);
  GetThreadPriorityBoost(mHandle[num], &boostState);
  printf("Thread Boost is: %d\n", boostState);
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

  SuspendThread(mHandle[0]);
  SuspendThread(mHandle[1]);
  printf("1. Process Priority\n");
  printf("2. Thread Priority\n");
  printf("3. Process Priority Boost\n");
  printf("4. Thread Priority Boost\n");
  printf("What to change? Print 1, 2, 3, 4 or eof to break\n");
  printf(">> ");
  int num = 0;
  while (std::cin >> num)
  {
    switch (num) {
      case 1: changePriorityProcess(); break;
      case 2: changePriorityThread(mHandle); break;
      case 3: changeProcessPriorityBoost(); break;
      case 4: changeThreadPriorityBoost(mHandle); break;
      default: continue;
    }
    printf(">> ");
  }
  ResumeThread(mHandle[0]);
  ResumeThread(mHandle[1]);

  Sleep(10000);

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
