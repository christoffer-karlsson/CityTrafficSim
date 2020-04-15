#include "application_state.h"

bool32 application_state::EditMode = 0;
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

bool32 application_state::GetEditModeEnabled()
{
	return EditMode;
}

vec3 &application_state::GetMouseCoordinateInWorld()
{
	return MouseCoordinateInWorld;
}

vec3u &application_state::GetMouseCoordinateInWorldTrunc()
{
	return MouseCoordinateInWorldTrunc;
}
