#pragma once

#include "common.h"
#include "direct3d.h"
#include "drawable.h"
#include "threading.h"
#include "mouse_picker.h"
#include "application_state.h"
#include "logger.h"

#include <vector>

enum class render_layer
{
	World, Agents, UserInterface, Graphs
};

class render_queue
{
	private:

	// TODO(Cristoffer): Containter for this.
	static std::vector<drawable*> World;
	static std::vector<drawable*> Agents;
	static std::vector<drawable*> UserInterfaceLayer;
	static std::vector<drawable*> Graphs;

	public:

	static void Init(){};
	static void Push(drawable *Drawable, render_layer Layer);
	static void Render();
};