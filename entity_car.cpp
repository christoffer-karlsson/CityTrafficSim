#include "entity_car.h"

entity_car::entity_car(uint32 ID, vec3 Position)
{
	this->Drawable = render_manager::GetDrawableCars();

	real32 R = static_cast <real32> (rand()) / static_cast <real32> (RAND_MAX);
	real32 G = static_cast <real32> (rand()) / static_cast <real32> (RAND_MAX);
	real32 B = static_cast <real32> (rand()) / static_cast <real32> (RAND_MAX);

	this->Color = vec4(R, G, B, 1.0f);

	SetID(ID);
	SetCollidable(0);
	SetSimulated(1);
	SetAlive(1);

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_real_distribution<> distr(1.0f, 7.0f); // define the range

	Speed = distr(eng);

	std::random_device rd2;
	std::mt19937 eng2(rd2());
	std::uniform_real_distribution<> distr2(0.0f, 360.0f);

	Angle = distr2(eng2);

	WorldModel->Position = Position;
	WorldModel->Rotation.y = Angle;
	WorldModel->Scale = vec3(0.25f, 0.25f, 0.25f);

	WorldModel->Update();
}

void entity_car::Update()
{
	Angle += Speed;

	if(Angle > 360.0f)
	{
		Angle = Angle - 360.0f;
	}

	//WorldModel->Rotation.y = Angle;
	WorldModel->Update();

	Drawable->PushInstance(WorldModel->GetMatrix(), Color);
}