#include "stdafx.h"
#include "Base.h"

CBase::CBase()
	: m_bFixScale(FALSE)
	, m_fFixScale(0.0f)
{
}

CBase::~CBase()
{
}

BOOL CBase::DrawBefore(Graphics* pDC, CAttributeMgr* pAttMgr)
{
	pDC->GetTransform(&m_OldMatrix);
	if (m_bFixScale)
	{
		m_fOldScale = pDC->GetPageScale();
		pDC->SetPageScale(m_fFixScale);
		Matrix mat;
		mat.SetElements(1, 0, 0, -1, 0, 0);
		pDC->SetTransform(&mat);
	}
	pDC->MultiplyTransform(&m_Matrix);
#ifdef _DEBUG
	REAL el[6];
	m_Matrix.GetElements(el);
#endif

	return TRUE;
}

BOOL CBase::DrawAfter(Graphics* pDC, CAttributeMgr* pAttMgr)
{
	pDC->SetTransform(&m_OldMatrix);
	if (m_bFixScale)
	{
		pDC->SetPageScale(m_fOldScale);
	}

	return TRUE;
}

BOOL CBase::DrawEntity(Graphics* pDC, CAttributeMgr* pAttMgr, BOOL bBoundBox)
{
	return TRUE;
}

BOOL CBase::Draw(Graphics* pDC, CAttributeMgr* pAttMgr, BOOL bBoundBox /*= FALSE*/)
{
	if (!DrawBefore(pDC, pAttMgr))
		return FALSE;
	if (!DrawEntity(pDC, pAttMgr, bBoundBox))
		return FALSE;
	if (!DrawAfter(pDC, pAttMgr))
		return FALSE;

	return TRUE;
}