// entity_manager.h
// Create and manage entities. 
// Returns 0 if entity could not be created.
// Returns entity ID if created successfully.

#pragma once

#include "common.h"
#include "logger.h"
#include "system_message.h"
#include "entity_car.h"

#include <string>
#include <vector>
#include <stack>

#define MAX_ENTITIES 5000

enum class entity_type
{
	Vehicle, Car,
};

// NOTE(Cristoffer): Uses array with indexing and stack to manage 
// IDs. Need fast index look up for entities.
class entity_manager
{
	private:

	static uint32 EntityCount;

	static std::stack<uint32>	   InactiveID;
	static std::unique_ptr<entity> Entity[MAX_ENTITIES];

	protected:

	static uint32 NewEntityID();

	public:

	static void   Init();
	static void   Simulate();
	static uint32 CreateEntity(vec3 Position, entity_type Type);
	static void   ReleaseEntity(uint32 ID);

	static uint32 GetEntityCount();
};