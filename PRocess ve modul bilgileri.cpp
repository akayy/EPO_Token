#include <windows.h>
#include<stdio.h>
#include <tlhelp32.h>
#include <tchar.h>

int main()
{

	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	// Curret processlerin snapshotlarý'ný aldýk 
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32;



	//Snapchat'ler alýnamassa hatalý bir þekilde bitir
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return 1;

	pe32.dwSize = sizeof(PROCESSENTRY32);   // Processentry32 struct boyuntunu set ediyoruz

	printf("|   Id     |                Name                 |     Arc      |    Vers    |Oncore|Handle|MinWsz|MaxWsz| \n");

	Process32First(hProcessSnap, &pe32); //Process32First ile ilk snapshot'tan baþladýk. hProcessSnapten ilkini pe32ye attýk

	do
	{

		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION,     //Belirtilen process'in handle deðerini açýyoruz.Open(Eriþim hakký bilgisi , inherit , processId )
			0,
			pe32.th32ProcessID);

		DWORD pVersion;
		DWORD pOnCore;
		BOOL Wow64;
		TCHAR *ProcArch = L"---";

		pVersion = GetProcessVersion(pe32.th32ProcessID);
		pOnCore = GetCurrentProcessorNumber();
		IsWow64Process(hProcess, &Wow64);

		switch (Wow64) {
		case true: ProcArch = L"WoW64"; break;
		case false: ProcArch = L"Native"; break;
		}
		SIZE_T minWorkSize, maxWorkSize;

		if (GetProcessWorkingSetSize(hProcess, &minWorkSize, &maxWorkSize)) {

		}
		printf("|----------|-------------------------------------|--------------|------------|-----|-----|------|-------| \n");
		printf("| %5u    |%35lS  | %6S       | %3d.%d      |%5d|%5d|%5lu|%5lu|\n", pe32.th32ProcessID,
			pe32.szExeFile,
			ProcArch,
			HIWORD(pVersion),
			LOWORD(pVersion),
			pOnCore,
			hProcess,
			minWorkSize / 1024,  //KB cinsinden
			maxWorkSize / 1024
			);
		//-----------
		hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pe32.th32ProcessID);
		if (hModuleSnap != INVALID_HANDLE_VALUE)
		{


			me32.dwSize = sizeof(MODULEENTRY32);
			if (Module32First(hModuleSnap, &me32))
			{
				Module32Next(hModuleSnap, &me32);
				do
				{
					printf("\n\n Module Name:%S \t Handle Value:%u", me32.szModule, me32.hModule);


				} while (Module32Next(hModuleSnap, &me32));
				printf("\n");
			}
			CloseHandle(hModuleSnap);
		}
		//------------------------
		CloseHandle(hProcess);
	} while (Process32Next(hProcessSnap, &pe32));  //Sýradaki processi' bilgilerinin almak için snaptshot'unu aldýk

	CloseHandle(hProcessSnap);

	return 0;
}
