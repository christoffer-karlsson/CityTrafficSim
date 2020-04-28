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

	// TODO: Implement a way to look up assets via text. 
	Mesh[asset_mesh_car] = new mesh(Persistence.LoadObjectFile("car.obj"), 0);
	Mesh[asset_mesh_car_indexed] = new mesh(Persistence.LoadObjectFile("car.obj"), 1);
	Mesh[asset_mesh_building] = new mesh(Persistence.LoadObjectFile("building.obj"), 0);
	Mesh[asset_mesh_building_indexed] = new mesh(Persistence.LoadObjectFile("building.obj"), 1);
}

mesh *asset_manager::GetMesh(asset_id ID)
{
	mesh *Result = nullptr;

	if(ID > 0 || ID < MAX_MODEL_FILES)
	{
		Result = Mesh[ID];
	}

	return Result;
}