#include "stdafx.h"
#include "RtreeMgr.h"
#include "Base.h"
#include "MainFrm.h"
#include "Archi3PrinterScaleBug_DemoDoc.h"
#include <list>
#include <algorithm>
#include <iterator>

CRtreeMgr::CRtreeMgr()
{
}

CRtreeMgr::~CRtreeMgr()
{
}

void CRtreeMgr::GetNode(__out std::list<CBase*>* pResult)
{
	ASSERT(pResult);

	auto pDoc = (CArchi3PrinterScaleBug_DemoDoc*)GetCurDocument();
	if (!pDoc)
	{
		__debugbreak();
		return;
	}

	auto mainList = pDoc->GetMainList();
	std::copy(mainList.begin(), mainList.end(),
		std::back_inserter(*pResult));
}

void CRtreeMgr::DrawRtree(Graphics* pDC, RectF rcArea, BOOL bBoundBox)
{
	std::list<CBase*> bases;
	GetNode(&bases);

	for (auto iter = bases.begin(); iter != bases.end(); ++iter)
	{
		((CBase*)*iter)->Draw(pDC, nullptr);
	}
}