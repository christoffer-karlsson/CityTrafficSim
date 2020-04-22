#pragma once

#include <DirectXMath.h>
#include "math.h"

using namespace DirectX;

struct instance_vs
{
	XMMATRIX Model;
	vec4 Color;
};