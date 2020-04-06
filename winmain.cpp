// winmain.cpp: Entry point for the program to create the window.

#include "application.h"

#include <windows.h>

int CALLBACK WinMain(HINSTANCE InstanceHandle, HINSTANCE PrevInstanceHandle, LPSTR CommandLine, int ShowCommand)
{
	// NOTE(Cristoffer): Initialize Microsoft COM Interface.
	CoInitialize(NULL);

	application CitySimulator;

	CitySimulator.Run();

	return 0;
};

/* TODO(Cristoffer): Long term todo-list, what should be implemented with time.

		- Memory management for tracking memory usage
		- Simulation region, simulate a reasonable region
		- Asset system
		- Dynamic asset loading

*/