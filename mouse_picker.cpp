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

void mouse_picker::RayTriangleIntersectWork(mouse_picker *Instance)
{
	position NewMousePositionInWorld = { 0, 0 };

	XMMATRIX World, View, Projection;

	World = Instance->Terrain->GetModel();
	View = Instance->Camera->GetViewMatrix();
	Projection = Instance->Camera->GetProjectionMatrix();

	XMVECTOR RayOriginScreen, RayDirectionScreen;
	XMVECTOR RayOrigin, RayDirection;

	RayOriginScreen = XMVectorSet(GetMouseX(), GetMouseY(), 0.0f, 1.0f);
	RayDirectionScreen = XMVectorSet(GetMouseX(), GetMouseY(), 1.0f, 1.0f);

	RayOrigin = XMVector3Unproject(RayOriginScreen, 0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 1.0f, Projection, View, World);
	RayDirection = XMVector3Unproject(RayDirectionScreen, 0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 1.0f, Projection, View, World);

	RayDirection = XMVector3Normalize(RayDirection - RayOrigin);

	SimpleMath::Ray Ray(RayOrigin, RayDirection);

	for(size_t Index = 0; Index < Instance->Terrain->GetVertexData().size(); Index += 4)
	{
		XMFLOAT3 V0, V1, V2, V3;
		V0.x = Instance->Terrain->GetVertexData().at(Index + 0).Position.X;
		V0.y = Instance->Terrain->GetVertexData().at(Index + 0).Position.Y;
		V0.z = Instance->Terrain->GetVertexData().at(Index + 0).Position.Z;
		V1.x = Instance->Terrain->GetVertexData().at(Index + 1).Position.X;
		V1.y = Instance->Terrain->GetVertexData().at(Index + 1).Position.Y;
		V1.z = Instance->Terrain->GetVertexData().at(Index + 1).Position.Z;
		V2.x = Instance->Terrain->GetVertexData().at(Index + 2).Position.X;
		V2.y = Instance->Terrain->GetVertexData().at(Index + 2).Position.Y;
		V2.z = Instance->Terrain->GetVertexData().at(Index + 2).Position.Z;
		V3.x = Instance->Terrain->GetVertexData().at(Index + 3).Position.X;
		V3.y = Instance->Terrain->GetVertexData().at(Index + 3).Position.Y;
		V3.z = Instance->Terrain->GetVertexData().at(Index + 3).Position.Z;

		real32 Distance;

		// NOTE(Cristoffer): Do the intersection test with triangle coordinates.
		if(Ray.Intersects(V0, V1, V2, Distance) ||
		   Ray.Intersects(V1, V3, V2, Distance))
		{
			NewMousePositionInWorld = Instance->Terrain->GetWorldCoordinate(Index);

			break;
		}
	}
	
	// NOTE(Cristoffer): Check if the mouse is on same coordinate as before, or at same.
	// Update as needed.
	bool IsOldLocation = (NewMousePositionInWorld.X == Instance->MousePositionInWorld.X && 
						  NewMousePositionInWorld.Y == Instance->MousePositionInWorld.Y);

	if(!IsOldLocation)
	{
		std::lock_guard<std::mutex> Lock(Instance->Mutex);

		// NOTE(Cristoffer): Since mouse have moved to new world coordinate, remove the
		// old tile highlight effect, and highlight the new tile.
		Instance->Terrain->SetTilePicked(Instance->MousePositionInWorld.X, Instance->MousePositionInWorld.Y, 0.0f);
		Instance->Terrain->SetTilePicked(NewMousePositionInWorld.X, NewMousePositionInWorld.Y, 1.0f);

		Instance->MousePositionInWorld.X = NewMousePositionInWorld.X;
		Instance->MousePositionInWorld.Y = NewMousePositionInWorld.Y;
	}

	//using namespace std::literals::chrono_literals;
	//std::this_thread::sleep_for(100ms);

	Instance->ThreadBusy = false;
}

void mouse_picker::Init(terrain *Terrain, camera *Camera)
{
	this->ThreadBusy = false;
	this->Terrain = Terrain;
	this->Camera = Camera;
}

void mouse_picker::TestMouseCollision()
{
	global_data_collector::CurrentlyPickedTileX = MousePositionInWorld.X;
	global_data_collector::CurrentlyPickedTileY = MousePositionInWorld.Y;

	// TODO(Cristoffer): Organize threading.
	if(!ThreadBusy)
	{
		ThreadBusy = true;
		std::thread t(RayTriangleIntersectWork, this);
		t.detach();
	}
}

position &mouse_picker::GetMousePositionInWorld()
{
	return MousePositionInWorld;
}