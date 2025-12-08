
// HackerToolsDlg.cpp: Implementation file
//

#include "stdafx.h"
#include "HackerTools.h"
#include "HackerToolsDlg.h"
#include "afxdialogex.h"
#include "CDia_User.h"
#include "CDia_Core.h"
#include "CHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHackerToolsDlg dialog



CHackerToolsDlg::CHackerToolsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HACKERTOOLS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHackerToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_MyTable);
}

BEGIN_MESSAGE_MAP(CHackerToolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &CHackerToolsDlg::OnHelp)
	ON_COMMAND(ID_32772, &CHackerToolsDlg::OnIntroductions)
END_MESSAGE_MAP()


// CHackerToolsDlg 消息处理程序

BOOL CHackerToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog. The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Initialize tabs
	m_MyTable.InsertItem(0, L"User Tools");
	m_MyTable.InsertItem(1, L"Kernel Tools");

	// Assign child window pointers
	m_MyTable.m_Dia[0] = new CDia_User();
	m_MyTable.m_Dia[1] = new CDia_Core();

	// Create child windows
	m_MyTable.m_Dia[0]->Create(IDD_USER, &m_MyTable);
	m_MyTable.m_Dia[1]->Create(IDD_CORE, &m_MyTable);

	// Control the size of both windows
	CRect rc;
	m_MyTable.GetClientRect(rc);
	rc.DeflateRect(2, 23, 2, 2);
	m_MyTable.m_Dia[0]->MoveWindow(rc);
	m_MyTable.m_Dia[1]->MoveWindow(rc);

	// Show the first child window
	m_MyTable.m_Dia[0]->ShowWindow(SW_SHOW);
	m_MyTable.m_Dia[1]->ShowWindow(SW_HIDE);
	
	// Enable single instance protection (prevent multiple instances)
	HANDLE hMutex = CreateMutexA(NULL, FALSE, "GuiShou");
	if (hMutex)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			MessageBox(L"Do not run multiple instances of this program. Exiting...");
			ExitProcess(-1);
		}
	}
	return TRUE;  // Return TRUE unless you set the focus to a control
}

void CHackerToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon. For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHackerToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHackerToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//************************************************************
// Function Name: OnHelp
// Function Description: Menu help button handler
// Author: GuiShou
// Date: 2018/12/18
// Parameters: void
// Return Value: void
//************************************************************
void CHackerToolsDlg::OnHelp()
{
	CHelp* m_Help = new CHelp;
	m_Help->Create(IDD_Help, NULL);
	m_Help->ShowWindow(SW_SHOW); 
}


//************************************************************
// Function Name: OnIntroductions
// Function Description: Menu introduction button handler
// Author: GuiShou
// Date: 2018/12/18
// Parameters: void
// Return Value: void
//************************************************************
void CHackerToolsDlg::OnIntroductions()
{
	MessageBox(L"Create By GuiShou");
}
