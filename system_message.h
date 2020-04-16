#pragma once

#include "common.h"
#include "timing.h"
#include "user_interface.h"
#include "render_manager.h"

#include <string>
#include <queue>
#include <algorithm>

#define TIME_TO_KILL_MESSAGE 5.0
#define MAX_MESSAGES_ALLOWED 8
#define OVERFLOW_THRESHOLD 50

#define SystemMessage(x) system_message::Push(x)

struct message
{
	std::string Text;
	real64 TimeStamp;
};

class system_message
{
	private:

	static std::queue<std::string> QueuedMessages;
	static std::vector<message> ActiveMessages;

	static uint32 UIElementID[MAX_MESSAGES_ALLOWED];
	static uint32 UITextID[MAX_MESSAGES_ALLOWED];

	static user_interface *UI;

	public:

	static void Init();
	static void Push(std::string Text);
	static void Update();
};