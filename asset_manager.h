#pragma once

#include "common.h"
#include "persistence.h"
#include "mesh.h"

#define MAX_MODEL_FILES 5

// NOTE(Cristoffer): Check for nullptr when getting assets.
class asset_manager
{
	private:

	static mesh *Mesh[MAX_MODEL_FILES];

	public:

	static void Init();

	static mesh *GetMesh(uint32 ID);
};