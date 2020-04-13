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
	// TODO(Cristoffer): Temporary until permanent interface classes exists. /////////
	world *World = new world(200, 200);
	user_interface *UI = new user_interface();
	entity_manager *EntityManager = new entity_manager();
	//object Object;
	mouse_picker TerrainPicker(World, World->Terrain, &Graphics.GetCamera());

	light_source::Init();
	///////////////////////////////////////////////////////////////////////////////////

	Window.ShowMouseCursor(0);
	Window.ClipMouseCursor(1);

	bool32 EditMode = false;

	real32 MoveX = 0.0f;
	real32 MoveY = 0.0f;
	real32 MoveZ = 0.0f;

	real32 PosX = 0.0f;
	real32 PosY = 0.0f;
	real32 PosZ = 0.0f;
	real32 Angle = 0.0f;
	real32 Scale = 0.0f;

	uint32 SystemInfoElement = UI->CreateElement(screen_anchor::TOP_LEFT, 10.0f, 10.0f);
	uint32 T1 = UI->AddNewText(SystemInfoElement, "FPS");
	uint32 T2 = UI->AddNewText(SystemInfoElement, "Frame Time");
	uint32 T3 = UI->AddNewText(SystemInfoElement, "Camera Position");
	uint32 T4 = UI->AddNewText(SystemInfoElement, "Mouse World Position");
	uint32 T5 = UI->AddNewText(SystemInfoElement, "Test");
	UI->SetBackgroundColor(SystemInfoElement, { 0.25f, 0.25f, 0.25f, 0.5f });
	UI->SetOffset(SystemInfoElement, 10.0f, 10.0f);
	UI->SetMargin(SystemInfoElement, 10.0f);
	UI->SetAdjustWidthToText(SystemInfoElement, true);

	uint32 EditModeElement = UI->CreateElement(screen_anchor::TOP_MIDDLE, 10.0f, 10.0f);
	UI->AddNewText(EditModeElement, "EDIT MODE ENABLED");
	UI->SetBackgroundColor(EditModeElement, { 0.25f, 0.25f, 0.25f, 0.5f });
	UI->SetOffset(EditModeElement, 0.0f, 10.0f);
	UI->SetMargin(EditModeElement, 20.0f);
	UI->SetHidden(EditModeElement, true);
	UI->SetAdjustHeightToText(EditModeElement, true);
	UI->SetAdjustWidthToText(EditModeElement, true);

	uint32 BottomLeft = UI->CreateElement(screen_anchor::BOTTOM_LEFT, 10.0f, 10.0f);
	UI->SetBackgroundColor(BottomLeft, { 0.25f, 0.25f, 0.25f, 0.5f });
	UI->AddNewText(BottomLeft, "CONTROLS");
	UI->AddNewText(BottomLeft, "\n");
	UI->AddNewText(BottomLeft, "W/A/S/D");
	UI->AddNewText(BottomLeft, "Camera movement.");
	UI->AddNewText(BottomLeft, "\n");
	UI->AddNewText(BottomLeft, "Mouse");
	UI->AddNewText(BottomLeft, "Camera look direction.");
	UI->AddNewText(BottomLeft, "\n");
	UI->AddNewText(BottomLeft, "CTRL/SPACE");
	UI->AddNewText(BottomLeft, "Move camera up and down.");
	UI->AddNewText(BottomLeft, "\n");
	UI->AddNewText(BottomLeft, "TAB");
	UI->AddNewText(BottomLeft, "Enable edit mode.");
	UI->AddNewText(BottomLeft, "\n");
	UI->AddNewText(BottomLeft, "LMB/MMB/RMB");
	UI->AddNewText(BottomLeft, "Add tile to the world map.");
	UI->AddNewText(BottomLeft, "\n");
	UI->AddNewText(BottomLeft, "F5/F9");
	UI->AddNewText(BottomLeft, "Save/Load tile map.");
	UI->SetOffset(BottomLeft, 10.0f, 10.0f);
	UI->SetMargin(BottomLeft, 10.0f);
	UI->SetAdjustHeightToText(BottomLeft, true);
	UI->SetAdjustWidthToText(BottomLeft, true);

	if(USE_MULTI_THREADING)
	{
		uint32 TopRight = UI->CreateElement(screen_anchor::TOP_RIGHT, 10.0f, 10.0f);
		UI->SetBackgroundColor(TopRight, { 0.25f, 0.25f, 0.25f, 0.5f });
		UI->AddNewText(TopRight, "MULTI-THREADING ENABLED");
		UI->SetOffset(TopRight, 10.0f, 10.0f);
		UI->SetMargin(TopRight, 10.0f);
		UI->SetAdjustWidthToText(TopRight, true);
	}

	uint32 MouseTip = UI->CreateElement(screen_anchor::MOUSE, 70.0f, 10.0f);
	UI->SetBackgroundColor(MouseTip, { 0.25f, 0.25f, 0.25f, 0.5f });
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

			if(MouseClicked(MOUSE_BUTTON_LEFT))
			{
				World->SetTile(global_data_collector::CurrentlyPickedTileX, global_data_collector::CurrentlyPickedTileY, tile_type::ROAD_Z);
				SystemMessage("Placed Z road tile at: " + std::to_string((int32)global_data_collector::CurrentlyPickedTileX) + ", " + std::to_string((int32)global_data_collector::CurrentlyPickedTileY) + ".");
			}

			if(MouseClicked(MOUSE_BUTTON_RIGHT))
			{
				World->SetTile(global_data_collector::CurrentlyPickedTileX, global_data_collector::CurrentlyPickedTileY, tile_type::ROAD_X);
				SystemMessage("Placed X road tile at: " + std::to_string((int32)global_data_collector::CurrentlyPickedTileX) + ", " + std::to_string((int32)global_data_collector::CurrentlyPickedTileY) + ".");
			}

			if(MouseClicked(MOUSE_BUTTON_MIDDLE))
			{
				World->SetTile(global_data_collector::CurrentlyPickedTileX, global_data_collector::CurrentlyPickedTileY, tile_type::CROSSROAD);
				SystemMessage("Placed crossroad tile at: " + std::to_string((int32)global_data_collector::CurrentlyPickedTileX) + ", " + std::to_string((int32)global_data_collector::CurrentlyPickedTileY) + ".");
			}

			if(MouseClicked(MOUSE_BUTTON_MIDDLE))
			{
				World->SetTile(global_data_collector::CurrentlyPickedTileX, global_data_collector::CurrentlyPickedTileY, tile_type::CROSSROAD);
				SystemMessage("Placed crossroad tile at: " + std::to_string((int32)global_data_collector::CurrentlyPickedTileX) + ", " + std::to_string((int32)global_data_collector::CurrentlyPickedTileY) + ".");
			}

			if(KeyReleased(KEY_DELETE))
			{
				World->SetTile(global_data_collector::CurrentlyPickedTileX, global_data_collector::CurrentlyPickedTileY, tile_type::GRASS);
				SystemMessage("Tile deleted at: " + std::to_string((int32)global_data_collector::CurrentlyPickedTileX) + ", " + std::to_string((int32)global_data_collector::CurrentlyPickedTileY) + ".");
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
			Persistence.LoadSavedWorldMap(World);
		}

		if(KeyReleased(KEY_ARROWRIGHT))
		{
			PosX += 1.0f;
			light_source::Position.x += +1.0f;
			//Object.SetPosition({ PosX, PosY, PosZ });
		}
		if(KeyReleased(KEY_ARROWLEFT))
		{
			PosX -= 1.0f;
			light_source::Position.x += -1.0f;
			//Object.SetPosition({ PosX, PosY, PosZ });
		}
		if(KeyReleased(KEY_ARROWDOWN))
		{
			PosZ -= 1.0f;
			light_source::Position.z += +1.0f;
			//Object.SetPosition({ PosX, PosY, PosZ });
		}
		if(KeyReleased(KEY_ARROWUP))
		{
			PosZ += 1.0f;
			light_source::Position.z += +1.0f;
			//Object.SetPosition({ PosX, PosY, PosZ });
		}
		if(GetMouseScrollUp())
		{
			Angle += 1.0f;
			light_source::Position.y += +1.0f;
			//Object.SetRotation({ 0.0f, Angle, 0.0f });
		}
		if(GetMouseScrollDown())
		{
			Angle -= 1.0f;
			light_source::Position.y += -1.0f;
			//Object.SetRotation({ 0.0f, Angle, 0.0f });
		}

		if(KeyReleased(KEY_1))
		{
			sys_message.Push("Added new message.");
		}
		if(KeyReleased(KEY_2))
		{
			sys_message.Push("Added new message.");
		}

		//Object.UpdateModel();

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

		UI->UpdateText(SystemInfoElement, T5, ("Light Source Position: " +
			std::to_string(light_source::Position.x) + ", " +
			std::to_string(light_source::Position.y) + ", " +
			std::to_string(light_source::Position.z)));

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

		//global_device_info::Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//Object.Draw(Graphics.GetCamera());
		
		Graphics.TestDrawTerrain(World->Terrain);
		Graphics.TestDrawLines();
		Graphics.TestDrawUI(UI);

		global_device_info::Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		system_message::GetInstance().Display(Graphics.GetCamera());

		Graphics.EndFrame();

		Timing.EndFrameTimer();
	}
}