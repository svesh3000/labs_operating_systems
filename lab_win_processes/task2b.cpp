#include <cstdlib>
#include <stdio.h>
#include <vector>
#include <windows.h>

bool runFlag = true;

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
  int param = *(int *)lpParameter;

  printf("I am ThreadProc=%d Hello!\n", param);
  while (runFlag)
  {
    printf("ThreadProc=%d in while!\n", param);
    Sleep(1000);
  }

  printf("ThreadProc=%d finished.\n", param);
  return 0;
}

int main(int argc, char * argv[])
{
  if (argc < 3)
  {
    printf("Usage: %s <n_threads> <time_to_live>\n", argv[0]);
    return 1;
  }
  int n_threads = std::atoi(argv[1]);
  int time_to_live = std::atoi(argv[2]);

  std::vector< HANDLE > mHandle(n_threads);
  std::vector< DWORD > mArg(n_threads);
  std::vector< DWORD > mId(n_threads);

  printf("I am main! Hello!\n");
  for (int i = 0; i < n_threads; i++)
  {
    mArg[i] = i + 1;
    mHandle[i] = CreateThread(NULL, 0, ThreadProc, &mArg[i], 0, &mId[i]);
    CloseHandle(mHandle[i]);
  }

  DWORD startTime = GetTickCount();
  while (GetTickCount() - startTime < time_to_live * 1000)
  {
    Sleep(1000);
  }
  runFlag = false;
  Sleep(5000);
  return 0;
}
