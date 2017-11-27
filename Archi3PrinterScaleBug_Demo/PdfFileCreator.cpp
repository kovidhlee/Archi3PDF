#include "stdafx.h"
#include "PdfFileCreator.h"
#include <memory>
#include <functional>
#include <winspool.h>
#include "MainFrm.h"
#include "Archi3PrinterScaleBug_DemoDoc.h"
#include "Base.h"
#include "CStringUtils.h"

namespace
{
	std::shared_ptr<HDC__> CreateSharedDC(
		_In_opt_ LPCWSTR pwszDriver, _In_opt_ LPCWSTR pwszDevice,
		_In_opt_ LPCWSTR pszPort, _In_opt_ CONST DEVMODEW * pdm)
	{
		return std::shared_ptr<HDC__>(CreateDCW(pwszDriver, pwszDevice, pszPort, pdm), DeleteDC);
	}

	std::shared_ptr<HDC__> CreateSharedDC(
		_In_opt_ LPCSTR pwszDriver, _In_opt_ LPCSTR pwszDevice,
		_In_opt_ LPCSTR pszPort, _In_opt_ CONST DEVMODEA * pdm)
	{
		return std::shared_ptr<HDC__>(CreateDCA(pwszDriver, pwszDevice, pszPort, pdm), DeleteDC);
	}
}

CPdfFileCreator::CPdfFileCreator()
{
}

CPdfFileCreator::~CPdfFileCreator()
{
}

std::shared_ptr<void> OpenPrinterShared(_In_  LPTSTR pPrinterName, _In_  LPPRINTER_DEFAULTS pDefault)
{
	HANDLE printerHandle = NULL;
	OpenPrinter(pPrinterName, &printerHandle, NULL);
	return std::shared_ptr<void>(printerHandle, ClosePrinter);
}

bool CPdfFileCreator::Create(CDC* pClientDC, LPCTSTR sFileFullPath, LPCTSTR sDocumentName, LPCTSTR sUserID)
{
	CString sErrMessage;

	CString sPrinterName(_T("Microsoft Print to PDF"));
	auto printerHandle = OpenPrinterShared((LPTSTR)(LPCTSTR)sPrinterName, NULL);
	if (!printerHandle)
	{
		sErrMessage = CStringUtils::FormattedString(_T("OpenPrinter failed.(errorCode : %d)"), GetLastError());
		AfxMessageBox(sErrMessage);
		return false;
	}

	// fetch size of printer info structure
	DWORD dwBytesNeeded = 0;
	DWORD dwBytesReturned = 0;
	GetPrinter(printerHandle.get(), 2, NULL, 0, &dwBytesNeeded);
	std::vector<BYTE> buffer(dwBytesNeeded, (BYTE)0);
	if (GetPrinter(printerHandle.get(), 2, buffer.data(), dwBytesNeeded, &dwBytesReturned) == 0)
	{
		sErrMessage = _T("GetPrinter failed.(fill in structure)");
		AfxMessageBox(sErrMessage);
		return false;
	}
	auto printerInfo = (PRINTER_INFO_2*)buffer.data();
	printerInfo->pDevMode->dmOrientation = DMORIENT_LANDSCAPE;

	// Get a device context for the printer

	auto hdcPrint = CreateSharedDC(NULL, sPrinterName, NULL, printerInfo->pDevMode);
	if (!hdcPrint)
	{
		sErrMessage = _T("CreateDC failed");
		AfxMessageBox(sErrMessage);
		return false;
	}

	if (!PrepareCanvas(printerHandle.get(), hdcPrint.get()))
		return false;

	DrawOnPDF(printerHandle.get(), hdcPrint.get(), sFileFullPath, sDocumentName, sUserID);

	return true;
}

bool CPdfFileCreator::PrepareCanvas(HANDLE pPrinterHandle, HDC pPrintDC)
{
	ASSERT(pPrinterHandle);
	ASSERT(pPrintDC);

	return true;
}

bool CPdfFileCreator::DrawOnPDF(HANDLE pPrinterHandle, HDC pPrintDC, LPCTSTR sFileFullPath, LPCTSTR sDocumentName, LPCTSTR sUserID)
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