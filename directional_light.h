#pragma once

#include "common.h"

#include <DirectXMath.h>

using namespace DirectX;

struct directional_light
{
    // NOTE(Cristoffer): Constant buffer need 16-byte packing.
    XMFLOAT3 Direction; alignas(16)
    //real32 Pad;
    XMFLOAT4 Ambient;
    XMFLOAT4 Diffuse;
};