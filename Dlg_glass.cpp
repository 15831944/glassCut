// Dlg_glass.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_glass.h"
#include "Dlg_KeyNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_glass dialog

#pragma warning( disable: 4244)

CDlg_glass::CDlg_glass(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_glass::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_glass)
	nItem = 0;
	//}}AFX_DATA_INIT
}


void CDlg_glass::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_glass)
	//}}AFX_DATA_MAP
//	DDX_GridControl(pDX, IDC_PRESSURE, m_Grid);
}


BEGIN_MESSAGE_MAP(CDlg_glass, CDialog)
	//{{AFX_MSG_MAP(CDlg_glass)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_glass message handlers

BOOL CDlg_glass::OnInitDialog() 
{
	CString  szStr;
	CDialog::OnInitDialog();
	m_nMM[0] = 0;//第零个不用
	m_nMM[1] = 2;
	m_nMM[2] = 3;
	m_nMM[3] = 4;
	m_nMM[4] = 5;
	m_nMM[5] = 6;
	m_nMM[6] = 8;
	m_nMM[7] = 10;
	m_nMM[8] = 12;
	m_nMM[9] = 15;
	m_nMM[10] = 19;
	m_nMM[11] = 20;
	OnLanguage();
	OnInitGrid(); 
    InitButton();
	SetWindowPos(&CWnd::wndTop,0,0,1024,768,SWP_SHOWWINDOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_glass::OnInitGrid() 
{
	
	m_ImageList.Create(MAKEINTRESOURCE(IDB_IMAGES), 16, 1, RGB(255,255,255));
	m_Grid.SubclassDlgItem(IDC_PRESSURE, this);

	m_Grid.SetImageList(&m_ImageList);
	m_Grid.SetFont(&g_fontList);
	
	m_Grid.SetEditable(TRUE);
	m_Grid.SetListMode(TRUE);
	m_Grid.EnableDragAndDrop(TRUE);
	m_Grid.SetHeaderSort(FALSE);
	m_Grid.SetRowResize(FALSE);
	m_Grid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));
	
	TRY {
		m_Grid.SetRowCount(12);
		m_Grid.SetColumnCount(20);//总列数
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
	
	PPRESSURE	pTempPress, pHeadPress;
	int			row, col;
	GV_ITEM Item;
	pHeadPress = g_CutPress.GetHeadPressure();

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
			case 1:		Item.szText.Format(_T("下刀压力"));	break;
			case 2:		Item.szText.Format(_T("抬刀压力"));	break;
			case 3:		Item.szText.Format(_T("抬刀延时"));	break;
			case 4:		Item.szText.Format(_T("抬刀后延时"));	break;
			case 5:		Item.szText.Format(_T("直线加压"));	break;
			case 6:		Item.szText.Format(_T("时间"));		break;
			case 7:		Item.szText.Format(_T("X正"));		break;
			case 8:		Item.szText.Format(_T("X反"));		break;
			case 9:		Item.szText.Format(_T("Y正"));		break;
			case 10:	Item.szText.Format(_T("Y反"));		break;
			case 11:	Item.szText.Format(_T("插补"));	break;
			case 12:	Item.szText.Format(_T("圆弧加压"));	break;
			case 13:	Item.szText.Format(_T("时间"));		break;
			case 14:	Item.szText.Format(_T("小压"));		break;
			case 15:	Item.szText.Format(_T("小半径"));	break;
			case 16:	Item.szText.Format(_T("中压"));		break;
			case 17:	Item.szText.Format(_T("大半径"));	break;
			case 18:	Item.szText.Format(_T("大压"));		break;
			case 19:	Item.szText.Format(_T("下刀延迟"));	break;
			default:	Item.szText.Format(_T("厚度"));		break;
			}
		}
		else
		{
			switch(col) 
			{
			case 1:		Item.szText.Format(_T("Down press"));		break;
			case 2:		Item.szText.Format(_T("Up press"));		break;
			case 3:		Item.szText.Format(_T("Cutter lifting delay"));		break;
			case 4:		Item.szText.Format(_T("After Up delay"));		break;
			case 5:		Item.szText.Format(_T("linear pressing"));		break;
			case 6:		Item.szText.Format(_T("Time"));				break;
			case 7:		Item.szText.Format(_T("X positive"));			break;
			case 8:		Item.szText.Format(_T("X reverse"));		break;
			case 9:		Item.szText.Format(_T("Y positive"));			break;
			case 10:	Item.szText.Format(_T("Y reverse"));		break;
			case 11:	Item.szText.Format(_T("Slant"));		   break;
			case 12:	Item.szText.Format(_T("Circular press"));		break;
			case 13:	Item.szText.Format(_T("Time"));				break;
			case 14:	Item.szText.Format(_T("Small press"));			break;
			case 15:	Item.szText.Format(_T("Minor radius"));		break;
			case 16:	Item.szText.Format(_T("Mid press"));			break;
			case 17:	Item.szText.Format(_T("Big radius"));		break;
			case 18:	Item.szText.Format(_T("Big press"));			break;
			case 19:	Item.szText.Format(_T("Down delay"));	break;
			default:	Item.szText.Format(_T("Thinckness"));		break;
			}
		}
		m_Grid.SetItem(&Item);
	}		
	// fill rows/cols with text
	for (row = 1,pTempPress=pHeadPress; row < m_Grid.GetRowCount(),pTempPress; row++,pTempPress=pTempPress->pNext)
	{
		for (col = 0; col < m_Grid.GetColumnCount(); col++)//行
		{ 
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			if (col < 1) /* 固定 列 显示mm的列*/
            {
				Item.nFormat = dwTextStyle;
				Item.szText.Format(_T("%d[mm]"),m_nMM[row]);
			}
            else 
            {
				Item.nFormat = dwTextStyle;
				switch(col) 
				{
				case 1:
					Item.szText.Format(_T("%.2f"),pTempPress->dToolDown);		
					break;
				case 2:
					Item.szText.Format(_T("%.2f"),pTempPress->dToolUp);		
					break;
				case 3:
					Item.szText.Format(_T("%d"),pTempPress->nUpDelay);	
					break; 
				case 4:
					Item.szText.Format(_T("%d"),pTempPress->nAfterUpDelay);	
					break;
				case 5:
					Item.szText.Format(_T("%.2f"),pTempPress->dLineAddPress);		
					break;
				case 6:
					Item.szText.Format(_T("%d"),pTempPress->nLineAddTime);		
					break;
				case 7:
					Item.szText.Format(_T("%.2f"),pTempPress->dPressXAdd);		
					break;
				case 8:
					Item.szText.Format(_T("%.2f"),pTempPress->dPressXSub);		
					break;
				case 9:
					Item.szText.Format(_T("%.2f"),pTempPress->dPressYAdd);		
					break;
				case 10:
					Item.szText.Format(_T("%.2f"),pTempPress->dPressYSub);		
					break;
				case 11:
					Item.szText.Format(_T("%.2f"),pTempPress->dPressSlant);		
					break;
				case 12:
					Item.szText.Format(_T("%.2f"),pTempPress->dArcAddPress);		
					break;
				case 13:
					Item.szText.Format(_T("%d"),pTempPress->nArcAddTime);		
					break;
				case 14:
					Item.szText.Format(_T("%.2f"),pTempPress->dPressSmall);		
					break;
				case 15:
					Item.szText.Format(_T("%.2f"),pTempPress->dRadiusSmall);		
					break;
				case 16:
					Item.szText.Format(_T("%.2f"),pTempPress->dPressMidle);		
					break;
				case 17:
					Item.szText.Format(_T("%.2f"),pTempPress->dRadiusBig);		
					break;
				case 18:
					Item.szText.Format(_T("%.2f"),pTempPress->dPressBig);		
					break;
				case 19:
					Item.szText.Format(_T("%d"),pTempPress->nToolDelay);		
					break;
				default:
					break;
				}
			}
			m_Grid.SetItem(&Item);			
		}
	}	
	m_Grid.AutoSize();
	m_Grid.SetFocus();
	m_Grid.SetFocusCell(1,1);
}

BOOL CDlg_glass::PreTranslateMessage(MSG* pMsg) 
{
	if( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CWnd			*pWnd=NULL;
		char			cClassName[50]={0};
		pWnd = GetFocus();
		GetClassName(pWnd->GetSafeHwnd(), cClassName, 50);//获取控件的类名    
		
		if(strstr(cClassName, "MFCGridCtrl"))
		{            
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlg_glass::OnButton8() 
{
	g_iPassgrade = 0;
	OnSavePressure();
	CDialog::OnOK();
}

void CDlg_glass::OnButton10() 
{
    g_iPassgrade = 0;
	CDialog::OnCancel();
}

void CDlg_glass::OnLanguage()
{
	int   i;
	int		nIndex;
	nIndex = g_iLanguage + 1;
	for(i=0;i<AR_GLASS;i++)
	{
		CWnd::SetDlgItemText(atoi(g_arr_glass[i][0]),g_arr_glass[i][nIndex]);
	}
}

void CDlg_glass::OnScale()
{
	CString		szStr;
	if(g_stu_pAxisH->sSpare==0)	/* 公制 */
	{
		szStr.Format("%.2f",g_stu_pAxisG->dSpareA);	SetDlgItemText(IDC_CENTERX,szStr);
		szStr.Format("%.2f",g_stu_pAxisH->dSpareA);	SetDlgItemText(IDC_CENTERY,szStr);
		szStr.Format("%.2f",g_stu_pAxisC->dSpareD);	SetDlgItemText(IDC_EDIT_MINCORNERSP,szStr);
		szStr.Format("%.2f",g_stu_pAxisD->dSpareD);	SetDlgItemText(IDC_EDIT_MINARCSP,szStr);
		szStr.Format("%.2f",g_stu_pAxisE->dSpareD);	SetDlgItemText(IDC_EDIT_MINRADIUS,szStr);
	}
	else						/* 英制 */
	{
		szStr.Format("%.2f",g_stu_pAxisG->dSpareA * MM_TO_IN);	SetDlgItemText(IDC_CENTERX,szStr);
		szStr.Format("%.2f",g_stu_pAxisH->dSpareA * MM_TO_IN);	SetDlgItemText(IDC_CENTERY,szStr);
		szStr.Format("%.2f",g_stu_pAxisC->dSpareD * MM_TO_IN);	SetDlgItemText(IDC_EDIT_MINCORNERSP,szStr);
		szStr.Format("%.2f",g_stu_pAxisD->dSpareD * MM_TO_IN);	SetDlgItemText(IDC_EDIT_MINARCSP,szStr);
		szStr.Format("%.2f",g_stu_pAxisE->dSpareD * MM_TO_IN);	SetDlgItemText(IDC_EDIT_MINRADIUS,szStr);
	}
}

void CDlg_glass::OnSavePressure() 
{
	CString		strTemp;
	
	DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
#ifndef _WIN32_WCE
    dwTextStyle |= DT_END_ELLIPSIS;
#endif
	
	PPRESSURE	pTempPress, pHeadPress;
	int			row, col;
	GV_ITEM Item;
	pHeadPress = g_CutPress.GetHeadPressure();
	
	for (row = 1,pTempPress=pHeadPress; row < m_Grid.GetRowCount(),pTempPress; row++,pTempPress=pTempPress->pNext)
	{
		strTemp.Empty();
		for (col = 0; col < m_Grid.GetColumnCount(); col++)
		{ 
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			m_Grid.GetItem(&Item);
			
			if (col < 1)	/* 固定列 */
			{
				Item.nFormat = dwTextStyle;
				strTemp = Item.szText;
				pTempPress->nThickness = atoi(strTemp);
			}
			else 
			{
				Item.nFormat = dwTextStyle;
				switch(col) 
				{
				case 1:
					pTempPress->dToolDown = atof(Item.szText);		
					break;
				case 2:
					pTempPress->dToolUp = atof(Item.szText);		
					break;
				case 3:
					pTempPress->nUpDelay = atoi(Item.szText);			
					break;
				case 4:
					pTempPress->nAfterUpDelay = atoi(Item.szText);			
					break;
				case 5:
					pTempPress->dLineAddPress = atof(Item.szText);		
					break;
				case 6:
					pTempPress->nLineAddTime = atoi(Item.szText);		
					break;
				case 7:
					pTempPress->dPressXAdd = atof(Item.szText);		
					break;
				case 8:
					pTempPress->dPressXSub = atof(Item.szText);		
					break;
				case 9:
					pTempPress->dPressYAdd = atof(Item.szText);		
					break;
				case 10:
					pTempPress->dPressYSub = atof(Item.szText);		
					break;
				case 11:
					pTempPress->dPressSlant = atof(Item.szText);		
					break;
				case 12:
					pTempPress->dArcAddPress = atof(Item.szText);		
					break;
				case 13:
					pTempPress->nArcAddTime = atoi(Item.szText);		
					break;
				case 14:
					pTempPress->dPressSmall = atof(Item.szText);		
					break;
				case 15:
					pTempPress->dRadiusSmall = atof(Item.szText);		
					break;
				case 16:
					pTempPress->dPressMidle = atof(Item.szText);		
					break;
				case 17:
					pTempPress->dRadiusBig = atof(Item.szText);		
					break;
				case 18:
					pTempPress->dPressBig = atof(Item.szText);		
					break;
				case 19:
					pTempPress->nToolDelay = atoi(Item.szText);		
					break;
				default:
					break;
				}
			}
		}
	}
	g_CutPress.SavePressure();
}

void CDlg_glass::InitButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_ZEOR1);
	//保存
	m_pButton[0].SetFont(&g_fontEdit);
	m_pButton[0].SetBitMapID(IDB_BITMAP_SAVE1,IDB_BITMAP_SAVE2);	
	m_pButton[0].Create(g_arr_glass[0][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(700, 705), c, this, IDC_BUTTON8); 
	
	//返回	
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[1].Create(g_arr_glass[2][g_iLanguage+1], WS_CHILD | WS_VISIBLE, CPoint(870, 705), c, this, IDC_BUTTON10); 
    
	DeleteObject(c); 	
}

BOOL CDlg_glass::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(g_stu_pAxisC->bSpareA==0)
		return CDialog::OnCommand(wParam, lParam);
	if (wParam != MAKELONG(IDC_PRESSURE, BN_CLICKED))
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
		strCell = m_Grid.GetItemText(pCell->row, pCell->col);
		KeyNum.m_strNew = KeyNum.m_strOld = strCell;
		if(KeyNum.DoModal()==IDOK)
		{
			m_Grid.SetItemText(pCell->row, pCell->col, KeyNum.m_strNew);
			m_Grid.RedrawCell(pCell->row, pCell->col);
		}
	}			
	return CDialog::OnCommand(wParam, lParam);
}
