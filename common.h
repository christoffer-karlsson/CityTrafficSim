// common.h: Miscellaneous typedefs, macros, etc that is used all over the place.

#pragma once

#include <stdint.h>
#include <cassert>

#define BUILD_NUMBER 14
#define SHOW_BUILD_NUMBER 1

#define DEBUG_MODE 1

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float  real32;
typedef double real64;

#if DEBUG_MODE

#define ASSERT(Expression) assert(Expression);

#else

#define ASSERT(Expression) Expression

#endif

#define ERROR_MESSAGE_0000 "Could not create a handle to window."