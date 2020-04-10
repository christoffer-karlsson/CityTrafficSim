// threading.h: 
// Add function calls to work queue to get them threaded.

/*	HOW THE CLASS DESIGN WORKS:

	1. [Independent background work] If the data is not critical to each frame, do this.

	uint32 ThreadWorkID = threading::GetInstance().GenerateUniqueWorkID();

	if(threading::GetInstance().WorkDone(ThreadWorkID))
	{
		threading::GetInstance().AddBackgroundWork(ThreadWorkID, [&]
		{
			 FunctionToRunThreaded();
		});
	}

	This way it is independent from the frame, it can update the data independently.

	2. [Joined work] If the threads has to be synced before proceeding.

	uint32 ThreadWorkID = threading::GetInstance().GenerateUniqueWorkID();

	3. [Generic work] "Fire and forget", use with care.

	threading::GetInstance().AddWork(ThreadWorkID, [&]
	{
		FunctionToRunThreaded();
	});
*/

#pragma once

#include "common.h"

#include <thread>
#include <vector>
#include <functional>
#include <queue>
#include <mutex>
#include <stack>

#include "global_data_collector.h"

#define MAX_SYNCED_JOBS 1000
#define MAX_THREADS		1000

class threading
{
	private:

	struct task
	{
		uint32 ID;
		std::function<void()> Function;
	};

	std::condition_variable ThreadBlocker;
	std::mutex Mutex;

	uint32	ThreadCount;
	bool	ThreadsTerminated;
	bool	ThreadIsWorking[MAX_THREADS];
	bool	WorkIsDone[MAX_SYNCED_JOBS];

	std::vector<bool> JoinedWorkIsDone[MAX_SYNCED_JOBS];

	std::vector<std::thread> Threads;
	std::queue<task> Jobs;
	std::stack<uint32> WorkID;

	static threading Instance;

	threading();

	public:

	uint32	GenerateUniqueWorkID();
	void	AddWork(std::function<void()> Function);
	void	AddJoinedWork(uint32 ID, std::function<void()> Function);
	void	AddBackgroundWork(uint32 ID, std::function<void()> Function);	// NOTE(Cristoffer): Add work to the queue, will automaticly be processed by a free thread.
	void	TerminateAllThreads();								// NOTE(Cristoffer): Terminates all threads and joining them, so that all threads are done operating before objects gets destroyed and data unavailable.
	void	WaitAllThreads();									// NOTE(Cristoffer): Sync all threads by waiting for everyone to be done.
	bool	WorkDone(uint32 WorkID);							// NOTE(Cristoffer): Checks if a task is done, based on unique work id.
	
	public:

	threading(const threading &Object) = delete;
	void operator=(const threading &Object) = delete;

	static threading &GetInstance()
	{
		static threading Instance;
		return Instance;
	};
};