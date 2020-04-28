// Documentation: https://docs.microsoft.com/en-us/windows/win32/seccrypto/common-hresult-values

/*
==========================================================
	Handles the HRESULT from calling the Direct3D
	functions.
==========================================================
*/

#pragma once

#include "common.h"

#include "windows.h"

#if DEBUG_MODE

#define D3D_ERROR_CHECK(Call) HR = (Call); if (FAILED(HR)) { DiagnosticMessage(HR); DebugBreak(); }

#else

#define D3D_ERROR_CHECK(Call) Call

#endif

void DiagnosticMessage(HRESULT Result);