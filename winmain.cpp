// winmain.cpp: Entry point for the program to create the window.

#include "application.h"

#include <windows.h>

int CALLBACK WinMain(HINSTANCE InstanceHandle, HINSTANCE PrevInstanceHandle, LPSTR CommandLine, int ShowCommand)
{
	application CitySimulator;

	CitySimulator.Run();

	return 0;
};