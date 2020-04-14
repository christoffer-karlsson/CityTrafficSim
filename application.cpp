#include "application.h"

application::application() :
	Window("City Traffic Simulator and Planner | Mid Sweden University Thesis Project | Cristoffer Tanda", 1920, 1080), 
	Timing(), 
	Running(true)
{
}

void application::Run()
{
	// NOTE(Cristoffer): Statics.
	direct3d::Init(Window.GetHandle());
	camera::Init();
	entity_manager::Init();
	system_message::Init();
	render_queue::Init();
	light_source::Init();

	// TODO(Cristoffer): Temporary until permanent interface classes exists. /////////
	world *World = new world(200, 200);
	user_interface *UI = new user_interface();
	entity_manager *EntityManager = new entity_manager();
	//mouse_picker TerrainPicker(World, World->Terrain, &Graphics.GetCamera());
	///////////////////////////////////////////////////////////////////////////////////

	Window.ShowMouseCursor(0);
	Window.ClipMouseCursor(1);

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
	uint32 T6 = UI->AddNewText(SystemInfoElement, "Test");
	uint32 T7 = UI->AddNewText(SystemInfoElement, "Test");
	uint32 T8 = UI->AddNewText(SystemInfoElement, "Test");
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

		if(KeyReleased(KEY_TAB))
		{
			application_state::ToggleEditMode();

			if(application_state::GetEditModeEnabled()) Window.ShowMouseCursor(1);
			if(!application_state::GetEditModeEnabled()) Window.ShowMouseCursor(0);
		}

		real32 CameraMovementSpeed = (real32)Timing.GetFrameTimeDeltaMilliseconds() * (15.0f / 1000.0f);

		if(KeyPressed(KEY_SHIFT))
		{
			CameraMovementSpeed *= 6.0f;
		}

		if(!application_state::GetEditModeEnabled())
		{
			camera::LookX(((real32)Timing.GetFrameTimeDeltaSeconds() * GetMouseRawX() * 300.0f / 1000.0f));
			camera::LookY(((real32)Timing.GetFrameTimeDeltaSeconds() * GetMouseRawY() * 300.0f / 1000.0f));
		}
		
		if(application_state::GetEditModeEnabled())
		{
			if(MouseClicked(MOUSE_BUTTON_LEFT))
			{
				//World->SetTile(0, 0, tile_type::ROAD_Z);
				//SystemMessage("Placed Z road tile at: " + std::to_string(CurrentlyPickedTileX) + ", " + std::to_string(CurrentlyPickedTileY) + ".");
			}

			if(MouseClicked(MOUSE_BUTTON_RIGHT))
			{
				//World->SetTile(CurrentlyPickedTileX, CurrentlyPickedTileY, tile_type::ROAD_X);
				//SystemMessage("Placed X road tile at: " + std::to_string(CurrentlyPickedTileX) + ", " + std::to_string(CurrentlyPickedTileY) + ".");
			}

			if(MouseClicked(MOUSE_BUTTON_MIDDLE))
			{
				//World->SetTile(CurrentlyPickedTileX, CurrentlyPickedTileY, tile_type::CROSSROAD);
				//SystemMessage("Placed crossroad tile at: " + std::to_string(CurrentlyPickedTileX) + ", " + std::to_string(CurrentlyPickedTileY) + ".");
			}

			if(MouseClicked(MOUSE_BUTTON_MIDDLE))
			{
				//World->SetTile(CurrentlyPickedTileX, CurrentlyPickedTileY, tile_type::CROSSROAD);
				//SystemMessage("Placed crossroad tile at: " + std::to_string(CurrentlyPickedTileX) + ", " + std::to_string(CurrentlyPickedTileY) + ".");
			}

			if(KeyReleased(KEY_DELETE))
			{
				//World->SetTile(CurrentlyPickedTileX, CurrentlyPickedTileY, tile_type::GRASS);
				//SystemMessage("Tile deleted at: " + std::to_string(CurrentlyPickedTileX) + ", " + std::to_string(CurrentlyPickedTileY) + ".");
			}
		}

		if(KeyPressed(KEY_W))
		{
			camera::MoveForward(CameraMovementSpeed);
		}

		if(KeyPressed(KEY_S))
		{
			camera::MoveBackward(CameraMovementSpeed);
		}

		if(KeyPressed(KEY_A))
		{
			camera::StrafeLeft(CameraMovementSpeed);
		}

		if(KeyPressed(KEY_D))
		{
			camera::StrafeRight(CameraMovementSpeed);
		}

		if(KeyPressed(KEY_SPACE))
		{
			camera::MoveUp(CameraMovementSpeed);
		}

		if(KeyPressed(KEY_CONTROL))
		{
			camera::MoveDown(CameraMovementSpeed);
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
			entity_manager::CreateEntity({1.0f, 1.0f, 1.0f}, entity_type::Vehicle);
		}
		if(KeyReleased(KEY_2))
		{
			
		}

		UI->UpdateText(SystemInfoElement, T1, ("Frame Per Second: " + 
												std::to_string(Timing.GetFramesPerSecond())));

		UI->UpdateText(SystemInfoElement, T2, ("Frame Time Delta: " +
												std::to_string(Timing.GetFrameTimeDeltaMilliseconds())));

		UI->UpdateText(SystemInfoElement, T3, ("Camera Position: " + 
												std::to_string(camera::GetPositionX()) + ", " +
												std::to_string(camera::GetPositionY()) + ", " +
												std::to_string(camera::GetPositionZ())));
		
		UI->UpdateText(SystemInfoElement, T4, ("Mouse World Position: " +
												std::to_string(0) + ", " +
												std::to_string(0)));

		UI->UpdateText(SystemInfoElement, T5, ("Light Source Position: " +
			std::to_string(light_source::Position.x) + ", " +
			std::to_string(light_source::Position.y) + ", " +
			std::to_string(light_source::Position.z)));

		UI->UpdateText(SystemInfoElement, T6, ("CollisionIndex: " +
			std::to_string(logger::GetUINT(logger::ref::CollisionIndex))));

		UI->UpdateText(SystemInfoElement, T7, ("Hit: " +
			std::to_string(logger::GetUINT(logger::ref::Hit))));

		if(application_state::GetEditModeEnabled())
		{
			UI->SetHidden(EditModeElement, false);

			UI->SetHidden(MouseTip, false);

			UI->UpdateText(MouseTip, MouseTipText,
				World->GetTileName(/*CurrentlyPickedTileX*/0, /*CurrentlyPickedTileY*/0));
		}
		else if(!application_state::GetEditModeEnabled())
		{
			UI->SetHidden(EditModeElement, true);
			UI->SetHidden(MouseTip, true);
		}

		UI->BuildElements();

		render_queue::Push(UI, render_layer::UserInterface);

		system_message::Update();

		entity_manager::Simulate();

		render_queue::Render();

		Timing.EndFrameTimer();
	}
}