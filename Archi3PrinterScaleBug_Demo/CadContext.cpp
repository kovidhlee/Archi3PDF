#include "stdafx.h"
#include "CadContext.h"

/*
	Imitate CcadContext class in Archi3 Project
*/

CCadContext::CCadContext()
	: m_fRateMax(0.f)
	, m_fRateMin(0.f)
	, m_fWinRate(0.f)
	, m_hWnd(nullptr)
	, m_fZoomRate(0.f)
{
}

CCadContext::~CCadContext()
{
}

CRect CCadContext::GetClientRect()
{
	CRect rcArea;
	::GetClientRect(m_hWnd, rcArea);
	return rcArea;
}

void CCadContext::SetMainView(HWND hWnd)
{
	m_hWnd = hWnd;
}

void CCadContext::SetCadContext(CADCONTEXT* pCon)
{
	m_hWnd = pCon->hWnd;
	m_fZoomRate = pCon->fBasicZoomRate;
	m_fRateMax = pCon->fZoomMax;
	m_fRateMin = pCon->fZoomMin;
	m_enUnit = pCon->enWorldUnit;
	m_Print = pCon->printCon;

	SetCenterPoint(pCon->ptViewCenter);
}

void CCadContext::GetCadContext(CADCONTEXT* pCon)
{
	pCon->hWnd = m_hWnd;
	pCon->fBasicZoomRate = m_fZoomRate;
	pCon->fZoomMax = m_fRateMax;
	pCon->fZoomMin = m_fRateMin;
	pCon->enWorldUnit = m_enUnit;
	pCon->printCon = m_Print;
	pCon->enRenderMode = KVDRM_HIGHQUALITY;
	pCon->ptViewCenter = GetCenterPoint();

	REAL el[6];
	m_WorldMat.GetElements(el);
}

void CCadContext::TranslateCenter(float dx, float dy, BOOL bDP /*= TRUE*/)
{
	Graphics gdGr(m_hWnd);
	CreateLogicalDC(&gdGr);

	PointF gdpt[2];
	if (bDP)
	{
		gdpt[0] = PointF(0, 0);
		gdpt[1] = PointF(dx, dy);
		gdGr.TransformPoints(CoordinateSpaceWorld, CoordinateSpaceDevice, gdpt, 2);
		gdpt[1] = gdpt[1] - gdpt[0];
	}
	else
	{
		gdpt[1] = PointF(dx, dy);
	}

	m_WorldMat.Translate(gdpt[1].X, gdpt[1].Y, MatrixOrderAppend);
}

void CCadContext::ZoomStep(CPoint ptCenter, float fRate, BOOL bZoomIn)
{
	Graphics gdGr(m_hWnd);
	CreateLogicalDC(&gdGr);

	PointF gdPrev(ptCenter.x, ptCenter.y);
	gdGr.TransformPoints(CoordinateSpaceWorld, CoordinateSpaceDevice, &gdPrev, 1);

	if (bZoomIn)
		IncreaseRate(fRate);
	else
		DecreaseRate(fRate);

	CreateLogicalDC(&gdGr);
	PointF gdCur(ptCenter.x, ptCenter.y);
	gdGr.TransformPoints(CoordinateSpaceWorld, CoordinateSpaceDevice, &gdCur, 1);

	m_WorldMat.Translate(gdCur.X - gdPrev.X, gdPrev.Y - gdCur.Y, MatrixOrderAppend);
}

void CCadContext::IncreaseRate(float fPercent)
{
	m_fZoomRate *= (1.f + (fPercent / 100));
}

void CCadContext::DecreaseRate(float fPercent)
{
	m_fZoomRate *= (1.f - (fPercent / 100));
}

void CCadContext::CreateLogicalDC(Graphics *pGr, BOOL bWantDisplay)
{
	if (m_Print.hPrintDC && !bWantDisplay)
	{
		pGr->SetPageUnit(m_Print.enPrintUnit);
		float fXrate = (m_Print.PrintSize.cx / m_Print.PrintDPI.Width) /
			(m_Print.rcPaper.Width() / m_Print.DisplayDPI.Width);
		float fYrate = (m_Print.PrintSize.cy / m_Print.PrintDPI.Height) /
			(m_Print.rcPaper.Height() / m_Print.DisplayDPI.Height);

		float fRate = 1.f;
		if (fXrate > fYrate)
		{
			fRate = ((fYrate) / m_Print.fDtoInchRate) * m_Print.fInchtoPRate;
		}
		else
		{
			fRate = ((fXrate) / m_Print.fDtoInchRate) * m_Print.fInchtoPRate;
		}

		pGr->SetPageScale(m_fZoomRate * fRate);
		pGr->SetTransform(&m_WorldMat);
		pGr->TranslateTransform(-m_Print.ptGap.X, m_Print.ptGap.Y, MatrixOrderAppend);
	}
	else
	{
		REAL el[6];
		m_WorldMat.GetElements(el);
		pGr->SetPageUnit(m_enUnit);
		pGr->SetPageScale(m_fZoomRate);
		pGr->SetTransform(&m_WorldMat);
	}
}

void CCadContext::CreateLogicalDC(CDC* pDC)
{
	float sizex, sizey;
	float tmpx, tmpy;
	CSize aSize;

	pDC->SetMapMode(MM_ISOTROPIC);
	// tmp는 view내에서 볼수 있는 실제 영역(mm)
	aSize.cx = aSize.cy = 100;	// 1mm
	pDC->HIMETRICtoDP(&aSize);	// 1mm는 몇 픽셀?
	CRect rcViewPort;
	::GetClientRect(m_hWnd, rcViewPort);

	tmpx = rcViewPort.Width() / float(aSize.cx);	// width의 총 길이(mm)
	tmpy = rcViewPort.Height() / float(aSize.cy);	// height의 총 길이(mm)

	sizex = (tmpx / m_fZoomRate);// * 10.f;// * m_fWinRate;
	sizey = (tmpy / m_fZoomRate);// * 10.f;// * m_fWinRate;

	pDC->SetWindowExt(sizex, -sizey);
	pDC->SetViewportExt(rcViewPort.Width(), rcViewPort.Height());

	REAL el[6];
	m_WorldMat.GetElements(el);
	pDC->SetWindowOrg(-el[4], el[5]);
}

void CCadContext::SetCenterPoint(CPoint ptNew)
{
	m_ptCenter = ptNew;	// dctest

	Graphics gdGr(m_hWnd);
	gdGr.SetPageUnit(m_enUnit);
	gdGr.SetPageScale(m_fZoomRate);

	PointF gdCenter(ptNew.x, ptNew.y);
	gdGr.TransformPoints(CoordinateSpaceWorld, CoordinateSpaceDevice, &gdCenter, 1);
	REAL elMat[6];
	m_WorldMat.GetElements(elMat);
	elMat[4] = gdCenter.X;
	elMat[5] = gdCenter.Y;
	m_WorldMat.SetElements(elMat[0], elMat[1], elMat[2], elMat[3],
		elMat[4], elMat[5]);
}

void CCadContext::SetCenterPoint(PointF ptNew)
{
	REAL elMat[6];
	m_WorldMat.GetElements(elMat);
	elMat[4] = ptNew.X;
	elMat[5] = ptNew.Y;
	m_WorldMat.SetElements(elMat[0], elMat[1], elMat[2], elMat[3],
		elMat[4], elMat[5]);
}

// 리턴을 CPointF로 해야 하는 것이 맞으나, 현재 Archi3에서 CPoint로 리턴하기 때문에
// 동일한 결과를 위해 CPoint로 리턴합니다.
CPoint CCadContext::GetCenterPoint()
{
	REAL elMat[6];
	m_WorldMat.GetElements(elMat);
	PointF gdCenter(elMat[4], elMat[5]);

	Graphics gdGr(m_hWnd);
	gdGr.SetPageUnit(m_enUnit);
	gdGr.SetPageScale(m_fZoomRate);
	gdGr.TransformPoints(CoordinateSpaceDevice, CoordinateSpaceWorld, &gdCenter, 1);

	return CPoint(static_cast<long>(gdCenter.X), static_cast<long>(gdCenter.Y));
}