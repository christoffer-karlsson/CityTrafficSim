#include "threading.h"

threading::threading() :
	ThreadsTerminated(false),
	ThreadCount(std::thread::hardware_concurrency())
{
	std::function <void(uint32)> Thread = [&](uint32 ThreadID)
	{
		while(true)
		{
			task Task;

			ThreadIsWorking[ThreadID] = false;

			{
				std::unique_lock<std::mutex> Lock{ Mutex };

				// NOTE(Cristoffer): Wait for condition_variable signal.
				while(Jobs.empty() || ThreadsTerminated)
				{
					ThreadBlocker.wait(Lock);
				}

				if(ThreadsTerminated)
				{
					break;
				}

				ThreadIsWorking[ThreadID] = true;

				Task.ID = Jobs.front().ID;
				Task.Function = Jobs.front().Function;

				Jobs.pop();
			}

			WorkIsDone[Task.ID] = false;

			Task.Function();

			WorkIsDone[Task.ID] = true;
		}
	};

	// TODO(Cristoffer): Replace hard-coded ranges.

	for(uint32 Index = 0; Index < MAX_SYNCED_JOBS; Index++)
	{
		WorkID.push(Index);
	}

	for(uint32 Index = 0; Index < MAX_SYNCED_JOBS; Index++)
	{
		WorkIsDone[Index] = true;
	}

	for(uint32 Index = 0; Index < MAX_THREADS; Index++)
	{
		ThreadIsWorking[Index] = false;
	}

	// TODO(Cristoffer): Decide how many threads to use, all that are given?
	for(uint32 Index = 0; Index < ThreadCount; Index++)
	{
		Threads.emplace_back(std::thread(Thread, Index));
	}
}

void threading::TerminateAllThreads()
{
	{
		std::unique_lock<std::mutex> Lock{ Mutex };

		ThreadsTerminated = true;
	}

	ThreadBlocker.notify_all();

	WaitAllThreads();

	// TODO(Cristoffer): Detach is working for the purpose for now.
	// Maybe implement proper joining.
	for(auto &Thread : Threads)
	{
		Thread.detach();
	}
}

void threading::AddWork(std::function<void()> Function)
{
	task Task;

	{
		std::unique_lock<std::mutex> Lock{ Mutex };

		Task.ID = 0;
		Task.Function = Function;

		Jobs.emplace(Task);
	}

	ThreadBlocker.notify_one();
}

void threading::AddJoinedWork(uint32 ID, std::function<void()> Function)
{
	task Task;

	{
		std::unique_lock<std::mutex> Lock{ Mutex };

		Task.ID = ID;
		Task.Function = Function;

		Jobs.emplace(Task);
	}

	ThreadBlocker.notify_one();
}

void threading::AddBackgroundWork(uint32 ID, std::function<void()> Function)
{
	task Task;

	{
		std::unique_lock<std::mutex> Lock{ Mutex };

		Task.ID = ID;
		Task.Function = Function;

		Jobs.emplace(Task);
	}

	ThreadBlocker.notify_one();
}

uint32 threading::GenerateUniqueWorkID()
{
	uint32 ID = 0;

	{
		std::unique_lock<std::mutex> Lock{ Mutex };

		ID = WorkID.top();
		WorkID.pop();
	}

	return ID;
}

bool threading::WorkDone(uint32 WorkID)
{
	return WorkIsDone[WorkID];
}

void threading::WaitAllThreads()
{
	bool ThreadsWorking = true;

	while(ThreadsWorking)
	{
		for(uint32 Index = 0; Index < ThreadCount; Index++)
		{
			if(ThreadIsWorking[Index])
			{
				break;
			}
			else if(!ThreadIsWorking[Index] && Index == (ThreadCount - 1))
			{
				ThreadsWorking = false;
				break;
			}
		}
	}
}