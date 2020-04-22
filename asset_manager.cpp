#include "asset_manager.h"

mesh *asset_manager::Mesh[];

void asset_manager::Init()
{
	for(uint32 Index = 0;
		Index < MAX_MODEL_FILES;
		Index++)
	{
		Mesh[Index] = nullptr;
	}

	persistence Persistence;

	// TODO(Cristoffer): Implement a way to look up assets via text. 
	Mesh[ASSET_MESH_CAR] = new mesh(Persistence.LoadObjectFile("car.obj"), 0);
	Mesh[ASSET_MESH_CAR_INDEXED] = new mesh(Persistence.LoadObjectFile("car.obj"), 1);
	Mesh[ASSET_MESH_BUILDING] = new mesh(Persistence.LoadObjectFile("building.obj"), 0);
	Mesh[ASSET_MESH_BUILDING_INDEXED] = new mesh(Persistence.LoadObjectFile("building.obj"), 1);
}

mesh *asset_manager::GetMesh(uint32 ID)
{
	mesh *Result = nullptr;

	if(ID > 0 || ID < MAX_MODEL_FILES)
	{
		Result = Mesh[ID];
	}

	return Result;
}