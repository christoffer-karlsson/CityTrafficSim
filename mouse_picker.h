#pragma once

#include "common.h"
#include "camera.h"
#include "mouse.h"
#include "terrain.h"
#include "global_device_info.h"
#include "global_data_collector.h"

#include <future>
#include <thread>
#include <atomic>

#include "external/SimpleMath.h"
#include <DirectXMath.h>

class mouse_picker
{
	private:

	terrain	*Terrain;
	camera	*Camera;

	std::mutex			Mutex;
	std::future<bool>	Job;
	std::atomic<bool>	ThreadBusy;

	position MousePositionInWorld;

	static void RayTriangleIntersectWork(mouse_picker *Instance);

	public:

	mouse_picker();
	mouse_picker(terrain *Terrain, camera *Camera);
	~mouse_picker() = default;

	mouse_picker(mouse_picker const &Object) = delete;
	void operator=(mouse_picker const &Object) = delete;

	void Init(terrain *Terrain, camera *Camera);

	void TestMouseCollision();

	position &GetMousePositionInWorld();
};
