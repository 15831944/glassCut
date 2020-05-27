// 2DDraw.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "2DDraw.h"
#include "benderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define  YHEIGHT 440
/////////////////////////////////////////////////////////////////////////////
// C2DDraw

C2DDraw::C2DDraw()
{
    memset(&Track,0,sizeof(TRACK));
	memset(&Green,'\0',sizeof(TRACK));
	pcurrTrack = NULL;
	pTrack = NULL;
	m_dBaseX = m_dBaseY = 3.0;
	m_dFullScreenZoom = 0.0001;
	m_dZoom = 0.0001;
	m_dFullBaseX = m_dFullBaseY = 3.0;
	m_pShowAddtion = NULL;
	m_dpGlassPos.x = .0;
	m_dpGlassPos.y = .0;
	m_dGlassAngle = .0;
	memset(&g_ExtraShow,0,sizeof(TRACK));
	memset(&GreenFileOpen,0,sizeof(TRACK));
	g_pShowSmall= NULL;
	m_nShowShelf = 0;
	m_lPosPreX = -1000000;
	m_lPosPreY = -1000000;
	m_lPosPreZ = -1000000;
	m_nShelfFont = GetPrivateProfileInt("SHEET","FONTBIG1",14,"D:\\program files\\GlassCutter\\ExtraPar.ini");

}

C2DDraw::~C2DDraw()
{
	FreeBlocks();
	FreeGreens();
	FreeExtraShow(); 
	FreeFileOpen();
}

BEGIN_MESSAGE_MAP(C2DDraw, CWnd)
	//{{AFX_MSG_MAP(C2DDraw)
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// C2DDraw message handlers
BOOL C2DDraw::Create(CWnd *pParentWnd, CRect rect) 
{
	if(!CWnd::Create(AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_OWNDC,
		::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW))),
		NULL,
		WS_CHILD|WS_BORDER|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_VISIBLE,
		rect, 
		pParentWnd,
		0))
	{
		return FALSE;
	}	
	SetTimer(1,150,NULL);
	return TRUE;
}

void C2DDraw::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if( nIDEvent == 1 && g_iMode != 5)//编辑/图库
	{
		if(true == DrawTail())
			DrawTrack();	
	}
	CWnd::OnTimer(nIDEvent);
}

void C2DDraw::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if (g_iMode == 5)
	{
		DrawBottero();
	}
	else
	{
		CBenderDlg *pDlg;
		pDlg = (CBenderDlg *)GetParent();
		if (pDlg!=NULL)
		{
			pDlg->InvalidateRect(CRect(2,245,17,703),FALSE);//左边
			pDlg->InvalidateRect(CRect(18,245,715,260),FALSE);//上边
		}	
		DrawGreen();
		DrawTrack();
	}
	// Do not call CWnd::OnPaint() for painting messages
}

void C2DDraw::DrawGreen()
{
	CDC *pDc;
	CDC DCMenu;
	pDc = GetDC();
	CRect rcBounds;
	GetClientRect(rcBounds);
	CPen penG01,*pOldPen;
	penG01.CreatePen(PS_SOLID,2,RGB(79,167,214));//RGB(0,200,0)
	
	CBitmap bitmap;
	DCMenu.CreateCompatibleDC(pDc);
    bitmap.LoadBitmap(IDB_BITMAP_BLACK);
	CBitmap *oldBit = DCMenu.SelectObject(&bitmap);
	//==============================平面图形
	if(Green.Next)
	{
		if (m_pShowAddtion != NULL)
		{
			ShowAdditionInf(&DCMenu);
		}
 		pOldPen = DCMenu.SelectObject(&penG01);
		for(pGreen = &Green; pGreen;pGreen = pGreen->Next)
		{
			if(pGreen->glColor!=0)
			{
	
				DCMenu.MoveTo((int)(m_dBaseX + pGreen->Prev->gl_x*m_dZoom)
					,(int)(YHEIGHT - (m_dBaseY + pGreen->Prev->gl_y*m_dZoom)));
				DCMenu.LineTo((int)(m_dBaseX + pGreen->gl_x*m_dZoom)
					,(int)(YHEIGHT-(m_dBaseY + pGreen->gl_y*m_dZoom)));				
				if (pGreen->bDraw)//在抬刀的时候画箭头
				{
					CGrPoint ptBgn, ptEnd;
					ptBgn.Set(pGreen->Prev->gl_x,pGreen->Prev->gl_y);
					ptEnd.Set(pGreen->gl_x,pGreen->gl_y);
					DrawArrowhead(&DCMenu,ptEnd,ptBgn);
				}		
			}					
		}
 		DCMenu.SelectObject(pOldPen);
	}
	pDc->BitBlt(0,0,rcBounds.Width(),rcBounds.Height(),&DCMenu,0,0,SRCCOPY);
	DCMenu.SelectObject(oldBit);
	penG01.DeleteObject();
	DeleteObject(DCMenu);
}

//显示跟踪的图形
void C2DDraw::DrawTrack()
{
	CDC *pDC = GetDC();
	CPen penRed, penYellow,*oldPen;
	penRed.CreatePen(PS_SOLID,2,RGB(170, 0, 0));
	penYellow.CreatePen(PS_SOLID,2,RGB(220,220, 0));
	oldPen = pDC->SelectObject(&penYellow);
	

	if (Track.Next!=NULL)
	{
		if( pcurrTrack != NULL && pcurrTrack->Prev != NULL)
		{
			pTrack=&Track;
			pDC->MoveTo((int)(m_dBaseX + pTrack->gl_x*m_dZoom), (int)(YHEIGHT - (m_dBaseY+pTrack->gl_y*m_dZoom)));
    		for(pTrack = pTrack->Next;pTrack;pTrack=pTrack->Next)
			{
				if(pTrack->glColor == 1)
                    pDC->SelectObject(&penRed);
				else
					pDC->SelectObject(&penYellow);
				pDC->LineTo((int)(m_dBaseX + pTrack->gl_x*m_dZoom), (int)(YHEIGHT - (m_dBaseY+pTrack->gl_y*m_dZoom)));		
			}
		}
	}
	pDC->SelectObject(oldPen);
	penRed.DeleteObject();
	penYellow.DeleteObject();
	DeleteObject(pDC);
}

void C2DDraw::FreeBlocks()
{	
	PTRACK    pBlock,pTempBlock;                   
	for (pBlock = Track.Next; pBlock;)
	{
		pTempBlock = pBlock->Next;
		delete pBlock;                        
		pBlock = pTempBlock;
		if(!pBlock)  break;
	}
	memset(&Track,0,sizeof(TRACK));
}
//擦除跟踪轨迹
void C2DDraw::ErasureTracks()
{
	FreeBlocks();
	Invalidate(TRUE);
}

void C2DDraw::ZoomIn()
{
	m_dZoom *= 1.05;
	Invalidate(TRUE);
}

void C2DDraw::ZoomOut()
{
	m_dZoom *= 0.95;
	Invalidate(TRUE);
}

void C2DDraw::MoveUp()
{
	m_dBaseY += 20.0;
	Invalidate(TRUE);
}

void C2DDraw::MoveRight()
{	
	m_dBaseX += 20.0;
	Invalidate(TRUE);
}

void C2DDraw::MoveLeft()
{	
	m_dBaseX -= 20.0;
	Invalidate(TRUE);
}

void C2DDraw::MoveDown()
{	
	m_dBaseY -= 20.0;
	Invalidate(TRUE);
}

//还原图形显示
void C2DDraw::RestoreDisplay()
{
	m_dBaseX = m_dFullBaseX;
	m_dBaseY = m_dFullBaseY; 
	m_dZoom = m_dFullScreenZoom;
	Invalidate(TRUE);
}

//记录跟踪轨迹
bool C2DDraw::DrawTail()
{
	double   glfx,glfy,glfz;
	PTRACK    pBlock;
	CString strRes; 
	char szResponse[30]={0};
	int nPos;
	long x_pos=-1000000,y_pos=-1000000,z_pos=-1000000;
	
	
	LONG lRc = g_Controller.Command("RPABC",szResponse,sizeof(szResponse));
	if (lRc != 0)
	{
		return false;
	}
	x_pos = (long)atoi(szResponse);
	strRes.Format("%s",szResponse);
	nPos = strRes.Find(',');			
	if( nPos != -1)
	{
		strRes = strRes.Mid(nPos+1);
		y_pos = (long)atoi(strRes);	
		nPos = strRes.Find(',');	
		if(nPos!=-1)
			z_pos = (long)atoi(strRes.Mid(nPos+1));
		
	}
    if(m_lPosPreX==x_pos && m_lPosPreY==y_pos && m_lPosPreZ==z_pos)
		return false;
    m_lPosPreX = x_pos;
    m_lPosPreY = y_pos;
    m_lPosPreZ = z_pos;
	glfx = x_pos / g_stu_pAxisA->d_pulse_user;
	glfy = y_pos / g_stu_pAxisB->d_pulse_user;
	glfz = z_pos / g_stu_pAxisC->d_pulse_user;
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)GetParent();
	if (pDlg!=NULL)
	{
		if(g_stu_pAxisH->sSpare==1)
		{
			glfx = glfx / IN_TO_MM;
			glfy = glfy / IN_TO_MM;
			glfz = glfz / IN_TO_MM;
		}
		strRes.Format("%.2f",glfx);
		pDlg->SetDlgItemText(IDC_STATIC_RPX,strRes);
		strRes.Format("%.2f",glfy);
		pDlg->SetDlgItemText(IDC_STATIC_RPY,strRes);
		strRes.Format("%.2f",glfz);
		pDlg->SetDlgItemText(IDC_STATIC_RPZ,strRes);
	}	
	int  out = 0;   
	if((int)Track.gl_x==0&&(int)Track.gl_y==0)
	{
		Track.gl_x = glfx;
		Track.gl_y = glfy;
		Track.glColor = out;
		pcurrTrack = pTrack = &Track;
	}
	else
	{
		pBlock = new TRACK;
		memset(pBlock,0,sizeof(TRACK));
		pcurrTrack->Next = pBlock;
		pBlock->Prev = pcurrTrack;
		pcurrTrack = pcurrTrack->Next;
		pcurrTrack->gl_x = glfx;
		pcurrTrack->gl_y = glfy;
		pcurrTrack->glColor = out;
	}
    return true;
}

//设置全屏显示的比例
void C2DDraw::SetMaxShow(double dScale)
{
    m_dZoom = dScale;
    m_dFullScreenZoom = dScale;
	m_dFullBaseX = 3;
	m_dFullBaseY = 3;
	Invalidate(TRUE);
}

//写入原边信息
void C2DDraw::SetAdditionInf(pShowInf pinf)
{
    m_pShowAddtion = pinf;
}

//显示原边信息
void C2DDraw::ShowAdditionInf(CDC* pDCMenu)
{  
	if (m_pShowAddtion->nX>0 && m_pShowAddtion->nY>0)
    {
		g_Dmcgc.GetGlassPos(m_dpGlassPos.x,m_dpGlassPos.y,m_dGlassAngle);
		DDrawRect(pDCMenu,0,0,m_pShowAddtion->nX,m_pShowAddtion->nY,0);
		CString str;
//		str.Format("%s%d*%d*%d",m_pShowAddtion->strStorage,m_pShowAddtion->nX,m_pShowAddtion->nY,m_pShowAddtion->nCount);
//		pDCMenu->SetTextAlign(TA_LEFT|TA_BOTTOM);
//		DDrawTextOut(pDCMenu,0,m_pShowAddtion->nY,str,int(12*10*m_dZoom));
		if (m_pShowAddtion->pShowSmall != NULL)
		{   
			pSmallInf smInf;
			double dScale = 1.0;//字体显示比例
			for (smInf=m_pShowAddtion->pShowSmall;smInf;smInf=smInf->pNext)
			{
				if (smInf->nSizeX < 100 || smInf->nSizeY<100)
				{
					dScale = 0.2;
				}
				else if (smInf->nSizeX < 200 || smInf->nSizeY<200)
				{
					dScale = 0.5;
				}
				else if (smInf->nSizeX < 400 || smInf->nSizeY<400)
				{
					dScale = 0.7;
				}
				else
				{
					dScale = 1.0;
				}
				if (smInf->strShelf == "*")//余片尺寸大于100显示
				{
					if (smInf->nSizeX>100 && smInf->nSizeY>100 && smInf->strNum.GetLength()>0 && smInf->strNum.GetAt(0) != 0x0a)
					{
						pDCMenu->SetTextAlign(TA_RIGHT|TA_BOTTOM);
						DDrawTextOut(pDCMenu,smInf->nOX+smInf->nSizeX,smInf->nOY,smInf->strSizeY,int(dScale*12*10*m_dZoom));
						DDrawTextOut(pDCMenu,smInf->nOX+smInf->nSizeX,smInf->nOY+(int)(75*dScale),smInf->strSizeX,int(dScale*12*10*m_dZoom));				
						pDCMenu->SetTextAlign(TA_CENTER|TA_BASELINE);
						DDrawTextOut(pDCMenu,smInf->nOX+smInf->nSizeX/2,smInf->nOY+smInf->nSizeY/2,smInf->strNum,int(dScale*19*10*m_dZoom));				
					}	
				}
				else
				{
					DDrawRect(pDCMenu,smInf->nOX,smInf->nOY,smInf->nSizeX,smInf->nSizeY);
					pDCMenu->SetTextAlign(TA_RIGHT|TA_BOTTOM);
					DDrawTextOut(pDCMenu,smInf->nOX+smInf->nSizeX,smInf->nOY,smInf->strSizeY,int(dScale*12*10*m_dZoom));
					DDrawTextOut(pDCMenu,smInf->nOX+smInf->nSizeX,smInf->nOY+(int)(75*dScale),smInf->strSizeX,int(dScale*12*10*m_dZoom));				
					if (smInf->strName.GetLength()>0 && smInf->strName.GetAt(0) != 0x0a)
					{
						pDCMenu->SetTextAlign(TA_LEFT|TA_TOP);
						CString str;
						if (1 == m_nShowShelf)
							str = smInf->strShelf;
						else
							str = smInf->strName;
						DDrawTextOut(pDCMenu,smInf->nOX,smInf->nOY+smInf->nSizeY,str,int(dScale*m_nShelfFont*10*m_dZoom));				
					}
					if (smInf->strNum.GetLength()>0 && smInf->strNum.GetAt(0) != 0x0a)
					{
						pDCMenu->SetTextAlign(TA_CENTER|TA_BASELINE);
						DDrawTextOut(pDCMenu,smInf->nOX+smInf->nSizeX/2,smInf->nOY+smInf->nSizeY/2,smInf->strNum,int(dScale*19*10*m_dZoom));				
					}				
				}
			
			}
		}
    } 
}

void C2DDraw::DDrawRect(CDC* pDCMenu,int ox,int oy,int x,int y,int nFill)
{
	Point2D   dpPosOrign,dpPos;
	POINT P[5];
	
	dpPos.x = (double)ox;
	dpPos.y = (double)oy;
    g_Dmcgc.SetGlassPointPos(&dpPos);
	dpPosOrign.x = dpPos.x;
	dpPosOrign.y = dpPos.y;
	P[0].x = (int)(m_dBaseX + dpPos.x*m_dZoom);
    P[0].y = (int)(YHEIGHT-(m_dBaseY + dpPos.y*m_dZoom));
	dpPos.x = ox+x;
	dpPos.y = oy;
    g_Dmcgc.SetGlassPointPos(&dpPos);
	P[1].x = (int)(m_dBaseX + dpPos.x*m_dZoom);
    P[1].y = (int)(YHEIGHT-(m_dBaseY + dpPos.y*m_dZoom));
	
	dpPos.x = ox+x;
	dpPos.y = oy+y;
    g_Dmcgc.SetGlassPointPos(&dpPos);
	P[2].x = (int)(m_dBaseX + dpPos.x*m_dZoom);
    P[2].y = (int)(YHEIGHT-(m_dBaseY + dpPos.y*m_dZoom));
	
	dpPos.x = ox;
	dpPos.y = oy+y;
    g_Dmcgc.SetGlassPointPos(&dpPos);
	P[3].x = (int)(m_dBaseX + dpPos.x*m_dZoom);
    P[3].y = (int)(YHEIGHT-(m_dBaseY + dpPos.y*m_dZoom));


	P[4].x = (int)(m_dBaseX + dpPosOrign.x*m_dZoom);
    P[4].y = (int)(YHEIGHT-(m_dBaseY + dpPosOrign.y*m_dZoom));

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
	pen.CreatePen(PS_SOLID,1,RGB(79,167,214));//0,200,0
	CPen *poldpen = pDCMenu->SelectObject(&pen);
	HBRUSH poldbrush = (HBRUSH)pDCMenu->SelectObject((HBRUSH)GetStockObject(NULL_BRUSH));
	pDCMenu->Polygon(P,5);
	pDCMenu->SelectObject(poldpen);
	pDCMenu->SelectObject(poldbrush);
    pen.DeleteObject();
}

int C2DDraw::DDrawTextOut(CDC* pDCMenu,int x,int y,const char* cstr,int nBig)
{
	Point2D   dpPos;
	dpPos.x = (double)x;
	dpPos.y = (double)y;
    g_Dmcgc.SetGlassPointPos(&dpPos); 
	x = (int)dpPos.x;
	y = (int)dpPos.y;
	CFont   font; 	
	if(nBig>45)
		nBig = 45;
	font.CreateFont(nBig,0,0,0,FW_MEDIUM,0,0,0,ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_ROMAN, "Times New Roman");  	   
	CFont *pOldFont = (CFont *)pDCMenu->SelectObject(&font);
	pDCMenu->SetBkMode(TRANSPARENT);
	pDCMenu->SetTextColor(RGB(0,0,0));
	pDCMenu->TextOut((int)(m_dBaseX + dpPos.x*m_dZoom),(int)(YHEIGHT-(m_dBaseY + dpPos.y*m_dZoom)),cstr);
	pDCMenu->SelectObject(pOldFont);
	DeleteObject(font);
	return 1;
}

//保存打开文件后的加工图形。不保存光电定位后的。
void C2DDraw::SaveFileOpenGreen()
{
	FreeFileOpen();    
	PTRACK    pBlock,pTempBlock;
	GreenFileOpen.gl_x = Green.gl_x;
	GreenFileOpen.gl_y = Green.gl_y;
	pTempBlock = &GreenFileOpen;
	for(pBlock = Green.Next;pBlock;pBlock=pBlock->Next)
	{
		pGreen = new TRACK;
		memset(pGreen,'\0',sizeof(TRACK));
		pGreen->glColor = pBlock->glColor;
		pGreen->gl_x = pBlock->gl_x;
		pGreen->gl_y = pBlock->gl_y;
		pGreen->Prev = pTempBlock;
		pTempBlock->Next = pGreen;
		pTempBlock = pGreen;
	}
}

//更换工件时，将保存打开文件后的加工图形全都删节
void C2DDraw::FreeFileOpen()
{
	PTRACK    pBlock,pTempBlock;                  
	for (pBlock = GreenFileOpen.Next; pBlock;)
	{
		pTempBlock = pBlock->Next;
		delete pBlock;                        
		pBlock = pTempBlock;
		if(!pBlock)  break;
	}
	memset(&GreenFileOpen,0,sizeof(TRACK));
}

//把图形的结构转换为画图的结构数据
void C2DDraw::CalGreen()                      
{
	//==============================平面图形
	PDMC    pdmc;
	CString sztmp;
	FreeGreens();
	memset(&Green,'\0',sizeof(TRACK));
	pcurrGreen = &Green;
	
	for(pdmc=g_Dmcgc.GetDmcNumber();pdmc;)
	{
		sztmp.Format("%s",pdmc->command);
		if(sztmp=="VP")
		{
			pGreen = new TRACK;
			memset(pGreen,'\0',sizeof(TRACK));
			pGreen->Prev = pcurrGreen;
			pcurrGreen->Next = pGreen;
			if(strstr(pdmc->szLineG,"G00"))
			{
				pGreen->glColor = 0;
			}
			else
			{
				pGreen->glColor = 1;
			}
			pGreen->gl_x = (float)(pdmc->usProPos.X);
			pGreen->gl_y = (float)(pdmc->usProPos.Y);
			if (pdmc->Next!=NULL && pdmc->Next->comG=='M')
			{
				pGreen->bDraw = true;
			}
			pcurrGreen = pcurrGreen->Next;
		}
		else if(sztmp=="CR")
		{
			gltDrawArc(pcurrGreen,pdmc,2.0f);
		}
		pdmc = pdmc->Next;
	}  	
}

void C2DDraw::FreeGreens()                      //更换工件时，将所照过的部分全都删节
{
	PTRACK    pBlock,pTempBlock;                 //  
	for (pBlock = Green.Next; pBlock;)
	{
		pTempBlock = pBlock->Next;
		delete pBlock;                        //DMC_FFREEA
		pBlock = pTempBlock;
		if(!pBlock)  break;
	}
	memset(&Green,0,sizeof(TRACK));
}

/* 将圆弧打碎成小线段 */
void C2DDraw::gltDrawArc(PTRACK pBe,PDMC pDmc,float interval)
{
	POINT3D pPoint,pCenter;
	float currAngle = (float)pDmc->usBAngle;
	int     i,number;
	
	if(!interval)        return;     /* 间隔为0，返回 */
	
	pCenter.x = pBe->gl_x - pDmc->usRadius  * cos(pDmc->usBAngle*PI/180)  / g_stu_pAxisA->d_pulse_user;/* 计算圆心 */
	pCenter.y = pBe->gl_y - pDmc->usRadius  * sin(pDmc->usBAngle*PI/180)  / g_stu_pAxisB->d_pulse_user;

	
	if(pDmc->usEAngle<0)     interval = -interval;//顺时针
	else	                 interval = interval; //逆时针
	
	number = (int)(pDmc->usEAngle/interval);    /* 计算循环次数 */
	if(fabs(pDmc->usEAngle-interval*number)*1000>0) /* 计算是否最后有余数，有余数加1次循环 */
		number++;
	
	for(i=0;i<number;i++)
	{
		pGreen = new TRACK;
		memset(pGreen,'\0',sizeof(TRACK));
		pGreen->Prev = pcurrGreen;
		pcurrGreen->Next = pGreen;
		pGreen->glColor = 1;
		if(i==number-1)	
		{
			currAngle = (float)(pDmc->usBAngle + pDmc->usEAngle);
			if (pDmc->Next!=NULL && pDmc->Next->comG=='M')
			{
				pGreen->bDraw = true;
			}			
		}
		else  
		{
			currAngle = (float)(currAngle + interval);			
		}
			
		pPoint.x = pCenter.x + pDmc->usRadius  * cos(currAngle*PI/180)  / g_stu_pAxisA->d_pulse_user;
		pPoint.y = pCenter.y + pDmc->usRadius  * sin(currAngle*PI/180)  / g_stu_pAxisB->d_pulse_user;
		
		pGreen->gl_x = (float)(pPoint.x);
		pGreen->gl_y = (float)(pPoint.y);		
		pcurrGreen = pcurrGreen->Next;
	}	
}

//复制当前显示在主界面的图形数据结构，用于在扩展时显示，保存在g_ExtraShow里
void C2DDraw::AddExtraShowData()
{
	FreeExtraShow();    
	PTRACK    pBlock,pTempBlock;
	g_ExtraShow.gl_x = GreenFileOpen.gl_x;
	g_ExtraShow.gl_y = GreenFileOpen.gl_y;
	pTempBlock = &g_ExtraShow;
	for(pBlock = GreenFileOpen.Next;pBlock;pBlock=pBlock->Next)
	{
		pGreen = new TRACK;
		memset(pGreen,'\0',sizeof(TRACK));
		pGreen->glColor = pBlock->glColor;
		pGreen->gl_x = pBlock->gl_x;
		pGreen->gl_y = pBlock->gl_y;
		pGreen->Prev = pTempBlock;
		pTempBlock->Next = pGreen;
		pTempBlock = pGreen;
	}
}

void C2DDraw::FreeExtraShow()
{
	PTRACK    pBlock,pTempBlock;                  
	for (pBlock = g_ExtraShow.Next; pBlock;)
	{
		pTempBlock = pBlock->Next;
		delete pBlock;                        
		pBlock = pTempBlock;
		if(!pBlock)  break;
	}
	memset(&g_ExtraShow,0,sizeof(TRACK));
}

void C2DDraw::DrawBottero()
{
	CDC *pDc;
	CDC DCMenu;
	pDc = GetDC();
	CRect rcBounds;
	GetClientRect(rcBounds);
	CPen penG01,*pOldPen;
	penG01.CreatePen(PS_SOLID,2,RGB(79,167,214));//RGB(0,200,0)
	
	CBitmap bitmap;
	DCMenu.CreateCompatibleDC(pDc);
    bitmap.LoadBitmap(IDB_BITMAP_BLACK);
	CBitmap *oldBit = DCMenu.SelectObject(&bitmap);	
	
	p_Command	stu_pCommand;
	pSegment	stu_pSegment;
	CPoint pointX(0,0);//显示X的剩余量的点坐标
	CPoint pointY(0,0);//显示Y的剩余量的点坐标
	CString strSize;
 

	int nTextMode = DCMenu.GetTextAlign();
	DCMenu.SetTextAlign(TA_CENTER | TA_TOP);
	pOldPen = DCMenu.SelectObject(&penG01);
	DCMenu.SetBkMode(TRANSPARENT);
	DDrawRect(&DCMenu,0,0,g_stu_pAxisB->sSpareA,g_stu_pAxisB->sSpareB,0);
	for(stu_pCommand=stuBtro.BtroComm;stu_pCommand;stu_pCommand=stu_pCommand->Next)
	{
		for(stu_pSegment=stu_pCommand->pStuSegment;stu_pSegment;stu_pSegment=stu_pSegment->Next)
		{
			if(stu_pSegment->bIsLine)
			{
				DCMenu.MoveTo((long)(m_dBaseX+stu_pSegment->fBeginX*m_dZoom) , (long)(YHEIGHT-(m_dBaseY+stu_pSegment->fBeginY*m_dZoom)));
				DCMenu.LineTo((long)(m_dBaseX+stu_pSegment->fEndX*m_dZoom) , (long)(YHEIGHT-(m_dBaseY+stu_pSegment->fEndY*m_dZoom)));
				if (stu_pCommand->chCom == 'X')
				{
					pointX.x = (int)(m_dBaseX+(stu_pSegment->fBeginX+g_nRemainderX/2)*m_dZoom);
					pointX.y = (int)(YHEIGHT-(m_dBaseY+stu_pSegment->fBeginY/m_dZoom));
					pointY = 0;	
					if (stu_pCommand->Next == NULL)
					{
						DCMenu.SetTextAlign(TA_LEFT | TA_TOP);
						strSize.Format("Y%d",int(stuBtro.lMaterialY-stuBtro.lModifyY));
						DCMenu.TextOut((long)(m_dBaseX+(stu_pSegment->fEndX-stu_pCommand->nValue)*m_dZoom),
							(int)(YHEIGHT-(m_dBaseY+(stu_pSegment->fBeginY+(stuBtro.lMaterialY-stuBtro.lModifyY)/2)*m_dZoom)),strSize);
						
					}				
				}
				else if (stu_pCommand->chCom == 'Y')
				{
					pointY.x = (int)(m_dBaseX+stu_pSegment->fBeginX*m_dZoom);
					pointY.y = (int)(YHEIGHT-(m_dBaseY+(stu_pSegment->fBeginY+g_nRemainderY/2)*m_dZoom));					
				
				}				
			}
			else
			{
				DCMenu.MoveTo((long)(m_dBaseX+stu_pSegment->fBeginX*m_dZoom) , (long)(YHEIGHT-(m_dBaseY+stu_pSegment->fBeginY*m_dZoom)));
				DCMenu.AngleArc((long)(m_dBaseX+stu_pSegment->pSegArc->fCenterX*m_dZoom), (long)(YHEIGHT-(m_dBaseY+stu_pSegment->pSegArc->fCenterY*m_dZoom)), 
					(long)(stu_pSegment->pSegArc->fRadius*m_dZoom), (float)(stu_pSegment->pSegArc->fBeginAngle), (float)(stu_pSegment->pSegArc->fSweepAngle));
			}
		}
		for (pRectDraw pDraw = stu_pCommand->pRect; pDraw!=NULL; pDraw=pDraw->Next)
		{
			if (stu_pCommand->pRect->nDraw ==1)
			{
				if (pDraw->rect.Width()<300 /*&& (-pDraw->rect.Height())>100*/)//防止数据长，重叠显示。
				{
					DCMenu.SetTextAlign(TA_CENTER | TA_TOP);
					strSize.Format("%d",pDraw->rect.Width());
					DCMenu.TextOut((int)(m_dBaseX+(pDraw->rect.left+pDraw->rect.Width()/2)*m_dZoom),
						(int)(YHEIGHT-(m_dBaseY+(pDraw->rect.bottom+(-(pDraw->rect.Height()/2)))*m_dZoom)),
						strSize);
					DCMenu.SetTextAlign(TA_CENTER | TA_BOTTOM);
					strSize.Format("%d",-(pDraw->rect.Height()));
					DCMenu.TextOut((int)(m_dBaseX+(pDraw->rect.left+pDraw->rect.Width()/2)*m_dZoom),
						(int)(YHEIGHT-(m_dBaseY+(pDraw->rect.bottom+(-(pDraw->rect.Height()/2)))*m_dZoom)),
						strSize);
				}
				else
				{
					DCMenu.SetTextAlign(TA_CENTER | TA_TOP);
					strSize.Format("%d*%d",pDraw->rect.Width(),-(pDraw->rect.Height()));
					DCMenu.TextOut((int)(m_dBaseX+(pDraw->rect.left+pDraw->rect.Width()/2)*m_dZoom),
						(int)(YHEIGHT-(m_dBaseY+(pDraw->rect.bottom+(-(pDraw->rect.Height()/2)))*m_dZoom))-5,
						strSize);
				}
			}			
		}
	}
	//显示剩余		
	if (pointX.x != 0 || pointX.y != 0)
	{
		DCMenu.SetTextAlign(TA_CENTER | TA_BOTTOM);
		strSize.Format("X%d",g_nRemainderX);
		DCMenu.TextOut(pointX.x,pointX.y,strSize);
	}
	if (pointY.x != 0 || pointY.y != 0)
	{
		DCMenu.SetTextAlign(TA_LEFT | TA_BASELINE);
		strSize.Format("Y%d",g_nRemainderY);
		DCMenu.TextOut(pointY.x,pointY.y,strSize);
	}
	DCMenu.SetTextAlign(nTextMode);	
	pDc->BitBlt(0,0,rcBounds.Width(),rcBounds.Height(),&DCMenu,0,0,SRCCOPY);
	DCMenu.SelectObject(oldBit);
	DCMenu.SelectObject(pOldPen);
	penG01.DeleteObject();
	DeleteObject(DCMenu);
}

//画箭头,在终点上画
//pDC画图dc；起点终点
void C2DDraw::DrawArrowhead(CDC *pDC, CGrPoint &ptBgn, CGrPoint &ptEnd)
{
	GR_LINE ln1, ln2;
	CPoint points[3];	
	CRgn rgn;
	CBrush br;
	br.CreateSolidBrush(RGB(79,167,214));
	if(pDC)
	{
	 	LineRevolve(ln1, ptBgn, ptEnd, (MATH_PI*2)-(MATH_PI/12),12.0/m_dZoom);
	  	LineRevolve(ln2, ptBgn, ptEnd, MATH_PI/12, 12.0/m_dZoom);
	 	ln1.pt1.ToCPoint(&points[0]);
	 	ln2.pt1.ToCPoint(&points[1]);
	 	ptBgn.ToCPoint(&points[2]);
 		for (int i=0; i<3; i++)
		{
			points[i].x = m_dBaseX + points[i].x*m_dZoom;
			points[i].y = YHEIGHT-(m_dBaseY+points[i].y*m_dZoom);
		}
		rgn.CreatePolygonRgn(points, 3, RGN_OR);
		pDC->FillRgn(&rgn, &br);
 	  	pDC->MoveTo(points[2]);
 	 	pDC->LineTo(points[0]);
 	 	pDC->MoveTo(points[2]);
 	 	pDC->LineTo(points[1]);		
	}
	if(rgn.m_hObject)
		rgn.DeleteObject();
	if(br.m_hObject)
		br.DeleteObject();
}
