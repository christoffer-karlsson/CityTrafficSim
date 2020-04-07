#include "application.h"

application::application() : 
	Window("City Traffic Simulator and Planner | Mid Sweden University Thesis Project | Cristoffer Tanda", 1280, 720), 
	Timing(), 
	Running(true),
	TimeCheck(0.0),
	Graphics(Window.GetHandle())
{
}

void application::Run()
{
	Window.ShowMouseCursor(0);
	Window.ClipMouseCursor(1);

	bool EditMode = false;
	real32 MoveX = 0.0f;
	real32 MoveY = 0.0f;
	real32 MoveZ = 0.0f;
	int32 X = 0;
	int32 Y = 0;

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

		// TODO(Cristoffer): Temporary input control for adjusting camera.

		if(KeyReleased(KEY_TAB))
		{
			EditMode = !EditMode;

			if(EditMode) Window.ShowMouseCursor(1);
			if(!EditMode) Window.ShowMouseCursor(0);
		}

		if(!EditMode)
		{
			real32 CameraMovementSpeed = (real32)Timing.GetFrameTimeDeltaSeconds() * (30.0f / 1.0f);

			if(KeyPressed(KEY_W))
			{
				Graphics.GetCamera().MoveForward(CameraMovementSpeed);
			}

			if(KeyPressed(KEY_S))
			{
				Graphics.GetCamera().MoveBackward(CameraMovementSpeed);
			}

			if(KeyPressed(KEY_A))
			{
				Graphics.GetCamera().StrafeLeft(CameraMovementSpeed);
			}

			if(KeyPressed(KEY_D))
			{
				Graphics.GetCamera().StrafeRight(CameraMovementSpeed);
			}

			if(KeyPressed(KEY_SPACE))
			{
				Graphics.GetCamera().MoveUp(CameraMovementSpeed);
			}

			if(KeyPressed(KEY_CONTROL))
			{
				Graphics.GetCamera().MoveDown(CameraMovementSpeed);
			}

			Graphics.GetCamera().LookX(((real32)Timing.GetFrameTimeDeltaSeconds() * GetMouseRawX() * 1.1f));
			Graphics.GetCamera().LookY(((real32)Timing.GetFrameTimeDeltaSeconds() * GetMouseRawY() * 1.1f));
		}

		if(KeyReleased(KEY_ARROWUP))
		{
			MoveZ += 1.0f;
			Y++;
		}

		if(KeyReleased(KEY_ARROWDOWN))
		{
			MoveZ -= 1.0f;
		}

		if(KeyReleased(KEY_ARROWLEFT))
		{
			MoveX -= 1.0f;
		}

		if(KeyReleased(KEY_ARROWRIGHT))
		{
			MoveX += 1.0f;
			X++;
		}

		MoveX = 0.0f;
		MoveY = 0.0f;
		MoveZ = 0.0f;

		std::string StringValue;
		std::wstring stemp;
		LPCWSTR sw;

		// NOTE(Cristoffer): Temporary work stuff.
		Graphics.TestDoWorkStuff();

		// NOTE(Cristoffer): Temporary render test.
		Graphics.BeginFrame();
		Graphics.TestDrawTerrain();
		Graphics.TestDraw();

		Graphics.BeginSpriteBatch();

		StringValue = "FPS: " + std::to_string(Timing.GetFramesPerSecond());
		stemp = std::wstring(StringValue.begin(), StringValue.end());
		sw = stemp.c_str();

		Graphics.DrawSpriteString(sw, 0.0f, 0.0f);

		StringValue = "Frame Time: " + std::to_string(Timing.GetFrameTimeDeltaMilliseconds()) + " ms";
		stemp = std::wstring(StringValue.begin(), StringValue.end());
		sw = stemp.c_str();

		Graphics.DrawSpriteString(sw, 0.0f, 16.0f);

		StringValue = "Camera Position: " + 
			std::to_string(Graphics.GetCamera().GetPositionX()) + ", " +
			std::to_string(Graphics.GetCamera().GetPositionY()) + ", " +
			std::to_string(Graphics.GetCamera().GetPositionZ());
		stemp = std::wstring(StringValue.begin(), StringValue.end());
		sw = stemp.c_str();

		Graphics.DrawSpriteString(sw, 0.0f, 32.0f);

		StringValue = "Mouse Picker: " +
			std::to_string(global_data_collector::CurrentlyPickedTileX) + ", " +
			std::to_string(global_data_collector::CurrentlyPickedTileY);
		stemp = std::wstring(StringValue.begin(), StringValue.end());
		sw = stemp.c_str();
		Graphics.DrawSpriteString(sw, 0.0f, 48.0f);

		StringValue = "THREAD JOBS: " +
			std::to_string(global_data_collector::JobCount);
		stemp = std::wstring(StringValue.begin(), StringValue.end());
		sw = stemp.c_str();
		Graphics.DrawSpriteString(sw, 0.0f, 64.0f);


		if(EditMode)
		{
			const wchar_t *Text = L"EDIT MODE ACTIVE";
			Vector2 t = Graphics.spriteFont->MeasureString(Text);

			Graphics.DrawSpriteString(Text, (global_device_info::FrameBufferWidth / 2.0f) - t.x, 2.0f);
		}

		Graphics.EndSpriteBatch();

		Graphics.EndFrame();

		Timing.EndFrameTimer();
	}
}