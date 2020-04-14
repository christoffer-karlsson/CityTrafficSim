#include "mouse_picker.h"

bool32 mouse_picker::TestMouseCollision(XMMATRIX &Model, std::vector<vec3> &Vertices)
{
	vec2 NewMousePositionInWorld(0.0f, 0.0f);

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
	//intersection with triangle geometry.
	SimpleMath::Ray Ray(RayOrigin, RayDirection);

	// NOTE(Cristoffer): Distance to the intersection (from origin).
	real32 Distance;

	for(uint64 Index = 0; (Index + 3) < Vertices.size(); Index += 3)
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

		// NOTE(Cristoffer): Do the intersection test with triangle coordinates.
		if(Ray.Intersects(V1, V2, V3, Distance))
		{
			// NOTE(Cristoffer): Index in the vertex buffer where the intersection is found.
			CollisionIndex = (uint32)Index;
			
			return 1;
		}
	}

	return 0;
}

uint32 mouse_picker::GetCollisionIndex()
{
	return CollisionIndex;
}
