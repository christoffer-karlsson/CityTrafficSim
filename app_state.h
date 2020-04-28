#pragma once

#include "common.h"
#include "math.h"

enum class context
{
	APP_CONTEXT_EDIT, 
	APP_CONTEXT_DEBUG, 
	APP_CONTEXT_SIMULATION,
};

class app_state
{
	private:

	static context	AppContext;
	static bool		Running;
	static bool		EditMode;
	static bool		DebugMenu;
	static vec3		MouseCoordinateInWorld;
	static vec3u	MouseCoordinateInWorldTruncated;

	public:

	static void Shutdown();
	static void SetContext(context Context);
	static void SetMouseCoordinateInWorld(vec3 MouseCoordinateInWorld);

	static void ToggleEditMode();
	static void ToggleDebugMenu();

	static bool		IsRunning();
	static context	GetAppContext();
	static bool		GetEditModeEnabled();
	static bool		GetDebugMenuEnabled();
	static vec3		&GetMouseCoordinateInWorld();
	static vec3u	&GetMouseCoordinateInWorldTruncated();
};