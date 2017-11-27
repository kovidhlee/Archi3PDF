// Archi3PrinterScaleBug_DemoView.h : CArchi3PrinterScaleBug_DemoView Ŭ������ �������̽�
//

#pragma once

class CArchi3PrinterScaleBug_DemoDoc;

class CArchi3PrinterScaleBug_DemoView : public CView
{
protected: // serialization������ ��������ϴ�.
	CArchi3PrinterScaleBug_DemoView();
	DECLARE_DYNCREATE(CArchi3PrinterScaleBug_DemoView)

	// Ư���Դϴ�.
public:
	CArchi3PrinterScaleBug_DemoDoc* GetDocument() const;

	// �۾��Դϴ�.
public:

	// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// �����Դϴ�.
public:
	virtual ~CArchi3PrinterScaleBug_DemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint pt);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint pt);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint pt);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Archi3PrinterScaleBug_DemoView.cpp�� ����� ����
inline CArchi3PrinterScaleBug_DemoDoc* CArchi3PrinterScaleBug_DemoView::GetDocument() const
{
	return reinterpret_cast<CArchi3PrinterScaleBug_DemoDoc*>(m_pDocument);
}
#endif
