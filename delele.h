#pragma once
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PWRCONTROL_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PWRCONTROL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef DELELE_EXPORTS
#define DELELE_API __declspec(dllexport)
#else
#define DELELE_API __declspec(dllimport)
#endif
#include "stdafx.h"
#include "windows.h"
// This class is exported from the pwrControl.dll

namespace pwr
{

	class DELELE_API pwrControl {
	public:
		static BOOL PWR(char *);
		static BOOL Shutdown();
		static BOOL Poweroff();
		static BOOL Reboot();
		static BOOL Logoff();
		static int Suspend();
		static BOOL Lock();
		static char *str(char *);
		// TODO: add your methods here.
	};


}
namespace sys
{
	class DELELE_API sysInfo
	{
	public:
		static TCHAR *getPCName(void);
		static TCHAR *getUsrName(void);
		static TCHAR *getComputerName(int param);
		static TCHAR *getSystemDirectory();
		static TCHAR *getWindowsDirectory();
		bool setComputerName(int NameType, LPCTSTR lpBuffer);
		static const char *getSystemVersion();
		static void getSystemInfo(SYSTEM_INFO sys);
		static BOOL getToken();
		static int get32Process();
		static void getMemoryStatus();
		static DWORD getProcessorType();
		static DWORD getNumberOfProcessors();
		static WORD getProcessorArchitecture();
		static void getSystemInstallDate();
		static void odev1();
	};


}

namespace prc
{
	class DELELE_API proc
	{
		public:
			static PROCESS_INFORMATION LaunchProcess(TCHAR *path);
			static void ListProcess();
	};
}




