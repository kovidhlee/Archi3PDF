#pragma once
class CPdfFileCreator
{
public:
	CPdfFileCreator();
	virtual ~CPdfFileCreator();

public:
	bool Create(CDC* pClientDC, LPCTSTR sFileFullPath, LPCTSTR sDocumentName, LPCTSTR sUserID);

private:
	bool PrepareCanvas(PHANDLE pPrinterHandle, HDC pPrintDC);
	bool DrawOnPDF(LPCTSTR sFileFullPath, LPCTSTR sDocumentName, LPCTSTR sUserID);
};
