#include "entity.h"

entity::entity() :
	ID(0),
	Simulated(1),
	Collidable(0),
	Alive(1),
	WorldModel(new world_model())
{
}

entity::~entity()
{
	delete WorldModel;
}

void entity::SetID(uint32 ID)
{
	this->ID = ID;
}

void entity::SetAlive(bool32 Set)
{
	this->Alive = Set;
}

void entity::SetSimulated(bool32 Set)
{
	this->Simulated = Set;
}

void entity::SetCollidable(bool32 Set)
{
	this->Collidable = Set;
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