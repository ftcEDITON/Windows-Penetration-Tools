#include "stdafx.h"
#include "HackerTools.h"
#include "CDia_User.h"
#include "afxdialogex.h"
#include "CBase.h"
#include "CInject.h"
#include "CStrat.h"
#include "CSelfStart.h"
#include "CPrivilege.h"
#include "CHide.h"
#include "CCompress.h"
#include "CEncrypt.h"
#include "CFunction.h"


// CDia_User dialog

IMPLEMENT_DYNAMIC(CDia_User, CDialogEx)

CDia_User::CDia_User(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USER, pParent)
{

}

CDia_User::~CDia_User()
{
}

void CDia_User::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDia_User, CDialogEx)
	ON_BN_CLICKED(IDC_Base, &CDia_User::OnBnClickedBase)
	ON_BN_CLICKED(IDC_Inject, &CDia_User::OnBnClickedInject)
	ON_BN_CLICKED(IDC_Start, &CDia_User::OnBnClickedStart)
	ON_BN_CLICKED(IDC_SelfStart, &CDia_User::OnBnClickedSelfstart)
	ON_BN_CLICKED(IDC_Privilege, &CDia_User::OnBnClickedPrivilege)
	ON_BN_CLICKED(IDC_Hide, &CDia_User::OnBnClickedHide)
	ON_BN_CLICKED(IDC_Compress, &CDia_User::OnBnClickedCompress)
	ON_BN_CLICKED(IDC_Encrypt, &CDia_User::OnBnClickedEncrypt)
	ON_BN_CLICKED(IDC_Other, &CDia_User::OnBnClickedOther)
END_MESSAGE_MAP()




//************************************************************
// Function Name: OnBnClickedBase
// Function Description: Basic techniques button handler
// Author: GuiShou
// Date: 2018/12/18
// Parameters: void
// Return Value: void
//************************************************************
void CDia_User::OnBnClickedBase()
{
	CBase *m_Base = new CBase;
	m_Base->Create(IDD_Base, NULL);
	m_Base->ShowWindow(SW_SHOW);
}



//************************************************************
// Function Name: OnBnClickedInject
// Function Description: Injection techniques button handler
// Author: GuiShou
// Date: 2018/12/18
// Parameters: void
// Return Value: void
//************************************************************
void CDia_User::OnBnClickedInject()
{
	CInject *m_Inject = new CInject;
	m_Inject->Create(IDD_Inject, NULL);
	m_Inject->ShowWindow(SW_SHOW);
}



//************************************************************
// Function Name: OnBnClickedStart
// Function Description: Startup techniques button handler
// Author: GuiShou
// Date: 2019/1/19
// Parameters: void
// Return Value: void
//************************************************************
void CDia_User::OnBnClickedStart()
{
	CStrat* m_Strat = new CStrat;
	m_Strat->Create(IDD_Start, NULL);
	m_Strat->ShowWindow(SW_SHOW);
}



//************************************************************
// Function Name: OnBnClickedSelfstart
// Function Description: Self-startup techniques button handler
// Author: GuiShou
// Date: 2019/1/19
// Parameters: void
// Return Value: void
//************************************************************
void CDia_User::OnBnClickedSelfstart()
{
	CSelfStart* m_SelfStrat = new CSelfStart;
	m_SelfStrat->Create(IDD_SelfStart, NULL);
	m_SelfStrat->ShowWindow(SW_SHOW);
}



//************************************************************
// Function Name: OnBnClickedPrivilege
// Function Description: Privilege escalation techniques button handler
// Author: GuiShou
// Date: 2019/1/23
// Parameters: void
// Return Value: void
//************************************************************
void CDia_User::OnBnClickedPrivilege()
{
	CPrivilege* m_Privilege = new CPrivilege;
	m_Privilege->Create(IDD_Privilege, NULL);
	m_Privilege->ShowWindow(SW_SHOW);
}


//************************************************************
// Function Name: OnBnClickedHide
// Function Description: Hiding techniques button handler
// Author: GuiShou
// Date: 2019/1/23
// Parameters: void
// Return Value: void
//************************************************************
void CDia_User::OnBnClickedHide()
{
	CHide* m_Hide = new CHide;
	m_Hide->Create(IDD_Hide, NULL);
	m_Hide->ShowWindow(SW_SHOW);
}



//************************************************************
// Function Name: OnBnClickedCompress
// Function Description: Compression techniques button handler
// Author: GuiShou
// Date: 2019/1/24
// Parameters: void
// Return Value: void
//************************************************************
void CDia_User::OnBnClickedCompress()
{
	CCompress* m_Compress = new CCompress;
	m_Compress->Create(IDD_Compress, NULL);
	m_Compress->ShowWindow(SW_SHOW);
}


//************************************************************
// Function Name: OnBnClickedEncrypt
// Function Description: Encryption techniques button handler
// Author: GuiShou
// Date: 2019/1/24
// Parameters: void
// Return Value: void
//************************************************************
void CDia_User::OnBnClickedEncrypt()
{
	CEncrypt* m_Encrypt = new CEncrypt;
	m_Encrypt->Create(IDD_Encrypt, NULL);
	m_Encrypt->ShowWindow(SW_SHOW);
}


//************************************************************
// Function Name: OnBnClickedOther
// Function Description: Other functions button handler
// Author: GuiShou
// Date: 2019/1/29
// Parameters: void
// Return Value: void
//************************************************************
void CDia_User::OnBnClickedOther()
{
	CFunction* m_Function = new CFunction;
	m_Function->Create(IDD_Function, NULL);
	m_Function->ShowWindow(SW_SHOW);
}
