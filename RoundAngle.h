// RoundAngle.h: interface for the CRoundAngle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROUNDANGLE_H__22CD1C35_7DD2_4AE8_83B5_D6F29CBE2B32__INCLUDED_)
#define AFX_ROUNDANGLE_H__22CD1C35_7DD2_4AE8_83B5_D6F29CBE2B32__INCLUDED_

#include "grMath.h"
#include "GrArc.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRoundAngle  
{
public:
	const CGrPoint* GetArcBgnPoint(BOOL bClockWise);
	const CGrPoint* GetArcEndPoint(BOOL bClockWise);
	void Offset(double fx, double fy);
	void PaintTo(CDC *pDC, BOOL bClockWiseDrawing=TRUE, double fArcDelta=(MATH_PI/10000.0f));
	BOOL Initialize(const double fRadius, const CGrPoint &grptNear, const CGrPoint &grptFar1, const CGrPoint &grptFar2);
	void Scale(double fScale);
	void Clean();
	CGrPoint m_ptVertex;	//被裁剪角的坐标
	double	 m_fVertexArc;	//被裁剪角的角度
	CGrArc   m_grArc;		//用于裁剪的圆弧
	CRoundAngle();
	virtual ~CRoundAngle();
};

#endif // !defined(AFX_ROUNDANGLE_H__22CD1C35_7DD2_4AE8_83B5_D6F29CBE2B32__INCLUDED_)
