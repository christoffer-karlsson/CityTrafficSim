#pragma once

#include "common.h"
#include "direct3d.h"

enum class shader_set_type
{
	SetVertexShader, SetPixelShader
};

class constant_buffer
{
	private:

	ID3D11Buffer *ConstantBuffer;

	uint32 Size;

	public:

	constant_buffer(void *ShaderInput, uint32 Size);
	~constant_buffer();

	void Update(void *ShaderInput);

	void Bind(uint32 Slot, shader_set_type ShaderType);
};