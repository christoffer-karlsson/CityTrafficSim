#pragma once

#include "common.h"
#include "math.h"

enum class context
{
	Edit, Debug, Simulation
};

class application_state
{
	private:

	static context Context;

	static bool32 EditMode;
	static bool32 DebugMenu;
	static vec3   MouseCoordinateInWorld;
	static vec3u  MouseCoordinateInWorldTrunc;

	public:

	static void SetContext(context Context);
	static void SetMouseCoordinateInWorld(vec3 MouseCoordinateInWorld);

	static void ToggleEditMode();
	static void ToggleDebugMenu();

	static context GetContext();
	static bool32  GetEditModeEnabled();
	static bool32  GetDebugMenuEnabled();
	static vec3    &GetMouseCoordinateInWorld();
	static vec3u   &GetMouseCoordinateInWorldTrunc();
};