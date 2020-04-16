#pragma once

#include "common.h"
#include "persistence.h"

#define MAX_OBJECT_FILES 5

// NOTE(Cristoffer): Check for nullptr when getting assets.
class asset_manager
{
	private:

	static obj_file *ObjectFile[MAX_OBJECT_FILES];

	public:

	static void Init();

	static obj_file *GetObjectFile(uint32 ID);
};