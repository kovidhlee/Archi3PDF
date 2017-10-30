// DxfMgr.h: interface for the CDxfMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DXFMGR_H__6EB4838B_4B54_4D7E_A5FB_407734CD5F0A__INCLUDED_)
#define AFX_DXFMGR_H__6EB4838B_4B54_4D7E_A5FB_407734CD5F0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGroup;
class CBase;

typedef struct tagBLOCK         // block 구조체.
{
	char	ID[256];
	char	LayerID[256];
	DWORD	pos;
	COLORREF color;
	int		flag;
	double	x;
	double	y;
	vector<CBase*> entity;
} DXF_BLOCK;

typedef struct tagPBLOCK         // block 의 offset값이나.. 좌표값등을 가지는 구조체.
{
	COLORREF		color;
	double	bx, by;
	double	mx, my;
	double	fx, fy;
	int		cx, cy;
	double	sx, sy;
	float   angle;
} DXF_PBLOCK;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct tagSTYLE
{
	char	ID[256];
	double	Height;
	double	Wfactor;
	double	slope;
	int		o_flag;
	int     std_Flag;
	char    szFont[256];
} DXF_STYLE;

typedef struct tagLTYPE
{
	char	ID[256];
	char    Descriptive[256];
	DashStyle Kind;
	int     KindNum;
	char    m_flag[30];
} DXF_LTYPE;

typedef struct tagDIMSTYLE
{
	char	ID[256];
	int		StandardFlags;
	int		HeadColor;
	double	ExtensionlineSize;
	int		LineColor;
	double	DimlineSize;
	double	Offset;
	char	Arrow1[512];
	char	Arrow2[512];
	double	ArrowSize;
	char	TextStyle[512];
	DWORD	hTextStyle;
	int		TextColor;
	double	TextHeight;
	int		Vtp;
	double	OffsetLine;
} DXF_DIMSTYLE;

typedef struct tagLAYER
{
	char	     ID[256];
	char		 szLTypeID[256];
	COLORREF	 color;
	int		     line_type;	// solid, dash, dot, dash_dot
	BOOL	     onoff;		// 0 : ON, 1 : OFF
	int			 std_Flag;
} DXF_LAYER;

typedef struct tagDXFINSERT
{
	char		szLayerID[256];
	char		szGroupID[256];
	char		szParent[256];
	float		fX;
	float		fY;
	float		fAngle;
	float		fFactorX;
	float		fFactorY;
	DXF_BLOCK*	pBlock;
} DXF_INSERT;

class CLayer;
class CAttribute;

int	GetDxfColorIndex(COLORREF clr);

class CDxfMgr
{
public:
	BOOL DxfFileOpen(CString filePath);
	CDxfMgr();
	virtual ~CDxfMgr();
private:
	CStdioFile m_sf;
	CString m_CurrentFilePath;

public:
	CGroup* GetGroup(CString strGroupName);
	void GetLayer(CArray<KVDclass_layer, KVDclass_layer>* pArr);
	void SetCreateLayer(BOOL bFlag) { m_bCreateLayer = bFlag; }
	int GetStream(CStdioFile &sf, TCHAR *buf);
	void DxfFileSave(LPCSTR filename);
	void ProcInsert();
	BOOL SectionEntity();
	BOOL SectionTables();
	BOOL SectionHeader();
	void DeleteMemory();
	CGroup* DxfFileLoad(BOOL bInsertWorkSP = TRUE);
	void LoadSTYLE(CStdioFile& sf);
	void LoadLAYER(CStdioFile& sf);
	void LoadLTYPE(CStdioFile& sf);
	BOOL LoadSectionBlock();
	BOOL LoadInsert();
	BOOL LoadDimension();

	CLayer* GetLayer(CString strID);
	BOOL GetLType(CString strID, CAttribute& att);
	BOOL GetStyle(CString strID, CAttribute& att);

	list<DXF_LTYPE> m_listLType;
	list<DXF_LAYER> m_listLayer;
	list<DXF_STYLE> m_listStyle;
	list<DXF_INSERT> m_listInsert;

	list<CLayer*> m_listlay;
	list<CGroup*> m_listGroup;
	CGroup* m_pCurGroup;

	int m_Hex, m_BlockCount;

	int	 m_lcount, m_scount, m_bcount, m_lycount, offsetX, offsetY;
	double	m_min_x, m_min_y, m_max_x, m_max_y, m_tw, m_th, m_TW, m_TH, m_f;
	double m_dBottomOffset, m_dLinesize, m_dTopOffset, m_dArrowSize, m_dTextSize;
	BOOL m_bCreateLayer;

	CLayer* m_pSpecial;
};                                           // 포인터를 저장한다. 평면데이터 회전시마다 새로운 위치가 되므로
											 // 이 데이터를 보관하고 있다가 그때 그때 사용해야함..

#endif // !defined(AFX_DXFMGR_H__6EB4838B_4B54_4D7E_A5FB_407734CD5F0A__INCLUDED_)
