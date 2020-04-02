// application.h: The main loop, starts the window and Direct3D context.

#pragma once

#include "common.h"
#include "window.h"
#include "timing.h"

#include <windows.h>
#include <string>

class application
{
	private:

	window		Window;
	timing		Timing;
	// TODO(Cristoffer): Implement next..
	//Thread		Thread;
	//Direct3D	Graphics;

	// TODO(Cristoffer): Temp! Remove this later.
	real64 TimeCheck;

	bool Running;

	public:

	application();
	~application();

	DISABLE_INSTANCE_COPY(application);

	void Run();
};