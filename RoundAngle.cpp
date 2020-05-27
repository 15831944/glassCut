// RoundAngle.cpp: implementation of the CRoundAngle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bender.h"
#include "RoundAngle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRoundAngle::CRoundAngle()
{
	Clean();
}

CRoundAngle::~CRoundAngle()
{

}

void CRoundAngle::Clean()
{
	m_ptVertex.Set(0,0);
	m_grArc.Clean();
}

void CRoundAngle::Scale(double fScale)
{
	m_grArc.Scale(fScale);
	m_ptVertex.Scale(fScale);
}

//初始化圆角
//fRadius:		圆弧的半径
//ptVertex:		被圆弧切割的角的顶点坐标
//ptBgn:		顺时针方向，圆弧的起点坐标
//ptEnd:		顺时针方向，圆弧的终点坐标
BOOL CRoundAngle::Initialize(const double m_fRadius, const CGrPoint &ptVertex, const CGrPoint &ptBgn, const CGrPoint &ptEnd)
{
	if(!m_grArc.InitRoundCornerArc(m_fRadius, ptVertex, ptBgn, ptEnd))
		return FALSE;
	m_fVertexArc = (MATH_PI-m_grArc.m_fArc);
	m_ptVertex = ptVertex;
	return TRUE;
}

void CRoundAngle::PaintTo(CDC *pDC, BOOL bClockWiseDrawing/*=TRUE*/, double fArcDelta/*=(MATH_PI/10000.0f)*/)
{
	m_grArc.PaintTo(pDC, bClockWiseDrawing, fArcDelta);
}

void CRoundAngle::Offset(double fx, double fy)
{
	m_grArc.m_ptC0.Offset(fx, fy);
	m_ptVertex.Offset(fx, fy);
	m_grArc.m_ptArcBgn.Offset(fx, fy);
	m_grArc.m_ptArcEnd.Offset(fx, fy);
}

const CGrPoint* CRoundAngle::GetArcBgnPoint(BOOL bClockWise)
{
	if(!bClockWise)
		return &(m_grArc.m_ptArcEnd);
	return &(m_grArc.m_ptArcBgn);
}

const CGrPoint* CRoundAngle::GetArcEndPoint(BOOL bClockWise)
{
	if(!bClockWise)
		return &(m_grArc.m_ptArcBgn);
	return &(m_grArc.m_ptArcEnd);
}
