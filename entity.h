#pragma once

#include "common.h"
#include "math.h"
#include "drawable.h"

class entity
{
	private:

	uint32	ID;

	vec3	Position;
	real32	Scale;
	real32	Rotation;

	bool32	Simulated;
	bool32	Collidable;
	bool32	Alive;


	protected:
	drawable *Drawable;

	void SetID(uint32 ID);
	void SetAlive(bool32 Set);
	void SetScale(real32 Scale);
	void SetSimulated(bool32 Set);
	void SetRotation(real32 Angle);
	void SetCollidable(bool32 Set);
	void SetPosition(vec3 Position);

	public:

	entity();

	virtual ~entity()
	{
	};

	virtual void Update() = 0;

	uint32 GetID();
	bool32 GetAlive();
	bool32 GetSimulated();
	bool32 GetCollidable();
};