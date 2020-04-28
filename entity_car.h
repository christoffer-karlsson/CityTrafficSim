#pragma once

#include "common.h"
#include "entity.h"
#include "world.h"

typedef enum { south_west, south_east, north_west, north_east } cardinal_dir;
typedef enum { turn_left, turn_right, forward, turn_back } turn_dir;

class entity_car : public entity
{
	private:

	drawable_cars *Drawable;

	vec4 Color;

	const real32 Speed = 1.0f;
	const real32 AngleNorth = 180.0f;
	const real32 AngleSouth = 0.0f;
	const real32 AngleWest = 270.0f;
	const real32 AngleEast = 90.0f;

	bool CrossRoadDecisionMade = false;

	vec3 Waypoint;

	real32 Angle;

	bool CheckIfTileIsRoad(uint32 PositionX, uint32 PositionZ);

	public:

	entity_car(uint32 ID, vec3 Position);

	void Update() override;
};