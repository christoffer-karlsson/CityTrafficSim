#include "asset_manager.h"

obj_file *asset_manager::ObjectFile[];

void asset_manager::Init()
{
	for(uint32 Index = 0;
		Index < MAX_OBJECT_FILES;
		Index++)
	{
		ObjectFile[Index] = nullptr;
	}

	persistence Persistence;

	ObjectFile[0] = Persistence.LoadObjectFile("car.obj");
	ObjectFile[1] = Persistence.LoadObjectFile("building.obj");
}

obj_file *asset_manager::GetObjectFile(uint32 ID)
{
	obj_file *Result = nullptr;

	if(ID > 0 || ID < MAX_OBJECT_FILES)
	{
		Result = ObjectFile[ID];
	}

	return Result;
}