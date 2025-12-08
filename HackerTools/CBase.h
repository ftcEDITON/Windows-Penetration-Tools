#pragma once


// CBase dialog

class CBase : public CDialogEx
{
	DECLARE_DYNAMIC(CBase)

public:
	CBase(CWnd* pParent = nullptr);   // Standard constructor
	virtual ~CBase();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Base };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRunsingle();
	afx_msg void OnBnClickedReleaseres();
	CString m_Edit;
};
