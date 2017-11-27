// Archi3PrinterScaleBug_Demo.h : Archi3PrinterScaleBug_Demo ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.

class CWorld;

// CArchi3PrinterScaleBug_DemoApp:
// �� Ŭ������ ������ ���ؼ��� Archi3PrinterScaleBug_Demo.cpp�� �����Ͻʽÿ�.
//

class CArchi3PrinterScaleBug_DemoApp : public CWinAppEx
{
public:
	CWorld* m_kvdWorld;
private:
	bool m_bGdiSuccess;
	ULONG_PTR m_gdiplusToken;

public:
	CArchi3PrinterScaleBug_DemoApp();
	virtual ~CArchi3PrinterScaleBug_DemoApp();

private:
	BOOL InitGDIPlus();
	void ReleaseGDIPlus();
	BOOL LoadTestScene();

	// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	CWorld* GetMainWorld()
	{
		return m_kvdWorld;
	}
};

extern CArchi3PrinterScaleBug_DemoApp theApp;
