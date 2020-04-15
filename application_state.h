#pragma once

#include "common.h"
#include "math.h"

class application_state
{
	private:

	static bool32 EditMode;
	static vec3   MouseCoordinateInWorld;
	static vec3u  MouseCoordinateInWorldTrunc;

	public:

	static void SetMouseCoordinateInWorld(vec3 MouseCoordinateInWorld);

	static void ToggleEditMode();

	static bool32 GetEditModeEnabled();
	static vec3   &GetMouseCoordinateInWorld();
	static vec3u  &GetMouseCoordinateInWorldTrunc();
};