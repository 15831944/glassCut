// GrEllipse.h: interface for the CGrEllipse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRELLIPSE_H__9C0E24B0_E954_4410_9900_658A40E1BB4F__INCLUDED_)
#define AFX_GRELLIPSE_H__9C0E24B0_E954_4410_9900_658A40E1BB4F__INCLUDED_

#include "grMath.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGrEllipse  
{	//À≥ ±’Î
public:
	double GetSweepArc();
	double GetArcEnd(BOOL bClockWise);
	double GetArcBgn(BOOL bClockWise);
	void GetOutline(GR_RECT &grRect);
	void GetEllipsesPoint(CGrPoint &output, double fArc);
	void PaintTo(CDC *pDC, BOOL bClockWiseDrawing=TRUE, double fDeltaArc=(MATH_PI/10000.0f));
	void Offset(double fx, double fy);
	void Scale(double fScale);
	BOOL InitEllipse(const CGrPoint &ptC0, double fA, double fB, double fArcBgn, double fArcEnd);
	CGrEllipse();
	virtual ~CGrEllipse();
	
protected:
	CGrPoint m_ptC0;
	double   m_fA;
	double   m_fB;
	double   m_fArcBgn;
	double   m_fArcEnd;
};

#endif // !defined(AFX_GRELLIPSE_H__9C0E24B0_E954_4410_9900_658A40E1BB4F__INCLUDED_)
