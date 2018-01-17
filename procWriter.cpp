#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	
	PVOID pAddress;
	char message[] = "Hello, from procWriter.exe!...\n";
	SIZE_T dw;

	ZeroMemory( &si, sizeof( si ) );
	si.cb = sizeof( si );
	ZeroMemory( &pi, sizeof( pi ) );
	
	if ( !CreateProcess( NULL, "procReader.exe", NULL, NULL, TRUE,
						 CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi ) ) {
		fprintf( stderr, "Cannot create process!..\n" );
		exit( EXIT_FAILURE );
	}

	printf( "Enter the data address of 'procReader.exe' :  " );
	scanf( "%lx", &pAddress );

	if ( !WriteProcessMemory( pi.hProcess, pAddress, message,
							  strlen( message ), &dw ) ) {
		fprintf( stderr, "Cannot write memory!..\n" );
		exit( EXIT_FAILURE );
	}

	WaitForSingleObject( pi.hProcess, INFINITE );
	return 0;
}