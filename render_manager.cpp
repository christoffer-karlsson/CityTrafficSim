#include "render_manager.h"

work_id render_manager::ThreadWorkID;

vec3u render_manager::OldCollisionPosition;

drawable *render_manager::Terrain;

std::vector<drawable*> render_manager::Agents;
std::vector<drawable*> render_manager::UserInterfaceLayer;
std::vector<drawable*> render_manager::Graphs;

void render_manager::Init()
{
	
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
	direct3d::BeginFrame();

	Terrain->Draw();

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

	direct3d::EndFrame();

	// NOTE(Cristoffer): Renderer only stores drawable pointers that
	// should get drawn for the frame, then clears them, with some exceptions
	// like the terrain, which is permanent.
	//World.clear();
	Agents.clear();
	UserInterfaceLayer.clear();
	//Graphs.clear();
}

void render_manager::TestMouseCollision()
{
	auto ThreadWork = [&]
	{
		mouse_picker WorldPicker;

		bool32 Hit = WorldPicker.TestMouseCollision(Terrain->GetModel(), Terrain->GetCollisionModel());

		Terrain->UpdateHighlightColorResource(OldCollisionPosition, 0);

		if(Hit)
		{
			vec3 NewCollisionPosition = WorldPicker.GetCollisionPosition();

			application_state::SetMouseCoordinateInWorld(NewCollisionPosition);

			vec3u NewCollisionPositionTruncated = application_state::GetMouseCoordinateInWorldTrunc();

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