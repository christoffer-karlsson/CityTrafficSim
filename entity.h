#pragma once

#include "common.h"
#include "math.h"
#include "timing.h"
#include "drawable.h"
#include "render_manager.h"

class entity
{
	private:

	uint32	ID;

	bool32	Simulated;
	bool32	Collidable;
	bool32	Alive;

	protected:

	world_model *WorldModel;

	void SetID(uint32 ID);
	void SetCollidable(bool32 Set);
	void SetSimulated(bool32 Set);
	void SetAlive(bool32 Set);

	public:

	entity();
	~entity();

	virtual void Update() = 0;

	uint32 GetID();
	bool32 GetAlive();
	bool32 GetSimulated();
	bool32 GetCollidable();
};