#pragma once

#include "common.h"
#include "camera.h"
#include "mouse.h"
#include "global_device_info.h"

#include "external/SimpleMath.h"
#include <DirectXMath.h>

class mouse_picker
{
	private:

	camera *Camera;

	real32 X, Y, Z;

	public:

	mouse_picker(camera *Camera);
	~mouse_picker() = default;

	//void Update();

	real32 GetRayX() const;
	real32 GetRayY() const;
	real32 GetRayZ() const;

	void TestIntersection();
};