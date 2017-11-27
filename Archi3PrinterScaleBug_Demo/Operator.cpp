#include "stdafx.h"
#include "Operator.h"
#include "CadContext.h"
#include "TempletNode.h"
#include "Archi3PrinterScaleBug_Demo.h"
#include "Archi3PrinterScaleBug_DemoDoc.h"
#include "MainFrm.h"
#include "KVDfunction.h"

/*
	Imitate CCadPrintOperator class in Archi3 Project
*/
COperator::COperator()
	: m_pCad(new CCadContext())
	, m_pTempletNode(new CTempletNode())
	, m_fZoomStep(20.0f)
	, m_bPan(false)
{
}

COperator::~COperator()
{
}

void COperator::InitWindow(HWND hWnd, CPoint point)
{
	auto pApp = (CArchi3PrinterScaleBug_DemoApp*)AfxGetApp();
	auto pDoc = (CArchi3PrinterScaleBug_DemoDoc*)GetCurDocument();
	CADCONTEXT stCad;
	{
		stCad.enWorldUnit = UnitMillimeter;
		stCad.fBasicZoomRate = 0.1f;
		stCad.hWnd = hWnd;
		stCad.ptViewCenter.x = point.x;
		stCad.ptViewCenter.y = point.y;
	}

	m_pCad->SetCadContext(&stCad);
	pApp->m_kvdWorld = pDoc->KVDworld_create(m_pCad.get());
}

void COperator::OnMouseWheel(short zDelta, CPoint point)
{
	if (zDelta > 0)
	{
		m_pCad->ZoomStep(point, m_fZoomStep, TRUE);
	}
	else
	{
		m_pCad->ZoomStep(point, m_fZoomStep, FALSE);
	}
}

void COperator::OnMouseMove(CPoint point)
{
	if (m_bPan)
	{
		CPoint ptMove = point - m_ptOldMouse;
		m_pCad->TranslateCenter(ptMove.x, ptMove.y, TRUE);
		m_ptOldMouse = point;
	}
}

void COperator::OnMButtonDown(CPoint point)
{
	m_bPan = true;
	m_ptOldMouse = point;
}

void COperator::OnMButtonUp(CPoint point)
{
	m_bPan = false;
}

void COperator::Render(BOOL bPrint, CDC* pDC)
{
	m_pTempletNode->Render(bPrint, pDC);
}