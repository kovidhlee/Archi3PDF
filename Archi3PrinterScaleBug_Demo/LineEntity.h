#pragma once
#include "Entity.h"
#include "KVDfunction.h"

class CAttributeMgr;
class CLineEntity : public CEntity
{
public:
	CLineEntity();
	virtual ~CLineEntity();

public:
	void SetPoint(PointF ptStart, PointF ptEnd);

public:
	virtual BOOL DrawEntity(Graphics* pDC, CAttributeMgr* pAttMgr, BOOL bBoundBox);
	virtual void Draw(CDC* pDC, CAttributeMgr* pAttMgr);

protected:
	PointF m_ptStart;
	PointF m_ptEnd;
	KVDtype_TransGroup m_tgStart;
	KVDtype_TransGroup m_tgEnd;
};
