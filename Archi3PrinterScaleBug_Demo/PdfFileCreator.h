#pragma once
class CPdfFileCreator
{
public:
	CPdfFileCreator();
	virtual ~CPdfFileCreator();

public:
	bool Create(CDC* pClientDC, LPCTSTR sFileFullPath, LPCTSTR sDocumentName, LPCTSTR sUserID);

private:
	bool PrepareCanvas(HANDLE pPrinterHandle, HDC pPrintDC);
	bool DrawOnPDF(HANDLE pPrinterHandle, HDC pPrintDC, LPCTSTR sFileFullPath, LPCTSTR sDocumentName, LPCTSTR sUserID);
};
