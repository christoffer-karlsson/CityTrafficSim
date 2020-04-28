/*
==========================================================
	Commonly used in every file.
==========================================================
*/

#pragma once

#include "types.h"

#include <cassert>

#define BUILD_NUMBER 28
#define SHOW_BUILD_NUMBER 1

// Enable debug stuff, such as assertions. Turn off when building release.
#define DEBUG_MODE 1
#define DEBUG_D3D 1
#define DEBUG_IMGUI 1

// Define if multi-threading should be used.
#define USE_MULTI_THREADING 1

#if DEBUG_MODE

#define ASSERT(Expression) assert(Expression);

#else

#define ASSERT(Expression) Expression

#endif