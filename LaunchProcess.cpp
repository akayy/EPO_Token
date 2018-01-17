#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

BOOL isWow64();

int _tmain(int argc, TCHAR *argv[])
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	TCHAR path[500];

	if (isWow64())
		swprintf_s(path, 500, L"x64\\%s", argv[1]);
	else
		swprintf_s(path, 500, L"x32\\%s", argv[1]);

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	
	CreateProcess(
		NULL, // No Module Name, Use Command Line
		path,  // command line
		NULL, // Process Handle not inheritable
		NULL, // Thread Handle not inheritable
		FALSE, // Set handle inheritance to false
		0, // No creation flag
		NULL, // Use Parent's enviroment block
		NULL, // Use parent's starting Directory
		&si, // Pointer to Startupınfo structure
		&pi // pointer to process_information structure
	);

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	
	return 0;
	
}

BOOL isWow64()
{
	TCHAR lpBuffer[500];
	GetSystemWow64Directory(lpBuffer, sizeof(lpBuffer));
	if (lpBuffer) return TRUE;
	else return FALSE;
}