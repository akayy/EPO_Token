// delele.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "delele.h"
#include <VersionHelpers.h>
#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <psapi.h>
#include <PowrProf.h>
#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")


namespace pwr
{

	BOOL pwrControl::PWR(char *param)
	{
		return 0;
	}

	BOOL pwrControl::Logoff()
	{
		return ExitWindowsEx(EWX_LOGOFF, 0);
	}

	BOOL pwrControl::Lock()
	{
		return LockWorkStation();
	}

	BOOL pwrControl::Shutdown() //LPTSTR is either char* or wchar_t depending on compiler
	{
		sys::sysInfo::getToken();
		if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,
			SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
			SHTDN_REASON_MINOR_UPGRADE |
			SHTDN_REASON_FLAG_PLANNED))
			return FALSE;

		//shutdown was successful
		return TRUE;
	}

	BOOL pwrControl::Poweroff() //LPTSTR is either char* or wchar_t depending on compiler
	{
		sys::sysInfo::getToken();
		if (!ExitWindowsEx(EWX_POWEROFF | EWX_FORCE,
			SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
			SHTDN_REASON_MINOR_UPGRADE |
			SHTDN_REASON_FLAG_PLANNED))
			return FALSE;
		//PowerOff was successful
		return TRUE;
	}
	BOOL pwrControl::Reboot() //LPTSTR is either char* or wchar_t depending on compiler
	{
		sys::sysInfo::getToken();
		if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE,
			SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
			SHTDN_REASON_MINOR_UPGRADE |
			SHTDN_REASON_FLAG_PLANNED))
			return FALSE;
		//PowerOff was successful
		return TRUE;
	}
	int pwrControl::Suspend()
	{
		return SetSuspendState(TRUE, NULL, FALSE);
	}

	char *pwrControl::str(char *c)
	{
		return c;
	}

}

namespace sys
{

	void sysInfo::odev1()
	{

		TCHAR *str = TEXT("Computer Name: " , sysInfo::getComputerName(0));
		MessageBox(NULL, _T("Open the message box "), _T("message"), MB_OK | MB_SYSTEMMODAL);
	}
#pragma comment(lib, "user32.lib")
#define INFO_BUFFER_SIZE 32767
	TCHAR  infoBuf[INFO_BUFFER_SIZE];
	DWORD  bufCharCount = INFO_BUFFER_SIZE;

	TCHAR *sysInfo::getPCName()
	{
		// Get and display the name of the computer. 
		GetComputerName(infoBuf, &bufCharCount);
		_tprintf(TEXT("\Computer name:      %s"), infoBuf);
		return infoBuf;
	}

	TCHAR *sysInfo::getUsrName()
	{
		// Get and display the user name. 
		GetUserName(infoBuf, &bufCharCount);
		_tprintf(TEXT("\nUser name:      %s"), infoBuf);
		return infoBuf;
	}

	TCHAR *sysInfo::getComputerName(int param)
	{

		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		CreateProcess(
			L"C:/windows/System32/wbem/wmic.exe", // No Module Name, Use Command Line
			L"wmic os get installdate",  // command line
			NULL, // Process Handle not inheritable
			NULL, // Thread Handle not inheritable
			FALSE, // Set handle inheritance to false
			0, // No creation flag
			NULL, // Use Parent's enviroment block
			NULL, // Use parent's starting Directory
			&si, // Pointer to Startupınfo structure
			&pi // pointer to process_information structure
		);
		return TEXT("hh");
	}

	TCHAR *sysInfo::getSystemDirectory()
	{
		GetSystemDirectory(infoBuf, INFO_BUFFER_SIZE);
		_tprintf(TEXT("\nSystem Directory:      %s"), infoBuf);
		return infoBuf;
	}

	TCHAR *sysInfo::getWindowsDirectory()
	{
		GetWindowsDirectory(infoBuf, INFO_BUFFER_SIZE);
		_tprintf(TEXT("\Windows Directory:      %s"), infoBuf);
		return infoBuf;
	}

	bool sysInfo::setComputerName(int NameType, LPCTSTR lpBuffer)
	{
		SetComputerNameEx(
			COMPUTER_NAME_FORMAT(NameType),
			lpBuffer
		);
		return FALSE;
	}

	const char *sysInfo::getSystemVersion()
	{
		const char *x = "xx";

		if (IsWindowsXPOrGreater())
		{
			x = "XPOrGreater\n";
		}

		if (IsWindowsXPSP1OrGreater())
		{
			x = "XPSP1OrGreater\n";
		}

		if (IsWindowsXPSP2OrGreater())
		{
			x = "XPSP2OrGreater\n";
		}

		if (IsWindowsXPSP3OrGreater())
		{
			x = "XPSP3OrGreater\n";
		}

		if (IsWindowsVistaOrGreater())
		{
			x = "VistaOrGreater\n";
		}

		if (IsWindowsVistaSP1OrGreater())
		{
			x = "VistaSP1OrGreater\n";
		}

		if (IsWindowsVistaSP2OrGreater())
		{
			x = "VistaSP2OrGreater\n";
		}

		if (IsWindows7OrGreater())
		{
			x = "Windows7OrGreater\n";
		}

		if (IsWindows7SP1OrGreater())
		{
			x = "Windows7SP1OrGreater\n";
		}

		if (IsWindows8OrGreater())
		{
			x = "Windows8OrGreater\n";
		}

		if (IsWindows8Point1OrGreater())
		{
			x = "Windows8Point1OrGreater\n";
		}

		printf("System Version : %s", x);

		return x;
	}

	void sysInfo::getSystemInstallDate()
	{
	}

	int sysInfo::get32Process()
	{
		using namespace std;
		HRESULT hres;

		// Initialize COM.
		hres = CoInitializeEx(0, COINIT_MULTITHREADED);
		if (FAILED(hres))
		{
			cout << "Failed to initialize COM library. "
				<< "Error code = 0x"
				<< hex << hres << endl;
			return 1;              // Program has failed.
		}

		// Initialize 
		hres = CoInitializeSecurity(
			NULL,
			-1,      // COM negotiates service                  
			NULL,    // Authentication services
			NULL,    // Reserved
			RPC_C_AUTHN_LEVEL_DEFAULT,    // authentication
			RPC_C_IMP_LEVEL_IMPERSONATE,  // Impersonation
			NULL,             // Authentication info 
			EOAC_NONE,        // Additional capabilities
			NULL              // Reserved
		);


		if (FAILED(hres))
		{
			cout << "Failed to initialize security. "
				<< "Error code = 0x"
				<< hex << hres << endl;
			CoUninitialize();
			return 1;          // Program has failed.
		}

		// Obtain the initial locator to Windows Management
		// on a particular host computer.
		IWbemLocator *pLoc = 0;

		hres = CoCreateInstance(
			CLSID_WbemLocator,
			0,
			CLSCTX_INPROC_SERVER,
			IID_IWbemLocator, (LPVOID *)&pLoc);

		if (FAILED(hres))
		{
			cout << "Failed to create IWbemLocator object. "
				<< "Error code = 0x"
				<< hex << hres << endl;
			CoUninitialize();
			return 1;       // Program has failed.
		}

		IWbemServices *pSvc = 0;

		// Connect to the root\cimv2 namespace with the
		// current user and obtain pointer pSvc
		// to make IWbemServices calls.

		hres = pLoc->ConnectServer(

			_bstr_t(L"ROOT\\CIMV2"), // WMI namespace
			NULL,                    // User name
			NULL,                    // User password
			0,                       // Locale
			NULL,                    // Security flags                 
			0,                       // Authority       
			0,                       // Context object
			&pSvc                    // IWbemServices proxy
		);

		if (FAILED(hres))
		{
			cout << "Could not connect. Error code = 0x"
				<< hex << hres << endl;
			pLoc->Release();
			CoUninitialize();
			return 1;                // Program has failed.
		}

		cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;

		// Set the IWbemServices proxy so that impersonation
		// of the user (client) occurs.
		hres = CoSetProxyBlanket(

			pSvc,                         // the proxy to set
			RPC_C_AUTHN_WINNT,            // authentication service
			RPC_C_AUTHZ_NONE,             // authorization service
			NULL,                         // Server principal name
			RPC_C_AUTHN_LEVEL_CALL,       // authentication level
			RPC_C_IMP_LEVEL_IMPERSONATE,  // impersonation level
			NULL,                         // client identity 
			EOAC_NONE                     // proxy capabilities     
		);

		if (FAILED(hres))
		{
			cout << "Could not set proxy blanket. Error code = 0x"
				<< hex << hres << endl;
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return 1;               // Program has failed.
		}


		// Use the IWbemServices pointer to make requests of WMI. 
		// Make requests here:

		// For example, query for all the running processes
		IEnumWbemClassObject* pEnumerator = NULL;
		hres = pSvc->ExecQuery(
			bstr_t("WQL"),
			bstr_t("SELECT * FROM Win32_Process"),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator);

		if (FAILED(hres))
		{
			cout << "Query for processes failed. "
				<< "Error code = 0x"
				<< hex << hres << endl;
			pSvc->Release();
			pLoc->Release();
			CoUninitialize();
			return 1;               // Program has failed.
		}
		else
		{
			IWbemClassObject *pclsObj;
			ULONG uReturn = 0;

			while (pEnumerator)
			{
				hres = pEnumerator->Next(WBEM_INFINITE, 1,
					&pclsObj, &uReturn);

				if (0 == uReturn)
				{
					break;
				}

				VARIANT vtProp;

				// Get the value of the Name property
				hres = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
				wcout << "Process Name : " << vtProp.bstrVal << endl;
				VariantClear(&vtProp);
			}

		}

		// Cleanup
		// ========

		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
	}

	void sysInfo::getSystemInfo(SYSTEM_INFO sys)
	{
		GetSystemInfo(&sys);
	}

#define DIV 1024
#define WIDTH 7
	void sysInfo::getMemoryStatus()
	{
		MEMORYSTATUSEX strct;
		strct.dwLength = sizeof(strct);
		GlobalMemoryStatusEx(&strct);
		printf("Memory Status: \n");
		_tprintf(TEXT("Total Memory %*I64d  MB :"), WIDTH, strct.ullTotalPhys / DIV);
		_tprintf(TEXT("In Use %*ld :"), strct.dwMemoryLoad);
		_tprintf(TEXT("Free Memory %*I64d Mb :"), WIDTH, strct.ullAvailPhys / DIV);
	}

	BOOL sysInfo::getToken()
	{

		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;

		// Get a token for this process. 

		if (!OpenProcessToken(GetCurrentProcess(),
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
			return(FALSE);

		// Get the LUID for the shutdown privilege. 

		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
			&tkp.Privileges[0].Luid);

		tkp.PrivilegeCount = 1;  // one privilege to set    
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

		// Get the shutdown privilege for this process. 

		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
			(PTOKEN_PRIVILEGES)NULL, 0);

		if (GetLastError() != ERROR_SUCCESS)
			return FALSE;

		return TRUE;
		// Shut down the system and force all applications to close. 
	}
	
	DWORD sysInfo::getProcessorType()
	{
		SYSTEM_INFO sys;
		sysInfo::getSystemInfo(sys);
		printf("Processor Type: %u", sys.dwProcessorType);
		return sys.dwProcessorType;
	}
	DWORD sysInfo::getNumberOfProcessors()
	{
		SYSTEM_INFO sys;
		sysInfo::getSystemInfo(sys);
		printf("  Number of processors: %u\n",
			sys.dwNumberOfProcessors);
		printf("Processor Type: %u ", sys.dwNumberOfProcessors);

		return sys.dwNumberOfProcessors;
	}
	WORD sysInfo::getProcessorArchitecture()
	{
		SYSTEM_INFO sys;
		sys::sysInfo::getSystemInfo(sys);
		printf("Processor Type: %u ", sys.wProcessorArchitecture);

		return sys.wProcessorArchitecture;
	}

	
}

namespace prc
{
	PROCESS_INFORMATION proc::LaunchProcess(TCHAR *path)
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

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
		
		return pi;
	}

}
