
// ProtobufferCompilerDlg.h : 头文件
//

#pragma once


// CProtobufferCompilerDlg 对话框
class CProtobufferCompilerDlg : public CDialogEx
{
// 构造
public:
	CProtobufferCompilerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PROTOBUFFERCOMPILER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	TCHAR	m_szWorkDir[MAX_PATH];
	CCheckListBox m_CheckListBox;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void FillFileListBox();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSelect1();
	afx_msg void OnBnClickedSelect2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();	
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
};
