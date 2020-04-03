#include "diagnostics.h"

void DiagnosticMessage(HRESULT Result)
{
	LPTSTR ErrorMessage = NULL;

	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		Result,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&ErrorMessage, 0,
		NULL);

	MessageBox(GetActiveWindow(),
		ErrorMessage,
		NULL,
		MB_OK | MB_ICONWARNING
		);
}