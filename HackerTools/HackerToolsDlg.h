
// HackerToolsDlg.h: Header file
//

#pragma once
#include "CMyTableCtrl.h"

// CHackerToolsDlg dialog
class CHackerToolsDlg : public CDialogEx
{
// Construction
public:
	CHackerToolsDlg(CWnd* pParent = nullptr);	// Standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HACKERTOOLS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHelp();
	afx_msg void OnIntroductions();
	CMyTableCtrl m_MyTable;
};
