#ifndef __GRAPH_MATH_H__
#define	__GRAPH_MATH_H__

#include "math.h"

#define MATH_PI		(3.1415926535897f)
#define MATH_2PI	(MATH_PI*2)
#define Rc2Grc(pDes, pSrc)	\
{\
	(pDes)->fl=(double)((pSrc)->left);\
	(pDes)->ft=(double)((pSrc)->top);\
	(pDes)->fr=(double)((pSrc)->right);\
	(pDes)->fb=(double)((pSrc)->bottom);\
}
#define Grc2Rc(pDes, pSrc)	\
{\
	(pDes)->left=(int)((pSrc)->fl+0.5f);\
	(pDes)->top=(int)((pSrc)->ft+0.5f);\
	(pDes)->right=(int)((pSrc)->fr+0.5f);\
	(pDes)->bottom=(int)((pSrc)->fb+0.5f);\
}

class CGrPoint
{
public:
	double fx;
	double fy;
	void Offset(double dx, double dy)
	{
		fx+=dx;
		fy+=dy;
	}
	void Offset(CGrPoint &pt)
	{
		fx+=pt.fx;
		fy+=pt.fy;
	}
	void Set(POINT &pt)
	{
		fx = pt.x;
		fy = pt.y;
	}
	void Set(CGrPoint &pt)
	{
		fx = pt.fx;
		fy = pt.fy;
	}
	void Set(double x, double y)
	{
		fx = x;
		fy = y;
	}
	void ToPoint(POINT *buff)
	{
		if(buff)
		{
			buff->x = (int)(fx+0.5f);
			buff->y = (int)(fy+0.5f);
		}
	}
	void ToCPoint(CPoint *buff)
	{
		if(buff)
		{
			buff->x = (int)(fx+0.5f);
			buff->y = (int)(fy+0.5f);
		}
	}
	void Scale(double fScale)
	{
		fx *= fScale;
		fy *= fScale;
	}
	CGrPoint(){Set(0,0);}
	CGrPoint(double fx, double fy){Set(fx,fy);}
};

typedef struct tagLineSegment
{
	CGrPoint pt1;
	CGrPoint ptCenter;
	CGrPoint pt2;
} GR_LINE;

typedef struct tagGraphRect
{
	double fX0;
	double fY0;
	double fX1;
	double fY1;
} GR_RECT;


double GetDistance(double fx1, double fy1, double fx2, double fy2);

double GetDistanceF(const CGrPoint &pt1, const CGrPoint &pt2);

double GetDistanceP(const POINT &pt1, const POINT &pt2);

void RetrievePointOfLine(CGrPoint &output, const CGrPoint &ptNear, const CGrPoint &ptFar, double fDistanceNear);

double RetrieveAngleOfTriangle(double fOppositeSide, double fAdjacentSide1, double fAdjacentSide2);

void PointExpend(POINT &point, UINT nPower);

void LineRevolve(GR_LINE &output, CGrPoint ptCenter, CGrPoint ptRef, double fSweepArc, double fRadius);

void LineParallelMoving(GR_LINE &output, const GR_LINE line, double fOffset, BOOL bToLeft);

void RetrieveArcCenter(CGrPoint &output, const double fRadius, const CGrPoint &ptArcBgn, const CGrPoint &ptArcEnd);

UINT GetArcQuadrant(double &fArc);

UINT GetPointQuadrant(const CGrPoint &pt);//根据坐标求象限
#endif

