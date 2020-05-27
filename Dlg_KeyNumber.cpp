// Dlg_KeyNumber.cpp : implementation file
//

#include "stdafx.h"
#include "Bender.h"
#include "Dlg_KeyNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_KeyNumber dialog


CDlg_KeyNumber::CDlg_KeyNumber(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_KeyNumber::IDD, pParent)
{
    m_greenbrush.CreateSolidBrush(RGB(0,255,0));//绿色
    m_yollowbrush.CreateSolidBrush(RGB(0,128,128));//标准灰色
    m_redbrush.CreateSolidBrush(RGB(255,0,0));//红色
    m_bluebrush.CreateSolidBrush(RGB(0,0,255));//兰色
	//{{AFX_DATA_INIT(CDlg_KeyNumber)
	m_strNew = _T("");
	m_strOld = _T("");
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
}


void CDlg_KeyNumber::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_KeyNumber)
	DDX_Control(pDX, IDC_BUTTON13, m_btn13);
	DDX_Control(pDX, IDC_BUTTON12, m_btn12);
	DDX_Control(pDX, IDC_BUTTON11, m_btn11);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_btnDel);
	DDX_Control(pDX, IDC_BUTTON_BK, m_btnBK);
	DDX_Control(pDX, IDC_BUTTON_9, m_btn9);
	DDX_Control(pDX, IDC_BUTTON_8, m_btn8);
	DDX_Control(pDX, IDC_BUTTON_7, m_btn7);
	DDX_Control(pDX, IDC_BUTTON_6, m_btn6);
	DDX_Control(pDX, IDC_BUTTON_5, m_btn5);
	DDX_Control(pDX, IDC_BUTTON_4, m_btn4);
	DDX_Control(pDX, IDC_BUTTON_3, m_btn3);
	DDX_Control(pDX, IDC_BUTTON_2, m_btn2);
	DDX_Control(pDX, IDC_BUTTON_1, m_btn1);
	DDX_Control(pDX, IDC_BUTTON_0, m_btn0);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_OK, m_btnOk);
	DDX_Control(pDX, IDC_EDIT_NEW, m_edtNew);
	DDX_Text(pDX, IDC_EDIT_NEW, m_strNew);
	DDX_Text(pDX, IDC_EDIT_OLD, m_strOld);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_KeyNumber, CDialog)
	//{{AFX_MSG_MAP(CDlg_KeyNumber)
	ON_BN_CLICKED(IDC_BUTTON_0, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON_1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON_BK, OnButtonBk)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_KeyNumber message handlers

void CDlg_KeyNumber::OnButton10() 
{
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_CHAR,0X30,0);
}

void CDlg_KeyNumber::OnButton1() 
{
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_CHAR,0X31,0);
}

void CDlg_KeyNumber::OnButton2() 
{
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_CHAR,0X32,0);
}

void CDlg_KeyNumber::OnButton3() 
{
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_CHAR,0X33,0);
}

void CDlg_KeyNumber::OnButton4() 
{
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_CHAR,0X34,0);
}

void CDlg_KeyNumber::OnButton5() 
{
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_CHAR,0X35,0);
}

void CDlg_KeyNumber::OnButton6() 
{
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_CHAR,0X36,0);
}

void CDlg_KeyNumber::OnButton7() 
{
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_CHAR,0X37,0);
}

void CDlg_KeyNumber::OnButton8() 
{
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_CHAR,0X38,0);
}

void CDlg_KeyNumber::OnButton9() 
{
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_CHAR,0X39,0);
}

void CDlg_KeyNumber::OnButtonBk() 
{
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_CHAR,VK_BACK,0);
}

void CDlg_KeyNumber::OnButton12() /* - */
{
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_CHAR,0X2D,0);
}

void CDlg_KeyNumber::OnButtonDel() 
{
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_KEYDOWN,VK_DELETE,0);
}

void CDlg_KeyNumber::OnCancel() 
{
	CDialog::OnCancel();
}

void CDlg_KeyNumber::OnBtnOk() 
{
	CString stemp;
	GetDlgItemText(IDC_EDIT_NEW,stemp);
	CDialog::OnOK();
}

void CDlg_KeyNumber::OnButton11() /* . */
{
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_CHAR,0X2E,0);
}

void CDlg_KeyNumber::OnButton13() /* + */
{
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_CHAR,0X2B,0);
}

void CDlg_KeyNumber::OnButtonFont() /* 改变窗口字体 */
{
	GetDlgItem(IDC_BUTTON_0)->SetFont(&g_fontKey);
	GetDlgItem(IDC_BUTTON_1)->SetFont(&g_fontKey);
	GetDlgItem(IDC_BUTTON_2)->SetFont(&g_fontKey);
	GetDlgItem(IDC_BUTTON_3)->SetFont(&g_fontKey);
	GetDlgItem(IDC_BUTTON_4)->SetFont(&g_fontKey);
	GetDlgItem(IDC_BUTTON_5)->SetFont(&g_fontKey);
	GetDlgItem(IDC_BUTTON_6)->SetFont(&g_fontKey);
	GetDlgItem(IDC_BUTTON_7)->SetFont(&g_fontKey);
	GetDlgItem(IDC_BUTTON_8)->SetFont(&g_fontKey);
	GetDlgItem(IDC_BUTTON_9)->SetFont(&g_fontKey);
	GetDlgItem(IDC_BUTTON11)->SetFont(&g_fontKey);
	GetDlgItem(IDC_BUTTON12)->SetFont(&g_fontKey);
	GetDlgItem(IDC_BUTTON13)->SetFont(&g_fontKey);
	GetDlgItem(IDC_BUTTON_BK)->SetFont(&g_fontButton);
	GetDlgItem(IDC_BUTTON_DEL)->SetFont(&g_fontButton);
	m_btnCancel.SetFont(&g_fontButton);
	m_btnOk.SetFont(&g_fontButton);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_NEW)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_OLD)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_EDIT_NEW)->SetFont(&g_fontEdit);
	GetDlgItem(IDC_EDIT_OLD)->SetFont(&g_fontEdit);
}

BOOL CDlg_KeyNumber::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	OnButtonFont();
	
	CWnd::SetWindowPos(&CWnd::wndTopMost,385,196,260,383,SWP_SHOWWINDOW);
	OnLanguage();	
	m_btn13.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn12.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn11.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnDel.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnBK.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn9.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn8.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn7.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn6.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn5.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn4.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn3.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn2.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn1.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn0.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnCancel.SetColour(RGB(255,0,0),RGB(255,255,0));
	m_btnOk.SetColour(RGB(0,255,0),RGB(255,255,0));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CDlg_KeyNumber::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (nCtlColor==CTLCOLOR_DLG||nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(255,255,128));//色
		pDC->SetBkColor(RGB(0,128,128));//黄色
		return (HBRUSH)m_yollowbrush.GetSafeHandle();
	}
	return hbr;
}

void CDlg_KeyNumber::OnLanguage()
{
	int   i;
	int		nIndex;
	nIndex = g_iLanguage + 1;
	for(i=0;i<AR_CNC;i++)
		CWnd::SetDlgItemText(atoi(g_arr_strCnc[i][0]),g_arr_strCnc[i][nIndex]);
}
