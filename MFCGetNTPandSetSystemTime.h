
// MFCGetNTPandSetSystemTime.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCGetNTPandSetSystemTimeApp:
// �йش����ʵ�֣������ MFCGetNTPandSetSystemTime.cpp
//

class CMFCGetNTPandSetSystemTimeApp : public CWinApp
{
public:
	CMFCGetNTPandSetSystemTimeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCGetNTPandSetSystemTimeApp theApp;