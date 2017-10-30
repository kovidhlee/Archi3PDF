#pragma once
#include "KVDfunction.h"
#include "DxfMgr.h"

class CAttribute : public KVD_ATTRIBUTE
{
public:
	CAttribute(KVD_ATTRIBUTE att);
	CAttribute();
	virtual ~CAttribute();

public:
	BOOL IsUsing(DWORD dwFlag) { return m_dwFlag & dwFlag; }
	CAttribute operator | (CAttribute att);
	void operator =(const KVD_ATTRIBUTE att);
	void operator =(const DXF_LTYPE dxfatt);
	void operator =(const DXF_STYLE dxfatt);
	void SetPenColor(COLORREF clr) { m_clrPen = clr; m_dwFlag |= KVDATT_PENCLR; }
	void SetBrushColor(COLORREF clr) { m_clrBrush = clr; m_dwFlag |= KVDATT_BRUSHCLR; }
	void SetLineStyle(DashStyle ds) { m_nLineStyle = ds; m_dwFlag |= KVDATT_LINE; }
	void SetLineWidth(float fWidth) { m_fLineWidth = fWidth; m_dwFlag |= KVDATT_LINEWIDTH; }
	//	void SetFont(LPWSTR lpwFont) { wcscpy_s(m_wFont, lpwFont); m_dwFlag |= KVDATT_FONT;}
	void SetFont(LPWSTR lpwFont) { wcscpy_s(m_wFont, lpwFont); m_dwFlag |= KVDATT_FONT; }
	void SetFontSize(float fSize) { m_fFontSize = fSize; m_dwFlag |= KVDATT_FONTSIZE; }
	void SetFontStyle(FontStyle fs) { m_nFontStyle = fs; m_dwFlag |= KVDATT_FONTSTYLE; }
	COLORREF GetPenColor() { return m_dwFlag & KVDATT_PENCLR ? m_clrPen : 0; }
	COLORREF GetBrushColor() { return m_dwFlag & KVDATT_BRUSHCLR ? m_clrBrush : 0; }
	DashStyle GetLineStyle() { return m_dwFlag & KVDATT_LINE ? m_nLineStyle : DashStyleSolid; }
	float GetLineWidth() { return m_dwFlag & KVDATT_LINEWIDTH ? m_fLineWidth : 0; }
	LPWSTR GetFont() { return m_dwFlag & KVDATT_FONT ? m_wFont : L"Arial"; }
	float GetFontSize() { return m_dwFlag & KVDATT_FONTSIZE ? m_fFontSize : 10.f; }
	FontStyle GetFontStyle() { return m_dwFlag & KVDATT_FONTSTYLE ? m_nFontStyle : FontStyleRegular; }

	void Adjust(Pen& pen);
	void Adjust(SolidBrush& brush);
};
