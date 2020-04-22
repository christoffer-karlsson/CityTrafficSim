#pragma once

#include "common.h"
#include "persistence.h"
#include "mesh.h"

#define MAX_MODEL_FILES 100

// TODO(Cristofer): Might need a better way for this. Temporary use defines
// to refer to objects for now.
#define ASSET_MESH_CAR 0
#define ASSET_MESH_CAR_INDEXED 1
#define ASSET_MESH_BUILDING 2
#define ASSET_MESH_BUILDING_INDEXED 3

// NOTE(Cristoffer): Check for nullptr when getting assets.
class asset_manager
{
	private:

	static mesh *Mesh[MAX_MODEL_FILES];

	public:

	static void Init();

	static mesh *GetMesh(uint32 ID);
};