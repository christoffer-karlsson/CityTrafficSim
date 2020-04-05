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
		/*if((CurrentTime - TimeCheck) > 1.0)
		{
			TimeCheck = CurrentTime;

			std::string StringValue = std::to_string(Timing.GetFramesPerSecond());

			std::wstring stemp = std::wstring(StringValue.begin(), StringValue.end());
			LPCWSTR sw = stemp.c_str();

			OutputDebugStringW(sw);
			OutputDebugStringW(L"\n");
		}*/

		// TODO(Cristoffer): Temporary input control for adjusting camera.

		real64 CameraMovementSpeed = Timing.GetFrameTimeDeltaSeconds() * (30.0f / 1.0f);

		if(KeyPressed(KEY_W))
		{
			Window.GetGraphicsDevice().GetCamera().MoveForward(CameraMovementSpeed);
		}

		if(KeyPressed(KEY_S))
		{
			Window.GetGraphicsDevice().GetCamera().MoveBackward(CameraMovementSpeed);
		}

		if(KeyPressed(KEY_A))
		{
			Window.GetGraphicsDevice().GetCamera().StrafeLeft(CameraMovementSpeed);
		}

		if(KeyPressed(KEY_D))
		{
			Window.GetGraphicsDevice().GetCamera().StrafeRight(CameraMovementSpeed);
		}

		if(KeyPressed(KEY_SPACE))
		{
			Window.GetGraphicsDevice().GetCamera().MoveUp(CameraMovementSpeed);
		}

		if(KeyPressed(KEY_CONTROL))
		{
			Window.GetGraphicsDevice().GetCamera().MoveDown(CameraMovementSpeed);
		}

		Window.GetGraphicsDevice().GetCamera().LookX((Timing.GetFrameTimeDeltaSeconds() * GetMouseRawX() * 1.1f));
		Window.GetGraphicsDevice().GetCamera().LookY((Timing.GetFrameTimeDeltaSeconds() * GetMouseRawY() * 1.1f));

		std::string StringValue;
		std::wstring stemp;
		LPCWSTR sw;

		// TODO(Cristoffer): Temporary render test.
		Window.GetGraphicsDevice().BeginFrame();
		Window.GetGraphicsDevice().TestDraw();

		Window.GetGraphicsDevice().BeginSpriteBatch();

		StringValue = "FPS: " + std::to_string(Timing.GetFramesPerSecond());
		stemp = std::wstring(StringValue.begin(), StringValue.end());
		sw = stemp.c_str();

		Window.GetGraphicsDevice().DrawSpriteString(sw, 0.0f, 0.0f);

		StringValue = "Frame Time: " + std::to_string(Timing.GetFrameTimeDeltaMilliseconds()) + " ms";
		stemp = std::wstring(StringValue.begin(), StringValue.end());
		sw = stemp.c_str();

		Window.GetGraphicsDevice().DrawSpriteString(sw, 0.0f, 16.0f);

		Window.GetGraphicsDevice().EndSpriteBatch();

		Window.GetGraphicsDevice().EndFrame();

		Timing.EndFrameTimer();
	}
}