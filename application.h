// application.h: The main loop, starts the window and Direct3D context.

#pragma once

#include "common.h"
#include "window.h"
#include "timing.h"
#include "persistence.h"
#include "direct3d.h"
#include "threading.h"
#include "math.h"
#include "entity_manager.h"
#include "light_source.h"
#include "render_manager.h"
#include "application_state.h"
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

#include <windows.h>
#include <string>

class application
{
	private:

	window		Window;
	timing		Timing;
	persistence	Persistence;

	bool Running;

	protected:

	void CameraControl();

	void SimulationContext();
	void EditContext();
	void DebugContext();

	public:

	application();
	~application() = default;
	application(application const &Object) = delete;
	void operator=(application const &Object) = delete;

	void Run();
};