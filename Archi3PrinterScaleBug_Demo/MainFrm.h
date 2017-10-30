// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once

class CArchi3PrinterScaleBug_DemoApp;
class CArchi3PrinterScaleBug_DemoDoc;

class CMainFrame : public CFrameWnd
{
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	// Ư���Դϴ�.
public:

	// �۾��Դϴ�.
public:

	// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

	// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};

inline CArchi3PrinterScaleBug_DemoApp* const GetMainApp()
{
	return (CArchi3PrinterScaleBug_DemoApp*)AfxGetApp();
}

inline CMainFrame* const GetMainFrame()
{
	return (CMainFrame*)AfxGetApp()->m_pMainWnd;
}

inline CArchi3PrinterScaleBug_DemoDoc* const GetCurDocument()
{
	CMainFrame* pMainFrame = GetMainFrame();
	if (!pMainFrame)
		return nullptr;

	return (CArchi3PrinterScaleBug_DemoDoc*)pMainFrame->GetActiveDocument();
}