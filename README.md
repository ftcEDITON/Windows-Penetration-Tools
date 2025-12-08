# HackerTools

A comprehensive Windows security toolkit written in C++ using MFC, designed for security researchers, penetration testers, and developers interested in Windows internals. This project demonstrates various security techniques including DLL injection, process manipulation, privilege escalation, and system monitoring capabilities.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Configuration](#configuration)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Building from Source](#building-from-source)
- [Code Examples](#code-examples)
- [Contributing](#contributing)
- [License](#license)

## Overview

HackerTools is a Windows-based security toolkit that provides a graphical interface for various security operations. The application is organized into two main sections: **User Tools** and **Kernel Tools**, each containing specialized modules for different security tasks.

The toolkit demonstrates advanced Windows API usage, process manipulation techniques, and security research methodologies.

## Features

#### 1. **DLL Injection**
- **ZwCreateThreadEx Injection**: Remote thread creation for DLL injection
- **APC Injection**: Asynchronous Procedure Call injection method
- **Global Hook Injection**: System-wide hook installation
- Process enumeration and selection
- Debug privilege management

#### 2. **Process Hiding & Disguising**
- **PEB Manipulation**: Modify Process Environment Block to disguise process identity
- **Process Replacement**: Replace target process with shellcode
- **DLL Hijacking**: Test and demonstrate DLL hijacking vulnerabilities
- Process path and command line modification

#### 3. **Privilege Escalation**
- Debug privilege enabling/disabling
- UAC bypass techniques (CMLuaUtil method)
- Process privilege enumeration
- Token manipulation

#### 4. **Self-Start Mechanisms**
- **Registry Auto-Start**: Modify Windows registry for persistence
- **Startup Folder**: Add programs to user startup directory
- **Windows Services**: Create, start, stop, and delete system services
- **Task Scheduler**: Schedule tasks for automatic execution

#### 5. **Process Enumeration**
- List all running processes
- Display process IDs and names
- Process information analysis

#### 6. **File Monitoring**
- Real-time file system monitoring
- Directory change detection
- File creation/modification tracking

#### 7. **Data Compression**
- zlib-based compression library
- File compression and decompression
- In-memory data compression
- Support for files up to 100MB

#### 8. **Encryption & Hashing**
- **Hash Calculation**: MD5, SHA-1, SHA-256, SHA-512
- **AES Encryption/Decryption**: Symmetric encryption
- **RSA Encryption/Decryption**: Asymmetric encryption with key generation
- File and data encryption support

#### 9. **Disk Operations**
- Disk information retrieval
- Free space and total space analysis
- File system type detection
- Disk enumeration

#### 10. **File Operations**
- File enumeration
- File attribute manipulation
- File system analysis

### Kernel Tools

Kernel-level tools and utilities (extensible framework for future kernel-mode features).

### Requirements
- **IDE**: Visual Studio 2022
- **Framework**: Microsoft Foundation Classes (MFC)
- **C++ Standard**: C++11+
- **Windows SDK**: Windows SDK 10.0+
- **Dependencies**: 
  - zlib (included in project)
  - Windows API libraries


## Building from Source

See the [Building from Source](#building-from-source) section for detailed instructions.

## Configuration

### Single Instance Protection

The application includes built-in protection against multiple instances. A mutex named "GuiShou" prevents concurrent execution.

### Debug Privilege

Many features require debug privileges. The application automatically attempts to enable debug privileges when needed, but administrator rights are typically required.

### zlib Configuration

The zlib compression library is pre-configured for both x86 and x64 architectures in Debug and Release modes. Static libraries are included in the project.

## Usage

### Getting Started

1. **Launch the Application**
   - Run `HackerTools.exe` as Administrator
   - The main window displays two tabs: "User Tools" and "Kernel Tools"

2. **Navigate Features**
   - Click on buttons in the User Tools tab to access different modules
   - Each module opens in a separate dialog window

### Common Use Cases

#### DLL Injection Example

1. Open the **Inject** module
2. Select injection method (ZwCreateThreadEx, APC, or Global Hook)
3. Choose target process from the process list
4. Select or drag-and-drop the DLL file
5. Click **Inject** to perform the injection

#### Process Disguising Example

1. Open the **Hide** module
2. Select disguise method:
   - **Pretend**: Modify PEB to change process appearance
   - **Puppet**: Replace process with shellcode
   - **Hijack**: DLL hijacking test
3. Provide target path and parameters
4. Execute the disguise operation

#### Privilege Escalation Example

1. Open the **Privilege** module
2. View current process privileges
3. Enable debug privileges or attempt UAC bypass
4. Check privilege status

#### Self-Start Configuration

1. Open the **SelfStart** module
2. Drag-and-drop the executable file
3. Choose persistence method:
   - Registry
   - Startup Folder
   - Task Scheduler
   - Windows Service
4. Configure and apply

#### File Encryption Example

1. Open the **Encrypt** module
2. Drag-and-drop file to encrypt
3. Choose encryption method:
   - **Hash**: Calculate file hash (MD5, SHA-256, etc.)
   - **AES**: Symmetric encryption
   - **RSA**: Asymmetric encryption (generates key pair)
4. Enter password/key information
5. Execute encryption

### Key Components

#### DLL Injection Methods

**ZwCreateThreadEx Injection**
```cpp
BOOL ZwCreateThreadExInjectDll(DWORD dwProcessId, char* pszDllFileName);
```
- Uses undocumented `ZwCreateThreadEx` API
- Creates remote thread in target process
- Loads DLL via `LoadLibrary`

**APC Injection**
```cpp
BOOL APCInject(char *pszProcessName, char *pszDllName);
```
- Uses Asynchronous Procedure Calls
- Injects into all threads of target process
- Leverages thread alertable state

**Global Hook**
```cpp
void SetGlobalHook();
```
- Installs system-wide Windows hook
- Uses `SetWindowsHookEx` API
- Requires hook DLL (MyHook project)

#### Process Manipulation

**PEB Modification**
```cpp
BOOL DisguiseProcess(const wchar_t* lpwszPath, const wchar_t* lpwszCmd);
```
- Modifies Process Environment Block
- Changes process path and command line
- Affects how process appears in task manager

**Process Replacement**
```cpp
BOOL ReplaceProcess(const wchar_t* pszFilePath, PVOID pReplaceData, 
                    DWORD dwReplaceDataSize, DWORD dwRunOffset);
```
- Replaces target process image
- Executes shellcode in process context
- Maintains process handle

#### UAC Bypass

**CMLuaUtil Method**
```cpp
BOOL CMLuaUtilBypassUAC(const wchar_t* lpwszExecutable);
```
- Uses COM interface elevation
- Leverages ICMLuaUtil interface
- Bypasses User Account Control prompts

#### Encryption Implementation

**AES Encryption**
- Uses Windows CryptoAPI
- Supports AES-128, AES-192, AES-256
- Password-based key derivation

**RSA Encryption**
- Generates RSA key pairs (2048-bit)
- Public key encryption
- Private key decryption

### Security Considerations

1. **Administrator Rights**: Most features require elevated privileges
2. **Antivirus Detection**: Some techniques may trigger antivirus alerts
3. **System Stability**: Incorrect usage may cause system instability
4. **Legal Compliance**: Ensure authorized use only

## Project Structure

```
HackerTools/
├── HackerTools/              # Main application
│   ├── CInject.*            # DLL injection module
│   ├── CHide.*              # Process hiding/disguising
│   ├── CPrivilege.*         # Privilege escalation
│   ├── CSelfStart.*         # Persistence mechanisms
│   ├── CEnumProcess.*        # Process enumeration
│   ├── CFileMonit.*         # File monitoring
│   ├── CCompress.*          # Compression utilities
│   ├── CEncrypt.*           # Encryption/hashing
│   ├── CDisk.*              # Disk operations
│   ├── CEnumFiles.*         # File enumeration
│   ├── CFileAttr.*          # File attributes
│   ├── CDia_User.*          # User tools dialog
│   ├── CDia_Core.*          # Kernel tools dialog
│   └── zlib/                # Compression library
├── MyHook/                  # Global hook DLL
├── TestDll/                 # Test DLL for injection
│   └── CBypassUAC.*         # UAC bypass implementation
├── DllHijackTest/           # DLL hijacking test
├── ServiceExeTest/          # Service test executable
└── HackerTools.sln          # Visual Studio solution
```

## Building from Source

### Prerequisites

1. Install Visual Studio 2022 with:
   - Desktop development with C++
   - MFC components
   - Windows SDK

2. Ensure you have administrator rights for building

### Build Steps

2. **Open Solution**
   - Open `HackerTools.sln` in Visual Studio

3. **Configure Build**
   - Select configuration: Debug or Release
   - Ensure all projects are set to build

4. **Build Solution**
   - Right-click solution → Build Solution
   - Or press `Ctrl+Shift+B`

5. **Output Location**
   - Executables will be in `HackerTools/[Configuration]/[Platform]/`

### Build Configurations

- **Debug**: Includes debug symbols, no optimizations
- **Release**: Optimized build, smaller executable size


### Troubleshooting

**Issue**: Missing MFC libraries
- **Solution**: Install "MFC and ATL support" in Visual Studio Installer

**Issue**: zlib linking errors
- **Solution**: Ensure zlib static libraries are in correct architecture folders

**Issue**: Windows SDK not found
- **Solution**: Install Windows SDK 10.0 or later via Visual Studio Installer

## Code Examples

### Example 1: Basic DLL Injection

```cpp
// Enable debug privilege
EnableDebugPrivilege(TRUE);

// Inject DLL into process
DWORD processId = GetPidByPname("notepad.exe");
ZwCreateThreadExInjectDll(processId, "C:\\path\\to\\mydll.dll");
```

### Example 2: Process Disguising

```cpp
// Disguise current process as system process
DisguiseProcess(L"C:\\Windows\\System32\\svchost.exe", 
                L"-k netsvcs");
```

### Example 3: UAC Bypass

```cpp
// Bypass UAC to run elevated executable
CMLuaUtilBypassUAC(L"C:\\Windows\\System32\\cmd.exe");
```

### Example 4: File Encryption

```cpp
// Read file data
BYTE* fileData;
DWORD fileSize;
GetFileData("C:\\test.txt", &fileData, &fileSize);

// Encrypt with AES
BYTE password[] = "MySecretPassword";
AesEncrypt(password, strlen((char*)password), 
           fileData, fileSize, fileSize * 2);
```

### Example 5: Self-Start via Registry

```cpp
// Add to registry startup
SetRegAutoRun("C:\\MyApp\\app.exe", "MyAppName");
```

## Contributing

1. **Fork the repository**
2. **Create a feature branch** (`git checkout -b feature/feature`)
3. **Commit your changes** (`git commit -m 'Add some Feature'`)
4. **Push to the branch** (`git push origin feature/Feature`)
5. **Open a Pull Request**

## Disclaimer

**This software is intended for educational and authorized security testing purposes only.** The authors and contributors are not liable for any misuse or damage caused by this software.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.