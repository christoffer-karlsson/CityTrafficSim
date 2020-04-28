#include "camera.h"

void camera::Init()
{
	Position = XMFLOAT3(50.0f, 60.0f, 0.0f);
	ViewDirection = XMFLOAT3(0.0f, 0.0f, 1.0f);
	UpDirection = XMFLOAT3(0.0f, 1.0f, 0.0f);
	SideDirection = XMFLOAT3(1.0f, 0.0f, 0.0f);

	FieldOfView = 70.0f;
	AspectRatio = d3d_api::GetBufferWidth() / d3d_api::GetBufferHeight();
	NearZ = 0.1f;
	FarZ = 1000.0f;

	LookY(0.6f);

	Projection = XMMatrixPerspectiveFovLH(FieldOfView, AspectRatio, NearZ, FarZ);

	Orthographic = XMMatrixOrthographicLH(d3d_api::GetBufferWidth(), d3d_api::GetBufferHeight(), NearZ, FarZ);

	Update();
}

void camera::SetPosition(real32 X, real32 Y, real32 Z)
{
	Position = XMFLOAT3(X, Y, Z);

	Update();
}

void camera::MoveForward(real32 Value)
{
	XMVECTOR ScaledViewDirection = XMVectorScale(XMLoadFloat3(&ViewDirection), Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);

	XMVECTOR NewPosition = XMVectorAdd(OldPosition, ScaledViewDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::MoveBackward(real32 Value)
{
	XMVECTOR ScaledViewDirection = XMVectorScale(XMLoadFloat3(&ViewDirection), Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);

	XMVECTOR NewPosition = XMVectorSubtract(OldPosition, ScaledViewDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::MoveLeft(real32 Value)
{
	XMVECTOR StrafeDirection = XMVector3Cross(XMLoadFloat3(&ViewDirection), XMLoadFloat3(&UpDirection));

	StrafeDirection = XMVectorScale(StrafeDirection, Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorAdd(OldPosition, StrafeDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::MoveRight(real32 Value)
{
	XMVECTOR StrafeDirection = XMVector3Cross(XMLoadFloat3(&ViewDirection), XMLoadFloat3(&UpDirection));

	StrafeDirection = XMVectorScale(StrafeDirection, Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorSubtract(OldPosition, StrafeDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::MoveUp(real32 Value)
{
	XMVECTOR Scale = XMVectorScale(XMLoadFloat3(&UpDirection), Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorAdd(OldPosition, Scale);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::MoveDown(real32 Value)
{
	XMVECTOR Scale = XMVectorScale(XMLoadFloat3(&UpDirection), Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorSubtract(OldPosition, Scale);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::LookX(real32 Value)
{
	XMMATRIX RotationMatrix = XMMatrixRotationAxis(FXMVECTOR(XMLoadFloat3(&UpDirection)), Value);

	XMVECTOR OldViewDirection = FXMVECTOR(XMLoadFloat3(&ViewDirection));
	XMVECTOR NewViewDirection = XMVector3Transform(OldViewDirection, RotationMatrix);

	XMStoreFloat3(&ViewDirection, NewViewDirection);

	Update();
}

void camera::LookY(real32 Value)
{
	XMVECTOR RotationAxis = XMVector3Cross(XMLoadFloat3(&ViewDirection), XMLoadFloat3(&UpDirection));

	XMMATRIX RotationMatrix = XMMatrixRotationAxis(RotationAxis, -Value);

	XMVECTOR OldViewDirection = FXMVECTOR(XMLoadFloat3(&ViewDirection));
	XMVECTOR NewViewDirection = XMVector3Transform(OldViewDirection, RotationMatrix);

	XMStoreFloat3(&ViewDirection, NewViewDirection);

	Update();
}

void camera::Update()
{
	View = XMMatrixLookAtLH(FXMVECTOR(XMLoadFloat3(&Position)),
		XMVectorAdd(FXMVECTOR(XMLoadFloat3(&Position)), FXMVECTOR(XMLoadFloat3(&ViewDirection))),
		FXMVECTOR(XMLoadFloat3(&UpDirection)));
}

vec3 camera::GetPosition()
{
	return { Position.x, Position.y, Position.z };
}

const XMMATRIX &camera::GetViewMatrix()
{
	return View;
}

const XMMATRIX &camera::GetProjectionMatrix()
{
	return Projection;
}

const XMMATRIX &camera::GetOrthographicMatrix()
{
	return Orthographic;
}

void R_SetActiveCamera(camera &Camera)
{
	ActiveCamera = &Camera;
}

void camera_pan::MoveForward(real32 Value)
{
	// To get a 45 degree angle on the pan.
	XMFLOAT3 PanAxis = XMFLOAT3(1.0f, 0.0f, 1.0f);

	XMVECTOR PanDirection = XMVector3Cross(XMLoadFloat3(&PanAxis), XMLoadFloat3(&UpDirection));

	PanDirection = XMVectorScale(PanDirection, Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorAdd(OldPosition, PanDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera_pan::MoveBackward(real32 Value)
{
	// To get a 45 degree angle on the pan.
	XMFLOAT3 PanAxis = XMFLOAT3(1.0f, 0.0f, 1.0f);

	XMVECTOR PanDirection = XMVector3Cross(XMLoadFloat3(&PanAxis), XMLoadFloat3(&UpDirection));

	PanDirection = XMVectorScale(PanDirection, -Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorAdd(OldPosition, PanDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera_pan::MoveLeft(real32 Value)
{
	// To get a 45 degree angle on the pan.
	XMFLOAT3 PanAxis = XMFLOAT3(-1.0f, 0.0f, 1.0f);

	XMVECTOR PanDirection = XMVector3Cross(XMLoadFloat3(&PanAxis), XMLoadFloat3(&UpDirection));

	PanDirection = XMVectorScale(PanDirection, Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorAdd(OldPosition, PanDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera_pan::MoveRight(real32 Value)
{
	// To get a 45 degree angle on the pan.
	XMFLOAT3 PanAxis = XMFLOAT3(-1.0f, 0.0f, 1.0f);

	XMVECTOR PanDirection = XMVector3Cross(XMLoadFloat3(&PanAxis), XMLoadFloat3(&UpDirection));

	PanDirection = XMVectorScale(PanDirection, -Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorAdd(OldPosition, PanDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}
