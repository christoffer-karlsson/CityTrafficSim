// application.h: The main loop, starts the window and Direct3D context.

#pragma once

#include "common.h"
#include "window.h"

#include <windows.h>

class application
{
	private:

	window		Window;
	//Direct3D	Graphics;
	//Timing		Timing;

	bool Running;

	public:

	application();
	~application();

	DISABLE_INSTANCE_COPY(application);

	void Run();
};