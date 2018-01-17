#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

char message[100];

int main( void )
{
	printf( "Enter '%lx' to 'procWriter.exe' window!...\n", message );
	printf( "Press ENTER to show received message!..\n" );
	getchar();
	printf ("%s", message );
	getchar();

	return 0;
}