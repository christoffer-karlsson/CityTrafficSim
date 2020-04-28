#include "app_state.h"

context app_state::AppContext = context::APP_CONTEXT_SIMULATION;
bool	app_state::Running = true;
bool	app_state::EditMode = false;
bool	app_state::DebugMenu = false;
vec3	app_state::MouseCoordinateInWorld;
vec3u	app_state::MouseCoordinateInWorldTruncated;

void app_state::SetMouseCoordinateInWorld(vec3 MouseCoordinateInWorld)
{
	MouseCoordinateInWorldTruncated = Truncate(MouseCoordinateInWorld);
	app_state::MouseCoordinateInWorld = MouseCoordinateInWorld;
}

void app_state::ToggleEditMode()
{
	EditMode = !EditMode;
}

void app_state::ToggleDebugMenu()
{
	DebugMenu = !DebugMenu;
}

void app_state::Shutdown()
{
	Running = false;
}

void app_state::SetContext(context Context)
{
	app_state::AppContext = Context;
}

bool app_state::IsRunning()
{
	return Running;
}

context app_state::GetAppContext()
{
	return AppContext;
}

bool app_state::GetEditModeEnabled()
{
	return EditMode;
}

bool app_state::GetDebugMenuEnabled()
{
	return DebugMenu;
}

vec3 &app_state::GetMouseCoordinateInWorld()
{
	return MouseCoordinateInWorld;
}

vec3u &app_state::GetMouseCoordinateInWorldTruncated()
{
	return MouseCoordinateInWorldTruncated;
}
