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
	asset_manager::Init();
	camera::Init();
	logger::Init();
	entity_manager::Init();
	system_message::Init();
	render_manager::Init();
	
	light_source::Init();

	world *World = new world(200, 200);

	render_manager::Push(World->GetTerrain(), render_layer::Terrain);

	// TODO(Cristoffer): Temporary until permanent interface classes exists. /////////
	user_interface *UI = new user_interface();

	#if DEBUG_MODE

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO(); (void)io;
	io.WantCaptureMouse = true;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(Window.GetHandle());
	ImGui_ImplDX11_Init(direct3d::GetDevice(), direct3d::GetContext());

	#endif

	Window.ShowMouseCursor(0);
	Window.ClipMouseCursor(1);

	uint32 SystemInfoElement = UI->CreateElement(screen_anchor::TOP_LEFT, 10.0f, 10.0f);
	uint32 T1 = UI->AddNewText(SystemInfoElement, "<element>");
	uint32 T2 = UI->AddNewText(SystemInfoElement, "<element>");
	uint32 T3 = UI->AddNewText(SystemInfoElement, "<element>");
	uint32 T4 = UI->AddNewText(SystemInfoElement, "<element>");
	uint32 T5 = UI->AddNewText(SystemInfoElement, "<element>");
	uint32 T6 = UI->AddNewText(SystemInfoElement, "<element>");
	uint32 T7 = UI->AddNewText(SystemInfoElement, "<element>");
	//uint32 T8 = UI->AddNewText(SystemInfoElement, "<element>");
	//uint32 T9 = UI->AddNewText(SystemInfoElement, "<element>");
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

	bool32 Load = Persistence.LoadSavedWorldMap(World);

	if(Load)
	{
		SystemMessage("World map loaded.");
		World->UpdateBuildings();
	}
	else
	{
		SystemMessage("Error! Could not open file.");
	}

	while(true)
	{
		Timing.StartFrameTimer();

		// NOTE(Cristoffer): Safely shut down all working threads before destroying
		// all the instances and shutting down.
		if(!Running)
		{
			if(direct3d::Debug != nullptr)
			{
				direct3d::Debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
			}
			
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

		#if DEBUG_MODE

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if(KeyReleased(KEY_F1))
		{
			application_state::ToggleDebugMenu();
		}

		if(application_state::GetDebugMenuEnabled())
		{
			Window.ShowMouseCursor(1);
			camera::DisableInput();

			ImGui::Begin("Point light");

			ImGui::SliderFloat3("LightPosition", &light_source::ConstantBuffer.LightPosition.x, -1000.0f, 1000.0f);
			ImGui::SliderFloat3("DiffuseColor", &light_source::ConstantBuffer.DiffuseColor.x, 0.0f, 1.0f);
			ImGui::SliderFloat3("Ambient", &light_source::ConstantBuffer.Ambient.x, 0.0f, 1.0f);
			ImGui::SliderFloat("DiffuseIntensity", &light_source::ConstantBuffer.DiffuseIntensity, 0.0f, 1.0f);
			ImGui::SliderFloat("AttenuationConstant", &light_source::ConstantBuffer.AttenuationConstant, 0.0f, 1.0f);
			ImGui::SliderFloat("AttenuationLinear", &light_source::ConstantBuffer.AttenuationLinear, 0.0f, 0.1f);
			ImGui::SliderFloat("AttenuationQuad", &light_source::ConstantBuffer.AttenuationQuad, 0.0f, 0.1f);

			ImGui::End();
		}
		else
		{
			//Window.ShowMouseCursor(0);
			camera::EnableInput();
		}

		#endif

		if(KeyReleased(KEY_TAB))
		{
			application_state::ToggleEditMode();

			if(application_state::GetEditModeEnabled()) Window.ShowMouseCursor(1);
			if(!application_state::GetEditModeEnabled()) Window.ShowMouseCursor(0);
		}

		CameraControl();
		
		if(application_state::GetEditModeEnabled())
		{
			vec3u MousePosition = application_state::GetMouseCoordinateInWorldTrunc();

			if(MouseClicked(MOUSE_BUTTON_LEFT))
			{
				
			}

			if(MouseClicked(MOUSE_BUTTON_RIGHT))
			{
				entity_manager::CreateEntity(application_state::GetMouseCoordinateInWorld(), entity_type::Car);
			}

			if(MouseClicked(MOUSE_BUTTON_MIDDLE))
			{
				
			}

			if(KeyReleased(KEY_DELETE))
			{
				World->SetTile(MousePosition, tile_type::GRASS);

				SystemMessage("Tile deleted at " +
					std::to_string(MousePosition.x) + ", " +
					std::to_string(MousePosition.y) + ", " +
					std::to_string(MousePosition.z) + ".");
			}

			if(KeyReleased(KEY_1))
			{
				World->SetTile(MousePosition, tile_type::ROAD_Z);

				SystemMessage("Placed north-south road tile at " +
					std::to_string(MousePosition.x) + ", " +
					std::to_string(MousePosition.y) + ", " +
					std::to_string(MousePosition.z) + ".");
			}

			if(KeyReleased(KEY_2))
			{
				World->SetTile(MousePosition, tile_type::ROAD_X);

				SystemMessage("Placed east-west road tile at " +
					std::to_string(MousePosition.x) + ", " +
					std::to_string(MousePosition.y) + ", " +
					std::to_string(MousePosition.z) + ".");
			}

			if(KeyReleased(KEY_3))
			{
				World->SetTile(MousePosition, tile_type::CROSSROAD);

				SystemMessage("Placed crossroad tile at " +
					std::to_string(MousePosition.x) + ", " +
					std::to_string(MousePosition.y) + ", " +
					std::to_string(MousePosition.z) + ".");
			}

			if(KeyReleased(KEY_4))
			{
				World->SetTile(MousePosition, tile_type::GROUND);

				SystemMessage("Placed ground tile at " +
					std::to_string(MousePosition.x) + ", " +
					std::to_string(MousePosition.y) + ", " +
					std::to_string(MousePosition.z) + ".");
			}

			if(KeyReleased(KEY_5))
			{
				World->SetTile(MousePosition, tile_type::WATER);

				SystemMessage("Placed water tile at " +
					std::to_string(MousePosition.x) + ", " +
					std::to_string(MousePosition.y) + ", " +
					std::to_string(MousePosition.z) + ".");
			}

			if(KeyReleased(KEY_6))
			{
				World->SetTile(MousePosition, tile_type::BUILDING);

				SystemMessage("Placed building tile at " +
					std::to_string(MousePosition.x) + ", " +
					std::to_string(MousePosition.y) + ", " +
					std::to_string(MousePosition.z) + ".");
			}
		}

		if(KeyReleased(KEY_8))
		{
			//entity_manager::CreateEntity(application_state::GetMouseCoordinateInWorld(), entity_type::Car);
		}

		if(KeyReleased(KEY_9))
		{
			/*for(uint32 x = 0;
				x < 70;
				x++)
			{
				for(uint32 z = 0;
					z < 70;
					z++)
				{
					entity_manager::CreateEntity(vec3((real32)x + (x + 2.0f), 0.0f, (real32)z + (z + 2.0f)), entity_type::Car);
				}
			}*/
			//entity_manager::CreateEntity(vec3(0.0f, 0.0f, 0.0f), entity_type::Car);
		}

		if(KeyReleased(KEY_F5))
		{
			bool32 Save = Persistence.SaveWorldMap(World);

			if(Save)
			{
				SystemMessage("World map saved.");
			}
			else
			{
				SystemMessage("Error! Could not open file.");
			}
		}

		if(KeyReleased(KEY_F9))
		{
			bool32 Load = Persistence.LoadSavedWorldMap(World);

			if(Load)
			{
				SystemMessage("World map loaded.");
				World->UpdateBuildings();
			}
			else
			{
				SystemMessage("Error! Could not open file.");
			}
		}

		if(KeyReleased(KEY_ARROWRIGHT))
		{
			//PosX += 1.0f;
			//light_source::Position.x += +1.0f;
			//Object.SetPosition({ PosX, PosY, PosZ });
		}
		if(KeyReleased(KEY_ARROWLEFT))
		{
			//PosX -= 1.0f;
			//light_source::SetPosition.x += -1.0f;
			//Object.SetPosition({ PosX, PosY, PosZ });
		}
		if(KeyReleased(KEY_ARROWDOWN))
		{
			//PosZ -= 1.0f;
			//light_source::Position.z += +1.0f;
			//Object.SetPosition({ PosX, PosY, PosZ });
		}
		if(KeyReleased(KEY_ARROWUP))
		{
			//PosZ += 1.0f;
			//light_source::Position.z += +1.0f;
			//Object.SetPosition({ PosX, PosY, PosZ });
		}
		if(GetMouseScrollUp())
		{
			vec3 Position = light_source::GetPosition();
			Position.y += 5.0f;
			light_source::SetPosition(Position);
		}
		if(GetMouseScrollDown())
		{
			vec3 Position = light_source::GetPosition();
			Position.y -= 5.0f;
			light_source::SetPosition(Position);
		}

		UI->UpdateText(SystemInfoElement, T1, ("Frame Per Second: " + 
												std::to_string(Timing.GetFramesPerSecond())));

		UI->UpdateText(SystemInfoElement, T2, ("Frame Time Delta: " +
												std::to_string(Timing.GetFrameTimeDeltaMilliseconds())));

		UI->UpdateText(SystemInfoElement, T3, ("Camera Position: " + 
												std::to_string(camera::GetPositionX()) + ", " +
												std::to_string(camera::GetPositionY()) + ", " +
												std::to_string(camera::GetPositionZ())));

		vec3 LightPosition = light_source::GetPosition();

		UI->UpdateText(SystemInfoElement, T4, ("Light Source Position: " +
			std::to_string(LightPosition.x) + ", " +
			std::to_string(LightPosition.y) + ", " +
			std::to_string(LightPosition.z)));

		UI->UpdateText(SystemInfoElement, T5, ("Entity Count: " +
			std::to_string(logger::GetUINT(logger::ref::EntityCount))));

		UI->UpdateText(SystemInfoElement, T6, ("Mouse World (Real): " +
			std::to_string(application_state::GetMouseCoordinateInWorld().x) + ", " +
			std::to_string(application_state::GetMouseCoordinateInWorld().y) + ", " +
			std::to_string(application_state::GetMouseCoordinateInWorld().z)));

		UI->UpdateText(SystemInfoElement, T7, ("Mouse World (Trunc): " +
			std::to_string(application_state::GetMouseCoordinateInWorldTrunc().x) + ", " +
			std::to_string(application_state::GetMouseCoordinateInWorldTrunc().y) + ", " +
			std::to_string(application_state::GetMouseCoordinateInWorldTrunc().z)));

		if(application_state::GetEditModeEnabled())
		{
			render_manager::TestMouseCollision();

			UI->SetHidden(EditModeElement, false);

			UI->SetHidden(MouseTip, false);

			UI->UpdateText(MouseTip, MouseTipText,
				World->GetTileDescription(Truncate(application_state::GetMouseCoordinateInWorld())));
		}
		else if(!application_state::GetEditModeEnabled())
		{
			UI->SetHidden(EditModeElement, true);
			UI->SetHidden(MouseTip, true);
		}

		UI->BuildElements();

		render_manager::Push(UI, render_layer::UserInterface);

		system_message::Update();

		entity_manager::Simulate();

		render_manager::Render();

		Timing.EndFrameTimer();
	}

	#if DEBUG_MODE
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	#endif
}

void application::CameraControl()
{
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
}
