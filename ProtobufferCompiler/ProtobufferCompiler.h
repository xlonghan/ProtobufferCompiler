
// ProtobufferCompiler.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CProtobufferCompilerApp:
// �йش����ʵ�֣������ ProtobufferCompiler.cpp
//

class CProtobufferCompilerApp : public CWinApp
{
public:
	CProtobufferCompilerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CProtobufferCompilerApp theApp;