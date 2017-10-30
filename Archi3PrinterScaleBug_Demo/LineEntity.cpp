#include "stdafx.h"
#include "LineEntity.h"

CLineEntity::CLineEntity()
	: m_tgStart(0)
	, m_tgEnd(0)
{
}

CLineEntity::~CLineEntity()
{
}

void CLineEntity::SetPoint(PointF ptStart, PointF ptEnd)
{
	m_ptStart = ptStart;
	m_ptEnd = ptEnd;
}

BOOL CLineEntity::DrawEntity(Graphics* pDC, CAttributeMgr* pAttMgr, BOOL bBoundBox)
{
	Pen gdPen(Color(255, 0, 0), 5);
	//������ ����� �����Ѵ�.(������)
	gdPen.SetEndCap(LineCapSquare);

	/************************************************************************/
	/* Added by heyho ���� �׷����� ������ ���� ������� ��� ����          */
	/************************************************************************/
	if (!_finite(m_ptStart.X) || !_finite(m_ptStart.Y))
	{
		m_ptStart.X = 0.0;
		m_ptStart.Y = 0.0;
	}
	if (!_finite(m_ptEnd.X) || !_finite(m_ptEnd.Y))
	{
		m_ptEnd.X = 0.0;
		m_ptEnd.Y = 0.0;
	}
	pDC->DrawLine(&gdPen, m_ptStart, m_ptEnd);
	return TRUE;
}

void CLineEntity::Draw(CDC* pDC, CAttributeMgr* pAttMgr)
{
}