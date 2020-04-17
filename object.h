// object.h
// An abstract drawable that takes one model asset and draws it. 

#pragma once

#include "drawable.h"

class object : public drawable
{
	private:

	struct cbuffer_input
	{
		XMMATRIX MVP;
		XMMATRIX Model;
	};

	model *Asset;

	public:

	object(model *Asset, vec3 Position, vec3 Scale, vec3 Rotation, vec4 Color);

	void Draw();
};