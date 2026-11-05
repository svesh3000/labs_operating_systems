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
    CloseHandle(mHandle[i]);
  }

  while (true)
  {
    printf("Main in while!\n");
    Sleep(1000);
  }
  return 0;
}
