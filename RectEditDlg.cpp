// RectEditDlgcpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "RectEditDlg.h"
#include "Dlg_KeyNumber.h"
#include "GraphDlg.h"/* 图库界面 */
#include "dlg_save.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRectEditDlg dialog


CRectEditDlg::CRectEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRectEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRectEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	p_FirstRectInf = 0;
	p_CurrentRectInf = NULL;
}

CRectEditDlg::~CRectEditDlg()
{
	DeleRectInf();
}

void CRectEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRectEditDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRectEditDlg, CDialog)
	//{{AFX_MSG_MAP(CRectEditDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_F1, OnButtonF1)
	ON_BN_CLICKED(IDC_BUTTON_F2, OnButtonF2)
	ON_BN_CLICKED(IDC_BUTTON_F3, OnButtonF3)
	ON_BN_CLICKED(IDC_BUTTON_F4, OnButtonF4)
	ON_BN_CLICKED(IDC_BUTTON_F5, OnButtonF5)
	ON_WM_COPYDATA()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRectEditDlg message handlers

BOOL CRectEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText("RECTEDIT");	
	// TODO: Add extra initialization here
	((CStatic *)GetDlgItem(IDC_STATIC_LIGHT))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_STATIC_HEIGHT))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_STATIC_SAFE))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_STATIC1))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_STATIC2))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_STATIC3))->SetFont(&g_fontEdit);
	if (g_iLanguage == 1)
	{
		SetDlgItemText(IDC_DEMO10CTRL1,"Rect Edit");
		SetDlgItemText(IDC_STATIC_LIGHT,"Lenght");
		SetDlgItemText(IDC_STATIC_HEIGHT,"Height");
		SetDlgItemText(IDC_STATIC_SAFE,"Safe Dis");
	}
	CString str;
	str.Format("%d",g_stu_pAxisB->sSpareA);
	SetDlgItemText(IDC_STATIC1,str);
	str.Format("%d",g_stu_pAxisB->sSpareB);
	SetDlgItemText(IDC_STATIC2,str);
	str.Format("%.0f",g_stu_pAxisH->dSpareC);
	SetDlgItemText(IDC_STATIC3,str);
	InitButton();
	AddNewRectInf();    
	OnInitGrid();	
	AddGrid();
	SetWindowPos(&CWnd::wndTop,0,0,1024,768,SWP_SHOWWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CRectEditDlg::InitButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_EDITSET1);
	//新建
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_NEW1,IDB_BITMAP_NEW2);
	m_pButton[1].Create("添加矩形", WS_CHILD | WS_VISIBLE, CPoint(300, 714), c, this, IDC_BUTTON_F1); 
	//删除
	m_pButton[2].SetFont(&g_fontEdit);
	m_pButton[2].SetBitMapID(IDB_BITMAP_DELETE1,IDB_BITMAP_DELETE2);
	m_pButton[2].Create("删除矩形", WS_CHILD | WS_VISIBLE, CPoint(740, 714), c, this, IDC_BUTTON_F2); 
	//保存G
	m_pButton[3].SetFont(&g_fontEdit);
	m_pButton[3].SetBitMapID(IDB_BITMAP_SAVEG1,IDB_BITMAP_SAVEG2);	
	m_pButton[3].Create("G CODE", WS_CHILD | WS_VISIBLE, CPoint(460, 714), c, this, IDC_BUTTON_F3); 	
	
	//发送
	m_pButton[5].SetFont(&g_fontEdit);
	m_pButton[5].SetBitMapID(IDB_BITMAP_SAVEPAR1,IDB_BITMAP_SAVEPAR2);	
	m_pButton[5].Create(g_strBottero[0][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(600, 714), c, this, IDC_BUTTON_F4); 
	
	//返回	
	m_pButton[4].SetFont(&g_fontEdit);
	m_pButton[4].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[4].Create(g_strBottero[7][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(900, 714), c, this, IDC_BUTTON_F5); 
    	
	DeleteObject(c);  
	
}

void CRectEditDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CDC DCMenu;
	CRect rcBounds;
	GetClientRect(rcBounds);
	CPen penG01,*pOldPen;
	penG01.CreatePen(PS_SOLID,2,RGB(79,167,214));//RGB(0,200,0)
	
	CBitmap bitmap;
	DCMenu.CreateCompatibleDC(&dc);
    bitmap.LoadBitmap(IDB_BITMAP_BLACK);//717*464
	CBitmap *oldBit = DCMenu.SelectObject(&bitmap);	
	pOldPen = DCMenu.SelectObject(&penG01);
	DCMenu.SetBkMode(TRANSPARENT);
	m_dScale = ((double)g_stu_pAxisB->sSpareA/(double)g_stu_pAxisB->sSpareB);
	if (m_dScale > 1.5453)
    {
		m_dScale = 700.0/g_stu_pAxisB->sSpareA;
    }
	else
	{
		m_dScale = 450.0/g_stu_pAxisB->sSpareB;
	}
	//原片尺寸
	CPoint  cOrigin(4,50);
    DrawRect(&DCMenu,0,0,g_stu_pAxisB->sSpareA,g_stu_pAxisB->sSpareB,0);
	DrawRectEdit(&DCMenu);
	dc.BitBlt(cOrigin.x,cOrigin.y,rcBounds.Width(),rcBounds.Height(),&DCMenu,0,0,SRCCOPY);
	DCMenu.SelectObject(oldBit);
	DCMenu.SelectObject(pOldPen);
	penG01.DeleteObject();
	DeleteObject(DCMenu);
}
void CRectEditDlg::DrawRectEdit(CDC* pDCMenu)
{
	for(p_stuRectEdit pRectInf=p_FirstRectInf;pRectInf;pRectInf=pRectInf->Next)
	{
		if (pRectInf->dpRect.x>0 && pRectInf->dpRect.y>0 && pRectInf->nNumX>0 && pRectInf->nNumY>0)
		{
			DrawRect(pDCMenu,pRectInf->dpStart.x,pRectInf->dpStart.y,
				pRectInf->nNumY*pRectInf->dpRect.x,
				pRectInf->nNumX*pRectInf->dpRect.y);
			for(int nRow=0;nRow<=pRectInf->nNumX;nRow++)
			{
				DrawLine(pDCMenu,pRectInf->dpStart.x,pRectInf->dpStart.y+nRow*pRectInf->dpRect.y,
					pRectInf->dpStart.x+pRectInf->nNumY*pRectInf->dpRect.x,pRectInf->dpStart.y+nRow*pRectInf->dpRect.y);
			}
			for (int nCol=0;nCol<=pRectInf->nNumY;nCol++)
			{
				DrawLine(pDCMenu,pRectInf->dpStart.x+nCol*pRectInf->dpRect.x,pRectInf->dpStart.y,
					pRectInf->dpStart.x+nCol*pRectInf->dpRect.x,pRectInf->dpStart.y+pRectInf->nNumX*pRectInf->dpRect.y);
			}
			//写尺寸,画异性
			for(nRow=0;nRow<pRectInf->nNumX;nRow++)
			{
                for (nCol=0;nCol<pRectInf->nNumY;nCol++)
				{
                   //写尺寸
 				   double dScale = 1.0;//字体显示比例
				   if (pRectInf->dpRect.x < 100 || pRectInf->dpRect.y<100)
				   {
					   dScale = 0.2;
				   }
				   else if (pRectInf->dpRect.x < 200 || pRectInf->dpRect.y<200)
				   {
					   dScale = 0.4;
				   }
				   else if (pRectInf->dpRect.x < 400 || pRectInf->dpRect.y<400)
				   {
					   dScale = 0.7;
					}
				   CFont   font; 
				   font.CreateFont((int)(120*dScale*m_dScale),0,0,0,FW_THIN,0,0,0,ANSI_CHARSET,
					   OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
					   DEFAULT_PITCH|FF_ROMAN, "Times New Roman"); 
				   CFont*   pOldFont=(CFont*)pDCMenu->SelectObject(&font);
				   TEXTMETRIC l_tm;
				   pDCMenu->GetTextMetrics(&l_tm);
				   pDCMenu->SetBkMode(TRANSPARENT);
				   pDCMenu->SetTextAlign(TA_CENTER|TA_BOTTOM);
				   pDCMenu->SetTextColor(RGB(0,0,0));//黑字					
				   CString str;
				   str.Format("%d",int(pRectInf->dpRect.x));
				   pDCMenu->TextOut(5+int((pRectInf->dpStart.x+pRectInf->dpRect.x/2+nCol*pRectInf->dpRect.x)*m_dScale),
					   455 - int((pRectInf->dpStart.y+pRectInf->dpRect.y/2+nRow*pRectInf->dpRect.y)*m_dScale),
					   str);	
				   pDCMenu->SetTextAlign(TA_CENTER|TA_TOP);
				   str.Format("%d",int(pRectInf->dpRect.y));
				   pDCMenu->TextOut(5+int((pRectInf->dpStart.x+pRectInf->dpRect.x/2+nCol*pRectInf->dpRect.x)*m_dScale),
					   455 - int((pRectInf->dpStart.y+pRectInf->dpRect.y/2+nRow*pRectInf->dpRect.y)*m_dScale),
					   str);
				   pDCMenu->SelectObject(pOldFont);				   
				   DeleteObject(font);	
				   //画异性
				   DrawGraph(pDCMenu,pRectInf,nRow,nCol);                   
				}
			}
		}       
	}
}

void CRectEditDlg::DrawLine(CDC* pDCMenu,int ox,int oy,int x,int y)
{
	pDCMenu->MoveTo((int)(5+ox*m_dScale),(int)(455-oy*m_dScale));
	pDCMenu->LineTo((int)(5+x*m_dScale),(int)(455-y*m_dScale));
}

void CRectEditDlg::DrawRect(CDC* pDCMenu,int ox,int oy,int x,int y,int nFill)
{
	
	Point2D   dpPosOrign,dpPos;
	POINT P[5];
	
	dpPosOrign.x = (double)ox;
	dpPosOrign.y = (double)oy;
	P[0].x = (int)(5 + dpPosOrign.x*m_dScale);
    P[0].y = (int)(455-dpPosOrign.y*m_dScale);
	dpPos.x = ox+x;
	dpPos.y = oy;
	P[1].x = (int)(5 + dpPos.x*m_dScale);
    P[1].y = (int)(455-dpPos.y*m_dScale);
	
	dpPos.x = ox+x;
	dpPos.y = oy+y;
	P[2].x = (int)(5 + dpPos.x*m_dScale);
    P[2].y = (int)(455-dpPos.y*m_dScale);
	
	dpPos.x = ox;
	dpPos.y = oy+y;
	P[3].x = (int)(5 + dpPos.x*m_dScale);
    P[3].y = (int)(455-dpPos.y*m_dScale);
	
	
	P[4].x = (int)(5 + dpPosOrign.x*m_dScale);
    P[4].y = (int)(455-dpPosOrign.y*m_dScale);
	
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
}

void CRectEditDlg::DrawGraph(CDC* pDCMenu,p_stuRectEdit pRectTemp,int nRow,int nCol)
{
	if (pRectTemp == NULL)
	{
		return;
	}
    CString strCmd = pRectTemp->szGraph;
	if (strCmd.IsEmpty()==TRUE)
		return;
	int			nOffsetX, nOffsetY;
	int			nPos;
	BOOL		bFirstP = TRUE;
	CString		pdcstr;
	CString		strText;
	CString		strRect = strCmd;
	nPos = strCmd.FindOneOf(";");
	strCmd = strCmd.Mid(nPos+1);
	nPos = strCmd.FindOneOf(";");	
	nOffsetX = pRectTemp->dpTrim.x + pRectTemp->dpStart.x + nCol*pRectTemp->dpRect.x;// 左
	nOffsetY = pRectTemp->dpTrim.y + pRectTemp->dpStart.y + nRow*pRectTemp->dpRect.y;// 下 
	
	while( nPos != -1)
	{
		CString pdcpoint;
		pdcstr = strCmd.Left(nPos);
		strCmd = strCmd.Mid(nPos+1);
		nPos = strCmd.FindOneOf(";");
		if(pdcstr.GetAt(0)=='0')
		{
			pdcpoint = pdcstr.Mid(1);
			int nPos;
			double pointx,pointy;
			nPos = pdcpoint.FindOneOf(",");
			pointx = atof(pdcpoint.Left(nPos));
			pointy = atof(pdcpoint.Mid(nPos+1));			
			pDCMenu->MoveTo((int)(5+(nOffsetX+pointx)*m_dScale),(int)(455-(nOffsetY+pointy)*m_dScale));
		}
		else if(pdcstr.GetAt(0)=='1')
		{
			pdcpoint = pdcstr.Mid(1);
			int nPos;
			double pointx,pointy;
			nPos = pdcpoint.FindOneOf(",");
			pointx = atof(pdcpoint.Left(nPos));
			pointy = atof(pdcpoint.Mid(nPos+1));			
			pDCMenu->LineTo((int)(5+(nOffsetX+pointx)*m_dScale),(int)(455-(nOffsetY+pointy)*m_dScale));		
		}
		else if(pdcstr.GetAt(0)=='2')
		{
			pdcpoint = pdcstr.Mid(1);
			int nPos;
			double pointx,pointy,pointR,pointQ,pointD;
			nPos = pdcpoint.FindOneOf(",");
			pointx = atof(pdcpoint.Left(nPos));
			pdcpoint = pdcpoint.Mid(nPos+1);
			nPos = pdcpoint.FindOneOf(",");
			pointy = atof(pdcpoint.Left(nPos));
			pdcpoint = pdcpoint.Mid(nPos+1);
			nPos = pdcpoint.FindOneOf(",");
			pointR = atof(pdcpoint.Left(nPos));

			if(fabs(pointR)<1)
				continue;
			
			pdcpoint = pdcpoint.Mid(nPos+1);
			nPos = pdcpoint.FindOneOf(",");
			pointQ = atof(pdcpoint.Left(nPos));
			pointD = atof(pdcpoint.Mid(nPos+1));

			pDCMenu->AngleArc((int)(5+(nOffsetX+pointx)*m_dScale), 
				455-(int)((nOffsetY+pointy)*m_dScale),
				(int)(pointR*m_dScale),(float)pointQ,(float)pointD);
				
		}
	}
}
void CRectEditDlg::AddNewRectInf()
{
	p_stuRectEdit pRectInf = NULL;
    pRectInf = new stuRectEdit;
	if (pRectInf != NULL)
	{
		memset(pRectInf,0,sizeof(stuRectEdit));
		if (p_FirstRectInf == NULL)
		{
			pRectInf->nIndex = 1;
			p_FirstRectInf = pRectInf;
			p_CurrentRectInf = pRectInf;
		}
		else
		{
			pRectInf->nIndex = p_CurrentRectInf->nIndex+1;
			pRectInf->Prev = p_CurrentRectInf;
			p_CurrentRectInf->Next = pRectInf;
			p_CurrentRectInf = pRectInf;
		}
	}
}

void CRectEditDlg::DeleRectInf()
{
	if (p_CurrentRectInf != NULL)
	{
        if (p_CurrentRectInf == p_FirstRectInf)
        {
			delete(p_CurrentRectInf);
			p_CurrentRectInf = NULL;
			p_FirstRectInf = NULL;
			m_Grid.SetRowCount(1);			
        }
		else
		{
			p_stuRectEdit pTemp;
			pTemp = p_CurrentRectInf;
			p_CurrentRectInf = pTemp->Prev;
			p_CurrentRectInf->Next = NULL;
			delete pTemp;
			pTemp = NULL;
			m_Grid.SetRowCount(p_CurrentRectInf->nIndex+1);			
		}
 	}
}

void CRectEditDlg::DeleAllRectInf()
{
	p_stuRectEdit pTemp = NULL;
	for(p_CurrentRectInf=p_FirstRectInf;p_CurrentRectInf;)
	{
		pTemp = p_CurrentRectInf->Next;
		delete(p_CurrentRectInf);
		p_CurrentRectInf = pTemp;
	}
	p_FirstRectInf = NULL;
}

void CRectEditDlg::OnInitGrid() 
{	
	m_Grid.SubclassDlgItem(IDC_RECTEDIT, this);
	m_Grid.SetFont(&g_fontList);	
	m_Grid.SetEditable(TRUE);
	m_Grid.SetListMode(TRUE);
	m_Grid.SetHeaderSort(FALSE);
	m_Grid.SetRowResize(FALSE);
	m_Grid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));
	
	TRY {
		m_Grid.SetRowCount(1);
		m_Grid.SetColumnCount(13);
		m_Grid.SetFixedRowCount(1);
		m_Grid.SetFixedColumnCount(1);
	}
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		e->Delete();
		return;
	}
    END_CATCH
		
		DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
#ifndef _WIN32_WCE
    dwTextStyle |= DT_END_ELLIPSIS;
#endif	
	int			row, col;
	GV_ITEM Item;
	row = 0;
	for (col = 0; col < m_Grid.GetColumnCount(); col++)
	{
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.row = row;
		Item.col = col;
		Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
		if(!g_iLanguage)
		{
			switch(col) 
			{
			case 0:		Item.szText.Format(_T("序号"));		break;
			case 1:		Item.szText.Format(_T("数量"));		break;
			case 2:		Item.szText.Format(_T("起点X"));	break;
			case 3:		Item.szText.Format(_T("起点Y"));	break;
			case 4:		Item.szText.Format(_T("长度"));		break;
			case 5:		Item.szText.Format(_T("宽度"));		break;
			case 6:		Item.szText.Format(_T("行"));		break;
			case 7:		Item.szText.Format(_T("列"));		break;
			case 8:		Item.szText.Format(_T("异形"));		break;
			case 9:		Item.szText.Format(_T("修边左"));	break;
			case 10:	Item.szText.Format(_T("修边下"));	break;			
			case 11:	Item.szText.Format(_T("终点X"));	break;
			case 12:	Item.szText.Format(_T("终点Y"));	break;			
			default:	break;
			}
		}
		else
		{
			switch(col) 
			{
			case 0:		Item.szText.Format(_T("Index"));		break;
			case 1:		Item.szText.Format(_T("Count"));		break;
			case 2:		Item.szText.Format(_T("First X"));		break;
			case 3:		Item.szText.Format(_T("First Y"));		break;
			case 4:		Item.szText.Format(_T("Lenght"));				break;
			case 5:		Item.szText.Format(_T("Height"));			break;
			case 6:		Item.szText.Format(_T("Row"));		break;
			case 7:		Item.szText.Format(_T("Col"));			break;
			case 8:		Item.szText.Format(_T("Grap"));		break;
			case 9:	    Item.szText.Format(_T("Trim X"));		   break;
			case 10:	Item.szText.Format(_T("Trim Y"));		break;
			case 11:	Item.szText.Format(_T("End X"));		   break;
			case 12:	Item.szText.Format(_T("End Y"));		break;
			default:	break;
			}
		}
		m_Grid.SetItem(&Item);
	}	
	m_Grid.AutoSize();
	m_Grid.SetFocus();	
}

void CRectEditDlg::AddGrid()
{
	if (p_CurrentRectInf != NULL)
	{
		m_Grid.SetRowCount(p_CurrentRectInf->nIndex+1);
		GV_ITEM Item;
		DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
#ifndef _WIN32_WCE
		dwTextStyle |= DT_END_ELLIPSIS;
#endif
		for (int col = 0; col < m_Grid.GetColumnCount(); col++)//行
		{ 
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = p_CurrentRectInf->nIndex;
			Item.col = col;
			
			Item.nFormat = dwTextStyle;
			switch(col) 
			{
			case 0:
				Item.szText.Format(_T("%d"),p_CurrentRectInf->nIndex);	
				break;
			case 1:
				Item.szText.Format(_T("%d"),p_CurrentRectInf->nNumX*p_CurrentRectInf->nNumY);		
				break;
			case 2:
				Item.szText.Format(_T("%.2f"),p_CurrentRectInf->dpStart.x);		
				break;
			case 3:
				Item.szText.Format(_T("%.2f"),p_CurrentRectInf->dpStart.y);		
				break;
			case 4:
				Item.szText.Format(_T("%.2f"),p_CurrentRectInf->dpRect.x);		
				break;
			case 5:
				Item.szText.Format(_T("%.2f"),p_CurrentRectInf->dpRect.y);		
				break;
			case 6:
				Item.szText.Format(_T("%d"),p_CurrentRectInf->nNumX);		
				break;
			case 7:
				Item.szText.Format(_T("%d"),p_CurrentRectInf->nNumY);		
				break;
			case 8:
				Item.szText.Format(_T("%.2f"),0);		
				break;
			case 9:
				Item.szText.Format(_T("%.2f"),p_CurrentRectInf->dpTrim.x);		
				break;
			case 10:
				Item.szText.Format(_T("%.2f"),p_CurrentRectInf->dpTrim.y);		
				break;				
			default:
				break;
			}		
			m_Grid.SetItem(&Item);	
		}
		m_Grid.RedrawRow(p_CurrentRectInf->nIndex);
		m_Grid.SetFocus();
        m_Grid.SetFocusCell(Item.row,2);
	}
}

BOOL CRectEditDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CWnd			*pWnd=NULL;
		char			cClassName[50]={0};
		pWnd = GetFocus();
		GetClassName(pWnd->GetSafeHwnd(), cClassName, 50);//获取控件的类名    
		
		if(strstr(cClassName, "MFCGridCtrl"))
		{ 
			CCellID cell;
			cell = m_Grid.GetFocusCell();			
			if (cell.col>0 && cell.row>0)
			{
				if (cell.col<10)
				{
					m_Grid.SetFocusCell(cell.row,cell.col+1);
				}
				for(p_stuRectEdit pTemp=p_FirstRectInf;pTemp;pTemp = pTemp->Next)
				{
					if (cell.row == pTemp->nIndex)
					{
						break;				
					}		
				}
				if (pTemp==NULL)
				{
					return TRUE;
				}
				pTemp->dpStart.x = atof(m_Grid.GetItemText(cell.row,2));
				pTemp->dpStart.y = atof(m_Grid.GetItemText(cell.row,3));
				pTemp->dpRect.x = atof(m_Grid.GetItemText(cell.row,4));
				pTemp->dpRect.y = atof(m_Grid.GetItemText(cell.row,5));
				pTemp->nNumX = atof(m_Grid.GetItemText(cell.row,6));
				pTemp->nNumY = atof(m_Grid.GetItemText(cell.row,7));
				pTemp->dpTrim.x = atof(m_Grid.GetItemText(cell.row,9));
				pTemp->dpTrim.y = atof(m_Grid.GetItemText(cell.row,10));
				CString str;
				str.Format("%d",pTemp->nNumX*pTemp->nNumY);
				m_Grid.SetItemText(cell.row,1,str);
				str.Format("%.2f",pTemp->dpStart.x + pTemp->dpRect.x*pTemp->nNumY);
				m_Grid.SetItemText(cell.row,11,str);
				str.Format("%.2f",pTemp->dpStart.y + pTemp->dpRect.y*pTemp->nNumX);
				m_Grid.SetItemText(cell.row,12,str);
				if ((pTemp->dpStart.y+pTemp->dpRect.y*pTemp->nNumX > (double)g_stu_pAxisB->sSpareB)
					||(pTemp->dpStart.x + pTemp->dpRect.x*pTemp->nNumY > (double)g_stu_pAxisB->sSpareA))
				{
					if(g_iLanguage==0)
						MessageBox("当前图形轨迹,超过玻璃尺寸!\r\n请重新输入!");
					else
						MessageBox("The current graphics trajectory,More than the glass size!");
					return TRUE;
				}
                if (StartPosIsRect(pTemp))
                {
					if(g_iLanguage==0)
						MessageBox("当前图形轨迹,在已用玻璃上!\r\n请重新输入!");
					else
						MessageBox("The current graphics trajectory, on the glass has been used!");
					return TRUE;
                }
				if (pTemp->dpRect.x>0 && pTemp->dpRect.y>0)
				{
					CString str;
					str = pTemp->szGraph;
					if (!str.IsEmpty())
					{
						POINT2D pRect;
						pRect.x = pTemp->dpRect.x - pTemp->dpTrim.x;
						pRect.y = pTemp->dpRect.y - pTemp->dpTrim.y;					
						
						int nPos = str.FindOneOf(",");
						double dx = atof(str.Left(nPos));
						double dy = atof(str.Mid(nPos+1));
						if (dx>pRect.x || dy>pRect.y)
						{
							if(g_iLanguage==0)
								MessageBox("图形太大，不能插入矩形!");
							else
								MessageBox("Graphic is too big, can't insert the rectangle!");
							return TRUE;
						}						
					}
								
				}				
				m_Grid.RedrawRow(cell.row);
				CRect rect(4,50,721,504);
				InvalidateRect(rect,FALSE);
			}
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CRectEditDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (wParam != MAKELONG(IDC_RECTEDIT, BN_CLICKED))
	{
		return CDialog::OnCommand(wParam, lParam);
	}
	CDlg_KeyNumber	KeyNum;
	CString			strCell;
	CCellID			*pCell=NULL;
	CWnd			*pWnd=NULL;
	char			cClassName[50]={0};
	
	pWnd = GetFocus();
	GetClassName(pWnd->GetSafeHwnd(), cClassName, 50);//获取控件的类名    
	
	if(strstr(cClassName, "MFCGridCtrl") || strstr(cClassName, "Edit"))
	{
		pCell = &(m_Grid.GetFocusCell());
		if (pCell->col == 8)
		{
			POINT2D pRect;
			pRect.x = atof(m_Grid.GetItemText(pCell->row,4)) - atof(m_Grid.GetItemText(pCell->row,9));
			pRect.y = atof(m_Grid.GetItemText(pCell->row,5)) - atof(m_Grid.GetItemText(pCell->row,10));
			if (pRect.x>0 && pRect.y>0)
			{
				CGraphDlg	dlg_graphLib;
				dlg_graphLib.m_bRectEdit = true;
				dlg_graphLib.m_Rect = pRect;
				dlg_graphLib.DoModal();			
			}
			
		}
		else
		{
			if(g_stu_pAxisC->bSpareA==0)
				return CDialog::OnCommand(wParam, lParam);
			strCell = m_Grid.GetItemText(pCell->row, pCell->col);
			KeyNum.m_strNew = KeyNum.m_strOld = strCell;
			if(KeyNum.DoModal()==IDOK)/* 触摸屏选项 */
			{
				m_Grid.SetItemText(pCell->row, pCell->col, KeyNum.m_strNew);
				m_Grid.RedrawCell(pCell->row, pCell->col);
				
			}
		}
		CCellID cell;
		cell = m_Grid.GetFocusCell();			
		if (cell.col>0 && cell.row>0)
		{			
			for(p_stuRectEdit pTemp=p_FirstRectInf;pTemp;pTemp = pTemp->Next)
			{
				if (cell.row == pTemp->nIndex)
				{
					break;				
				}		
			}
			if (pTemp==NULL)
			{
				return TRUE;
			}
			pTemp->dpStart.x = atof(m_Grid.GetItemText(cell.row,2));
			pTemp->dpStart.y = atof(m_Grid.GetItemText(cell.row,3));
			pTemp->dpRect.x = atof(m_Grid.GetItemText(cell.row,4));
			pTemp->dpRect.y = atof(m_Grid.GetItemText(cell.row,5));
			pTemp->nNumX = atof(m_Grid.GetItemText(cell.row,6));
			pTemp->nNumY = atof(m_Grid.GetItemText(cell.row,7));
			pTemp->dpTrim.x = atof(m_Grid.GetItemText(cell.row,9));
			pTemp->dpTrim.y = atof(m_Grid.GetItemText(cell.row,10));
			CString str;
			str.Format("%d",pTemp->nNumX*pTemp->nNumY);
			m_Grid.SetItemText(cell.row,1,str);
			str.Format("%.2f",pTemp->dpStart.x + pTemp->dpRect.x*pTemp->nNumY);
			m_Grid.SetItemText(cell.row,11,str);
			str.Format("%.2f",pTemp->dpStart.y + pTemp->dpRect.y*pTemp->nNumX);
			m_Grid.SetItemText(cell.row,12,str);
			if ((pTemp->dpStart.y+pTemp->dpRect.y*pTemp->nNumX > (double)g_stu_pAxisB->sSpareB)
				||(pTemp->dpStart.x + pTemp->dpRect.x*pTemp->nNumY > (double)g_stu_pAxisB->sSpareA))
			{
				if(g_iLanguage==0)
					MessageBox("当前图形轨迹,超过玻璃尺寸!\r\n请重新输入!");
				else
                    MessageBox("The current graphics trajectory,More than the glass size!");
				return TRUE;
			}
			if (StartPosIsRect(pTemp))
			{
				if(g_iLanguage==0)
					MessageBox("当前图形轨迹,在已用玻璃上!\r\n请重新输入!");
				else
                    MessageBox("The current graphics trajectory, on the glass has been used!");
				return TRUE;
			}
			if (pTemp->dpRect.x>0 && pTemp->dpRect.y>0)
			{
				CString str;
				str = pTemp->szGraph;
				if (!str.IsEmpty())
				{
					POINT2D pRect;
					pRect.x = pTemp->dpRect.x - pTemp->dpTrim.x;
					pRect.y = pTemp->dpRect.y - pTemp->dpTrim.y;					
					
					int nPos = str.FindOneOf(",");
					double dx = atof(str.Left(nPos));
					double dy = atof(str.Mid(nPos+1));
					if (dx>pRect.x || dy>pRect.y)
					{
						if(g_iLanguage==0)
							MessageBox("图形太大，不能插入矩形!");
						else
                            MessageBox("Graphic is too big, can't insert the rectangle!");
						return TRUE;
					}						
				}
				
			}				
			m_Grid.RedrawRow(cell.row);
			CRect rect(4,50,721,504);
			InvalidateRect(rect,FALSE);
		}
	}				
	return CDialog::OnCommand(wParam, lParam);
}

//新建
void CRectEditDlg::OnButtonF1()
{
    AddNewRectInf();
	AddGrid();
}

//删除
void CRectEditDlg::OnButtonF2()
{
	DeleRectInf();
	CRect rect(4,50,721,504);
	InvalidateRect(rect,FALSE);
}

//保存G
void CRectEditDlg::OnButtonF3()
{
	if (p_FirstRectInf!=NULL &&p_FirstRectInf->dpRect.x>0 
		&& p_FirstRectInf->dpRect.y>0 && p_FirstRectInf->nNumX>0 
		&& p_FirstRectInf->nNumY>0)
	{
		dlg_save  dlgSave;
		dlgSave.strExtName = ".g";
		if (IDCANCEL == dlgSave.DoModal())	return;
		if(g_strSavefile.IsEmpty())			return;
		SaveGcode();
	}

}

//发送
void CRectEditDlg::OnButtonF4()
{
	if (p_FirstRectInf!=NULL &&p_FirstRectInf->dpRect.x>0 
		&& p_FirstRectInf->dpRect.y>0 && p_FirstRectInf->nNumX>0 
		&& p_FirstRectInf->nNumY>0)
	{
		g_strSavefile = "Rect.g";
		SaveGcode();
		CDialog::OnOK();
	}
}

//返回
void CRectEditDlg::OnButtonF5()
{
	CDialog::OnCancel();
}

BOOL CRectEditDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	// TODO: Add your message handler code here and/or call default
	CString	strTemp;
	strTemp.Format("%s", (char*)pCopyDataStruct->lpData);	
	CCellID cell;
	cell = m_Grid.GetFocusCell();
	if(pCopyDataStruct->dwData==0)
	{
		if (cell.col>0 && cell.row>0)
		{			
			m_Grid.SetItemText(cell.row,8,strTemp);
			m_Grid.RedrawRow(cell.row);			
		}	
	}
 	else if(pCopyDataStruct->dwData==1)
	{        
		for(p_stuRectEdit pTemp=p_FirstRectInf;pTemp;pTemp = pTemp->Next)
		{
			if (cell.row == pTemp->nIndex)
			{
			    strcpy(pTemp->szGraph,strTemp);	
				break;
			}		
		}	
	}
	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

void CRectEditDlg::OnCancel()
{

}

void CRectEditDlg::OnOK()
{

}

void CRectEditDlg::SaveGcode()
{
	CString strFilename;
	CString		strUp,strDown;	
	strFilename = g_strOriginalPathD+"gcode\\"+g_strSavefile;
	g_strShowName = g_strSavefile;
	g_strGfile = strFilename;
    g_strSavefile = "";
	FILE		*fileG;
	if (!(fileG = fopen(strFilename, "wt")))
	{
		MessageBox("Could not open file!","error",MB_OK|MB_ICONINFORMATION);
		return;
	}
	WriteLittleInf(fileG);
	if(g_stu_pAxisA->bSpareA)	/* 注油 */
	{
		strUp = "M14\n";
		strDown = "M13\n";
	}
	else						/* 不注油 */
	{
		strUp = "M10\n";
		strDown = "M09\n";
	}
	fprintf(fileG, "G90\n");
	for(p_stuRectEdit pRectInf=p_FirstRectInf;pRectInf;pRectInf=pRectInf->Next)
	{
		if (pRectInf->dpRect.x>0 && pRectInf->dpRect.y>0 && pRectInf->nNumX>0 && pRectInf->nNumY>0)
		{			
			for(int nRow=0;nRow<=pRectInf->nNumX;nRow++)
			{
				if (((g_stu_pAxisB->sSpareB - (pRectInf->dpStart.y+nRow*pRectInf->dpRect.y)) > g_stu_pAxisH->dSpareC)
					&&((pRectInf->dpStart.y+nRow*pRectInf->dpRect.y)>g_stu_pAxisH->dSpareC))
				{
					//横线起点的安全距离
					double dStart = pRectInf->dpStart.x;
                    //横线终点的安全距离
					double dEnd=pRectInf->dpStart.x+pRectInf->nNumY*pRectInf->dpRect.x;
                    double dX1,dX2;
					int nReturn = CombinationLineX(pRectInf,pRectInf->dpStart.y+nRow*pRectInf->dpRect.y,
						dStart,dEnd,dX1,dX2);
					if (nReturn == 0)//不合并
					{
						if(pRectInf->dpStart.x < g_stu_pAxisH->dSpareC)
							dStart = g_stu_pAxisH->dSpareC;
						if(dEnd > g_stu_pAxisB->sSpareA-g_stu_pAxisH->dSpareC)
							dEnd = g_stu_pAxisB->sSpareA-g_stu_pAxisH->dSpareC;
						fprintf(fileG, strUp);
						fprintf(fileG, "G00X%.2f,Y%.2f\n",dStart,pRectInf->dpStart.y+nRow*pRectInf->dpRect.y);
						fprintf(fileG, strDown);
						fprintf(fileG, "G01X%.2f,Y%.2f\n",dEnd,pRectInf->dpStart.y+nRow*pRectInf->dpRect.y);					
					}	
					else if (nReturn == 1)//合并
					{
						if(dX1 < g_stu_pAxisH->dSpareC)
							dX1 = g_stu_pAxisH->dSpareC;
						if(dX2 > g_stu_pAxisB->sSpareA-g_stu_pAxisH->dSpareC)
							dX2 = g_stu_pAxisB->sSpareA-g_stu_pAxisH->dSpareC;
						fprintf(fileG, strUp);
						fprintf(fileG, "G00X%.2f,Y%.2f\n",dX1,pRectInf->dpStart.y+nRow*pRectInf->dpRect.y);
						fprintf(fileG, strDown);
						fprintf(fileG, "G01X%.2f,Y%.2f\n",dX2,pRectInf->dpStart.y+nRow*pRectInf->dpRect.y);		
					}
				}

			}
			for (int nCol=0;nCol<=pRectInf->nNumY;nCol++)
			{	
				if (((g_stu_pAxisB->sSpareA - (pRectInf->dpStart.x+nCol*pRectInf->dpRect.x)) > g_stu_pAxisH->dSpareC)
					&&((pRectInf->dpStart.x+nCol*pRectInf->dpRect.x)>g_stu_pAxisH->dSpareC))
				{
					//竖线起点的安全距离
					double dStart = pRectInf->dpStart.y;
                  //竖线终点的安全距离
					double dEnd=pRectInf->dpStart.y+pRectInf->nNumX*pRectInf->dpRect.y;
                    double dY1,dY2;
					int nReturn = CombinationLineY(pRectInf,pRectInf->dpStart.x+nCol*pRectInf->dpRect.x,
						dStart,dEnd,dY1,dY2);
					if (nReturn == 0)//不合并
					{
						if(dStart < g_stu_pAxisH->dSpareC)
							dStart = g_stu_pAxisH->dSpareC;
						if(dEnd > g_stu_pAxisB->sSpareB-g_stu_pAxisH->dSpareC)
							dEnd = g_stu_pAxisB->sSpareB-g_stu_pAxisH->dSpareC;
						fprintf(fileG, strUp);
						fprintf(fileG, "G00X%.2f,Y%.2f\n",pRectInf->dpStart.x+nCol*pRectInf->dpRect.x,dStart);
						fprintf(fileG, strDown);
						fprintf(fileG, "G01X%.2f,Y%.2f\n",pRectInf->dpStart.x+nCol*pRectInf->dpRect.x,dEnd);					
					}
					else if (nReturn == 1)
					{
						if(dY1 < g_stu_pAxisH->dSpareC)
							dY1 = g_stu_pAxisH->dSpareC;
						if(dY2 > g_stu_pAxisB->sSpareB-g_stu_pAxisH->dSpareC)
							dY2 = g_stu_pAxisB->sSpareB-g_stu_pAxisH->dSpareC;
						fprintf(fileG, strUp);
						fprintf(fileG, "G00X%.2f,Y%.2f\n",pRectInf->dpStart.x+nCol*pRectInf->dpRect.x,dY1);
						fprintf(fileG, strDown);
						fprintf(fileG, "G01X%.2f,Y%.2f\n",pRectInf->dpStart.x+nCol*pRectInf->dpRect.x,dY2);	
					}					
				}
			}
			//写异性g
			int nDown=0;//是否已经下刀0没有;1已经下过
			CString strCmd = pRectInf->szGraph;
			if (strCmd.IsEmpty()==TRUE)
			{			
				continue;
			}
			for(nRow=0;nRow<pRectInf->nNumX;nRow++)
			{
                for (nCol=0;nCol<pRectInf->nNumY;nCol++)
				{					
					int			nOffsetX, nOffsetY;
					int			nPos;
					BOOL		bFirstP = TRUE;
					CString		pdcstr;
					CString		strText;
					strCmd = pRectInf->szGraph;
					nPos = strCmd.FindOneOf(";");
					strCmd = strCmd.Mid(nPos+1);
					nPos = strCmd.FindOneOf(";");	
					nOffsetX = pRectInf->dpTrim.x + pRectInf->dpStart.x + nCol*pRectInf->dpRect.x;// 左
					nOffsetY = pRectInf->dpTrim.y + pRectInf->dpStart.y + nRow*pRectInf->dpRect.y;// 下 
             
					//写异性g
					while( nPos != -1)
					{
						CString pdcpoint;
						pdcstr = strCmd.Left(nPos);
						strCmd = strCmd.Mid(nPos+1);
						nPos = strCmd.FindOneOf(";");
						if(pdcstr.GetAt(0)=='0')
						{
							pdcpoint = pdcstr.Mid(1);
							int nPos;
							double pointx,pointy;
							nPos = pdcpoint.FindOneOf(",");
							pointx = atof(pdcpoint.Left(nPos));
							pointy = atof(pdcpoint.Mid(nPos+1));						
							fprintf(fileG, strUp);
							fprintf(fileG, "G00X%.2f,Y%.2f\n",nOffsetX+pointx,nOffsetY+pointy);
							nDown = 0;

						}
						else if(pdcstr.GetAt(0)=='1')
						{
							pdcpoint = pdcstr.Mid(1);
							int nPos;
							double pointx,pointy;
							nPos = pdcpoint.FindOneOf(",");
							pointx = atof(pdcpoint.Left(nPos));
							pointy = atof(pdcpoint.Mid(nPos+1));
							if (nDown == 0)
							{
								fprintf(fileG, strDown);
								nDown = 1;
							}
							fprintf(fileG, "G01X%.2f,Y%.2f\n",nOffsetX+pointx,nOffsetY+pointy);

						}
						else if(pdcstr.GetAt(0)=='2')
						{
							pdcpoint = pdcstr.Mid(1);
							int nPos;
							double pointx,pointy,pointR,pointQ,pointD;
							nPos = pdcpoint.FindOneOf(",");
							pointx = atof(pdcpoint.Left(nPos));
							pdcpoint = pdcpoint.Mid(nPos+1);
							nPos = pdcpoint.FindOneOf(",");
							pointy = atof(pdcpoint.Left(nPos));
							pdcpoint = pdcpoint.Mid(nPos+1);
							nPos = pdcpoint.FindOneOf(",");
							pointR = atof(pdcpoint.Left(nPos));
							
							if(fabs(pointR)<1)
								continue;
							
							pdcpoint = pdcpoint.Mid(nPos+1);
							nPos = pdcpoint.FindOneOf(",");
							pointQ = atof(pdcpoint.Left(nPos));
							pointD = atof(pdcpoint.Mid(nPos+1));					
							

							double Gendx=pointR*cos((pointQ+pointD)*PI/180)+nOffsetX+pointx;
							double Gendy=pointR*sin((pointQ+pointD)*PI/180)+nOffsetY+pointy;
							double fI=-pointR*cos(pointQ*PI/180);
							double fJ=-pointR*sin(pointQ*PI/180);
							if (nDown == 0)
							{
								fprintf(fileG, strDown);
								nDown = 1;
							}
							if(pointD>0)
							{
								fprintf(fileG, "G03 X%f Y%f I%f J%f\n",Gendx,Gendy,fI,fJ);								
							}
							else
							{
								fprintf(fileG, "G02 X%f Y%f I%f J%f\n",Gendx,Gendy,fI,fJ);								
							}				
						}
					}                 
				}
			}//写异性g
		}       
	}
	fprintf(fileG, strUp);
	fprintf(fileG, "G90G00X0Y0Z0\n");
	if(g_stu_pAxisG->bSpare)
		fprintf(fileG, "M99\n");
	fprintf(fileG, "M30\n");
	fclose(fileG);	
}

//写小片信息
void CRectEditDlg::WriteLittleInf(FILE *file)
{
	FILE *fileG = file;
	int nNO = 0;
	CString strWrite;
	fprintf(fileG, "N%02d   P%4d=%d\n",nNO,3000+nNO,g_stu_pAxisB->sSpareA);//原片X方向尺寸
	nNO++;
	fprintf(fileG, "N%02d   P%4d=%d\n",nNO,3000+nNO,g_stu_pAxisB->sSpareB);//原片Y方向尺寸
	nNO++;
	fprintf(fileG, "N%02d   P%4d=%d\n",nNO,3000+nNO,0);//代表原片X1修边
	nNO++;
	fprintf(fileG, "N%02d   P%4d=%d\n",nNO,3000+nNO,0);//代表原片Y1修边
	nNO++;
	fprintf(fileG, "N%02d   P%4d=%d\n",nNO,3000+nNO,0);//代表原片X2修边
	nNO++;
	fprintf(fileG, "N%02d   P%4d=%d\n",nNO,3000+nNO,0);//代表原片Y2修边
	nNO++;
	fprintf(fileG, "N%02d   P%4d=%d\n",nNO,3000+nNO,1);//代表原片数量
	nNO++;	
    nNO = 11;
	//写尺寸
	for(p_stuRectEdit pRectInf=p_FirstRectInf;pRectInf;pRectInf=pRectInf->Next)
	{
		for(int nRow=0;nRow<pRectInf->nNumX;nRow++)
		{
			for (int nCol=0;nCol<pRectInf->nNumY;nCol++)
			{
				if (((g_stu_pAxisB->sSpareA - (pRectInf->dpStart.x+(nCol+1)*pRectInf->dpRect.x)) > g_stu_pAxisH->dSpareC)
					&& ((g_stu_pAxisB->sSpareB - (pRectInf->dpStart.y+(nRow+1)*pRectInf->dpRect.y)) > g_stu_pAxisH->dSpareC))
				{
		    		fprintf(fileG, "N%2d   P%4d=%.0f_%.0f_%.0f_%.0f_%.0f_%.0f___\n",
						nNO,4000+nNO,pRectInf->dpRect.x,pRectInf->dpRect.y,pRectInf->dpStart.x+nCol*pRectInf->dpRect.x,
						pRectInf->dpStart.y+nRow*pRectInf->dpRect.y,pRectInf->dpRect.x,pRectInf->dpRect.y);//原片X方向尺寸
					nNO++;
				}
			}
		}		
	}
}

//合并横线，当前的矩形指针，起点的dx1，终点的dx2. 合并后的。
//返回0需要不合并，返回1需要合并，返回2本直线不处理,已经被合并过。
int CRectEditDlg::CombinationLineX(p_stuRectEdit pEditTemp,double dy,double dx1,double dx2,double &d1,double &d2)
{
	int nCom=0;
	for(p_stuRectEdit pRectInf=p_FirstRectInf;pRectInf;pRectInf=pRectInf->Next)
	{
		if(pRectInf == pEditTemp)
			continue;
        for(int nRow=0;nRow<=pRectInf->nNumX;nRow++)
		{

			if (fabs(dy-(pRectInf->dpStart.y+nRow*pRectInf->dpRect.y))>0.01)
			{
				continue;//不同的横线上
			}
			//横线起点
			double dStartX = pRectInf->dpStart.x;
			//横线终点
			double dEndX=pRectInf->dpStart.x+pRectInf->nNumY*pRectInf->dpRect.x;
			
			if (dStartX>dx1&&(dStartX-dx2)>0.01)//dx在左边
			{
				continue;
			}
            else if ((dx1-dEndX)>0.01&&dx2>dEndX)//在右边
            {
				continue;
            }
			else if((dx1>dStartX&&dx2<dEndX)||(fabs(dx1-dStartX)<0.01&&dx2<dEndX)
				||(dx1>dStartX&&fabs(dx2-dEndX)<0.01))//在内部
			{
                return 2;
			}
			else if((dx1<dStartX&&dx2>dEndX)||(fabs(dx1-dStartX)<0.01&&dx2>dEndX)
				||(fabs(dx2-dEndX)<0.01&&dx1<dStartX))//在外部
			{
               continue;
			}
			else if(fabs(dx1-dStartX)<0.01&&fabs(dx2-dEndX)<0.01)//重合
			{
				if (pEditTemp->nIndex > pRectInf->nIndex)//在后面舍去
				{
					return 2;
				}
			}
            else if(fabs(dx2-dStartX)<0.01)//dx的右边刚好相接
            {
			    d1 = dx1;
				dx2 = dEndX;
				d2 = dEndX;
				nCom = 1;
            }
			else if(dStartX>dx1&&dx2>dStartX&&dEndX>dx2)//dx的右边有相接，并有重合
			{
                d1 = dx1;
			    dx2 = dEndX;
			    d2 = dEndX;
			    nCom = 1;
			}
			else if(fabs(dx1-dEndX)<0.01)//dx的左边刚好相接
			{
                return 2;
			}
			else if (dx1>dStartX&&dEndX>dx1&&dx2>dEndX)//dx的左边有相接，并有重合
			{
			    return 2;
			}		
		}
	}
	if (nCom==1)
	{
		return 1;
	}
	return 0;
}

//合并横线，当前的矩形指针，起点的dy1，终点的dy2. 合并后的。
//返回0需要不合并，返回1需要合并，返回2本直线不处理,已经被合并过。
//向上合并，下边舍去
int CRectEditDlg::CombinationLineY(p_stuRectEdit pEditTemp,double dx,double dy1,double dy2,double &d1,double &d2)
{
	int nCom=0;
	for(p_stuRectEdit pRectInf=p_FirstRectInf;pRectInf;pRectInf=pRectInf->Next)
	{
		if(pRectInf == pEditTemp)
			continue;
        for(int nCol=0;nCol<=pRectInf->nNumY;nCol++)
		{
			
			if (fabs(dx-(pRectInf->dpStart.x+nCol*pRectInf->dpRect.x))>0.01)
			{
				continue;//不同的横线上
			}
			//横线起点
			double dStartY = pRectInf->dpStart.y;
			//横线终点
			double dEndY=pRectInf->dpStart.y+pRectInf->nNumX*pRectInf->dpRect.y;
			
			if (dStartY>dy1&&(dStartY-dy2)>0.01)//dx在下边
			{
				continue;
			}
            else if ((dy1-dEndY)>0.01&&dy2>dEndY)//dx在上边
            {
				continue;
            }
			else if((dy1>dStartY&&dy2<dEndY)||(fabs(dy1-dStartY)<0.01&&dy2<dEndY)
				||(dy1>dStartY&&fabs(dy2-dEndY)<0.01))//在内部
			{
                return 2;
			}
			else if((dy1<dStartY&&dy2>dEndY)||(fabs(dy1-dStartY)<0.01&&dy2>dEndY)
				||(fabs(dy2-dEndY)<0.01&&dy1<dStartY))//在外部
			{
				continue;
			}
			else if(fabs(dy1-dStartY)<0.01&&fabs(dy2-dEndY)<0.01)//重合
			{
				if (pEditTemp->nIndex > pRectInf->nIndex)//在后面舍去
				{
					return 2;
				}
			}
            else if(fabs(dy2-dStartY)<0.01)//dx的上边刚好相接
            {
				d1 = dy1;
				dy2 = dEndY;
				d2 = dEndY;
				nCom = 1;
            }
			else if(dStartY>dy1&&dy2>dStartY&&dEndY>dy2)//dx的上边有相接，并有重合
			{
                d1 = dy1;
				dy2 = dEndY;
				d2 = dEndY;
				nCom = 1;
			}
			else if(fabs(dy1-dEndY)<0.01)//dx的下边刚好相接
			{
                return 2;
			}
			else if (dy1>dStartY&&dEndY>dy1&&dy2>dEndY)//dx的下边有相接，并有重合
			{
				return 2;
			}		
		}
	}
	if (nCom==1)
	{
		return 1;
	}
	return 0;
}

//判断起点在不在已有的范围内。有返回true
bool CRectEditDlg::StartPosIsRect(p_stuRectEdit pEditTemp)
{
    for(p_stuRectEdit pRectInf=p_FirstRectInf;pRectInf;pRectInf=pRectInf->Next)
	{
		if (pRectInf == pEditTemp)
		{
			return false;
		}
		//左下角
		if ((pEditTemp->dpStart.x>=pRectInf->dpStart.x) && (pEditTemp->dpStart.x<pRectInf->dpStart.x + pRectInf->dpRect.x*pRectInf->nNumY)
			&&(pEditTemp->dpStart.y>=pRectInf->dpStart.y) && (pEditTemp->dpStart.y<pRectInf->dpStart.y+pRectInf->dpRect.y*pRectInf->nNumX))
		{
			return true;
		}
		//右下角
		if ((pEditTemp->dpStart.x+pEditTemp->dpRect.x*pEditTemp->nNumY>=pRectInf->dpStart.x) && (pEditTemp->dpStart.x<pRectInf->dpStart.x + pRectInf->dpRect.x*pRectInf->nNumY)
			&&(pEditTemp->dpStart.y>=pRectInf->dpStart.y) && (pEditTemp->dpStart.y<pRectInf->dpStart.y+pRectInf->dpRect.y*pRectInf->nNumX))
		{
			return true;
		}
		//左上角
		if ((pEditTemp->dpStart.x>=pRectInf->dpStart.x) && (pEditTemp->dpStart.x<pRectInf->dpStart.x + pRectInf->dpRect.x*pRectInf->nNumY)
			&&(pEditTemp->dpStart.y+pEditTemp->dpRect.y*pEditTemp->nNumX>=pRectInf->dpStart.y) && (pEditTemp->dpStart.y<pRectInf->dpStart.y+pRectInf->dpRect.y*pRectInf->nNumX))
		{
			return true;
		}
		//右上角
		if ((pEditTemp->dpStart.x+pEditTemp->dpRect.x*pEditTemp->nNumY>=pRectInf->dpStart.x) && (pEditTemp->dpStart.x<pRectInf->dpStart.x + pRectInf->dpRect.x*pRectInf->nNumY)
			&&(pEditTemp->dpStart.y+pEditTemp->dpRect.y*pEditTemp->nNumX>=pRectInf->dpStart.y) && (pEditTemp->dpStart.y<pRectInf->dpStart.y+pRectInf->dpRect.y*pRectInf->nNumX))
		{
			return true;
		}	
	}
	return false;
}
