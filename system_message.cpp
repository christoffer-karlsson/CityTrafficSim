#include "system_message.h"

system_message::system_message()
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

	for(uint32 Index = 0;
		Index < MAX_MESSAGES_ALLOWED;
		Index++)
	{
		ExtraOffset = Index * 50.0f;

		UIElementID[Index] = UI->CreateElement(screen_anchor::MIDDLE_LEFT, 10.0f, 10.0f);
		UITextID[Index] = UI->AddNewText(UIElementID[Index], "system_message");
		UI->SetBackgroundColor(UIElementID[Index], { 0.25f, 0.25f, 0.25f, 0.5f });
		UI->SetOffset(UIElementID[Index], 10.0f, 10.0f + ExtraOffset);
		UI->SetMargin(UIElementID[Index], 10.0f);
		UI->SetAdjustWidthToText(UIElementID[Index], true);
		UI->SetHidden(UIElementID[Index], false);
	}
}

void system_message::Push(std::string Text)
{
	QueuedMessages.push(Text);
}

void system_message::Display(camera &Camera)
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

	std::vector<std::vector<message>::iterator> TempIt;

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
		uint32 TextSlots = MaxMessages - ActiveMessages.size();

		for(uint32 Index = 0;
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
	for(uint32 Index = 0;
		Index < ActiveMessages.size();
		Index++)
	{
		message Message = ActiveMessages.at(Index);

		real64 MessageTimeLeft = Timeout - (CurrentTime - Message.TimeStamp);

		uint32 ElementIndex = ActiveMessages.size() - Index; // Just to inverse the order.

		UI->UpdateText(ElementIndex, UITextID[Index], Message.Text);
		UI->SetHidden(ElementIndex, false);

		// TODO(Cristoffer): Correct values but does not work. Look at later. No fade effect for now.
		if(MessageTimeLeft > 2000.0)
		{
			real32 FadeValue = 1.0f - ((real32)MessageTimeLeft / 2000.0f) * 0.5f;

			UI->SetBackgroundAlpha(ElementIndex, FadeValue);
		}

		if(MessageTimeLeft < 2000.0)
		{
			real32 FadeValue = 0.5f * (real32)MessageTimeLeft / 2000.0f;

			UI->SetBackgroundAlpha(ElementIndex, FadeValue);
		}
	}

	UI->CalculateTextPositions();
	UI->CalculateVertices();

	UI->Draw(Camera);
	UI->DrawStrings();
}