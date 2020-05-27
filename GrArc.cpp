// GrArc.cpp: implementation of the CGrArc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bender.h"
#include "GrArc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGrArc::CGrArc()
{
	Clean();
}

CGrArc::~CGrArc()
{
	Clean();
}

void CGrArc::Clean()
{
	m_fArc = 0.0f;
	m_fRadius = 0.0f;
	m_ptC0.Set(0,0);
	m_ptArcBgn.Set(0,0);
	m_ptArcEnd.Set(0,0);
	m_bClosed=FALSE;
}

//圆弧整体坐标缩放
void CGrArc::Scale(double fScale)
{
	m_fRadius *= fScale;
	m_ptC0.Scale(fScale);
	m_ptArcBgn.Scale(fScale);
	m_ptArcEnd.Scale(fScale);
}

//圆弧整体坐标偏移
void CGrArc::Offset(double fx, double fy)
{
	m_ptC0.Offset(fx, fy);
	m_ptArcBgn.Offset(fx, fy);
	m_ptArcEnd.Offset(fx, fy);
}


//初始化圆角圆弧
//fRadius:		圆弧的半径
//ptVertex:		被圆弧切割的角的顶点坐标
//ptBgn:		顺时针方向，圆弧的起点坐标
//ptEnd:		顺时针方向，圆弧的终点坐标
BOOL CGrArc::InitRoundCornerArc(double fRadius, const CGrPoint &ptVertex, const CGrPoint &ptBgn, const CGrPoint &ptEnd)
{
	double fOppositeSide, fAdjacentSide1, fAdjacentSide2;
	double fTemp, fVertexArc;
	CGrPoint ptTemp;
	
	fOppositeSide = GetDistanceF(ptBgn, ptEnd);
	fAdjacentSide1 = GetDistanceF(ptVertex, ptBgn);
	fAdjacentSide2 = GetDistanceF(ptVertex, ptEnd);
	if(fRadius>fAdjacentSide1 || fRadius>fAdjacentSide2)
		return FALSE;
	
	fVertexArc = RetrieveAngleOfTriangle(fOppositeSide, fAdjacentSide1, fAdjacentSide2);
	
	fTemp = fRadius/tan(fVertexArc/2);
	
	RetrievePointOfLine(m_ptArcBgn, ptVertex, ptBgn, fTemp);
	RetrievePointOfLine(m_ptArcEnd, ptVertex, ptEnd, fTemp);
	
	fTemp = GetDistanceF(m_ptArcBgn, m_ptArcEnd)/2;
	RetrievePointOfLine(ptTemp, m_ptArcBgn, m_ptArcEnd, fTemp);
	
	fTemp = fRadius/sin(fVertexArc/2);
	RetrievePointOfLine(m_ptC0, ptVertex, ptTemp, fTemp);
	
	m_fRadius = fRadius;
	m_fArc = (MATH_PI-fVertexArc);
	m_bClosed=FALSE;
	return TRUE;
}


//初始化圆弧
//fRadius:		圆弧的半径
//ptC0:			圆弧的圆心
//ptArcBgn:		顺时针方向，圆弧的起点坐标
//ptArcEnd:		顺时针方向，圆弧的终点坐标
BOOL CGrArc::InitArc(double fRadius, const CGrPoint &ptC0, const CGrPoint &ptArcBgn, const CGrPoint &ptArcEnd, BOOL bGreaterArc/*=FALSE*/)
{
	double fd;

	m_fRadius = fRadius;
	m_ptC0 = ptC0;
	m_ptArcBgn = ptArcBgn;
	m_ptArcEnd = ptArcEnd;

	fd = GetDistanceF(m_ptArcBgn, m_ptArcEnd);
	m_fArc = RetrieveAngleOfTriangle(fd, m_fRadius, m_fRadius);
	m_bClosed=FALSE;
	if(bGreaterArc)
	{
		if(fd>0.0001f)
		{
			m_fArc = (MATH_PI*2)-m_fArc;
		}
		else
		{
			m_ptArcEnd = m_ptArcBgn;
			m_fArc = MATH_PI*2;
			m_bClosed=TRUE;
		}
	}
	return TRUE;
}


//初始化圆弧
//ptC0:			圆弧的圆心
//ptArcBgn:		顺时针方向，圆弧的起点坐标
//ptArcEnd:		顺时针方向，圆弧的终点坐标
BOOL CGrArc::InitArcA(const CGrPoint &ptC0, const CGrPoint &ptArcBgn, const CGrPoint &ptArcEnd, BOOL bGreaterArc)
{
	double r;
	r = GetDistanceF(ptC0, ptArcBgn);
	return InitArc(r, ptC0, ptArcBgn, ptArcEnd, bGreaterArc);
}


//初始化圆
//fRadius:		圆的半径
//ptC0:			圆的圆心
BOOL CGrArc::InitCircle(double fRadius, CGrPoint &ptC0)
{
	CGrPoint ptTemp;
	ptTemp = ptC0;
	ptTemp.Offset(-fRadius, 0);
	return InitArc(fRadius, ptC0, ptTemp, ptTemp, TRUE);
}


BOOL CGrArc::IsClosed()
{
	return m_bClosed;
}



//将圆弧画到由pDC指定的DC上
//bClockWiseDrawing:	TRUE-->顺时针画，否则逆时针画；
//fDeltaArc:			角度分辨率，值越小画出的圆弧越精细；
void CGrArc::PaintTo(CDC *pDC, BOOL bClockWiseDrawing/*=TRUE*/, double fDeltaArc/*=(MATH_PI/10000.0f)*/)
{
	GR_LINE line;
	CGrPoint ptMoving;
	CGrPoint *pPtBgn=NULL, *pPtEnd=NULL;
	double fTestSum, fTestSlice;
	int i, count;
	CPoint pt;
	if(!pDC)
		return;
	
	if(fDeltaArc<0)
		fDeltaArc *= -1;
	if(fDeltaArc>m_fArc)
		fDeltaArc = m_fArc;
	count = (int)(m_fArc/fDeltaArc);
	
	fTestSlice = fDeltaArc;
	if(bClockWiseDrawing)
	{
		fDeltaArc *= -1;
		pPtBgn = &m_ptArcBgn;
		pPtEnd = &m_ptArcEnd;
	}
	else
	{
		pPtBgn = &m_ptArcEnd;
		pPtEnd = &m_ptArcBgn;
	}

	ptMoving = *pPtBgn;
	pPtBgn->ToCPoint(&pt);
	pDC->LineTo(pt);
	fTestSum=0;
	for(i=0; (i<count); i++)
	{
		LineRevolve(line, m_ptC0, ptMoving, fDeltaArc, m_fRadius);
		line.pt1.ToCPoint(&pt);
		pDC->LineTo(pt);
		ptMoving = line.pt1;
		fTestSum += fTestSlice;
	}
	pPtEnd->ToCPoint(&pt);
	pDC->LineTo(pt);
}


//获取圆弧的边界矩形
void CGrArc::GetOutline(GR_RECT &grRect)
{
	GR_LINE line;
	CGrPoint ptMoving;
	double fMaxX, fMaxY, fMinX, fMinY;
	int i, count;
	double fDeltaArc=(MATH_PI/100000.0f);
	
	if(fDeltaArc>m_fArc)
		fDeltaArc = m_fArc;
	count = (int)(m_fArc/fDeltaArc);
	count = abs(count);
	
	fDeltaArc *= -1;
	
	line.pt1 = m_ptArcBgn;
	ptMoving = line.pt1;
	fMinX = fMaxX = ptMoving.fx;
	fMinY = fMaxY = ptMoving.fy;
	for(i=0; (i<count); i++)
	{
		LineRevolve(line, m_ptC0, ptMoving, fDeltaArc, m_fRadius);
		ptMoving = line.pt1;
		if(ptMoving.fx>fMaxX)
			fMaxX = ptMoving.fx;
		if(ptMoving.fy>fMaxY)
			fMaxY = ptMoving.fy;
		if(ptMoving.fx<fMinX)
			fMinX = ptMoving.fx;
		if(ptMoving.fy<fMinY)
			fMinY = ptMoving.fy;
	}
	
	grRect.fX0 = fMinX;
	grRect.fY0 = fMinY;
	grRect.fX1 = fMaxX;
	grRect.fY1 = fMaxY;
}


//计算本圆弧和目标圆弧的交点
//ptC0:		目标圆弧的圆心；
//r:		目标圆弧的半径；
//bWiseClock:	是否顺时针；
CGrPoint CGrArc::RetrieveCrossPoint(const CGrPoint ptC0, double r, BOOL bWiseClock)
{
	GR_LINE line;
	CGrPoint ptCross;
	CGrPoint ptMoving;
	double fMinDiffR, fDiffR;
	int i, count;
	double fDeltaArc=(MATH_PI/100000.0f);
	
	if(fDeltaArc>m_fArc)
		fDeltaArc = m_fArc;
	count = (int)(m_fArc/fDeltaArc);
	count = abs(count);
	
	if(bWiseClock)
		line.pt1 = m_ptArcEnd;
	else
		line.pt1 = m_ptArcBgn;
	ptMoving = line.pt1;
	fMinDiffR = GetDistanceF(ptMoving, ptC0);
	fMinDiffR -= r;
	if(fMinDiffR<0)
		fMinDiffR *= -1.0f;
	ptCross = ptMoving;
	for(i=0; (i<count); i++)
	{
		LineRevolve(line, m_ptC0, ptMoving, fDeltaArc, m_fRadius);
		ptMoving = line.pt1;
		fDiffR = GetDistanceF(ptMoving, ptC0);
		fDiffR -= r;
		if(fDiffR<0)
			fDiffR *= -1.0f;
		if(fDiffR<fMinDiffR)
		{
			fMinDiffR = fDiffR;
			ptCross = ptMoving;
		}
	}
	
	return ptCross;
}


//获取圆弧上的中点坐标
BOOL CGrArc::GetArcMidpoint(CGrPoint &pt)
{
	GR_LINE line;
	LineRevolve(line, m_ptC0, m_ptArcEnd, m_fArc/2, m_fRadius);
	pt = line.pt1;
	return TRUE;
}

