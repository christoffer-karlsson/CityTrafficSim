#pragma once

#include "common.h"

class application_state
{
	private:

	static bool32 EditMode;

	public:

	static void ToggleEditMode();

	static bool32 GetEditModeEnabled();
};