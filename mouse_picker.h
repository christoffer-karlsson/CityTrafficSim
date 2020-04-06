#pragma once

#include "common.h"
#include "camera.h"
#include "mouse.h"
#include "global_device_info.h"

#include <DirectXMath.h>

class mouse_picker
{
	private:

	camera *Camera;

	XMFLOAT3 RayNormalised;
	XMFLOAT4 RayClip;
	XMFLOAT4 RayCamera;
	XMFLOAT3 RayWorld;

	public:

	mouse_picker(camera *Camera);
	~mouse_picker() = default;

	void Update();

	real32 GetRayX() const;
	real32 GetRayY() const;
	real32 GetRayZ() const;
};