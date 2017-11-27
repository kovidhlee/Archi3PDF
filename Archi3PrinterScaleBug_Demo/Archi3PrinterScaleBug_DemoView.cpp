// Archi3PrinterScaleBug_DemoView.cpp : CArchi3PrinterScaleBug_DemoView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Archi3PrinterScaleBug_Demo.h"
#endif

#include "Archi3PrinterScaleBug_DemoDoc.h"
#include "Archi3PrinterScaleBug_DemoView.h"
#include "MainFrm.h"
#include "base.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CArchi3PrinterScaleBug_DemoView

IMPLEMENT_DYNCREATE(CArchi3PrinterScaleBug_DemoView, CView)

BEGIN_MESSAGE_MAP(CArchi3PrinterScaleBug_DemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CArchi3PrinterScaleBug_DemoView 생성/소멸

CArchi3PrinterScaleBug_DemoView::CArchi3PrinterScaleBug_DemoView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CArchi3PrinterScaleBug_DemoView::~CArchi3PrinterScaleBug_DemoView()
{
}

BOOL CArchi3PrinterScaleBug_DemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CArchi3PrinterScaleBug_DemoView 그리기

void CArchi3PrinterScaleBug_DemoView::OnDraw(CDC* pDC)
{
	CArchi3PrinterScaleBug_DemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OPER_Render(pDC->IsPrinting(), pDC);
}

// CArchi3PrinterScaleBug_DemoView 인쇄

BOOL CArchi3PrinterScaleBug_DemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CArchi3PrinterScaleBug_DemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CArchi3PrinterScaleBug_DemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

// CArchi3PrinterScaleBug_DemoView 진단

#ifdef _DEBUG
void CArchi3PrinterScaleBug_DemoView::AssertValid() const
{
	CView::AssertValid();
}

void CArchi3PrinterScaleBug_DemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

CArchi3PrinterScaleBug_DemoDoc* CArchi3PrinterScaleBug_DemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CArchi3PrinterScaleBug_DemoDoc)));
	return (CArchi3PrinterScaleBug_DemoDoc*)m_pDocument;
}

// CArchi3PrinterScaleBug_DemoView 메시지 처리기

int CArchi3PrinterScaleBug_DemoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CPoint pt;
	pt.x = lpCreateStruct->cx / 2;
	pt.y = lpCreateStruct->cy / 2;

	auto hwnd = GetSafeHwnd();
	GetDocument()->OPER_InitWindow(hwnd, pt);

	return 0;
}

BOOL CArchi3PrinterScaleBug_DemoView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CRect rt;
	this->GetWindowRect(rt);
	CPoint ptView = pt;
	ptView.x -= rt.left;
	ptView.y -= rt.top;

	GetDocument()->OPER_OnMouseWheel(zDelta, ptView);
	Invalidate(FALSE);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CArchi3PrinterScaleBug_DemoView::OnMouseMove(UINT nFlags, CPoint pt)
{
	GetDocument()->OPER_OnMouseMove(pt);
	GetDocument()->OPER_Render();

	CView::OnMouseMove(nFlags, pt);
}

void CArchi3PrinterScaleBug_DemoView::OnMButtonDown(UINT nFlags, CPoint pt)
{
	GetDocument()->OPER_OnMButtonDown(pt);
	CView::OnMButtonDown(nFlags, pt);
}

void CArchi3PrinterScaleBug_DemoView::OnMButtonUp(UINT nFlags, CPoint pt)
{
	GetDocument()->OPER_OnMButtonUp(pt);
	CView::OnMButtonUp(nFlags, pt);
}

void CArchi3PrinterScaleBug_DemoView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (VK_F3 == nChar)
	{
		GetDocument()->OnPdfFileSave();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}