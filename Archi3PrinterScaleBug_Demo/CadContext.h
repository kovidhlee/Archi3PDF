#pragma once

#include "KVDfunction.h"

class CCadContext
{
public:
	float m_fRateMax;
	float m_fRateMin;
	float m_fWinRate;
	CPoint m_ptCenter;
	CRect m_rectViewport;
	Matrix m_WorldMat;
	HWND m_hWnd;
	Unit m_enUnit;
	float m_fZoomRate;
	PRINTCONTEXT m_Print;

public:
	CCadContext();
	virtual ~CCadContext();

public:
	CRect GetClientRect();

	void SetMainView(HWND hWnd);
	void SetCadContext(CADCONTEXT* pCon);
	void GetCadContext(CADCONTEXT* pCon);
	void TranslateCenter(float dx, float dy, BOOL bDP = TRUE);
	void ZoomStep(CPoint ptCenter, float fRate, BOOL bZoomIn);
	void IncreaseRate(float fPercent);
	void DecreaseRate(float fPercent);
	void CreateLogicalDC(CDC* pDC);
	void CreateLogicalDC(Graphics *pGr, BOOL bWantDisplay = FALSE);
	void SetCenterPoint(CPoint ptNew);
	void SetCenterPoint(PointF ptNew);
	CPoint	GetCenterPoint();
};
