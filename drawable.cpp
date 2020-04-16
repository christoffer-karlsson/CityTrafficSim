#include "drawable.h"

drawable::drawable()
{
	Model = XMMatrixIdentity();
	InitialModel = XMMatrixIdentity();
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

void drawable::SetInitialModel(vec3 Position, vec3 Scale, vec3 Rotation)
{
	SetPosition(Position);
	SetRotation(Rotation);
	SetScale(Scale);

	Update();

	// NOTE(Cristoffer): Store copy of the "initial" model.
	//InitialModel = Model;
}

void drawable::SetPosition(vec3 Position)
{
	this->Position = Position;
}

void drawable::SetRotation(vec3 Rotation)
{
	this->Rotation = Rotation;
}

void drawable::SetScale(vec3 Scale)
{
	this->Scale = Scale;
}

vec3 &drawable::GetPosition()
{
	return Position;
}

vec3 &drawable::GetRotation()
{
	return Rotation;
}

vec3 &drawable::GetScale()
{
	return Scale;
}

void drawable::Update()
{
	Model = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	XMMATRIX ScaleMatrix = XMMatrixScaling(Scale.x, Scale.y, Scale.z);
	XMMATRIX TranslationMatrix = XMMatrixTranslation(Position.x, Position.y, Position.z);

	XMVECTOR RotationAxisX = XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f);
	XMVECTOR RotationAxisY = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	XMVECTOR RotationAxisZ = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);

	XMMATRIX RotationInX = XMMatrixRotationAxis(RotationAxisX, DegreeToRadian(Rotation.x));
	XMMATRIX RotationInY = XMMatrixRotationAxis(RotationAxisY, DegreeToRadian(Rotation.y));
	XMMATRIX RotationInZ = XMMatrixRotationAxis(RotationAxisZ, DegreeToRadian(Rotation.z));

	XMMATRIX RotationMatrix = RotationInX * RotationInY * RotationInZ;

	Model = Model * RotationMatrix * TranslationMatrix * ScaleMatrix;
}

XMMATRIX &drawable::GetModel()
{
	return Model;
}

std::vector<vec3> &drawable::GetCollisionModel()
{
	return CollisionModel;
}
