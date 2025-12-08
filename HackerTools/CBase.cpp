// CBase.cpp: Implementation file
//

#include "stdafx.h"
#include "HackerTools.h"
#include "CBase.h"
#include "afxdialogex.h"
#include "resource.h"


// CBase dialog




IMPLEMENT_DYNAMIC(CBase, CDialogEx)

CBase::CBase(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Base, pParent)
	, m_Edit(_T(""))
{

}

CBase::~CBase()
{
}

void CBase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
}


BEGIN_MESSAGE_MAP(CBase, CDialogEx)
	ON_BN_CLICKED(IDC_RunSingle, &CBase::OnBnClickedRunsingle)
	ON_BN_CLICKED(IDC_ReleaseRes, &CBase::OnBnClickedReleaseres)
END_MESSAGE_MAP()



//************************************************************
// Function Name: OnBnClickedRunsingle
// Function Description: Single instance protection button handler
// Author: GuiShou
// Date: 2018/12/18
// Parameters: void
// Return Value: void
//************************************************************
void CBase::OnBnClickedRunsingle()
{
	MessageBox(L"Single instance protection is enabled by default");
}


//************************************************************
// Function Name: OnBnClickedReleaseres
// Function Description: Release resources button handler
// Author: GuiShou
// Date: 2018/12/18
// Parameters: void
// Return Value: void
//************************************************************
void CBase::OnBnClickedReleaseres()
{
	// Find resources in the specified module
	HRSRC hRsrc1 = FindResource(NULL, MAKEINTRESOURCE(IDR_GUISHOU1), TEXT("GUISHOU"));
	HRSRC hRsrc2 = FindResource(NULL, MAKEINTRESOURCE(IDR_GUISHOU2), TEXT("GUISHOU"));

	if (hRsrc1==NULL|| hRsrc2==NULL)
	{
		m_Edit += L"Failed to find resources\r\n";
	}
	else
	{
		m_Edit += L"Successfully found resources\r\n";
	}
	
	// Get resource size
	DWORD dwSize1 = SizeofResource(NULL, hRsrc1);
	DWORD dwSize2 = SizeofResource(NULL, hRsrc2);
	if (dwSize1&&dwSize2)
	{
		m_Edit += L"Successfully obtained resource size\r\n";
	}
	else
	{
		m_Edit += L"Failed to obtain resource size\r\n";
	}

	// Load resources into memory
	HGLOBAL hGlobal1 = LoadResource(NULL, hRsrc1);
	HGLOBAL hGlobal2 = LoadResource(NULL, hRsrc2);
	if (hGlobal1&&hGlobal2)
	{
		m_Edit += L"Successfully loaded resources\r\n";
	}
	else
	{
		m_Edit += L"Failed to load resources\r\n";
	}

	// Lock resources
	LPVOID lpVoid1 = LockResource(hGlobal1);
	LPVOID lpVoid2 = LockResource(hGlobal2);
	if (lpVoid1&&lpVoid2)
	{
		m_Edit += L"Successfully locked resources\r\n";
	}
	else
	{
		m_Edit += L"Failed to lock resources\r\n";
	}

	// Save resources as files
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;
	fopen_s(&fp1, "MyHookDll.dll", "wb+");
	fopen_s(&fp2, "TestDll.dll", "wb+");
	if (fp1&&fp2)
	{
		m_Edit += L"Successfully saved resources to local files\r\n";
	}
	fwrite(lpVoid1,sizeof(char),dwSize1,fp1);
	fwrite(lpVoid2,sizeof(char),dwSize2,fp2);
	fclose(fp1);
	fclose(fp2);
	UpdateData(FALSE);
}
