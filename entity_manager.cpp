#include "entity_manager.h"

entity_manager::entity_manager()
{
	for(uint32 Index = 0;
		Index < MAX_ENTITIES_ALLOWED;
		Index++)
	{
		AvailableID.push(Index);
	}
}

entity_manager::~entity_manager()
{

}

uint32 entity_manager::NewEntityID()
{
	uint32 Result = 0;

	if(AvailableID.size() > 0)
	{
		Result = AvailableID.top();

		AvailableID.pop();
	}

	return Result;
}

void entity_manager::ReleaseEntityID(uint64 Index)
{
	uint32 ReleasedID = Entity.at(Index).get()->GetID();

	AvailableID.push(ReleasedID);
}

void entity_manager::CreateVehicle(vec3 Position)
{
	if(GetEntityCount() >= MAX_ENTITIES_ALLOWED)
	{
		// TODO(Cristoffer): Handle the case of too many entities!
		return;
	}

	Entity.push_back(std::make_unique<vehicle>(NewEntityID(), Position));
}

void entity_manager::Simulate()
{
	
}

uint64 entity_manager::GetEntityCount()
{
	return Entity.size();
}
