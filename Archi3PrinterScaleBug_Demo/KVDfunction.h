#pragma once

#if !defined(_KVDFUNCTION_H_)
#define _KVDFUNCTION_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _GDIPLUS_H
#include <gdiplus.h>
using namespace Gdiplus;
#endif

#include <VECTOR>
using namespace std;

#include <AFXTEMPL.H>

#define KVD_DATA_VERSION	102

#define KVDTG_1		0x0001
#define KVDTG_2		0x0002
#define KVDTG_3		0x0004
#define KVDTG_4		0x0008
#define KVDTG_5		0x0010
#define KVDTG_6		0x0020

#define KVDATT_PENCLR 0x0001
#define KVDATT_BRUSHCLR 0x0002
#define KVDATT_LINE	0x0004
#define KVDATT_LINEWIDTH 0x0008
#define KVDATT_FONT 0x0010
#define KVDATT_FONTSIZE 0x0020
#define KVDATT_FONTSTYLE 0x0040

#define KVDET_BASE 0x0001
#define KVDET_GROUP 0x0002
#define KVDET_ENTITY 0x0004
#define KVDET_LINEENTITY 0x0008
#define KVDET_POLYENT 0x0010
#define KVDET_TEXT	0x0020
#define KVDET_SOLIDENT 0x0040
#define KVDET_DIMENSION 0x0080
#define KVDET_POINTENT 0x0100
#define KVDET_CIRCLEENT 0x0200
#define KVDET_ARCENT 0x0400
#define KVDET_IMAGEENT 0x0800
#define KVDET_CADENT 0x1000
#define KVDET_BEZIERENT 0x2000

enum KVD_RENDERMODE
{
	KVDRM_LOWQUALITY = 0,
	KVDRM_NORMAL = 1,
	KVDRM_HIGHQUALITY = 2,
	KVDRM_BOUNDBOX = 3
};

enum KVD_STATUS {
	KVDsta_ok = 0,
	KVDsta_GDIPlusInitFail = 1,
	KVDsta_differenttype = 2,
	KVDsta_cadcontextisnull = 3,
	KVDsta_GraphicsObjectFail = 4,
	KVDsta_mainworldisnull = 5,
	KVDsta_false = 6,
	KVDsta_notcollisionentity = 7,
	KVDsta_collisionoverflow = 8,
	KVDsta_snapduplication = 9,
	KVDsta_fileopenfail = 10,
	KVDsta_StartDocFailed = 11,
	KVDsta_StartPageFailed = 12,
};

enum KVD_MSTYPE {
	KVDMS_MAIN = 0,
	KVDMS_WORK = 1,
	KVDMS_SUB = 2,
	KVDMS_ALL = 3
};

enum KVD_SNAPTYPE {
	KVDST_NONE = 0,
	KVDST_NORMAL = 0x0001,
	KVDST_BOUND = 0x0002,
	KVDST_CROSS = 0x0004,
	KVDST_NEAR = 0x0008,
	KVDST_PERPEND = 0x0016,
	KVDST_EXTENSION = 0x0032,
	KVDST_ANGLE = 0x0064,
};

enum KVD_GRIDTYPE {
	KVDGT_NORMAL = 0,
	KVDGT_CENTER = 1,
	KVDGT_PAPER = 2,
	KVDGT_ROD = 3
};

enum KVD_DIMTYPE {
	KVDDT_ORDINATE = 0,
	KVDDT_ALIGNED = 1,
	KVDDT_CIRCLE = 2,
	KVDDT_RADIAN = 3
};

enum KVD_NODETYPE {
	KVDNT_NONE = 0,
	KVDNT_BASE = 1,
	KVDNT_GROUP = 2,
	KVDNT_ENTITY = 3,
	KVDNT_LINE = 4,
	KVDNT_POLY = 5,
	KVDNT_CIRCLE = 6,
	KVDNT_ARC = 7,
	KVDNT_TEXT = 8,
	KVDNT_POINT = 9,
	KVDNT_IMAGE = 10,
	KVDNT_SOLID = 11,
	KVDNT_DIMENSION = 12,
	KVDNT_BEZIER = 13
};

struct PRINTCONTEXT {
	PRINTCONTEXT() {
		hPrintDC = NULL;
	}
	HDC hPrintDC;
	CRect rcPaper;
	PointF ptGap;			// World Axis
	CSize  PrintSize;		// pixel
	SizeF DisplayDPI;
	SizeF PrintDPI;

	Unit enPrintUnit;
	float fDtoInchRate;		// 디스플레이 Unit에서 인치로 변경
	float fInchtoPRate;		// 인치에서 Print Unit으로 변경
							// 디스플레이 Unit가 UnitMillimeter 이고 Print Unit이 UnitPoint일 경우
							// fDtoInchRate = 25.4, fInchtoPRate = 72;
};

struct  CADCONTEXT {
	HWND hWnd;
	Unit enWorldUnit;	// GDI+ enum Unit
	CPoint	ptViewCenter;		// Pixel Unit View Center
	float	fZoomMax;
	float	fZoomMin;
	float	fBasicZoomRate;
	KVD_RENDERMODE enRenderMode;
	Matrix	WorldMat;
	PRINTCONTEXT printCon;
};

struct KVD_ATTRIBUTE {
	KVD_ATTRIBUTE() {
		m_wTrans = 255;
		m_nLineStyle = DashStyleSolid;
		for (int p = 0; p < 8; p++)
			m_DashPattern[p] = 0.f;
		m_DashPatCount = 0;
		m_fLineWidth = 0.f;
		m_fFontSize = 0.f;
		m_nFontStyle = FontStyleRegular;
		ZeroMemory(m_wFont, sizeof(WCHAR)*LF_FACESIZE);
		m_dwFlag = 0;
	}
	COLORREF m_clrPen;
	COLORREF m_clrBrush;
	WORD	m_wTrans;

	DashStyle m_nLineStyle;
	REAL m_DashPattern[8];		//DashStyleCustom 일 경우 사용
	int  m_DashPatCount;

	float	  m_fLineWidth;
	float	m_fFontSize;

	FontStyle m_nFontStyle;
	WCHAR	m_wFont[LF_FACESIZE];
	DWORD	m_dwFlag;
};

struct KVD_GRID_LINE {
	KVD_GRID_LINE() {
		m_LineStyle = DashStyleSolid;
	}
	Color m_clrLine;
	DashStyle m_LineStyle;
	UINT	m_nUnitGap;
};

struct KVD_GRID {
	KVD_GRID() {
		m_enType = KVDGT_NORMAL;
		m_nSnap = 50;
		m_nMargin = 0;
		m_clrBG.SetFromCOLORREF(RGB(255, 255, 255));
		m_clrMainLine.SetFromCOLORREF(RGB(0, 0, 0));
		m_MLStyle = DashStyleSolid;
		m_stLine[0].m_clrLine.SetFromCOLORREF(RGB(240, 240, 240));
		m_stLine[0].m_nUnitGap = 10;
		m_stLine[1].m_clrLine.SetFromCOLORREF(RGB(220, 220, 220));
		m_stLine[1].m_nUnitGap = 50;
		m_stLine[2].m_clrLine.SetFromCOLORREF(RGB(120, 120, 120));
		m_stLine[2].m_nUnitGap = 100;
		m_bDrawFlag = TRUE;
		m_nLineIndex = 3;
		m_bGridIsSnap = FALSE;
	}
	KVD_GRIDTYPE m_enType;
	Color m_clrBG;
	Color m_clrMainLine;
	DashStyle m_MLStyle;
	KVD_GRID_LINE m_stLine[10];
	UINT	m_nLineIndex;
	BOOL m_bDrawFlag;

	UINT m_nSnap;
	UINT m_nMargin;

	BOOL m_bGridIsSnap;
};

struct KVD_DIMENSION {
	float fTopHeigh;
	float fGap;
	KVD_ATTRIBUTE kvdAtt;
	KVD_DIMTYPE enType;
	PointF ptSolid[6];
	int nSolidIndex;
	BOOL	bXAxis;
};

typedef void (CALLBACK* KVD_LPDRAW)(Graphics*);
typedef void* KVDclass_context;
typedef void* KVDclass_world;
typedef void* KVDclass_group;
typedef void* KVDclass_entity;
typedef void* KVDclass_layer;
typedef void* KVDclass_base;
typedef void* KVDclass_graphic;
typedef void* KVDclass_snap;

typedef DWORD KVDtype_TransGroup;

#define _KVPOINT3D
class KVPoint3F
{
public:
	KVPoint3F() {}
	KVPoint3F(float x, float y, float z) { X = x; Y = y; Z = z; }
	BOOL operator==(IN const KVPoint3F& point) const
	{
		return (X == point.X) && (Y == point.Y) && (Z == point.Z);
	}

	REAL X;
	REAL Y;
	REAL Z;
};

typedef struct _PolyMeshData
{
	CString strName;
	std::vector<KVPoint3F> Vetices;
	std::vector<unsigned short> Indies;
	std::vector<BYTE> lineFlags;
}POLYMESHDATA;

enum DWG3DTYPE {
	_3DFACE,
	_3DLINE
};
typedef struct _dwg3DData
{
	_dwg3DData()
	{
		pLayer = NULL;
		nType = _3DFACE;
	}
	KVDclass_layer pLayer;
	DWG3DTYPE nType;
	KVPoint3F ptCenter;
	KVPoint3F rotate;
	KVPoint3F scale;
	std::vector<POLYMESHDATA*> DataArray;
	//Added by heyho dwg
	CString   szDataname;
	KVPoint3F ptSize;
}DWG3DDATA;

#endif //_KVDFUNCTION_H_