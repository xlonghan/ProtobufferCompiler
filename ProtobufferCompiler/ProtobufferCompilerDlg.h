
// ProtobufferCompilerDlg.h : ͷ�ļ�
//

#pragma once


// CProtobufferCompilerDlg �Ի���
class CProtobufferCompilerDlg : public CDialogEx
{
// ����
public:
	CProtobufferCompilerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PROTOBUFFERCOMPILER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	TCHAR	m_szWorkDir[MAX_PATH];
	CCheckListBox m_CheckListBox;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
