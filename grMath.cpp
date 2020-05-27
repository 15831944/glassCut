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

//�����߶���ĳһ�������
//ptNear��ptFar�ֱ�Ϊֱ���ϵ������ο��㣻
//fDistanceNearΪҪ��ĵ㵽ptNear��ľ��룻
void RetrievePointOfLine(CGrPoint &output, const CGrPoint &ptNear, const CGrPoint &ptFar, double fDistanceNear)
{
	GR_LINE line;
	LineRevolve(line, ptNear, ptFar, 0, fDistanceNear);
	output = line.pt1;
	return;
}

//�������߼���нǽǶ�
// fOppositeSideΪ�Ա߳���
// fAdjacentSide1��fAdjacentSide2Ϊ�����ڱߵĳ���
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


//��������������
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

//���ݽǶ�������
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


//��һ���߶���ʱ��ת��һ���ǶȺ󣬵õ�һ���µ��߶Σ�
//ptCenter��	Ϊת�������ĵ㣻
//ptRef��		ת���Ĳο��㣻
//fSweepArc��	��ʱ��ת���ĽǶȣ�
//fRadius��		��output.ptCenterһ��ȷ�����߶εĶ˵㵽output.ptCenter�ľ��룻
//output��		�µ��߶Σ������У�output.ptCenter����ptCenter, output.pt1ΪptRef��ʱ��ת���������߶����Ҿ���output.ptCenterΪ
//				fRadius�Ķ˵㣬output.pt2Ϊoutput.pt1��output.ptCenterΪ���ĵľ���㣩��
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

//����Բ���İ뾶���ҵ������˵�����ȷ��Բ����Բ������
//fRadius��		�뾶
//ptArcBgn��	˳ʱ�뷽��Բ����������ꣻ
//ptArcEnd��	˳ʱ�뷽��Բ�����յ����ꣻ
//output��		�������Բ�����ꣻ
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


