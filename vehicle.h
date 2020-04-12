#pragma once

#include "common.h"
#include "entity.h"
#include "math.h"
#include "object.h"

class vehicle : public entity
{
	private:

	real32 Speed;

	public:

	vehicle(uint32 ID, vec3 Position);
	~vehicle();

	void Update() override;
};