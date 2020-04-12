#pragma once

#include "common.h"
#include "diagnostics.h"
#include "global_device_info.h"
#include "camera.h"
#include "math.h"
#include "texture.h"
#include "vertex_buffer.h"
#include "shader.h"
#include "constant_buffer.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>
#include <vector>

using namespace DirectX;

class drawable
{
	private:

	XMMATRIX InitialModel;

	protected:
	XMMATRIX Model;

	texture			*Texture;
	shader			*Shader;
	vertex_buffer	*VertexBuffer;
	constant_buffer *ConstantBuffer;

	vec3 Position;
	vec3 Rotation;
	vec3 Scale;

	public:

	drawable();
	virtual ~drawable();

	virtual void Draw(camera &Camera) = 0;

	// NOTE(Cristoffer): Set up initial model properly for each drawable when created.
	// This will be used as reference to be able to reset rotations etc.
	void SetInitialModel(vec3 Position, vec3 Scale, vec3 Rotation);

	void SetPosition(vec3 Position);
	void SetRotation(vec3 Rotation);
	void SetScale(vec3 Scale);

	void UpdateModel();

	XMMATRIX &GetModel();

	// NOTE(Cristoffer): Needed for 16-byte alignments due to DirectX::XMMATRIX, when allocating to heap.

	void *operator new(size_t Data)
	{
		return _mm_malloc(Data, 16);
	}

	void operator delete(void *Pointer)
	{
		_mm_free(Pointer);
	}
};