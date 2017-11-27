// Archi3PrinterScaleBug_DemoView.h : CArchi3PrinterScaleBug_DemoView 클래스의 인터페이스
//

#pragma once

class CArchi3PrinterScaleBug_DemoDoc;

class CArchi3PrinterScaleBug_DemoView : public CView
{
protected: // serialization에서만 만들어집니다.
	CArchi3PrinterScaleBug_DemoView();
	DECLARE_DYNCREATE(CArchi3PrinterScaleBug_DemoView)

	// 특성입니다.
public:
	CArchi3PrinterScaleBug_DemoDoc* GetDocument() const;

	// 작업입니다.
public:

	// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 구현입니다.
public:
	virtual ~CArchi3PrinterScaleBug_DemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint pt);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint pt);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint pt);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Archi3PrinterScaleBug_DemoView.cpp의 디버그 버전
inline CArchi3PrinterScaleBug_DemoDoc* CArchi3PrinterScaleBug_DemoView::GetDocument() const
{
	return reinterpret_cast<CArchi3PrinterScaleBug_DemoDoc*>(m_pDocument);
}
#endif
