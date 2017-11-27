#pragma once
#include <memory>
#include "RtreeMgr.h"

class CCadContext;

class CWorld
{
private:
	CCadContext* m_pContext;
	CRtreeMgr m_Rtree;
public:
	CWorld();
	virtual ~CWorld();

public:
	void Draw(RectF rcClip = RectF(0, 0, 0, 0), BOOL bDPClip = FALSE, float fClipGap = 10.f);
	void Print(RectF rcClip = RectF(0, 0, 0, 0), BOOL bDPClip = FALSE);

	inline Graphics* GetGraphics(BOOL bAdjustWorldMat = TRUE, HDC hPrintDC = NULL);
	inline PointF DPtoLP(CPoint pt, Graphics* pGr = nullptr);
	inline CPoint LPtoDP(PointF pt, Graphics* pGr = nullptr);
	inline RectF DPtoLP(CRect rc, Graphics* pGr = nullptr);
	inline CRect LPtoDP(RectF rc, Graphics* pGr = nullptr);

	CCadContext* SetCadContext(CCadContext* p);
};
