// light_source.h
// Represents a point light source. Contains the position and the
// constant buffer needed for pixel shaders that the light should affect.
// Reference article: https://learnopengl.com/Lighting/Basic-Lighting

#pragma once

#include "common.h"

#include <DirectXMath.h>

using namespace DirectX;

struct cbuffer_light
{
	XMFLOAT3 LightPosition; alignas(16)
	XMFLOAT3 Ambient; alignas(16)
	XMFLOAT3 DiffuseColor; alignas(16)

	// NOTE(Cristoffer): Attenuation values, see: http://wiki.ogre3d.org/-Point+Light+Attenuation
	real32 DiffuseIntensity = 0.85f;
	real32 AttenuationConstant = 1.0f;
	real32 AttenuationLinear = 0.002f;
	real32 AttenuationQuad = 0.000007f;
};

class light_source
{
	public:

	static cbuffer_light ConstantBuffer;

	public:

	static void Init();

	static void SetPosition(vec3 Position);
	static void SetAmbient(vec3 Ambient);
	static void SetDiffuseColor(vec3 Diffuse);

	static vec3 GetPosition();

	static cbuffer_light &GetConstantBuffer();
};