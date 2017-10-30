#include "stdafx.h"
#include "Attribute.h"

CAttribute::CAttribute(KVD_ATTRIBUTE att)
{
	m_clrPen = att.m_clrPen;
	m_clrBrush = att.m_clrBrush;
	m_wTrans = att.m_wTrans;
	m_nLineStyle = att.m_nLineStyle;
	memcpy(m_DashPattern, att.m_DashPattern, sizeof(REAL) * 8);
	m_DashPatCount = att.m_DashPatCount;
	m_fLineWidth = att.m_fLineWidth;
	//wcscpy_s(m_wFont,att.m_wFont);
	wcscpy_s(m_wFont, att.m_wFont);
	m_fFontSize = att.m_fFontSize;
	m_nFontStyle = att.m_nFontStyle;
	m_dwFlag = att.m_dwFlag;
}

CAttribute::CAttribute()
{
	m_clrPen = m_clrBrush = 0;
	m_nLineStyle = DashStyleSolid;
}

CAttribute::~CAttribute()
{
}

void CAttribute::operator =(const KVD_ATTRIBUTE att)
{
	m_clrPen = att.m_clrPen;
	m_clrBrush = att.m_clrBrush;
	m_wTrans = att.m_wTrans;
	m_nLineStyle = att.m_nLineStyle;
	memcpy(m_DashPattern, att.m_DashPattern, sizeof(REAL) * 8);
	m_DashPatCount = att.m_DashPatCount;
	m_fLineWidth = att.m_fLineWidth;
	//wcscpy_s(m_wFont,att.m_wFont);
	wcscpy_s(m_wFont, att.m_wFont);
	m_fFontSize = att.m_fFontSize;
	m_nFontStyle = att.m_nFontStyle;
	m_dwFlag = att.m_dwFlag;
}

CAttribute CAttribute::operator | (CAttribute att)
{
	CAttribute temp = *this;

	if (att.m_dwFlag & KVDATT_PENCLR)
		temp.m_clrPen = att.m_clrPen;
	if (att.m_dwFlag & KVDATT_BRUSHCLR)
	{
		temp.m_clrBrush = att.m_clrBrush;
		temp.m_wTrans = att.m_wTrans;
	}
	if (att.m_dwFlag & KVDATT_LINE)
	{
		temp.m_nLineStyle = att.m_nLineStyle;
		memcpy(temp.m_DashPattern, att.m_DashPattern, sizeof(REAL) * 8);
		temp.m_DashPatCount = att.m_DashPatCount;
	}
	if (att.m_dwFlag & KVDATT_LINEWIDTH)
		temp.m_fLineWidth = att.m_fLineWidth;
	if (att.m_dwFlag & KVDATT_FONT)
		//wcscpy_s(temp.m_wFont, att.m_wFont);
		wcscpy_s(temp.m_wFont, att.m_wFont);
	if (att.m_dwFlag & KVDATT_FONTSIZE)
		temp.m_fFontSize = att.m_fFontSize;
	if (att.m_dwFlag & KVDATT_FONTSTYLE)
		temp.m_nFontStyle = att.m_nFontStyle;

	temp.m_dwFlag = m_dwFlag | att.m_dwFlag;
	return temp;
}

void CAttribute::operator =(const DXF_LTYPE dxfatt)
{
	SetLineStyle(dxfatt.Kind);
}

void CAttribute::operator =(const DXF_STYLE dxfatt)
{
	if (strlen(dxfatt.szFont) > 0)
	{
		::AfxA2WHelper(m_wFont, dxfatt.szFont, 100);
		m_dwFlag |= KVDATT_FONT;
	}
	SetFontSize(dxfatt.Height);
}

void CAttribute::Adjust(Pen& pen)
{
	Color gdColor;
	gdColor.SetFromCOLORREF(GetPenColor());
	pen.SetColor(gdColor);
	pen.SetDashStyle(GetLineStyle());
	if (m_DashPatCount > 0 && GetLineStyle() != DashStyleSolid)
		pen.SetDashPattern(m_DashPattern, m_DashPatCount);

	pen.SetWidth(GetLineWidth());
}

void CAttribute::Adjust(SolidBrush& brush)
{
	Color gdColor;
	gdColor.SetFromCOLORREF(GetBrushColor());
	brush.SetColor(gdColor);
}

//int	CAttribute::GetByteData(BYTE* pData, int nCurIndex, int nMaxSize)
//{
//	KVD_MEMCPY(pData[nCurIndex], m_clrPen, COLORREF, nCurIndex);
//	KVD_MEMCPY(pData[nCurIndex], m_clrBrush, COLORREF, nCurIndex);
//	KVD_MEMCPY(pData[nCurIndex], m_wTrans, WORD, nCurIndex);
//
//	KVD_MEMCPY(pData[nCurIndex], m_nLineStyle, DashStyle, nCurIndex);
//	KVD_MEMCPYARR(pData[nCurIndex], m_DashPattern, REAL, 8, nCurIndex);
//
//	KVD_MEMCPY(pData[nCurIndex], m_DashPatCount, int, nCurIndex);
//	KVD_MEMCPY(pData[nCurIndex], m_fLineWidth, float, nCurIndex);
//	KVD_MEMCPY(pData[nCurIndex], m_fFontSize, float, nCurIndex);
//	KVD_MEMCPY(pData[nCurIndex], m_nFontStyle, FontStyle, nCurIndex);
//	KVD_MEMCPYARR(pData[nCurIndex], m_wFont, WCHAR, LF_FACESIZE, nCurIndex);
//	KVD_MEMCPY(pData[nCurIndex], m_dwFlag, DWORD, nCurIndex);
//
//	return nCurIndex;
//}