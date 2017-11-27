#pragma once

class CTempletNode
{
private:
	RectF m_rcClip;

public:
	CTempletNode();
	virtual ~CTempletNode();

public:
	void Render(BOOL bPrint, CDC* pDC);

private:
	float GetDisplayDPIWidth(Graphics* pDisplay);
	float GetDisplayDPIHeight(Graphics* pDisplay);
	float GetPrintDPIWidth(Graphics* pPrint);
	float GetPrintDPIHeight(Graphics* pPrint);
	int GetDeviceContextWidth(CDC* pDC);
	int GetDeviceContextHeight(CDC* pDC);
	RectF GetCurClipArea();
};
