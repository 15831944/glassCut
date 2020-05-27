// dlg_pass.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "dlg_pass.h"
#include "Dlg_KeyChar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dlg_pass dialog


dlg_pass::dlg_pass(CWnd* pParent /*=NULL*/)
	: CDialog(dlg_pass::IDD, pParent)
{
    m_greenbrush.CreateSolidBrush(RGB(0,255,0));//绿色
    m_yollowbrush.CreateSolidBrush(RGB(212,208,200));//标准灰色
    m_redbrush.CreateSolidBrush(RGB(255,0,0));//红色
    m_bluebrush.CreateSolidBrush(RGB(0,0,255));//兰色
	//{{AFX_DATA_INIT(dlg_pass)
	//}}AFX_DATA_INIT
}
dlg_pass::~dlg_pass()
{
	m_greenbrush.DeleteObject();
	m_yollowbrush.DeleteObject();
	m_redbrush.DeleteObject();
	m_bluebrush.DeleteObject();	
}


void dlg_pass::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dlg_pass)
	DDX_Control(pDX, IDC_EDIT_PASS, m_edtPass);
	DDX_Control(pDX, IDC_BUTTON6, m_ok);
	DDX_Control(pDX, IDC_BUTTON7, m_can);
	DDX_Control(pDX, IDC_BUTTON8, m_can2);
	DDX_Control(pDX, IDC_DEMO10CTRL1, m_demo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dlg_pass, CDialog)
	//{{AFX_MSG_MAP(dlg_pass)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dlg_pass message handlers
HBRUSH dlg_pass::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (nCtlColor==CTLCOLOR_DLG||nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0,128,128));//色
		pDC->SetBkColor(RGB(212,208,200));//黄色
		return (HBRUSH)m_yollowbrush.GetSafeHandle();
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
BOOL dlg_pass::OnInitDialog() 
{
	CDialog::OnInitDialog();
    OnReSetCtl();
    OnLanguage();
	
	m_can2.SetColour(g_crFontD);   
	m_can.SetColour(g_crFontD);   
	m_ok.SetColour(g_crFontA);       

	HasReadValue(strPass0,USER_SECRET1);

	HasReadValue(strPass1,USER_SECRET2);

	HasReadValue(strPass2,USER_SECRET3);


//*************************************************************************************************	
	CEdit *p_edtPass;
	p_edtPass = (CEdit*)GetDlgItem(IDC_EDIT_PASS);
	p_edtPass->SetFont(&g_fontEdit);
	if(g_iPassgrade==0)
	{
		m_ok.EnableWindow(TRUE);
		m_can.EnableWindow(FALSE);
        p_edtPass->EnableWindow(TRUE);
	}
	else
	{
		m_ok.EnableWindow(FALSE);
		m_can.EnableWindow(TRUE);
        p_edtPass->EnableWindow(FALSE);
	}
//*************************************************************************************************	
	p_edtPass->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void dlg_pass::OnButton6() 
{
	// TODO: Add extra validation here
	//测试
//   	g_iPassgrade = 1;
//   	CDialog::OnOK();
//   	return;
	//测试

	if(HasReadValue(strPass0,USER_SECRET1)==0)
		return;
	CEdit *p_edtPass;
	p_edtPass = (CEdit*)GetDlgItem(IDC_EDIT_PASS);
	CString   strPass;

	CWnd::GetDlgItemText(IDC_EDIT_PASS,strPass);
	char ch[15],*p0,p1[15],p2[15];
	strcpy(ch,LPCTSTR(strPass));
	p0 = strPass0.GetBuffer(0);
	strcpy(p1,LPCTSTR(strPass1));
	strcpy(p2,LPCTSTR(strPass2));
    if(g_iPassgrade==0)
	{
	    if(strcmp( p0, ch) == 0)
		{
            g_iPassgrade = 1;//权限级别
    		m_ok.EnableWindow(FALSE);
    		m_can.EnableWindow(TRUE);
            p_edtPass->EnableWindow(FALSE);
			CDialog::OnOK();
		}
    	else if(strcmp( p1, ch)==0)
		{
            g_iPassgrade = 2;//权限级别
    		m_ok.EnableWindow(FALSE);
    		m_can.EnableWindow(TRUE);
            p_edtPass->EnableWindow(FALSE);
			CDialog::OnOK();
		}
	    else if(strcmp( p2, ch)==0)
		{
            g_iPassgrade = 3;//权限级别
    		m_ok.EnableWindow(FALSE);
    		m_can.EnableWindow(TRUE);
            p_edtPass->EnableWindow(FALSE);
			CDialog::OnOK();
		}
	    else
		{
        	CWnd::SetDlgItemText(IDC_EDIT_PASS,"");
			OnShowMessageBox(31, g_iLanguage, TRUE);
		}
	}
	else
	{
		OnShowMessageBox(32, g_iLanguage, TRUE);
	}
	p_edtPass->SetFocus();
}

void dlg_pass::OnButton7() 
{
	// TODO: Add extra cleanup here
	CEdit *p_edtPass;
	p_edtPass = (CEdit*)GetDlgItem(IDC_EDIT_PASS);
	if(g_iPassgrade!=0)
	{
        g_iPassgrade = 0;//权限级别
		m_ok.EnableWindow(TRUE);
		m_can.EnableWindow(FALSE);
        p_edtPass->EnableWindow(TRUE);
		p_edtPass->SetWindowText("");
		OnShowMessageBox(33, g_iLanguage, TRUE);
	}
	p_edtPass->SetFocus();
}

void dlg_pass::OnButton8() 
{
	CDialog::OnCancel();
}

BOOL dlg_pass::PreTranslateMessage(MSG* pMsg) 
{
 	if(pMsg->lParam==VK_TAB||pMsg->wParam==VK_TAB)
		return TRUE;
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
	{
		OnButton6();
		return TRUE;
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

void dlg_pass::OnLanguage()
{
	int   i;
	int		nIndex;
	nIndex = g_iLanguage + 1;
	for(i=0;i<AR_PASS;i++)
	{
		if(g_arr_strPass[i][nIndex]=="NULL")		g_arr_strPass[i][nIndex] = "";
		SetDlgItemText(atoi(g_arr_strPass[i][0]),g_arr_strPass[i][nIndex]);
	}
}

void dlg_pass::OnReSetCtl()
{
	GetDlgItem(IDC_STATIC1)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_EDIT_PASS)->SetFont(&g_fontEdit);
	GetDlgItem(IDC_BUTTON6)->SetFont(&g_fontButton);
	GetDlgItem(IDC_BUTTON7)->SetFont(&g_fontButton);
	GetDlgItem(IDC_BUTTON8)->SetFont(&g_fontButton);
	CenterWindow();	
}

LRESULT dlg_pass::OnEditDouble(WPARAM wParam, LPARAM lParam) 
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
	KeyChar.m_bIsPsw = TRUE;
	switch(wParam) 
	{
	case IDC_EDIT_PASS:		GetDlgItemText(IDC_STATIC1,KeyChar.m_strTitle);			break;
	default:
		break;
	}
	if(KeyChar.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyChar.m_strNew);
	
	return 0;
}
