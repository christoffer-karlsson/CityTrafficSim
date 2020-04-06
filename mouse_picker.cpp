#include "mouse_picker.h"

/*void mouse_picker::Update()
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
}*/

real32 mouse_picker::GetRayX() const
{
	return X;
}

real32 mouse_picker::GetRayY() const
{
	return Y;
}

real32 mouse_picker::GetRayZ() const
{
	return Z;
}

void mouse_picker::TestIntersection()
{
	XMMATRIX World, View, Projection;

	World = XMMatrixIdentity();
	View = Camera->GetViewMatrix();
	Projection = Camera->GetProjectionMatrix();

	XMVECTOR RayOriginScreen, RayDirectionScreen;
	XMVECTOR RayOrigin, RayDirection;

	RayOriginScreen = XMVectorSet(GetMouseX(),GetMouseY(), 0.0f, 1.0f);
	RayDirectionScreen = XMVectorSet(GetMouseX(), GetMouseY(), 1.0f, 1.0f);

	RayOrigin = XMVector3Unproject(RayOriginScreen, 0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 1.0f, Projection, View, World);
	RayDirection = XMVector3Unproject(RayDirectionScreen, 0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 1.0f, Projection, View, World);

	RayDirection = XMVector3Normalize(RayDirection - RayOrigin);

	SimpleMath::Ray Ray(RayOrigin, RayDirection);

	bool RayHit = false;

	//for(size_t TriIndex = 0; TriIndex < billboard2.size(); TriIndex++)
	//{
		//real32 Distance;

		//RayHit = Ray.Intersects();
	//}

	//XMFLOAT3 IntersectionVector;
	//XMStoreFloat3(&IntersectionVector, XMVectorAdd(RayOrigin, RayDirection) * 10.0f);

	//XMFLOAT3 Test;
	//XMStoreFloat3(&Test, RayDirection);

	//X = IntersectionVector.x;
	//Y = IntersectionVector.y;
	//Z = IntersectionVector.z;
	//X = Ray.position.x;
	//Y = Ray.position.y;
	//Z = Ray.position.z;
}

mouse_picker::mouse_picker(camera *Camera) :
	Camera(Camera)
{
}