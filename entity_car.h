#pragma once

#include "common.h"
#include "entity.h"

class entity_car : public entity
{
	private:

	drawable_cars *Drawable;

	vec4 Color;

	real32 Speed;

	real32 Angle;

	public:

	entity_car(uint32 ID, vec3 Position);

	void Update() override;
};