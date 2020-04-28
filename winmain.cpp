#include "application.h"

#include "windows.h"

/*
==========================================================
	Windows entry point.
==========================================================
*/

int CALLBACK WinMain(HINSTANCE InstanceHandle, HINSTANCE PrevInstanceHandle, LPSTR CommandLine, int ShowCommand)
{
	// Initialize Microsoft COM Interface.
	CoInitialize(NULL);

	application CitySimulator;

	CitySimulator.Run();

	return 0;
};