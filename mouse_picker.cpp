#include "mouse_picker.h"

mouse_picker::mouse_picker(world *World, terrain *Terrain, camera *Camera) :
	World(World),
	CurrentMousePositionInWorld(vec2(0.0f, 0.0f)),
	Terrain(Terrain),
	Camera(Camera)
{
}

void mouse_picker::RayTriangleIntersectWork()
{
	vec2 NewMousePositionInWorld(0.0f, 0.0f);

	XMMATRIX WorldModel, View, Projection;

	WorldModel = Terrain->GetModel();
	View = Camera->GetViewMatrix();
	Projection = Camera->GetProjectionMatrix();

	XMVECTOR RayOriginScreen, RayDirectionScreen;
	XMVECTOR RayOrigin, RayDirection;

	RayOriginScreen = XMVectorSet(GetMouseX(), GetMouseY(), 0.0f, 1.0f);
	RayDirectionScreen = XMVectorSet(GetMouseX(), GetMouseY(), 1.0f, 1.0f);

	// TODO(Cristoffer): Get proper screen size.
	RayOrigin = XMVector3Unproject(RayOriginScreen, 0.0f, 0.0f, 1920.0f, 1080.0f, 0.0f, 1.0f, Projection, View, WorldModel);
	RayDirection = XMVector3Unproject(RayDirectionScreen, 0.0f, 0.0f, 1920.0f, 1080.0f, 0.0f, 1.0f, Projection, View, WorldModel);

	RayDirection = XMVector3Normalize(RayDirection - RayOrigin);

	// NOTE(Cristoffer): DX SimpleMath library for calculating the ray 
	//intersection with triangle geometry.
	SimpleMath::Ray Ray(RayOrigin, RayDirection);

	bool32 CollisionFound = false;

	// NOTE(Cristoffer): Index in the vertex buffer where the intersection is found.
	uint32 PlaneCollisionIndex = 0;

	// NOTE(Cristoffer): Distance to the intersection (from origin).
	real32 Distance;

	for(uint64 Index = 0; Index < Terrain->GetVertexData().size(); Index += 4)
	{
		XMFLOAT3 V0, V1, V2, V3;
		V0.x = Terrain->GetVertexData().at(Index + 0).Position.x;
		V0.y = Terrain->GetVertexData().at(Index + 0).Position.y;
		V0.z = Terrain->GetVertexData().at(Index + 0).Position.z;
		V1.x = Terrain->GetVertexData().at(Index + 1).Position.x;
		V1.y = Terrain->GetVertexData().at(Index + 1).Position.y;
		V1.z = Terrain->GetVertexData().at(Index + 1).Position.z;
		V2.x = Terrain->GetVertexData().at(Index + 2).Position.x;
		V2.y = Terrain->GetVertexData().at(Index + 2).Position.y;
		V2.z = Terrain->GetVertexData().at(Index + 2).Position.z;
		V3.x = Terrain->GetVertexData().at(Index + 3).Position.x;
		V3.y = Terrain->GetVertexData().at(Index + 3).Position.y;
		V3.z = Terrain->GetVertexData().at(Index + 3).Position.z;

		// NOTE(Cristoffer): Do the intersection test with triangle coordinates.
		if(Ray.Intersects(V0, V1, V2, Distance) ||
		   Ray.Intersects(V1, V3, V2, Distance))
		{
			CollisionFound = true;
			PlaneCollisionIndex = Index;
			break;
		}
	}

	// NOTE(Cristoffer): Since we got no collision, remove highlight from the current position.
	if(!CollisionFound)
	{
		Terrain->UpdateTileHighlighResource(World->GetWidth(), (int32)CurrentMousePositionInWorld.x, (int32)CurrentMousePositionInWorld.y, 0.0f);

		return;
	}

	NewMousePositionInWorld = Terrain->GetWorldCoordinate(PlaneCollisionIndex);
	
	// NOTE(Cristoffer): Check if the mouse is on same coordinate as before, or at same.
	// Update as needed.
	bool IsOldLocation = (NewMousePositionInWorld.x == CurrentMousePositionInWorld.x && 
						  NewMousePositionInWorld.y == CurrentMousePositionInWorld.y);

	if(!IsOldLocation)
	{
		// NOTE(Cristoffer): Since mouse have moved to new world coordinate, remove the
		// old tile highlight effect, and highlight the new tile.
		Terrain->UpdateTileHighlighResource(World->GetWidth(), (int32)CurrentMousePositionInWorld.x, (int32)CurrentMousePositionInWorld.y, 0.0f);
		Terrain->UpdateTileHighlighResource(World->GetWidth(), (int32)NewMousePositionInWorld.x, (int32)NewMousePositionInWorld.y, 1.0f);

		CurrentMousePositionInWorld.x = NewMousePositionInWorld.x;
		CurrentMousePositionInWorld.y = NewMousePositionInWorld.y;
	}
}

void mouse_picker::TestMouseCollision()
{
	global_data_collector::CurrentlyPickedTileX = CurrentMousePositionInWorld.x;
	global_data_collector::CurrentlyPickedTileY = CurrentMousePositionInWorld.y;

	if(USE_MULTI_THREADING)
	{
		if(thread_pool.WorkDone(ThreadWorkID))
		{
			thread_pool.AddBackgroundWork(ThreadWorkID, [&]
			{
				RayTriangleIntersectWork();
			});
		}
	}
	else
	{
		RayTriangleIntersectWork();
	}
}

vec2 &mouse_picker::GetMousePositionInWorld()
{
	return CurrentMousePositionInWorld;
}