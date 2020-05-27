// GrPath.cpp: implementation of the CGrPath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bender.h"
#include "GrPath.h"
#include "grMath.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGrPath::CGrPath()
{
	memset(&m_clip, 0, sizeof(GR_CLIP));
	m_nNodeCount=0;
	memset(m_nodes, 0, sizeof(m_nodes));
	memset(&m_rcClip, 0, sizeof(GR_RECT));
	memset(m_dimensions, 0, sizeof(m_dimensions));
	m_nDimentsionCount=0;
	m_pGCodeBuff = new char[16*1024*1024];
	if(m_pGCodeBuff)
		m_pGCodeBuff[0]='\0';
	UpdateClipRect();
	m_bG00 = FALSE;
}

CGrPath::~CGrPath()
{
	Reset();
	if(m_pGCodeBuff)
		delete m_pGCodeBuff;
}

void CGrPath::Reset()
{
	int i;
	GR_NODE *pNode=NULL;
	memset(&m_clip, 0, sizeof(GR_CLIP));
	pNode=&(m_nodes[0]);
	for(i=0; i<(int)m_nNodeCount; i++,pNode++)
	{
		if(pNode->pRoundAngle)
		{
			delete pNode->pRoundAngle;
			pNode->pRoundAngle=NULL;
		}
		if(pNode->pEllipse)
		{
			delete pNode->pEllipse;
			pNode->pEllipse=NULL;
		}
	}
	m_nNodeCount=0;
	memset(m_nodes, 0, sizeof(m_nodes));
	memset(&m_rcClip, 0, sizeof(GR_RECT));
	memset(m_dimensions, 0, sizeof(m_dimensions));
	m_nDimentsionCount = 0;
	UpdateClipRect();
}

//整体坐标缩放
void CGrPath::Scale(double fScale)
{
	int i;
	GR_NODE *pNode=NULL;
	GR_DIMENSION *pDimension=NULL;
	m_clip.X1 *= fScale;
	m_clip.Y1 *= fScale;
	m_clip.X2 *= fScale;
	m_clip.Y2 *= fScale;
	for(i=0; i<(int)m_nNodeCount; i++)
	{
		pNode = &m_nodes[i];
		pNode->grptSharp.Scale(fScale);
		pNode->fMinWidth *= fScale;
		pNode->fMinHeight *= fScale;
		if(pNode->pRoundAngle)
		{
			pNode->pRoundAngle->Scale(fScale);
		}
		if(pNode->pEllipse)
		{
			pNode->pEllipse->Scale(fScale);
		}
	}
	for(i=0; i<(int)m_nDimentsionCount; i++)
	{
		pDimension = &m_dimensions[i];
		//pDimension->fMarkDistance *= fScale;
		pDimension->pt1.Scale(fScale);
		pDimension->pt2.Scale(fScale);
		pDimension->ptC0.Scale(fScale);
	}
	m_rcClip.fX0 *= fScale;
	m_rcClip.fY0 *= fScale;
	m_rcClip.fX1 *= fScale;
	m_rcClip.fY1 *= fScale;
// 	UpdateClipRect();
}

//添加一个节点
BOOL CGrPath::NodeAppend(const GR_NODE &node)
{
	if(m_nNodeCount>=MAX_NODEs)
		return FALSE;
	memcpy(&m_nodes[m_nNodeCount], &node, sizeof(GR_NODE));
	if(GNT_INDEPENDENT_CIRCLE==m_nodes[m_nNodeCount].nNodeType)
		m_nodes[m_nNodeCount].bIsCloseNode=TRUE;
	if (m_bG00)
	{
        m_nodes[m_nNodeCount].bIsCloseNode=TRUE;
		m_bG00 = FALSE;
	}
	m_nNodeCount++;
	CheckClipRect(m_nNodeCount-1);
	return TRUE;
}


//添加尖角节点
BOOL CGrPath::AddSharpNodes(const CGrPoint *arrPoints, UINT nCount)
{
	GR_NODE grNode;
	UINT i;
	if(!arrPoints)
		return FALSE;
	memset(&grNode, 0, sizeof(GR_NODE));
	grNode.nNodeType = GNT_SHARP_ANGLE;
	for(i=0; i<(int)nCount; i++)
	{
		grNode.grptSharp = arrPoints[i];
		this->NodeAppend(grNode);
	}
	return TRUE;
}

//添加尺寸标注
BOOL CGrPath::DimensionAppend(const GR_DIMENSION &dimension)
{
	if(m_nDimentsionCount>MAX_NODEs)
		return FALSE;
	memcpy(&m_dimensions[m_nDimentsionCount], &dimension, sizeof(GR_DIMENSION));
	m_nDimentsionCount++;
	return TRUE;
}

//设置边界
void CGrPath::SetClip(const GR_CLIP &clip)
{
	memcpy(&m_clip, &clip, sizeof(GR_CLIP));
	UpdateClipRect();
}

//获取边界
BOOL CGrPath::GetClip(GR_CLIP &buff)
{
	memcpy(&buff, &m_clip, sizeof(GR_CLIP));
	return TRUE;
}


//检查并更新边界尺寸
void CGrPath::FitClipRect(const double fXMax, const double fYMax)
{
	if(fXMax>m_rcClip.fX1)
		m_rcClip.fX1=fXMax;
	if(fYMax>m_rcClip.fY1)
		m_rcClip.fY1=fYMax;
}

void CGrPath::CheckClipRect(UINT nNodeIndex)
{
	GR_NODE *pNode=NULL;
	GR_RECT grRect;
	double fx, fy;
	if(nNodeIndex<m_nNodeCount)
	{
		pNode=&m_nodes[nNodeIndex];
		
		fx = m_clip.X1 + pNode->fMinWidth + m_clip.X2;
		fy = m_clip.Y1 + pNode->fMinHeight + m_clip.Y2;
		FitClipRect(fx, fy);
		
		if(GNT_INDEPENDENT_CIRCLE==pNode->nNodeType)
		{
			if(pNode->pRoundAngle)
			{
				fx = (pNode->pRoundAngle->m_grArc.m_ptC0.fx+pNode->pRoundAngle->m_grArc.m_fRadius+m_clip.X2);
				fy = (pNode->pRoundAngle->m_grArc.m_ptC0.fy+pNode->pRoundAngle->m_grArc.m_fRadius+m_clip.Y2);
				FitClipRect(fx, fy);
			}
		}
		else if(GNT_ELLIPSE==pNode->nNodeType)
		{
			if(pNode->pEllipse)
			{
				pNode->pEllipse->GetOutline(grRect);
				fx = (grRect.fX1+m_clip.X2);
				fy = (grRect.fY1+m_clip.Y2);
				FitClipRect(fx, fy);
			}
		}
		else if(GNT_SHARP_ANGLE==pNode->nNodeType)
		{
			fx = (pNode->grptSharp.fx+m_clip.X2);
			fy = (pNode->grptSharp.fy+m_clip.Y2);
			FitClipRect(fx, fy);
		}
		else if(GNT_ROUND_ANGLE==pNode->nNodeType)
		{
			if(pNode->pRoundAngle)
			{
// 				fx = (pNode->pRoundAngle->m_ptVertex.fx+m_clip.X2);
// 				fy = (pNode->pRoundAngle->m_ptVertex.fy+m_clip.Y2);
// 				FitClipRect(fx, fy);
// 				
				pNode->pRoundAngle->m_grArc.GetOutline(grRect);
				fx = (grRect.fX1+m_clip.X2);
				fy = (grRect.fY1+m_clip.Y2);
				FitClipRect(fx, fy);
			}
		}
	}
}

//确定边界尺寸
void CGrPath::UpdateClipRect()
{
	memset(&m_rcClip, 0, sizeof(GR_RECT));

	m_rcClip.fX0 = 0;
	m_rcClip.fY0 = 0;

	for(int i=0; i<(int)m_nNodeCount; i++)
	{
		CheckClipRect(i);
	}
}

//画坐标轴
void DrawCoordinate(CDC *pDC, LPCRECT lpRect, COLORREF color)
{
	CPen pen(PS_SOLID, 1, color);
	CPen *pOldPen=NULL;
	CRgn rgn;
	CBrush br;
	POINT points[8];
	CRect rc;
	
	rc = *lpRect;
	rc.left -= 1;
	
	br.CreateSolidBrush(color);
	
	points[0].x = rc.left;
	points[0].y = rc.bottom+12;
	points[1].x = rc.left-4;
	points[1].y = rc.bottom;
	points[2].x = rc.left+4;
	points[2].y = rc.bottom;
	rgn.CreatePolygonRgn(points, 3, RGN_OR);
	pDC->FillRgn(&rgn, &br);
	rgn.DeleteObject();
	
	points[0].x = rc.right+12;
	points[0].y = rc.top;
	points[1].x = rc.right;
	points[1].y = rc.top-4;
	points[2].x = rc.right;
	points[2].y = rc.top+4;
	rgn.CreatePolygonRgn(points, 3, RGN_OR);
	pDC->FillRgn(&rgn, &br);
	rgn.DeleteObject();
	
	
	pOldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(rc.left, rc.bottom);
	pDC->LineTo(rc.left, rc.top-1);
	pDC->LineTo(rc.right, rc.top-1);
	
	// 	rc.left += 1;
	// 	pDC->FillSolidRect(&rc, RGB(252,252,252));
	
	if(pen.m_hObject)
		pen.DeleteObject();
	if(br.m_hObject)
		br.DeleteObject();
}

//在pDC指定的DC上绘制图形；
//lpRect:		绘图区域；
//color:		图形的前景色；
void CGrPath::PaintTo(CDC *pDC, const LPCRECT lpRect, const COLORREF color)
{
	double fScale, w, h;
	GR_NODE *pNode=NULL;
	CRoundAngle *pRoundAngle=NULL;
	CGrEllipse *pEllipse=NULL;
	POINT pt0, pt1;
	CRgn  rgn;
	CBrush brFill, brFrame;
	CRect  rc;
	int index, count;
	BOOL bWillRestart;
	CGrPoint grPt;
	GR_RECT rcGraph, rcPath;

	if(!pDC || !lpRect)
		return;
	if(!m_nNodeCount)
		return;

	brFill.CreateSolidBrush(color);
	brFrame.CreateSolidBrush(RGB(0,0,0));
	if(!brFill.m_hObject)
		return;
	if(!brFrame.m_hObject)
		return;

	GetGraphRect(rcGraph);

	GetPathRect(rcPath);
	m_rcClip.fX0 = rcPath.fX0-m_clip.X1;
	m_rcClip.fY0 = rcPath.fY0-m_clip.Y1;
	m_rcClip.fX1 = rcPath.fX1+m_clip.X2;
	m_rcClip.fY1 = rcPath.fY1+m_clip.Y2;
// 	if(m_rcClip.fX0!=0.0f || m_rcClip.fY0!=0.0f)
// 		this->Offset(-m_rcClip.fX0, -m_rcClip.fY0);

	//全部从0,0开始画图解决现实缩放
// 	w = (rcGraph.fX1-rcGraph.fX0+m_clip.X2);
// 	h = (rcGraph.fY1-rcGraph.fY0+m_clip.Y2);
	w = (rcGraph.fX1+m_clip.X2);
	h = (rcGraph.fY1+m_clip.Y2);

	if(w>h)
	{
		if(w!=0.0f)
			fScale = (lpRect->right-lpRect->left)/w;
		else
			fScale=0;
	}
	else
	{
		if(h!=0.0f)
			fScale = (lpRect->bottom-lpRect->top)/h;
		else
			fScale=0;
	}

	this->Scale(fScale);

	rc.left  = lpRect->left + (int)(m_rcClip.fX0+0.5f);
	rc.top   = lpRect->top +  (int)(m_rcClip.fY0+0.5f);
	rc.right = lpRect->left + (int)(m_rcClip.fX1+0.5f);
	rc.bottom= lpRect->top +  (int)(m_rcClip.fY1+0.5f);
	pDC->FillSolidRect(&rc, RGB(250,250,250));
	DrawCoordinate(pDC, &rc, RGB(220,220,220));

	index = 0;
	pNode = &(m_nodes[0]);
	bWillRestart = TRUE;

	for( ; index<(int)m_nNodeCount; index++,pNode++)
	{
		if(GNT_INDEPENDENT_CIRCLE==pNode->nNodeType)
		{
			pRoundAngle=pNode->pRoundAngle;
			if(!pRoundAngle)
				continue;
			rc.left  = (int)(pRoundAngle->m_grArc.m_ptC0.fx-pRoundAngle->m_grArc.m_fRadius+0.5f);
			rc.top   = (int)(pRoundAngle->m_grArc.m_ptC0.fy-pRoundAngle->m_grArc.m_fRadius+0.5f);
			rc.right = rc.left + (int)(pRoundAngle->m_grArc.m_fRadius*2+0.5f);
			rc.bottom= rc.top + (int)(pRoundAngle->m_grArc.m_fRadius*2+0.5f);
			rgn.CreateEllipticRgnIndirect(&rc);
			if(rgn.m_hObject)
			{
				rgn.OffsetRgn(lpRect->left, lpRect->top);
				pDC->FillRgn(&rgn, &brFill);
				pDC->FrameRgn(&rgn, &brFrame, 1,1);
				rgn.DeleteObject();
			}
			bWillRestart = pNode->bIsCloseNode;
		}
		else
			break;
	}

#if 1
	pDC->BeginPath();
	pDC->SetBkMode(TRANSPARENT);
#endif

	count=0;
	for(; index<(int)m_nNodeCount; index++,count++,pNode++)
	{
		if(pNode->bIsSplitPoint)
			continue;
		if(bWillRestart)
		{
			if(count>0)
				pDC->LineTo(pt0);
			count=0;
		}
		if(GNT_SHARP_ANGLE==pNode->nNodeType)
		{
			pNode->grptSharp.ToPoint(&pt1);
			if(count<=0)
				pDC->MoveTo(pt1);
			if(bWillRestart)
			{
				pt0 = pt1;
				pDC->MoveTo(pt1);
			}
			else
			{
				pDC->LineTo(pt1);
			}
		}
		else if(GNT_ROUND_ANGLE==pNode->nNodeType)
		{
			pRoundAngle=pNode->pRoundAngle;
			if(!pRoundAngle)
				continue;
			grPt = *(pRoundAngle->GetArcBgnPoint(!(pNode->bAnticlockwise)));
			grPt.ToPoint(&pt1);
			if(count<=0)
				pDC->MoveTo(pt1);
			if(bWillRestart)
				pt0 = pt1;
			else
				pDC->LineTo(pt1);
			pRoundAngle->PaintTo(pDC, !(pNode->bAnticlockwise), (MATH_PI/10000.0f));
		}
		else if(GNT_ELLIPSE==pNode->nNodeType)
		{
			pEllipse = pNode->pEllipse;
			if(!pEllipse)
				continue;
			pEllipse->GetEllipsesPoint(grPt, pEllipse->GetArcBgn(!(pNode->bAnticlockwise)));
			grPt.ToPoint(&pt1);
			if(count<=0)
				pDC->MoveTo(pt1);
			if(bWillRestart)
				pt0 = pt1;
			else
				pDC->LineTo(pt1);
			pEllipse->PaintTo(pDC, !(pNode->bAnticlockwise), ELLIPSE_RESOLUTION);
		}
		bWillRestart = pNode->bIsCloseNode;
	}
	if(count>0)
		pDC->LineTo(pt0);
#if 1
	pDC->EndPath();

	if(!rgn.m_hObject)
		rgn.CreateFromPath(pDC);

	if(rgn.m_hObject)
	{
		rgn.OffsetRgn(lpRect->left, lpRect->top);
		pDC->FillRgn(&rgn, &brFill);
		pDC->FrameRgn(&rgn, &brFrame, 1,1);
	}

	if(rgn.m_hObject)
		rgn.DeleteObject();
#endif


	CPoint cpt;
	CPen pen(PS_SOLID, 1, RGB(0,0,0));
	CPen *pOldPen=pDC->SelectObject(&pen);
	index = 0;
	pNode = &m_nodes[0];
	bWillRestart=TRUE;
	for(index=0; index<(int)m_nNodeCount; index++, pNode++)
	{
		if(!pNode->bIsSplitPoint)
			continue;
		if(GNT_SHARP_ANGLE==pNode->nNodeType)
		{
			pNode->grptSharp.ToCPoint(&cpt);
			cpt.Offset(lpRect->left, lpRect->top);
			if(bWillRestart)
			{
				pDC->MoveTo(cpt);
				bWillRestart=FALSE;
			}
			else
			{
				pDC->LineTo(cpt);
				bWillRestart=TRUE;
			}
		}
		else if(GNT_ELLIPSE==pNode->nNodeType)
		{

		}
		else if(GNT_INDEPENDENT_CIRCLE==pNode->nNodeType)
		{
			pRoundAngle=pNode->pRoundAngle;
			if(!pRoundAngle)
				continue;
			rc.left  = (int)(pRoundAngle->m_grArc.m_ptC0.fx-pRoundAngle->m_grArc.m_fRadius+0.5f);
			rc.top   = (int)(pRoundAngle->m_grArc.m_ptC0.fy-pRoundAngle->m_grArc.m_fRadius+0.5f);
			rc.right = rc.left + (int)(pRoundAngle->m_grArc.m_fRadius*2+0.5f);
			rc.bottom= rc.top + (int)(pRoundAngle->m_grArc.m_fRadius*2+0.5f);
			rgn.CreateEllipticRgnIndirect(&rc);
			if(rgn.m_hObject)
			{
				rgn.OffsetRgn(lpRect->left, lpRect->top);
				pDC->FillRgn(&rgn, &brFill);
				pDC->FrameRgn(&rgn, &brFrame, 1,1);
				rgn.DeleteObject();
			}
			bWillRestart = pNode->bIsCloseNode;
		}
	}
	if(pOldPen)
		pDC->SelectObject(pOldPen);
	if(pen.m_hObject)
		pen.DeleteObject();

	brFill.DeleteObject();
	brFrame.DeleteObject();

	DrawDimension(pDC, lpRect);
	
	this->Scale(1/fScale);
}

//画箭头
void DrawArrowhead(CDC *pDC, CGrPoint &ptBgn, CGrPoint &ptEnd)
{
	GR_LINE ln1, ln2;
	CPoint points[3];
	double fArc=(MATH_PI/6);
	CRgn rgn;
	CBrush br;
	br.CreateSolidBrush(RGB(96,96,96));
	if(pDC)
	{
		LineRevolve(ln2, ptBgn, ptEnd, (MATH_PI*2)-(fArc/2), 16);
		LineRevolve(ln1, ptBgn, ptEnd, fArc/2, 16);
		ln1.pt1.ToCPoint(&points[0]);
		ln2.pt1.ToCPoint(&points[1]);
		ptBgn.ToCPoint(&points[2]);
		rgn.CreatePolygonRgn(points, 3, RGN_OR);
		pDC->FillRgn(&rgn, &br);
	}
	if(rgn.m_hObject)
		rgn.DeleteObject();
	if(br.m_hObject)
		br.DeleteObject();
}

//将所有尺寸标注绘制到pDC指定的DC上
void CGrPath::DrawDimension(CDC *pDC, const LPCRECT lpRect)
{
	const COLORREF color=RGB(96,96,96);
	GR_DIMENSION *pDimension=NULL;
	double fDeltaArc=0, d, w, h;
	CGrPoint ptBgn, ptEnd, ptTxt;
	CPen pen(PS_SOLID, 1, color);
	CPen *pOldPen=NULL;
	GR_LINE line;
	CString str;
	CDC tmpDC;
	CFont *pOldFont=NULL, font;
	LOGFONT lf;
	int i;
	CGrArc grArc;

	if(!pDC)
		return;

	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 16;
	lf.lfWidth = 8;
	lf.lfWeight = 300;
	lf.lfQuality=PROOF_QUALITY;
	lf.lfPitchAndFamily=VARIABLE_PITCH | FF_SWISS;
	strcpy(lf.lfFaceName, "Arial");
	font.CreateFontIndirect(&lf);
	font.GetLogFont(&lf);

	pOldPen = pDC->SelectObject(&pen);
	pOldFont = pDC->SelectObject(&font);

	pDimension = &m_dimensions[0];
	for(i=0; i<(int)m_nDimentsionCount; i++,pDimension++)
	{
		str.Format("%s", pDimension->szMark);
		w = lf.lfWidth*(str.GetLength()+1);
		h = lf.lfHeight;
		switch(pDimension->nMarkType)
		{
		case 2:
		case 3:
			if(3==pDimension->nMarkType)
				grArc.InitArcA(pDimension->ptC0, pDimension->pt1, pDimension->pt2, TRUE);
			else
				grArc.InitArcA(pDimension->ptC0, pDimension->pt1, pDimension->pt2, FALSE);
			grArc.Offset(lpRect->left, lpRect->top);
			grArc.GetArcMidpoint(ptTxt);
			pDC->MoveTo((int)(grArc.m_ptArcBgn.fx), (int)(grArc.m_ptArcBgn.fy));
			grArc.PaintTo(pDC);
			LineRevolve(line, grArc.m_ptC0, grArc.m_ptArcBgn, -(MATH_PI/30), grArc.m_fRadius);
			DrawArrowhead(pDC, grArc.m_ptArcBgn, line.pt1);
			LineRevolve(line, grArc.m_ptC0, grArc.m_ptArcEnd, (MATH_PI/30), grArc.m_fRadius);
			DrawArrowhead(pDC, grArc.m_ptArcEnd, line.pt1);
			break;
		case 1:
		case 0:
		default:
			RetrieveDimensionPos(ptBgn, ptEnd, *pDimension);
			ptBgn.Offset(lpRect->left, lpRect->top);
			ptEnd.Offset(lpRect->left, lpRect->top);
			if(0==pDimension->nMarkType)
			{
				DrawArrowhead(pDC, ptBgn, ptEnd);
				if(pDimension->fMarkDistance>=2.0f)
				{
#if 0
					LineRevolve(line, ptBgn, ptEnd, -(MATH_PI/2), pDimension->fMarkDistance/2);
					pDC->MoveTo((int)(line.pt1.fx), (int)(line.pt1.fy));
					pDC->LineTo((int)(line.pt2.fx), (int)(line.pt2.fy));
#else
					LineRevolve(line, ptBgn, ptEnd, -(MATH_PI/2), pDimension->fMarkDistance);
					pDC->MoveTo((int)(line.ptCenter.fx), (int)(line.ptCenter.fy));
					pDC->LineTo((int)(line.pt1.fx), (int)(line.pt1.fy));
#endif
				}
			}
			
			DrawArrowhead(pDC, ptEnd, ptBgn);
			if(pDimension->fMarkDistance>=2.0f)
			{
#if 0
				LineRevolve(line, ptEnd, ptBgn, (MATH_PI/2), pDimension->fMarkDistance/2);
				pDC->MoveTo((int)(line.pt1.fx), (int)(line.pt1.fy));
				pDC->LineTo((int)(line.pt2.fx), (int)(line.pt2.fy));
#else
				LineRevolve(line, ptEnd, ptBgn, (MATH_PI/2), pDimension->fMarkDistance);
				pDC->MoveTo((int)(line.ptCenter.fx), (int)(line.ptCenter.fy));
				pDC->LineTo((int)(line.pt1.fx), (int)(line.pt1.fy));
#endif
			}
			
			pDC->MoveTo((int)(ptBgn.fx), (int)(ptBgn.fy));
			pDC->LineTo((int)(ptEnd.fx), (int)(ptEnd.fy));

			d = GetDistanceF(ptBgn, ptEnd);
			if(1==pDimension->nMarkType && d<(2.5f*w))
				ptTxt = ptBgn;
			else
				ptTxt.Set((ptBgn.fx+ptEnd.fx)/2, (ptBgn.fy+ptEnd.fy)/2);
		}

		if(pDimension->szMark[0])
		{
			CreateDC(&tmpDC, pDC, (int)w, (int)h);
			if(tmpDC.m_hDC)
			{
				tmpDC.SetTextColor(color);
				tmpDC.SetTextAlign(TA_CENTER);
				tmpDC.FillSolidRect(0, 0, (int)w, (int)h, RGB(255,255,255));
				tmpDC.TextOut((int)(w/2), 0, str);
				ConvertGraphCoordinate(&tmpDC);
				pDC->BitBlt((int)(ptTxt.fx-w/2), (int)(ptTxt.fy-(h/2)), (int)w, (int)h, &tmpDC, 0, 0, SRCCOPY);
				tmpDC.DeleteDC();
			}
			else
			{
				pDC->SetTextColor(RGB(0,0,0));
				pDC->SetTextAlign(TA_CENTER);
				pDC->TextOut((int)(ptTxt.fx), (int)(ptTxt.fy), str);
			}
		}
	}
	
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);

	if(pen.m_hObject)
		pen.DeleteObject();
	if(font.m_hObject)
		font.DeleteObject();
}


//生成G代码
const char* CGrPath::MakeGCode()
{
	int index, len, count, nSlices;
	GR_NODE *pNode=NULL;
	CRoundAngle *pRoundAngle=NULL;
	CGrPoint pt, pt0, ptLast, ptRelativeC0, ptBackupOrigin;
	BOOL bWillRestart;
	double fArc, fDelta, fArcEnd;
	int nCut=0;//1切割开始

	// 备份画图坐标
	ptBackupOrigin.Set(m_rcClip.fX0, m_rcClip.fY0);
	// 转换为G代码坐标
	this->Offset(-m_rcClip.fX0, -m_rcClip.fY0);

	len = 0;
	m_pGCodeBuff[len]='\0';

	ptLast.Set(0,0);

	len += sprintf(m_pGCodeBuff+len, "G90\r\n");
/*	if(m_nNodeCount)
	{
		len += sprintf(m_pGCodeBuff+len, "M14\r\n");
		len += sprintf(m_pGCodeBuff+len, "G00 X%.1f Y%.1f\r\n", m_rcClip.fX0, m_rcClip.fY0);
		len += sprintf(m_pGCodeBuff+len, "M13\r\n");
		len += sprintf(m_pGCodeBuff+len, "G01 X%.1f Y%.1f\r\n", m_rcClip.fX0, m_rcClip.fY1);
		len += sprintf(m_pGCodeBuff+len, "G01 X%.1f Y%.1f\r\n", m_rcClip.fX1, m_rcClip.fY1);
		len += sprintf(m_pGCodeBuff+len, "G01 X%.1f Y%.1f\r\n", m_rcClip.fX1, m_rcClip.fY0);
		len += sprintf(m_pGCodeBuff+len, "G01 X%.1f Y%.1f\r\n", m_rcClip.fX0, m_rcClip.fY0);
	}
*/

	index = 0;
	pNode = &(m_nodes[0]);
	bWillRestart = TRUE;
	
	for( ; index<(int)m_nNodeCount; index++,pNode++)
	{
		if(GNT_INDEPENDENT_CIRCLE==pNode->nNodeType)
		{
			pRoundAngle=pNode->pRoundAngle;
			if(!pRoundAngle)
				continue;
			pt = pRoundAngle->m_grArc.m_ptC0;
			pt.Offset(pRoundAngle->m_grArc.m_fRadius*(-1), 0);
			
			//圆心相对于圆弧起始点的坐标
			ptRelativeC0 = pRoundAngle->m_grArc.m_ptC0;
			ptRelativeC0.Offset(-pt.fx, -pt.fy);
            len += sprintf(m_pGCodeBuff+len, "M14\r\n");
			len += sprintf(m_pGCodeBuff+len, "G00 X%.2f Y%.2f\r\n", pt.fx, pt.fy);
            len += sprintf(m_pGCodeBuff+len, "M13\r\n");
			len += sprintf(m_pGCodeBuff+len, "%s ", (!(pNode->bAnticlockwise)? "G02":"G03"));
			len += sprintf(m_pGCodeBuff+len, "X%.2f Y%.2f I%.2f J%.2f\r\n", pt.fx, pt.fy, ptRelativeC0.fx, ptRelativeC0.fy);
			ptLast = pt;			
			bWillRestart = pNode->bIsCloseNode;
		}
		else
			break;
	}
	
	count=0;
	for(; index<(int)m_nNodeCount; index++,count++,pNode++)
	{
		if(pNode->bIsSplitPoint)
			continue;
		if(bWillRestart)
		{
			if(count>0)
			{
				if(ptLast.fx!=pt0.fx || ptLast.fy!=pt0.fy)
				{
					if (nCut==0)
					{
						len += sprintf(m_pGCodeBuff+len, "M13\r\n");
						nCut = 1;
					}					len += sprintf(m_pGCodeBuff+len, "G01 X%.2f Y%.2f\r\n", pt0.fx, pt0.fy);
					ptLast = pt0;
				}
			}			
			count=0;
		}
		if(GNT_SHARP_ANGLE==pNode->nNodeType)
		{
			pt = pNode->grptSharp;
			if(ptLast.fx!=pt.fx || ptLast.fy!=pt.fy)
			{
				if (bWillRestart)
				{
					len += sprintf(m_pGCodeBuff+len, "M14\r\n");
					nCut = 0;
				}
				else
				{   
					if (nCut==0)
					{				
						len += sprintf(m_pGCodeBuff+len, "M13\r\n");
						nCut = 1;
					}
				}
				len += sprintf(m_pGCodeBuff+len, "%s X%.2f Y%.2f\r\n", (bWillRestart? "G00" : "G01"), pt.fx, pt.fy);
				ptLast = pt;
			}
			if(bWillRestart)
				pt0 = pt;
			bWillRestart = pNode->bIsCloseNode;
		}
		else if(GNT_ROUND_ANGLE==pNode->nNodeType)
		{
			pRoundAngle=pNode->pRoundAngle;
			if(!pRoundAngle)
				continue;
			pt = *(pRoundAngle->GetArcBgnPoint(!(pNode->bAnticlockwise)));
			if(ptLast.fx!=pt.fx || ptLast.fy!=pt.fy)
			{
				if (bWillRestart)
				{
					len += sprintf(m_pGCodeBuff+len, "M14\r\n");
					nCut = 0;
				}
				else 									 
				{	
					if (nCut==0)
					{
						len += sprintf(m_pGCodeBuff+len, "M13\r\n");
						nCut = 1;
					}
				}
				len += sprintf(m_pGCodeBuff+len, "%s X%.2f Y%.2f\r\n", (bWillRestart? "G00" : "G01"), pt.fx, pt.fy);
				ptLast = pt;
			}
			if(bWillRestart)
				pt0 = pt;

			//圆心相对于圆弧起始点的坐标
			ptRelativeC0 = pRoundAngle->m_grArc.m_ptC0;
			ptRelativeC0.Offset(-pt.fx, -pt.fy);

			pt = *(pRoundAngle->GetArcEndPoint(!(pNode->bAnticlockwise)));
            if (nCut==0)				 
			{				
				len += sprintf(m_pGCodeBuff+len, "M13\r\n");
				nCut = 1;
			}
			len += sprintf(m_pGCodeBuff+len, "%s ", (!(pNode->bAnticlockwise)? "G02" : "G03"));
			len += sprintf(m_pGCodeBuff+len, "X%.2f Y%.2f I%.2f J%.2f\r\n", pt.fx, pt.fy,
				ptRelativeC0.fx,
				ptRelativeC0.fy);
			ptLast = pt;
			bWillRestart = pNode->bIsCloseNode;
		}
		else if(GNT_ELLIPSE==pNode->nNodeType)
		{
			fDelta = ELLIPSE_RESOLUTION;
			nSlices = (int)(pNode->pEllipse->GetSweepArc()/fDelta);
			fDelta = (pNode->pEllipse->GetSweepArc()/nSlices);	//修正

			fArc = pNode->pEllipse->GetArcBgn(!(pNode->bAnticlockwise));
			pNode->pEllipse->GetEllipsesPoint(pt, fArc);			
			if(ptLast.fx!=pt.fx || ptLast.fy!=pt.fy)
			{
				if (bWillRestart)
				{
					len += sprintf(m_pGCodeBuff+len, "M14\r\n");
					nCut = 0;
				}
				else 									 
				{	
					if (nCut==0)
					{
						len += sprintf(m_pGCodeBuff+len, "M13\r\n");
						nCut = 1;
					}
				}
				len += sprintf(m_pGCodeBuff+len, "%s X%.2f Y%.2f\r\n", (bWillRestart? "G00" : "G01"), pt.fx, pt.fy);
				ptLast = pt;
			}
			if(bWillRestart)
				pt0 = pt;
			fArcEnd = pNode->pEllipse->GetArcEnd(!(pNode->bAnticlockwise));
			if(pNode->bAnticlockwise)
			{
				while(fArc<=fArcEnd)
				{
					if(fArc<0)
						fArc += MATH_2PI;
					if(fArc>MATH_2PI)
						fArc -= MATH_2PI;
					pNode->pEllipse->GetEllipsesPoint(pt, fArc);
					if(ptLast.fx!=pt.fx || ptLast.fy!=pt.fy)//不是同一个点
					{
						if (nCut==0)
						{
							len += sprintf(m_pGCodeBuff+len, "M13\r\n");
							nCut = 1;
						}
						len += sprintf(m_pGCodeBuff+len, "G01 X%.2f Y%.2f\r\n", pt.fx, pt.fy);
					}
					ptLast = pt;
					fArc += fDelta;
				}
			}
			else
			{
				while(fArc>=fArcEnd)
				{
					if(fArc<0)
						fArc += MATH_2PI;
					if(fArc>MATH_2PI)
						fArc -= MATH_2PI;
					pNode->pEllipse->GetEllipsesPoint(pt, fArc);
					if(ptLast.fx!=pt.fx || ptLast.fy!=pt.fy)//不是同一个点
					{
						if (nCut==0)
						{
							len += sprintf(m_pGCodeBuff+len, "M13\r\n");
							nCut = 1;
						}
						len += sprintf(m_pGCodeBuff+len, "G01 X%.2f Y%.2f\r\n", pt.fx, pt.fy);
					}
					ptLast = pt;
					fArc -= fDelta;
				}
			}
			bWillRestart = pNode->bIsCloseNode;			
		}
	}
	if(count>0)
	{
		if(ptLast.fx!=pt0.fx || ptLast.fy!=pt0.fy)
		{

			if (nCut==0)
			{				
				len += sprintf(m_pGCodeBuff+len, "M13\r\n");
				nCut = 1;
			}
			len += sprintf(m_pGCodeBuff+len, "G01 X%.2f Y%.2f\r\n", pt0.fx, pt0.fy);
			ptLast = pt0;
		}
	}

	index = 0;
	pNode = &m_nodes[0];
	bWillRestart = TRUE;	
	for(index=0; index<(int)m_nNodeCount; index++, pNode++)
	{
		if(!pNode->bIsSplitPoint)
			continue;
		if(GNT_SHARP_ANGLE==pNode->nNodeType)
		{
			pt = pNode->grptSharp;
			if(bWillRestart)
			{
				if(ptLast.fx!=pt.fx || ptLast.fy!=pt.fy)
				{
					len += sprintf(m_pGCodeBuff+len, "G00 X%.2f Y%.2f\r\n", pt.fx, pt.fy);
					ptLast = pt;
				}
				bWillRestart=FALSE;
			}
			else
			{
				if(ptLast.fx!=pt.fx || ptLast.fy!=pt.fy)
				{
					len += sprintf(m_pGCodeBuff+len, "G01 X%.2f Y%.2f\r\n", pt.fx, pt.fy);
					ptLast = pt;
				}
				bWillRestart=TRUE;
			}
		}
		else if(GNT_ELLIPSE==pNode->nNodeType)
		{

		}
		else if(GNT_INDEPENDENT_CIRCLE==pNode->nNodeType)
		{
			pRoundAngle=pNode->pRoundAngle;
			if(!pRoundAngle)
				continue;
			pt = pRoundAngle->m_grArc.m_ptC0;
			pt.Offset(pRoundAngle->m_grArc.m_fRadius*(-1), 0);
			
			//圆心相对于圆弧起始点的坐标
			ptRelativeC0 = pRoundAngle->m_grArc.m_ptC0;
			ptRelativeC0.Offset(-pt.fx, -pt.fy);

			if(ptLast.fx!=pt.fx || ptLast.fy!=pt.fy)
			{
				len += sprintf(m_pGCodeBuff+len, "G00 X%.2f Y%.2f\r\n", pt.fx, pt.fy);
				ptLast = pt;
			}
			len += sprintf(m_pGCodeBuff+len, "%s ", (!(pNode->bAnticlockwise)? "G02":"G03"));
			len += sprintf(m_pGCodeBuff+len, "X%.2f Y%.2f I%.2f J%.2f\r\n", pt.fx, pt.fy, ptRelativeC0.fx, ptRelativeC0.fy);
			ptLast = pt;
			bWillRestart = pNode->bIsCloseNode;
		}
	}

	len += sprintf(m_pGCodeBuff+len, "M14\r\n");
	len += sprintf(m_pGCodeBuff+len, "G90G00X0Y0Z0\r\n");
	if(g_stu_pAxisG->bSpare)
		len += sprintf(m_pGCodeBuff+len, "M99\r\n");
    len += sprintf(m_pGCodeBuff+len, "M30\r\n");

	m_pGCodeBuff[len] = '\0';

	// 恢复画图坐标
	this->Offset(ptBackupOrigin.fx, ptBackupOrigin.fy);

	return m_pGCodeBuff;
}

//整体坐标偏移
void CGrPath::Offset(double fx, double fy)
{
	int index;
	GR_NODE *pNode=NULL;
	CRoundAngle *pRoundAngle=NULL;
	CGrEllipse *pEllipse=NULL;

	index = 0;
	pNode = &(m_nodes[0]);
	
	for( ; index<(int)m_nNodeCount; index++,pNode++)
	{
		pNode->grptSharp.Offset(fx, fy);
		pNode->fMinWidth += fx;
		pNode->fMinHeight += fy;
		pRoundAngle=pNode->pRoundAngle;
		if(pRoundAngle)
			pRoundAngle->Offset(fx, fy);
		pEllipse=pNode->pEllipse;
		if(pEllipse)
			pEllipse->Offset(fx, fy);
	}

	GR_DIMENSION *pDimension=NULL;
	int i;
	
	pDimension = &m_dimensions[0];
	for(i=0; i<(int)m_nDimentsionCount; i++,pDimension++)
	{
		pDimension->pt1.Offset(fx, fy);
		pDimension->pt2.Offset(fx, fy);
		pDimension->ptC0.Offset(fx, fy);
	}

	UpdateClipRect();
}

//添加一条线段尺寸标注线
BOOL CGrPath::DimensionAppendD(const CGrPoint &ptLineBgn, const CGrPoint &ptLineEnd, LPCTSTR lpszMark, double fMarkDistance/*=16*/)
{
	GR_DIMENSION dimension;
	memset(&dimension, 0, sizeof(GR_DIMENSION));
	dimension.nMarkType = 0;
	dimension.fMarkDistance = fMarkDistance;
	dimension.pt1 = ptLineBgn;
	dimension.pt2 = ptLineEnd;
	if(lpszMark)
		strncpy(dimension.szMark, lpszMark, 16-1);
	return (this->DimensionAppend(dimension));
}

//添加一条线段尺寸标注线
BOOL CGrPath::DimensionAppendD(double fxBgn, double fyBgn, double fxEnd, double fyEnd, LPCTSTR lpszMark, double fMarkDistance/*=16*/)
{
	CGrPoint ptBgn, ptEnd;
	ptBgn.Set(fxBgn, fyBgn);
	ptEnd.Set(fxEnd, fyEnd);
	return DimensionAppendD(ptBgn, ptEnd, lpszMark, fMarkDistance);
}

//添加一条线段尺寸标注线
BOOL CGrPath::DimensionAppendD(const GR_LINE &line, LPCTSTR lpszMark, double fMarkDistance/*=16*/)
{
	return DimensionAppendD(line.pt1, line.pt2, lpszMark, fMarkDistance);
}

//添加一个圆弧节点
BOOL CGrPath::AddArcNode(const CGrArc &Arc, BOOL bClockWiseDrawing/*=TRUE*/)
{
	CRoundAngle *pRA = new CRoundAngle;
	if(!pRA)	return FALSE;
	pRA->m_grArc = Arc;
	pRA->m_fVertexArc = (MATH_PI-Arc.m_fArc);
	pRA->m_ptVertex.Set(0, 0);

	GR_NODE node;
	memset(&node, 0, sizeof(GR_NODE));
	node.nNodeType = GNT_ROUND_ANGLE;
	node.pRoundAngle = pRA;
	node.bAnticlockwise = !bClockWiseDrawing;
	if(!this->NodeAppend(node))
	{
		delete pRA;
		return FALSE;
	}
	return TRUE;
}


//添加一个独立圆节点
BOOL CGrPath::AddIndependentCircleNode(CGrArc &Arc)
{
	GR_NODE *pLatestNode=NULL;
	if(!AddArcNode(Arc))
		return FALSE;
	if(!m_nNodeCount)
		return FALSE;
	pLatestNode = &m_nodes[m_nNodeCount-1];
	pLatestNode->nNodeType = GNT_INDEPENDENT_CIRCLE;
	pLatestNode->bIsCloseNode=TRUE;
	return TRUE;
}

//添加一个椭圆弧节点
BOOL CGrPath::AddEllipseNode(CGrEllipse &grEllipse, BOOL bClockWiseDrawing/*=TRUE*/)
{
	CGrEllipse *pEllipse = new CGrEllipse;
	if(!pEllipse)	return FALSE;
	//memcpy(pEllipse, &grEllipse, sizeof(CGrEllipse));
	*pEllipse = grEllipse;
	GR_NODE node;
	memset(&node, 0, sizeof(GR_NODE));
	node.nNodeType = GNT_ELLIPSE;
	node.pEllipse = pEllipse;
	node.bAnticlockwise = !bClockWiseDrawing;
	if(!this->NodeAppend(node))
	{
		delete pEllipse;
		return FALSE;
	}
	return TRUE;
}

//添加一个分割节点，每两个分割节点构成一条分割线
BOOL CGrPath::AddSplitNode(const CGrPoint &point)
{
	GR_NODE grNode;
	memset(&grNode, 0, sizeof(GR_NODE));
	grNode.nNodeType = GNT_SHARP_ANGLE;
	grNode.bIsSplitPoint = TRUE;
	grNode.grptSharp = point;
	return this->NodeAppend(grNode);
}

//添加一个分割圆节点
BOOL CGrPath::AddSplitCircle(const CGrArc &arc, BOOL bClockWiseDrawing/*=TRUE*/)
{
	GR_NODE *pLatestNode=NULL;
	if(!AddArcNode(arc, bClockWiseDrawing))
		return FALSE;
	if(!m_nNodeCount)
		return FALSE;
	pLatestNode = &m_nodes[m_nNodeCount-1];
	pLatestNode->nNodeType = GNT_INDEPENDENT_CIRCLE;
	pLatestNode->bIsCloseNode=TRUE;
	pLatestNode->bIsSplitPoint=TRUE;
	return TRUE;
}


//添加一个圆角节点
BOOL CGrPath::AddRoundAngleNode(const CGrPoint &ptVertex, const CGrArc &Arc, BOOL bClockWiseDrawing/*=TRUE*/)
{
	GR_NODE *pLatestNode=NULL;
	if(!AddArcNode(Arc))
		return FALSE;
	if(!m_nNodeCount)
		return FALSE;
	pLatestNode = &m_nodes[m_nNodeCount-1];
	pLatestNode->pRoundAngle->m_ptVertex = ptVertex;
	pLatestNode->bAnticlockwise = !bClockWiseDrawing;
	return TRUE;
}


//添加一条半径尺寸标注线
BOOL CGrPath::DimensionAppendR(const CGrPoint &ptLineBgn, const CGrPoint &ptLineEnd, LPCTSTR lpszMark, double fMarkDistance/*=0*/)
{
	GR_DIMENSION dimension;
	memset(&dimension, 0, sizeof(GR_DIMENSION));
	dimension.nMarkType = 1;
	dimension.fMarkDistance = fMarkDistance;
	dimension.pt1 = ptLineBgn;
	dimension.pt2 = ptLineEnd;
	if(lpszMark)
		strncpy(dimension.szMark, lpszMark, 16-1);
	return this->DimensionAppend(dimension);
}

//添加一条半径尺寸标注线
BOOL CGrPath::DimensionAppendR(const CGrPoint &ptCO, double radius, double arc, LPCTSTR lpszMark, double fMarkDistance/*=0*/)
{
	GR_DIMENSION dimension;
	GR_LINE line;
	memset(&dimension, 0, sizeof(GR_DIMENSION));
	dimension.nMarkType = 1;
	dimension.fMarkDistance = fMarkDistance;
	dimension.pt1 = ptCO;
	dimension.pt2 = dimension.pt1;
	dimension.pt2.Offset(radius, 0);
	if(arc!=0.0f)
	{
		LineRevolve(line, dimension.pt1, dimension.pt2, arc, radius);
		dimension.pt2 = line.pt1;
	}
	if(lpszMark)
		strncpy(dimension.szMark, lpszMark, 16-1);
	return this->DimensionAppend(dimension);
}

//添加一条角度标注线
BOOL CGrPath::DimensionAppendA(const CGrPoint &ptC0, const CGrPoint &ptBgn, const CGrPoint &ptEnd, LPCTSTR lpszMark, BOOL bGreaterArc/*=FALSE*/)
{
	GR_DIMENSION dimension;
	memset(&dimension, 0, sizeof(GR_DIMENSION));
	if(bGreaterArc)
		dimension.nMarkType = 3;
	else
		dimension.nMarkType = 2;
	dimension.fMarkDistance = 0;
	dimension.pt1 = ptBgn;
	dimension.pt2 = ptEnd;
	dimension.ptC0 = ptC0;
	if(lpszMark)
		strncpy(dimension.szMark, lpszMark, 16-1);
	return this->DimensionAppend(dimension);
}


//确定标志线在图形中的绘制位置
void CGrPath::RetrieveDimensionPos(CGrPoint &oPt1, CGrPoint &oPt2, const GR_DIMENSION &iDimension)
{
	GR_DIMENSION dimension;
	GR_LINE line;
	double fLength, fOffset;
	//fOffset = ((iDimension.fMarkDistance/2)+1.0f);
	fOffset = ((iDimension.fMarkDistance)+1.0f);
	if(iDimension.pt1.fx==iDimension.pt2.fx)
	{
		oPt1 = iDimension.pt1;
		oPt2 = iDimension.pt2;
		if(oPt1.fy > oPt2.fy)
		{
			oPt1.Offset(fOffset, 0);
			oPt2.Offset(fOffset, 0);
		}
		else
		{
			oPt1.Offset(-fOffset, 0);
			oPt2.Offset(-fOffset, 0);
		}
	}
	else if(iDimension.pt1.fy==iDimension.pt2.fy)
	{
		oPt1 = iDimension.pt1;
		oPt2 = iDimension.pt2;
		if(oPt1.fx > oPt2.fx)
		{
			oPt1.Offset(0, -fOffset);
			oPt2.Offset(0, -fOffset);
		}
		else
		{
			oPt1.Offset(0, fOffset);
			oPt2.Offset(0, fOffset);
		}
	}
	else
	{
		fLength = GetDistanceF(iDimension.pt1, iDimension.pt2);
		//LineRevolve(line, iDimension.pt1, iDimension.pt2, MATH_PI/2, (iDimension.fMarkDistance/2)+1.0f);
		LineRevolve(line, iDimension.pt1, iDimension.pt2, MATH_PI/2, (iDimension.fMarkDistance)+1.0f);
		oPt1 = line.pt1;
		LineRevolve(line, oPt1, iDimension.pt1, MATH_PI/2, fLength);
		oPt2 = line.pt1;
	}
}



void CGrPath::GetGraphRect(GR_RECT &rcGraph)
{
	GR_RECT rc;
	GetPathRect(rcGraph);
	GetDimensionsRect(rc);
	if(rcGraph.fX0>rc.fX0)
		rcGraph.fX0 = rc.fX0;
	if(rcGraph.fY0>rc.fY0)
		rcGraph.fY0 = rc.fY0;
	if(rcGraph.fX1<rc.fX1)
		rcGraph.fX1 = rc.fX1;
	if(rcGraph.fY1<rc.fY1)
		rcGraph.fY1 = rc.fY1;
}

void CGrPath::GetPathRect(GR_RECT &rcPath)
{
	GR_NODE *pNode=NULL;
	GR_RECT rc;
	CRoundAngle *pRoundAngle=NULL;
	CGrEllipse *pEllipse=NULL;
	UINT i;
	
	memset(&rcPath, 0, sizeof(GR_RECT));
	rcPath.fX0 = (double)(0x0FFFFFFF);
	rcPath.fY0 = (double)(0x0FFFFFFF);
	rcPath.fX1 = -(double)(0x0FFFFFFF);
	rcPath.fY1 = -(double)(0x0FFFFFFF);
	for(i=0; i<m_nNodeCount; i++)
	{
		pNode = &m_nodes[i];
		memset(&rc, 0, sizeof(GR_RECT));
		switch(pNode->nNodeType)
		{
		case GNT_SHARP_ANGLE:
			rc.fX0 = pNode->grptSharp.fx;
			rc.fY0 = pNode->grptSharp.fy;
			rc.fX1 = pNode->grptSharp.fx;
			rc.fY1 = pNode->grptSharp.fy;
			break;
		case GNT_ROUND_ANGLE:
		case GNT_INDEPENDENT_CIRCLE:
			pRoundAngle = pNode->pRoundAngle;
			if(!pRoundAngle)
				continue;
			if(GNT_INDEPENDENT_CIRCLE==pNode->nNodeType)
			{
				rc.fX0 = (pRoundAngle->m_grArc.m_ptC0.fx-pRoundAngle->m_grArc.m_fRadius);
				rc.fY0 = (pRoundAngle->m_grArc.m_ptC0.fy-pRoundAngle->m_grArc.m_fRadius);
				rc.fX1 = rc.fX0 + (pRoundAngle->m_grArc.m_fRadius*2);
				rc.fY1 = rc.fY0 + (pRoundAngle->m_grArc.m_fRadius*2);
			}
			else
			{
				pRoundAngle->m_grArc.GetOutline(rc);
			}
			break;
		case GNT_ELLIPSE:
			pEllipse = pNode->pEllipse;
			if(!pEllipse)
				continue;
			pEllipse->GetOutline(rc);
			break;
		default:
			continue;
			break;
		}
		
		if(rcPath.fX0>rc.fX0)
			rcPath.fX0 = rc.fX0;
		if(rcPath.fY0>rc.fY0)
			rcPath.fY0 = rc.fY0;
		if(rcPath.fX1<rc.fX1)
			rcPath.fX1 = rc.fX1;
		if(rcPath.fY1<rc.fY1)
			rcPath.fY1 = rc.fY1;
	}
}

void CGrPath::GetDimensionsRect(GR_RECT &rcDimensions)
{
	GR_RECT rc;
	CRoundAngle *pRoundAngle=NULL;
	CGrEllipse *pEllipse=NULL;
	GR_DIMENSION *pDimension=NULL;
	UINT i;
	
	memset(&rcDimensions, 0, sizeof(GR_RECT));
	rcDimensions.fX0 = (double)(0x0FFFFFFF);
	rcDimensions.fY0 = (double)(0x0FFFFFFF);
	rcDimensions.fX1 = -(double)(0x0FFFFFFF);
	rcDimensions.fY1 = -(double)(0x0FFFFFFF);

	for(i=0; i<m_nDimentsionCount; i++)
	{
		pDimension = &m_dimensions[i];
		rc.fX0 = min(pDimension->pt1.fx, pDimension->pt2.fx);
		rc.fY0 = min(pDimension->pt1.fy, pDimension->pt2.fy);
		rc.fX1 = max(pDimension->pt1.fx, pDimension->pt2.fx);
		rc.fY1 = max(pDimension->pt1.fy, pDimension->pt2.fy);
		
		if(rcDimensions.fX0>rc.fX0)
			rcDimensions.fX0 = rc.fX0;
		if(rcDimensions.fY0>rc.fY0)
			rcDimensions.fY0 = rc.fY0;
		if(rcDimensions.fX1<rc.fX1)
			rcDimensions.fX1 = rc.fX1;
		if(rcDimensions.fY1<rc.fY1)
			rcDimensions.fY1 = rc.fY1;
	}
}

//生成套料用的格式
CString CGrPath::MakeNestData()
{
	int index,count, nSlices;
	GR_NODE *pNode=NULL;
	CRoundAngle *pRoundAngle=NULL;
	CGrPoint pt, pt0, ptLast, ptRelativeC0, ptBackupOrigin;
	BOOL bWillRestart;
	double fArc, fDelta, fArcEnd;	
    CString strTemp,strCode;
    BOOL bUseG00 = FALSE;


	if(m_nNodeCount)
	{
		strTemp.Format("%f,%f;",m_rcClip.fX1,m_rcClip.fY1);
		strCode += strTemp;
	}


	index = 0;
	pNode = &(m_nodes[0]);
	bWillRestart = TRUE;
	
// 	if (pNode && pNode->grptSharp.fx==0.0&&pNode->grptSharp.fy==0.0)
// 	{
// 		strTemp.Format("0 %f,%f;",pt.fx, pt.fy);
// 		strCode += strTemp; 
// 	}
	for( ; index<(int)m_nNodeCount; index++,pNode++)
	{
		if(GNT_INDEPENDENT_CIRCLE==pNode->nNodeType)
		{
			pRoundAngle=pNode->pRoundAngle;
			if(!pRoundAngle)
				continue;
			pt = pRoundAngle->m_grArc.m_ptC0;
			pt.Offset(pRoundAngle->m_grArc.m_fRadius*(-1), 0);
			
			//圆心相对于圆弧起始点的坐标
			ptRelativeC0 = pRoundAngle->m_grArc.m_ptC0;
			ptRelativeC0.Offset(-pt.fx, -pt.fy);
			strTemp.Format("0 %f,%f;",pt.fx, pt.fy);
			bUseG00 = TRUE;
			strCode += strTemp;
			CGrPoint pOrign = pRoundAngle->m_grArc.m_ptC0;
			double dRadiu = pRoundAngle->m_grArc.m_fRadius;
			CGrPoint dStartPoint = *(pRoundAngle->GetArcBgnPoint(!(pNode->bAnticlockwise)));
			dStartPoint.Offset(-pOrign.fx,-pOrign.fy);
			double dfArc = pRoundAngle->m_grArc.m_fArc;
			double fFx, fFy;
			fFx = (dStartPoint.fx<0)? (-1) : (1);	
			fFy = (dStartPoint.fy<0)? (-1) : (1);	
			double fArcBgn = atan((dStartPoint.fy*fFy)/(dStartPoint.fx*fFx));
			int nQuadrant = GetPointQuadrant(dStartPoint);
			switch(nQuadrant)
			{
			case 0:	fArcBgn = fArcBgn;				break;
			case 1:	fArcBgn = MATH_PI-fArcBgn;		break;
			case 2:	fArcBgn = MATH_PI+fArcBgn;		break;
			case 3:	fArcBgn = (MATH_PI*2)-fArcBgn;	break;
			default:	break;
			}
			fArcBgn = fArcBgn*180/MATH_PI;
			dfArc = dfArc*180/MATH_PI;
			if (pNode->bAnticlockwise)
			{
				strTemp.Format("2 %f,%f,%f,%f,%f;",pOrign.fx,pOrign.fy,dRadiu,fArcBgn,dfArc);
			}
			else
			{
				strTemp.Format("2 %f,%f,%f,%f,%f;",pOrign.fx,pOrign.fy,dRadiu,fArcBgn,-dfArc);
			}
			strCode += strTemp;
			
			ptLast = pt;			
			bWillRestart = pNode->bIsCloseNode;
		}
		else
			break;
	}
	
	count=0;
	for(; index<(int)m_nNodeCount; index++,count++,pNode++)
	{
		if(pNode->bIsSplitPoint)
			continue;
		if(bWillRestart)
		{
			if(count>0)
			{
				if(ptLast.fx!=pt0.fx || ptLast.fy!=pt0.fy)
				{
					if (!bUseG00)
					{
						strTemp.Format("0 %f,%f;",ptLast.fx, ptLast.fy);
						strCode += strTemp;
						bUseG00 = TRUE;
					}
					strTemp.Format("1 %f,%f;",pt0.fx, pt0.fy);
					strCode += strTemp;
					ptLast = pt0;
				}
			}			
			count=0;
		}
		if(GNT_SHARP_ANGLE==pNode->nNodeType)
		{
			pt = pNode->grptSharp;
			if(ptLast.fx!=pt.fx || ptLast.fy!=pt.fy)
			{				
				if (bWillRestart)
				{
                    strTemp.Format("0 %f,%f;",pt.fx, pt.fy);
					bUseG00 = TRUE;
				}
				else
				{
					if (!bUseG00)
					{
						strTemp.Format("0 %f,%f;",ptLast.fx, ptLast.fy);
						strCode += strTemp;
					}
					strTemp.Format("1 %f,%f;",pt.fx, pt.fy);
				}
				strCode += strTemp;
				ptLast = pt;
			}
			if(bWillRestart)
				pt0 = pt;
			bWillRestart = pNode->bIsCloseNode;
		}
		else if(GNT_ROUND_ANGLE==pNode->nNodeType)
		{
			pRoundAngle=pNode->pRoundAngle;
			if(!pRoundAngle)
				continue;
			pt = *(pRoundAngle->GetArcBgnPoint(!(pNode->bAnticlockwise)));
			if(ptLast.fx!=pt.fx || ptLast.fy!=pt.fy)
			{
				
				if (bWillRestart)
				{
                    strTemp.Format("0 %f,%f;",pt.fx, pt.fy);
					bUseG00 = TRUE;
				}
				else
				{
					if (!bUseG00)
					{
						strTemp.Format("0 %f,%f;",ptLast.fx, ptLast.fy);
						strCode += strTemp;
						bUseG00 = TRUE;
					}
					strTemp.Format("1 %f,%f;",pt.fx, pt.fy);
				}
				strCode += strTemp;
				ptLast = pt;
			}
			if(bWillRestart)
				pt0 = pt;

			//圆心相对于圆弧起始点的坐标
			ptRelativeC0 = pRoundAngle->m_grArc.m_ptC0;
			ptRelativeC0.Offset(-pt.fx, -pt.fy);

			pt = *(pRoundAngle->GetArcEndPoint(!(pNode->bAnticlockwise)));
            
			CGrPoint pOrign = pRoundAngle->m_grArc.m_ptC0;
			double dRadiu = pRoundAngle->m_grArc.m_fRadius;
			CGrPoint dStartPoint = *(pRoundAngle->GetArcBgnPoint(!(pNode->bAnticlockwise)));
			dStartPoint.Offset(-pOrign.fx,-pOrign.fy);
			double dfArc = pRoundAngle->m_grArc.m_fArc;
			double fFx, fFy;
			fFx = (dStartPoint.fx<0)? (-1) : (1);	
			fFy = (dStartPoint.fy<0)? (-1) : (1);	
			double fArcBgn = atan((dStartPoint.fy*fFy)/(dStartPoint.fx*fFx));
			int nQuadrant = GetPointQuadrant(dStartPoint);
			switch(nQuadrant)
			{
			case 0:	fArcBgn = fArcBgn;				break;
			case 1:	fArcBgn = MATH_PI-fArcBgn;		break;
			case 2:	fArcBgn = MATH_PI+fArcBgn;		break;
			case 3:	fArcBgn = (MATH_PI*2)-fArcBgn;	break;
			default:	break;
			}
			fArcBgn = fArcBgn*180/MATH_PI;
			dfArc = dfArc*180/MATH_PI;
			if (!bUseG00)
			{
				strTemp.Format("0 %f,%f;",ptLast.fx, ptLast.fy);
				strCode += strTemp;
				bUseG00 = TRUE;
			}
			if (pNode->bAnticlockwise)
			{
				strTemp.Format("2 %f,%f,%f,%f,%f;",pOrign.fx,pOrign.fy,dRadiu,fArcBgn,dfArc);
			}
			else
			{
				strTemp.Format("2 %f,%f,%f,%f,%f;",pOrign.fx,pOrign.fy,dRadiu,fArcBgn,-dfArc);
			}
            strCode += strTemp;
			ptLast = pt;
			bWillRestart = pNode->bIsCloseNode;
		}
		else if(GNT_ELLIPSE==pNode->nNodeType)
		{
			fDelta = ELLIPSE_RESOLUTION;
			nSlices = (int)(pNode->pEllipse->GetSweepArc()/fDelta);
			fDelta = (pNode->pEllipse->GetSweepArc()/nSlices);	//修正

			fArc = pNode->pEllipse->GetArcBgn(!(pNode->bAnticlockwise));
			pNode->pEllipse->GetEllipsesPoint(pt, fArc);			
			if(ptLast.fx!=pt.fx || ptLast.fy!=pt.fy)
			{				
				if (bWillRestart)
				{
                    strTemp.Format("0 %f,%f;",pt.fx, pt.fy);
					bUseG00 = TRUE;
				}
				else
				{
					if (!bUseG00)
					{
						strTemp.Format("0 %f,%f;",ptLast.fx, ptLast.fy);
						strCode += strTemp;
						bUseG00 = TRUE;
					}
					strTemp.Format("1 %f,%f;",pt.fx, pt.fy);
				}
				strCode += strTemp;
				ptLast = pt;
			}
			if(bWillRestart)
				pt0 = pt;
			fArcEnd = pNode->pEllipse->GetArcEnd(!(pNode->bAnticlockwise));
			if(pNode->bAnticlockwise)
			{
				while(fArc<=fArcEnd)
				{
					if(fArc<0)
						fArc += MATH_2PI;
					if(fArc>MATH_2PI)
						fArc -= MATH_2PI;
					pNode->pEllipse->GetEllipsesPoint(pt, fArc);
					if (!bUseG00)
					{
						strTemp.Format("0 %f,%f;",ptLast.fx, ptLast.fy);
						strCode += strTemp;
						bUseG00 = TRUE;
					}
					strTemp.Format("1 %f,%f;",pt.fx, pt.fy);
					strCode += strTemp;					
					ptLast = pt;
					fArc += fDelta;
				}
			}
			else
			{
				while(fArc>=fArcEnd)
				{
					if(fArc<0)
						fArc += MATH_2PI;
					if(fArc>MATH_2PI)
						fArc -= MATH_2PI;
					pNode->pEllipse->GetEllipsesPoint(pt, fArc);
					if (!bUseG00)
					{
						strTemp.Format("0 %f,%f;",ptLast.fx, ptLast.fy);
						strCode += strTemp;
						bUseG00 = TRUE;
					}
					strTemp.Format("1 %f,%f;",pt.fx, pt.fy);
					strCode += strTemp;	
					ptLast = pt;
					fArc -= fDelta;
				}
			}
			bWillRestart = pNode->bIsCloseNode;			
		}
	}
	if(count>0)
	{
		if(ptLast.fx!=pt0.fx || ptLast.fy!=pt0.fy)
		{
			if (!bUseG00)
			{
				strTemp.Format("0 %f,%f;",ptLast.fx, ptLast.fy);
				strCode += strTemp;
				bUseG00 = TRUE;
			}
			strTemp.Format("1 %f,%f;",pt0.fx, pt0.fy);
			strCode += strTemp;	
			ptLast = pt0;
		}
	}

	index = 0;
	pNode = &m_nodes[0];
	bWillRestart = TRUE;	
	for(index=0; index<(int)m_nNodeCount; index++, pNode++)
	{
		if(!pNode->bIsSplitPoint)
			continue;
		if(GNT_SHARP_ANGLE==pNode->nNodeType)
		{
			pt = pNode->grptSharp;
			if(bWillRestart)
			{
				if(ptLast.fx!=pt.fx || ptLast.fy!=pt.fy)
				{
					strTemp.Format("0 %f,%f;",pt.fx, pt.fy);
					strCode += strTemp;	
					bUseG00 = TRUE;
					ptLast = pt;
				}
				bWillRestart=FALSE;
			}
			else
			{
				if(ptLast.fx!=pt.fx || ptLast.fy!=pt.fy)
				{
					strTemp.Format("0 %f,%f;",pt.fx, pt.fy);
					strCode += strTemp;	
					bUseG00 = TRUE;
					ptLast = pt;
				}
				bWillRestart=TRUE;
			}
		}
		
		else if(GNT_INDEPENDENT_CIRCLE==pNode->nNodeType)
		{
			pRoundAngle=pNode->pRoundAngle;
			if(!pRoundAngle)
				continue;
			pt = pRoundAngle->m_grArc.m_ptC0;
			pt.Offset(pRoundAngle->m_grArc.m_fRadius*(-1), 0);
			
			//圆心相对于圆弧起始点的坐标
			ptRelativeC0 = pRoundAngle->m_grArc.m_ptC0;
			ptRelativeC0.Offset(-pt.fx, -pt.fy);

			if(ptLast.fx!=pt.fx || ptLast.fy!=pt.fy)
			{				
				strTemp.Format("0 %f,%f;",pt.fx, pt.fy);
				strCode += strTemp;	
				bUseG00 = TRUE;
				ptLast = pt;
			}

			CGrPoint pOrign = pRoundAngle->m_grArc.m_ptC0;
			double dRadiu = pRoundAngle->m_grArc.m_fRadius;
			CGrPoint dStartPoint = *(pRoundAngle->GetArcBgnPoint(!(pNode->bAnticlockwise)));
			dStartPoint.Offset(-pOrign.fx,-pOrign.fy);
			double dfArc = pRoundAngle->m_grArc.m_fArc;
			double fFx, fFy;
			fFx = (dStartPoint.fx<0)? (-1) : (1);	
			fFy = (dStartPoint.fy<0)? (-1) : (1);	
			double fArcBgn = atan((dStartPoint.fy*fFy)/(dStartPoint.fx*fFx));
			int nQuadrant = GetPointQuadrant(dStartPoint);
			switch(nQuadrant)
			{
			case 0:	fArcBgn = fArcBgn;				break;
			case 1:	fArcBgn = MATH_PI-fArcBgn;		break;
			case 2:	fArcBgn = MATH_PI+fArcBgn;		break;
			case 3:	fArcBgn = (MATH_PI*2)-fArcBgn;	break;
			default:	break;
			}
			fArcBgn = fArcBgn*180/MATH_PI;
			dfArc = dfArc*180/MATH_PI;
			if (pNode->bAnticlockwise)
			{
				strTemp.Format("2 %f,%f,%f,%f,%f;",pOrign.fx,pOrign.fy,dRadiu,fArcBgn,dfArc);
			}
			else
			{
				strTemp.Format("2 %f,%f,%f,%f,%f;",pOrign.fx,pOrign.fy,dRadiu,fArcBgn,-dfArc);
			}
            strCode += strTemp;
			ptLast = pt;
			bWillRestart = pNode->bIsCloseNode;
		}
	}
	return strCode;
}