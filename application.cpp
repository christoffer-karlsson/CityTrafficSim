#include "application.h"

// TODO: Move?
light_point		WorldLight;
camera_free		DebugCamera;
camera_pan		LockedCamera;
camera			*ActiveCamera;
world			World;

application::application() :
	Window("City Traffic Simulator and Planner | Mid Sweden University Thesis Project | Cristoffer Tanda", 1920, 1080), 
	Timing()
{
}

void application::Run()
{
	// Global statics.
	d3d_api::Init(Window.GetHandle());
	asset_manager::Init();
	logger::Init();
	entity_manager::Init();
	system_message::Init();
	render_manager::Init();

	DebugCamera.Init();
	LockedCamera.Init();
	World.Init(200, 200);

	R_SetActiveCamera(DebugCamera);

	WorldLight.Position = XMFLOAT3(55.0f, 735.0f, -440.0f);
	WorldLight.DiffuseColor = XMFLOAT3(0.87f, 0.81f, 0.78f);
	WorldLight.AmbientColor = XMFLOAT3(0.50f, 0.61f, 0.83f);

	render_manager::Push(World.GetTerrain(), render_layer::Terrain);

	// TODO: Temporary until permanent interface classes exists. /////////
	user_interface *UI = new user_interface();

	#if DEBUG_IMGUI

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO(); (void)io;
	io.WantCaptureMouse = true;
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(Window.GetHandle());
	ImGui_ImplDX11_Init(d3d_api::GetDevice(), d3d_api::GetContext());

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

	bool32 Load = Persistence.LoadSavedWorldMap();

	if(Load)
	{
		SystemMessage("World map loaded.");
		World.UpdateBuildings();
	}
	else
	{
		SystemMessage("Error! Could not open file.");
	}

	while(true)
	{
		Timing.StartFrameTimer();

		// Safely shut down all working threads, by waiting for work
		// to be done before destroying instances.
		if(!app_state::IsRunning())
		{
			if(d3d_api::Debug != nullptr)
			{
				d3d_api::Debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
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
			app_state::Shutdown();
		}

		#if DEBUG_IMGUI

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if(KeyReleased(KEY_F1))
		{
			app_state::ToggleDebugMenu();
		}

		if(app_state::GetDebugMenuEnabled())
		{
			Window.ShowMouseCursor(1);

			ImGui::Begin("Point light");

			ImGui::SliderFloat3("LightPosition", &WorldLight.Position.x, -1000.0f, 1000.0f);
			ImGui::SliderFloat3("DiffuseColor", &WorldLight.DiffuseColor.x, 0.0f, 1.0f);
			ImGui::SliderFloat3("Ambient", &WorldLight.AmbientColor.x, 0.0f, 1.0f);
			ImGui::SliderFloat("DiffuseIntensity", &WorldLight.DiffuseIntensity, 0.0f, 1.0f);
			ImGui::SliderFloat("AttenuationConstant", &WorldLight.AttenuationConstant, 0.0f, 1.0f);
			ImGui::SliderFloat("AttenuationLinear", &WorldLight.AttenuationLinear, 0.0f, 0.1f);
			ImGui::SliderFloat("AttenuationQuad", &WorldLight.AttenuationQuad, 0.0f, 0.1f);

			ImGui::End();
		}
		else
		{
			//Window.ShowMouseCursor(0);
		}

		#endif

		if(KeyReleased(KEY_TAB))
		{
			app_state::ToggleEditMode();

			if(app_state::GetEditModeEnabled()) Window.ShowMouseCursor(1);
			if(!app_state::GetEditModeEnabled()) Window.ShowMouseCursor(0);
		}

		real32 CameraMovementSpeed = (real32)Timing.GetFrameTimeDeltaMilliseconds() * (15.0f / 1000.0f);

		if(KeyPressed(KEY_SHIFT))
		{
			CameraMovementSpeed *= 6.0f;
		}

		if(!app_state::GetEditModeEnabled())
		{


			ActiveCamera->LookX(((real32)Timing.GetFrameTimeDeltaSeconds() * GetMouseRawX() * 300.0f / 1000.0f));
			ActiveCamera->LookY(((real32)Timing.GetFrameTimeDeltaSeconds() * GetMouseRawY() * 300.0f / 1000.0f));
		}

		if(KeyPressed(KEY_W))
		{
			ActiveCamera->MoveForward(CameraMovementSpeed);
		}

		if(KeyPressed(KEY_S))
		{
			ActiveCamera->MoveBackward(CameraMovementSpeed);
		}

		if(KeyPressed(KEY_A))
		{
			ActiveCamera->MoveLeft(CameraMovementSpeed);
		}

		if(KeyPressed(KEY_D))
		{
			ActiveCamera->MoveRight(CameraMovementSpeed);
		}

		if(KeyPressed(KEY_SPACE))
		{
			ActiveCamera->MoveUp(CameraMovementSpeed);
		}

		if(KeyPressed(KEY_CONTROL))
		{
			ActiveCamera->MoveDown(CameraMovementSpeed);
		}
		
		if(app_state::GetEditModeEnabled())
		{
			vec3u MousePosition = app_state::GetMouseCoordinateInWorldTruncated();

			if(MouseClicked(MOUSE_BUTTON_LEFT))
			{
				
			}

			if(MouseClicked(MOUSE_BUTTON_RIGHT))
			{
				entity_manager::CreateEntity(app_state::GetMouseCoordinateInWorld(), entity_type::Car);
			}

			if(MouseClicked(MOUSE_BUTTON_MIDDLE))
			{
				
			}

			if(KeyReleased(KEY_DELETE))
			{
				World.SetTile(MousePosition, tile_type::GRASS);

				SystemMessage("Tile deleted at " +
					std::to_string(MousePosition.x) + ", " +
					std::to_string(MousePosition.y) + ", " +
					std::to_string(MousePosition.z) + ".");
			}

			if(KeyReleased(KEY_1))
			{
				World.SetTile(MousePosition, tile_type::ROAD_Z);

				SystemMessage("Placed north-south road tile at " +
					std::to_string(MousePosition.x) + ", " +
					std::to_string(MousePosition.y) + ", " +
					std::to_string(MousePosition.z) + ".");
			}

			if(KeyReleased(KEY_2))
			{
				World.SetTile(MousePosition, tile_type::ROAD_X);

				SystemMessage("Placed east-west road tile at " +
					std::to_string(MousePosition.x) + ", " +
					std::to_string(MousePosition.y) + ", " +
					std::to_string(MousePosition.z) + ".");
			}

			if(KeyReleased(KEY_3))
			{
				World.SetTile(MousePosition, tile_type::CROSSROAD);

				SystemMessage("Placed crossroad tile at " +
					std::to_string(MousePosition.x) + ", " +
					std::to_string(MousePosition.y) + ", " +
					std::to_string(MousePosition.z) + ".");
			}

			if(KeyReleased(KEY_4))
			{
				World.SetTile(MousePosition, tile_type::GROUND);

				SystemMessage("Placed ground tile at " +
					std::to_string(MousePosition.x) + ", " +
					std::to_string(MousePosition.y) + ", " +
					std::to_string(MousePosition.z) + ".");
			}

			if(KeyReleased(KEY_5))
			{
				World.SetTile(MousePosition, tile_type::WATER);

				SystemMessage("Placed water tile at " +
					std::to_string(MousePosition.x) + ", " +
					std::to_string(MousePosition.y) + ", " +
					std::to_string(MousePosition.z) + ".");
			}

			if(KeyReleased(KEY_6))
			{
				World.SetTile(MousePosition, tile_type::BUILDING);

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
			bool32 Save = Persistence.SaveWorldMap();

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
			bool32 Load = Persistence.LoadSavedWorldMap();

			if(Load)
			{
				SystemMessage("World map loaded.");
				World.UpdateBuildings();
			}
			else
			{
				SystemMessage("Error! Could not open file.");
			}
		}

		if(KeyReleased(KEY_ARROWRIGHT))
		{
			
		}
		if(KeyReleased(KEY_ARROWLEFT))
		{
			
		}
		if(KeyReleased(KEY_ARROWDOWN))
		{
			
		}
		if(KeyReleased(KEY_ARROWUP))
		{
			
		}
		if(GetMouseScrollUp())
		{
			
		}
		if(GetMouseScrollDown())
		{
			
		}

		UI->UpdateText(SystemInfoElement, T1, ("Frame Per Second: " + 
												std::to_string(Timing.GetFramesPerSecond())));

		UI->UpdateText(SystemInfoElement, T2, ("Frame Time Delta: " +
												std::to_string(Timing.GetFrameTimeDeltaMilliseconds())));

		UI->UpdateText(SystemInfoElement, T3, ("Camera Position: " + 
												std::to_string(ActiveCamera->GetPosition().x) + ", " +
												std::to_string(ActiveCamera->GetPosition().y) + ", " +
												std::to_string(ActiveCamera->GetPosition().z)));

		UI->UpdateText(SystemInfoElement, T4, ("Light Source Position: " +
			std::to_string(WorldLight.Position.x) + ", " +
			std::to_string(WorldLight.Position.y) + ", " +
			std::to_string(WorldLight.Position.z)));

		UI->UpdateText(SystemInfoElement, T5, ("Entity Count: " +
			std::to_string(logger::GetUINT(logger::ref::EntityCount))));

		UI->UpdateText(SystemInfoElement, T6, ("Mouse World (Real): " +
			std::to_string(app_state::GetMouseCoordinateInWorld().x) + ", " +
			std::to_string(app_state::GetMouseCoordinateInWorld().y) + ", " +
			std::to_string(app_state::GetMouseCoordinateInWorld().z)));

		UI->UpdateText(SystemInfoElement, T7, ("Mouse World (Trunc): " +
			std::to_string(app_state::GetMouseCoordinateInWorldTruncated().x) + ", " +
			std::to_string(app_state::GetMouseCoordinateInWorldTruncated().y) + ", " +
			std::to_string(app_state::GetMouseCoordinateInWorldTruncated().z)));

		if(app_state::GetEditModeEnabled())
		{
			render_manager::TestMouseCollision();

			UI->SetHidden(EditModeElement, false);

			UI->SetHidden(MouseTip, false);

			UI->UpdateText(MouseTip, MouseTipText,
				World.GetTileDescription(Truncate(app_state::GetMouseCoordinateInWorld())));
		}
		else if(!app_state::GetEditModeEnabled())
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

	#if DEBUG_IMGUI
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	#endif
}