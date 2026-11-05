#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <winscard.h>

int main()
{
  std::string file_path;
  std::cout << "Input file name: ";
  std::getline(std::cin, file_path);
  std::cout << "\n";

  std::wifstream config_file(file_path);
  if (!config_file.is_open())
  {
    std::cerr << "ERROR: can not open config file\n";
    return 1;
  }

  std::vector< std::wstring > paths;
  std::wstring line;
  while (std::getline(config_file, line))
  {
    if (!line.empty())
    {
      paths.push_back(line);
    }
  }

  for (size_t i = 0; i < paths.size(); i++)
  {
    STARTUPINFOW si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);

    DWORD creationFlags = NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE;
    if (!CreateProcessW(NULL, &paths[i][0], NULL, NULL, FALSE, creationFlags, NULL, NULL, &si, &pi))
    {
      std::cerr << "CreateProcess failed on error " << GetLastError() << "\n";
      return 1;
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
  }
}
