
#include "pch.h"
#include <windows.h>
#include<stdio.h>


// Service entry function and callback function
void __stdcall ServiceMain(DWORD dwArgc, char *lpszArgv);
void __stdcall ServiceCtrlHandle(DWORD dwOperateCode);
BOOL TellSCM(DWORD dwState, DWORD dwExitCode, DWORD dwProgress);
void DoTask();

// Service name
char g_szServiceName[MAX_PATH] = "GuiShou.exe";
SERVICE_STATUS_HANDLE g_ServiceStatusHandle = { 0 };	//服务状态句柄


// The main process notifies the SCM that the executable file contains several services,
// and gives the address of the ServiceMain callback function for each service.
int main()
{
	// Complete the initialization of ServiceMain
	// This structure records the names of all services contained in this service program and the entry functions of the services
	SERVICE_TABLE_ENTRY stDispatchTable[] = { {g_szServiceName,(LPSERVICE_MAIN_FUNCTION)ServiceMain},{NULL,NULL} };

	// Call StartServiceCtrlDispatcher and communicate with SCM
	// StartServiceCtrlDispatcher will create a new thread for each non-empty element passed to it
	StartServiceCtrlDispatcher(stDispatchTable);

	return 0;
}

// Service entry function and callback function
void __stdcall ServiceMain(DWORD dwArgc, char *lpszArgv)
{
	//1. Call RegisterServiceCtrlHandler function to notify SCM of the address of its CtrlHandler callback function
	g_ServiceStatusHandle = RegisterServiceCtrlHandler(g_szServiceName, ServiceCtrlHandle);
	//2. Call SetServiceStatus to tell SCM that the service is initializing
	TellSCM(SERVICE_START_PENDING, 0, 1);
	TellSCM(SERVICE_RUNNING, 0, 0);

	// The code for your own program is placed here
	// !!Attention!! This must be a dead loop here, otherwise the user process cannot be created when the computer is turned off and then turned on (not a restart)
	while (TRUE)
	{
		Sleep(5000);
		DoTask();
	}

}

// Service control function
void __stdcall ServiceCtrlHandle(DWORD dwOperateCode)
{
	switch (dwOperateCode)
	{
	case SERVICE_CONTROL_PAUSE:
	{
		// Pause
		TellSCM(SERVICE_PAUSE_PENDING, 0, 1);
		TellSCM(SERVICE_PAUSED, 0, 0);
		break;
	}
	case SERVICE_CONTROL_CONTINUE:
	{
		// Continue
		TellSCM(SERVICE_CONTINUE_PENDING, 0, 1);
		TellSCM(SERVICE_RUNNING, 0, 0);
		break;
	}
	case SERVICE_CONTROL_STOP:
	{
		// Stop
		TellSCM(SERVICE_STOP_PENDING, 0, 1);
		TellSCM(SERVICE_STOPPED, 0, 0);
		break;
	}
	case SERVICE_CONTROL_INTERROGATE:
	{
		// Interrogate
		break;
	}
	default:
		break;
	}
}

BOOL TellSCM(DWORD dwState, DWORD dwExitCode, DWORD dwProgress)
{
	SERVICE_STATUS ServiceStatus = { 0 };
	BOOL bRet = FALSE;
	RtlZeroMemory(&ServiceStatus, sizeof(ServiceStatus));

	// The type of the service executable file
	ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	// Tell SCM your service's current state
	ServiceStatus.dwCurrentState = dwState;	
	// Specify what kind of control notifications the service is willing to accept: stop, pause or continue, shutdown
	ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_SHUTDOWN;
	// Set the exit code
	ServiceStatus.dwWin32ExitCode = dwExitCode;
	ServiceStatus.dwWaitHint = 3000;

	// Set the service running state
	bRet = SetServiceStatus(g_ServiceStatusHandle, &ServiceStatus);
	return bRet;
}

void DoTask()
{
	// The code for your own program is placed here
	printf("This is the service control program!");
	system("pause");
}