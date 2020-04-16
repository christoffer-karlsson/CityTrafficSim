#pragma once

#include "common.h"
#include "math.h"
#include "drawable.h"

class entity
{
	private:

	uint32	ID;

	bool32	Simulated;
	bool32	Collidable;
	bool32	Alive;

	drawable *Drawable;

	protected:

	void SetID(uint32 ID);
	void SetPosition(vec3 Position);
	void SetRotation(vec3 Rotation);
	void SetScale(vec3 Scale);
	void SetCollidable(bool32 Set);
	void SetSimulated(bool32 Set);
	void SetAlive(bool32 Set);
	void SetDrawable(drawable *Drawable);

	vec3 &GetPosition();
	vec3 &GetRotation();
	vec3 &GetScale();

	drawable *GetDrawable();

	void UpdateDrawable();

	public:

	entity();
	~entity();

	virtual void Update() = 0;

	uint32 GetID();
	bool32 GetAlive();
	bool32 GetSimulated();
	bool32 GetCollidable();
};