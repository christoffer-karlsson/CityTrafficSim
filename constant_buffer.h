#pragma once

#include "common.h"
#include "direct3d.h"

class constant_buffer
{
	private:

	ID3D11Buffer *ConstantBuffer;

	uint32 Size;

	public:

	constant_buffer(void *ShaderInput, uint32 Size);
	~constant_buffer();

	void Update(void *ShaderInput);

	void Bind();
};