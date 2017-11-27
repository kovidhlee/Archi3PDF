// Archi3PrinterScaleBug_Demo.h : Archi3PrinterScaleBug_Demo 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.

class CWorld;

// CArchi3PrinterScaleBug_DemoApp:
// 이 클래스의 구현에 대해서는 Archi3PrinterScaleBug_Demo.cpp을 참조하십시오.
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

	// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// 구현입니다.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	CWorld* GetMainWorld()
	{
		return m_kvdWorld;
	}
};

extern CArchi3PrinterScaleBug_DemoApp theApp;
