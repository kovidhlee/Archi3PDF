// Archi3PrinterScaleBug_DemoView.cpp : CArchi3PrinterScaleBug_DemoView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CArchi3PrinterScaleBug_DemoView ����/�Ҹ�

CArchi3PrinterScaleBug_DemoView::CArchi3PrinterScaleBug_DemoView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CArchi3PrinterScaleBug_DemoView::~CArchi3PrinterScaleBug_DemoView()
{
}

BOOL CArchi3PrinterScaleBug_DemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CArchi3PrinterScaleBug_DemoView �׸���

void CArchi3PrinterScaleBug_DemoView::OnDraw(CDC* pDC)
{
	CArchi3PrinterScaleBug_DemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Gdiplus::Graphics g(pDC->m_hDC);
	{
		Pen pen(Color(255, 0, 0), 1.f);
		auto mainList = pDoc->GetMainList();
		for (auto iter = mainList.begin(); iter != mainList.end(); ++iter)
		{
			CBase* pBase = *iter;
			pBase->Draw(pDC, nullptr);
		}
	}
}

// CArchi3PrinterScaleBug_DemoView �μ�

BOOL CArchi3PrinterScaleBug_DemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CArchi3PrinterScaleBug_DemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CArchi3PrinterScaleBug_DemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

// CArchi3PrinterScaleBug_DemoView ����

#ifdef _DEBUG
void CArchi3PrinterScaleBug_DemoView::AssertValid() const
{
	CView::AssertValid();
}

void CArchi3PrinterScaleBug_DemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CArchi3PrinterScaleBug_DemoDoc* CArchi3PrinterScaleBug_DemoView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CArchi3PrinterScaleBug_DemoDoc)));
	return (CArchi3PrinterScaleBug_DemoDoc*)m_pDocument;
}
#endif //_DEBUG

// CArchi3PrinterScaleBug_DemoView �޽��� ó����

void CArchi3PrinterScaleBug_DemoView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (VK_F3 == nChar)
	{
		GetDocument()->OnPdfFileSave();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}