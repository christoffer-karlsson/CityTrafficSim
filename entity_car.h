#pragma once

#include "common.h"
#include "entity.h"
#include "math.h"
#include "object.h"
#include "asset_manager.h"
#include "render_manager.h"
#include "timing.h"

class entity_car : public entity
{
	private:

	real32 Speed;

	public:

	entity_car(uint32 ID, vec3 Position);

	void Update() override;
};