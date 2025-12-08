
#include "stdafx.h"

extern HMODULE g_hDllMoudle;	//dll handle
// Shared memory
#pragma data_seg("mydata")	// Create a data segment named mydata
	HHOOK g_hHook = NULL;
#pragma data_seg()
#pragma comment(linker,"/SECTION:mydata,RWS")  // Set the mydata data segment to be read, write and shareable

extern "C" _declspec(dllexport)
// Hook callback function
LRESULT GetMsgProc(int code, WPARAM wParam, LPARAM lParam)
{
	MessageBoxA(0, "You are infected", "You are infected", 0);
	return CallNextHookEx(g_hHook, code, wParam, lParam);
}

extern "C" _declspec(dllexport)
// Set global hook
BOOL SetGlobalHook()
{
	g_hHook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, g_hDllMoudle, 0);
	if (g_hHook==NULL)
	{
		return FALSE;
	}
	return TRUE;
}


// Uninstall global hook
