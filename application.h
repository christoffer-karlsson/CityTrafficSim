// application.h: The main loop, starts the window and Direct3D context.

#pragma once

#include "common.h"
#include "window.h"
#include "timing.h"
#include "persistence.h"
#include "global_device_info.h"
#include "global_data_collector.h"
#include "direct3d.h"
#include "threading.h"

#include <windows.h>
#include <string>

class application
{
	private:

	window		Window;
	timing		Timing;
	direct3d	Graphics;
	persistence Persistence;

	bool Running;

	public:

	application();
	~application() = default;
	application(application const &Object) = delete;
	void operator=(application const &Object) = delete;

	void Run();
};