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

	CRect rcClient = m_pContext->GetClientRect(); 	// ���� �������� ũ��.(DP)
	rcClient.NormalizeRect();

	Graphics graph(m_pContext->m_hWnd);

	Bitmap memBit(rcClient.Width(), rcClient.Height(), &graph);
	Graphics memGra(&memBit);

	// Ŭ���� ���� ���� �� LP��� ����, ���������� clear
	if (rcClip.IsEmptyArea())	// �Էµ� Ŭ���� ������ ���� ��� ȭ��ũ��� Ŭ����.
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

	if (!rcClip.IsEmptyArea() && !bDPClip)	// �Էµ� Ŭ���� ������ LP����
	{
		memGra.SetClip(rcClip);
	}

	memGra.GetClipBounds(&rcQueryArea);
	if (!rcClip.IsEmptyArea())
	{
		rcQueryArea.Inflate(-fClipGap, -fClipGap);
		memGra.SetClip(rcQueryArea);	// Ŭ���� ������ �������� �׷����� �ʴ� �͵� ����
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

	// ����Ʈ�� �׷��� ���� ������ ������ ���Ե� ����̴�.
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