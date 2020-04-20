// drawable_cars.h
// Instanced drawing of car model object.

#pragma once

#include "drawable.h"
#include "drawable_cars_instance.h"

// NOTE(Cristoffer): 512 is the limit by the gpu.
// 1024 matrices are max, and we need 2 matrices per object.
// Remember to change this value in shader also!
#define MAX_INSTANCES 5000

class drawable_cars : public drawable
{
	private:

	struct cbuffer_input
	{
		XMMATRIX ViewProjection;
	};

	mesh *Asset;

	uint32 InstanceCount;

	//drawable_cars_instance *Instance;

	std::vector<drawable_cars_instance> Instance;

	public:

	drawable_cars(mesh *Asset, uint32 InstanceCount);

	void Draw();

	void PushInstance(XMMATRIX &Model, vec4 &Color);
};