#include "render_manager.h"

work_id render_manager::ThreadWorkID;

vec3u render_manager::OldCollisionPosition;

drawable *render_manager::Terrain;
drawable_cars *render_manager::Cars;
drawable_buildings *render_manager::Buildings;

std::vector<drawable*> render_manager::Agents;
std::vector<drawable*> render_manager::UserInterfaceLayer;
std::vector<drawable*> render_manager::Graphs;

void render_manager::Init()
{
	// NOTE(Cristoffer): Instanced drawables.
	Cars = new drawable_cars(asset_manager::GetMesh(asset_mesh_car_indexed));
	Buildings = new drawable_buildings(asset_manager::GetMesh(asset_mesh_building));
}

void render_manager::Push(drawable *Drawable, render_layer Layer)
{
	if(Layer == render_layer::Terrain)
	{
		Terrain = Drawable;
	}

	if(Layer == render_layer::Agents)
	{
		Agents.push_back(Drawable);
	}

	if(Layer == render_layer::UserInterface)
	{
		UserInterfaceLayer.push_back(Drawable);
	}

	if(Layer == render_layer::Graphs)
	{
		Graphs.push_back(Drawable);
	}
}

void render_manager::Render()
{
	d3d_api::BeginFrame();

	Terrain->Draw();

	if(!app_state::GetEditModeEnabled())
	{
		Buildings->Draw();
	}

	Cars->Draw();

	for(auto Iterator = Agents.begin();
		Iterator != Agents.end();
		Iterator++)
	{
		(*Iterator)->Draw();
	}

	for(auto Iterator = Graphs.begin();
		Iterator != Graphs.end();
		Iterator++)
	{
		(*Iterator)->Draw();
	}

	for(auto Iterator = UserInterfaceLayer.begin();
		Iterator != UserInterfaceLayer.end();
		Iterator++)
	{
		(*Iterator)->Draw();
	}

	#if DEBUG_IMGUI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	#endif

	d3d_api::EndFrame();

	// NOTE(Cristoffer): Renderer only stores drawable pointers that
	// should get drawn for the frame, then clears them, with some exceptions
	// like the terrain, which is permanent.
	Agents.clear();
	UserInterfaceLayer.clear();
}

void render_manager::TestMouseCollision()
{
	auto ThreadWork = [&]
	{
		mouse_picker WorldPicker;

		bool32 Hit = WorldPicker.TestMouseCollision(Terrain->GetWorldModel().GetMatrix(), Terrain->GetCollisionModel());

		Terrain->UpdateHighlightColorResource(OldCollisionPosition, 0);

		if(Hit)
		{
			vec3 NewCollisionPosition = WorldPicker.GetCollisionPosition();

			app_state::SetMouseCoordinateInWorld(NewCollisionPosition);

			vec3u NewCollisionPositionTruncated = app_state::GetMouseCoordinateInWorldTruncated();

			Terrain->UpdateHighlightColorResource(NewCollisionPositionTruncated, 1);

			OldCollisionPosition = NewCollisionPositionTruncated;
		}
	};

	if(USE_MULTI_THREADING)
	{
		if(thread_pool.WorkDone(ThreadWorkID))
		{
			thread_pool.AddBackgroundWork(ThreadWorkID, ThreadWork);
		}
	}
	else
	{
		ThreadWork();
	}
}

drawable_cars *render_manager::GetDrawableCars()
{
	return Cars;
}

drawable_buildings *render_manager::GetDrawableBuildings()
{
	return Buildings;
}
