
// RoutePlanning1.0.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRoutePlanning10App: 
// �йش����ʵ�֣������ RoutePlanning1.0.cpp
//

class CRoutePlanning10App : public CWinApp
{
public:
	CRoutePlanning10App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRoutePlanning10App theApp;