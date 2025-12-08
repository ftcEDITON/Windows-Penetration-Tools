// CCmdResult.cpp: Implementation file
//

#include "stdafx.h"
#include "HackerTools.h"
#include "CCmdResult.h"
#include "afxdialogex.h"


// CCmdResult dialog

IMPLEMENT_DYNAMIC(CCmdResult, CDialogEx)

CCmdResult::CCmdResult(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CmdResult, pParent)
	, m_Cmd(_T("ping 127.0.0.1"))
	, m_Result(_T(""))
{

}

CCmdResult::~CCmdResult()
{
}

void CCmdResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Cmd);
	DDX_Text(pDX, IDC_EDIT2, m_Result);
}


BEGIN_MESSAGE_MAP(CCmdResult, CDialogEx)
	ON_BN_CLICKED(IDC_ShowCmd, &CCmdResult::OnBnClickedShowcmd)
END_MESSAGE_MAP()


//************************************************************
// Function Name: PipeCmd
// Function Description: Get the execution result of CMD
// Author: GuiShou
// Parameters: char * pszCmd,cmd command char * pszResultBuffer, buffer to receive the result of CMD DWORD dwResultBufferSize, buffer size
// Return Value: BOOL
//************************************************************
BOOL CCmdResult::PipeCmd(char* pszCmd, char * pszResultBuffer, DWORD dwResultBufferSize)
{
	HANDLE hReadPipe = NULL;
	HANDLE hWritePipe = NULL;
	SECURITY_ATTRIBUTES securityAttributes = { 0 };
	BOOL bRet = FALSE;
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	// Set the security attributes of the pipe
	securityAttributes.bInheritHandle = TRUE;
	securityAttributes.nLength = sizeof(securityAttributes);
	securityAttributes.lpSecurityDescriptor = NULL;
	// Create an anonymous pipe
	bRet = ::CreatePipe(&hReadPipe, &hWritePipe, &securityAttributes, 0);
	if (FALSE == bRet)
	{
		MessageBox(L"CreatePipe Error");
		return FALSE;
	}
	// Set the parameters of the new process
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;
	si.hStdError = hWritePipe;
	si.hStdOutput = hWritePipe;
	// Create a new process to execute the command, and write the execution result to the anonymous pipe
	USES_CONVERSION;
	bRet = ::CreateProcess(NULL, A2W(pszCmd), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	if (FALSE == bRet)
	{
		MessageBox(L"CreateProcess Error");
	}

	// Wait for the command to execute
	::WaitForSingleObject(pi.hThread, INFINITE);
	::WaitForSingleObject(pi.hProcess, INFINITE);
	// Read the result from the anonymous pipe to the output buffer
	::RtlZeroMemory(pszResultBuffer, dwResultBufferSize);
	::ReadFile(hReadPipe, pszResultBuffer, dwResultBufferSize, NULL, NULL);
	// Close the handles, release the memory
	::CloseHandle(pi.hThread);
	::CloseHandle(pi.hProcess);
	::CloseHandle(hWritePipe);
	::CloseHandle(hReadPipe);

	return TRUE;
}



//************************************************************
// Function Name: OnBnClickedShowcmd
// Function Description: Respond to the execution and get the CMD result button
// Author: GuiShou
// Parameters: void
// Return Value: void
//************************************************************
void CCmdResult::OnBnClickedShowcmd()
{
	UpdateData(TRUE);
	// Check if the command is empty
	if (m_Cmd==L"")
	{
		MessageBox(L"CMD命令不能为空");
		return;
	}
	// Clear the previous display result
	m_Result = "";

	// Get the CMD command to execute
	char szResultBuffer[512] = { 0 };
	DWORD dwResultBufferSize = 512;
	// Execute the CMD command and get the execution result data
	USES_CONVERSION;
	if (FALSE==PipeCmd(W2A(m_Cmd), szResultBuffer, 512))
	{
		MessageBox(L"pipe cmd error");
	}
	// Display to the interface
	m_Result += A2W(szResultBuffer);
	UpdateData(FALSE);
}

