#include "StdAfx.h"
#include "grMath.h"

double GetDistance(double fx1, double fy1, double fx2, double fy2)
{
	double fdx, fdy, z;
	fdx = fx2-fx1;
	fdy = fy2-fy1;
	z = sqrt(fdx*fdx+fdy*fdy);
	return z;
}

double GetDistanceF(const CGrPoint &pt1, const CGrPoint &pt2)
{
	return GetDistance(pt1.fx, pt1.fy, pt2.fx, pt2.fy);
}

//计算线段上某一点的坐标
//ptNear和ptFar分别为直线上的两个参考点；
//fDistanceNear为要求的点到ptNear点的距离；
void RetrievePointOfLine(CGrPoint &output, const CGrPoint &ptNear, const CGrPoint &ptFar, double fDistanceNear)
{
	GR_LINE line;
	LineRevolve(line, ptNear, ptFar, 0, fDistanceNear);
	output = line.pt1;
	return;
}

//根据三边计算夹角角度
// fOppositeSide为对边长度
// fAdjacentSide1和fAdjacentSide2为两条邻边的长度
double RetrieveAngleOfTriangle(double fOppositeSide, double fAdjacentSide1, double fAdjacentSide2)
{
	long double fTemp;
	if(fOppositeSide>=(fAdjacentSide1+fAdjacentSide2))
	{
		return (MATH_PI);
	}
	fTemp = (fAdjacentSide1*fAdjacentSide1)+(fAdjacentSide2*fAdjacentSide2);
	fTemp -= (fOppositeSide*fOppositeSide);
	fTemp /= (2*fAdjacentSide1*fAdjacentSide2);
	fTemp = acos(fTemp);
	if(fTemp<0)
		fTemp=0;
	return fTemp;
}


void PointExpend(POINT &point, UINT nPower)
{
	point.x *= nPower;
	point.y *= nPower;
}


//根据坐标求象限
UINT GetPointQuadrant(const CGrPoint &pt)
{
	UINT nIndex;
	if(pt.fx>0 && pt.fy>=0)
		nIndex=0;
	else if(pt.fx<=0 && pt.fy>0)
		nIndex=1;
	else if(pt.fx<0 && pt.fy<=0)
		nIndex=2;
	else
		nIndex=3;
	return nIndex;
}

//根据角度求象限
UINT GetArcQuadrant(double &fArc)
{
	UINT nIndex;
	if(fArc<0)
		fArc += MATH_2PI;
	if(fArc>MATH_2PI)
		fArc -= MATH_2PI;
	if(fArc<(MATH_PI/2))			nIndex=0;
	else if(fArc<(MATH_PI))			nIndex=1;
	else if(fArc<(MATH_PI*1.5f))	nIndex=2;
	else							nIndex=3;
	return nIndex;
}


//将一条线段逆时针转动一定角度后，得到一条新的线段；
//ptCenter：	为转动的中心点；
//ptRef：		转动的参考点；
//fSweepArc：	逆时针转动的角度；
//fRadius：		与output.ptCenter一起确定新线段的端点到output.ptCenter的距离；
//output：		新的线段，（其中：output.ptCenter等于ptCenter, output.pt1为ptRef逆时针转动后在新线段上且距离output.ptCenter为
//				fRadius的端点，output.pt2为output.pt1以output.ptCenter为中心的镜像点）；
void LineRevolve(GR_LINE &output, CGrPoint ptCenter, CGrPoint ptRef, double fSweepArc, double fRadius)
{
	CGrPoint pt0, pt1;
	double fArcBgn, fArc, fFx, fFy, bakSweepArc;
	int nQuadrant;
	
	memset(&output, 0, sizeof(GR_LINE));
	
	bakSweepArc = fSweepArc;
	
	while(fSweepArc<0)
	{ fSweepArc += (MATH_PI*2); }
	
	pt0 = ptCenter;
	
	ptCenter.fx -= pt0.fx;
	ptCenter.fy -= pt0.fy;
	ptRef.fx -= pt0.fx;
	ptRef.fy -= pt0.fy;
	
	nQuadrant = GetPointQuadrant(ptRef);
	fFx = (ptRef.fx<0)? (-1) : (1);	
	fFy = (ptRef.fy<0)? (-1) : (1);	
	fArcBgn = atan((ptRef.fy*fFy)/(ptRef.fx*fFx));
	switch(nQuadrant)
	{
	case 0:	fArcBgn = fArcBgn;				break;
	case 1:	fArcBgn = MATH_PI-fArcBgn;		break;
	case 2:	fArcBgn = MATH_PI+fArcBgn;		break;
	case 3:	fArcBgn = (MATH_PI*2)-fArcBgn;	break;
	default:	break;
	}
	
	fArc = (fArcBgn+fSweepArc);
	while(fArc>=(MATH_PI*2))
	{	fArc-=(MATH_PI*2);	}	
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
	default:	break;
	}
	
	output.pt1.fx = fRadius*cos(fArc);
	output.pt1.fy = fRadius*sin(fArc);
	output.pt1.fx *= fFx;
	output.pt1.fy *= fFy;
	
	output.pt2.fx = output.pt1.fx*(-1);
	output.pt2.fy = output.pt1.fy*(-1);
	
	output.ptCenter = ptCenter;
	
	output.pt1.Offset(pt0);
	output.pt2.Offset(pt0);
	output.ptCenter.Offset(pt0);
}

//根据圆弧的半径和弦的两个端点坐标确定圆弧的圆心坐标
//fRadius：		半径
//ptArcBgn：	顺时针方向，圆弧的起点坐标；
//ptArcEnd：	顺时针方向，圆弧的终点坐标；
//output：		计算出的圆心坐标；
void RetrieveArcCenter(CGrPoint &output, const double fRadius, const CGrPoint &ptArcBgn, const CGrPoint &ptArcEnd)
{
	double fChord=GetDistanceF(ptArcBgn, ptArcEnd);
	double fArc=RetrieveAngleOfTriangle(fRadius, fRadius, fChord);
	GR_LINE line;

	if(fArc<0)
		return;
	LineRevolve(line, ptArcEnd, ptArcBgn, fArc, fRadius);
	output = line.pt1;
}


