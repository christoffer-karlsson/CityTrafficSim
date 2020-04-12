// mouse_picker.h:
// Transform mouse pointer X,Y screen coordinates to world coordinates and
// checks for intersects with triangles.

#pragma once

#include "common.h"
#include "camera.h"
#include "mouse.h"
#include "global_device_info.h"
#include "global_data_collector.h"
#include "threading.h"
#include "vertex_buffer.h"

#include "world.h"

#include "external/SimpleMath.h"
#include <DirectXMath.h>

class mouse_picker
{
	private:

	world *World;
	terrain	*Terrain;
	camera	*Camera;

	vec2 CurrentMousePositionInWorld;

	void RayTriangleIntersectWork();

	public:

	work_id ThreadWorkID;

	mouse_picker(world *World, terrain *Terrain, camera *Camera);
	~mouse_picker() = default;

	mouse_picker(mouse_picker const &Object) = delete;
	void operator=(mouse_picker const &Object) = delete;

	void TestMouseCollision();

	vec2 &GetMousePositionInWorld();
};
