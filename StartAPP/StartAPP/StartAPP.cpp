#include <iostream>
#include <Windows.h>

void main()
{
    SetEnvironmentVariable(L"TURN", L"0");
    SetEnvironmentVariable(L"BUFFER", L"1");
    STARTUPINFO startupinfo = { sizeof startupinfo };
    PROCESS_INFORMATION processInformation = { 0 };
    CreateProcess(L"..\\..\\LVProcB\\x64\\Debug\\LVProcB.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupinfo, &processInformation);
    CreateProcess(L"..\\..\\LVProcA\\x64\\Debug\\LVProcA.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupinfo, &processInformation);
}
