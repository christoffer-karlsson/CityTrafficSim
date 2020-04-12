#include "vehicle.h"

vehicle::vehicle(uint32 ID, vec3 Position)
{
	SetID(ID);
	SetPosition(Position);

	this->Speed = 0.0f;

	Drawable = nullptr;
}

vehicle::~vehicle()
{
}

void vehicle::Update()
{
	vec2 V1 = vec2(2.0f, 1.0f);
	vec2 V2 = vec2(5.0f, 3.0f);

	Speed = (V1 * V2) * Speed;
}