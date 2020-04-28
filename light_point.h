// Reference article: https://learnopengl.com/Lighting/Basic-Lighting
// Attenuation value reference: http://wiki.ogre3d.org/-Point+Light+Attenuation

/*
==========================================================
	Light point. Represents a point light position
	with attenuation values.
==========================================================
*/

#pragma once

#include "common.h"

#include <DirectXMath.h>

using namespace DirectX;

struct light_point
{
	// One byte offsets for 16 byte shader input alignment.
	XMFLOAT3 Position;		alignas(16)
	XMFLOAT3 AmbientColor;	alignas(16)
	XMFLOAT3 DiffuseColor;	alignas(16)

	real32 DiffuseIntensity = 0.85f;
	real32 AttenuationConstant = 1.0f;
	real32 AttenuationLinear = 0.002f;
	real32 AttenuationQuad = 0.000007f;
};

extern light_point WorldLight;