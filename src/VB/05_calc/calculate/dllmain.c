#include "dll.h"
#include <windows.h>
#include "compute.hpp"

extern "C" DLLIMPORT __stdcall double compute(char *expression)
{
	checkVars();
	fillArithmeticUnitVector(expression);
	computePostfixExpressionQueue();
	return computeValue();
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			break;
		}
		case DLL_THREAD_DETACH:
		{
			break;
		}
	}

	/* Return TRUE on success, FALSE on failure */
	return TRUE;
}
