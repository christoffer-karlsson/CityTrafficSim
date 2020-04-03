#include "application.h"

application::application() : 
	Window("City Traffic Simulator and Planner | Mid Sweden University Thesis Project | Cristoffer Tanda", 1280, 720), 
	Timing(), 
	Running(true),
	TimeCheck(0.0)
{
}

void application::Run()
{
	Window.ShowMouseCursor(1);
	Window.ClipMouseCursor(0);

	HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);

	while(Running)
	{
		Timing.StartFrameTimer();

		MSG Message;

		while(PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		if(KeyReleased(KEY_ESCAPE))
		{
			Running = FALSE;
		}



		real64 CurrentTime = Timing.GetWallclockSeconds();

		// NOTE(Cristoffer): Run program here!!
		if((CurrentTime - TimeCheck) > 1.0)
		{
			TimeCheck = CurrentTime;

			std::string StringValue = std::to_string(Timing.GetFramesPerSecond());

			std::wstring stemp = std::wstring(StringValue.begin(), StringValue.end());
			LPCWSTR sw = stemp.c_str();

			OutputDebugStringW(sw);
			OutputDebugStringW(L"\n");
		}

		// TODO(Cristoffer): Temporary input control for adjusting camera.
		if(KeyPressed(KEY_W))
		{
			Window.GetGraphicsDevice().GetCamera().MoveForward(0.01f);
		}

		if(KeyPressed(KEY_S))
		{
			Window.GetGraphicsDevice().GetCamera().MoveBackward(0.01f);
		}

		if(KeyPressed(KEY_A))
		{
			Window.GetGraphicsDevice().GetCamera().StrafeLeft(0.01f);
		}

		if(KeyPressed(KEY_D))
		{
			Window.GetGraphicsDevice().GetCamera().StrafeRight(0.01f);
		}

		if(KeyPressed(KEY_SPACE))
		{
			Window.GetGraphicsDevice().GetCamera().MoveUp(0.01f);
		}

		if(KeyPressed(KEY_CONTROL))
		{
			Window.GetGraphicsDevice().GetCamera().MoveDown(0.01f);
		}

		Window.GetGraphicsDevice().GetCamera().LookX(GetMouseRawX() * 0.001f);
		Window.GetGraphicsDevice().GetCamera().LookY(GetMouseRawY() * 0.001f);

		// TODO(Cristoffer): Temporary render test.
		Window.GetGraphicsDevice().BeginFrame();
		Window.GetGraphicsDevice().TestDraw();
		Window.GetGraphicsDevice().EndFrame();

		Timing.EndFrameTimer();
	}
}