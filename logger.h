// logger.h
// Log values globally for debugging and testing purposes only.

#pragma once

#include "common.h"

#define MAX_LOG 1000

// NOTE(Cristoffer):  How to use:
// 1. Put MyVariable name in the enum.
// 2. logger::LogINT(MyVariable, logger::ref::MyVariable);
// 3. logger::GetINT(logger::ref::MyVariable);

class logger
{
	private:

	static int32 ValueINT[MAX_LOG];
	static uint32 ValueUINT[MAX_LOG];
	static real32 ValueREAL[MAX_LOG];

	public:

	enum ref
	{
		EntityCount, MouseWorldX, MouseWorldY
	};

	static void Init()
	{
		for(uint32 Index = 0;
			Index < MAX_LOG;
			Index++)
		{
			ValueINT[Index] = 0;
			ValueUINT[Index] = 0;
			ValueREAL[Index] = 0;
		}
	};

	static void LogINT(int32 Value, ref Reference)
	{
		ValueINT[Reference] = Value;
	};

	static void LogUINT(uint32 Value, ref Reference)
	{
		ValueUINT[Reference] = Value;
	};

	static void LogREAL(real32 Value, ref Reference)
	{
		ValueREAL[Reference] = Value;
	};

	static int32 GetINT(ref Reference)
	{
		return ValueINT[Reference];
	};

	static uint32 GetUINT(ref Reference)
	{
		return ValueUINT[Reference];
	};

	static real32 GetREAL(ref Reference)
	{
		return ValueREAL[Reference];
	};
};