#pragma once


// CDia_Core dialog

class CDia_Core : public CDialogEx
{
	DECLARE_DYNAMIC(CDia_Core)

public:
	CDia_Core(CWnd* pParent = nullptr);   // Standard constructor
	virtual ~CDia_Core();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
