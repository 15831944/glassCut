// dlg_ShowExtra.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "dlg_ShowExtra.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cdlg_ShowExtra dialog


Cdlg_ShowExtra::Cdlg_ShowExtra(CWnd* pParent /*=NULL*/)
	: CDialog(Cdlg_ShowExtra::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cdlg_ShowExtra)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nShowExpandX = 1024;
	m_nShowExpandY = 768;
	m_dScale = 0;
	m_nShowShelf = GetPrivateProfileInt("SHOW","SHELF",0,INIFILE_ADDEXTRA);
	m_nShelfFont = GetPrivateProfileInt("SHEET","FONTBIG2",22,"D:\\program files\\GlassCutter\\ExtraPar.ini");

}


void Cdlg_ShowExtra::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdlg_ShowExtra)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cdlg_ShowExtra, CDialog)
	//{{AFX_MSG_MAP(Cdlg_ShowExtra)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cdlg_ShowExtra message handlers

void Cdlg_ShowExtra::OnCancel() 
{
	// TODO: Add extra cleanup here
	
//	CDialog::OnCancel();
}

void Cdlg_ShowExtra::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

BOOL Cdlg_ShowExtra::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowPos(CWnd::GetOwner(),EXTRASHOWORIGNX,0,m_nShowExpandX+EXTRASHOWORIGNX,m_nShowExpandY,SWP_SHOWWINDOW);    
	return TRUE;  	              
}

void Cdlg_ShowExtra::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rect(EXTRASHOWORIGNX,0,m_nShowExpandX+EXTRASHOWORIGNX,m_nShowExpandY);

	CBitmap bitmap;	
	MemuDc.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc,m_nShowExpandX,m_nShowExpandY);
	CBitmap *oldBit = MemuDc.SelectObject(&bitmap);	
	MemuDc.FillSolidRect(0,0,m_nShowExpandX,m_nShowExpandY,RGB(255,255,255));
	CPen pen(PS_SOLID, 4, RGB(0,0,0));
	CPen *oldPen = MemuDc.SelectObject(&pen);
	DrawGraph();
	dc.StretchBlt(0,0,m_nShowExpandX,m_nShowExpandY,&MemuDc,0,0,m_nShowExpandX,m_nShowExpandY,SRCCOPY);
	MemuDc.SelectObject(oldBit);
	MemuDc.SelectObject(oldPen);
	pen.DeleteObject();
	bitmap.DeleteObject();
	MemuDc.DeleteDC();	
	
}

void Cdlg_ShowExtra::DrawGraph()
{
    PTRACK      pGreen;         	
	if(g_ExtraShow.Next)
	{		
		if (g_pShowSmall->nX>0 && g_pShowSmall->nY>0)//如果有小片矩形信息显示
		{		
			DrawRect(&MemuDc,0,0,g_pShowSmall->nX,g_pShowSmall->nY,0);
			CString str;
			str.Format("%s  %s",g_pShowSmall->strStorage,g_strExtraFile);
			MemuDc.SetTextAlign(TA_LEFT|TA_BOTTOM);
			DrawTextOut(0,g_pShowSmall->nY+10,str,25);
                  
			if (g_pShowSmall->pShowSmall != NULL)
			{  
				double dScale = 1.0;//字体显示比例
				pSmallInf smInf;
				for (smInf=g_pShowSmall->pShowSmall;smInf;smInf=smInf->pNext)
				{
					if (smInf->nSizeX < 100 || smInf->nSizeY<100)
					{
						dScale = 0.4;
					}
					else if (smInf->nSizeX < 200 || smInf->nSizeY<200)
					{
						dScale = 0.6;
					}
					else if (smInf->nSizeX < 400 || smInf->nSizeY<400)
					{
						dScale = 0.7;
					}
					else
					{
						dScale = 1.0;
					}
					if (smInf->strShelf == "*")//显示余片//余片尺寸大于100显示
					{
						if (smInf->nSizeX>100 && smInf->nSizeY>100 && smInf->strNum.GetLength()>0 && smInf->strNum.GetAt(0) != 0x0a)
						{
							MemuDc.SetTextAlign(TA_RIGHT|TA_BOTTOM);
							str = smInf->strSizeY;
							DrawTextOut(smInf->nOX+smInf->nSizeX,smInf->nOY,str,28*dScale);
							str = smInf->strSizeX;
							
							CFont   font; 
							font.CreateFont((int)(28*dScale),0,0,0,FW_THIN,0,0,0,ANSI_CHARSET,
								OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
								DEFAULT_PITCH|FF_ROMAN, "Times New Roman"); 
							CFont*   pOldFont=(CFont*)MemuDc.SelectObject(&font);
							MemuDc.SetBkMode(TRANSPARENT);
							MemuDc.SetTextColor(RGB(0,0,0));//黑字					
							MemuDc.TextOut(10+int((smInf->nOX+smInf->nSizeX)*m_dScale),758 - int(smInf->nOY*m_dScale+m_tm.tmHeight),str);	
							MemuDc.GetTextMetrics(&m_tm);
							MemuDc.SelectObject(pOldFont);						
							DeleteObject(font);	
							MemuDc.SetTextAlign(TA_CENTER|TA_BASELINE);
							DrawTextOut(smInf->nOX+smInf->nSizeX/2,smInf->nOY+smInf->nSizeY/2,smInf->strNum,45*dScale);				
						}
					}
					else
					{
						DrawRect(&MemuDc,smInf->nOX,smInf->nOY,smInf->nSizeX,smInf->nSizeY);				
						MemuDc.SetTextAlign(TA_RIGHT|TA_BOTTOM);
						str = smInf->strSizeY;
						DrawTextOut(smInf->nOX+smInf->nSizeX,smInf->nOY,str,28*dScale);
						str = smInf->strSizeX;
					
						CFont   font; 
						font.CreateFont((int)(28*dScale),0,0,0,FW_THIN,0,0,0,ANSI_CHARSET,
							OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							DEFAULT_PITCH|FF_ROMAN, "Times New Roman"); 
						CFont*   pOldFont=(CFont*)MemuDc.SelectObject(&font);
						MemuDc.SetBkMode(TRANSPARENT);
						MemuDc.SetTextColor(RGB(0,0,0));//黑字					
						MemuDc.TextOut(10+int((smInf->nOX+smInf->nSizeX)*m_dScale),758 - int(smInf->nOY*m_dScale+m_tm.tmHeight),str);	
						MemuDc.GetTextMetrics(&m_tm);
						MemuDc.SelectObject(pOldFont);
						
						DeleteObject(font);	

						if (smInf->strName.GetLength()>0 && smInf->strName.GetAt(0) != 0x0a)
						{
							MemuDc.SetTextAlign(TA_LEFT|TA_TOP);
							CString str;
							if (1 == m_nShowShelf)
								str = smInf->strShelf;
							else
								str = smInf->strName;
							DrawTextOut(smInf->nOX+10,smInf->nOY+smInf->nSizeY,str,m_nShelfFont*dScale);				
						}
						if (smInf->strNum.GetLength()>0 && smInf->strNum.GetAt(0) != 0x0a)
						{
							MemuDc.SetTextAlign(TA_CENTER|TA_BASELINE);
							DrawTextOut(smInf->nOX+smInf->nSizeX/2,smInf->nOY+smInf->nSizeY/2,smInf->strNum,45*dScale);				
						}
					}
				}
			}
		}		
		//显示轨迹
		CPen pen;
		pen.CreatePen(PS_SOLID,2,RGB(0,0,0));//0,200,0
		CPen *poldpen = MemuDc.SelectObject(&pen);
		for(pGreen = &g_ExtraShow; pGreen;pGreen = pGreen->Next)
		{
			if(pGreen->glColor!=0)
			{
				MemuDc.MoveTo(10+int(pGreen->Prev->gl_x*m_dScale),758 - int(pGreen->Prev->gl_y*m_dScale));
				MemuDc.LineTo(10+int(pGreen->gl_x*m_dScale),758 - int(pGreen->gl_y*m_dScale));						
			}					
		}
		MemuDc.SelectObject(poldpen);
		pen.DeleteObject();

	}
}
//设置全屏显示的比例
void Cdlg_ShowExtra::SetMaxShow(double dScaleX,double dScaleY)
{   
	double dXY = dScaleX / dScaleY;
    if (dXY > 1.52)
    {		
		m_dScale = 1004.0 / dScaleX * 0.9;
    }
	else
	{
		m_dScale = 748.0 / dScaleY * 0.9;		
	}
}

void Cdlg_ShowExtra::DrawRect(CDC* pDCMenu,int ox,int oy,int x,int y,int nFill)
{

	Point2D   dpPosOrign,dpPos;
	POINT P[5];
	
	dpPosOrign.x = (double)ox;
	dpPosOrign.y = (double)oy;
//    g_Dmcgc.SetGlassPointPos(&dpPos);
	P[0].x = (int)(10 + dpPosOrign.x*m_dScale);
    P[0].y = (int)(758-dpPosOrign.y*m_dScale);
	dpPos.x = ox+x;
	dpPos.y = oy;
//    g_Dmcgc.SetGlassPointPos(&dpPos);
	P[1].x = (int)(10 + dpPos.x*m_dScale);
    P[1].y = (int)(758-dpPos.y*m_dScale);
	
	dpPos.x = ox+x;
	dpPos.y = oy+y;
//    g_Dmcgc.SetGlassPointPos(&dpPos);
	P[2].x = (int)(10 + dpPos.x*m_dScale);
    P[2].y = (int)(758-dpPos.y*m_dScale);
	
	dpPos.x = ox;
	dpPos.y = oy+y;
//    g_Dmcgc.SetGlassPointPos(&dpPos);
	P[3].x = (int)(10 + dpPos.x*m_dScale);
    P[3].y = (int)(758-dpPos.y*m_dScale);
	
	
	P[4].x = (int)(10 + dpPosOrign.x*m_dScale);
    P[4].y = (int)(758-dpPosOrign.y*m_dScale);
	
	if (nFill == 1)
	{
		//填充小矩形
		CRgn rg;
		CBrush b(RGB(199,219,237));//199,237,204
		rg.CreatePolygonRgn(P,5,WINDING);
		pDCMenu->FillRgn(&rg,&b);
	}
	else
	{
		//填充大矩形
		CBrush Brush(RGB(255, 255, 255));
		//		Brush.CreateHatchBrush(HS_BDIAGONAL, RGB(0, 0, 0));
		CBrush *pOldBrush = pDCMenu->SelectObject(&Brush);
		CRgn rg;
		rg.CreatePolygonRgn(P,5,WINDING);
		pDCMenu->FillRgn(&rg,&Brush);
		pDCMenu->SelectObject(pOldBrush);
		Brush.DeleteObject();
	}
	//画矩形外框
    CPen pen;
	pen.CreatePen(PS_SOLID,3,RGB(0,0,0));//0,200,0
	CPen *poldpen = pDCMenu->SelectObject(&pen);
	HBRUSH poldbrush = (HBRUSH)pDCMenu->SelectObject((HBRUSH)GetStockObject(NULL_BRUSH));
	pDCMenu->Polygon(P,5);
	pDCMenu->SelectObject(poldpen);
	pDCMenu->SelectObject(poldbrush);
    pen.DeleteObject();
				
}

void Cdlg_ShowExtra::DrawTextOut(int x,int y,const char* cstr,int nFontBig)
{ 
	CFont   font; 
	font.CreateFont(nFontBig,0,0,0,FW_THIN,0,0,0,ANSI_CHARSET,
		   OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		   DEFAULT_PITCH|FF_ROMAN, "Times New Roman");  	   
	   
	CFont*   pOldFont=(CFont*)MemuDc.SelectObject(&font);
    MemuDc.SetBkMode(TRANSPARENT);
    MemuDc.SetTextColor(RGB(0,0,0));//黑字
	MemuDc.TextOut(10+int(x*m_dScale),758 - int(y*m_dScale),cstr);	
    MemuDc.GetTextMetrics(&m_tm);
	MemuDc.SelectObject(pOldFont);

	DeleteObject(font);	
}