// Dlg_DrawCad.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_DrawCad.h"
#include "Dlg_KeyNumber.h"
#include "dlg_save.h"
#include "dlg_path2.h"
#include "Dlg_KeyNumber.h"
#include "benderDlg.h"
#include "SetXY.h"
#include <vector>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_DrawCad dialog


CDlg_DrawCad::CDlg_DrawCad(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_DrawCad::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_DrawCad)
	m_dBeginX = 0.0;
	m_dBeginY = 0.0;
	m_dEndX = 0.0;
	m_dEndY = 0.0;
	m_dMidX = 0.0;
	m_dMidY = 0.0;
	m_nRdoTool = 0;
	//}}AFX_DATA_INIT
	bookImageList.Create(16,16,ILC_COLOR32,2,2); 
	m_nScrollMinPos = 0;
	m_nScrollMaxPos = 100;
	m_bClickTree	= FALSE;
	m_unLeft = 0;
	m_unRight = 0;
	m_unUp = 0;
	m_unDown = 0;
}

void CDlg_DrawCad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_DrawCad)
	DDX_Control(pDX, IDC_BUTTON_PAN, m_clrBMove);
	DDX_Control(pDX, IDC_BUTTON_ZOOM, m_clrBZoom);
	DDX_Control(pDX, IDC_BUTTON_GRID2, m_clrbGrid2);
	DDX_Control(pDX, IDC_BUTTON_GRID, m_clrbGrid);
	DDX_Control(pDX, IDC_BUTTON_SPACE, m_clrbSpace);
	DDX_Control(pDX, IDC_BUTTON_FORWORD, m_clrbReverse);
	DDX_Control(pDX, IDC_BUTTON_UP, m_clrbUp);
	DDX_Control(pDX, IDC_BUTTON_DOWN, m_clrbDown);
	DDX_Control(pDX, IDC_BUTTON_AGAIN, m_clrbAgain);
	DDX_Control(pDX, IDC_BUTTON_SORT, m_clrbSort);
	DDX_Control(pDX, IDC_BUTTON_PICKUP, m_clrbPickUp);
	DDX_Control(pDX, IDC_STATIC_BEGIN, m_stcBegin);
	DDX_Control(pDX, IDC_STATIC_END, m_stcEnd);
	DDX_Control(pDX, IDC_STATIC_MID, m_stcMid);
	DDX_Control(pDX, IDC_EDIT_MIDY, m_edtMidY);
	DDX_Control(pDX, IDC_EDIT_MIDX, m_edtMidX);
	DDX_Control(pDX, IDC_EDIT_ENDY, m_edtEndY);
	DDX_Control(pDX, IDC_EDIT_ENDX, m_edtEndX);
	DDX_Control(pDX, IDC_EDIT_BEGINY, m_edtBeginY);
	DDX_Control(pDX, IDC_EDIT_BEGINX, m_edtBeginX);
	DDX_Control(pDX, IDC_SCROLLBAR_Y, m_ocxScrollY);
	DDX_Control(pDX, IDC_SCROLLBAR_X, m_ocxScrollX);
	DDX_Control(pDX, IDC_TREECTL, m_TreeCtl);
	DDX_Control(pDX, IDC_GRIDCADCTRL, m_GridCad);
	DDX_Text(pDX, IDC_EDIT_BEGINX, m_dBeginX);
	DDX_Text(pDX, IDC_EDIT_BEGINY, m_dBeginY);
	DDX_Text(pDX, IDC_EDIT_ENDX, m_dEndX);
	DDX_Text(pDX, IDC_EDIT_ENDY, m_dEndY);
	DDX_Text(pDX, IDC_EDIT_MIDX, m_dMidX);
	DDX_Text(pDX, IDC_EDIT_MIDY, m_dMidY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_DrawCad, CDialog)
	//{{AFX_MSG_MAP(CDlg_DrawCad)
	ON_BN_CLICKED(IDC_BUTTON_CS8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON_CS7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON_CS1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON_CS3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON_CS4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON_CS5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON_CS6, OnButton6)
	ON_WM_TIMER()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREECTL, OnSelchangedTreectl)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_NOTIFY(NM_CLICK, IDC_TREECTL, OnClickTreectl)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	ON_EN_SETFOCUS(IDC_EDIT_BEGINX, OnSetfocusEditBeginx)
	ON_EN_SETFOCUS(IDC_EDIT_BEGINY, OnSetfocusEditBeginy)
	ON_EN_SETFOCUS(IDC_EDIT_MIDX, OnSetfocusEditMidx)
	ON_EN_SETFOCUS(IDC_EDIT_MIDY, OnSetfocusEditMidy)
	ON_EN_SETFOCUS(IDC_EDIT_ENDX, OnSetfocusEditEndx)
	ON_EN_SETFOCUS(IDC_EDIT_ENDY, OnSetfocusEditEndy)
	ON_EN_KILLFOCUS(IDC_EDIT_BEGINX, OnKillfocusEditPosition)
	ON_BN_CLICKED(IDC_BUTTON_CS10, OnButtonCs10)
	ON_BN_CLICKED(IDC_BUTTON_SPACE, OnButtonSpace)
	ON_BN_CLICKED(IDC_BUTTON_GRID, OnButtonGrid)
	ON_BN_CLICKED(IDC_BUTTON_UP, OnButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, OnButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_FORWORD, OnButtonForword)
	ON_BN_CLICKED(IDC_BUTTON_PICKUP, OnButtonPickup)
	ON_BN_CLICKED(IDC_BUTTON_SORT, OnButtonSort)
	ON_BN_CLICKED(IDC_BUTTON_GRID2, OnButtonGrid2)
	ON_BN_CLICKED(IDC_BUTTON_AGAIN, OnButtonAgain)
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_BUTTON_ZOOM, OnButtonZoom)
	ON_EN_KILLFOCUS(IDC_EDIT_BEGINY, OnKillfocusEditPosition)
	ON_EN_KILLFOCUS(IDC_EDIT_ENDX, OnKillfocusEditPosition)
	ON_EN_KILLFOCUS(IDC_EDIT_ENDY, OnKillfocusEditPosition)
	ON_EN_KILLFOCUS(IDC_EDIT_MIDX, OnKillfocusEditPosition)
	ON_EN_KILLFOCUS(IDC_EDIT_MIDY, OnKillfocusEditPosition)
	ON_BN_CLICKED(IDC_BUTTON_PAN, OnButtonPan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_DrawCad message handlers

BOOL CDlg_DrawCad::OnInitDialog() 
{
	CDialog::OnInitDialog();

	OnLanguage();
	InitButton(); 

	// TODO: Add extra initialization here
	OnInitGridCAD();
	bookImageList.Add( AfxGetApp()->LoadIcon(IDR_MAINFRAME));	// 0
	bookImageList.Add( AfxGetApp()->LoadIcon(IDI_ICON_GRAPH));	// 1 Graph
	bookImageList.Add( AfxGetApp()->LoadIcon(IDI_ICON_LINE));	// 2 Line
	bookImageList.Add( AfxGetApp()->LoadIcon(IDI_ICON_G2));		// 3 Arc 2
	bookImageList.Add( AfxGetApp()->LoadIcon(IDI_ICON_G3));		// 4 Arc 3
	m_TreeCtl.SetImageList(&bookImageList,TVSIL_NORMAL);
	m_TreeCtl.SetFont(&g_fontList);

	SetCurrGraphInfo();
	SetWindowPos(CWnd::GetOwner(),0,0,g_screen.x,g_screen.y,SWP_SHOWWINDOW);
	SetTimer(1,200, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_DrawCad::OnButton7() 
{

	CString   strFilename;
	dlg_save  dlgSave;
	
	dlgSave.strExtName = ".cxf";
	if (IDCANCEL == dlgSave.DoModal())  return;
	
	strFilename = g_strOriginalPathD+"glass\\"+g_strSavefile;
	g_strSavefile = "";
	m_GridCad.SaveSCRFile(strFilename);	

}

void CDlg_DrawCad::OnButton8() 
{
	
	CString   strFilename;
	dlg_save  dlgSave;
	
	dlgSave.strExtName = ".g";
	if (IDCANCEL == dlgSave.DoModal())  return;
	
	strFilename = g_strOriginalPathD+"gcode\\"+g_strSavefile;
	g_strSavefile = "";
	m_GridCad.SetHeadandTail("G90\nM25\nM23\n", "M24\nM26\n");	
	
	m_GridCad.SetUpandDown("M13\n", "M14\n");
	
	m_GridCad.SaveGCode(LPCTSTR(strFilename));	

}

void CDlg_DrawCad::OnInitGridCAD() 
{	
	m_ocxScrollX.SetScrollRange(m_nScrollMinPos,m_nScrollMaxPos);
	m_ocxScrollX.SetScrollPos(m_nScrollMinPos);
	m_GridCad.SetNScrollCurrWidthPos(m_nScrollMaxPos);
	
	m_ocxScrollY.SetScrollRange(m_nScrollMinPos,m_nScrollMaxPos);
	m_ocxScrollY.SetScrollPos(m_nScrollMaxPos);
	m_GridCad.SetNScrollCurrHeightPos(m_nScrollMinPos);

	m_GridCad.SetForeColor(RGB(0, 128, 0));
	m_GridCad.SetClrSignLine(RGB(180, 205, 205));
	m_GridCad.SetNSpace(5);				/* 画图网格大小 */
	m_GridCad.SetDGridSpace(30.0);		/* 网格距离 */
	m_GridCad.SetNPenWidthLine(2);
}

void CDlg_DrawCad::OnButton1() /* 新建 数据/图形 */
{
	//list排序,起点排序
    if (m_clrbAgain.GetState()==0 || m_clrbPickUp.GetState()==0)
		return;

	m_GridCad.DelAllData();
	m_GridCad.SetSetCompList(0);
}

void CDlg_DrawCad::OnButton3() /* 增加图形 */
{
	//list排序,起点排序
    if (m_clrbAgain.GetState()==0 || m_clrbPickUp.GetState()==0)
		return;	
	//防止不在最后一个list添加
	long nGraph = m_GridCad.GetGraphList();//头指针
	PGRAPHLIST pGraphList = (PGRAPHLIST)nGraph;	
	if(pGraphList != NULL)
	{
		/* 查找当前图形段 */
		for (PGRAPHLIST pTempGraphList=pGraphList; pTempGraphList; pTempGraphList=pTempGraphList->Next)
		{
			if(pTempGraphList->nSort == m_nCurrGraphIndex)
			{
				if (pTempGraphList->Next !=NULL)
				{
					return;
				}
				break;
			}
		}
	}
	m_GridCad.AddGraphList();
	OnInitList();
	m_nCurrGraphIndex  = m_GridCad.GetGraphCounts();
	m_GridCad.SetCurrentCurve(m_nCurrGraphIndex, m_nCurrSegmentIndex);
	SetCurrGraphInfo();
}

void CDlg_DrawCad::OnButton4() /* 删除图形 */
{
	//list排序,起点排序
    if (m_clrbAgain.GetState()==0 || m_clrbPickUp.GetState()==0)
		return;
	m_GridCad.DelCurrGraph();
}

void CDlg_DrawCad::OnButton5() /* 删除 */
{
	//list排序,起点排序
    if (m_clrbAgain.GetState()==0 || m_clrbPickUp.GetState()==0)
		return;

	m_GridCad.DelData();
}

void CDlg_DrawCad::OnButton6() /* 圆弧 */
{
	//list排序,起点排序
    if (m_clrbAgain.GetState()==0 || m_clrbPickUp.GetState()==0)
		return;

	m_GridCad.SetArc();
}

void CDlg_DrawCad::OnInitList() /* 显示数据 */
{
	long		nGraph;
	PGRAPHLIST  pGraphList, pTempGraph;
	CString		strGraph, strSect;
	
	HTREEITEM hItemRoot;
	PGRAPH pTempSect; //所画图形的各部分，如一条直线，一段圆弧
	
	nGraph = m_GridCad.GetGraphList();
	pGraphList = (PGRAPHLIST)nGraph;
	nGraph = m_GridCad.GetGraphCounts();
	
	if(pGraphList == NULL)
	{
		m_TreeCtl.DeleteAllItems();
		return;
	}

	m_TreeCtl.DeleteAllItems();
	for(pTempGraph = pGraphList; pTempGraph; pTempGraph = pTempGraph->Next)
	{
		if(g_iLanguage==0)
			strGraph.Format("图形 %d", pTempGraph->nSort);
		else
			strGraph.Format("Graph %d", pTempGraph->nSort);
			
		hItemRoot = m_TreeCtl.InsertItem(strGraph, 1, 1, TVI_ROOT);
		for(pTempSect = pTempGraph->pGraph; pTempSect; pTempSect = pTempSect->Next)
		{
			strGraph.Format("%d.%d", pTempGraph->nSort, pTempSect->nIndex);
			if(g_iLanguage==0)
			{
				if(pTempSect->chLine ==1 )
					m_TreeCtl.InsertItem("直线" + strGraph, 2, 2, hItemRoot);
				else if(pTempSect->chLine ==2 )
					m_TreeCtl.InsertItem("顺弧" + strGraph, 3, 3, hItemRoot);
				else if(pTempSect->chLine ==3 )
					m_TreeCtl.InsertItem("逆弧" + strGraph, 4, 4, hItemRoot);
				else
					return;
			}
			else
			{
				if(pTempSect->chLine ==1 )
					m_TreeCtl.InsertItem("Line " + strGraph, 2, 2, hItemRoot);
				else if(pTempSect->chLine ==2 )
					m_TreeCtl.InsertItem("CW ARC" + strGraph, 3, 3, hItemRoot);
				else if(pTempSect->chLine ==3 )
					m_TreeCtl.InsertItem("CCW ARC" + strGraph, 4, 4, hItemRoot);
				else
					return;
			}
		}
	}
}


BOOL CDlg_DrawCad::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->lParam==VK_ESCAPE||pMsg->wParam==VK_ESCAPE)
		return TRUE;
	
	if(pMsg->wParam == VK_DOWN || pMsg->wParam==VK_RETURN)
	{
		if(pMsg->message==WM_KEYUP)
		{
			/* 将数据写入CADDATA */
			SetCurrGraphData();
			ChangeFocusEdit();
		}
		return(TRUE);
	}
	if(pMsg->message == WM_MOUSEWHEEL)//鼠标滑轮控制图形放大缩小
	{
        CRect rect;
		GetDlgItem(IDC_GRIDCADCTRL)->GetWindowRect(&rect);
		if (rect.PtInRect(pMsg->pt))
		{
			SendMessage(WM_MOUSEWHEEL,pMsg->wParam,pMsg->lParam);
			return TRUE;
		}
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlg_DrawCad::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==1)
	{
		KillTimer(1);
		OnOpenFile();//G代码程序打开.
	}

	CDialog::OnTimer(nIDEvent);
}

void CDlg_DrawCad::OnGetCadPos() 
{
	long		nPointCad;
	PCADDATA	pCadGrid;
	CString		strInfo;

	nPointCad = m_GridCad.GetCurrPosition();
	pCadGrid = (PCADDATA)nPointCad;
	strInfo.Format("%.2f, %.2f", pCadGrid->PointPara.x, pCadGrid->PointPara.y);
	SetDlgItemText(IDC_STATIC_CURRPOS, strInfo);
}

BEGIN_EVENTSINK_MAP(CDlg_DrawCad, CDialog)
    //{{AFX_EVENTSINK_MAP(CDlg_DrawCad)
	ON_EVENT(CDlg_DrawCad, IDC_GRIDCADCTRL, 2 /* DrawGraph */, OnDrawGraphGridcadctrl1, VTS_NONE)
	ON_EVENT(CDlg_DrawCad, IDC_GRIDCADCTRL, 1 /* MovePosition */, OnMovePositionGridcadctrl1, VTS_NONE)
	ON_EVENT(CDlg_DrawCad, IDC_GRIDCADCTRL, 3 /* UpdateData */, OnUpdateDataGridcadctrl, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDlg_DrawCad::OnDrawGraphGridcadctrl1() 
{
	OnInitList();
	GetLastGraphData();
	GetCurrGraphInfo();
	SetTreeFocus();
}


void CDlg_DrawCad::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nSBCode)
	{
	case SB_LINEUP:
		{
			int iCurPos = pScrollBar->GetScrollPos(); 
			if (iCurPos>=m_nScrollMinPos)
			{
				if(iCurPos == m_nScrollMinPos)	
				{
					m_unUp++;
					iCurPos = iCurPos-m_unUp+1; 
				}
				else
				{
                     m_unUp = 0;
				}
				pScrollBar->SetScrollPos(iCurPos-1); 
				m_GridCad.SetNScrollCurrHeightPos(m_nScrollMaxPos-(iCurPos-1));
			}
		}
		break;
	case SB_LINEDOWN:
		{
			int iCurPos = pScrollBar->GetScrollPos(); 
			if (iCurPos<=m_nScrollMaxPos)
			{
				if(iCurPos == m_nScrollMaxPos)	
				{
					m_unDown++;
					iCurPos = iCurPos+m_unDown-1;
				}
				else
				{
					m_unDown = 0;
				}
				pScrollBar->SetScrollPos(iCurPos+1); 
				m_GridCad.SetNScrollCurrHeightPos(m_nScrollMaxPos-(iCurPos+1));
			}
		}
		break;
	case SB_PAGEUP:
		{
			int iCurPos = pScrollBar->GetScrollPos(); 			
			pScrollBar->SetScrollPos(iCurPos-1); 
			m_GridCad.SetNScrollCurrHeightPos(m_nScrollMaxPos-(iCurPos-1));
			m_unDown = 0;
			m_unUp = 0;
		}
		break;
	case SB_PAGEDOWN:
		{
			int iCurPos = pScrollBar->GetScrollPos(); 
			pScrollBar->SetScrollPos(iCurPos+1); 
			m_GridCad.SetNScrollCurrHeightPos(m_nScrollMaxPos-(iCurPos+1));
			m_unDown = 0;
			m_unUp = 0;
		}
		break;
	case SB_THUMBTRACK:
		{
			pScrollBar->SetScrollPos(nPos); 
			m_GridCad.SetNScrollCurrHeightPos(m_nScrollMaxPos-nPos);
			m_unDown = 0;
			m_unUp = 0;
		}
		break;
	default:
		break;
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CDlg_DrawCad::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nSBCode)
	{
	case SB_LINELEFT:
		{
			int iCurPos = pScrollBar->GetScrollPos(); 
			if (iCurPos>=m_nScrollMinPos)
			{
				if(iCurPos == m_nScrollMinPos)	
				{
					m_unLeft++;
                    iCurPos = iCurPos-m_unLeft+1;
				}
				else
				{
					m_unLeft = 0;
				}
				pScrollBar->SetScrollPos(iCurPos-1);
				m_GridCad.SetNScrollCurrWidthPos(m_nScrollMaxPos-(iCurPos-1));
			}
		}
		break;
	case SB_LINERIGHT:
		{
			int iCurPos = pScrollBar->GetScrollPos(); 
			if (iCurPos<=m_nScrollMaxPos)
			{
				if(iCurPos == m_nScrollMaxPos)	
				{
                    m_unRight++;
                    iCurPos = iCurPos+m_unRight-1;
				}
				else
				{
					m_unRight = 0;
				}
				pScrollBar->SetScrollPos(iCurPos+1); 
				m_GridCad.SetNScrollCurrWidthPos(m_nScrollMaxPos-(iCurPos+1));
			}
			else 
			{
				m_GridCad.SetNScrollCurrWidthPos(m_nScrollMaxPos-(iCurPos+1));
			}
		}
		break;
	case SB_PAGELEFT:
		{
			int iCurPos = pScrollBar->GetScrollPos(); 			
			pScrollBar->SetScrollPos(iCurPos-1); 
			m_GridCad.SetNScrollCurrWidthPos(m_nScrollMaxPos-(iCurPos-1));
			m_unLeft = 0;
			m_unRight = 0;
		}
		break;
	case SB_PAGERIGHT:
		{
			int iCurPos = pScrollBar->GetScrollPos(); 
			pScrollBar->SetScrollPos(iCurPos+1); 
			m_GridCad.SetNScrollCurrWidthPos(m_nScrollMaxPos-(iCurPos+1));
			m_unLeft = 0;
			m_unRight = 0;
		}
		break;
	case SB_THUMBTRACK:
		{
			pScrollBar->SetScrollPos(nPos); 
			m_GridCad.SetNScrollCurrWidthPos(m_nScrollMaxPos-nPos);
			m_unLeft = 0;
			m_unRight = 0;
		}
		break;
	default:
		break;
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlg_DrawCad::OnMovePositionGridcadctrl1() 
{
	OnGetCadPos();
}
/************************************************************************/
/* 根据选择的节点选中状态，设置相关节点的选中状态                   */
/************************************************************************/
void CDlg_DrawCad::SetItemCheckState(HTREEITEM item, BOOL bCheck)
{
	SetChildCheck(item, bCheck);
	SetParentCheck(item, bCheck);
}
/************************************************************************/
/* 设置子节点的选中状态                                              */
/************************************************************************/
void CDlg_DrawCad::SetChildCheck(HTREEITEM item, BOOL bCheck)
{
	HTREEITEM child = m_TreeCtl.GetChildItem(item);
	while(child)
	{
		m_TreeCtl.SetCheck(child, bCheck);		
		child = m_TreeCtl.GetNextItem(child, TVGN_NEXT);
	}
}
/************************************************************************/
/* 设置父节点选中状态                                                 */
/************************************************************************/
void CDlg_DrawCad::SetParentCheck(HTREEITEM item, BOOL bCheck)
{
	HTREEITEM parent = m_TreeCtl.GetParentItem(item);
	if(parent == NULL)
		return;
	if(bCheck)
		m_TreeCtl.SetCheck(parent, bCheck);
	else
	{
		HTREEITEM bro = m_TreeCtl.GetNextItem(item, TVGN_NEXT);
		BOOL bFlag = false;
		while(bro)
		{
			if(m_TreeCtl.GetCheck(bro))
			{
				bFlag = true;
				break;
			}
			bro = m_TreeCtl.GetNextItem(bro, TVGN_NEXT);
		}
		if(!bFlag)
		{
			bro = m_TreeCtl.GetNextItem(item, TVGN_PREVIOUS);
			while(bro)
			{
				if(m_TreeCtl.GetCheck(bro))
				{
					bFlag = true;
					break;
				}
				bro = m_TreeCtl.GetNextItem(bro, TVGN_PREVIOUS);
			}
		}
		if(!bFlag)
			m_TreeCtl.SetCheck(parent, false);
	}
}

void CDlg_DrawCad::OnClickTreectl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_bClickTree = TRUE;
	*pResult = 0;

	CPoint point;
	UINT uFlag;
	GetCursorPos(&point);
	m_TreeCtl.ScreenToClient(&point);
	HTREEITEM item = m_TreeCtl.HitTest(point, &uFlag);
	if((item) && (TVHT_ONITEMSTATEICON & uFlag))   
	{   
		m_bClickTree = FALSE;
		BOOL bCheck = m_TreeCtl.GetCheck(item);
		SetItemCheckState(item, !bCheck);
	}   

}

void CDlg_DrawCad::OnSelchangedTreectl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	HTREEITEM hItem;
	CString	strGraph, strSect;	
	hItem = m_TreeCtl.GetSelectedItem();
	if(hItem)
	{
		int nCount;
		strGraph = m_TreeCtl.GetItemText(hItem);
		nCount = strGraph.GetLength();
		
		if(strGraph.Left(4) == "图形")
		{
			if (m_bClickTree) 
			{
				strSect = strGraph.Right(nCount - 4);
				m_GridCad.SetNCurrGraph(atoi(strSect));
				m_bClickTree = FALSE;
				m_nCurrGraphIndex = atoi(strSect);//获得几号图形的图号
			}
		}
		else	//不管直线，顺弧，逆弧都只提取其在图形中的标号
		{
			strSect = strGraph.Right(nCount - 4);
			int i = strSect.Find(".");
			
			m_nCurrGraphIndex = atoi(strSect.Left(i));		//获得几号图形的图号
			m_nCurrSegmentIndex = atoi(strSect.Mid(i + 1));	//获得几号图形的图段
			m_GridCad.SetCurrentCurve(m_nCurrGraphIndex, m_nCurrSegmentIndex);
		}
	}	
	GetCurrGraphData();
	GetCurrGraphInfo();
	*pResult = 0;
}

void CDlg_DrawCad::OnOpenFile()//程序打开.
{
    if(strstr(g_strGfile,".cxf")||strstr(g_strGfile,".CXF"))/* 模具 */
	{
		m_GridCad.OpenSCRFile(g_strGfile);
	}
	else if(strstr(g_strGfile,".g")||strstr(g_strGfile,".G"))/* 模具 */
	{
		m_GridCad.OpenSCRFile(g_strGfile);
	}
	else if (strstr(g_strGfile,".dxf")||strstr(g_strGfile,".DXF"))
	{
		CBenderDlg* dlg =(CBenderDlg *)GetParent();
		if (dlg != NULL)
		{
			CDxf2G  DxftoGCad;
			DxftoGCad.SetSortOrder(g_stu_pAxisD->bSpare, g_stu_pAxisD->bSpareA, (int)g_stu_pAxisE->sSpare);
			int nDxf = DxftoGCad.SetInputFile((char*)((const char*)g_strGfile));
			if(nDxf>0)
			{
				if(!g_iLanguage)
					AfxMessageBox("版本号不对，请使用R12版的DXF文件！");
				else
					AfxMessageBox("File Version Error,Plase Change To R12 Dxf File!");
				return;
			}
			DxftoGCad.SetDownOperation("M13\n");
			DxftoGCad.SetUpOperation("M14\n");	
			DxftoGCad.SetHeadTailHomeOperation("M25\nM23","M24\nM26","G90G00X0Y0Z0");
			g_strGfile = g_strOriginalPathC + "dxf.g";
			DxftoGCad.SetOutputFile((char*)((const char*)g_strGfile));
			m_GridCad.OpenSCRFile(g_strGfile);
		}
	}
}

void CDlg_DrawCad::GetCurrGraphData()  /* 获取当前图形的起点、终点数据 */
{
	long		nGraph;
	PGRAPHLIST  pGraphList, pTempGraphList;
	PGRAPH		pTempGraph, pGraph = NULL;
	
	nGraph = m_GridCad.GetGraphList();
	pGraphList = (PGRAPHLIST)nGraph;
	
	if(pGraphList == NULL)
		return;
	/* 查找当前图形段 */
	for (pTempGraphList=pGraphList; pTempGraphList; pTempGraphList=pTempGraphList->Next)
	{
		if(pTempGraphList->nSort == m_nCurrGraphIndex)
		{
			for (pTempGraph=pTempGraphList->pGraph; pTempGraph; pTempGraph=pTempGraph->Next)
			{
				if (pTempGraph->nIndex == m_nCurrSegmentIndex)
				{ 
					pGraph = pTempGraph;
					break;
				}
			}
			break;
		}
	}
	if(pGraph)
	{
		m_dBeginX = pGraph->pPosBegin->PointPara.x;
		m_dBeginY = pGraph->pPosBegin->PointPara.y;
		m_dEndX = pGraph->pPosEnd->PointPara.x;
		m_dEndY = pGraph->pPosEnd->PointPara.y;
		if(pGraph->chLine > 1)
		{
			m_dMidX = pGraph->pPosMid->PointPara.x;
			m_dMidY = pGraph->pPosMid->PointPara.y;
			m_edtMidY.EnableWindow(TRUE);
			m_edtMidX.EnableWindow(TRUE);
			m_stcMid.EnableWindow(TRUE);
		}
		else
		{
			m_dMidX = 0.0;
			m_dMidY = 0.0;
			m_edtMidY.EnableWindow(FALSE);
			m_edtMidX.EnableWindow(FALSE);
			m_stcMid.EnableWindow(FALSE);
		}
		UpdateData(FALSE);
	}
}

void CDlg_DrawCad::SetCurrGraphData()  /* 设置当前图形的起点、终点数据 */
{
	long		nGraph;
	PGRAPHLIST  pGraphList, pTempGraphList;
	PGRAPH		pTempGraph, pGraph = NULL;
	
	nGraph = m_GridCad.GetGraphList();
	pGraphList = (PGRAPHLIST)nGraph;
	
	if(pGraphList == NULL)
		return;
	/* 查找当前图形段 */
	for (pTempGraphList=pGraphList; pTempGraphList; pTempGraphList=pTempGraphList->Next)
	{
		if(pTempGraphList->nSort == m_nCurrGraphIndex)
		{
			for (pTempGraph=pTempGraphList->pGraph; pTempGraph; pTempGraph=pTempGraph->Next)
			{
				if (pTempGraph->nIndex == m_nCurrSegmentIndex)
				{ 
					pGraph = pTempGraph;
					break;
				}
			}
			break;
		}
	}
	if(pGraph)
	{
		UpdateData(TRUE);
		pGraph->pPosBegin->PointPara.x = m_dBeginX;
		pGraph->pPosBegin->PointPara.y = m_dBeginY;
		pGraph->pPosEnd->PointPara.x = m_dEndX;
		pGraph->pPosEnd->PointPara.y = m_dEndY;
		if(pGraph->chLine > 1)
		{
			pGraph->pPosMid->PointPara.x = m_dMidX;
			pGraph->pPosMid->PointPara.y = m_dMidY;
			m_edtMidY.EnableWindow(TRUE);
			m_edtMidX.EnableWindow(TRUE);
			m_stcMid.EnableWindow(TRUE);
		}
		else
		{
			m_edtMidY.EnableWindow(FALSE);
			m_edtMidX.EnableWindow(FALSE);
			m_stcMid.EnableWindow(FALSE);
		}
		m_GridCad.ReDraw();
	}
}

void CDlg_DrawCad::GetLastGraphData()  /* 获取最后图形的起点、终点数据 */
{
	long		nGraph;
	PGRAPHLIST  pGraphList, pTempGraphList;
	PGRAPH		pTempGraph, pGraph = NULL;
	
	nGraph = m_GridCad.GetGraphList();
	pGraphList = (PGRAPHLIST)nGraph;
	
	if(pGraphList == NULL)
		return;
	/* 查找当前图形段 */
	for (pTempGraphList=pGraphList; pTempGraphList; pTempGraphList=pTempGraphList->Next)
	{
		if(pTempGraphList->Next == NULL)
		{
			m_nCurrGraphIndex = pTempGraphList->nSort;
			for (pTempGraph=pTempGraphList->pGraph; pTempGraph; pTempGraph=pTempGraph->Next)
			{
				if (pTempGraph->Next == NULL)
				{ 
					m_nCurrSegmentIndex = pTempGraph->nIndex;
					pGraph = pTempGraph;
					break;
				}
			}
			break;
		}
	}
	if(pGraph)
	{
		m_dBeginX = pGraph->pPosBegin->PointPara.x;
		m_dBeginY = pGraph->pPosBegin->PointPara.y;
		m_dEndX = pGraph->pPosEnd->PointPara.x;
		m_dEndY = pGraph->pPosEnd->PointPara.y;
		if(pGraph->chLine > 1)
		{
			m_dMidX = pGraph->pPosMid->PointPara.x;
			m_dMidY = pGraph->pPosMid->PointPara.y;
			m_edtMidY.EnableWindow(TRUE);
			m_edtMidX.EnableWindow(TRUE);
			m_stcMid.EnableWindow(TRUE);
		}
		else
		{
			m_dMidX = 0.0;
			m_dMidY = 0.0;
			m_edtMidY.EnableWindow(FALSE);
			m_edtMidX.EnableWindow(FALSE);
			m_stcMid.EnableWindow(FALSE);
		}
		UpdateData(FALSE);
	}
}

void CDlg_DrawCad::GetCurrGraphInfo()  /* 获取当前图形的相关信息 */
{
	long		nGraph;
	PGRAPHLIST  pGraphList, pTempGraphList;
	PGRAPHLIST  pCurrList = NULL;
	
	nGraph = m_GridCad.GetGraphList();
	pGraphList = (PGRAPHLIST)nGraph;
	
	if(pGraphList == NULL)
	{
		return;
	}
	/* 查找当前图形段 */
	for (pTempGraphList=pGraphList; pTempGraphList; pTempGraphList=pTempGraphList->Next)
	{
		if(pTempGraphList->nSort == m_nCurrGraphIndex)
		{
			pCurrList = pTempGraphList;
			break;
		}
	}
	if(pCurrList)
	{
		
		if(pCurrList->nSplineStyle > 0)	/* 变量为设置窗口中样条的样式 */
		{
			m_GridCad.SetSpline(pCurrList->nSort, 1);		/* 网格距离 */
			m_GridCad.ReDraw();
		}
		else
		{
			m_GridCad.SetSpline(pCurrList->nSort, 0);		/* 网格距离 */
			m_GridCad.ReDraw();
		}
		UpdateData(FALSE);
	}
}

PGRAPHLIST CDlg_DrawCad::SetCurrGraphInfo()  /* 设置当前图形的相关信息 */
{
	long		nGraph;
	PGRAPHLIST  pTempGraphList = NULL;
	PGRAPHLIST  pGraphList = NULL;
	PGRAPHLIST  pCurrList = NULL;
	
	nGraph = m_GridCad.GetGraphList();
	pGraphList = (PGRAPHLIST)nGraph;
	
	if(pGraphList == NULL)
	{
		return pGraphList;
	}
	/* 查找当前图形段 */
	for (pTempGraphList=pGraphList; pTempGraphList; pTempGraphList=pTempGraphList->Next)
	{
		if(pTempGraphList->nSort == m_nCurrGraphIndex)
		{
			pCurrList = pTempGraphList;
			break;
		}
	}
	if(pCurrList)
	{
		UpdateData(TRUE);		
		pCurrList->nSplineStyle = 0;
		m_GridCad.SetSpline(pCurrList->nSort, 0);		/* 网格距离 */
		m_GridCad.ReDraw();
	}
	return pGraphList;
}

void CDlg_DrawCad::OnSetfocusEditBeginx() 
{
	// TODO: Add your control notification handler code here
	((CEdit *)GetDlgItem(IDC_EDIT_BEGINX))->SetSel(0,-1);
}

void CDlg_DrawCad::OnSetfocusEditBeginy() 
{
	// TODO: Add your control notification handler code here
	((CEdit *)GetDlgItem(IDC_EDIT_BEGINY))->SetSel(0,-1);
}

void CDlg_DrawCad::OnSetfocusEditMidx() 
{
	// TODO: Add your control notification handler code here
	((CEdit *)GetDlgItem(IDC_EDIT_MIDX))->SetSel(0,-1);
}

void CDlg_DrawCad::OnSetfocusEditMidy() 
{
	// TODO: Add your control notification handler code here
	((CEdit *)GetDlgItem(IDC_EDIT_MIDY))->SetSel(0,-1);
}

void CDlg_DrawCad::OnSetfocusEditEndx() 
{
	// TODO: Add your control notification handler code here
	((CEdit *)GetDlgItem(IDC_EDIT_ENDX))->SetSel(0,-1);
}

void CDlg_DrawCad::OnSetfocusEditEndy() 
{
	// TODO: Add your control notification handler code here
	((CEdit *)GetDlgItem(IDC_EDIT_ENDY))->SetSel(0,-1);
}

LRESULT CDlg_DrawCad::OnEditDouble(WPARAM wParam, LPARAM lParam) 
{
	CString				strTmp;
	CDlg_KeyNumber		KeyNum;
	if(lParam==1)
	{
		((CEdit *)GetDlgItem(wParam))->SetSel(0,-1);
		return 0;
	}

	CWnd::GetDlgItemText(wParam,strTmp);
	KeyNum.m_strNew = KeyNum.m_strOld = strTmp;

	switch(wParam) 
	{
	case IDC_EDIT_BEGINX:				
		GetDlgItemText(IDC_STATIC_BEGIN, KeyNum.m_strTitle);					
		break;
	case IDC_EDIT_BEGINY:				
		GetDlgItemText(IDC_STATIC_BEGIN, KeyNum.m_strTitle);					
		break;
	case IDC_EDIT_MIDX:				
		GetDlgItemText(IDC_STATIC_MID, KeyNum.m_strTitle);					
		break;
	case IDC_EDIT_MIDY:				
		GetDlgItemText(IDC_STATIC_MID, KeyNum.m_strTitle);					
		break;
	case IDC_EDIT_ENDX:				
		GetDlgItemText(IDC_STATIC_END, KeyNum.m_strTitle);					
		break;
	case IDC_EDIT_ENDY:				
		GetDlgItemText(IDC_STATIC_END, KeyNum.m_strTitle);					
		break;
	default:
		break;
	}
	if(g_stu_pAxisC->bSpareA && KeyNum.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	
	return 0;
}

/* 输入数据后，切换到下一个EDIT框 */
void CDlg_DrawCad::ChangeFocusEdit() 
{
	keybd_event(VK_TAB, 0, 0, 0);                 //换行
	keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);		
}

void CDlg_DrawCad::OnKillfocusEditPosition() 
{
	SetCurrGraphData();
}

void CDlg_DrawCad::OnButtonCs10() 
{
	m_GridCad.DelAllData();
	CDialog::OnOK();
}

void CDlg_DrawCad::OnLanguage()
{
	for(int i=0;i<AR_DRAWCAD;i++)
	{
		if(strstr(g_arr_drawcad[i][g_iLanguage], "NULL"))
			SetDlgItemText(atoi(g_arr_drawcad[i][2]), "");
		else
			SetDlgItemText(atoi(g_arr_drawcad[i][2]), g_arr_drawcad[i][g_iLanguage]);
	}
	if (g_iLanguage == 1)
	{
        SetDlgItemText(IDC_BUTTON_UP, "Up");
        SetDlgItemText(IDC_BUTTON_DOWN, "Down");
		SetDlgItemText(IDC_BUTTON_FORWORD,"Rev");
		SetDlgItemText(IDC_BUTTON_PICKUP,"PickOn");
		SetDlgItemText(IDC_BUTTON_SORT,"SORT");
		SetDlgItemText(IDC_BUTTON_SPACE,"SPACE");
		SetDlgItemText(IDC_BUTTON_GRID,"Zoom");//放大
		SetDlgItemText(IDC_BUTTON_GRID2,"Narrow");//缩小
		SetDlgItemText(IDC_STATIC_STARTPOS,"Start Point");
		SetDlgItemText(IDC_STATIC_REVERSE,"Reverse");
		SetDlgItemText(IDC_STATIC_SORT,"Sort Cut");
		SetDlgItemText(IDC_BUTTON_AGAIN,"Again");
	}
}

void CDlg_DrawCad::OnButtonSpace() 
{
	// TODO: Add your control notification handler code here
	CDlg_KeyNumber	KeyNum;
	double			dTemp;
	
	if(KeyNum.DoModal()==IDOK)
	{
		dTemp = atof(KeyNum.m_strNew);
		if(dTemp>0.1)
		{
			m_GridCad.SetDGridSpace(dTemp);	/* 网格距离 */
		}
	}

}
//显示放大
void CDlg_DrawCad::OnButtonGrid() 
{
	m_GridCad.SetNSpace(m_GridCad.GetNSpace()+1);	/* 网格距离 */
}

void CDlg_DrawCad::OnButtonUp() 
{  
	//list排序,起点排序
    if (m_clrbAgain.GetState()==0 || m_clrbPickUp.GetState()==0)
		return;

	m_GridCad.ListForward();
}

void CDlg_DrawCad::OnButtonDown() 
{
	//list排序,起点排序
    if (m_clrbAgain.GetState()==0 || m_clrbPickUp.GetState()==0)
		return;

	m_GridCad.ListBackWard();
}

//反向
void CDlg_DrawCad::OnButtonForword() 
{
	//list排序,起点排序
    if (m_clrbAgain.GetState()==0 || m_clrbPickUp.GetState()==0)
		return;

	m_GridCad.ReverseGraph();
}

void CDlg_DrawCad::OnButtonPickup() 
{
	CString strName;
	GetDlgItemText(IDC_BUTTON_PICKUP,strName);
	if (strName == "拾取关" || strName == "PickOff")
	{
		m_clrbPickUp.SetState(0);
		m_GridCad.PickUpBeginPos(1);
		if (g_iLanguage == 1)
		{
			SetDlgItemText(IDC_BUTTON_PICKUP,"PickOn");

		}
		else
		{
			SetDlgItemText(IDC_BUTTON_PICKUP,"拾取开");
		}
		m_clrbAgain.SetState(1);
		m_GridCad.SortListStart(0);
		if (g_iLanguage == 1)
		{
			SetDlgItemText(IDC_BUTTON_AGAIN,"PickOff");
			
		}
		else
		{
			SetDlgItemText(IDC_BUTTON_AGAIN,"拾取关");
		}

	}
	else
	{
		m_clrbPickUp.SetState(1);
		m_GridCad.PickUpBeginPos(0);
		if (g_iLanguage == 1)
		{
			SetDlgItemText(IDC_BUTTON_PICKUP,"PickOff");
			
		}
		else
		{
			SetDlgItemText(IDC_BUTTON_PICKUP,"拾取关");
		}
	}
}

void CDlg_DrawCad::OnButtonSort() 
{
	// TODO: Add your control notification handler code here
	CString strName;
	GetDlgItemText(IDC_BUTTON_PICKUP,strName);
	if (strName == "拾取开" ||strName == "PICK ON")
	{
		m_GridCad.ChangeStart();		
	}
}

void CDlg_DrawCad::InitButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_FILESTY1);
	//新建	
	m_pButton[0].SetFont(&g_fontEdit);
	m_pButton[0].SetBitMapID(IDB_BITMAP_NEW1,IDB_BITMAP_NEW2);	
	m_pButton[0].Create(g_arr_drawcad[1][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(5, 710), c, this, IDC_BUTTON_CS1); 
	//增加图形
	m_pButton[1].HaveBitmap(1);
	m_pButton[1].SetFont(&g_fontStatic);
	m_pButton[1].SetBitMapID(IDB_BITMAP1,IDB_BITMAP2);	
	m_pButton[1].Create(g_arr_drawcad[2][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(135, 710), c, this, IDC_BUTTON_CS3); 
	//删除图形
	m_pButton[2].HaveBitmap(1);
	m_pButton[2].SetFont(&g_fontStatic);
	m_pButton[2].SetBitMapID(IDB_BITMAP1,IDB_BITMAP2);	
	m_pButton[2].Create(g_arr_drawcad[3][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(260, 710), c, this, IDC_BUTTON_CS4); 
	//删除线段	
	m_pButton[3].HaveBitmap(1);
	m_pButton[3].SetFont(&g_fontStatic);
	m_pButton[3].SetBitMapID(IDB_BITMAP1,IDB_BITMAP2);	
	m_pButton[3].Create(g_arr_drawcad[7][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(385, 710), c, this, IDC_BUTTON_CS5); 
	
	//圆弧
	m_pButton[4].SetFont(&g_fontEdit);
	m_pButton[4].SetBitMapID(IDB_BITMAP_ARC1,IDB_BITMAP_ARC2);	
	m_pButton[4].Create(g_arr_drawcad[4][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(510, 710), c, this, IDC_BUTTON_CS6); 
	
	//保存CXf
	m_pButton[5].SetFont(&g_fontStatic);
	m_pButton[5].SetBitMapID(IDB_BITMAP_SAVECXF1,IDB_BITMAP_SAVECXF2);	
	m_pButton[5].Create(g_arr_drawcad[13][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(640, 710), c, this, IDC_BUTTON_CS7); 
	//保存G
	m_pButton[6].SetFont(&g_fontStatic);
	m_pButton[6].SetBitMapID(IDB_BITMAP_SAVEG1,IDB_BITMAP_SAVEG2);	
	m_pButton[6].Create(g_arr_drawcad[5][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(765, 710), c, this, IDC_BUTTON_CS8); 
	
	//返回	
	m_pButton[7].SetFont(&g_fontEdit);
	m_pButton[7].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[7].Create(g_arr_drawcad[6][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(900, 710), c, this, IDC_BUTTON_CS10); 
    
	DeleteObject(c);
}

//显示缩小
void CDlg_DrawCad::OnButtonGrid2() 
{
	// TODO: Add your control notification handler code here
    m_GridCad.SetNSpace(m_GridCad.GetNSpace()-1);	/* 网格距离 */	
}

//根据当前的行数,在上移下移以后调用
void CDlg_DrawCad::SetTreeFocus()
{
	m_nCurrGraphIndex = m_GridCad.GetNCurrGraph();
	int nIndex = 0;
    HTREEITEM hmyItem=m_TreeCtl.GetRootItem();//得到根节点
	if (hmyItem)
	{   
		HTREEITEM hNextItem = hmyItem;		
		while(hNextItem != NULL)
		{
			nIndex++;
			if (m_nCurrGraphIndex == nIndex)
			{
				m_TreeCtl.SetFocus();
				m_TreeCtl.SelectItem(hNextItem);
				break;
			}
            hNextItem = m_TreeCtl.GetNextItem(hNextItem,TVGN_NEXT);			
		}
	}
}

void CDlg_DrawCad::OnButtonAgain() 
{
	CString strName;
	GetDlgItemText(IDC_BUTTON_AGAIN,strName);
	if (strName == "拾取关" || strName == "PickOff")
	{
		m_clrbAgain.SetState(0);
		m_GridCad.SortListStart(1);
		if (g_iLanguage == 1)
		{
			SetDlgItemText(IDC_BUTTON_AGAIN,"PickOn");
			
		}
		else
		{
			SetDlgItemText(IDC_BUTTON_AGAIN,"拾取开");
		}
		m_clrbPickUp.SetState(1);
		m_GridCad.PickUpBeginPos(0);
		if (g_iLanguage == 1)
		{
			SetDlgItemText(IDC_BUTTON_PICKUP,"PickOff");			
		}
		else
		{
			SetDlgItemText(IDC_BUTTON_PICKUP,"拾取关");
		}
	}
	else
	{
		m_clrbAgain.SetState(1);
		m_GridCad.SortListStart(0);
		if (g_iLanguage == 1)
		{
			SetDlgItemText(IDC_BUTTON_AGAIN,"PickOff");
			
		}
		else
		{
			SetDlgItemText(IDC_BUTTON_AGAIN,"拾取关");
		}
	}	
}

BOOL CDlg_DrawCad::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	if(zDelta>0)	OnButtonGrid();
	else			OnButtonGrid2();

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CDlg_DrawCad::OnButtonZoom() 
{
	HTREEITEM hmyItem=m_TreeCtl.GetRootItem();//得到根节点
	if (hmyItem)
	{   
		HTREEITEM hNextItem = hmyItem;
		vector<int> l_selectArray;//选择		  
		int l_ListIndex = 1;  // 将被选中的图元check
		while(hNextItem != NULL)
		{
			if(NULL != m_TreeCtl.GetCheck(hNextItem))
			{        		
				l_selectArray.push_back(l_ListIndex);  // 将图元放入选择集中
			}
			hNextItem = m_TreeCtl.GetNextItem(hNextItem,TVGN_NEXT);	
			l_ListIndex++;			
		}
        if (!l_selectArray.empty())
        {
			
			CSetXY dlg;
			if (IDOK == dlg.DoModal())
			{
				int nCount = l_selectArray.size();
				short FAR  *pCheck = new short[nCount];
				for (int i=0; i<nCount; i++)
				{
					pCheck[i] = (short)l_selectArray[i];
				} 
				m_GridCad.SetCheckList(pCheck,nCount);				
				m_GridCad.ZoomInOut(dlg.m_dX,dlg.m_dY);
				delete[] pCheck; 
				pCheck = NULL;
				m_GridCad.SetCheckList(pCheck,0);		
			}
			l_selectArray.clear();
        } 
	}		
}

void CDlg_DrawCad::OnButtonPan() 
{
	// TODO: Add your control notification handler code here
	HTREEITEM hmyItem=m_TreeCtl.GetRootItem();//得到根节点
	if (hmyItem)
	{   
		HTREEITEM hNextItem = hmyItem;
		vector<int> l_selectArray;//选择		  
	    int l_ListIndex = 1;  // 将被选中的图元check
		while(hNextItem != NULL)
		{
		    if(NULL != m_TreeCtl.GetCheck(hNextItem))
			{        		
				l_selectArray.push_back(l_ListIndex);  // 将图元放入选择集中
			}
			hNextItem = m_TreeCtl.GetNextItem(hNextItem,TVGN_NEXT);	
			l_ListIndex++;			
		}
        if (!l_selectArray.empty())
        {

			CSetXY dlg;
			if (IDOK == dlg.DoModal())
			{
				int nCount = l_selectArray.size();
				short FAR  *pCheck = new short[nCount];
				for (int i=0; i<nCount; i++)
				{
					pCheck[i] = (short)l_selectArray[i];
				} 
				m_GridCad.SetCheckList(pCheck,nCount);				
				m_GridCad.MovePostion(dlg.m_dX,dlg.m_dY);
				delete[] pCheck; 
				pCheck = NULL;
				m_GridCad.SetCheckList(pCheck,0);		
			}
			l_selectArray.clear();
        } 
	}	
}

void CDlg_DrawCad::OnUpdateDataGridcadctrl() 
{
	GetCurrGraphData();
	SetTreeFocus();
}
