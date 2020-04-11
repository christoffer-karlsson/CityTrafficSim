#include "application.h"

application::application() :
	Window("City Traffic Simulator and Planner | Mid Sweden University Thesis Project | Cristoffer Tanda", 1920, 1080), 
	Timing(), 
	Running(true),
	Graphics(Window.GetHandle())
{
}

void application::Run()
{
	world *World = new world(100, 100);

	user_interface *UI = new user_interface();

	terrain *Terrain = new terrain(World);

	mouse_picker TerrainPicker;
	TerrainPicker.Init(Terrain, &Graphics.GetCamera());

	Window.ShowMouseCursor(0);
	Window.ClipMouseCursor(1);

	bool EditMode = false;
	real32 MoveX = 0.0f;
	real32 MoveY = 0.0f;
	real32 MoveZ = 0.0f;
	int32 X = 0;
	int32 Y = 0;

	uint32 SystemInfoElement = UI->CreateElement(TOP_LEFT, 10.0f, 10.0f);
	uint32 T1 = UI->AddNewText(SystemInfoElement, "FPS");
	uint32 T2 = UI->AddNewText(SystemInfoElement, "Frame Time");
	uint32 T3 = UI->AddNewText(SystemInfoElement, "Camera Position");
	uint32 T4 = UI->AddNewText(SystemInfoElement, "Mouse World Position");
	UI->SetBackgroundColor(SystemInfoElement, { 0.25f, 0.25f, 0.25f, 0.75f });
	UI->SetOffset(SystemInfoElement, 10.0f, 10.0f);
	UI->SetMargin(SystemInfoElement, 10.0f);
	UI->SetAdjustWidthToText(SystemInfoElement, true);

	uint32 EditModeElement = UI->CreateElement(TOP_MIDDLE, 10.0f, 10.0f);
	UI->AddNewText(EditModeElement, "EDIT MODE ENABLED");
	UI->SetBackgroundColor(EditModeElement, { 0.25f, 0.25f, 0.25f, 0.75f });
	UI->SetOffset(EditModeElement, 0.0f, 10.0f);
	UI->SetMargin(EditModeElement, 20.0f);
	UI->SetHidden(EditModeElement, true);
	UI->SetAdjustHeightToText(EditModeElement, true);
	UI->SetAdjustWidthToText(EditModeElement, true);

	uint32 BottomLeft = UI->CreateElement(BOTTOM_LEFT, 10.0f, 10.0f);
	UI->SetBackgroundColor(BottomLeft, { 0.25f, 0.25f, 0.25f, 0.75f });
	UI->AddNewText(BottomLeft, "CONTROLS");
	UI->AddNewText(BottomLeft, "\n");
	UI->AddNewText(BottomLeft, "W, A, S, D");
	UI->AddNewText(BottomLeft, "Camera movement.");
	UI->AddNewText(BottomLeft, "\n");
	UI->AddNewText(BottomLeft, "Mouse X,Y Axis");
	UI->AddNewText(BottomLeft, "Camera look direction.");
	UI->AddNewText(BottomLeft, "\n");
	UI->AddNewText(BottomLeft, "CTRL, SPACE");
	UI->AddNewText(BottomLeft, "Move camera up and down.");
	UI->AddNewText(BottomLeft, "\n");
	UI->AddNewText(BottomLeft, "TAB");
	UI->AddNewText(BottomLeft, "Enable edit mode.");
	UI->AddNewText(BottomLeft, "\n");
	UI->AddNewText(BottomLeft, "LMB, MMB, RMB");
	UI->AddNewText(BottomLeft, "Add tile to the world map.");
	UI->SetOffset(BottomLeft, 10.0f, 10.0f);
	UI->SetMargin(BottomLeft, 10.0f);
	UI->SetAdjustHeightToText(BottomLeft, true);
	UI->SetAdjustWidthToText(BottomLeft, true);

	if(USE_MULTI_THREADING)
	{
		uint32 TopRight = UI->CreateElement(TOP_RIGHT, 10.0f, 10.0f);
		UI->SetBackgroundColor(TopRight, { 0.25f, 0.25f, 0.25f, 0.75f });
		UI->AddNewText(TopRight, "MULTI-THREADING ENABLED");
		UI->SetOffset(TopRight, 10.0f, 10.0f);
		UI->SetMargin(TopRight, 10.0f);
		UI->SetAdjustWidthToText(TopRight, true);
	}

	uint32 MouseTip = UI->CreateElement(MOUSE, 70.0f, 10.0f);
	UI->SetBackgroundColor(MouseTip, { 0.25f, 0.25f, 0.25f, 0.75f });
	UI->SetOffset(MouseTip, 10.0f, 10.0f);
	UI->SetMargin(MouseTip, 10.0f);
	UI->SetAdjustWidthToText(MouseTip, true);
	UI->SetHidden(MouseTip, true);
	uint32 MouseTipText = UI->AddNewText(MouseTip, "Info");

	while(true)
	{
		Timing.StartFrameTimer();

		// NOTE(Cristoffer): Safely shut down all working threads before destroying
		// all the instances and shutting down.
		if(!Running)
		{
			threading::GetInstance().WaitAllThreads();
			threading::GetInstance().TerminateAllThreads();

			break;
		}

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

		// TODO(Cristoffer): Temporary input control for adjusting camera.

		if(KeyReleased(KEY_TAB))
		{
			EditMode = !EditMode;

			if(EditMode) Window.ShowMouseCursor(1);
			if(!EditMode) Window.ShowMouseCursor(0);
		}

		real32 CameraMovementSpeed = (real32)Timing.GetFrameTimeDeltaMilliseconds() * (15.0f / 1000.0f);

		if(KeyPressed(KEY_SHIFT))
		{
			CameraMovementSpeed *= 6.0f;
		}

		if(!EditMode)
		{
			Graphics.GetCamera().LookX(((real32)Timing.GetFrameTimeDeltaSeconds() * GetMouseRawX() * 300.0f / 1000.0f));
			Graphics.GetCamera().LookY(((real32)Timing.GetFrameTimeDeltaSeconds() * GetMouseRawY() * 300.0f / 1000.0f));
		}
		
		if(EditMode)
		{
			TerrainPicker.TestMouseCollision();

			if(MousePressed(MOUSE_BUTTON_LEFT))
			{
				World->SetTile(global_data_collector::CurrentlyPickedTileX, global_data_collector::CurrentlyPickedTileY, ROAD_Z);
				Terrain->UpdateTileTypeResource(global_data_collector::CurrentlyPickedTileX, global_data_collector::CurrentlyPickedTileY, ROAD_Z);
			}

			if(MousePressed(MOUSE_BUTTON_RIGHT))
			{
				World->SetTile(global_data_collector::CurrentlyPickedTileX, global_data_collector::CurrentlyPickedTileY, ROAD_X);
				Terrain->UpdateTileTypeResource(global_data_collector::CurrentlyPickedTileX, global_data_collector::CurrentlyPickedTileY, ROAD_X);
			}

			if(MousePressed(MOUSE_BUTTON_MIDDLE))
			{
				World->SetTile(global_data_collector::CurrentlyPickedTileX, global_data_collector::CurrentlyPickedTileY, CROSSROAD);
				Terrain->UpdateTileTypeResource(global_data_collector::CurrentlyPickedTileX, global_data_collector::CurrentlyPickedTileY, CROSSROAD);
			}
		}

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

		if(KeyReleased(KEY_F5))
		{
			Persistence.SaveWorldMap(World);
		}

		if(KeyReleased(KEY_F9))
		{
			Persistence.LoadSavedWorldMap(World, Terrain);
		}

		UI->UpdateText(SystemInfoElement, T1, ("Frame Per Second: " + 
												std::to_string(Timing.GetFramesPerSecond())));

		UI->UpdateText(SystemInfoElement, T2, ("Frame Time Delta: " +
												std::to_string(Timing.GetFrameTimeDeltaMilliseconds())));

		UI->UpdateText(SystemInfoElement, T3, ("Camera Position: " + 
												std::to_string(Graphics.GetCamera().GetPositionX()) + ", " + 
												std::to_string(Graphics.GetCamera().GetPositionY()) + ", " + 
												std::to_string(Graphics.GetCamera().GetPositionZ())));
		
		UI->UpdateText(SystemInfoElement, T4, ("Mouse World Position: " +
												std::to_string(global_data_collector::CurrentlyPickedTileX) + ", " +
												std::to_string(global_data_collector::CurrentlyPickedTileY)));

		if(EditMode)
		{
			UI->SetHidden(EditModeElement, false);

			UI->SetHidden(MouseTip, false);

			UI->UpdateText(MouseTip, MouseTipText, 
			World->GetTileName((int32)global_data_collector::CurrentlyPickedTileX, (int32)global_data_collector::CurrentlyPickedTileY));
		}
		else if(!EditMode)
		{
			UI->SetHidden(EditModeElement, true);
			UI->SetHidden(MouseTip, true);
		}

		UI->BuildElements();

		// NOTE(Cristoffer): Temporary render test.
		Graphics.BeginFrame();

		Graphics.TestDrawTerrain(Terrain);
		Graphics.TestDraw();
		Graphics.TestDrawUI(UI);

		Graphics.EndFrame();

		Timing.EndFrameTimer();
	}
}