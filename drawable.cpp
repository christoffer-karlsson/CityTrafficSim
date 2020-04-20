#include "drawable.h"

drawable::drawable()
{
	Texture = nullptr;
	VertexShader = nullptr;
	IndexBuffer = nullptr;
	PixelShader = nullptr;
	VertexBuffer = nullptr;
	InstanceBuffer = nullptr;

	for(uint32 Index = 0;
		Index < MAX_CONSTANT_BUFFERS;
		Index++)
	{
		ConstantBuffer[Index] = nullptr;
	}
}

drawable::~drawable()
{
	delete Texture;
	delete VertexShader;
	delete IndexBuffer;
	delete PixelShader;
	delete VertexBuffer;
	delete InstanceBuffer;

	for(uint32 Index = 0;
		Index < MAX_CONSTANT_BUFFERS;
		Index++)
	{
		delete ConstantBuffer[Index];
	}
}

world_model &drawable::GetWorldModel()
{
	return Model;
}

std::vector<vec3> &drawable::GetCollisionModel()
{
	return CollisionModel;
}
