// GrArc.h: interface for the CGrArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRARC_H__F949DF71_FDFD_4E96_A4CA_8F5F4221C081__INCLUDED_)
#define AFX_GRARC_H__F949DF71_FDFD_4E96_A4CA_8F5F4221C081__INCLUDED_

#include "grMath.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGrArc  
{	//˳ʱ��
public:
	BOOL GetArcMidpoint(CGrPoint &pt);
	BOOL InitArcA(const CGrPoint &ptC0, const CGrPoint &ptArcBgn, const CGrPoint &ptArcEnd, BOOL bGreaterArc=FALSE);
	CGrPoint RetrieveCrossPoint(const CGrPoint ptC0, double r, BOOL bWiseClock);
	BOOL InitCircle(double fRadius, CGrPoint &ptC0);
	void GetOutline(GR_RECT &grRect);
	BOOL IsClosed();
	void PaintTo(CDC *pDC, BOOL bClockWiseDrawing=TRUE, double fDeltaArc=(MATH_PI/10000.0f));
	void Clean();
	BOOL InitArc(double fRadius, const CGrPoint &ptC0, const CGrPoint &ptArcBgn, const CGrPoint &ptArcEnd, BOOL bGreaterArc=FALSE);
	BOOL InitRoundCornerArc(double fRadius, const CGrPoint &ptVertex, const CGrPoint &ptBgn, const CGrPoint &ptEnd);
	void Offset(double fx, double fy);
	void Scale(double fScale);
	double   m_fRadius;		//Բ���뾶
	double   m_fArc;		//Բ������
	CGrPoint m_ptC0;		//Բ��Բ��
	CGrPoint m_ptArcBgn;	//˳ʱ�뷽��Բ�������
	CGrPoint m_ptArcEnd;	//˳ʱ�뷽��Բ�����յ�

	CGrArc();
	virtual ~CGrArc();

protected:
	BOOL m_bClosed;
};

#endif // !defined(AFX_GRARC_H__F949DF71_FDFD_4E96_A4CA_8F5F4221C081__INCLUDED_)
