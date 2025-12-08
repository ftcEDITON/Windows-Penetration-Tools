#pragma once


// CCmdResult dialog

class CCmdResult : public CDialogEx
{
	DECLARE_DYNAMIC(CCmdResult)

public:
	CCmdResult(CWnd* pParent = nullptr);   // Standard constructor
	virtual ~CCmdResult();

// Dialog data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CmdResult };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_Cmd;
	CString m_Result;


	// Execute the cmd command, and get the execution result data
	BOOL PipeCmd(char *pszCmd, char* pszResultBuffer, DWORD dwResultBufferSize);
	afx_msg void OnBnClickedShowcmd();
};
