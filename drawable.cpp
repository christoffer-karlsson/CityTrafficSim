#include "drawable.h"

drawable::drawable()
{
	Model = XMMatrixIdentity();
	Texture = nullptr;
	Shader = nullptr;
	VertexBuffer = nullptr;
	ConstantBuffer = nullptr;
}

drawable::~drawable()
{
	delete Texture;
	delete Shader;
	delete VertexBuffer;
	delete ConstantBuffer;
}

void drawable::SetModelPosition(real32 X, real32 Y, real32 Z)
{
	Model = Model * XMMatrixTranslation(X, Y, Z);
}

void drawable::SetModelScale(real32 X, real32 Y, real32 Z)
{
	Model = Model * XMMatrixScaling(X, Y, Z);
}