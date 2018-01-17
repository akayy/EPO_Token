/*
* This 64bit compiled program is used to list informations 
* about the currently running processes in the system.
* Process id ( HexaDecimal ), 
* Process's module name (The exe program name),
* Process Version, Process Architecture,
* Processor core number are will be listed below.
*
*/

/*Necessary Libraries are included*/
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <psapi.h>

#ifdef _WIN64 // Provides not to run in 32bit compilation version
//  Function declaration:
void ListProcesses();

/*
* This Function does all the job of handling process informations 
* and printing using winapi.
* The Base function is "CreateToolhelp32Snapshot()" used in this program.
* It is slightly similer to "EnumProcesses()" winapi this may be also used.
*/
void ListProcesses()
{

	/*
	* Program Variables
	*/
	HANDLE hProcessSnap; //handle variable of CreateToolhelp32Snapshot 
	HANDLE hProcess; // Process Handle
	DWORD ProcessVersion; // Process Version variable. basically int type
	/*These are used to define if the process isWow64*/
	/*Determines whether the specified process is running under WOW64*/
	TCHAR *ProcArch = L""; 	BOOL Wow64; 
	/*Describes an entry from a list of the processes residing 
	in the system address space when a snapshot was taken.*/
	PROCESSENTRY32 pe32;
	/*Core number*/
	ULONG ProcessOnCore;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	// Set the size of the structure before using it.
	pe32.dwSize = sizeof(PROCESSENTRY32);
	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);           // clean the snapshot object
	}

	// Now walk the snapshot of processes, and
	// display information about each process in turn
	do
	{
		_tprintf(TEXT("\n\n====================================================="));
		_tprintf(TEXT("\n PROCESS NAME:  %s"), pe32.szExeFile);
		_tprintf(TEXT("\n-------------------------------------------------------"));
		/*Handled the process with all privileges from the first snapshot*/
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
		/*Got the version number*/
		ProcessVersion = GetProcessVersion(pe32.th32ProcessID);
		/*Processor Core number*/
		ProcessOnCore =	GetCurrentProcessorNumber();
		/* if The function is under WOW64 */
		IsWow64Process(hProcess, &Wow64);
	     /* Controlling block */
		switch (Wow64) {
		case true: ProcArch = L"WoW64"; break;
		case false: ProcArch = L"Native"; break;
		}
		/* Printing all the informations*/ 
		_tprintf(TEXT("\n  Process ID            =   0x%08X"), pe32.th32ProcessID);
		_tprintf(TEXT("\n  Process Version       =   %d.%d"), HIWORD(ProcessVersion), LOWORD(ProcessVersion) );
		_tprintf(TEXT("\n  Process Archtecture   =   %4s"), ProcArch);
		_tprintf(TEXT("\n  Process on Core       =   %d"), ProcessOnCore);

		CloseHandle(hProcess); // Closing the process handle
		/* process enumerating to handle next one*/
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
}


int main()
{
	ListProcesses();
	Sleep(10000);
	return 0;
}
#endif 

