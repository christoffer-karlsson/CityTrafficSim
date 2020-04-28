#pragma once

#include "common.h"
#include "persistence.h"
#include "mesh.h"

#define MAX_MODEL_FILES 100

typedef enum
{
	asset_mesh_car,
	asset_mesh_car_indexed,
	asset_mesh_building,
	asset_mesh_building_indexed,

} asset_id;

// NOTE(Cristoffer): Check for nullptr when getting assets.
class asset_manager
{
	private:

	static mesh *Mesh[MAX_MODEL_FILES];

	public:

	static void Init();

	static mesh *GetMesh(asset_id ID);
};