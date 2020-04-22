// drawable_building.h
// Instanced drawing of building model object.

#pragma once

#include "drawable.h"
#include "instance_vs.h"

#define MAX_INSTANCES 5000

class drawable_buildings : public drawable
{
	private:

	struct cbuffer_input
	{
		XMMATRIX ViewProjection;
	};

	mesh *Asset;

	std::vector<instance_vs> Instance;

	public:

	drawable_buildings(mesh *Asset);

	void Draw();

	void PushInstance(XMMATRIX &Model, vec4 &Color);
	void ClearInstances();
};