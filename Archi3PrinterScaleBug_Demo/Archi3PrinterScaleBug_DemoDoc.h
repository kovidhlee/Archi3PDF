// Archi3PrinterScaleBug_DemoDoc.h : CArchi3PrinterScaleBug_DemoDoc Ŭ������ �������̽�
//

#pragma once
#include <memory>

class CBase;
class COperator;
class CWorld;
class CCadContext;

class CArchi3PrinterScaleBug_DemoDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CArchi3PrinterScaleBug_DemoDoc();
	DECLARE_DYNCREATE(CArchi3PrinterScaleBug_DemoDoc)

	// Ư���Դϴ�.
	// �۾��Դϴ�.
public:

	// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// �����Դϴ�.
public:
	virtual ~CArchi3PrinterScaleBug_DemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	std::list<CBase*> m_MainList;
	std::shared_ptr<COperator> m_pOperator;
	std::shared_ptr<CWorld> m_pWorld;

public:
	void PushSampleEntities();
	void ClearList();
	void OPER_InitWindow(HWND hWnd, CPoint point = CPoint(0, 0));
	void OPER_OnMouseMove(CPoint pt);
	void OPER_OnMouseWheel(short zDelta, CPoint pt);
	void OPER_OnMButtonDown(CPoint pt);
	void OPER_OnMButtonUp(CPoint pt);
	void OPER_Render(BOOL bPrint = FALSE, CDC* pDC = nullptr);
	CWorld* KVDworld_create(CCadContext* pCad);
	RectF KVDworld_dptolp_rect(Graphics* pGr, CRect rc);
	void KVDworld_draw(BOOL bPrint, RectF rcClip, BOOL bDPClip, float fClipGap);

private:
	CString GetSampleFilePath() const;
	CString GetSampleDocumentName() const;
	CString GetSampleUserID() const;

public:
	std::list<CBase*> GetMainList() const { return m_MainList; }
	void SetMainList(std::list<CBase*> val) { m_MainList = val; }

protected:

public:
	afx_msg void OnPdfFileSave();
	// ������ �޽��� �� �Լ�
protected:

	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
