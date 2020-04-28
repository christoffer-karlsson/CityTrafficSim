#pragma once

#include "common.h"
#include "world_model.h"
#include "d3d_diagnostics.h"
#include "camera.h"
#include "math.h"
#include "texture.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_shader.h"
#include "pixel_shader.h"
#include "constant_buffer.h"
#include "instance_buffer.h"
#include "light_point.h"
#include "light_directional.h"
#include "mesh.h"

#include <memory>
#include <vector>

#define MAX_CONSTANT_BUFFERS 10

class drawable
{
	private:

	world_model Model;

	protected:

	texture			*Texture;
	vertex_shader	*VertexShader;
	pixel_shader	*PixelShader;
	vertex_buffer	*VertexBuffer;
	index_buffer	*IndexBuffer;
	instance_buffer *InstanceBuffer;
	constant_buffer *ConstantBuffer[MAX_CONSTANT_BUFFERS];

	std::vector<vec3> CollisionModel;

	public:

	drawable();
	virtual ~drawable();

	virtual void Draw() = 0;

	world_model &GetWorldModel();

	// NOTE(Cristoffer): Override this if drawable child has a highlight color resource.
	virtual void UpdateHighlightColorResource(vec3u Position, bool32 IsHighlighted){};

	// NOTE(Cristoffer): Override if drawable is instanced.
	virtual uint32 AddInstance(vec3 Position, vec4 Color, vec3 &Rotation, vec3 &Scale)
	{
		return -1;
	};
	virtual void UpdateInstance(uint32 ID, vec3 &Position){};
	virtual void UpdateInstance(uint32 ID, vec3 &Position, vec3 &Rotation, vec3 &Scale){};

	std::vector<vec3> &GetCollisionModel();

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