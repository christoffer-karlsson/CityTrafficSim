#pragma once

#include "common.h"
#include "persistence.h"

#define MAX_MODEL_FILES 5

// NOTE(Cristoffer): Check for nullptr when getting assets.
class asset_manager
{
	private:

	static model *Model[MAX_MODEL_FILES];

	public:

	static void Init();

	static model *GetModel(uint32 ID);
};