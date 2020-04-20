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
	Mesh[0] = new mesh(Persistence.LoadObjectFile("car.obj"));
	Mesh[1] = new mesh(Persistence.LoadObjectFile("building.obj"));
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