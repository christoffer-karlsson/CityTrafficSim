// common.h: Miscellaneous typedefs, macros, settings, etc that is used all over the place.

#pragma once

#include "types.h"

#include <cassert>

#define BUILD_NUMBER 24
#define SHOW_BUILD_NUMBER 1

// NOTE(Cristoffer): Enable debug stuff, such as assertions. Turn off
// when building release.
#define DEBUG_MODE 1

// NOTE(Cristoffer): Define if multi-threading should be used.
// Supports change at run time, so maybe make a changeable variable of
// this to experiment?
#define USE_MULTI_THREADING 1

#if DEBUG_MODE

#define ASSERT(Expression) assert(Expression);

#else

#define ASSERT(Expression) Expression

#endif

#define singleton public

// NOTE(Cristoffer): Predefined messages. Might be useless to do this.
#define ERROR_MESSAGE_0000 "Could not create a handle to window."