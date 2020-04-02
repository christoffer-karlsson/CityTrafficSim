// d3d_diagnostics.h: Debug utility, checking HRESULT messages and displaying them.
// Only enabled in debug mode.
// https://docs.microsoft.com/en-us/windows/win32/seccrypto/common-hresult-values

#pragma once

#include "common.h"

#include <windows.h>

#if DEBUG_MODE

#define D3D_ERROR_CHECK(Call) HR = (Call); if (FAILED(HR)) { DiagnosticMessage(HR); DebugBreak(); }

#else

#define D3D_ERROR_CHECK(Call) Call

#endif

void DiagnosticMessage(HRESULT Result);