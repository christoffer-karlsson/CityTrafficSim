#include "world_model.h"

const XMVECTOR const_rotation_vectors::RotationVectorAxisX = XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f);
const XMVECTOR const_rotation_vectors::RotationVectorAxisY = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
const XMVECTOR const_rotation_vectors::RotationVectorAxisZ = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);

XMMATRIX ConstructModelXXX(vec3 Position, vec3 Scale, vec3 Rotation)
{
	XMMATRIX Model;

	Model = XMMatrixIdentity();

	XMMATRIX ScaleMatrix = XMMatrixScaling(Scale.x, Scale.y, Scale.z);

	XMMATRIX TranslationMatrix = XMMatrixTranslation(Position.x, Position.y, Position.z);

	XMMATRIX RotationInX = XMMatrixRotationAxis(const_rotation_vectors::RotationVectorAxisX, DegreeToRadian(Rotation.x));
	XMMATRIX RotationInY = XMMatrixRotationAxis(const_rotation_vectors::RotationVectorAxisY, DegreeToRadian(Rotation.y));
	XMMATRIX RotationInZ = XMMatrixRotationAxis(const_rotation_vectors::RotationVectorAxisZ, DegreeToRadian(Rotation.z));

	XMMATRIX RotationMatrix = RotationInX * RotationInY * RotationInZ;

	Model = Model * RotationMatrix * TranslationMatrix * ScaleMatrix;

	return Model;
}


world_model::world_model() :
	Position(vec3(0.0f, 0.0f, 0.0f)),
	Scale(vec3(1.0f, 1.0f, 1.0f)),
	Rotation(vec3(0.0f, 0.0f, 0.0f))
{
	Update();
}

world_model::world_model(vec3 Position, vec3 Scale, vec3 Rotation) :
	Model(),
	Position(Position),
	Scale(Scale),
	Rotation(Rotation)
{
	Update();
}

void world_model::Update()
{
	Model = XMMatrixIdentity();

	XMMATRIX ScaleMatrix = XMMatrixScaling(Scale.x, Scale.y, Scale.z);

	XMMATRIX TranslationMatrix = XMMatrixTranslation(Position.x, Position.y, Position.z);

	XMMATRIX RotationInX = XMMatrixRotationAxis(const_rotation_vectors::RotationVectorAxisX, DegreeToRadian(Rotation.x));
	XMMATRIX RotationInY = XMMatrixRotationAxis(const_rotation_vectors::RotationVectorAxisY, DegreeToRadian(Rotation.y));
	XMMATRIX RotationInZ = XMMatrixRotationAxis(const_rotation_vectors::RotationVectorAxisZ, DegreeToRadian(Rotation.z));

	XMMATRIX RotationMatrix = RotationInX * RotationInY * RotationInZ;

	Model = Model * RotationMatrix * TranslationMatrix * ScaleMatrix;
}

XMMATRIX &world_model::GetMatrix()
{
	return Model;
}
