#pragma once
class CAttributeMgr;

class CBase
{
private:
	Matrix m_Matrix;

	BOOL m_bFixScale;
	Matrix m_OldMatrix;
	float m_fOldScale;
	float m_fFixScale;

public:
	CBase();
	virtual ~CBase();

public:
	virtual BOOL DrawBefore(Graphics* pDC, CAttributeMgr* pAttMgr);
	virtual BOOL DrawAfter(Graphics* pDC, CAttributeMgr* pAttMgr);
	virtual BOOL DrawEntity(Graphics* pDC, CAttributeMgr* pAttMgr, BOOL bBoundBox);
	virtual BOOL Draw(Graphics* pDC, CAttributeMgr* pAttMgr, BOOL bBoundBox = FALSE);

	virtual void Draw(CDC* pDC, CAttributeMgr* pAttMgr) {}
};
