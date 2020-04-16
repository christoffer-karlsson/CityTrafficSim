#include "light_source.h"

cbuffer_light light_source::ConstantBuffer;

void light_source::Init(vec3 Position)
{
	ConstantBuffer.LightPosition.x = Position.x;
	ConstantBuffer.LightPosition.y = Position.y;
	ConstantBuffer.LightPosition.z = Position.z;

	ConstantBuffer.DiffuseColor.x = 1.0f;
	ConstantBuffer.DiffuseColor.y = 1.0f;
	ConstantBuffer.DiffuseColor.z = 1.0f;

	ConstantBuffer.Ambient.x = 0.15f;
	ConstantBuffer.Ambient.y = 0.15f;
	ConstantBuffer.Ambient.z = 0.20f;
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