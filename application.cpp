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

	uint32 SystemInfoElement = Graphics.GetUI()->CreateElement(TOP_LEFT, 350.0f, 10.0f);

	uint32 T1 = Graphics.GetUI()->AddNewText(SystemInfoElement, "SYSTEM INFO");
	uint32 T2 = Graphics.GetUI()->AddNewText(SystemInfoElement, "FPS");
	uint32 T3 = Graphics.GetUI()->AddNewText(SystemInfoElement, "Frame Time");
	uint32 T4 = Graphics.GetUI()->AddNewText(SystemInfoElement, "Camera Position");
	uint32 T5 = Graphics.GetUI()->AddNewText(SystemInfoElement, "Mouse Picker");
	uint32 T6 = Graphics.GetUI()->AddNewText(SystemInfoElement, "Yas");

	Graphics.GetUI()->SetBackgroundColor(SystemInfoElement, { 0.25f, 0.25f, 0.25f, 0.75f });
	Graphics.GetUI()->SetOffset(SystemInfoElement, 10.0f, 10.0f);
	Graphics.GetUI()->SetMargin(SystemInfoElement, 10.0f);
	Graphics.GetUI()->SetAdjustWidthToText(SystemInfoElement, true);

	uint32 EditModeElement = Graphics.GetUI()->CreateElement(TOP_MIDDLE, 10.0f, 10.0f);
	Graphics.GetUI()->AddNewText(EditModeElement, "EDIT MODE ENABLED");
	Graphics.GetUI()->SetBackgroundColor(EditModeElement, { 0.25f, 0.25f, 0.25f, 0.75f });
	Graphics.GetUI()->SetOffset(EditModeElement, 0.0f, 10.0f);
	Graphics.GetUI()->SetMargin(EditModeElement, 20.0f);
	Graphics.GetUI()->SetHidden(EditModeElement, true);
	Graphics.GetUI()->SetAdjustHeightToText(EditModeElement, true);
	Graphics.GetUI()->SetAdjustWidthToText(EditModeElement, true);

	uint32 TopMiddle = Graphics.GetUI()->CreateElement(TOP_MIDDLE, 100.0f, 100.0f);
	Graphics.GetUI()->SetBackgroundColor(TopMiddle, { 0.25f, 0.25f, 0.25f, 0.75f });
	Graphics.GetUI()->AddNewText(TopMiddle, "TopMiddle");
	Graphics.GetUI()->SetOffset(TopMiddle, 10.0f, 10.0f);
	Graphics.GetUI()->SetMargin(TopMiddle, 10.0f);

	uint32 TopRight = Graphics.GetUI()->CreateElement(TOP_RIGHT, 100.0f, 100.0f);
	Graphics.GetUI()->SetBackgroundColor(TopRight, { 0.25f, 0.25f, 0.25f, 0.75f });
	Graphics.GetUI()->AddNewText(TopRight, "TopRight");
	Graphics.GetUI()->AddNewText(TopRight, "More test text for this box.");
	Graphics.GetUI()->SetOffset(TopRight, 10.0f, 10.0f);
	Graphics.GetUI()->SetMargin(TopRight, 10.0f);

	uint32 BottomLeft = Graphics.GetUI()->CreateElement(BOTTOM_LEFT, 100.0f, 100.0f);
	Graphics.GetUI()->SetBackgroundColor(BottomLeft, { 0.25f, 0.25f, 0.25f, 0.75f });
	Graphics.GetUI()->AddNewText(BottomLeft, "BottomLeft");
	Graphics.GetUI()->AddNewText(BottomLeft, "A second row of text.");
	Graphics.GetUI()->SetOffset(BottomLeft, 10.0f, 10.0f);
	Graphics.GetUI()->SetMargin(BottomLeft, 10.0f);

	uint32 BottomMiddle = Graphics.GetUI()->CreateElement(BOTTOM_MIDDLE, 100.0f, 100.0f);
	Graphics.GetUI()->SetBackgroundColor(BottomMiddle, { 0.25f, 0.25f, 0.25f, 0.75f });
	Graphics.GetUI()->AddNewText(BottomMiddle, "BottomMiddle");
	Graphics.GetUI()->SetOffset(BottomMiddle, 10.0f, 10.0f);
	Graphics.GetUI()->SetMargin(BottomMiddle, 10.0f);
	Graphics.GetUI()->SetAdjustWidthToText(BottomMiddle, true);

	uint32 BottomRight = Graphics.GetUI()->CreateElement(BOTTOM_RIGHT, 100.0f, 100.0f);
	Graphics.GetUI()->SetBackgroundColor(BottomRight, { 0.25f, 0.25f, 0.25f, 0.75f });
	Graphics.GetUI()->AddNewText(BottomRight, "BottomRight");
	Graphics.GetUI()->SetOffset(BottomRight, 10.0f, 10.0f);
	Graphics.GetUI()->SetMargin(BottomRight, 10.0f);

	uint32 MiddleLeft = Graphics.GetUI()->CreateElement(MIDDLE_LEFT, 100.0f, 100.0f);
	Graphics.GetUI()->SetBackgroundColor(MiddleLeft, { 0.25f, 0.25f, 0.25f, 0.75f });
	Graphics.GetUI()->AddNewText(MiddleLeft, "MiddleLeft");
	Graphics.GetUI()->SetOffset(MiddleLeft, 10.0f, 10.0f);
	Graphics.GetUI()->SetMargin(MiddleLeft, 10.0f);

	uint32 MiddleMiddle = Graphics.GetUI()->CreateElement(MIDDLE_MIDDLE, 200.0f, 100.0f);
	Graphics.GetUI()->SetBackgroundColor(MiddleMiddle, { 0.25f, 0.25f, 0.25f, 0.75f });
	Graphics.GetUI()->AddNewText(MiddleMiddle, "MiddleMiddle");
	Graphics.GetUI()->AddNewText(MiddleMiddle, "Usually we will want to launch more than one thread at once and do some work in parallel. In order to do this we could create an array of threads versus creating a single thread like in our first example.");
	Graphics.GetUI()->SetMargin(MiddleMiddle, 10.0f);
	Graphics.GetUI()->SetAdjustWidthToText(MiddleMiddle, false);

	uint32 MiddleRight = Graphics.GetUI()->CreateElement(MIDDLE_RIGHT, 100.0f, 100.0f);
	Graphics.GetUI()->SetBackgroundColor(MiddleRight, { 0.25f, 0.25f, 0.25f, 0.75f });
	Graphics.GetUI()->AddNewText(MiddleRight, "MiddleRight");
	Graphics.GetUI()->SetMargin(MiddleRight, 10.0f);
	Graphics.GetUI()->SetOffset(MiddleRight, 10.0f, 10.0f);

	Graphics.GetUI()->BuildElements();

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
			real32 CameraMovementSpeed = (real32)Timing.GetFrameTimeDeltaMilliseconds() * (8.0f / 1000.0f);

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

			Graphics.GetCamera().LookX(((real32)Timing.GetFrameTimeDeltaSeconds() * GetMouseRawX() * 8.0f / 1000.0f));
			Graphics.GetCamera().LookY(((real32)Timing.GetFrameTimeDeltaSeconds() * GetMouseRawY() * 8.0f / 1000.0f));
		}
		
		if(EditMode)
		{
			Graphics.TestDoEditorWorkStuff();

			if(MousePressed(MOUSE_BUTTON_LEFT))
			{
				Graphics.TestSetTile(global_data_collector::CurrentlyPickedTileX, global_data_collector::CurrentlyPickedTileY, ROAD_Z);
			}

			if(MousePressed(MOUSE_BUTTON_RIGHT))
			{
				Graphics.TestSetTile(global_data_collector::CurrentlyPickedTileX, global_data_collector::CurrentlyPickedTileY, ROAD_X);
			}

			if(MousePressed(MOUSE_BUTTON_MIDDLE))
			{
				Graphics.TestSetTile(global_data_collector::CurrentlyPickedTileX, global_data_collector::CurrentlyPickedTileY, CROSSROAD);
			}
		}

		Graphics.GetUI()->UpdateText(SystemInfoElement, T1, ("FPS: " + 
															 std::to_string(Timing.GetFramesPerSecond())));

		Graphics.GetUI()->UpdateText(SystemInfoElement, T2, ("Camera Position: " + 
															 std::to_string(Graphics.GetCamera().GetPositionX()) + ", " + 
															 std::to_string(Graphics.GetCamera().GetPositionY()) + ", " + 
															 std::to_string(Graphics.GetCamera().GetPositionZ())));
		
		Graphics.GetUI()->UpdateText(SystemInfoElement, T3, ("Mouse Picker: " +
															 std::to_string(global_data_collector::CurrentlyPickedTileX) + ", " +
															 std::to_string(global_data_collector::CurrentlyPickedTileY)));

		if(EditMode)
		{
			Graphics.GetUI()->SetHidden(EditModeElement, false);
		}
		else
		{
			Graphics.GetUI()->SetHidden(EditModeElement, true);
		}

		Graphics.GetUI()->BuildElements();

		// NOTE(Cristoffer): Temporary work stuff.
		Graphics.TestDoWorkStuff();

		// NOTE(Cristoffer): Temporary render test.
		Graphics.BeginFrame();
		Graphics.TestDrawTerrain();
		Graphics.TestDraw();
		Graphics.TestDrawUI();

		Graphics.EndFrame();

		Timing.EndFrameTimer();
	}
}

void application::UserInterface()
{
	
}