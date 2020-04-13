#pragma once

#include "common.h"

class light_source
{
	public:

	static vec3 Position;

	light_source()
	{
		Position = vec3(100.0f, 200.0f, 100.0f);
	};

	static void Init()
	{
		Position = vec3(100.0f, 200.0f, 100.0f);
	}
};