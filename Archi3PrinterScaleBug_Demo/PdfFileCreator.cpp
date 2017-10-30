#include "stdafx.h"
#include "PdfFileCreator.h"
#include <winspool.h>
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

	HDC hdcPrint;
	HANDLE printerHandle;
	DWORD dwBytesReturned = 0;
	DWORD dwBytesNeeded = 0;

	PRINTER_INFO_2* p2 = nullptr;

	TCHAR sPrinterName[100];
	{
		ZeroMemory(&sPrinterName, sizeof(TCHAR) * 100);
		_tcscpy_s(sPrinterName, _countof(sPrinterName), _T("Microsoft Print to PDF"));
	}

	if (!OpenPrinter(sPrinterName, &printerHandle, NULL))
	{
		sErrMessage = CStringUtils::FormattedString(_T("OpenPrinter failed.(errorCode : %d)"), GetLastError());
		AfxMessageBox(sErrMessage);
		goto CleanUp;
	}

	// fetch size of printer info structure
	GetPrinter(printerHandle, 2, NULL, 0, &dwBytesNeeded);

	// fill in printer info structure
	p2 = (PRINTER_INFO_2*) new BYTE[dwBytesNeeded];
	if (GetPrinter(printerHandle, 2, (LPBYTE)p2, dwBytesNeeded, &dwBytesReturned) == 0)
	{
		sErrMessage = _T("GetPrinter failed.(fill in structure)");
		AfxMessageBox(sErrMessage);
		goto CleanUp;
	}

	p2->pDevMode->dmOrientation = DMORIENT_LANDSCAPE;

	// Get a device context for the printer
	if (NULL == (hdcPrint = CreateDC(NULL, sPrinterName, NULL, p2->pDevMode)))
	{
		sErrMessage = _T("CreateDC failed");
		AfxMessageBox(sErrMessage);

		goto CleanUp;
	}

	bool bResult = PrepareCanvas(&printerHandle, hdcPrint);
	if (bResult)
	{
		DrawOnPDF(sFileFullPath, sDocumentName, sUserID);
	}

CleanUp:
	SAFE_DELETE_ARRAY(p2);
	ClosePrinter(printerHandle);
	DeleteDC(hdcPrint);

	BOOL bSuccess = sErrMessage.IsEmpty();
	if (bSuccess)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool CPdfFileCreator::PrepareCanvas(PHANDLE pPrinterHandle, HDC pPrintDC)
{
	ASSERT(pPrinterHandle);
	ASSERT(pPrintDC);

	return true;
}

bool CPdfFileCreator::DrawOnPDF(LPCTSTR sFileFullPath, LPCTSTR sDocumentName, LPCTSTR sUserID)
{
	return true;
}