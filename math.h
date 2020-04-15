#pragma once

#include "common.h"
#include <cmath>

#define math_pi 3.14159265359f

inline real32 DegreeToRadian(real32 Angle)
{
	return Angle * math_pi / 180.0f;
}

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

inline uint64 WorldCoordinateToIndex(uint64 Width, uint32 Stride, uint64 X, uint64 Y)
{
	uint64 Pitch = Width * Stride * X;

	uint64 Index = Pitch + Y * Stride;

	return Index;
}

// TODO(Cristoffer): Look at this later. Simple cast for now.
inline vec3u Truncate(vec3 &V1)
{
	vec3u Result;

	
	//Result.x = std::ceil(V1.x);
	//Result.y = std::floor(V1.y);
	//Result.z = std::ceil(V1.z);

	Result.x = (uint32)V1.x;
	Result.y = (uint32)V1.y;
	Result.z = (uint32)V1.z;

	return Result;
}

// TODO(Cristoffer): Find the where the ray intersect Y plane at zero with a tolerance.
// Temporary algorithm, this might be bad. Think about a better way to do this.
// DONT USE THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*inline vec3 FindRayIntersectAtZeroInY(vec3 Origin, vec3 Direction)
{
	// NOTE(Cristoffer): Arbitrary values.
	real32 Tolerance = 0.01f;
	real32 Ray = 1000.0f;
	real32 MinPoint = 0.0f;
	real32 MaxPoint = Ray;
	//vec3 MinPoint = Origin + 0.0f * Direction;
	//vec3 MaxPoint = Origin + Ray * Direction;
	vec3 Point = Origin + Ray * Direction;
	while(std::abs(Point.y) > Tolerance)
	{
		// NOTE(Cristoffer): Check if y=0 is over or under and
		// do a binary search.
		if(Point.y > 0)
		{
			Point = Origin + Ray / 2.0f * Direction;
		}
		else if(Point.y < 0)
		{
			MinPoint = MaxPoint / 2.0f;
			Ray = Ray - (Ray / 2.0f);
		}
	}

	return Point;
}*/

