#pragma once


// CHelp dialog

class CHelp : public CDialogEx
{
	DECLARE_DYNAMIC(CHelp)

public:
	CHelp(CWnd* pParent = nullptr);   // Standard constructor
	virtual ~CHelp();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Help };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTreeCtrl m_Tree;
};
