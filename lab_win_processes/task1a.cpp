#include <iostream>
#include <windows.h>

int main()
{
  wchar_t lpCommandLine[] = L"C:\\WINDOWS\\SYSTEM32\\NOTEPAD.EXE temp.txt";

  STARTUPINFOW si{};
  PROCESS_INFORMATION pi{};
  si.cb = sizeof(si);

  DWORD creationFlags = NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE;
  if (!CreateProcessW(NULL, lpCommandLine, NULL, NULL, FALSE, creationFlags, NULL, NULL, &si, &pi))
  {
    std::cerr << "CreateProcess failed on error " << GetLastError() << "\n";
    return 1;
  }

  std::cout << "ProcessHandle=" << pi.hProcess << "\n";
  std::cout << "ThreadHandle=" << pi.hThread << "\n";

  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
}
