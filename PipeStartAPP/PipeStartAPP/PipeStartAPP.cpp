#include <iostream>
#include <string>
#include "stdafx.h"

int main()
{
	_TCHAR streamErr[100];
	_TCHAR streamIn0[100];
	_TCHAR streamOut0[100];
	_TCHAR streamIn1[100];
	_TCHAR streamOut1[100];

	HANDLE hWritePipe0, hReadPipe0;
	SECURITY_ATTRIBUTES saPipe0 = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };
	SECURITY_ATTRIBUTES saFileIn0 = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };
	HANDLE hFileIn0 = CreateFile(L"In0.txt", GENERIC_READ, 0,
		&saFileIn0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileIn0 == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Could not open file <%s> (error %d)\n", streamIn0, GetLastError());
		getchar();
		return 0;
	}

	SECURITY_ATTRIBUTES saFileErr = { sizeof(SECURITY_ATTRIBUTES),nullptr,TRUE };
	HANDLE hFileErr = CreateFile(L"Errors.txt", GENERIC_WRITE, 0,
		&saFileErr,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (hFileErr == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Could not open file <%s> (error %d)\n", streamErr, GetLastError());
		getchar();
		return 0;
	}

	SECURITY_ATTRIBUTES saFileOut0 = { sizeof(SECURITY_ATTRIBUTES),nullptr,TRUE };
	HANDLE hFileOut0 = CreateFile(L"Out0.txt", GENERIC_WRITE, 0,
		&saFileOut0,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileOut0 == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Could not open file <%s> (error %d)\n", streamOut0, GetLastError());
		getchar();
		return 0;
	}

	BOOL bPipe0 = CreatePipe(&hReadPipe0, &hWritePipe0, &saPipe0, 0);
	if (!bPipe0)
	{
		wprintf(L"Could not create Pipe (error %d)\n", GetLastError());
		getchar();
		return 0;
	}

	HANDLE hWritePipe1, hReadPipe1;
	SECURITY_ATTRIBUTES saPipe1 = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };
	SECURITY_ATTRIBUTES saFileIn1 = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };
	HANDLE hFileIn1 = CreateFile(L"In1.txt", GENERIC_READ, 0,
		&saFileIn1,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileIn1 == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Could not open file <%s> (error %d)\n", streamIn0, GetLastError());
		getchar();
		return 0;
	}

	SECURITY_ATTRIBUTES saFileOut1 = { sizeof(SECURITY_ATTRIBUTES),NULL,TRUE };
	HANDLE hFileOut1 = CreateFile(L"Out1.txt", GENERIC_WRITE, 0,
		&saFileOut1,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFileOut1 == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Could not open file <%s> (error %d)\n", streamOut0, GetLastError());
		getchar();
		return 0;
	}

	BOOL bPipe1 = CreatePipe(&hReadPipe1, &hWritePipe1, &saPipe1, 0);
	if (!bPipe1)
	{
		wprintf(L"Could not create Pipe (error %d)\n", GetLastError());
		getchar();
		return 0;
	}

	unsigned long long writeHandle0 = (unsigned long long)hWritePipe0;
	unsigned long long readHandle0 = (unsigned long long)hReadPipe1;
	unsigned long long writeHandle1 = (unsigned long long)hWritePipe1;
	unsigned long long readHandle1 = (unsigned long long)hReadPipe0;

	STARTUPINFO startupInfo = { sizeof startupInfo };
	PROCESS_INFORMATION processInformation = { 0 };

	std::wstring args0 = L"..\\..\\PProcA\\x64\\Debug\\PProcA.exe " + std::to_wstring(writeHandle0) + L" " + std::to_wstring(readHandle0);
	_TCHAR line0[512];
	wcscpy_s(line0, args0.c_str());

	BOOL bPr0 = CreateProcess(NULL,
		line0, NULL,
		NULL, TRUE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&startupInfo,
		&processInformation);
	if (!bPr0)
	{
		wprintf(L"Could not create process <%s>(error %d)\n", GetLastError());
		getchar();
		return 0;
	}

	std::wstring args1 = L"..\\..\\PProcA\\x64\\Debug\\PProcA.exe " + std::to_wstring(writeHandle1) + L" " + std::to_wstring(readHandle1);
	_TCHAR line[512];
	wcscpy_s(line, args1.c_str());
	BOOL bPr1 = CreateProcess(NULL,
		line, NULL,
		NULL, TRUE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&startupInfo,
		&processInformation);
	if (!bPr1)
	{
		wprintf(L"Could not create process <%s>(error %d)\n", GetLastError());
		getchar();
		return 0;
	}


	CloseHandle(hWritePipe1);
	CloseHandle(hReadPipe0);
	CloseHandle(hWritePipe0);
	CloseHandle(hReadPipe1);
	CloseHandle(hFileErr);
	return 0;
}