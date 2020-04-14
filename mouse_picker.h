// mouse_picker.h:
// Transform mouse pointer X,Y screen coordinates to world coordinates and
// checks for intersects with triangles.

#pragma once

#include "common.h"
#include "camera.h"
#include "mouse.h"
#include "direct3d.h"

#include "external/SimpleMath.h"

#include <vector>

class mouse_picker
{
	private:

	uint32 CollisionIndex;

	public:

	mouse_picker() = default;
	~mouse_picker() = default;

	// NOTE(Cristoffer): Returns true if collision is found, stores the index in given container.
	bool32 TestMouseCollision(XMMATRIX &Model, std::vector<vec3> &Vertices);

	uint32 GetCollisionIndex();
};
