#pragma once

#include "common.h"
#include "timing.h"
#include "user_interface.h"
#include "threading.h"

#include <string>
#include <queue>
#include <algorithm>

#define TIME_TO_KILL_MESSAGE 5.0
#define MAX_MESSAGES_ALLOWED 8
#define OVERFLOW_THRESHOLD 50

#define sys_message system_message::GetInstance()
#define SystemMessage(x) system_message::GetInstance().Push(x)

class system_message
{
	singleton:

	system_message(const system_message &Object) = delete;
	void operator=(const system_message &Object) = delete;

	static system_message &GetInstance()
	{
		static system_message Instance;
		return Instance;
	};

	struct message
	{
		std::string Text;
		real64 TimeStamp;
	};

	private:

	static system_message Instance;

	system_message();

	std::queue<std::string> QueuedMessages;
	std::vector<message> ActiveMessages;

	user_interface *UI;

	camera Camera;

	uint32 UIElementID[MAX_MESSAGES_ALLOWED];
	uint32 UITextID[MAX_MESSAGES_ALLOWED];

	public:

	void Push(std::string Text);

	void Display(camera &Camera);
};