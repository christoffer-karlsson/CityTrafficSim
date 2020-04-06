#include "mouse_picker.h"

void mouse_picker::Update()
{
	// NOTE(Cristoffer): Normalise mouse window coordinate.
	real32 X = (2.0f * GetMouseX()) / global_device_info::FrameBufferWidth - 1.0f;
	real32 Y = 1.0f - (2.0f * GetMouseY()) / global_device_info::FrameBufferHeight;
	real32 Z = 1.0f;

	RayNormalised.x = X;
	RayNormalised.y = Y;
	RayNormalised.z = Z;

	// NOTE(Cristoffer): Make the ray point forward.
	RayClip = XMFLOAT4(RayNormalised.x, RayNormalised.y, -1.0f, 1.0f);

	// NOTE(Cristoffer): Inverse Camera Projection Matrx * RayClip Vector
	// This is to get from camera space to clip space.
	FXMVECTOR RayClipVector = FXMVECTOR(XMLoadFloat4(&RayClip));
	XMMATRIX InverseCameraProjection = XMMatrixInverse(nullptr, Camera->GetProjectionMatrix());
	FXMVECTOR RayClipTransform = XMVector4Transform(RayClipVector, InverseCameraProjection);
	XMStoreFloat4(&RayCamera, RayClipTransform);

	// NOTE(Cristoffer): Inverse Camera View Matrx * RayEye Vector
	FXMVECTOR RayCameraVector = FXMVECTOR(XMLoadFloat4(&RayCamera));
	XMMATRIX InverseCameraView = XMMatrixInverse(nullptr, Camera->GetViewMatrix());
	FXMVECTOR RayCameraTransform = XMVector4Transform(RayCameraVector, InverseCameraProjection);
	XMStoreFloat3(&RayWorld, RayCameraTransform);

	// NOTE(Cristoffer): RayWorld = Normalize(RayWorld)
	FXMVECTOR RayWorldVector = FXMVECTOR(XMLoadFloat3(&RayWorld));
	FXMVECTOR RayWorldNormalized = XMVector3Normalize(RayWorldVector);
	XMStoreFloat3(&RayWorld, RayWorldNormalized);

	//XMVector3Unproject
}

real32 mouse_picker::GetRayX() const
{
	return RayWorld.x;
}

real32 mouse_picker::GetRayY() const
{
	return RayWorld.y;
}

real32 mouse_picker::GetRayZ() const
{
	return RayWorld.z;
}

mouse_picker::mouse_picker(camera *Camera)
{
	this->Camera = Camera;
}