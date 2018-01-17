#include<Windows.h>
#include<lmcons.h>
#include<stdio.h>

#define BUF_SÝZE 512
typedef VOID(WINAPI *SYSINF)(LPSYSTEM_INFO);//sysinf bizim tanýmladýðýmýz bir structure


int main(){

	TCHAR mesaj[BUF_SÝZE];
	*mesaj = NULL;
	TCHAR nbname[MAX_COMPUTERNAME_LENGTH + 1];
	TCHAR username[UNLEN +5]; 
	DWORD nbname_size = MAX_COMPUTERNAME_LENGTH + 1;
	DWORD username_size = UNLEN + 1;
	
	if (!GetComputerName(nbname, &nbname_size)) {
		return 0;
	}  
		if (!GetUserName(username, &username_size)) {
		return 0;
	}
	
	HINSTANCE hInstance;
	SYSINF sysINF;
	SYSTEM_INFO si;
	 TCHAR *cpuArch;

	hInstance = LoadLibrary(L"kernel32.dll");

	if (hInstance == NULL)
	{
		printf("LoadLibrary : Loading DLL is failed");
		return 1;
	}
	else
		sysINF = (SYSINF)GetProcAddress(hInstance, "GetNativeSystemInfo");


	if (NULL == sysINF)
	{
		printf("GetProcAddress(): Getting function address is failed.");
		GetSystemInfo(&si); //64 bitse bunu çaðýr deðilse aþagýdaki
	}
	else
		sysINF(&si); // 32 biti çaðýr


	switch (si.wProcessorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_AMD64:
		cpuArch = L"64-Bit";
		break;

	case PROCESSOR_ARCHITECTURE_INTEL:
		cpuArch = L"32-Bit";
		break;

	default: cpuArch = L"Bilinmiyor";
		break;
	}
		
		
	
	
//	TCHAR nproc[10];
	
//	swprintf_s(nproc, 10, L"%d", si.dwNumberOfProcessors);
	swprintf_s(mesaj, 100, L"Bilgisayar:%s\nKullanicı:%s\nÝþlemci:%d\nMimari:%s", nbname, username, si.dwNumberOfProcessors,cpuArch);
	
   
	
/*	wcscat_s(mesaj, L"Bilgisayar:");
	wcscat_s(mesaj,nbname);
	
	wcscat_s(mesaj, L"\nKullanýcý:");
	wcscat_s(mesaj, username);
	
	wcscat_s(mesaj, L"\nÝþlemci:");
	wcscat_s(mesaj, nproc);
	
	wcscat_s(mesaj, L"\nMimari:");
	wcscat_s(mesaj, cpuArch);
	*/
	MessageBox(NULL, 
		       mesaj,
		       L"Sistem Bilgisi",
		       MB_OK | MB_ICONINFORMATION);
	
	
	

	return 0;
}
