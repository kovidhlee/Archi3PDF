#include "stdafx.h"
#include "PdfFileCreator.h"
#include <memory>
#include <functional>
#include <winspool.h>
#include "MainFrm.h"
#include "Archi3PrinterScaleBug_DemoDoc.h"
#include "Base.h"
#include "CStringUtils.h"

CPdfFileCreator::CPdfFileCreator()
{
}

CPdfFileCreator::~CPdfFileCreator()
{
}

bool CPdfFileCreator::Create(CDC* pClientDC, LPCTSTR sFileFullPath, LPCTSTR sDocumentName, LPCTSTR sUserID)
{
	CString sErrMessage;

	TCHAR sPrinterName[100];
	{
		ZeroMemory(&sPrinterName, sizeof(TCHAR) * 100);
		_tcscpy_s(sPrinterName, _countof(sPrinterName), _T("Microsoft Print to PDF"));
	}

	HANDLE printerHandle;
	if (!OpenPrinter(sPrinterName, &printerHandle, NULL))
	{
		sErrMessage = CStringUtils::FormattedString(_T("OpenPrinter failed.(errorCode : %d)"), GetLastError());
		AfxMessageBox(sErrMessage);
		return false;
	}
	std::shared_ptr<void> printerHandleHolder(printerHandle, ClosePrinter);

	// fetch size of printer info structure
	DWORD dwBytesNeeded = 0;
	DWORD dwBytesReturned = 0;
	GetPrinter(printerHandleHolder.get(), 2, NULL, 0, &dwBytesNeeded);
	std::vector<BYTE> buffer(dwBytesNeeded, (BYTE)0);
	if (GetPrinter(printerHandleHolder.get(), 2, buffer.data(), dwBytesNeeded, &dwBytesReturned) == 0)
	{
		sErrMessage = _T("GetPrinter failed.(fill in structure)");
		AfxMessageBox(sErrMessage);
		return false;
	}
	auto p2 = (PRINTER_INFO_2*)buffer.data();
	p2->pDevMode->dmOrientation = DMORIENT_LANDSCAPE;

	// Get a device context for the printer
	std::shared_ptr<HDC__> hdcPrint(CreateDC(NULL, sPrinterName, NULL, p2->pDevMode), DeleteDC);

	if (!hdcPrint)
	{
		sErrMessage = _T("CreateDC failed");
		AfxMessageBox(sErrMessage);
		return false;
	}

	if (!PrepareCanvas(&printerHandle, hdcPrint.get()))
		return false;

	DrawOnPDF(&printerHandle, hdcPrint.get(), sFileFullPath, sDocumentName, sUserID);
	return true;
}

bool CPdfFileCreator::PrepareCanvas(PHANDLE pPrinterHandle, HDC pPrintDC)
{
	ASSERT(pPrinterHandle);
	ASSERT(pPrintDC);

	return true;
}

bool CPdfFileCreator::DrawOnPDF(PHANDLE pPrinterHandle, HDC pPrintDC, LPCTSTR sFileFullPath, LPCTSTR sDocumentName, LPCTSTR sUserID)
{
	ASSERT(pPrinterHandle);
	ASSERT(pPrintDC);

	CString sErrMessage;

	DOCINFO docInfo;
	{
		ZeroMemory(&docInfo, sizeof(docInfo));
		docInfo.cbSize = sizeof(docInfo);
		docInfo.lpszDocName = sDocumentName;
		docInfo.lpszOutput = sFileFullPath;
	}

	int nResult = 0;
	if ((nResult = StartDoc(pPrintDC, &docInfo)) < 0)
	{
		sErrMessage = _T("StartDoc failed");
		ASSERT(0);
		goto CleanUp;
	}

	if (!StartPage(pPrintDC))
	{
		sErrMessage = _T("StartPage failed");
		ASSERT(0);
		goto CleanUp;
	}

	Graphics* g = new Graphics(pPrintDC, pPrinterHandle);
	{
		auto pDoc = (CArchi3PrinterScaleBug_DemoDoc*)GetCurDocument();
		if (!pDoc)
		{
			sErrMessage = _T("GetCurDocument() failed");
			ASSERT(0);
			SAFE_DELETE(g);
			goto CleanUp;
		}

		auto mainList = pDoc->GetMainList();
		for (auto iter = mainList.begin(); iter != mainList.end(); ++iter)
		{
			CBase* pBase = *iter;
			pBase->Draw(g, nullptr);
		}
	}
	SAFE_DELETE(g);

CleanUp:
	EndPage(pPrintDC);
	EndDoc(pPrintDC);

	auto noError = sErrMessage.IsEmpty();
	if (noError)
	{
		return true;
	}
	else
	{
		return false;
	}
}