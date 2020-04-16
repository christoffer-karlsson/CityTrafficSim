#include "entity.h"

entity::entity() :
	ID(0),
	Simulated(true),
	Collidable(false),
	Alive(true),
	Drawable(nullptr)
{
}

entity::~entity()
{
	delete Drawable;
}

void entity::SetID(uint32 ID)
{
	this->ID = ID;
}

void entity::SetAlive(bool32 Set)
{
	this->Alive = Set;
}

void entity::SetDrawable(drawable *Drawable)
{
	this->Drawable = Drawable;
}

vec3 &entity::GetPosition()
{
	return Drawable->GetPosition();
}

vec3 &entity::GetRotation()
{
	return Drawable->GetRotation();
}

vec3 &entity::GetScale()
{
	return Drawable->GetScale();
}

void entity::SetSimulated(bool32 Set)
{
	this->Simulated = Set;
}

void entity::SetCollidable(bool32 Set)
{
	this->Collidable = Set;
}

void entity::SetPosition(vec3 Position)
{
	this->Drawable->SetPosition(Position);
}

void entity::SetRotation(vec3 Angle)
{
	this->Drawable->SetRotation(Angle);
}

void entity::SetScale(vec3 Scale)
{
	this->Drawable->SetScale(Scale);
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

drawable *entity::GetDrawable()
{
	return Drawable;
}

void entity::UpdateDrawable()
{
	Drawable->Update();
}
