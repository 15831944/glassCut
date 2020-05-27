// GrPath.h: interface for the CGrPath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRPATH_H__2FD3CA75_1494_4773_A3CE_C8D2E83B793B__INCLUDED_)
#define AFX_GRPATH_H__2FD3CA75_1494_4773_A3CE_C8D2E83B793B__INCLUDED_

#include "GrMath.h"
#include "RoundAngle.h"
#include "GrEllipse.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ELLIPSE_RESOLUTION		(MATH_PI/100.0f)

enum graph_node_type
{
	GNT_SHARP_ANGLE=0,
	GNT_ROUND_ANGLE,
	GNT_INDEPENDENT_CIRCLE,
	GNT_ELLIPSE,
};

typedef struct tagGraphNode
{
	UINT nNodeType;		//enum graph_node_type
	BOOL bIsCloseNode;
	BOOL bIsSplitPoint;		//是否是分割线的端点
	CGrPoint grptSharp;
	CRoundAngle *pRoundAngle;	//当nNodeType==GNT_ROUND_ANGLE时有效
	CGrEllipse  *pEllipse;		//当nNodeType==GNT_ELLIPSE时有效
	BOOL   bAnticlockwise;		//圆弧或椭圆弧的方向
	double fMinWidth;
	double fMinHeight;
} GR_NODE;

typedef struct tagGraphClip
{
	double X1;
	double Y1;
	double X2;
	double Y2;
} GR_CLIP;

typedef struct tagGraphDimension
{
	UINT nMarkType;
	double fMarkDistance;
	CGrPoint pt1;
	CGrPoint pt2;
	CGrPoint ptC0;
	char szMark[16];
} GR_DIMENSION;

class CGrPath  
{
public:
	void GetDimensionsRect(GR_RECT &rcDimensions);
	void GetPathRect(GR_RECT &rcPath);
	void GetGraphRect(GR_RECT &rcGraph);
	BOOL AddSplitCircle(const CGrArc &arc, BOOL bClockWiseDrawing=TRUE);
	BOOL AddSplitNode(const CGrPoint &point);
	BOOL AddEllipseNode(CGrEllipse &grEllipse, BOOL bClockWiseDrawing=TRUE);
	static void RetrieveDimensionPos(CGrPoint &oPt1, CGrPoint &oPt2, const GR_DIMENSION &iDimension);
	BOOL DimensionAppendA(const CGrPoint &ptC0, const CGrPoint &ptBgn, const CGrPoint &ptEnd, LPCTSTR lpszMark, BOOL bGreaterArc=FALSE);
	BOOL DimensionAppendR(const CGrPoint &ptLineBgn, const CGrPoint &ptLineEnd, LPCTSTR lpszMark, double fMarkDistance=0);
	BOOL DimensionAppendR(const CGrPoint &ptCO, double radius, double arc, LPCTSTR lpszMark, double fMarkDistance=0);
	BOOL AddIndependentCircleNode(CGrArc &Arc);
	BOOL AddRoundAngleNode(const CGrPoint &ptVertex, const CGrArc &Arc, BOOL bClockWiseDrawing=TRUE);
	BOOL AddArcNode(const CGrArc &Arc, BOOL bClockWiseDrawing=TRUE);
	BOOL AddSharpNodes(const CGrPoint *arrPoints, UINT nCount);
	BOOL DimensionAppendD(const CGrPoint &ptLineBgn, const CGrPoint &ptLineEnd, LPCTSTR lpszMark, double fMarkDistance=16);
	BOOL DimensionAppendD(double fxBgn, double fyBgn, double fxEnd, double fyEnd, LPCTSTR lpszMark, double fMarkDistance=16);
	BOOL DimensionAppendD(const GR_LINE &line, LPCTSTR lpszMark, double fMarkDistance=16);
	void Offset(double fx, double fy);
	const char* MakeGCode();
	void PaintTo(CDC *pDC, const LPCRECT lpRect, const COLORREF color);
	BOOL DimensionAppend(const GR_DIMENSION &dimension);
	BOOL GetClip(GR_CLIP &buff);
	void SetClip(const GR_CLIP &clip);
	BOOL NodeAppend(const GR_NODE &node);
	void Reset();
	void Scale(double fScale);
	enum { MAX_NODEs = 256 };
	CGrPath();
	virtual ~CGrPath();
	//生成套料用的格式
	CString MakeNestData();
	GR_RECT m_rcClip;
	BOOL m_bG00;//标记图形的start;

protected:
	void CheckClipRect(UINT nNodeIndex);
	char *m_pGCodeBuff;
	void DrawDimension(CDC *pDC, const LPCRECT lpRect);
	UINT m_nDimentsionCount;
	GR_DIMENSION m_dimensions[MAX_NODEs];
	void FitClipRect(const double fXMax, const double fYMax);
	void UpdateClipRect();
	GR_CLIP m_clip;
	GR_NODE m_nodes[MAX_NODEs];
	UINT m_nNodeCount;
};

#endif // !defined(AFX_GRPATH_H__2FD3CA75_1494_4773_A3CE_C8D2E83B793B__INCLUDED_)
