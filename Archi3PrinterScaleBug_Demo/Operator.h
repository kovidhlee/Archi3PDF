#pragma once

#include <memory>

class CCadContext;
class CTempletNode;

class COperator
{
private:
	std::shared_ptr<CCadContext> m_pCad;
	std::shared_ptr<CTempletNode> m_pTempletNode;
	float m_fZoomStep;
	bool m_bPan;
	CPoint m_ptOldMouse;

public:
	COperator();
	virtual ~COperator();

public:
	void InitWindow(HWND hWnd, CPoint point);
	void OnMouseWheel(short zDelta, CPoint point);
	void OnMouseMove(CPoint point);
	void OnMButtonDown(CPoint point);
	void OnMButtonUp(CPoint point);
	void Render(BOOL bPrint, CDC* pDC);
};
