#include "camera.h"

XMMATRIX camera::View;
XMMATRIX camera::Projection;
XMMATRIX camera::Ortho;

XMFLOAT3 camera::Position;
XMFLOAT3 camera::ViewDirection;
XMFLOAT3 camera::UpDirection;
XMFLOAT3 camera::SideDirection;

real32 camera::FieldOfView;
real32 camera::AspectRatio;
real32 camera::NearZ;
real32 camera::FarZ;

bool32 camera::InputDisabled = 0;

void camera::Init()
{
	// TODO(Cristoffer): Perhaps need different projections when doing UI stuff later.

	Position = XMFLOAT3(50.0f, 60.0f, 0.0f);
	ViewDirection = XMFLOAT3(0.0f, 0.0f, 1.0f);
	UpDirection = XMFLOAT3(0.0f, 1.0f, 0.0f);
	SideDirection = XMFLOAT3(1.0f, 0.0f, 0.0f);

	FieldOfView = 70.0f;
	AspectRatio = direct3d::GetBufferWidth() / direct3d::GetBufferHeight();
	NearZ = 0.1f;
	FarZ = 1000.0f;

	LookY(0.6f);

	Projection = XMMatrixPerspectiveFovLH(FieldOfView, AspectRatio, NearZ, FarZ);

	Ortho = XMMatrixOrthographicLH(direct3d::GetBufferWidth(), direct3d::GetBufferHeight(), NearZ, FarZ);

	Update();
}

void camera::DisableInput()
{
	InputDisabled = 1;
}

void camera::EnableInput()
{
	InputDisabled = 0;
}

void camera::SetPosition(real32 X, real32 Y, real32 Z)
{
	if(InputDisabled) return;

	Position = XMFLOAT3(X, Y, Z);

	Update();
}

void camera::PanForward(real32 Value)
{
	if(InputDisabled) return;

	// NOTE(Cristoffer): To get a 45 degree angle on the pan.
	XMFLOAT3 PanAxis = XMFLOAT3(1.0f, 0.0f, 1.0f);

	XMVECTOR PanDirection = XMVector3Cross(XMLoadFloat3(&PanAxis), XMLoadFloat3(&UpDirection));

	PanDirection = XMVectorScale(PanDirection, Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorAdd(OldPosition, PanDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::PanBackward(real32 Value)
{
	if(InputDisabled) return;

	// NOTE(Cristoffer): To get a 45 degree angle on the pan.
	XMFLOAT3 PanAxis = XMFLOAT3(1.0f, 0.0f, 1.0f);

	XMVECTOR PanDirection = XMVector3Cross(XMLoadFloat3(&PanAxis), XMLoadFloat3(&UpDirection));

	PanDirection = XMVectorScale(PanDirection, -Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorAdd(OldPosition, PanDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::PanLeft(real32 Value)
{
	if(InputDisabled) return;

	// NOTE(Cristoffer): To get a 45 degree angle on the pan.
	XMFLOAT3 PanAxis = XMFLOAT3(-1.0f, 0.0f, 1.0f);

	XMVECTOR PanDirection = XMVector3Cross(XMLoadFloat3(&PanAxis), XMLoadFloat3(&UpDirection));

	PanDirection = XMVectorScale(PanDirection, Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorAdd(OldPosition, PanDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::PanRight(real32 Value)
{
	if(InputDisabled) return;

	// NOTE(Cristoffer): To get a 45 degree angle on the pan.
	XMFLOAT3 PanAxis = XMFLOAT3(-1.0f, 0.0f, 1.0f);

	XMVECTOR PanDirection = XMVector3Cross(XMLoadFloat3(&PanAxis), XMLoadFloat3(&UpDirection));

	PanDirection = XMVectorScale(PanDirection, -Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorAdd(OldPosition, PanDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::MoveForward(real32 Value)
{
	if(InputDisabled) return;

	XMVECTOR ScaledViewDirection = XMVectorScale(XMLoadFloat3(&ViewDirection), Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);

	XMVECTOR NewPosition = XMVectorAdd(OldPosition, ScaledViewDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::MoveBackward(real32 Value)
{
	if(InputDisabled) return;

	XMVECTOR ScaledViewDirection = XMVectorScale(XMLoadFloat3(&ViewDirection), Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);

	XMVECTOR NewPosition = XMVectorSubtract(OldPosition, ScaledViewDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::StrafeLeft(real32 Value)
{
	if(InputDisabled) return;

	XMVECTOR StrafeDirection = XMVector3Cross(XMLoadFloat3(&ViewDirection), XMLoadFloat3(&UpDirection));

	StrafeDirection = XMVectorScale(StrafeDirection, Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorAdd(OldPosition, StrafeDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::StrafeRight(real32 Value)
{
	if(InputDisabled) return;

	XMVECTOR StrafeDirection = XMVector3Cross(XMLoadFloat3(&ViewDirection), XMLoadFloat3(&UpDirection));

	StrafeDirection = XMVectorScale(StrafeDirection, Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorSubtract(OldPosition, StrafeDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::MoveUp(real32 Value)
{
	if(InputDisabled) return;

	XMVECTOR Scale = XMVectorScale(XMLoadFloat3(&UpDirection), Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorAdd(OldPosition, Scale);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::MoveDown(real32 Value)
{
	if(InputDisabled) return;

	XMVECTOR Scale = XMVectorScale(XMLoadFloat3(&UpDirection), Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorSubtract(OldPosition, Scale);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::LookX(real32 Value)
{
	if(InputDisabled) return;

	XMMATRIX RotationMatrix = XMMatrixRotationAxis(FXMVECTOR(XMLoadFloat3(&UpDirection)), Value);

	XMVECTOR OldViewDirection = FXMVECTOR(XMLoadFloat3(&ViewDirection));
	XMVECTOR NewViewDirection = XMVector3Transform(OldViewDirection, RotationMatrix);

	XMStoreFloat3(&ViewDirection, NewViewDirection);

	Update();
}

void camera::LookY(real32 Value)
{
	if(InputDisabled) return;

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

real32 camera::GetPositionX()
{
	return Position.x;
}

real32 camera::GetPositionY()
{
	return Position.y;
}

real32 camera::GetPositionZ()
{
	return Position.z;
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
	return Ortho;
}
