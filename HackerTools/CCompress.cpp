// CCompress.cpp: Implementation file
//

#include "stdafx.h"
#include "HackerTools.h"
#include "CCompress.h"
#include "afxdialogex.h"
#include <winternl.h>





// CCompress dialog

IMPLEMENT_DYNAMIC(CCompress, CDialogEx)

CCompress::CCompress(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Compress, pParent)
	, m_Path(_T(""))
	, m_Data(_T(""))
	, m_Tip(_T(""))
{

}

CCompress::~CCompress()
{
}

void CCompress::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Path);
	DDX_Text(pDX, IDC_EDIT2, m_Data);
	DDX_Text(pDX, IDC_EDIT3, m_Tip);
}


BEGIN_MESSAGE_MAP(CCompress, CDialogEx)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_DataCompress, &CCompress::OnBnClickedDatacompress)
	ON_BN_CLICKED(IDC_FileCompress, &CCompress::OnBnClickedFilecompress)
END_MESSAGE_MAP()





// Define necessary function pointers
typedef NTSTATUS(WINAPI *typedef_RtlGetCompressionWorkSpaceSize)(
	_In_  USHORT CompressionFormatAndEngine,
	_Out_ PULONG CompressBufferWorkSpaceSize,
	_Out_ PULONG CompressFragmentWorkSpaceSize
	);

typedef NTSTATUS(WINAPI *typedef_RtlCompressBuffer)(
	_In_  USHORT CompressionFormatAndEngine,
	_In_  PUCHAR UncompressedBuffer,
	_In_  ULONG  UncompressedBufferSize,
	_Out_ PUCHAR CompressedBuffer,
	_In_  ULONG  CompressedBufferSize,
	_In_  ULONG  UncompressedChunkSize,
	_Out_ PULONG FinalCompressedSize,
	_In_  PVOID  WorkSpace
	);

typedef NTSTATUS(WINAPI *typedef_RtlDecompressBuffer)(
	_In_  USHORT CompressionFormat,
	_Out_ PUCHAR UncompressedBuffer,
	_In_  ULONG  UncompressedBufferSize,
	_In_  PUCHAR CompressedBuffer,
	_In_  ULONG  CompressedBufferSize,
	_Out_ PULONG FinalUncompressedSize
	);




BOOL CCompress::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//Cancel the filter of the file drag message in administrator mode
	ChangeWindowMessageFilterEx(m_hWnd, WM_DROPFILES, MSGFLT_ALLOW, NULL);
	ChangeWindowMessageFilterEx(m_hWnd, 0x0049, MSGFLT_ALLOW, NULL);

	return TRUE;  
}


//************************************************************
// Function Name: OnDropFiles
// Function Description: Respond to the file drag message
// Author: GuiShou
// Parameters: HDROP hDropInfo, file handle
// Return Value: void
//************************************************************
void CCompress::OnDropFiles(HDROP hDropInfo)
{
	// Clear the content of the text box
	m_Path = "";

	// Get the file path
	TCHAR szPath[MAX_PATH] = { 0 };
	DragQueryFile(hDropInfo, 0, szPath, MAX_PATH);

	// Display to the control
	m_Path = szPath;

	UpdateData(FALSE);

	CDialogEx::OnDropFiles(hDropInfo);
}


//************************************************************
// Function Name: OnBnClickedDatacompress
// Function Description: Data compression button
// Author: GuiShou
// Parameters: void
// Return Value: void
//************************************************************
void CCompress::OnBnClickedDatacompress()
{
	UpdateData(TRUE);
	// Check if the data is empty
	if (m_Data == "")
	{
		MessageBox(L"Data cannot be empty");
		return;
	}


	BYTE *pCompressData = NULL;		//Compressed data
	DWORD dwCompressDataLength = 0;	//Compressed data length
	BYTE* pUnCompressData = NULL;	//Uncompressed data
	DWORD dwUnCompressDataLength;	//Uncompressed data length

	//MFC's problem, need to display the hexadecimal of the compressed data on the interface

	//Convert data
	USES_CONVERSION;
	pUnCompressData = (BYTE*)W2A(m_Data);
	dwUnCompressDataLength = ::lstrlenA((LPCSTR)pUnCompressData);

	//Compress data
	DataCompress(pUnCompressData, dwUnCompressDataLength, &pCompressData, &dwCompressDataLength);

	//Uncompress data
	DataDeCompress(pCompressData, dwCompressDataLength, &pUnCompressData, &dwUnCompressDataLength);

	CString temp;
	//Clear the content displayed on the control
	m_Data = "";
	
	//Display the original data
	m_Data += "The original data is:\r\n";
	temp = ByteToCString(pUnCompressData, dwUnCompressDataLength);
	m_Data += temp;
	m_Data += "\r\n";


	//Display the compressed data
	m_Data += "The compressed data is:\r\n";
	temp = ByteToCString(pCompressData, dwCompressDataLength);
	m_Data += temp;
	m_Data += "\r\n";


	//Display the uncompressed data
	m_Data += "The uncompressed data is:\r\n";
	temp = ByteToCString(pUnCompressData, dwUnCompressDataLength);
	m_Data += temp;
	m_Data += "\r\n";

	 //Display to the control
	UpdateData(FALSE);
}



//************************************************************
// Function Name: OnBnClickedFilecompress
// Function Description: File decompression button
// Author: GuiShou
// Parameters: void
// Return Value: void
//************************************************************
void CCompress::OnBnClickedFilecompress()
{
	// Check if the file exists
	if (GetFileAttributes(m_Path)==INVALID_FILE_ATTRIBUTES)
	{
		MessageBox(L"File does not exist! Please try again!");
		return;
	}

	BOOL bRet = FALSE;
	BYTE* pCompressData = NULL;
	DWORD dwCompressDataSize = 0;
	BYTE* pUnCompressData = NULL;
	DWORD dwUnCompressDataSize = 0;
	USES_CONVERSION;

	//Compress the file to data
	bRet = Zlib_CompressData(W2A(m_Path), &pCompressData, &dwCompressDataSize);
	if (bRet==FALSE)
	{
		m_Tip += "Failed to compress the file to data\r\n";
		return;
	}
	else
	{
		m_Tip += "Successfully compressed the file to data\r\n";
	}
	//Save the compressed data to a file
	bRet = SaveToFile("CompressFile.GuiShou", pCompressData, dwCompressDataSize);
	if (bRet == FALSE)
	{
		m_Tip += "Failed to save the compressed file\r\n";
		return;
	}
	else
	{
		m_Tip += "Successfully saved the compressed file\r\n";
	}

	//Uncompress the file to data
	bRet = Zlib_UnCompressData("CompressFile.GuiShou", &pUnCompressData, &dwUnCompressDataSize);
	if (bRet == FALSE)
	{
		m_Tip += "Failed to uncompress the file to data\r\n";
		return;
	}
	else
	{
		m_Tip += "Successfully uncompressed the file to data\r\n";
	}
	//Save the uncompressed data to a file
	bRet = SaveToFile("GuiShou.exe",pUnCompressData, dwUnCompressDataSize);
	if (bRet == FALSE)
	{
		m_Tip += "Failed to save the uncompressed data to a file\r\n";
		return;
	}
	else
	{
		m_Tip += "Successfully saved the uncompressed data to a file\r\n";
	}
	//Release memory
	delete[] pUnCompressData;
	delete[] pCompressData;
	UpdateData(FALSE);
}



//************************************************************
// Function Name: DataCompress
// Function Description: Data compression
// Author: GuiShou
// Parameters: BYTE*  pUncompressData, Uncompressed data
// Parameters: DWORD dwUncompressDataLength, Uncompressed data length
// Parameters: BYTE** ppCompressData, Compressed data
// Parameters: DWORD * pdwCompressDataLength, Compressed data length
// Return Value: BOOL, Whether successful
//************************************************************
BOOL CCompress::DataCompress(BYTE* pUncompressData, DWORD dwUncompressDataLength, BYTE** ppCompressData, DWORD* pdwCompressDataLength)
{


	BOOL bRet = FALSE;
	NTSTATUS status = 0;
	HMODULE hModule = NULL;
	//Define function pointer variables
	typedef_RtlGetCompressionWorkSpaceSize RtlGetCompressionWorkSpaceSize = NULL;
	typedef_RtlCompressBuffer RtlCompressBuffer = NULL;
	DWORD dwWorkSpaceSize = 0;
	DWORD dwFragmentWorkSpaceSize = 0;
	BYTE* pWorkSpace = NULL;
	BYTE* pCompressData = NULL;
	DWORD dwCompressDataLength = 4096;
	DWORD dwFinalCompressSize = 0;

	do 
	{
		//Load ntdll.dll
		hModule = LoadLibrary(L"ntdll.dll");
		if (hModule==NULL)
		{
			m_Tip += L"LoadLibrary Error\r\n";
			break;
		}

		//Get function address
		RtlGetCompressionWorkSpaceSize = (typedef_RtlGetCompressionWorkSpaceSize)::GetProcAddress(hModule, "RtlGetCompressionWorkSpaceSize");
		if (NULL == RtlGetCompressionWorkSpaceSize)
		{
			m_Tip += L"GetProcAddress Error\r\n";
			break;
		}
		RtlCompressBuffer = (typedef_RtlCompressBuffer)::GetProcAddress(hModule, "RtlCompressBuffer");
		if (NULL == RtlCompressBuffer)
		{
			m_Tip += L"GetProcAddress Error\r\n";
			break;
		}

		//Get WorkSpace size
		status = RtlGetCompressionWorkSpaceSize(COMPRESSION_FORMAT_LZNT1 | COMPRESSION_ENGINE_STANDARD, &dwWorkSpaceSize, &dwFragmentWorkSpaceSize);
		if (0!=status)
		{
			m_Tip += L"RtlGetCompressionWorkSpaceSize Error\r\n";
			break;
		}

		//Apply dynamic memory
		pWorkSpace = new BYTE[dwWorkSpaceSize]{ 0 };
		if (pWorkSpace==NULL)
		{
			m_Tip += L"new Error\r\n";
			break;
		}

		while (TRUE)
		{
			//Apply dynamic memory to store compressed data
			pCompressData = new BYTE[dwCompressDataLength];
			if (pCompressData == NULL)
			{
				m_Tip += L"new Error\r\n";
				break;
			}


			//Start compressing data
			RtlCompressBuffer(COMPRESSION_FORMAT_LZNT1,pUncompressData,dwUncompressDataLength,(PUCHAR)pCompressData,dwCompressDataLength,4096,&dwFinalCompressSize,(PVOID)pWorkSpace);

			//If the buffer size of the compressed data is less than the final compressed size, it means compression failed, and compression needs to be re-compressed
			if (dwCompressDataLength<dwFinalCompressSize)
			{
				//Release memory
				if (pCompressData)
				{
					delete[] pCompressData;
				}
				dwCompressDataLength = dwFinalCompressSize;
			}
			else
			{
				//If the compression is successful, exit the loop
				break;
			}
		}

		//Return the compressed data and length
		*ppCompressData = pCompressData;
		*pdwCompressDataLength = dwFinalCompressSize;
		bRet = TRUE;
		UpdateData(FALSE);

	} while (FALSE);

	//Release resources
	if (pWorkSpace)
	{
		delete[] pWorkSpace;
	}
	if (hModule)
	{
		FreeLibrary(hModule);
	}
	return bRet;
}



//************************************************************
// Function Name: DataDeCompress
// Function Description: Data decompression
// Author: GuiShou
// Parameters: BYTE* pCompressData, Compressed data
// Parameters: DWORD dwCompressDataLength, Compressed data length
// Parameters: BYTE** ppUncompressData, Uncompressed data
// Parameters: DWORD* pdwUncompressDataLength, Uncompressed data length
// Return Value: BOOL, Whether successful
//************************************************************

BOOL CCompress::DataDeCompress(BYTE* pCompressData, DWORD dwCompressDataLength, BYTE** ppUncompressData, DWORD* pdwUncompressDataLength)
{
	BOOL bRet = FALSE;
	HMODULE hModule = NULL;
	typedef_RtlDecompressBuffer RtlDecompressBuffer = NULL;
	BYTE *pUncompressData = NULL;
	DWORD dwUncompressDataLength = 4096;
	DWORD dwFinalUncompressSize = 0;
	do
	{
		// Load ntdll.dll
		hModule = ::LoadLibraryA("ntdll.dll");
		if (NULL == hModule)
		{
			m_Tip += " LoadLibrary Error\r\n";
			break;
		}

		// Get the address of the RtlDecompressBuffer function
		RtlDecompressBuffer = (typedef_RtlDecompressBuffer)::GetProcAddress(hModule, "RtlDecompressBuffer");
		if (NULL == RtlDecompressBuffer)
		{
			m_Tip += " GetProcAddress Error\r\n";
			break;
		}

		while (TRUE)
		{
			// Apply dynamic memory
			pUncompressData = new BYTE[dwUncompressDataLength];
			if (NULL == pUncompressData)
			{
				m_Tip += " new Error\r\n";
				break;
			}
			::RtlZeroMemory(pUncompressData, dwUncompressDataLength);

			// Call RtlCompressBuffer to compress data
			RtlDecompressBuffer(COMPRESSION_FORMAT_LZNT1, pUncompressData, dwUncompressDataLength, pCompressData, dwCompressDataLength, &dwFinalUncompressSize);
			if (dwUncompressDataLength < dwFinalUncompressSize)
			{
				// Release memory
				if (pUncompressData)
				{
					delete[]pUncompressData;
					pUncompressData = NULL;
				}
				dwUncompressDataLength = dwFinalUncompressSize;
			}
			else
			{
				break;
			}
		}

		// Return the uncompressed data and length
		*ppUncompressData = pUncompressData;
		*pdwUncompressDataLength = dwFinalUncompressSize;
		bRet = TRUE;

	} while (FALSE);

	// Release resources
	if (hModule)
	{
		::FreeLibrary(hModule);
	}

	return bRet;
}


//************************************************************
// Function Name: ByteToCString
// Function Description: Convert BYTE* to a hexadecimal CString
// Author: GuiShou
// Parameters: BYTE * str, BYTE* to convert
// Parameters: DWORD dwLength, Length
// Return Value: CString
//************************************************************
CString CCompress::ByteToCString(BYTE* str,DWORD dwLength)
{
	//拷贝压缩之后的数据到数组
	BYTE tempStr[4096] = { 0 };
	memcpy(tempStr, str, dwLength);

	//将解压缩的数据转为十六进制 显示到界面
	CString cStr;
	CString data;
	DWORD i = 0;

	for (i = 0; i < dwLength; i++)
	{
		cStr.Format(L"%02x", tempStr[i]);
		data += cStr;

	}

	return data;
}


//************************************************************
// 函数名称: Zlib_CompressData
// 函数说明: 将文件压缩为数据
// 作	 者: GuiShou
// 时	 间: 2019/1/27
// 参	 数: char * pszCompressFileName 需要压缩的文件完整路径
// 参	 数: BYTE ** ppCompressData 压缩后的数据
// 参	 数: DWORD* pdwCompressDataSize 压缩后的数据大小
//************************************************************
BOOL CCompress::Zlib_CompressData(char* pszCompressFileName, BYTE** ppCompressData, DWORD* pdwCompressDataSize)
{
	//注意可能出现压缩后的文件比压缩前的文件大的现象
	//打开文件 获取数据
	HANDLE hFile = CreateFileA(pszCompressFileName,GENERIC_READ,
	FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE,NULL);
	if (hFile==INVALID_HANDLE_VALUE)
	{
		m_Tip += "CreateFileA Error\r\n";
		return FALSE;
	}

	//获取文件大小
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	if (MAX_SRC_FILE_SIZE<dwFileSize)
	{
		m_Tip += "单个文件大小限制为100M！\r\n";
		CloseHandle(hFile);
		return FALSE;
	}

	DWORD dwDestDataSize = dwFileSize;	

	//申请空间存放源文件
	BYTE* pSrcData = new BYTE[dwFileSize]{ 0 };
	if (pSrcData==NULL)
	{
		m_Tip += "new Error\r\n";
		CloseHandle(hFile);
		return FALSE;
	}
	//申请空间存放压缩后的目标文件
	BYTE* pDestData = new BYTE[dwDestDataSize]{ 0 };
	if (pDestData == NULL)
	{
		m_Tip += "new Error\r\n";
		CloseHandle(hFile);
		return FALSE;
	}

	DWORD dwRet = 0;
	//读取源文件到内存
	ReadFile(hFile, pSrcData, dwFileSize, &dwRet, NULL);
	if ((0>=dwRet)||dwRet!=dwFileSize)
	{
		delete[] pSrcData;
		delete[] pDestData;
		CloseHandle(hFile);
		return FALSE;
	}

	//开始压缩数据
	int iRet = 0;
	do 
	{
		iRet = compress(pDestData, &dwDestDataSize, pSrcData, dwFileSize);
		if (0==iRet)
		{
			//成功
			break;
		}
		else if(-5==iRet)
		{
			//输出缓冲区不够大 以100KB大小递增 
			delete[] pDestData;
			dwDestDataSize = dwDestDataSize + (100 * 1024);
			pDestData = new BYTE[dwDestDataSize];
			if (pDestData==NULL)
			{
				delete[] pDestData;
				CloseHandle(hFile);
				return FALSE;
			} 
		}
		else
		{
			//没有足够的内存或者其他情况
			delete[] pDestData;
			delete[] pSrcData;
			CloseHandle(hFile);
			return FALSE;
		}
	} while (TRUE);

	//返回数据
	*ppCompressData = pDestData;
	*pdwCompressDataSize = dwDestDataSize;

	//释放内存
	delete[] pSrcData;
	CloseHandle(hFile);
	return TRUE;
}



//************************************************************
// 函数名称: SaveToFile
// 函数说明: 将数据保存为文件
// 作	 者: GuiShou
// 时	 间: 2019/1/27
// 参	 数: char * pszFileName 文件名
// 参	 数: BYTE * pData 数据
// 参	 数: DWORD dwDataSize 数据大小
//************************************************************
BOOL CCompress::SaveToFile(char * pszFileName, BYTE * pData, DWORD dwDataSize)
{
	char szSaveName[MAX_PATH] = { 0 };
	lstrcpyA(szSaveName,pszFileName);
	//去掉路径前缀
	PathStripPathA(szSaveName);

	//创建文件
	HANDLE hFile = CreateFileA(szSaveName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (hFile==INVALID_HANDLE_VALUE)
	{
		m_Tip += "CreateFileA\r\n";
		return FALSE;
	}
	//写入数据
	DWORD dwRet = 0;
	WriteFile(hFile, pData, dwDataSize, &dwRet, NULL);
	//关闭句柄
	CloseHandle(hFile);
	return TRUE;

}


//************************************************************
// 函数名称: Zlib_UnCompressData
// 函数说明: 将文件解压缩为数据
// 作	 者: GuiShou
// 时	 间: 2019/1/27
// 参	 数: char * pszUncompressFileName 需要解压缩的文件名
// 参	 数: BYTE ** ppUnCompressData 解压缩后的数据
// 参	 数: pdwUnCompressDataSizee  解压缩后的数据大小
//************************************************************
BOOL CCompress::Zlib_UnCompressData(char * pszUncompressFileName, BYTE ** ppUnCompressData, DWORD* pdwUnCompressDataSize)
{
	//打开文件并获取数据
	HANDLE hFile = CreateFileA(pszUncompressFileName, GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		m_Tip += "CreateFileA Error\r\n";
		return FALSE;
	}

	//获取文件大小
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	DWORD dwDestDataSize = MAX_SRC_FILE_SIZE;	//目标文件大小

	//根据源文件大小申请空间
	BYTE* pSrcData = new BYTE[dwFileSize]{ 0 };
	if (pSrcData==NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}

	//根据目标文件大小申请空间
	BYTE* pDestData = new BYTE[dwDestDataSize]{ 0 };
	if (pDestData == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}

	DWORD dwRet = 0;
	//读取需要解压缩的文件的到内存
	ReadFile(hFile, pSrcData, dwFileSize, &dwRet, NULL);
	if ((0>=dwRet)||dwRet!=dwFileSize)
	{
		delete[]pDestData;
		delete[]pSrcData;
		::CloseHandle(hFile);
		return FALSE;
	}
	
	//解压缩数据
	int iRet = 0;
	do 
	{
		iRet = uncompress(pDestData, &dwDestDataSize, pSrcData, dwFileSize);
		if (0==iRet)
		{
			//成功
			break;
		}
		else if (-5==iRet)
		{
			//输出缓冲区不够大 以100KB大小递增
			delete[]pDestData;
			pDestData = NULL;
			dwDestDataSize = dwDestDataSize + (100 * 1024);
			pDestData = new BYTE[dwDestDataSize];
			if (NULL == pDestData)
			{
				delete[]pSrcData;
				pSrcData = NULL;
				::CloseHandle(hFile);
				return FALSE;
			}
		}
		else
		{
			//没有足够的内存 或其他情况
			delete[]pDestData;
			pDestData = NULL;
			delete[]pSrcData;
			pSrcData = NULL;
			::CloseHandle(hFile);
			return FALSE;
		}
	} while (TRUE);

	//返回数据
	*ppUnCompressData = pDestData;
	*pdwUnCompressDataSize = dwDestDataSize;

	//释放内存
	delete[]pSrcData;
	pSrcData = NULL;
	::CloseHandle(hFile);

	return TRUE;
}


