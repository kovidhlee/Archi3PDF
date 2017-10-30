// Archi3PrinterScaleBug_DemoDoc.cpp : CArchi3PrinterScaleBug_DemoDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Archi3PrinterScaleBug_Demo.h"
#endif

#include "Archi3PrinterScaleBug_DemoDoc.h"

#include <propkey.h>
#include "MainFrm.h"
#include "Archi3PrinterScaleBug_DemoView.h"
#include "PdfFileCreator.h"
#include "LineEntity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CArchi3PrinterScaleBug_DemoDoc

IMPLEMENT_DYNCREATE(CArchi3PrinterScaleBug_DemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CArchi3PrinterScaleBug_DemoDoc, CDocument)
END_MESSAGE_MAP()

// CArchi3PrinterScaleBug_DemoDoc ����/�Ҹ�

CArchi3PrinterScaleBug_DemoDoc::CArchi3PrinterScaleBug_DemoDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
}

CArchi3PrinterScaleBug_DemoDoc::~CArchi3PrinterScaleBug_DemoDoc()
{
	ClearList();
}

BOOL CArchi3PrinterScaleBug_DemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}

// CArchi3PrinterScaleBug_DemoDoc serialization

void CArchi3PrinterScaleBug_DemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CArchi3PrinterScaleBug_DemoDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CArchi3PrinterScaleBug_DemoDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CArchi3PrinterScaleBug_DemoDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CArchi3PrinterScaleBug_DemoDoc ����

#ifdef _DEBUG
void CArchi3PrinterScaleBug_DemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CArchi3PrinterScaleBug_DemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

CString CArchi3PrinterScaleBug_DemoDoc::GetSampleFilePath() const
{
	return _T("d:\\test1.pdf");
}

CString CArchi3PrinterScaleBug_DemoDoc::GetSampleDocumentName() const
{
	return GetTitle();
}

CString CArchi3PrinterScaleBug_DemoDoc::GetSampleUserID() const
{
	return _T("dhlee");
}

void CArchi3PrinterScaleBug_DemoDoc::PushSampleEntities()
{
	PointF ptStart, ptEnd;

	CLineEntity* pLineEntity = new CLineEntity;
	{
		ptStart.X = 100.f;
		ptStart.Y = 100.f;
		ptEnd.X = 200.f;
		ptEnd.Y = 100.f;
		pLineEntity->SetPoint(ptStart, ptEnd);
		m_MainList.push_back(pLineEntity);
	}

	CLineEntity* pLineEntity2 = new CLineEntity;
	{
		ptStart.X = 300.f;
		ptStart.Y = 100.f;
		ptEnd.X = 600.f;
		ptEnd.Y = 100.f;
		pLineEntity2->SetPoint(ptStart, ptEnd);
		m_MainList.push_back(pLineEntity2);
	}
}

void CArchi3PrinterScaleBug_DemoDoc::ClearList()
{
	auto size = m_MainList.size();
	for (auto iter = m_MainList.begin(); iter != m_MainList.end(); ++iter)
	{
		CBase* pBase = *iter;
		SAFE_DELETE(pBase);
	}
	m_MainList.clear();

	ASSERT(m_MainList.size() == 0);
}

void CArchi3PrinterScaleBug_DemoDoc::OnPdfFileSave()
{
	auto pView = (CArchi3PrinterScaleBug_DemoView*)::GetMainFrame()->GetActiveView();
	CDC* pDC = pView->GetDC();
	{
		CString sFileFullPath = GetSampleFilePath();
		CString sDocumentName = GetSampleDocumentName();
		CString sUserID = GetSampleUserID();

		DeleteFile(sFileFullPath);

		CPdfFileCreator pdfCreator;
		if (!pdfCreator.Create(pDC, sFileFullPath, sDocumentName, sUserID))
		{
			ASSERT(0);
			goto CleanUp;
		}
	}
CleanUp:
	pView->ReleaseDC(pDC);
}

#endif //_DEBUG

// CArchi3PrinterScaleBug_DemoDoc ���