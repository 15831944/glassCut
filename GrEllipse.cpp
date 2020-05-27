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


//��ʼ����Բ��
//ptC0:			��Բ����Բ��
//fA:			���ᣬ������Բ���о��εĺ�ߵ�һ�룻
//fB:			���ᣬ������Բ���о��ε��ݱߵ�һ�룻
//fArcBgn:		˳ʱ�뷽����Բ����������ꣻ
//fArcEnd:		˳ʱ�뷽����Բ�����յ����ꣻ
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

//��Բ��������������
void CGrEllipse::Scale(double fScale)
{
	this->m_ptC0.Scale(fScale);
	this->m_fA *= fScale;
	this->m_fB *= fScale;
}

//��Բ����������ƫ��
void CGrEllipse::Offset(double fx, double fy)
{
	this->m_ptC0.Offset(fx, fy);
}

//����Բ������pDCָ����DC��
//bClockWiseDrawing:	TRUE-->˳ʱ�뻭��������ʱ�뻭��
//fDeltaArc:			�Ƕȷֱ��ʣ�ֵԽС��������Բ��Խ��ϸ��
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

//��ȡ��Բ���϶�Ӧ�Ƕ�ΪfArc��һ���������
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

//��ȡ��Բ���ı߽����
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

//��ȡ��Բ������㣬��ȡ����ʱ�뷽��Ķ��壻
double CGrEllipse::GetArcBgn(BOOL bClockWise)
{
	if(!bClockWise)
		return m_fArcEnd;
	return m_fArcBgn;
}

//��ȡ��Բ�����յ㣬��ȡ����ʱ�뷽��Ķ��壻
double CGrEllipse::GetArcEnd(BOOL bClockWise)
{
	if(!bClockWise)
		return m_fArcBgn;
	return m_fArcEnd;
}

//��ȡ��Բ��ɨ���ĽǶȣ�
double CGrEllipse::GetSweepArc()
{
	return (m_fArcBgn-m_fArcEnd);
}

