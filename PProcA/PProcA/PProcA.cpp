#include <iostream>
#include <string>
#include <Windows.h>

#include <stdio.h>
#include <tchar.h>

void callMenu() {
    std::cout << "1 - Send message\n";
    std::cout << "2 - Recieve message\n";
    std::cout << "0 - Exit\n";
}

int main(int argc, char** args)
{
    HANDLE hPipeOut = (HANDLE)std::stoull(args[1]);
    HANDLE hPipeIn = (HANDLE)std::stoull(args[2]);
    HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
    int state = 1;
    while (state) {
        callMenu();
        std::cin >> state;
        if (state > 2 || state < 0) {
            std::cout << "Wrong state";
            return 1;
        }
        if (state == 1) {
            std::wstring input;
            std::wcin >> input;
            _TCHAR line[128];
            wcscpy_s(line, input.c_str());
            WriteFile(hPipeOut, line, input.size() * sizeof(_TCHAR), NULL, NULL);
        }
        if (state == 2) {
            DWORD bytesAvail = 0;
            if (!PeekNamedPipe(hPipeIn, NULL, 0, NULL, &bytesAvail, NULL)) {
                std::cout << "Failed to call PeekNamedPipe" << std::endl;
            }
            if (bytesAvail) {
                _TCHAR buf[512];
                DWORD n;
                BOOL success = ReadFile(hPipeIn, buf, bytesAvail * sizeof(_TCHAR), &n, NULL);
                if (!success || n == 0) {
                    std::cout << "Failed to call ReadFile" << std::endl;
                }
                std::wcout << std::wstring(buf, buf + n);
                std::cout << '\n';
            }
            else {
                std::cout << "Nothing to receive" << '\n';
            }
        }
    }
}
