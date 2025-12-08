#include "stdafx.h"
#include "HackerTools.h"
#include "CInject.h"
#include "afxdialogex.h"
#include <afxpriv.h>
#include <TlHelp32.h>


// CInject dialog

IMPLEMENT_DYNAMIC(CInject, CDialogEx)

CInject::CInject(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Inject, pParent)
	, m_Radio(0)
	, m_Edit(_T("Please drag MyHookDll.dll here"))
	, m_TipMsg(_T(""))
	, m_PidAndName(_T(""))
{

}

CInject::~CInject()
{
}

void CInject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio);
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
	DDX_Text(pDX, IDC_EDIT3, m_TipMsg);
	DDX_Text(pDX, IDC_EDIT2, m_PidAndName);
	DDX_Control(pDX, IDC_EDIT3, m_objEdit);
}


BEGIN_MESSAGE_MAP(CInject, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CInject::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CInject::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &CInject::OnBnClickedRadio1)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_Inject, &CInject::OnBnClickedInject)
END_MESSAGE_MAP()




BOOL CInject::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_EDIT2)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);

	// Disable drag message filtering in administrator mode
	ChangeWindowMessageFilterEx(m_hWnd, WM_DROPFILES, MSGFLT_ALLOW, NULL);
	ChangeWindowMessageFilterEx(m_hWnd, 0x0049, MSGFLT_ALLOW, NULL);

	return TRUE; 
}


//************************************************************
// Function Name: OnBnClickedRadio1
// Function Description: Handle radio button selection
// Author: GuiShou
// Date: 2018/12/18
// Parameters: void
// Return Value: void
//************************************************************
void CInject::OnBnClickedRadio1()
{
	UpdateData(TRUE);
	switch (m_Radio)
	{
	case 0:
	{
		m_Edit = L"Please drag MyHookDll.dll here";
		GetDlgItem(IDC_EDIT2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
		m_TipMsg = "";
	}
		break;
	case 1:
	{
		m_Edit = L"Please drag TestDll.dll here";
		m_PidAndName = L"Please enter the target process ID";
		GetDlgItem(IDC_EDIT2)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC1)->ShowWindow(TRUE);
		SetDlgItemText(IDC_STATIC1, L"Please enter process ID");
		m_TipMsg = "";
	}	
		break;
	case 2:
	{
		m_Edit = L"Please drag TestDll.dll here";
		//m_Edit = L"C:\\Users\\GuiShou\\Desktop\\TestDll.dll";
		m_PidAndName = L"Please enter the target process name";
		//m_PidAndName = L"QQ.exe";
		GetDlgItem(IDC_EDIT2)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC1)->ShowWindow(TRUE);
		SetDlgItemText(IDC_STATIC1, L"Please enter process name");
		m_TipMsg = "";
	}
	break;
	default:
		break;
	}
	UpdateData(FALSE);
}



//************************************************************
// Function Name: OnDropFiles 
// Function Description: Handle file drag and drop
// Author: GuiShou
// Date: 2018/12/18
// Parameters: HDROP hDropInfo - Drag and drop file handle
// Return Value: void
//************************************************************
void CInject::OnDropFiles(HDROP hDropInfo)
{
	// Get file path
	TCHAR szPath[MAX_PATH] = { 0 };
	DragQueryFile(hDropInfo, 0, szPath, MAX_PATH);

	// Check if file extension is DLL
	LPTSTR pszExtension=PathFindExtension(szPath);
	if (lstrcmp(pszExtension, L".dll")==0)
	{
		// Display in control
		m_Edit = szPath;
		UpdateData(FALSE);
	}
	else
	{
		MessageBox(L"Please drag a valid DLL file");
	}
	
	CDialogEx::OnDropFiles(hDropInfo);
}



//************************************************************
// Function Name: OnBnClickedInject 
// Function Description: Handle injection start button
// Author: GuiShou
// Date: 2018/12/18
// Parameters: void
// Return Value: void
//************************************************************
void CInject::OnBnClickedInject()
{
	// Check if file exists
	if (GetFileAttributes(m_Edit) == INVALID_FILE_ATTRIBUTES)
	{
		MessageBox(L"File does not exist. Please try again.");
		return;
	}
	UpdateData(TRUE);
	switch (m_Radio)
	{

	case 0:
	{
		if (m_Edit == L"" || m_Edit == L"Please drag MyHookDll.dll here")
		{
			MessageBox(L"Please drag a valid DLL file");
		}
		else
		{
			// Global hook injection
			SetGlobalHook();
		}
	}
	break;
	case 1:
	{
		if (m_Edit == L"" || m_Edit == L"Please drag TestDll.dll here")
		{
			MessageBox(L"Please drag a valid DLL file");
		}
		else if (m_PidAndName == L"Please enter the target process ID"|| m_PidAndName=="")
		{
			MessageBox(L"Please enter the target process ID");
		}
		else
		{
			USES_CONVERSION;
			char* szDllPath = T2A(m_Edit);
			DWORD dwProcessId = _ttoi(m_PidAndName);

			// Enable debug privilege for current process token
			BOOL bRet = EnableDebugPrivilege(TRUE);
			if (bRet)
			{
				m_TipMsg += L"Privilege escalation successful\r\n";
			}
			else
			{
				m_TipMsg += L"Privilege escalation failed\r\n";
			}

			// Remote thread injection
			BOOL bIsSuccess = ZwCreateThreadExInjectDll(dwProcessId, szDllPath);
			if (bIsSuccess)
			{
				m_TipMsg += L"Remote thread injection successful\r\n";
			}
			else
			{
				m_TipMsg += L"Remote thread injection failed\r\n";
			}
		}
		
	}
	break;
	case 2:
	{
		// Check if DLL path is empty
		if (m_Edit == L"" || m_Edit == L"Please drag TestDll.dll here")
		{
			MessageBox(L"Please drag a valid DLL file");
		}
		// Check if process name is empty
		else if (m_PidAndName== L"Please enter the target process name"|| m_PidAndName=="")
		{
			MessageBox(L"Please enter a valid process name");
		}
		else
		{
			// Enable debug privilege
			EnableDebugPrivilege(TRUE);

			USES_CONVERSION;
			char* szProcessName = T2A(m_PidAndName);
			char* szDllPath = T2A(m_Edit);
			// APC injection
			BOOL bRet = FALSE;
			bRet = APCInject(szProcessName, szDllPath);
			if (bRet)
			{
				m_TipMsg += L"APC injection successful\r\n";
				// Scroll to the last line
				m_objEdit.LineScroll(m_objEdit.GetLineCount());
			}
			else
			{
				m_TipMsg += L"APC injection failed\r\n";
				// Scroll to the last line
				m_objEdit.LineScroll(m_objEdit.GetLineCount());
			}
		}
	}
	break;
	default:
		break;
	}
	UpdateData(FALSE);
}




//************************************************************
// Function Name: SetGlobalHook 
// Function Description: Set global hook
// Author: GuiShou
// Date: 2018/12/18
// Parameters: void
// Return Value: void
//************************************************************
void CInject::SetGlobalHook()
{
	// Define function pointer and function pointer variable
	typedef BOOL(*typedef_SetGlobalHook)();
	typedef_SetGlobalHook fnSetGlobalHook = NULL;


	// Get DLL load base address
	HMODULE hDll = LoadLibrary(m_Edit);
	if (hDll)
	{
		m_TipMsg += L"DLL loaded successfully\r\n";
	}
	else
	{
		m_TipMsg += L"DLL load failed\r\n";
	}

	// Get function address and assign to function pointer variable
	fnSetGlobalHook = (typedef_SetGlobalHook)GetProcAddress(hDll, "SetGlobalHook");
	if (fnSetGlobalHook)
	{
		m_TipMsg += L"Function address loaded successfully\r\n";
	}
	else
	{
		m_TipMsg += L"Function address load failed\r\n";
	}
	// Set global hook
	BOOL bRet = fnSetGlobalHook();
	if (bRet)
	{
		m_TipMsg += L"Global hook set successfully, infinite message boxes will start\r\n";
	}
	else
	{
		m_TipMsg += L"Global hook set failed\r\n";
	}

	UpdateData(FALSE);

}




//************************************************************
// Function Name: ZwCreateThreadExInjectDll 
// Function Description: Implement remote thread injection using ZwCreateThreadEx
// Author: GuiShou
// Date: 2018/12/19
// Parameters: dwProcessId - Process ID, pszDllFileName - DLL path name
// Return Value: BOOL - Success or failure
//************************************************************
BOOL CInject::ZwCreateThreadExInjectDll(DWORD dwProcessId, char* pszDllFileName)
{
	HANDLE hProcess = NULL;
	SIZE_T dwSize = 0;
	LPVOID pDllAddr = NULL;
	FARPROC pFunProcAddr = NULL;
	HANDLE hRemoteThread = NULL;
	DWORD dwStatus = 0;

	// Open target process and get handle
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	if (hProcess==NULL)
	{
		m_TipMsg += L"Failed to open process\r\n";
		return FALSE;
	}
	else
	{
		m_TipMsg += L"Process opened successfully\r\n";
	}

	// Allocate memory in the target process
	dwSize = strlen(pszDllFileName) + 1;
	pDllAddr = VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
	if (pDllAddr==NULL)
	{
		m_TipMsg += L"Failed to allocate memory\r\n";
		return FALSE;
	}
	else
	{
		m_TipMsg += L"Memory allocated successfully\r\n";
	}

	// Write data to allocated memory
	BOOL bIsSucess = WriteProcessMemory(hProcess, pDllAddr, pszDllFileName, dwSize, NULL);
	if (bIsSucess==FALSE)
	{
		m_TipMsg += L"Failed to write memory\r\n";
		return FALSE;
	}
	else
	{
		m_TipMsg += L"Memory written successfully\r\n";
	}

	// Load ntdll.dll
	HMODULE hNtdll = LoadLibraryA("ntdll.dll");
	if (hNtdll==NULL)
	{
		m_TipMsg += L"Failed to load ntdll\r\n";
		return FALSE;
	}
	else
	{
		m_TipMsg += L"ntdll loaded successfully\r\n";
	}

	// Get LoadLibraryA function address
	pFunProcAddr = GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA");
	if (pFunProcAddr==NULL)
	{
		m_TipMsg += L"Failed to load LoadLibraryA function address\r\n";
		return FALSE;
	}
	else
	{
		m_TipMsg += L"LoadLibraryA function address loaded successfully\r\n";
	}

	// Get ZwCreateThread function address - ZwCreateThread has different declarations in 64-bit and 32-bit
#ifdef _WIN64
	typedef DWORD(WINAPI *typedef_ZwCreateThreadEx)(
		PHANDLE ThreadHandle,
		ACCESS_MASK DesiredAccess,
		LPVOID ObjectAttributes,
		HANDLE ProcessHandle,
		LPTHREAD_START_ROUTINE lpStartAddress,
		LPVOID lpParameter,
		ULONG CreateThreadFlags,
		SIZE_T ZeroBits,
		SIZE_T StackSize,
		SIZE_T MaximumStackSize,
		LPVOID pUnkown);
#else
	typedef DWORD(WINAPI *typedef_ZwCreateThreadEx)(
		PHANDLE ThreadHandle,
		ACCESS_MASK DesiredAccess,
		LPVOID ObjectAttributes,
		HANDLE ProcessHandle,
		LPTHREAD_START_ROUTINE lpStartAddress,
		LPVOID lpParameter,
		BOOL CreateSuspended,
		DWORD dwStackSize,
		DWORD dw1,
		DWORD dw2,
		LPVOID pUnkown);
#endif
	typedef_ZwCreateThreadEx ZwCreateThreadEx = (typedef_ZwCreateThreadEx)GetProcAddress(hNtdll, "ZwCreateThreadEx");
	if (ZwCreateThreadEx==NULL)
	{
		m_TipMsg += L"Failed to load ZwCreateThreadEx function address\r\n";
		return FALSE;
	}
	else
	{
		m_TipMsg += L"ZwCreateThreadEx function address loaded successfully\r\n";
	}
	// Use ZwCreateThreadEx function to create remote thread and implement DLL injection
	dwStatus = ZwCreateThreadEx(&hRemoteThread, THREAD_ALL_ACCESS, NULL,
	hProcess, (LPTHREAD_START_ROUTINE)pFunProcAddr, pDllAddr, 0, 0, 0, 0, NULL);
	if (hRemoteThread==NULL)
	{
		m_TipMsg += L"Remote thread injection failed\r\n";
		return FALSE;
	}
	else
	{
		m_TipMsg += L"Remote thread injection successful\r\n";
	}

	// Close handles
	CloseHandle(hProcess);
	FreeLibrary(hNtdll);
	return TRUE;

}


//************************************************************
// Function Name: EnableDebugPrivilege 
// Function Description: Enable debug privilege
// Author: GuiShou
// Date: 2018/12/19
// Parameters: fEnable - Whether to enable privilege
// Return Value: BOOL - Success or failure
//************************************************************
BOOL CInject::EnableDebugPrivilege(BOOL fEnable)
{
	BOOL fOk = FALSE;	HANDLE hToken;
	// Open process token with modify privilege access
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		// Token privileges structure
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		// Get LUID
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = fEnable ? SE_PRIVILEGE_ENABLED : 0;
		// Adjust privileges
		AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
		fOk = (GetLastError() == ERROR_SUCCESS);
		CloseHandle(hToken);
	}
	return(fOk);
}



//************************************************************
// Function Name: APCInject 
// Function Description: Inject DLL into target process using APC
// Author: GuiShou
// Date: 2018/12/19
// Parameters: pszProcessName - Process name, pszDllName - DLL path name
// Return Value: BOOL - Success or failure
//************************************************************
BOOL CInject::APCInject(char *pszProcessName, char *pszDllName)
{
	BOOL bRet = FALSE;
	DWORD dwProcessId = 0;
	DWORD *pThreadId = NULL;
	DWORD dwThreadIdLength = 0;
	HANDLE hProcess = NULL;
	HANDLE hThread = NULL;
	PVOID pBaseAddress = NULL;
	PVOID pLoadLibraryAFunc = NULL;
	SIZE_T dwRet = 0;
	DWORD dwDllPathLen = strlen(pszDllName) + 1;
	DWORD i = 0;

	do 
	{
		// Get process ID by process name
		dwProcessId = GetPidByPname(pszProcessName);
		if (0>=dwProcessId)
		{
			m_TipMsg += L"Failed to get process ID!\r\n";
			bRet = FALSE;
			break;
		}
		else
		{
			m_TipMsg += L"Process ID obtained successfully!\r\n";
		}
		// Get thread IDs by process ID
		bRet = GetAllTidByPid(dwProcessId, &pThreadId, &dwThreadIdLength);
		if (bRet==FALSE)
		{
			m_TipMsg += L"Failed to get all thread IDs\r\n";
			bRet = FALSE;
			break;
		}
		else
		{
			m_TipMsg += L"All thread IDs obtained successfully\r\n";
		}

		// Open target process
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
		if (hProcess==NULL)
		{
			m_TipMsg += L"Failed to open target process\r\n";
			bRet = FALSE;
			break;
		}
		else
		{
			m_TipMsg += L"Target process opened successfully\r\n";
		}
		// Allocate memory in target process space
		pBaseAddress = VirtualAllocEx(hProcess, NULL, dwDllPathLen, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (pBaseAddress == NULL)
		{
			m_TipMsg += L"Failed to allocate memory in target process\r\n";
			bRet = FALSE;
			break;
		}
		else
		{
			m_TipMsg += L"Memory allocated in target process successfully\r\n";
		}
		// Write DLL path data to allocated space
		WriteProcessMemory(hProcess, pBaseAddress, pszDllName, dwDllPathLen, &dwRet);
		if (dwRet!=dwDllPathLen)
		{
			m_TipMsg += L"Failed to write memory in target process\r\n";
			bRet = FALSE;
			break;
		}
		else
		{
			m_TipMsg += L"Memory written in target process successfully\r\n";
		}

		// Get LoadLibrary address
		pLoadLibraryAFunc = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
		if (pLoadLibraryAFunc==NULL)
		{
			m_TipMsg += L"Failed to get LoadLibrary address\r\n";
			bRet = FALSE;
			break;
		}
		else
		{
			m_TipMsg += L"LoadLibrary address obtained successfully\r\n";
		}

		// Iterate through threads and insert APC
		for (i = 0; i < dwThreadIdLength; i++)
		{
			// Open thread
			hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, pThreadId[i]);
			if (hThread)
			{
				// Insert APC
				QueueUserAPC((PAPCFUNC)pLoadLibraryAFunc, hThread, (ULONG_PTR)pBaseAddress);
				// Close thread handle
				CloseHandle(hThread);
				hThread = NULL;
			}
		}
		bRet = TRUE;
	} while (FALSE);

	// Free memory
	if (hProcess)
	{
		CloseHandle(hProcess);
		hProcess = NULL;
	}
	if (hThread)
	{
		delete[] pThreadId;
		pThreadId = NULL;
	}
	return bRet;
}



//************************************************************
// Function Name: GetAllTidByPid 
// Function Description: Get all thread IDs by process ID
// Author: GuiShou
// Date: 2018/12/19
// Parameters: dwProcessId - Process ID, ppThreadId - Thread ID array, pdwThreadIdLength - Number of thread IDs
// Return Value: BOOL - Success or failure
//************************************************************
BOOL CInject::GetAllTidByPid(DWORD dwProcessId, DWORD** ppThreadId, DWORD* pdwThreadIdLength)
{
	DWORD* pThreadId = NULL;
	DWORD dwThreadIdLength = 0;
	DWORD dwBuffLength = 1000;
	THREADENTRY32 te32 = { 0 };
	HANDLE hSnapShot = NULL;
	BOOL bRet = TRUE;

	do 
	{
		// Allocate memory
		pThreadId = new DWORD[dwBuffLength];
		if (pThreadId==NULL)
		{
			m_TipMsg += L"Failed to allocate memory!\r\n";
			bRet = FALSE;
			break;
		}
		else
		{
			m_TipMsg += L"Memory allocated successfully!\r\n";
		}
		RtlZeroMemory(pThreadId, (dwBuffLength * sizeof(DWORD)));

		// Get thread snapshot
		RtlZeroMemory(&te32, sizeof(te32));
		te32.dwSize = sizeof(te32);
		hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		if (hSnapShot == NULL)
		{
			m_TipMsg += L"Failed to create thread snapshot!\r\n";
			bRet = FALSE;
			break;
		}
		else
		{
			m_TipMsg += L"Thread snapshot created successfully!\r\n";
		}

		// Get first snapshot information
		bRet = Thread32First(hSnapShot, &te32);
		while (bRet)
		{
			// Get thread ID corresponding to process
			if (te32.th32OwnerProcessID==dwProcessId)
			{
				pThreadId[dwThreadIdLength] = te32.th32ThreadID;
				dwThreadIdLength++;
			}
			// Iterate to next thread snapshot information
			bRet = Thread32Next(hSnapShot, &te32);
		}
		// Return
		*ppThreadId = pThreadId;
		*pdwThreadIdLength = dwThreadIdLength;
		bRet = TRUE;

	} while (FALSE);

	if (FALSE==bRet)
	{
		if (pThreadId)
		{
			delete[] pThreadId;
			pThreadId = NULL;
		}
	}
	return bRet;
}


//************************************************************
// Function Name: GetPidByPname 
// Function Description: Get process ID by process name
// Author: GuiShou
// Date: 2018/12/19
// Parameters: pszProcessName - Process name
// Return Value: DWORD - Process ID
//************************************************************
DWORD CInject::GetPidByPname(char* pszProcessName)
{
	DWORD dwProcessId = 0;
	PROCESSENTRY32 pe32 = { 0 };
	HANDLE hSnapshot = NULL;
	BOOL bRet = FALSE;
	RtlZeroMemory(&pe32, sizeof(pe32));
	pe32.dwSize = sizeof(pe32);

	// Get process snapshot
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == NULL)
	{
		m_TipMsg += L"Failed to create process snapshot\r\n";
		return dwProcessId;
	}
	else
	{
		m_TipMsg += L"Process snapshot created successfully\r\n";	
	}

	// Get first process snapshot information
	bRet = Process32First(hSnapshot, &pe32);
	while (bRet)
	{
		// Get snapshot information
		USES_CONVERSION;
		CString ProcessName = A2T(pszProcessName);
		if (0==lstrcmp(pe32.szExeFile, ProcessName))
		{
			dwProcessId = pe32.th32ProcessID;
			break;
		}
		// Iterate to next process snapshot information
		bRet = Process32Next(hSnapshot, &pe32);
	}
	return dwProcessId;
}
