#pragma once

#include "common.h"
#include "vehicle.h"

#include <vector>
#include <stack>

#define MAX_ENTITIES_ALLOWED 1000

class entity_manager
{
	private:

	std::vector<std::unique_ptr<entity>> Entity;

	std::stack<uint32> AvailableID;

	protected:

	uint32	NewEntityID();
	void	ReleaseEntityID(uint64 Index);

	public:

	entity_manager();
	~entity_manager();

	void Simulate();
	void CreateVehicle(vec3 Position);

	uint64 GetEntityCount();
};