#include "camera.h"

camera::camera()
{
	// TODO(Cristoffer): Perhaps need different projections when doing UI stuff later.
	CameraType = CAM_PERSPECTIVE;

	Position = XMFLOAT3(0.0f, 5.0f, -20.0f);
	ViewDirection = XMFLOAT3(0.0f, 0.0f, 1.0f);
	UpDirection = XMFLOAT3(0.0f, 1.0f, 0.0f);
	SideDirection = XMFLOAT3(1.0f, 0.0f, 0.0f);

	FieldOfView = 70.0f;
	AspectRatio = global_device_info::FrameBufferWidth / global_device_info::FrameBufferHeight;
	DrawStartZ = 0.1f;
	DrawDistanceZ = 1000.0f;

	LookY(0.3f);

	if(CameraType == CAM_ORTHOGRAPHIC)
	{
		Projection = XMMatrixOrthographicLH(16.0f, 9.0f, -1.0f, 20.0f);
	}
	else if(CameraType == CAM_PERSPECTIVE)
	{
		Projection = XMMatrixPerspectiveFovLH(FieldOfView, AspectRatio, DrawStartZ, DrawDistanceZ);
	}
	else
	{
		Projection = XMMatrixIdentity();
	}

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

void camera::StrafeLeft(real32 Value)
{
	XMVECTOR StrafeDirection = XMVector3Cross(XMLoadFloat3(&ViewDirection), XMLoadFloat3(&UpDirection));

	StrafeDirection = XMVectorScale(StrafeDirection, Value);

	XMVECTOR OldPosition = XMLoadFloat3(&Position);
	XMVECTOR NewPosition = XMVectorAdd(OldPosition, StrafeDirection);

	XMStoreFloat3(&Position, NewPosition);

	Update();
}

void camera::StrafeRight(real32 Value)
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

real32 camera::GetPositionX() const
{
	return Position.x;
}

real32 camera::GetPositionY() const
{
	return Position.y;
}

real32 camera::GetPositionZ() const
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