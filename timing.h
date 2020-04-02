// timing.h: Stores timing data
// Documentation used: https://docs.microsoft.com/sv-se/windows/win32/sysinfo/acquiring-high-resolution-time-stamps

#pragma once

#include "common.h"

#include <windows.h>

class timing
{
	private:

	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds, Frequency;

	real64 TimeElapsedMicroseconds;
	real64 TimeElapsedMilliseconds;
	real64 TimeElapsedSeconds;

	// NOTE(Cristoffer): Keeping this static, so that total time passed can be accessed 
	// in any translation since first instantiation of this class.
	static real64 WallclockMilliseconds;
	static real64 WallclockSeconds;

	real64 FrameCounter;
	real64 OneSecondElapsed;
	real64 FramesPerSecond;

	public:

	timing();
	~timing();

	void StartFrameTimer();
	void EndFrameTimer();

	real64 GetTimeElapsedSeconds() const;
	real64 GetTimeElapsedMilliseconds() const;

	static real64 GetWallclockSeconds();
	static real64 GetWallclockMilliseconds();

	real64 GetFramesPerSecond() const;
};