// GrEllipse.cpp: implementation of the CGrEllipse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bender.h"
#include "GrEllipse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGrEllipse::CGrEllipse()
{
	m_ptC0.Set(0,0);
	m_fA = 0;
	m_fB = 0;
	m_fArcBgn = 0;
	m_fArcEnd = 0;
}

CGrEllipse::~CGrEllipse()
{

}


//初始化椭圆弧
//ptC0:			椭圆弧的圆心
//fA:			横轴，即，椭圆外切矩形的横边的一半；
//fB:			纵轴，即，椭圆外切矩形的纵边的一半；
//fArcBgn:		顺时针方向，椭圆弧的起点坐标；
//fArcEnd:		顺时针方向，椭圆弧的终点坐标；
BOOL CGrEllipse::InitEllipse(const CGrPoint &ptC0, double fA, double fB, double fArcBgn, double fArcEnd)
{
	m_ptC0 = ptC0;
	m_fA = fA;
	m_fB = fB;
	m_fArcBgn = fArcBgn;
	m_fArcEnd = fArcEnd;
	if(m_fArcBgn<0)
		m_fArcBgn += MATH_2PI;
	if(m_fArcBgn>MATH_2PI)
		m_fArcBgn -= MATH_2PI;
	if(m_fArcEnd<0)
		m_fArcEnd += MATH_2PI;
	if(m_fArcEnd>MATH_2PI)
		m_fArcEnd -= MATH_2PI;
	return TRUE;
}

//椭圆弧整体坐标缩放
void CGrEllipse::Scale(double fScale)
{
	this->m_ptC0.Scale(fScale);
	this->m_fA *= fScale;
	this->m_fB *= fScale;
}

//椭圆弧整体坐标偏移
void CGrEllipse::Offset(double fx, double fy)
{
	this->m_ptC0.Offset(fx, fy);
}

//将椭圆弧画到pDC指定的DC上
//bClockWiseDrawing:	TRUE-->顺时针画，否则逆时针画；
//fDeltaArc:			角度分辨率，值越小画出的椭圆弧越精细；
void CGrEllipse::PaintTo(CDC *pDC, BOOL bClockWiseDrawing/*=TRUE*/, double fDeltaArc/*=(MATH_PI/10000.0f)*/)
{
	double fArc;
	int count;
	CGrPoint point;

	if(!pDC)
		return;
	
	fArc = (m_fArcBgn-m_fArcEnd);
	while(fArc<0)
	{	fArc += (MATH_2PI);	}
	if(fDeltaArc<0)
		fDeltaArc *= -1;
	if(fDeltaArc>fArc)
		fDeltaArc = fArc;
	count = (int)(fArc/fDeltaArc);
	fDeltaArc = (fArc/count);

	if(bClockWiseDrawing)
	{
		fArc = m_fArcBgn;
		while(fArc>=m_fArcEnd)
		{
			if(fArc<0)
				fArc += MATH_2PI;
			if(fArc>MATH_2PI)
				fArc -= MATH_2PI;
			GetEllipsesPoint(point, fArc);
			pDC->LineTo((int)(point.fx), (int)(point.fy));
			fArc -= fDeltaArc;
		}
	}
	else
	{
		fArc = m_fArcEnd;
		while(fArc<=m_fArcBgn)
		{
			if(fArc<0)
				fArc += MATH_2PI;
			if(fArc>MATH_2PI)
				fArc -= MATH_2PI;
			GetEllipsesPoint(point, fArc);
			pDC->LineTo((int)(point.fx), (int)(point.fy));
			fArc += fDeltaArc;
		}
	}
}

//获取椭圆弧上对应角度为fArc的一个点的坐标
void CGrEllipse::GetEllipsesPoint(CGrPoint &output, double fArc)
{
	double fTan, fFx, fFy;
	UINT nQuadrant;

	if(fArc<0)
		fArc += MATH_2PI;
	if(fArc>MATH_2PI)
		fArc -= MATH_2PI;
	
	nQuadrant = GetArcQuadrant(fArc);
	switch(nQuadrant)
	{
	case 0:
		fArc = fArc;
		fFx = 1;	fFy = 1;
		break;
	case 1:
		fArc = MATH_PI-fArc;
		fFx = -1;	fFy = 1;
		break;
	case 2:
		fArc = fArc-MATH_PI;
		fFx = -1;	fFy = -1;
		break;
	case 3:
		fArc = (MATH_PI*2)-fArc;
		fFx = 1;	fFy = -1;
		break;
	default:
		break;
	}
	
	fTan = tan(fArc);
	
	output.fx = (m_fA*m_fB)/(sqrt((m_fB*m_fB)+(m_fA*m_fA)*(fTan*fTan)));
	output.fy = output.fx*fTan;
	output.fx *= fFx;
	output.fy *= fFy;
	
	output.Offset(m_ptC0);
}

//获取椭圆弧的边界矩形
void CGrEllipse::GetOutline(GR_RECT &grRect)
{
	double fArc, fDelta;
	CGrPoint point;

	fDelta=(MATH_PI/10000.0f);
	fArc = m_fArcEnd;
	GetEllipsesPoint(point, fArc);
	grRect.fX0 = point.fx;
	grRect.fY0 = point.fy;
	grRect.fX1 = point.fx;
	grRect.fY1 = point.fy;
	while(fArc<=m_fArcBgn)
	{
		fArc += fDelta;
		GetEllipsesPoint(point, fArc);
		if(point.fx<grRect.fX0)
			grRect.fX0 = point.fx;
		if(point.fy<grRect.fY0)
			grRect.fY0 = point.fy;
		if(point.fx>grRect.fX1)
			grRect.fX1 = point.fx;
		if(point.fy>grRect.fY1)
			grRect.fY1 = point.fy;
	}
}

//获取椭圆弧的起点，还取决于时针方向的定义；
double CGrEllipse::GetArcBgn(BOOL bClockWise)
{
	if(!bClockWise)
		return m_fArcEnd;
	return m_fArcBgn;
}

//获取椭圆弧的终点，还取决于时针方向的定义；
double CGrEllipse::GetArcEnd(BOOL bClockWise)
{
	if(!bClockWise)
		return m_fArcBgn;
	return m_fArcEnd;
}

//获取椭圆弧扫过的角度；
double CGrEllipse::GetSweepArc()
{
	return (m_fArcBgn-m_fArcEnd);
}

