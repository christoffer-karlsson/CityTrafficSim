#pragma once

#include "common.h"

#define math_pi 3.14159265359f

inline vec3 Scale(real32 &k, vec3 &v)
{
	vec3 Result;

	Result.x = k * v.x;
	Result.y = k * v.y;
	Result.z = k * v.z;

	return Result;
}

inline vec3 Cross(vec3 &v1, vec3 &v2)
{
	vec3 Result;

	Result.x = v1.y * v2.z - v1.z * v2.y;
	Result.y = v1.z * v2.x - v1.x * v2.z;
	Result.z = v1.x * v2.y - v1.y * v2.x;

	return Result;
}

inline uint64 WorldCoordinateToIndex(uint64 Width, uint32 Stride, int64 X, int64 Y)
{
	uint64 Pitch = Width * Stride * X;

	uint64 Index = Pitch + Y * Stride;

	return Index;
}

inline real32 DegreeToRadian(real32 Angle)
{
	return Angle * math_pi / 180.0f;
}