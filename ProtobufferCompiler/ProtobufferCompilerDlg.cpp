
// ProtobufferCompilerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProtobufferCompiler.h"
#include "ProtobufferCompilerDlg.h"
#include "afxdialogex.h"
#include <vector>
//#include <Shlobj.h>
//#pragma comment(lib,"Shell32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//����Ŀ¼
bool GetWorkDirectory(TCHAR szWorkDirectory[], WORD wBufferCount)
{
	//ģ��·��
	TCHAR szModulePath[MAX_PATH]=TEXT("");
	GetModuleFileName(AfxGetInstanceHandle(),szModulePath,MAX_PATH);

	//�����ļ�
	for (INT i=lstrlen(szModulePath);i>=0;i--)
	{
		if (szModulePath[i]==TEXT('\\'))
		{
			szModulePath[i]=0;
			break;
		}
	}

	//���ý��
	ASSERT(szModulePath[0]!=0);
	lstrcpyn(szWorkDirectory,szModulePath,wBufferCount);

	return true;
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProtobufferCompilerDlg �Ի���



CProtobufferCompilerDlg::CProtobufferCompilerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProtobufferCompilerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	ZeroMemory(m_szWorkDir,sizeof(m_szWorkDir));
}

void CProtobufferCompilerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_LIST1,m_CheckListBox);
}

BEGIN_MESSAGE_MAP(CProtobufferCompilerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CProtobufferCompilerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &CProtobufferCompilerDlg::OnBnClickedSelect1)
	ON_BN_CLICKED(IDC_CHECK2, &CProtobufferCompilerDlg::OnBnClickedSelect2)
	ON_BN_CLICKED(IDOK, &CProtobufferCompilerDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CProtobufferCompilerDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CProtobufferCompilerDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &CProtobufferCompilerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CProtobufferCompilerDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CProtobufferCompilerDlg ��Ϣ�������

BOOL CProtobufferCompilerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	GetWorkDirectory(m_szWorkDir,MAX_PATH);
	SetDlgItemText(IDC_EDIT1,m_szWorkDir);
	SetDlgItemText(IDC_EDIT2,m_szWorkDir);

	m_CheckListBox.ModifyStyle(0,LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);
	m_CheckListBox.SetCheckStyle(BS_AUTOCHECKBOX);
	FillFileListBox();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CProtobufferCompilerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CProtobufferCompilerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CProtobufferCompilerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void TraverseDir(CString& dir, std::vector<CString>& arrFileNames)
{
	CFileFind ff;
	if (dir.Right(1) != TEXT("\\"))
		dir += TEXT("\\");
	dir += TEXT("*.proto");

	BOOL ret = ff.FindFile(dir);
	while (ret)
	{
		ret = ff.FindNextFile();
		if (ff.IsDirectory() && !ff.IsDots())
		{
			CString path = ff.GetFilePath();
			TraverseDir(path, arrFileNames);
		}
		else if (!ff.IsDirectory() && !ff.IsDots())
		{
			CString name = ff.GetFileName();
			CString path = ff.GetFilePath();
			arrFileNames.push_back(path);
		}
		else
		{
			CString name = ff.GetFileName();
			CString path = ff.GetFilePath();
			arrFileNames.push_back(path);
		}
	}
	ff.Close();
}
void CProtobufferCompilerDlg::FillFileListBox()
{
	CString szDirInput=TEXT("");
	GetDlgItemText(IDC_EDIT1,szDirInput);
	if (!PathFileExists(szDirInput))
	{
		AfxMessageBox(TEXT("��ѡ����ȷ������/���Ŀ¼"));
		return;
	}
	std::vector<CString> arrFileNames;
	TraverseDir(szDirInput,arrFileNames);

	m_CheckListBox.ResetContent();
	for (INT i=0; i<arrFileNames.size(); i++)
	{
		m_CheckListBox.AddString(arrFileNames[i]);
	}
}

void CProtobufferCompilerDlg::OnBnClickedOk()
{
	TCHAR szArgv[10][MAX_PATH]={TEXT("")};
	TCHAR szDirInput[MAX_PATH]=TEXT("");
	TCHAR szDirOutput[MAX_PATH]=TEXT("");
	GetDlgItemText(IDC_EDIT1,szDirInput,MAX_PATH);
	GetDlgItemText(IDC_EDIT2,szDirOutput,MAX_PATH);
	if (!PathFileExists(szDirInput) || !PathFileExists(szDirOutput))
	{
		AfxMessageBox(TEXT("��ѡ����ȷ������/���Ŀ¼"));
		return;
	}

	//_sntprintf(szArgv[0],MAX_PATH,TEXT("--proto_path=%s"),szDirInput);
	//_sntprintf(szArgv[1],MAX_PATH,TEXT("--cpp_out=%s"),szDirOutput);
	//_sntprintf(szArgv[2],MAX_PATH,TEXT("%s"),TEXT("Person3.proto"));
	//const char* pszArgv[10]={NULL};
	//pszArgv[0]=szArgv[0];
	//pszArgv[1]=szArgv[1];
	//pszArgv[2]=szArgv[2];
	//google::protobuf::compiler::CommandLineInterface cli;
	//cli.AllowPlugins("protoc-");

	//// Proto2 C++
	//google::protobuf::compiler::cpp::CppGenerator cpp_generator;
	//cli.RegisterGenerator("--cpp_out", "--cpp_opt", &cpp_generator,
	//	"Generate C++ header and source.");

	//cli.Run(3, pszArgv);
	//Sleep(1000);

	//TCHAR szCmdParam[MAX_PATH]=TEXT("");
	//_sntprintf(szCmdParam,MAX_PATH,TEXT("%s\\protoc.exe --cpp_out=%s --proto_path=%s"),m_szWorkDir,szDirOutput,TEXT("Person3.proto"));
	//WinExec(szCmdParam,SW_SHOWNORMAL);

	//TCHAR szCmdParam[MAX_PATH]=TEXT("");
	//_sntprintf(szCmdParam,MAX_PATH,TEXT("--cpp_out=%s --proto_path=%s"),szDirOutput,TEXT("Person3.proto"));
	//TCHAR szExePath[MAX_PATH]=TEXT("");
	//_sntprintf(szExePath,MAX_PATH,TEXT("%s\\protoc.exe"),m_szWorkDir);
	//HINSTANCE hResult=ShellExecute(m_hWnd,"open",szExePath,szCmdParam,NULL,SW_SHOWNORMAL);

	SECURITY_ATTRIBUTES sa;  
	HANDLE hRead,hWrite;  

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);  
	sa.lpSecurityDescriptor = NULL;  
	sa.bInheritHandle = TRUE;  

	if(!CreatePipe(&hRead,&hWrite,&sa,0))  
	{  
		MessageBox("CreatePipe Failed");  
		return;  
	}  

	STARTUPINFO StartInfo;  
	ZeroMemory(&StartInfo,sizeof(STARTUPINFO));  
	StartInfo.cb = sizeof(STARTUPINFO);  
	GetStartupInfo(&StartInfo);  
	StartInfo.hStdError = hWrite;  
	StartInfo.hStdOutput = hWrite;  
	StartInfo.wShowWindow = SW_HIDE;  
	StartInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;  

	CString strOutput=TEXT(""); 
	CString strFileName=TEXT("");
	CString strExePath=TEXT("");
	strExePath.Format(TEXT("%s\\protoc.exe"),m_szWorkDir);

	for (int i=0; i<m_CheckListBox.GetCount(); i++)
	{
		if (m_CheckListBox.GetCheck(i)==BST_CHECKED)
		{
			TCHAR szCmdLine[MAX_PATH]=TEXT("");
			CString strItemText=TEXT("");
			m_CheckListBox.GetText(i,strItemText);
			strFileName.Format(TEXT("%s"),strItemText);
			_sntprintf(szCmdLine,MAX_PATH,TEXT("protoc --cpp_out=%s --proto_path=%s %s"),szDirOutput,szDirInput,strFileName);

			PROCESS_INFORMATION ProcessInfo;
			ZeroMemory(&ProcessInfo,sizeof(PROCESS_INFORMATION)); 
			if(!CreateProcess(strExePath,szCmdLine,NULL,NULL,TRUE,NULL,NULL,NULL,&StartInfo,&ProcessInfo))  
			{  
				ZeroMemory(&ProcessInfo,sizeof(ProcessInfo));
				MessageBox("���̴���ʧ��!");  
				return;  
			} 
			CloseHandle(hWrite);

			TCHAR buffer[4096] = TEXT("");  		
			DWORD bytesRead=0;  

			strOutput += strItemText;
			strOutput += ": ";
			while(1)  
			{  
				if(NULL == ReadFile(hRead,buffer,4095,&bytesRead,NULL))  
				{  
					break;  
				}
				strOutput += buffer; 
				Sleep(10);  
			}
			if (strOutput.Right(2)==TEXT(": "))
			{
				strOutput += TEXT("Success!");
			}
			strOutput += "\r\n";
		}
	}

	CloseHandle(hRead);  

	if (strOutput.GetLength()>0)
	{
		AfxMessageBox(strOutput);
	}
	
	return;
}

//ȫѡ
void CProtobufferCompilerDlg::OnBnClickedSelect1()
{
	bool bCheckd=((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()==BST_CHECKED?true:false;
	if (bCheckd)
	{
		for (int i=0; i<m_CheckListBox.GetCount(); i++)
		{
			if (m_CheckListBox.GetCheck(i)!=BST_CHECKED)
			{
				m_CheckListBox.SetCheck(i,BST_CHECKED);
			}
		}
	}
	else
	{
		for (int i=0; i<m_CheckListBox.GetCount(); i++)
		{
			if (m_CheckListBox.GetCheck(i)==BST_CHECKED)
			{
				m_CheckListBox.SetCheck(i,BST_UNCHECKED);
			}
		}
	}
}

//��ѡ
void CProtobufferCompilerDlg::OnBnClickedSelect2()
{
	for (int i=0; i<m_CheckListBox.GetCount(); i++)
	{
		if (m_CheckListBox.GetCheck(i)==BST_CHECKED)
		{
			m_CheckListBox.SetCheck(i,BST_UNCHECKED);
		}
		else
		{
			m_CheckListBox.SetCheck(i,BST_CHECKED);
		}
	}
}

void CProtobufferCompilerDlg::OnEnChangeEdit1()
{
	return;
}

void CProtobufferCompilerDlg::OnEnChangeEdit2()
{
	return;
}

void CProtobufferCompilerDlg::OnBnClickedButton1()
{
	CString strFoldPath;
	CFolderPickerDialog dlg(m_szWorkDir, 0, NULL, 0); 
	if(dlg.DoModal()==IDOK)  
	{      
		strFoldPath=dlg.GetPathName();    //���·��  
	}  

	if (!PathFileExists(strFoldPath))
	{
		AfxMessageBox(TEXT("��ѡ����ȷ������Ŀ¼"));
	}
	else
	{
		SetDlgItemText(IDC_EDIT1,strFoldPath);
		FillFileListBox();
	}
}

void CProtobufferCompilerDlg::OnBnClickedButton2()
{
	CString strFoldPath;
	CFolderPickerDialog dlg(m_szWorkDir, 0, NULL, 0); 
	if(dlg.DoModal()==IDOK)  
	{      
		strFoldPath=dlg.GetPathName();    //���·��  
	}  

	SetDlgItemText(IDC_EDIT2,strFoldPath);
}