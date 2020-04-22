#include "light_source.h"

cbuffer_light light_source::ConstantBuffer;

void light_source::Init()
{
	ConstantBuffer.LightPosition.x = 55.0f;
	ConstantBuffer.LightPosition.y = 735.0f;
	ConstantBuffer.LightPosition.z = -440.f;

	ConstantBuffer.DiffuseColor.x = 0.87f;
	ConstantBuffer.DiffuseColor.y = 0.81f;
	ConstantBuffer.DiffuseColor.z = 0.78f;

	ConstantBuffer.Ambient.x = 0.50f;
	ConstantBuffer.Ambient.y = 0.61f;
	ConstantBuffer.Ambient.z = 0.83f;
}

void light_source::SetPosition(vec3 Position)
{
	ConstantBuffer.LightPosition.x = Position.x;
	ConstantBuffer.LightPosition.y = Position.y;
	ConstantBuffer.LightPosition.z = Position.z;
}

void light_source::SetAmbient(vec3 Ambient)
{
	ConstantBuffer.Ambient.x = Ambient.x;
	ConstantBuffer.Ambient.y = Ambient.y;
	ConstantBuffer.Ambient.z = Ambient.z;
}

void light_source::SetDiffuseColor(vec3 Diffuse)
{
	ConstantBuffer.DiffuseColor.x = Diffuse.x;
	ConstantBuffer.DiffuseColor.y = Diffuse.y;
	ConstantBuffer.DiffuseColor.z = Diffuse.z;
}

vec3 light_source::GetPosition()
{
	vec3 Result;

	Result.x = ConstantBuffer.LightPosition.x;
	Result.y = ConstantBuffer.LightPosition.y;
	Result.z = ConstantBuffer.LightPosition.z;

	return Result;
}

cbuffer_light &light_source::GetConstantBuffer()
{
	return ConstantBuffer;
}