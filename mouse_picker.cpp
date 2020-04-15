#include "mouse_picker.h"

bool32 mouse_picker::TestMouseCollision(XMMATRIX &Model, std::vector<vec3> &Vertices)
{
	XMMATRIX View, Projection;

	View = camera::GetViewMatrix();
	Projection = camera::GetProjectionMatrix();

	XMVECTOR RayOriginScreen, RayDirectionScreen;
	XMVECTOR RayOrigin, RayDirection;

	RayOriginScreen = XMVectorSet(GetMouseX(), GetMouseY(), 0.0f, 1.0f);
	RayDirectionScreen = XMVectorSet(GetMouseX(), GetMouseY(), 1.0f, 1.0f);

	RayOrigin = XMVector3Unproject(RayOriginScreen, 0.0f, 0.0f, direct3d::GetBufferWidth(), direct3d::GetBufferHeight(), 0.0f, 1.0f, Projection, View, Model);
	RayDirection = XMVector3Unproject(RayDirectionScreen, 0.0f, 0.0f, direct3d::GetBufferWidth(), direct3d::GetBufferHeight(), 0.0f, 1.0f, Projection, View, Model);

	RayDirection = XMVector3Normalize(RayDirection - RayOrigin);

	// NOTE(Cristoffer): DX SimpleMath library for calculating the ray 
	// intersection with triangle geometry.
	SimpleMath::Ray Ray(RayOrigin, RayDirection);
	
	// NOTE(Cristoffer): Iterate and collision test the triangles with the ray.
	for(uint64 Index = 0; Index < Vertices.size(); Index += 3)
	{
		XMFLOAT3 V1, V2, V3;

		V1.x = Vertices.at(Index + 0).x;
		V1.y = Vertices.at(Index + 0).y;
		V1.z = Vertices.at(Index + 0).z;

		V2.x = Vertices.at(Index + 1).x;
		V2.y = Vertices.at(Index + 1).y;
		V2.z = Vertices.at(Index + 1).z;

		V3.x = Vertices.at(Index + 2).x;
		V3.y = Vertices.at(Index + 2).y;
		V3.z = Vertices.at(Index + 2).z;

		real32 Distance;

		// NOTE(Cristoffer): Do the intersection test with triangle coordinates.
		// If intersection found, we get the distance. With the distance we can simply
		// calculate where in the world the intersection happened with the formula:
		// P = Origin + Distance * Direction.
		if(Ray.Intersects(V1, V2, V3, Distance))
		{
			XMVECTOR Position = RayOrigin + Distance * RayDirection;

			XMFLOAT4 Vector;
			XMStoreFloat4(&Vector, Position);

			CollisionPosition = vec3(Vector.x, Vector.y, Vector.z);

			return 1;
		}
	}

	return 0;
}

vec3 mouse_picker::GetCollisionPosition()
{
	return CollisionPosition;
}