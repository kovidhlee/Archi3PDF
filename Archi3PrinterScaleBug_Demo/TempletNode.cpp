#include "stdafx.h"
#include "TempletNode.h"
#include "World.h"
#include "MainFrm.h"
#include "Archi3PrinterScaleBug_DemoDoc.h"
/*
	imitate CTempletNode class in Archi3 Project
*/

CTempletNode::CTempletNode()
{
}

CTempletNode::~CTempletNode()
{
}

void CTempletNode::Render(BOOL bPrint, CDC* pDC)
{
	if (bPrint && pDC)
	{
	}
	else
	{
		RectF rcArea = GetCurClipArea();
		CRect rciArea(rcArea.GetLeft(), rcArea.GetTop(), rcArea.GetRight(), rcArea.GetBottom());
		rcArea = GetCurDocument()->KVDworld_dptolp_rect(nullptr, rciArea);
		GetCurDocument()->KVDworld_draw(bPrint, m_rcClip, FALSE, 0.f);
	}
}

float CTempletNode::GetDisplayDPIWidth(Graphics* pDisplay)
{
	ASSERT(pDisplay);

	return pDisplay->GetDpiX();
}

float CTempletNode::GetDisplayDPIHeight(Graphics* pDisplay)
{
	ASSERT(pDisplay);

	return pDisplay->GetDpiY();
}

float CTempletNode::GetPrintDPIWidth(Graphics* pPrint)
{
	ASSERT(pPrint);

	return pPrint->GetDpiX();
}

float CTempletNode::GetPrintDPIHeight(Graphics* pPrint)
{
	ASSERT(pPrint);

	return pPrint->GetDpiY();
}

int CTempletNode::GetDeviceContextWidth(CDC* pDC)
{
	ASSERT(pDC);

	return pDC->GetDeviceCaps(HORZRES);
}

int CTempletNode::GetDeviceContextHeight(CDC* pDC)
{
	ASSERT(pDC);

	return pDC->GetDeviceCaps(VERTRES);
}

RectF CTempletNode::GetCurClipArea()
{
	return RectF(0, 0, 0, 0);
}