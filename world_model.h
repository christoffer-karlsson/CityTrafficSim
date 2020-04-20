// world_model.h
// Interface to do translation, scaling and rotation with the matrix model.

#pragma once

#include "common.h"
#include "math.h"
#include <DirectXMath.h>

using namespace DirectX;

// NOTE(Cristoffer): Global constants.
struct const_rotation_vectors
{
	static const XMVECTOR RotationVectorAxisX;
	static const XMVECTOR RotationVectorAxisY;
	static const XMVECTOR RotationVectorAxisZ;
};

// TODO(Cristoffer): Temp.
XMMATRIX ConstructModelXXX(vec3 Position, vec3 Scale, vec3 Rotation);

class world_model
{
	private:

	XMMATRIX Model;

	public:

	vec3 Position;
	vec3 Scale;
	vec3 Rotation;

	world_model();
	world_model(vec3 Position, vec3 Scale, vec3 Rotation);
	~world_model() = default;

	void Update();

	XMMATRIX &GetMatrix();
};