#include "system_message.h"

std::queue<std::string> system_message::QueuedMessages;
std::vector<message> system_message::ActiveMessages;

user_interface *system_message::UI;

uint32 system_message::UIElementID[MAX_MESSAGES_ALLOWED];
uint32 system_message::UITextID[MAX_MESSAGES_ALLOWED];

void system_message::Init()
{
	UI = new user_interface();

	for(uint32 Index = 0;
		Index < MAX_MESSAGES_ALLOWED;
		Index++)
	{
		UIElementID[Index] = 0;
		UITextID[Index] = 0;
	}

	real32 ExtraOffset = 0;
	real32 Margin = 10.0f;
	real32 Offset = 10.0f;
	real32 BetweenDistance = 50.0f;
	real32 VerticalOffsetCentered = (MAX_MESSAGES_ALLOWED * (Offset + Margin)) / 2.0f;

	for(uint32 Index = 0;
		Index < MAX_MESSAGES_ALLOWED;
		Index++)
	{
		ExtraOffset = Index * BetweenDistance;

		UIElementID[Index] = UI->CreateElement(screen_anchor::MIDDLE_LEFT, 10.0f, 10.0f);
		UITextID[Index] = UI->AddNewText(UIElementID[Index], "system_message");
		UI->SetBackgroundColor(UIElementID[Index], { 0.25f, 0.25f, 0.25f, 0.5f });
		UI->SetOffset(UIElementID[Index], Offset, Offset + ExtraOffset - VerticalOffsetCentered);
		UI->SetMargin(UIElementID[Index], Margin);
		UI->SetAdjustWidthToText(UIElementID[Index], true);
		UI->SetHidden(UIElementID[Index], false);
	}
}

void system_message::Push(std::string Text)
{
	QueuedMessages.push(Text);
}

void system_message::Update()
{
	// NOTE(Cristoffer): Protect against overflow of message queue. If detected
	// reset it completly so behaviour doesn't get too wierd.
	if(QueuedMessages.size() > OVERFLOW_THRESHOLD)
	{
		while(!QueuedMessages.empty())
		{
			QueuedMessages.pop();
		}
	}

	UI->SetHidden(0, true);
	UI->SetHidden(1, true);
	UI->SetHidden(2, true);
	UI->SetHidden(3, true);
	UI->SetHidden(4, true);
	UI->SetHidden(5, true);
	UI->SetHidden(6, true);
	UI->SetHidden(7, true);
	UI->SetHidden(8, true);
	UI->SetHidden(9, true);

	real64 Timeout = TIME_TO_KILL_MESSAGE * 1000.0;
	real64 CurrentTime = timing::GetWallclockMilliseconds();
	uint32 MaxMessages = MAX_MESSAGES_ALLOWED;

	// NOTE(Cristoffer): Check message time outs and delete them.
	ActiveMessages.erase( std::remove_if(ActiveMessages.begin(), ActiveMessages.end(), [&](message const &Message)
	{
		real64 ElapsedTime = CurrentTime - Message.TimeStamp;
		return ElapsedTime >= Timeout;
	}), ActiveMessages.end());

	// NOTE(Cristoffer): Fill text empty text slots from the queue.
	if(ActiveMessages.size() < MaxMessages)
	{
		// NOTE(Cristoffer): Available slots.
		uint64 TextSlots = MaxMessages - ActiveMessages.size();

		for(uint64 Index = 0;
			Index < TextSlots;
			Index++)
		{
			if(!QueuedMessages.empty())
			{
				message Message = { QueuedMessages.front(), CurrentTime };
				ActiveMessages.push_back(Message);

				QueuedMessages.pop();
			}
		}
	}

	// NOTE(Cristoffer): Active messages.
	for(uint64 Index = 0;
		Index < ActiveMessages.size();
		Index++)
	{
		message Message = ActiveMessages.at(Index);

		real64 MessageTimeLeft = Timeout - (CurrentTime - Message.TimeStamp);

		// NOTE(Cristoffer): To reverse the order of elements on screen.
		uint32 ElementIndex = ActiveMessages.size() - (uint32)Index;

		UI->UpdateText(ElementIndex, UITextID[Index], Message.Text);
		UI->SetHidden(ElementIndex, false);

		// TODO(Cristoffer): Correct values but does not work. Look at later. No fade effect for now.
		/*if(MessageTimeLeft > 2000.0)
		{
			real32 Timeout = (real32)TIME_TO_KILL_MESSAGE * 1000.0f;

			Time = TIME_TO_KILL_MESSAGE 

			real32 FadeValue = 1.0f - ((real32)MessageTimeLeft / 2000.0f) * 0.5f;

			UI->SetBackgroundAlpha(ElementIndex, FadeValue);
		}*/

		/*if(MessageTimeLeft < 1000.0)
		{
			real32 FadeValue = 0.5 * (real32)MessageTimeLeft / 1000.0f;

			UI->SetBackgroundAlpha(ElementIndex, FadeValue);
			UI->SetTextAlpha(ElementIndex, FadeValue);
		}*/
	}

	UI->BuildElements();

	render_queue::Push(UI, render_layer::UserInterface);
}