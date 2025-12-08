#pragma once


// CDia_User dialog

class CDia_User : public CDialogEx
{
	DECLARE_DYNAMIC(CDia_User)

public:
	CDia_User(CWnd* pParent = nullptr);   // Standard constructor
	virtual ~CDia_User();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBase();
	afx_msg void OnBnClickedInject();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedSelfstart();
	afx_msg void OnBnClickedPrivilege();
	afx_msg void OnBnClickedHide();
	afx_msg void OnBnClickedCompress();
	afx_msg void OnBnClickedEncrypt();
	afx_msg void OnBnClickedOther();
};
