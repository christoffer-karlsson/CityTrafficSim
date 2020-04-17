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

	vec3(vec2 &V, real32 z)
	{
		this->x = V.x;
		this->y = V.y;
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

struct vec3u
{
	uint32 x, y, z;

	vec3u()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	vec3u(uint32 x, uint32 y, uint32 z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	friend vec3u operator+(const vec3u &lhs, const vec3u &rhs)
	{
		vec3u Result;

		Result.x = lhs.x + rhs.x;
		Result.y = lhs.y + rhs.y;
		Result.z = lhs.z + rhs.z;

		return Result;
	};

	friend uint32 operator*(const vec3u &lhs, const vec3u &rhs)
	{
		uint32 Result = lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;

		return Result;
	};

	friend vec3u operator*(const uint32 &lhs, const vec3u &rhs)
	{
		vec3u Result;

		Result.x = lhs * rhs.x;
		Result.y = lhs * rhs.y;
		Result.z = lhs * rhs.z;

		return Result;
	};

	friend vec3u operator*(const vec3u &lhs, const uint32 &rhs)
	{
		vec3u Result;

		Result.x = lhs.x * rhs;
		Result.y = lhs.y * rhs;
		Result.z = lhs.z * rhs;

		return Result;
	};
};

struct vec3i
{
	int32 x, y, z;

	vec3i()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	vec3i(int32 x, int32 y, int32 z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	friend vec3i operator+(const vec3i &lhs, const vec3i &rhs)
	{
		vec3i Result;

		Result.x = lhs.x + rhs.x;
		Result.y = lhs.y + rhs.y;
		Result.z = lhs.z + rhs.z;

		return Result;
	};

	friend int32 operator*(const vec3i &lhs, const vec3i &rhs)
	{
		int32 Result = lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;

		return Result;
	};

	friend vec3i operator*(const int32 &lhs, const vec3i &rhs)
	{
		vec3i Result;

		Result.x = lhs * rhs.x;
		Result.y = lhs * rhs.y;
		Result.z = lhs * rhs.z;

		return Result;
	};

	friend vec3i operator*(const vec3i &lhs, const int32 &rhs)
	{
		vec3i Result;

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