/*
==========================================================
	Supply constant data to a shader.
	Bind to either vertex or pixel shader.
==========================================================
*/

#pragma once

#include "common.h"
#include "d3d_api.h"

enum class shader_set_type
{
	SetVertexShader, SetPixelShader
};

class constant_buffer
{
	private:

	ID3D11Buffer	*ConstantBuffer;
	uint32			Size;

	public:

	constant_buffer(void *ShaderInput, uint32 Size);
	~constant_buffer();

	void Update(void *ShaderInput);

	void Bind(uint32 Slot, shader_set_type ShaderType);
};