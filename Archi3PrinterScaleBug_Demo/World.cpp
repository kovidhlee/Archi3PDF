#include "stdafx.h"
#include "World.h"
#include "CadContext.h"
#include "RtreeMgr.h"

CWorld::CWorld()
	:m_pContext(nullptr)
{
}

CWorld::~CWorld()
{
}

void CWorld::Draw(RectF rcClip /*= RectF(0, 0, 0, 0)*/, BOOL bDPClip /*= FALSE*/, float fClipGap /*= 10.f*/)
{
	if (!m_pContext)
	{
		__debugbreak();
		return;
	}

	CRect rcClient = m_pContext->GetClientRect(); 	// 현재 윈도우의 크기.(DP)
	rcClient.NormalizeRect();

	Graphics graph(m_pContext->m_hWnd);

	Bitmap memBit(rcClient.Width(), rcClient.Height(), &graph);
	Graphics memGra(&memBit);

	// 클리핑 영역 설정 및 LP모드 변경, 바탕색으로 clear
	if (rcClip.IsEmptyArea())	// 입력된 클리핑 영역이 없을 경우 화면크기로 클리핑.
	{
		RectF gdClip(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height());
		memGra.SetClip(gdClip);
	}
	else if (bDPClip)
	{
		memGra.SetClip(rcClip);
	}

	RectF rcQueryArea;
	memGra.GetClipBounds(&rcQueryArea);

	m_pContext->CreateLogicalDC(&memGra);

	if (!rcClip.IsEmptyArea() && !bDPClip)	// 입력된 클리핑 영역이 LP영역
	{
		memGra.SetClip(rcClip);
	}

	memGra.GetClipBounds(&rcQueryArea);
	if (!rcClip.IsEmptyArea())
	{
		rcQueryArea.Inflate(-fClipGap, -fClipGap);
		memGra.SetClip(rcQueryArea);	// 클리핑 영역에 걸쳐져서 그려지지 않는 것들 때문
	}

	Color clBackground = Color(255, 255, 255);
	memGra.Clear(clBackground);

	if (!rcClip.IsEmptyArea())
	{
		rcQueryArea.Inflate(fClipGap, fClipGap);
		memGra.SetClip(rcQueryArea);
		rcQueryArea.Inflate(fClipGap, fClipGap);
	}

	m_Rtree.DrawRtree(&memGra, rcQueryArea, FALSE);

	CachedBitmap gdCach(&memBit, &graph);
	graph.DrawCachedBitmap(&gdCach, 0, 0);
}

void CWorld::Print(RectF rcClip /*= RectF(0, 0, 0, 0)*/, BOOL bDPClip /*= FALSE*/)
{
	if (!m_pContext)
	{
		__debugbreak();
		return;
	}

	CRect rcClient = m_pContext->GetClientRect();
	rcClient.NormalizeRect();

	if (!m_pContext->m_Print.hPrintDC)
	{
		__debugbreak();
		return;
	}
	Graphics graph(m_pContext->m_Print.hPrintDC);

	Color clBackground = Color(255, 255, 255);
	graph.Clear(clBackground);

	if (bDPClip && !rcClip.IsEmptyArea())
	{
		graph.SetClip(rcClip);
	}

	m_pContext->CreateLogicalDC(&graph);
	if (!bDPClip && !rcClip.IsEmptyArea())
	{
		graph.SetClip(rcClip);
	}

	// 프린트시 그려질 노드는 윈도우 영역에 포함된 모두이다.
	Graphics grDis(m_pContext->m_hWnd);
	m_pContext->CreateLogicalDC(&grDis, TRUE);
	RectF rclpClient = DPtoLP(rcClient, &grDis);
}

Graphics* CWorld::GetGraphics(BOOL bAdjustWorldMat /*= TRUE*/, HDC hPrintDC /*= NULL*/)
{
	if (!m_pContext)
		return nullptr;

	Graphics* pGr;
	if (!hPrintDC)
	{
		pGr = Graphics::FromHWND(m_pContext->m_hWnd);
	}
	else
	{
		pGr = Graphics::FromHDC(hPrintDC);
	}

	m_pContext->CreateLogicalDC(pGr);
	if (!bAdjustWorldMat)
	{
		Matrix mat(1, 0, 0, -1, 0, 0);
		pGr->SetTransform(&mat);
	}

	return pGr;
}

PointF CWorld::DPtoLP(CPoint pt, Graphics* pGr /*= nullptr*/)
{
	if (!pGr)
	{
		pGr = GetGraphics();
	}

	PointF gdpt(pt.x, pt.y);
	if (pGr)
	{
		pGr->TransformPoints(CoordinateSpaceWorld, CoordinateSpaceDevice, &gdpt, 1);
	}

	return gdpt;
}

RectF CWorld::DPtoLP(CRect rc, Graphics* pGr /*= nullptr*/)
{
	if (!pGr)
	{
		pGr = GetGraphics();
	}

	PointF pt1(rc.left, rc.top);
	PointF pt2(rc.right, rc.bottom);

	if (pGr)
	{
		pGr->TransformPoints(CoordinateSpaceWorld, CoordinateSpaceDevice, &pt1, 1);
		pGr->TransformPoints(CoordinateSpaceWorld, CoordinateSpaceDevice, &pt2, 1);
	}

	return RectF(min(pt1.X, pt2.X), min(pt1.Y, pt2.Y),
		fabsf(pt1.X - pt2.X), fabsf(pt1.Y - pt2.Y));
}

CPoint CWorld::LPtoDP(PointF pt, Graphics* pGr /*= nullptr*/)
{
	if (!pGr)
	{
		pGr = GetGraphics();
	}

	PointF gdpt = pt;
	if (pGr)
		pGr->TransformPoints(CoordinateSpaceDevice, CoordinateSpaceWorld, &gdpt, 1);

	return CPoint((LONG)gdpt.X, (LONG)gdpt.Y);
}

CRect CWorld::LPtoDP(RectF rc, Graphics* pGr /*= nullptr*/)
{
	if (!pGr)
	{
		pGr = GetGraphics();
	}

	PointF pt1(rc.GetLeft(), rc.GetTop());
	PointF pt2(rc.GetRight(), rc.GetBottom());

	if (pGr)
	{
		pGr->TransformPoints(CoordinateSpaceDevice, CoordinateSpaceWorld, &pt1, 1);
		pGr->TransformPoints(CoordinateSpaceDevice, CoordinateSpaceWorld, &pt2, 1);
	}
	CRect rcArea((LONG)pt1.X, (LONG)pt1.Y, (LONG)pt2.X, (LONG)pt2.Y);
	rcArea.NormalizeRect();
	return rcArea;
}

CCadContext* CWorld::SetCadContext(CCadContext* p)
{
	CCadContext* pTemp = m_pContext;
	m_pContext = p;
	return pTemp;
}