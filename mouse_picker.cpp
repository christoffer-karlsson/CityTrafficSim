#include "mouse_picker.h"

mouse_picker::mouse_picker() :
	MousePositionInWorld({ 0, 0 }),
	Terrain(nullptr),
	Camera(nullptr)
{
}

mouse_picker::mouse_picker(terrain *Terrain, camera *Camera) :
	MousePositionInWorld({ 0, 0 }),
	Terrain(Terrain),
	Camera(Camera)
{
}

void mouse_picker::RayTriangleIntersectWork()
{
	position NewMousePositionInWorld = { 0, 0 };

	XMMATRIX World, View, Projection;

	World = Terrain->GetModel();
	View = Camera->GetViewMatrix();
	Projection = Camera->GetProjectionMatrix();

	XMVECTOR RayOriginScreen, RayDirectionScreen;
	XMVECTOR RayOrigin, RayDirection;

	RayOriginScreen = XMVectorSet(GetMouseX(), GetMouseY(), 0.0f, 1.0f);
	RayDirectionScreen = XMVectorSet(GetMouseX(), GetMouseY(), 1.0f, 1.0f);

	RayOrigin = XMVector3Unproject(RayOriginScreen, 0.0f, 0.0f, 1920.0f, 1080.0f, 0.0f, 1.0f, Projection, View, World);
	RayDirection = XMVector3Unproject(RayDirectionScreen, 0.0f, 0.0f, 1920.0f, 1080.0f, 0.0f, 1.0f, Projection, View, World);

	RayDirection = XMVector3Normalize(RayDirection - RayOrigin);

	SimpleMath::Ray Ray(RayOrigin, RayDirection);

	for(uint32 Index = 0; Index < Terrain->GetVertexData().size(); Index += 4)
	{
		XMFLOAT3 V0, V1, V2, V3;
		V0.x = Terrain->GetVertexData().at(Index + 0).Position.X;
		V0.y = Terrain->GetVertexData().at(Index + 0).Position.Y;
		V0.z = Terrain->GetVertexData().at(Index + 0).Position.Z;
		V1.x = Terrain->GetVertexData().at(Index + 1).Position.X;
		V1.y = Terrain->GetVertexData().at(Index + 1).Position.Y;
		V1.z = Terrain->GetVertexData().at(Index + 1).Position.Z;
		V2.x = Terrain->GetVertexData().at(Index + 2).Position.X;
		V2.y = Terrain->GetVertexData().at(Index + 2).Position.Y;
		V2.z = Terrain->GetVertexData().at(Index + 2).Position.Z;
		V3.x = Terrain->GetVertexData().at(Index + 3).Position.X;
		V3.y = Terrain->GetVertexData().at(Index + 3).Position.Y;
		V3.z = Terrain->GetVertexData().at(Index + 3).Position.Z;

		real32 Distance;

		// NOTE(Cristoffer): Do the intersection test with triangle coordinates.
		if(Ray.Intersects(V0, V1, V2, Distance) ||
		   Ray.Intersects(V1, V3, V2, Distance))
		{
			NewMousePositionInWorld = Terrain->GetWorldCoordinate(Index);

			break;
		}
	}
	
	// NOTE(Cristoffer): Check if the mouse is on same coordinate as before, or at same.
	// Update as needed.
	bool IsOldLocation = (NewMousePositionInWorld.X == MousePositionInWorld.X && 
						  NewMousePositionInWorld.Y == MousePositionInWorld.Y);

	if(!IsOldLocation)
	{
		// NOTE(Cristoffer): Since mouse have moved to new world coordinate, remove the
		// old tile highlight effect, and highlight the new tile.
		Terrain->UpdateTileHighlighResource((int32)MousePositionInWorld.X, (int32)MousePositionInWorld.Y, 0.0f);
		Terrain->UpdateTileHighlighResource((int32)NewMousePositionInWorld.X, (int32)NewMousePositionInWorld.Y, 1.0f);

		MousePositionInWorld.X = NewMousePositionInWorld.X;
		MousePositionInWorld.Y = NewMousePositionInWorld.Y;
	}
}

void mouse_picker::Init(terrain *Terrain, camera *Camera)
{
	this->Terrain = Terrain;
	this->Camera = Camera;
}

void mouse_picker::TestMouseCollision()
{
	global_data_collector::CurrentlyPickedTileX = MousePositionInWorld.X;
	global_data_collector::CurrentlyPickedTileY = MousePositionInWorld.Y;

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

position &mouse_picker::GetMousePositionInWorld()
{
	return MousePositionInWorld;
}