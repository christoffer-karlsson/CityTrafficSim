/*
==========================================================
	Main application loop where everything is ran.
==========================================================
*/

#pragma once

#include "common.h"
#include "window.h"
#include "timing.h"
#include "persistence.h"
#include "d3d_api.h"
#include "threading.h"
#include "math.h"
#include "entity_manager.h"
#include "light_point.h"
#include "render_manager.h"
#include "app_state.h"
#include "logger.h"
#include "system_message.h"
#include "asset_manager.h"
#include "drawable_cars.h"
#include "world.h"

#if DEBUG_MODE

#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_win32.h"
#include "external/imgui/imgui_impl_dx11.h"

#endif

#include "windows.h"
#include <string>

class application
{
	private:

	window		Window;
	timing		Timing;
	persistence	Persistence;

	public:

	application();
	~application() = default;
	application(application const &Object) = delete;
	void operator=(application const &Object) = delete;

	void Run();
};