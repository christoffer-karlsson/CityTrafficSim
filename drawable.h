#pragma once

#include "common.h"
#include "diagnostics.h"
#include "global_device_info.h"
#include "camera.h"
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

struct position
{
	real32 X, Y, Z;
};

struct color
{
	real32 R, G, B, A;
};

class drawable
{
	protected:

	texture			*Texture;
	shader			*Shader;
	vertex_buffer	*VertexBuffer;
	constant_buffer *ConstantBuffer;

	XMMATRIX Model;

	public:

	drawable();
	virtual ~drawable();

	virtual void Draw(camera &Camera) = 0;

	void SetModelPosition(real32 X, real32 Y, real32 Z);
	void SetModelScale(real32 X, real32 Y, real32 Z);

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