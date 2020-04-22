#include "application_state.h"

context application_state::Context = context::Simulation;

bool32 application_state::EditMode = 0;
bool32 application_state::DebugMenu = 0;
vec3   application_state::MouseCoordinateInWorld;
vec3u  application_state::MouseCoordinateInWorldTrunc;

void application_state::SetMouseCoordinateInWorld(vec3 MouseCoordinateInWorld)
{
	// TODO(Cristoffer): Need proper casting from real to integer. It doesn't map too well
	// right now. Look at this later.
	MouseCoordinateInWorldTrunc = Truncate(MouseCoordinateInWorld);

	application_state::MouseCoordinateInWorld = MouseCoordinateInWorld;
}

void application_state::ToggleEditMode()
{
	if(EditMode == 0)
	{
		EditMode = 1;
	}
	else
	{
		EditMode = 0;
	}
}

void application_state::ToggleDebugMenu()
{
	if(DebugMenu == 0)
	{
		DebugMenu = 1;
	}
	else
	{
		DebugMenu = 0;
	}
}

void application_state::SetContext(context Context)
{
	application_state::Context = Context;
}

context application_state::GetContext()
{
	return Context;
}

bool32 application_state::GetEditModeEnabled()
{
	return EditMode;
}

bool32 application_state::GetDebugMenuEnabled()
{
	return DebugMenu;
}

vec3 &application_state::GetMouseCoordinateInWorld()
{
	return MouseCoordinateInWorld;
}

vec3u &application_state::GetMouseCoordinateInWorldTrunc()
{
	return MouseCoordinateInWorldTrunc;
}
