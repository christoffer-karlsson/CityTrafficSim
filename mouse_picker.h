// mouse_picker.h:
// Transform mouse pointer X,Y screen coordinates to world coordinates and
// checks for intersects with triangles.

#pragma once

#include "common.h"
#include "camera.h"
#include "mouse.h"
#include "terrain.h"
#include "global_device_info.h"
#include "global_data_collector.h"
#include "threading.h"

#include "external/SimpleMath.h"
#include <DirectXMath.h>

class mouse_picker
{
	private:

	terrain	*Terrain;
	camera	*Camera;

	uint32 ThreadWorkID;

	position MousePositionInWorld;

	void RayTriangleIntersectWork();

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
