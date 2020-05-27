// dlg_super.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "dlg_super.h"
#include "Dlg_KeyChar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dlg_super dialog


dlg_super::dlg_super(CWnd* pParent /*=NULL*/)
	: CDialog(dlg_super::IDD, pParent)
{
	//{{AFX_DATA_INIT(dlg_super)
	//}}AFX_DATA_INIT
}


void dlg_super::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dlg_super)
	DDX_Control(pDX, IDC_STATIC_3, m_s3);
	DDX_Control(pDX, IDC_STATIC_2, m_s2);
	DDX_Control(pDX, IDC_STATIC_1, m_s1);
	DDX_Control(pDX, IDC_EDIT6, m_e6);
	DDX_Control(pDX, IDC_EDIT5, m_e5);
	DDX_Control(pDX, IDC_EDIT4, m_e4);
	DDX_Control(pDX, IDC_EDIT3, m_e3);
	DDX_Control(pDX, IDC_EDIT2, m_e2);
	DDX_Control(pDX, IDC_EDIT1, m_e1);
	DDX_Control(pDX, IDC_DEMO10CTRL1, m_demo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dlg_super, CDialog)
	//{{AFX_MSG_MAP(dlg_super)
	ON_BN_CLICKED(IDC_BUTTONS7, OnButtons7)
	ON_BN_CLICKED(IDC_BUTTONS8, OnButtons8)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dlg_super message handlers
BOOL dlg_super::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if(!g_iLanguage)     SetWindowText("修改密码");
	else                 SetWindowText("Modify password");	

	HasReadValue(pass0,USER_SECRET1);
	HasReadValue(pass1,USER_SECRET2);
	HasReadValue(pass2,USER_SECRET3);

	CWnd::SetDlgItemText(IDC_STATIC_1,pass0);
	CWnd::SetDlgItemText(IDC_STATIC_2,pass1);
	CWnd::SetDlgItemText(IDC_STATIC_3,pass2);
	CWnd::SetDlgItemText(IDC_EDIT5,pass0);
	CWnd::SetDlgItemText(IDC_EDIT1,pass1);
	CWnd::SetDlgItemText(IDC_EDIT3,pass2);

//****************************************************************	
	if(g_iPassgrade==2)
	{
		m_e3.EnableWindow(FALSE);
		m_e4.EnableWindow(FALSE);
		m_e5.EnableWindow(FALSE);
		m_e6.EnableWindow(FALSE);
		m_s1.SetWindowText("********");
		m_s3.SetWindowText("********");
	}
	else if(g_iPassgrade==3)
	{
		m_e1.EnableWindow(FALSE);
		m_e2.EnableWindow(FALSE);
		m_e5.EnableWindow(FALSE);
		m_e6.EnableWindow(FALSE);
		m_s1.SetWindowText("********");
		m_s2.SetWindowText("********");
	}
    OnLanguage();
	InitButton();
	SetWindowPos(&CWnd::wndTop,0,0,1024,768,SWP_SHOWWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL dlg_super::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
		return TRUE;	
	return CDialog::PreTranslateMessage(pMsg);
}

void dlg_super::OnLanguage()
{
	int   i;
	int		nIndex;
	nIndex = g_iLanguage + 1;
	for(i=0;i<AR_SUPER;i++)
	{
		if(g_arr_strSuper[i][nIndex]=="NULL")		g_arr_strSuper[i][nIndex] = "";
		SetDlgItemText(atoi(g_arr_strSuper[i][0]),g_arr_strSuper[i][nIndex]);
	}
}

void dlg_super::OnButtons7() 
{
	if (g_iLanguage == 0)
	{
		if(AfxMessageBox("是否修改密码?",MB_YESNO) != IDYES)
			return;
	}
	else
	{
		if(AfxMessageBox("Will you amend password?",MB_YESNO) != IDYES)
			return;
	}
	CEdit *m_membera0,*m_membera1,*m_memberb0,*m_memberb1,*m_memberc0,*m_memberc1;
	CString s_membera0,s_membera1,s_memberb0,s_memberb1,s_memberc0,s_memberc1;
	m_membera0 = (CEdit*)GetDlgItem(IDC_EDIT1);
	m_membera1 = (CEdit*)GetDlgItem(IDC_EDIT2);
	m_memberb0 = (CEdit*)GetDlgItem(IDC_EDIT3);
	m_memberb1 = (CEdit*)GetDlgItem(IDC_EDIT4);
	m_memberc0 = (CEdit*)GetDlgItem(IDC_EDIT5);
	m_memberc1 = (CEdit*)GetDlgItem(IDC_EDIT6);
	m_membera0->GetWindowText(s_membera0);
	m_membera1->GetWindowText(s_membera1);
	m_memberb0->GetWindowText(s_memberb0);
	m_memberb1->GetWindowText(s_memberb1);
	m_memberc0->GetWindowText(s_memberc0);
	m_memberc1->GetWindowText(s_memberc1);
	if(s_membera0==s_membera1)
	{
		HasWriteValue(s_membera1,USER_SECRET2);
	}
	else
	{
		if (g_iLanguage == 0)
		{
			MessageBox("管理员1密码设定不一致");
		}
		else
		{
			MessageBox("Password 1 is error");
		}

	}
	if(s_memberb0==s_memberb1)
	{
		HasWriteValue(s_memberb1,USER_SECRET3);
	}
	else
	{
		if (g_iLanguage == 0)
		{
			MessageBox("管理员2密码设定不一致");
		}
		else
		{
			MessageBox("Password 2 is error");
		}
	}
	if(s_memberc0==s_memberc1)
	{
		HasWriteValue(s_memberc1,USER_SECRET1);
	}
	else
	{
		if (g_iLanguage == 0)
		{
			MessageBox("超级管理员密码设定不一致");
		}
		else
		{
			MessageBox("Administrator is error");
		}

	}
    g_iPassgrade = 0;
	CDialog::OnOK();
}

void dlg_super::OnButtons8() 
{
    g_iPassgrade = 0;
	CDialog::OnCancel();
}

LRESULT dlg_super::OnEditDouble(WPARAM wParam, LPARAM lParam) 
{
	CString				strTmp;
	CDlg_KeyChar		KeyChar;
	
	if(lParam==1)/* 有触摸屏 */
	{
		((CEdit *)GetDlgItem(wParam))->SetSel(0,-1);
		return 0;
	}
	
	CWnd::GetDlgItemText(wParam,strTmp);
	KeyChar.m_strNew = KeyChar.m_strOld = strTmp;
	switch(wParam) 
	{
	case IDC_EDIT1:				KeyChar.m_strTitle = "管理员1  新密码";				break;
	case IDC_EDIT2:				KeyChar.m_strTitle = "管理员1  重复";				break;
	case IDC_EDIT3:				KeyChar.m_strTitle = "管理员2  新密码";				break;
	case IDC_EDIT4:		    	KeyChar.m_strTitle = "管理员2  重复";				break;
	case IDC_EDIT5:				KeyChar.m_strTitle = "超级管理员  新密码";			break;
	case IDC_EDIT6:				KeyChar.m_strTitle = "超级管理员  重复";			break;
	default:
		break;
	}
	if(KeyChar.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyChar.m_strNew);
	
	return 0;
}

void dlg_super::OnPaint() 
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

void dlg_super::InitButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_ZEOR1);
	//保存
	m_pButton[0].SetFont(&g_fontEdit);
	m_pButton[0].SetBitMapID(IDB_BITMAP_SAVE1,IDB_BITMAP_SAVE2);	
	m_pButton[0].Create(g_arr_strSuper[12][g_iLanguage + 1], WS_CHILD | WS_VISIBLE, CPoint(700, 705), c, this, IDC_BUTTONS7); 
	
	//返回	
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[1].Create(g_arr_strSuper[13][g_iLanguage + 1], WS_CHILD | WS_VISIBLE, CPoint(870, 705), c, this, IDC_BUTTONS8); 
    
	DeleteObject(c); 	
}

HBRUSH dlg_super::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
