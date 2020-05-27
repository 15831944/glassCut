// dlg_ustLimit.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "dlg_ustLimit.h"
#include "Dlg_KeyNumber.h"
#include "Dlg_KeyChar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dlg_ustLimit dialog


dlg_ustLimit::dlg_ustLimit(CWnd* pParent /*=NULL*/)
	: CDialog(dlg_ustLimit::IDD, pParent)
{
	//{{AFX_DATA_INIT(dlg_ustLimit)
	//}}AFX_DATA_INIT
}


void dlg_ustLimit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dlg_ustLimit)
	DDX_Control(pDX, IDC_STATIC_DAY1, m_ctrday1);
	DDX_Control(pDX, IDC_STATIC_MON1, m_ctrmon1);
	DDX_Control(pDX, IDC_STATIC_YEAR1, m_ctryear1);
	DDX_Control(pDX, IDC_STATIC_DATE1, m_ctrdate1);
	DDX_Control(pDX, IDC_STATIC_DATE2, m_ctrdate2);
	DDX_Control(pDX, IDC_EDIT1, m_edt1);
	DDX_Control(pDX, IDC_EDIT_YEAR2, m_edtYear2);
	DDX_Control(pDX, IDC_EDIT_YEAR1, m_edtYear1);
	DDX_Control(pDX, IDC_EDIT_MONTH1, m_edtMonth1);
	DDX_Control(pDX, IDC_EDIT_DAY1, m_edtDay1);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_cal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dlg_ustLimit, CDialog)
	//{{AFX_MSG_MAP(dlg_ustLimit)
	ON_BN_CLICKED(IDC_BUTTONL7, OnButtonl7)
	ON_BN_CLICKED(IDC_BUTTONL8, OnButtonl8)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dlg_ustLimit message handlers

BOOL dlg_ustLimit::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	OnLanguageustLimit();
    OnButtonTime();	
	//读以下五个加密时间信息
	HasReadValue(g_arr_strLimit[0][0],TIME_YEAR);//加密的时间
	HasReadValue(g_arr_strLimit[0][1],TIME_MONTH);//加密的时间
	HasReadValue(g_arr_strLimit[0][2],TIME_DAY);//加密的时间
	HasReadValue(g_arr_strLimit[0][3],TIME_SECRET);//加密的密码
	HasReadValue(g_arr_strLimit[0][4],TIME_VENDER);//加密的厂家号

	
	CWnd::SetDlgItemText(IDC_EDIT_YEAR1,g_arr_strLimit[0][0]);
	CWnd::SetDlgItemText(IDC_EDIT_MONTH1,g_arr_strLimit[0][1]);	
	CWnd::SetDlgItemText(IDC_EDIT_DAY1,g_arr_strLimit[0][2]);
	CWnd::SetDlgItemText(IDC_EDIT1,g_arr_strLimit[0][3]);
	CWnd::SetDlgItemText(IDC_EDIT_YEAR2,g_arr_strLimit[0][4]);//厂家号
    InitButton();
	SetWindowPos(&CWnd::wndTop,0,0,1024,768,SWP_SHOWWINDOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void dlg_ustLimit::OnButtonl7() 
{
	CString tmp;
    GetDlgItemText(IDC_EDIT_YEAR1,tmp);    
	HasWriteValue(tmp,TIME_YEAR);

	GetDlgItemText(IDC_EDIT_MONTH1,tmp);        
	HasWriteValue(tmp,TIME_MONTH);

	GetDlgItemText(IDC_EDIT_DAY1,tmp);          
	HasWriteValue(tmp,TIME_DAY);

	GetDlgItemText(IDC_EDIT1,tmp);              
	HasWriteValue(tmp,TIME_SECRET);

	GetDlgItemText(IDC_EDIT_YEAR2,tmp);         
	HasWriteValue(tmp,TIME_VENDER);	

    g_iPassgrade = 0;
	CDialog::OnOK();
}

BOOL dlg_ustLimit::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->lParam==VK_TAB||pMsg->wParam==VK_TAB)
		return TRUE;
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void dlg_ustLimit::OnButtonTime() 
{
	CString temp,str;
	CTime   tm;
	m_cal.GetCurSel(tm);
	if (!g_iLanguage) 
	{
		str.Format("%d",tm.GetYear());
		temp = str+"年";
		str.Format("%d",tm.GetMonth());
		temp = temp + str+"月";
		str.Format("%d",tm.GetDay());
		temp = temp + str+"日";
	}
	else
	{
		str.Format("%d",tm.GetYear());
		temp = str + " - ";
		str.Format("%d",tm.GetMonth());
		temp = temp + str + " - ";
		str.Format("%d",tm.GetDay());
		temp = temp + str;
	}
	CWnd::SetDlgItemText(IDC_STATIC_DAY,temp);
}

void dlg_ustLimit::OnButtonl8() 
{
    g_iPassgrade = 0; 
	CDialog::OnOK();
}

LRESULT dlg_ustLimit::OnEditDouble(WPARAM wParam, LPARAM lParam) 
{
	CString				strTmp;
	CDlg_KeyNumber		KeyNum;
	
	if(lParam==1)/* 有触摸屏 */
	{
		((CEdit *)GetDlgItem(wParam))->SetSel(0,-1);
		return 0;
	}
	
	CWnd::GetDlgItemText(wParam,strTmp);
	KeyNum.m_strNew = KeyNum.m_strOld = strTmp;
	
	if (!g_iLanguage) 
	{
		switch(wParam) 
		{
		case IDC_EDIT_YEAR1:			KeyNum.m_strTitle = "日期1  年份";				break;
		case IDC_EDIT_YEAR2:			KeyNum.m_strTitle = "厂家号";				break;
			
		case IDC_EDIT_MONTH1:			KeyNum.m_strTitle = "日期1  月份";				break;			
		case IDC_EDIT_DAY1:				KeyNum.m_strTitle = "日期1  日期";				break;		
		case IDC_EDIT1:					KeyNum.m_strTitle = "日期1  密码";				break;		
		default:
			break;
		}
	}
	else
	{
		switch(wParam) 
		{
		case IDC_EDIT_YEAR1:			KeyNum.m_strTitle = "Date1  Year";				break;
		case IDC_EDIT_YEAR2:			KeyNum.m_strTitle = "NO.";				        break;			
		case IDC_EDIT_MONTH1:			KeyNum.m_strTitle = "Date1  Month";				break;
		case IDC_EDIT_DAY1:				KeyNum.m_strTitle = "Date1  Day";				break;			
		case IDC_EDIT1:					KeyNum.m_strTitle = "Date1  PassWord";			break;		
		default:
			break;
		}
	}
	if (wParam == IDC_EDIT_YEAR2)
	{
		CDlg_KeyChar		KeyChar;
		KeyChar.m_strNew = KeyChar.m_strOld = strTmp;
		if(KeyChar.DoModal()==IDOK)
			CWnd::SetDlgItemText(wParam,KeyChar.m_strNew);

	}
	else 
	{
		if(KeyNum.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	}
	
	return 0;
}

void dlg_ustLimit::OnLanguageustLimit()
{
	if (!g_iLanguage) 
	{
		CWnd::GetDlgItem(IDC_STATIC_CURTIEM)->SetWindowText("当前日期：");
		CWnd::GetDlgItem(IDC_DEMO10CTRL1)->SetWindowText("使用限制");		
		m_ctrdate1.SetWindowText("到期时间");
		m_ctrdate2.SetWindowText("厂家号");
		m_ctryear1.SetWindowText("年");
		m_ctrmon1.SetWindowText("月");
		m_ctrday1.SetWindowText("日");
		
	}
	else
	{
		CWnd::GetDlgItem(IDC_BUTTONL6)->SetWindowText(""); 
		CWnd::GetDlgItem(IDC_BUTTONL7)->SetWindowText("SetUp");
		CWnd::GetDlgItem(IDC_BUTTONL8)->SetWindowText("Return");
		CWnd::GetDlgItem(IDC_STATIC_CURTIEM)->SetWindowText("Current Time:");
		CWnd::GetDlgItem(IDC_DEMO10CTRL1)->SetWindowText("Usage Limit");
		m_ctrdate1.SetWindowText("1st Password");
		m_ctrdate2.SetWindowText("Vender NO.");
		m_ctryear1.SetWindowText("Year");		
		m_ctrmon1.SetWindowText("Month");		
		m_ctrday1.SetWindowText("Day");
	}
}

void dlg_ustLimit::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//贴背景图片
	CDC  MemDc;
	CBitmap bitmap;	
	MemDc.CreateCompatibleDC(&dc);
	bitmap.LoadBitmap(IDB_BITMAP_DIALOG);
	CBitmap *pOldBit = MemDc.SelectObject(&bitmap);
	dc.BitBlt(0,0,1024,768,&MemDc,0,0,SRCCOPY);
	MemDc.SelectObject(pOldBit);
	bitmap.DeleteObject();
	MemDc.DeleteDC();
	CDialog::OnPaint();		
	// Do not call CDialog::OnPaint() for painting messages
}

void dlg_ustLimit::InitButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_ZEOR1);
	//保存
	m_pButton[0].SetFont(&g_fontEdit);
	m_pButton[0].SetBitMapID(IDB_BITMAP_SAVE1,IDB_BITMAP_SAVE2);	
	m_pButton[0].Create(g_arr_strSuper[12][g_iLanguage + 1], WS_CHILD | WS_VISIBLE, CPoint(700, 705), c, this, IDC_BUTTONL7); 
	
	//返回	
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[1].Create(g_arr_strSuper[13][g_iLanguage + 1], WS_CHILD | WS_VISIBLE, CPoint(870, 705), c, this, IDC_BUTTONL8); 
    
	DeleteObject(c); 	
}

HBRUSH dlg_ustLimit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
#ifdef POWERLAND
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(RGB(165,198,248));
		return (HBRUSH)GetStockObject(NULL_BRUSH);		
	}
#endif
	return hbr;
}
