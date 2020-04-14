#include "application_state.h"

bool32 application_state::EditMode = 0;

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
