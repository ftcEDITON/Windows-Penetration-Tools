// CHelp.cpp: Implementation file
//

#include "stdafx.h"
#include "HackerTools.h"
#include "CHelp.h"
#include "afxdialogex.h"


// CHelp dialog

IMPLEMENT_DYNAMIC(CHelp, CDialogEx)

CHelp::CHelp(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Help, pParent)
{

}

CHelp::~CHelp()
{
}

void CHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
}


BEGIN_MESSAGE_MAP(CHelp, CDialogEx)
END_MESSAGE_MAP()


// CHelp message handlers


BOOL CHelp::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HTREEITEM Basic=m_Tree.InsertItem(L"Basic Techniques");
	HTREEITEM ReleaseResoures= m_Tree.InsertItem(L"Resource Release",Basic);
	HTREEITEM ReleaseResouresHelp= m_Tree.InsertItem(L"Release DLLs required for subsequent function tests in the same directory", ReleaseResoures);

	HTREEITEM RunSigle= m_Tree.InsertItem(L"Single Instance Protection",Basic);
	HTREEITEM RunSigleHelp= m_Tree.InsertItem(L"Use mutex to prevent multiple instances. Enabled by default. Only one instance of this program can run.", RunSigle);

	HTREEITEM Inject = m_Tree.InsertItem(L"Injection Techniques");
	HTREEITEM GlobalHook = m_Tree.InsertItem(L"Global Hook Injection", Inject);
	HTREEITEM GlobalHookHelp1 = m_Tree.InsertItem(L"Drag MyHookDll.dll (released using resource release technique) to the window. Test DLL only has a MessageBox", GlobalHook);
	HTREEITEM GlobalHookHelp2 = m_Tree.InsertItem(L"Hooks WM_GETMESSAGE messages. A message box will appear whenever any program in the system receives a message", GlobalHook);
	HTREEITEM GlobalHookHelp3 = m_Tree.InsertItem(L"If many programs are running, the system may freeze. Use with caution!", GlobalHook);

	HTREEITEM RemoteThread = m_Tree.InsertItem(L"Remote Thread Injection", Inject);
	HTREEITEM RemoteThreadHelp1 = m_Tree.InsertItem(L"1. Drag TestDll.dll (released using resource release technique)", RemoteThread);
	HTREEITEM RemoteThreadHelp2 = m_Tree.InsertItem(L"2. Enter the target process ID", RemoteThread);
	HTREEITEM RemoteThreadHelp3 = m_Tree.InsertItem(L"3. Click start injection to inject the test DLL into the target process. Test DLL only has a MessageBox", RemoteThread);
	HTREEITEM RemoteThreadHelp4 = m_Tree.InsertItem(L"4. May fail if the target process has high privileges or strict detection (e.g., QQ.exe)", RemoteThread);

	HTREEITEM APCInject = m_Tree.InsertItem(L"APC Injection", Inject);
	HTREEITEM APCInjectHelp1 = m_Tree.InsertItem(L"1. Drag TestDll.dll (released using resource release technique)", APCInject);
	HTREEITEM APCInjectHelp2 = m_Tree.InsertItem(L"2. Enter the target process name", APCInject);
	HTREEITEM APCInjectHelp3 = m_Tree.InsertItem(L"3. Click start injection to inject the test DLL into the target process. Test DLL only has a MessageBox", APCInject);
	HTREEITEM APCInjectHelp4 = m_Tree.InsertItem(L"4. May fail if the target process has high privileges or strict detection (e.g., QQ.exe)", APCInject);

	HTREEITEM Start=m_Tree.InsertItem(L"Startup Techniques");
	HTREEITEM Create_Process = m_Tree.InsertItem(L"Create Process API", Start);
	HTREEITEM Create_ProcessHelp1 = m_Tree.InsertItem(L"Drag any exe file to the window", Create_Process);
	HTREEITEM Create_ProcessHelp2 = m_Tree.InsertItem(L"Click the button to create a process using three different methods", Create_Process);

	HTREEITEM MemoryLoad = m_Tree.InsertItem(L"Memory Load and Run", Start);
	HTREEITEM MemoryLoadHelp1 = m_Tree.InsertItem(L"Drag TestDll.dll (released using resource release technique)", MemoryLoad);
	HTREEITEM MemoryLoadHelp2 = m_Tree.InsertItem(L"Click the button to simulate PE loader and load TestDll into program memory, then run directly", MemoryLoad);
	HTREEITEM MemoryLoadHelp3 = m_Tree.InsertItem(L"If the DLL is hidden in resources, it can run directly without releasing to local disk", MemoryLoad);

	HTREEITEM SelfStart=m_Tree.InsertItem(L"Self-Startup Techniques");
	HTREEITEM RegEdit = m_Tree.InsertItem(L"Registry", SelfStart);
	HTREEITEM RegEditHelp1 = m_Tree.InsertItem(L"Drag any exe file to the window", RegEdit);
	HTREEITEM RegEditHelp2 = m_Tree.InsertItem(L"Click the button to write the program's full path to registry startup items", RegEdit);
	HTREEITEM RegEditHelp3 = m_Tree.InsertItem(L"Target program will start with system startup", RegEdit);
	HTREEITEM RegEditHelp4 = m_Tree.InsertItem(L"You can view or delete using the registry path shown in the prompt window", RegEdit);

	HTREEITEM StartDir = m_Tree.InsertItem(L"Startup Folder", SelfStart);
	HTREEITEM StartDirHelp1 = m_Tree.InsertItem(L"Drag any exe file to the window", StartDir);
	HTREEITEM StartDirHelp2 = m_Tree.InsertItem(L"Click the button to copy the program to the system startup folder", StartDir);
	HTREEITEM StartDirHelp3 = m_Tree.InsertItem(L"Target program will start automatically when user logs in", StartDir);
	HTREEITEM StartDirHelp4 = m_Tree.InsertItem(L"You can view or delete using the startup folder path shown in the prompt window", StartDir);

	HTREEITEM Task = m_Tree.InsertItem(L"Scheduled Tasks", SelfStart);
	HTREEITEM TaskHelp = m_Tree.InsertItem(L"This feature requires administrator privileges", Task);
	HTREEITEM TaskHelp1 = m_Tree.InsertItem(L"Drag any exe file to the window", Task);
	HTREEITEM TaskHelp2 = m_Tree.InsertItem(L"Click the button to write the target program to system scheduled tasks", Task);
	HTREEITEM TaskHelp3 = m_Tree.InsertItem(L"Program will start when user logs in", Task);
	HTREEITEM TaskHelp4 = m_Tree.InsertItem(L"You can delete the added event in scheduled tasks", Task);

	HTREEITEM SystemService = m_Tree.InsertItem(L"System Service", SelfStart);
	HTREEITEM SystemServiceHelp = m_Tree.InsertItem(L"This feature requires administrator privileges", SystemService);
	HTREEITEM SystemServiceHelp1 = m_Tree.InsertItem(L"Drag ServiceExeTest.exe to the window", SystemService);
	HTREEITEM SystemServiceHelp2 = m_Tree.InsertItem(L"Click the button to register ServiceExeTest.exe as a system service", SystemService);
	HTREEITEM SystemServiceHelp3 = m_Tree.InsertItem(L"ServiceExeTest.exe will run in the background", SystemService);
	HTREEITEM SystemServiceHelp4 = m_Tree.InsertItem(L"ServiceExeTest.exe contains no code, it's just an empty service application", SystemService);
	HTREEITEM SystemServiceHelp5 = m_Tree.InsertItem(L"You can delete it using Task Manager", SystemService);


	HTREEITEM Privilege=m_Tree.InsertItem(L"Privilege Escalation Techniques");
	HTREEITEM Debug = m_Tree.InsertItem(L"Enable Debug Privilege", Privilege);
	HTREEITEM DebugHelp1 = m_Tree.InsertItem(L"This feature requires administrator privileges", Debug);
	HTREEITEM DebugHelp2 = m_Tree.InsertItem(L"Click the button to obtain Debug privilege", Debug);

	HTREEITEM BypassUAC = m_Tree.InsertItem(L"BypassUAC", Privilege);
	HTREEITEM BypassUACHelp = m_Tree.InsertItem(L"Click the button to use COM component to elevate to administrator privileges", BypassUAC);
	HTREEITEM BypassUACHelp1 = m_Tree.InsertItem(L"Open a command prompt with administrator privileges without showing a dialog", BypassUAC);

	HTREEITEM FindAllPrivilege = m_Tree.InsertItem(L"View Current Process Privileges", Privilege);
	HTREEITEM FindAllPrivilegeHelp = m_Tree.InsertItem(L"Click the button to display all privileges of the current program in the List control", FindAllPrivilege);
	HTREEITEM FindAllPrivilegeHelp1 = m_Tree.InsertItem(L"Use this function to check if Debug privilege elevation is effective", FindAllPrivilege);

	HTREEITEM Hide=m_Tree.InsertItem(L"Hiding Techniques");
	HTREEITEM Pretend = m_Tree.InsertItem(L"Process Disguise", Hide);
	HTREEITEM PretendHelp1 = m_Tree.InsertItem(L"Click the button to disguise this process as Explorer.exe", Pretend);
	HTREEITEM PretendHelp2 = m_Tree.InsertItem(L"This program is 32-bit. This feature only works on 32-bit systems", Pretend);

	HTREEITEM Puppet = m_Tree.InsertItem(L"Puppet Process", Hide);
	HTREEITEM PuppetHelp = m_Tree.InsertItem(L"Drag any exe file to the window", Puppet);
	HTREEITEM PuppetHelp1 = m_Tree.InsertItem(L"Click the button to inject MessageBox ShellCode into the target exe", Puppet);

	HTREEITEM DllHijack = m_Tree.InsertItem(L"DLL Hijacking", Hide);
	HTREEITEM DllHijackHelp = m_Tree.InsertItem(L"Principle: When PE loader loads DLL, replace the original DLL with a custom DLL and add code to the custom DLL", DllHijack);
	HTREEITEM DllHijackHelp1 = m_Tree.InsertItem(L"This feature is not implemented in the interface. You can perform manual operations", DllHijack);
	HTREEITEM DllHijackHelp2 = m_Tree.InsertItem(L"1. Find DllHijackTest.dll (released using resource release technique)", DllHijack);
	HTREEITEM DllHijackHelp3 = m_Tree.InsertItem(L"2. Rename the DLL to oledlg.dll", DllHijack);
	HTREEITEM DllHijackHelp4 = m_Tree.InsertItem(L"3. Find oledlg.dll in C:\\Windows\\SysWOW64 directory and rename it to Old_oledlg", DllHijack);
	HTREEITEM DllHijackHelp5 = m_Tree.InsertItem(L"4. If renaming fails, please search for a solution", DllHijack);
	HTREEITEM DllHijackHelp6 = m_Tree.InsertItem(L"5. Place oledlg.dll in the SysWOW64 directory", DllHijack);
	HTREEITEM DllHijackHelp7 = m_Tree.InsertItem(L"6. Run FileCleaner2.0.exe", DllHijack);
	HTREEITEM DllHijackHelp8 = m_Tree.InsertItem(L"7. The hijacked DLL forwards all functions of the original DLL, so it won't affect program execution", DllHijack);
	HTREEITEM DllHijackHelp9 = m_Tree.InsertItem(L"8. The hijacked DLL has a MessageBox function in DllMain to indicate successful hijacking", DllHijack);


	HTREEITEM Compress=m_Tree.InsertItem(L"Compression Techniques");
	HTREEITEM DataCompress = m_Tree.InsertItem(L"Data Compression", Compress);
	HTREEITEM DataCompressHelp = m_Tree.InsertItem(L"Enter data in the text box and click the button to compress and decompress the input data", DataCompress);
	HTREEITEM FileCompress = m_Tree.InsertItem(L"File Compression", Compress);
	HTREEITEM FileCompressHelp = m_Tree.InsertItem(L"Drag a file to the window and click the button to compress and decompress the file", FileCompress);


	HTREEITEM Encrypt=m_Tree.InsertItem(L"Encryption Techniques");
	HTREEITEM HASH=m_Tree.InsertItem(L"HASH", Encrypt);
	HTREEITEM HASHHelp=m_Tree.InsertItem(L"Drag a file to the window and click the button to calculate the file's hash value", HASH);

	HTREEITEM AES=m_Tree.InsertItem(L"AES Encryption/Decryption", Encrypt);
	HTREEITEM AESHelp=m_Tree.InsertItem(L"Enter data in the data window and click the button to get the AES encrypted/decrypted value", AES);

	HTREEITEM RAS=m_Tree.InsertItem(L"RSA Encryption/Decryption", Encrypt);
	HTREEITEM RASHelp=m_Tree.InsertItem(L"Enter data in the data window and click the button to get the RSA encrypted/decrypted value", RAS);


	HTREEITEM Function=m_Tree.InsertItem(L"Function Techniques");
	HTREEITEM FindAllProcess=m_Tree.InsertItem(L"Process Enumeration", Function);
	HTREEITEM FindAllProcessHelp=m_Tree.InsertItem(L"Enumerate all current processes", FindAllProcess);

	HTREEITEM FindAllFile=m_Tree.InsertItem(L"File Enumeration", Function);
	HTREEITEM FindAllFileHelp=m_Tree.InsertItem(L"Enumerate all files in the current system. Can view file attributes and disk information", FindAllFile);
	HTREEITEM FindAllFileHelp1=m_Tree.InsertItem(L"Can view file attributes and disk information. Double-click to enter the next directory level", FindAllFile);

	HTREEITEM ScreenShot=m_Tree.InsertItem(L"Desktop Screenshot", Function);
	HTREEITEM ScreenShotHelp=m_Tree.InsertItem(L"Capture a screenshot of the current screen. Screenshot is saved in the program's directory", ScreenShot);

	HTREEITEM KeyBoardRecord=m_Tree.InsertItem(L"Keystroke Recording", Function);
	HTREEITEM KeyBoardRecordHelp=m_Tree.InsertItem(L"Implements a keyboard logger that records all keystrokes", KeyBoardRecord);
	HTREEITEM KeyBoardRecordHelp1=m_Tree.InsertItem(L"Keystroke records are stored in log.txt on drive D", KeyBoardRecord);

	HTREEITEM RemoteCMD =m_Tree.InsertItem(L"Remote CMD", Function);
	HTREEITEM RemoteCMDHelp =m_Tree.InsertItem(L"Enter CMD commands in the command box, e.g., ping 127.0.0.1", RemoteCMD);
	HTREEITEM RemoteCMDHelp1 =m_Tree.InsertItem(L"The execution results of CMD commands will be displayed in the data window", RemoteCMD);

	HTREEITEM USBMonitoring =m_Tree.InsertItem(L"USB Monitoring", Function);
	HTREEITEM USBMonitoringHelp =m_Tree.InsertItem(L"1. Monitor USB insertion and removal. Enabled by default", USBMonitoring);
	HTREEITEM USBMonitoringHelp2 =m_Tree.InsertItem(L"2. Copy all .txt files from USB to the program's current directory. Modify source code to copy other file types", USBMonitoring);

	HTREEITEM FileMonitoring =m_Tree.InsertItem(L"File Monitoring", Function);
	HTREEITEM FileMonitoringHelp =m_Tree.InsertItem(L"Monitor file operations on drive D", FileMonitoring);
	
	return TRUE;  
}
