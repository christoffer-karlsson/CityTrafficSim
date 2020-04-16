#include "entity_car.h"

entity_car::entity_car(uint32 ID, vec3 Position)
{
	SetID(ID);
	SetCollidable(0);
	SetSimulated(1);
	SetAlive(1);

	SetDrawable(new object(
		asset_manager::GetObjectFile(0),
		Position,
		vec3(1.0f, 1.0f, 1.0f),
		vec3(0.0f, 180.0f, 0.0f),
		vec4(0.5f, 0.5f, 0.5f, 1.0f)));

	this->Speed = 0.0f;
}

void entity_car::Update()
{
	vec3 Position = GetPosition();

	if(Position.z > 200.0f)
	{
		SetAlive(0);
	}
	else
	{
		Position.z += 0.1f;
	}

	SetPosition(Position);

	UpdateDrawable();

	render_manager::Push(GetDrawable(), render_layer::Agents);
}