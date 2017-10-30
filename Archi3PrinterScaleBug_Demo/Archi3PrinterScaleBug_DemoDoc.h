// Archi3PrinterScaleBug_DemoDoc.h : CArchi3PrinterScaleBug_DemoDoc Ŭ������ �������̽�
//

#pragma once

class CBase;

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
	// ������ �޽��� �� �Լ�
protected:

	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
