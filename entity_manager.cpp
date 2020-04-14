#include "entity_manager.h"

uint32 entity_manager::EntityCount;
std::stack<uint32> entity_manager::InactiveID;
std::unique_ptr<entity> entity_manager::Entity[];

void entity_manager::Init()
{
	EntityCount = 0;

	// NOTE(Cristoffer): Generate ID's.
	for(uint32 Index = 0;
		Index < MAX_ENTITIES;
		Index++)
	{
		InactiveID.push(Index);
		Entity[Index] = nullptr;
	}
}

uint32 entity_manager::NewEntityID()
{
	uint32 Result = 0;

	if(InactiveID.size() > 0)
	{
		Result = InactiveID.top();

		InactiveID.pop();
	}

	return Result;
}

uint32 entity_manager::CreateEntity(vec3 Position, entity_type Type)
{
	if(GetEntityCount() >= MAX_ENTITIES)
	{
		// TODO(Cristoffer): Handle the case of too many entities!
		SystemMessage("Error! Tried to create entity over the max limit!");
		return 0;
	}

	uint32 ID = NewEntityID();

	if(ID > 0 && ID <= MAX_ENTITIES)
	{
		std::string Message = "[" + std::to_string(ID) + "] Entity  created.";
		SystemMessage(Message);

		switch(Type)
		{
			case entity_type::Vehicle:	
			
			Entity[ID] = std::make_unique<vehicle>(ID, vec3(0.0f, 0.0f, 0.0f)); 
			break;

			case entity_type::Car:		
			
			Entity[ID] = std::make_unique<vehicle>(ID, vec3(0.0f, 0.0f, 0.0f)); 
			break;
		}

		EntityCount++;
	}

	return ID;
}

void entity_manager::Simulate()
{
	logger::LogUINT(EntityCount, logger::ref::EntityCount);

	for(uint32 Index = 0;
		Index < MAX_ENTITIES;
		Index++)
	{
		if(Entity[Index] != nullptr)
		{
			Entity[Index].get()->Update();
		}
	}
}

void entity_manager::ReleaseEntity(uint32 ID)
{
	if(ID <= MAX_ENTITIES)
	{
		std::string Message = "[" + std::to_string(ID) + "] Entity  deleted.";
		SystemMessage(Message);

		Entity[ID].release();
		Entity[ID] = nullptr;
		InactiveID.push(ID);
		EntityCount--;
	}
}

uint32 entity_manager::GetEntityCount()
{
	return EntityCount;
}
