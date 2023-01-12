#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <windef.h>
#include <handleapi.h>
#include <TlHelp32.h>
#include <vector>

#define ID 1;

void callMenu() {
    std::cout << "1 - Send message\n";
    std::cout << "2 - Recieve message\n";
    std::cout << "0 - Exit\n";
}

void endProcByName(std::string str) {
    std::vector<DWORD> pids;
    std::wstring targetProcessName(str.begin(), str.end());
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //all processes
    PROCESSENTRY32W entry; //current process
    entry.dwSize = sizeof entry;

    if (!Process32FirstW(snap, &entry)) { //start with the first in snapshot
        return;
    }

    do {
        if (std::wstring(entry.szExeFile) == targetProcessName) {
            pids.emplace_back(entry.th32ProcessID); //name matches; add to list
        }
    } while (Process32NextW(snap, &entry)); //keep going until end of snapshot

    for (int i(0); i < pids.size(); ++i) {
        HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pids[i]);
        TerminateProcess(processHandle, 1);
        CloseHandle(processHandle);
    }
}

int main()
{
    STARTUPINFO startupinfo = { sizeof startupinfo };
    PROCESS_INFORMATION processInformation = { 0 };
    int state = 1;
    while (state) {
        callMenu();
        std::cin >> state;
        if (state > 2 || state < 0) {
            std::cout << "Wrong state";
            return 1;
        }
        if (state == 1) {
            int num;
            std::cin >> num;
            wchar_t istr[32];
            _itow_s(1, istr, 10);
            SetEnvironmentVariable(L"TURN", istr);
            _itow_s(num, istr, 10);
            SetEnvironmentVariable(L"BUFFER", istr);
            endProcByName("LVProcA.exe");
            CreateProcess(L"..\\..\\LVProcA\\x64\\Debug\\LVProcA.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupinfo, &processInformation);
        }
        if (state == 2) {
            wchar_t wcstr[32];
            GetEnvironmentVariable(L"TURN", wcstr, sizeof(wcstr));
            wchar_t istr[32];
            _itow_s(2, istr, 10);
            if (wcscmp(wcstr, istr) == 0) {
                GetEnvironmentVariable(L"TURN", wcstr, sizeof(wcstr));
                std::cout << wcstr << "\n";
            }
            else {
                std::cout << "Nothing to recieve\n";
            }
        }
    }
}
