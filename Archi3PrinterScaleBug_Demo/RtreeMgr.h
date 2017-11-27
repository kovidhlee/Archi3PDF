#pragma once

class CBase;
class CRtreeMgr
{
public:
	CRtreeMgr();
	virtual ~CRtreeMgr();

public:
	void GetNode(__out std::list<CBase*>* pResult);
	void DrawRtree(Graphics* pDC, RectF rcArea, BOOL bBoundBox);
};
