/*
==========================================================
    Directional lighting.
==========================================================
*/

#pragma once

#include "common.h"

#include <DirectXMath.h>

using namespace DirectX;

struct light_directional
{
    XMFLOAT3 Direction; alignas(16)
    XMFLOAT4 Ambient;
    XMFLOAT4 Diffuse;
};