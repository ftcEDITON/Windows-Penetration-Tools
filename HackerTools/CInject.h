#pragma once


// CInject dialog

class CInject : public CDialogEx
{
	DECLARE_DYNAMIC(CInject)

public:
	CInject(CWnd* pParent = nullptr);   // Standard constructor
	virtual ~CInject();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Inject };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_Radio;			// Variable bound to radio button
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedInject();
	

	CString m_Edit;		// Edit box for storing DLL path
	CString m_TipMsg;	// Injection status messages

	void SetGlobalHook();		// Set global hook
	BOOL ZwCreateThreadExInjectDll(DWORD dwProcessId, char* pszDllFileName);	// Remote thread injection
	CString m_PidAndName;
	virtual BOOL OnInitDialog();
	BOOL EnableDebugPrivilege(BOOL fEnable);	// Enable debug privilege
	BOOL APCInject(char *pszProcessName, char *pszDllName);	// APC injection
	DWORD GetPidByPname(char* pszProcessName);		// Get process ID by process name
	BOOL GetAllTidByPid(DWORD dwProcessId,DWORD** ppThreadId,DWORD* pdwThreadIdLength);	// Get all thread IDs by process ID

	CEdit m_objEdit;
};
