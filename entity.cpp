#include "entity.h"

entity::entity() :
	ID(0),
	Position(vec3()),
	Scale(0.0f),
	Rotation(0.0f),
	Simulated(true),
	Collidable(false),
	Alive(true),
	Drawable(nullptr)
{
}

void entity::SetID(uint32 ID)
{
	this->ID = ID;
}

void entity::SetAlive(bool32 Set)
{
	this->Alive = Set;
}

void entity::SetScale(real32 Scale)
{
	this->Scale = Scale;
}

void entity::SetSimulated(bool32 Set)
{
	this->Simulated = Set;
}

void entity::SetRotation(real32 Angle)
{
	this->Rotation = Angle;
}

void entity::SetCollidable(bool32 Set)
{
	this->Collidable = Set;
}

void entity::SetPosition(vec3 Position)
{
	this->Position = Position;
}

uint32 entity::GetID()
{
	return ID;
}

bool32 entity::GetAlive()
{
	return Alive;
}

bool32 entity::GetSimulated()
{
	return Simulated;
}

bool32 entity::GetCollidable()
{
	return Collidable;
}
