// drawable_object.h
// An abstract drawable that takes one model asset and draws it. 

#pragma once

#include "drawable.h"

class drawable_object : public drawable
{
	private:

	mesh *Asset;

	struct cbuffer_input
	{
		XMMATRIX MVP;
		XMMATRIX Model;
	};

	public:

	drawable_object(mesh *Asset, vec3 Position, vec3 Scale, vec3 Rotation, vec4 Color);
	~drawable_object();

	void Draw();
};