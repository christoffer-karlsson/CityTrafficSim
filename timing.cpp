#include "timing.h"

real64 timing::WallclockSeconds = 0.0;
real64 timing::WallclockMilliseconds = 0.0;
real64 timing::FrameTimeDeltaSeconds = 0.0;
real64 timing::FrameTimeDeltaMilliseconds = 0.0;

timing::timing() : 
	StartingTime(), 
	EndingTime(), 
	ElapsedMicroseconds(), 
	Frequency(),
	TimeElapsedMicroseconds(0.0), 
	TimeElapsedMilliseconds(0.0), 
	TimeElapsedSeconds(0.0),
	FrameCounter(0.0), 
	OneSecondElapsed(0.0), 
	FramesPerSecond(0.0)
{
}

timing::~timing()
{
}

void timing::StartFrameTimer()
{
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);
}

void timing::EndFrameTimer()
{
	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;

	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	TimeElapsedMicroseconds = (real64)ElapsedMicroseconds.QuadPart;
	TimeElapsedMilliseconds = TimeElapsedMicroseconds / (real64)(1000.0);
	TimeElapsedSeconds = TimeElapsedMilliseconds / (real64)(1000.0);

	FrameTimeDeltaSeconds = TimeElapsedSeconds;
	FrameTimeDeltaMilliseconds = TimeElapsedMilliseconds;

	WallclockMilliseconds += TimeElapsedMilliseconds;
	WallclockSeconds += TimeElapsedSeconds;

	// NOTE(Cristoffer): Frame counting.
	// TODO(Cristoffer): Perhaps this is unnecessary? Could use the frame time to
	// calculate frames per second instead and keep it out of this class. 
	// Think about this later.
	if(OneSecondElapsed > 1.0)
	{
		FramesPerSecond = FrameCounter;
		FrameCounter = 0.0;
		OneSecondElapsed = 0.0;
	}
	else
	{
		OneSecondElapsed += TimeElapsedSeconds;
		FrameCounter += 1.0;
	}
}

real64 timing::GetTimeElapsedSeconds() const
{
	return TimeElapsedSeconds;
}

real64 timing::GetTimeElapsedMilliseconds() const
{
	return TimeElapsedMilliseconds;
}

real64 timing::GetWallclockSeconds()
{
	return WallclockSeconds;
}

real64 timing::GetWallclockMilliseconds()
{
	return WallclockMilliseconds;
}

real64 timing::GetFrameTimeDeltaSeconds()
{
	return FrameTimeDeltaSeconds;
}

real64 timing::GetFrameTimeDeltaMilliseconds()
{
	return FrameTimeDeltaMilliseconds;
}

real64 timing::GetFramesPerSecond() const
{
	return FramesPerSecond;
}