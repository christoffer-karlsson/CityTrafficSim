#include "asset_manager.h"

model *asset_manager::Model[];

void asset_manager::Init()
{
	for(uint32 Index = 0;
		Index < MAX_MODEL_FILES;
		Index++)
	{
		Model[Index] = nullptr;
	}

	persistence Persistence;

	// TODO(Cristoffer): Implement a way to look up assets via text. 
	Model[0] = new model(Persistence.LoadObjectFile("car.obj"));
	Model[1] = new model(Persistence.LoadObjectFile("building.obj"));
}

model *asset_manager::GetModel(uint32 ID)
{
	model *Result = nullptr;

	if(ID > 0 || ID < MAX_MODEL_FILES)
	{
		Result = Model[ID];
	}

	return Result;
}