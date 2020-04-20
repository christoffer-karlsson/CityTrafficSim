#pragma once

#include "common.h"
#include "direct3d.h"
#include "drawable.h"
#include "threading.h"
#include "mouse_picker.h"
#include "application_state.h"
#include "logger.h"
#include "drawable_cars.h"
#include "asset_manager.h"

#include <vector>

enum class render_layer
{
	Terrain, Agents, UserInterface, Graphs, Instanced
};

class render_manager
{
	private:

	static work_id ThreadWorkID;

	static vec3u OldCollisionPosition;

	// TODO(Cristoffer): Containter for this.
	static drawable *Terrain;
	static drawable_cars *InstancedCars;

	static std::vector<drawable*> Agents;
	static std::vector<drawable*> UserInterfaceLayer;
	static std::vector<drawable*> Graphs;

	public:

	static void Init();
	static void Push(drawable *Drawable, render_layer Layer);
	static void Render();
	static void TestMouseCollision();

	static drawable_cars *GetInstancedCars();
};