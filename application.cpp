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

	mouse_picker MousePicker(&Graphics.GetCamera());

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
			real64 CameraMovementSpeed = Timing.GetFrameTimeDeltaSeconds() * (30.0f / 1.0f);

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

			Graphics.GetCamera().LookX((Timing.GetFrameTimeDeltaSeconds() * GetMouseRawX() * 1.1f));
			Graphics.GetCamera().LookY((Timing.GetFrameTimeDeltaSeconds() * GetMouseRawY() * 1.1f));
		}

		if(KeyReleased(KEY_ARROWUP))
		{
			MoveZ += 1.0f;
			Y++;
			Graphics.TestUpdateBuffer(0.0f + X, 0.0f + Y);
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
			Graphics.TestUpdateBuffer(0.0f + X, 0.0f + Y);
		}

		std::string StringValue;
		std::wstring stemp;
		LPCWSTR sw;

		MousePicker.Update();

		// TODO(Cristoffer): Temporary render test.
		Graphics.BeginFrame();
		Graphics.TestDraw();
		//Graphics.TestDrawEntity(MousePicker.GetRayX(), MousePicker.GetRayY(), MousePicker.GetRayZ()+5.0f);

		Graphics.TestDrawEntity(0.0f + MoveX, 0.0f, 0.0f + MoveZ);

		MoveX = 0.0f;
		MoveY = 0.0f;
		MoveZ = 0.0f;

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
			std::to_string(MousePicker.GetRayX()) + ", " +
			std::to_string(MousePicker.GetRayY()) + ", " +
			std::to_string(MousePicker.GetRayZ());
		stemp = std::wstring(StringValue.begin(), StringValue.end());
		sw = stemp.c_str();
		Graphics.DrawSpriteString(sw, 0.0f, 48.0f);


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