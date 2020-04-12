#pragma once

#include <stdint.h>

// NOTE(Cristoffer): For pristine looking code.
typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef int32_t bool32;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float  real32;
typedef double real64;

// NOTE(Cristoffer): This cannot be a strong type, because used for indexing.
enum tile_type
{
	GRASS,
	ROAD_Z,
	ROAD_X,
	CROSSROAD,
	SIDEWALK,
	WATER,
};

struct vec2
{
	real32 x, y;

	vec2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	vec2(real32 x, real32 y)
	{
		this->x = x;
		this->y = y;
	}

	friend vec2 operator+(const vec2 &lhs, const vec2 &rhs)
	{
		vec2 Result;

		Result.x = lhs.x + rhs.x;
		Result.y = lhs.y + rhs.y;

		return Result;
	};

	friend real32 operator*(const vec2 &lhs, const vec2 &rhs)
	{
		real32 Result = lhs.x * rhs.x + lhs.y * rhs.y;

		return Result;
	};

	friend vec2 operator*(const real32 &lhs, const vec2 &rhs)
	{
		vec2 Result;

		Result.x = lhs * rhs.x;
		Result.y = lhs * rhs.y;

		return Result;
	};

	friend vec2 operator*(const vec2 &lhs, const real32 &rhs)
	{
		vec2 Result;

		Result.x = lhs.x * rhs;
		Result.y = lhs.y * rhs;

		return Result;
	};
};

struct vec3
{
	real32 x, y, z;

	vec3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	vec3(real32 x, real32 y, real32 z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	friend vec3 operator+(const vec3 &lhs, const vec3 &rhs)
	{
		vec3 Result;

		Result.x = lhs.x + rhs.x;
		Result.y = lhs.y + rhs.y;
		Result.z = lhs.z + rhs.z;

		return Result;
	};

	friend real32 operator*(const vec3 &lhs, const vec3 &rhs)
	{
		real32 Result = lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;

		return Result;
	};

	friend vec3 operator*(const real32 &lhs, const vec3 &rhs)
	{
		vec3 Result;

		Result.x = lhs * rhs.x;
		Result.y = lhs * rhs.y;
		Result.z = lhs * rhs.z;

		return Result;
	};

	friend vec3 operator*(const vec3 &lhs, const real32 &rhs)
	{
		vec3 Result;

		Result.x = lhs.x * rhs;
		Result.y = lhs.y * rhs;
		Result.z = lhs.z * rhs;

		return Result;
	};
};

struct vec4
{
	real32 x, y, z, w;

	vec4()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}

	vec4(real32 x, real32 y, real32 z, real32 w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	friend vec4 operator+(const vec4 &lhs, const vec4 &rhs)
	{
		vec4 Result;

		Result.x = lhs.x + rhs.x;
		Result.y = lhs.y + rhs.y;
		Result.z = lhs.z + rhs.z;

		return Result;
	};

	friend real32 operator*(const vec4 &lhs, const vec4 &rhs)
	{
		real32 Result = lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;

		return Result;
	};

	friend vec4 operator*(const real32 &lhs, const vec4 &rhs)
	{
		vec4 Result;

		Result.x = lhs * rhs.x;
		Result.y = lhs * rhs.y;
		Result.z = lhs * rhs.z;

		return Result;
	};

	friend vec4 operator*(const vec4 &lhs, const real32 &rhs)
	{
		vec4 Result;

		Result.x = lhs.x * rhs;
		Result.y = lhs.y * rhs;
		Result.z = lhs.z * rhs;

		return Result;
	};
};