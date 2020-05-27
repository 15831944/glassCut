// dlg_path2.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "dlg_path2.h"
#include "Dlg_KeyChar.h"
#include "dlg_manager.h"
#include "Dlg_DrawCad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dlg_path2 dialog


dlg_path2::dlg_path2(CWnd* pParent /*=NULL*/)
	: CDialog(dlg_path2::IDD, pParent)
{
	//{{AFX_DATA_INIT(dlg_path2)
	m_file = _T("");
	//}}AFX_DATA_INIT
}


void dlg_path2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dlg_path2)
	DDX_Control(pDX, IDC_LIST_GCODE, m_ListGcode);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_STATIC_FILE, m_file);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dlg_path2, CDialog)
	//{{AFX_MSG_MAP(dlg_path2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dlg_path2 message handlers

BOOL dlg_path2::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
    OnLanguage();
	InitButton();
    OnReSetCtl();
	m_strFilePath = "";
	m_img.Create(IDB_BITMAP_FILETYPE,16,1,RGB(100,0,0));
	m_list.SetImageList(&m_img, LVSIL_SMALL);
	OnButton3(); 
//===============================================================
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void dlg_path2::OnButton10() 
{
	g_iIsDxf = 0;
	CDialog::OnCancel();
}

void dlg_path2::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int i,n,iState;
    CFileFind cFinder;
	long      lLengh=0;
	CString   strLen;
    BOOL      bWorking;
 	int nItemSelected=m_list.GetSelectedCount();	//如果没有选择，不用处理
	if(nItemSelected<1)		
		return;
	n = m_list.GetItemCount();	//列表单项目的个数
	for(i=n-1;i>=0;i--)
	{
		iState=m_list.GetItemState(i,LVIS_SELECTED);
		if(iState!=0)
            m_strFilename = m_list.GetItemText(i,0);
	}
	if(m_strFilename == m_strHeadShow || m_strFilename=="")//如果是返回上一级目录
		 return;
	if(m_iStyle == 0)					
		bWorking = cFinder.FindFile(_T(g_strOriginalPathD+"glass\\"+m_strFilename));
	else if(m_iStyle == 1)			
		bWorking = cFinder.FindFile(_T(g_strOriginalPathD+"dxf\\"+m_strFilePath+m_strFilename));
	else if(m_iStyle == 2)			
		bWorking = cFinder.FindFile(_T(g_strOriginalPathD+"gcode\\"+m_strFilePath+m_strFilename));
    while (bWorking)
    {
        bWorking = cFinder.FindNextFile();
        lLengh = cFinder.GetLength();
		strLen.Format("%d",lLengh);
    }
	SetDlgItemText(IDC_STATIC_FILE,m_strFilename);
	SetDlgItemText(IDC_STATIC_LENGH,strLen+" B");
	if (lLengh > 0)
	{
		if(m_iStyle == 2)
		{
			m_strFileShow = g_strOriginalPathD+"gcode\\"+m_strFilePath+m_strFilename;
		}
		else if(m_iStyle == 1 || m_iStyle == 0)
		{
			if(m_iStyle == 1)
				m_strFileShow = g_strOriginalPathD+"dxf\\"+m_strFilePath+m_strFilename;
			else
				m_strFileShow = g_strOriginalPathD+"glass\\"+m_strFilename;

			CDxf2G  DxftoGCad;
			DxftoGCad.SetSortOrder(g_stu_pAxisD->bSpare, g_stu_pAxisD->bSpareA, (int)g_stu_pAxisE->sSpare);
			int nDxf = DxftoGCad.SetInputFile((char*)((const char*)m_strFileShow));
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
			m_strFileShow = g_strOriginalPathC + "Tempdxf.g";
			DxftoGCad.SetOutputFile((char*)((const char*)m_strFileShow));
		}		
		ProcessGcodeInf();		
	}
	*pResult = 0;
}

BOOL dlg_path2::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->lParam==VK_TAB||pMsg->wParam==VK_TAB)
		return TRUE;
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void dlg_path2::OnButton7() 
{
	if(m_strFilename == m_strHeadShow)//如果是返回上一级目录
	{
		return;
	}
	if(m_strFilename=="")
	{
		OnShowMessageBox(27, g_iLanguage, FALSE);
		return;
	}
	if (m_iStyle == 2)
	{
		if((!strstr(m_strFilename,".g")))
			return;
	}
	g_strGfile = g_strDxffile = ""; 
	if(m_iStyle == 0)					g_strGfile = g_strOriginalPathD+"glass\\"+m_strFilename;
	else if(m_iStyle == 1)			g_strGfile = g_strOriginalPathD+"dxf\\"+m_strFilePath+m_strFilename;
	else if(m_iStyle == 2)			g_strGfile = g_strOriginalPathD+"gcode\\"+m_strFilePath+m_strFilename;	
    g_strShowName = m_strFilename;
	g_iIsDxf = 0;
	CDialog::OnOK();
}

void dlg_path2::OnLanguage()
{
	int   i;
	int		nIndex;
	nIndex = g_iLanguage + 1;
	for(i=0;i<AR_PATH2;i++)
	{
		if (g_arr_strPath2[i][nIndex] == "NULL")
		{
			g_arr_strPath2[i][nIndex]="";
		}
		CWnd::SetDlgItemText(atoi(g_arr_strPath2[i][0]),g_arr_strPath2[i][nIndex]);
	}
	
	if (g_iLanguage == 0)
	{
		m_strHeadShow = "----返回上一级目录----";
	}
	else
	{
		m_strHeadShow = "----Return Up----";
		CWnd::SetDlgItemText(IDC_STATIC_FILEVIEW,"File View：");
	}
}

void dlg_path2::OnReSetCtl()
{
	GetDlgItem(IDC_LIST1)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_FILEVIEW)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC1)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_LIST_GCODE)->SetFont(&g_fontStatic);
	SetWindowPos(CWnd::GetOwner(),0,0,g_screen.x,g_screen.y,SWP_SHOWWINDOW);
}

void dlg_path2::OnButton1() 
{
	BOOL bWorking;
    CFileFind cFinder;
	int i = 0;

	m_list.DeleteAllItems();
    m_iStyle = 0;	
	bWorking = cFinder.FindFile(_T(g_strOriginalPathD+"glass\\*.c*"));  //工件文件的后缀名
	
    while (bWorking)
    {
        bWorking = cFinder.FindNextFile();

        m_list.InsertItem(i,(LPCTSTR) cFinder.GetFileName(),1);
		i++;
    }
	m_list.SetItemState(0,3,0xffff);//SetFocus();
	m_list.SetFocus();

}

void dlg_path2::OnButton2() 
{
	BOOL bWorking;
    CFileFind cFinder;
	int i = 0;
	
	m_list.DeleteAllItems();
	if (m_iStyle != 1)
	{
		m_strFilePath = "";
		m_iStyle = 1;
	}
	if(!m_strFilePath.IsEmpty())
	{
		m_list.InsertItem(i,m_strHeadShow,2);
		i++;
	}
	
	//**************寻找文件夹*******************************
	bWorking = cFinder.FindFile(_T("D:\\Program Files\\GlassCutter\\dxf\\"+m_strFilePath+"*.*")); 
	while (bWorking)
	{
		bWorking = cFinder.FindNextFile();
		if (cFinder.IsDirectory() && !cFinder.IsDots() && !cFinder.IsHidden())
		{
			//	GetIconIndex(cFinder.GetFileName());
			m_list.InsertItem(i,(LPCTSTR) cFinder.GetFileName(),0);
			i++;
		}
	}
	//*********************************************
	
	bWorking = cFinder.FindFile(_T("D:\\Program Files\\GlassCutter\\dxf\\"+m_strFilePath+"*.dxf"));  //工件文件的后缀名	
    while (bWorking)
    {
        bWorking = cFinder.FindNextFile();
		
        m_list.InsertItem(i,(LPCTSTR) cFinder.GetFileName(),1);
		i++;
    }
	m_list.SetItemState(0,3,0xffff);//SetFocus();
	m_list.SetFocus();
}

void dlg_path2::OnButton3() 
{
	BOOL bWorking;
    CFileFind cFinder;
	int i = 0;

	m_list.DeleteAllItems();
	if (m_iStyle != 2)
	{
		m_strFilePath = "";
		m_iStyle = 2;
	}
	if(!m_strFilePath.IsEmpty())
	{
		m_list.InsertItem(i,m_strHeadShow,2);
		i++;
	}

	//**************寻找文件夹*******************************
	bWorking = cFinder.FindFile(_T("D:\\Program Files\\GlassCutter\\gcode\\"+m_strFilePath+"*.*")); 
	while (bWorking)
	{
		bWorking = cFinder.FindNextFile();
		if (cFinder.IsDirectory() && !cFinder.IsDots() && !cFinder.IsHidden())
		{
			//	GetIconIndex(cFinder.GetFileName());
			m_list.InsertItem(i,(LPCTSTR) cFinder.GetFileName(),0);
			i++;
		}
	}
	//*********************************************

	bWorking = cFinder.FindFile(_T("D:\\Program Files\\GlassCutter\\gcode\\"+m_strFilePath+"*.g"));  //工件文件的后缀名	
    while (bWorking)
    {
        bWorking = cFinder.FindNextFile();

        m_list.InsertItem(i,(LPCTSTR) cFinder.GetFileName(),1);
		i++;
    }
	m_list.SetItemState(0,3,0xffff);//SetFocus();
	m_list.SetFocus();
}

void dlg_path2::OnButton5() 
{
	dlg_manager manager;
	manager.DoModal();
}

void dlg_path2::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(m_iStyle == 2)//G代码选择       
	{
		if(m_strFilename == m_strHeadShow)//如果是返回上一级目录
		{
			GotoFowardMenu();
			return;
		}
		g_strGfile = g_strOriginalPathD+"gcode\\"+m_strFilePath+m_strFilename;
		//**************鉴定是否是文件夹*******************************
		int i = 0;
		BOOL bWorking;
		CFileFind cFinder;
		bWorking = cFinder.FindFile(_T(g_strGfile)); 
		while (bWorking)
		{
			bWorking = cFinder.FindNextFile();
			if (cFinder.IsDirectory())//是文件夹,打开后返回
			{
				m_list.DeleteAllItems();
				m_strFilePath += m_strFilename + "\\";
				if(!m_strFilePath.IsEmpty())
				{
					m_list.InsertItem(i,m_strHeadShow,2);
					i++;
				}
				
				CString strPath = g_strGfile + "\\*.*";
				bWorking = cFinder.FindFile(_T(strPath)); 
				while (bWorking)
				{
					bWorking = cFinder.FindNextFile();
					if (cFinder.IsDirectory() && !cFinder.IsDots() && !cFinder.IsHidden())
					{
						m_list.InsertItem(i,(LPCTSTR) cFinder.GetFileName(),0);
						i++;
					}
				}
				
				strPath = g_strGfile + "\\*.g";
				bWorking = cFinder.FindFile(_T(strPath)); 
				while (bWorking)
				{
					bWorking = cFinder.FindNextFile();
					//	GetIconIndex(cFinder.GetFileName());
					m_list.InsertItem(i,(LPCTSTR) cFinder.GetFileName(),1);
					i++;
				}	
				
				cFinder.Close();
				m_list.SetItemState(0,3,0xffff);//SetFocus();
				m_list.SetFocus();
				return;
			}
			cFinder.Close(); //不是文件夹,继续后续操作
			OnButton7();
			return;
		}
		//*********************************************
	}
	else if(m_iStyle == 1)//dxf代码选择
	{
		if(m_strFilename == m_strHeadShow)//如果是返回上一级目录
		{
			GotoFowardMenu();
			return;
		}
		g_strGfile = g_strOriginalPathD+"dxf\\"+m_strFilePath+m_strFilename;
		//**************鉴定是否是文件夹*******************************
		int i = 0;
		BOOL bWorking;
		CFileFind cFinder;
		bWorking = cFinder.FindFile(_T(g_strGfile)); 
		while (bWorking)
		{
			bWorking = cFinder.FindNextFile();
			if (cFinder.IsDirectory())//是文件夹,打开后返回
			{
				m_list.DeleteAllItems();
				m_strFilePath += m_strFilename + "\\";
				if(!m_strFilePath.IsEmpty())
				{
					m_list.InsertItem(i,m_strHeadShow,2);
					i++;
				}
				
				CString strPath = g_strGfile + "\\*.*";
				bWorking = cFinder.FindFile(_T(strPath)); 
				while (bWorking)
				{
					bWorking = cFinder.FindNextFile();
					if (cFinder.IsDirectory() && !cFinder.IsDots() && !cFinder.IsHidden())
					{
						m_list.InsertItem(i,(LPCTSTR) cFinder.GetFileName(),0);
						i++;
					}
				}
				
				strPath = g_strGfile + "\\*.dxf";
				bWorking = cFinder.FindFile(_T(strPath)); 
				while (bWorking)
				{
					bWorking = cFinder.FindNextFile();
					m_list.InsertItem(i,(LPCTSTR) cFinder.GetFileName(),1);
					i++;
				}	
				
				cFinder.Close();
				m_list.SetItemState(0,3,0xffff);//SetFocus();
				m_list.SetFocus();
				return;
			}
			cFinder.Close(); //不是文件夹,继续后续操作
			OnButton7();
			return;
		}
	}
    g_strShowName = m_strFilename;	
	*pResult = 0;
}

//返回上级目录
void dlg_path2::GotoFowardMenu()
{
	int step = 0;
	bool bEnd = false;

	while (m_strFilePath.GetLength() > 0)
	{
		char c = m_strFilePath.GetAt(m_strFilePath.GetLength()-1);
		switch(step)
		{
		case 0:
			{
				if(c == '\\')
				{
					step = 1;
					m_strFilePath.Delete(m_strFilePath.GetLength()-1,1);
				}
				else 
					m_strFilePath.Delete(m_strFilePath.GetLength()-1,1);
			}
			break;
		case 1:
			{
				if(c == '\\')
					bEnd = true;
				else 
					m_strFilePath.Delete(m_strFilePath.GetLength()-1,1);
			}
			break;
		}		
		if(bEnd)
			break;
	}
	m_strFilename = "";
    if(m_iStyle == 1)//dxf代码选择
	{
		OnButton2();
	}
	else
	{
		OnButton3();
	}
}

void dlg_path2::InitButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_FILESTY1);
	//cxf	
	m_pButton[0].SetFont(&g_fontEdit);
	m_pButton[0].SetBitMapID(IDB_BITMAP_FILESTY1,IDB_BITMAP_FILESTY2);	
	m_pButton[0].Create(g_arr_strPath2[4][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(310, 705), c, this, IDC_BUTTON1); 
	//dxf	
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_FILESTY1,IDB_BITMAP_FILESTY2);	
	m_pButton[1].Create(g_arr_strPath2[5][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(170, 705), c, this, IDC_BUTTON2); 
	//G
	m_pButton[2].SetFont(&g_fontEdit);
	m_pButton[2].SetBitMapID(IDB_BITMAP_FILESTY1,IDB_BITMAP_FILESTY2);	
	m_pButton[2].Create(g_arr_strPath2[6][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(30, 705), c, this, IDC_BUTTON3); 
	
	//打开	
	m_pButton[4].SetFont(&g_fontEdit);
	m_pButton[4].SetBitMapID(IDB_BITMAP_OPEN1,IDB_BITMAP_OPEN2);	
	m_pButton[4].Create(g_arr_strPath2[3][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(460, 705), c, this, IDC_BUTTON7); 
	
	//绘图
	m_pButton[6].SetFont(&g_fontEdit);
	m_pButton[6].SetBitMapID(IDB_BITMAP_DRAW1,IDB_BITMAP_DRAW2);	
	m_pButton[6].Create(g_arr_strPath2[8][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(600, 705), c, this, IDC_BUTTON4); 

	//文件管理	
	m_pButton[3].SetFont(&g_fontStatic);
	m_pButton[3].SetBitMapID(IDB_BITMAP_FILEMAN1,IDB_BITMAP_FILEMAN2);	
	m_pButton[3].Create(g_arr_strPath2[7][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(750, 705), c, this, IDC_BUTTON5); 
	//返回	
	m_pButton[5].SetFont(&g_fontEdit);
	m_pButton[5].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[5].Create(g_arr_strPath2[9][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(900, 705), c, this, IDC_BUTTON10); 
    
	DeleteObject(c);
}

void dlg_path2::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//贴背景图片
	CDC  MemDc;
	CBitmap bitmap;	
	MemDc.CreateCompatibleDC(&dc);
	bitmap.LoadBitmap(IDB_BITMAP_DIALOG);
	CBitmap *pOldBit = MemDc.SelectObject(&bitmap);
	MemDc.FillSolidRect(665,375,351,300,RGB(255,255,255));
    DrawGcode(&MemDc);
	dc.BitBlt(0,0,1024,768,&MemDc,0,0,SRCCOPY);
	MemDc.SelectObject(pOldBit);
	bitmap.DeleteObject();
	MemDc.DeleteDC();
	CDialog::OnPaint();	
	// Do not call CDialog::OnPaint() for painting messages
}

HBRUSH dlg_path2::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (pWnd->GetDlgCtrlID()==IDC_STATIC1 || pWnd->GetDlgCtrlID()==IDC_STATIC_FILEVIEW)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);		
	}	
	return hbr;
}

void dlg_path2::OnButton4()
{
	if(m_strFilename == m_strHeadShow || m_strFilename=="")//如果是返回上一级目录
	{
		return;
	}	
	if (m_iStyle == 2)
	{
		if((!strstr(m_strFilename,".g")))
			return;
	}
	g_strGfile = g_strDxffile = ""; 
	if(m_iStyle == 0)					g_strGfile = g_strOriginalPathD+"glass\\"+m_strFilename;
	else if(m_iStyle == 1)			g_strGfile = g_strOriginalPathD+"dxf\\"+m_strFilePath+m_strFilename;
	else if(m_iStyle == 2)			g_strGfile = g_strOriginalPathD+"gcode\\"+m_strFilePath+m_strFilename;     
	CDlg_DrawCad dlg;	
	dlg.DoModal();
}

//得到G代码的文本，画图信息,显示并画图
void dlg_path2::ProcessGcodeInf()
{
	if(0 == m_ReadGcode.SetGFile(m_strFileShow))
	{
       ShowListGcode();
	   CRect rect(665,375,351+665,300+375);
	   InvalidateRect(&rect,TRUE);
	}
}

//显示G代码文本信息
void dlg_path2::ShowListGcode()
{	
	m_ListGcode.ResetContent();
	for (int i=0;i<m_ReadGcode.m_nVecSize;i++)
	{
		m_ListGcode.InsertString(i,m_ReadGcode.m_vecGCode[i].strGCode);
	}
}

//画图(665,375,351+665,300+375)
void dlg_path2::DrawGcode(CDC *pMenuDc)
{
	CPen pen;
	pen.CreatePen(PS_SOLID,2,RGB(79,167,214));//0,200,0
	CPen *poldpen = pMenuDc->SelectObject(&pen);
	POINT2D pointBg;
	POINT2D pointEnd;	 
	double dScale = 347.0 / (m_ReadGcode.m_rct.right-m_ReadGcode.m_rct.left);
	double dScaleY = 296.0 / (m_ReadGcode.m_rct.top-m_ReadGcode.m_rct.bottom);
	if (dScale > dScaleY)
	{
		dScale = dScaleY;
	}
	bool bHaveG00 = false;
	for (int i=0;i<m_ReadGcode.m_nVecSize;i++)
	{
		G_Code g = m_ReadGcode.m_vecGCode[i];
		if (g.bDraw)
		{
			if (g.bG00)
			{
				pointEnd = g.stuData.line.en;
				pMenuDc->MoveTo(667 + int(pointEnd.x * dScale),673 - int(pointEnd.y * dScale));
				bHaveG00 = true;
			}
			else
			{
				if (g.stuData.bLineOrArc)
				{
					pointEnd = g.stuData.line.en;
					if (!bHaveG00)
					{
						pointBg = g.stuData.line.bg;
						pMenuDc->MoveTo(667 + int(pointBg.x * dScale),673 - int(pointBg.y * dScale));
						bHaveG00 = true;
					}
					pMenuDc->LineTo(667 + int(pointEnd.x * dScale),673 - int(pointEnd.y * dScale));	
				}
				else
				{
					if (!bHaveG00)
					{
						pointBg = g.stuData.arc.bg;
						pMenuDc->MoveTo(667 + int(pointBg.x * dScale),673 - int(pointBg.y * dScale));
						bHaveG00 = true;
					}
				    BreakDrawArc(pMenuDc,g.stuData.arc,dScale);
				}
			}
		}   
	}
	pMenuDc->SelectObject(poldpen);
	pen.DeleteObject();
}

//将圆弧打碎成小线段,并画图，解决直接画圆的精度丢失
//pMenuDc:画图用虚拟dc；arc:圆弧信息；dScale:画图比例
void dlg_path2::BreakDrawArc(CDC *pMenuDc, tagArc arc, double dScale)
{
	POINT3D pPoint,pCenter;
	float currAngle = arc.fStart;
	int     i,number;
	float interval = 2.0f;//打碎精度	
	
	pCenter.x = arc.o.x;/* 计算圆心 */
	pCenter.y = arc.o.y;
	
	
	if(arc.fSweep<0)     interval = -interval;//顺时针
	else	             interval = interval; //逆时针
	
	number = (int)(arc.fSweep/interval);    /* 计算循环次数 */
	if(fabs(arc.fSweep-interval*number)*1000>0) /* 计算是否最后有余数，有余数加1次循环 */
		number++;
	
	for(i=0;i<number;i++)
	{
		if(i==number-1)				
			currAngle = (float)(arc.fStart + arc.fSweep);
		else        				
			currAngle = (float)(currAngle + interval);
		
		pPoint.x = pCenter.x + arc.r * cos(currAngle*PI/180);
		pPoint.y = pCenter.y + arc.r * sin(currAngle*PI/180);
		pMenuDc->LineTo(667 + int(pPoint.x * dScale),673 - int(pPoint.y * dScale));		
	}	
}
