#include "render_queue.h"

std::vector<drawable*> render_queue::World;
std::vector<drawable*> render_queue::Agents;
std::vector<drawable*> render_queue::UserInterfaceLayer;
std::vector<drawable*> render_queue::Graphs;

void render_queue::Push(drawable *Drawable, render_layer Layer)
{
	if(Layer == render_layer::World)
	{
		World.push_back(Drawable);
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

void render_queue::Render()
{
	direct3d::BeginFrame();

	mouse_picker WorldPicker;

	for(auto Iterator = World.begin();
		Iterator != World.end();
		Iterator++)
	{
		(*Iterator)->Draw();

		if(application_state::GetEditModeEnabled())
		{
			bool32 Hit = WorldPicker.TestMouseCollision((*Iterator)->GetModel(), (*Iterator)->GetVertexTriangles());
			
			logger::LogUINT(WorldPicker.GetCollisionIndex(), logger::ref::CollisionIndex);
			logger::LogUINT(Hit, logger::ref::Hit);
		}
	}

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

		if(application_state::GetEditModeEnabled())
		{
			bool32 Hit = WorldPicker.TestMouseCollision((*Iterator)->GetModel(), (*Iterator)->GetVertexTriangles());
			
			logger::LogUINT(WorldPicker.GetCollisionIndex(), logger::ref::CollisionIndex);
			logger::LogUINT(Hit, logger::ref::Hit);
		}
	}

	direct3d::EndFrame();

	// TODO(Cristoffer): Should the render queue store drawables forever?
	// Store for now until entities is up and running.
	//World.clear();
	//Agents.clear();
	UserInterfaceLayer.clear();
	//Graphs.clear();
}