// threading.h: 
// Add function calls to work queue pool to get them threaded.

/*	HOW THE CLASS DESIGN WORKS:

	$ [INDEPENDENT BACKGROUND WORK] If the data is not critical to each frame or independent, do this.

		1.	work_id ThreadWorkID;

		2.	if(threading::GetInstance().WorkDone(ThreadWorkID))
			{
				threading::GetInstance().AddBackgroundWork(ThreadWorkID, [&]
				{
					FunctionToRunThreaded();
				});
			}

	$ [JOINED/SYNCED WORK] If the thread has to be synced at some point.

		1.	Create unique key object:
		
				work_id ThreadWorkID;

		2.	Start the work:

				threading::GetInstance().AddBackgroundWork(ThreadWorkID, [&]
				{
					FunctionToRunThreaded();
				});

		3.	Wait for work to be done:

				threading::GetInstance().WaitThread();

	$ [GENERIC WORK] "Fire and forget".

		1.	threading::GetInstance().AddWork(ThreadWorkID, [&]
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

#define thread_pool threading::GetInstance()

class work_id;

class threading
{
	friend class work_id;

	singleton:

	threading(const threading &Object) = delete;
	void operator=(const threading &Object) = delete;

	static threading &GetInstance()
	{
		static threading Instance;
		return Instance;
	};

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

	uint32	GenerateUniqueWorkID();

	public:
	
	void AddWork(std::function<void()> Function);

	// NOTE(Cristoffer): Add work to the queue, will automaticly be processed by a free thread.
	// WorkID object needs to be created in order to use it.
	void AddBackgroundWork(work_id &ID, std::function<void()> Function);	

	// NOTE(Cristoffer): Terminates all threads and joining them, so that all threads are done operating before objects gets destroyed and data unavailable.
	void TerminateAllThreads();		

	// NOTE(Cristoffer): Sync all threads by locking up main thread and wait for all work to be done.
	void WaitAllThreads();						

	// NOTE(Cristoffer): Lock up the main thread waiting for specifik work to be done.
	void WaitThread(work_id &ID);

	// NOTE(Cristoffer): Checks if a task is done, based on unique work id.
	bool WorkDone(work_id &ID);							
};

// NOTE(Cristoffer): Trying to make the work id system safer by requiring an object,
// that automaticly will create an unique ID. Otherwise it is too easy to refer to 
// bad IDs by just typing in any given integer.
class work_id
{
	private:

	uint32 ID;

	public:

	work_id(const work_id &Object) = delete;
	void operator=(const work_id &Object) = delete;

	work_id() : ID(threading::GetInstance().GenerateUniqueWorkID())
	{
	}

	uint32 &GetID()
	{
		return ID;
	}
};