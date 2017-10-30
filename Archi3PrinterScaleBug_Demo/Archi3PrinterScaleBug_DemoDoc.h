// Archi3PrinterScaleBug_DemoDoc.h : CArchi3PrinterScaleBug_DemoDoc 클래스의 인터페이스
//

#pragma once

class CBase;

class CArchi3PrinterScaleBug_DemoDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CArchi3PrinterScaleBug_DemoDoc();
	DECLARE_DYNCREATE(CArchi3PrinterScaleBug_DemoDoc)

	// 특성입니다.
	// 작업입니다.
public:

	// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// 구현입니다.
public:
	virtual ~CArchi3PrinterScaleBug_DemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	std::list<CBase*> m_MainList;

public:
	void PushSampleEntities();
	void ClearList();

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
	// 생성된 메시지 맵 함수
protected:

	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
