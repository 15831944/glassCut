// Dlg_NestNum.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_NestNum.h"
#include "Dlg_KeyNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_NestNum dialog


CDlg_NestNum::CDlg_NestNum(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_NestNum::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_NestNum)
	m_nSetNum = 1;
	//}}AFX_DATA_INIT
}


void CDlg_NestNum::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_NestNum)
	DDX_Control(pDX, IDC_STATIC1, m_stcNum);
	DDX_Text(pDX, IDC_EDIT_NUM, m_nSetNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_NestNum, CDialog)
	//{{AFX_MSG_MAP(CDlg_NestNum)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_NestNum message handlers

void CDlg_NestNum::OnButtonOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nNum = m_nSetNum;
	sqrm[kind]=m_nSetNum;
	kind = kind+1;
	
	if( m_nSetNum <= 0 )
	{
		MessageBox("添加个数不能小于0!","Error",MB_OK|MB_ICONWARNING);
		return ;
	}
	CDialog::OnOK();
}

void CDlg_NestNum::OnButtonCancel() 
{
	CDialog::OnCancel();
}

BOOL CDlg_NestNum::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_pEdit[0].SubclassDlgItem(IDC_EDIT_NUM, this);
	if( g_iLanguage == 1)
	{
		SetDlgItemText(IDC_STATIC1,"Parts number");
		SetDlgItemText(IDC_BUTTON_OK, "OK");
		SetDlgItemText(IDC_BUTTON_CANCEL, "Cancel");
	}
	
	m_clrButton[0].SubclassDlgItem(IDC_BUTTON_OK, this);
	m_clrButton[1].SubclassDlgItem(IDC_BUTTON_CANCEL, this);
	m_clrButton[0].SetFont(&g_fontButton);
	m_clrButton[1].SetFont(&g_fontButton);
	m_stcNum.SetFont(&g_fontStatic);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

int CDlg_NestNum::GetNum()
{	
	return m_nNum;
}

void CDlg_NestNum::OnOK()
{
	OnButtonOk();
}

void CDlg_NestNum::OnCancel()
{
	OnButtonCancel();
}

LRESULT CDlg_NestNum::OnEditDouble(WPARAM wParam, LPARAM lParam)
{
	CString			strTmp;
	CDlg_KeyNumber	KeyNum;
	
	if(lParam==1)/* 有触摸屏 */
	{
		((CEdit *)GetDlgItem(wParam))->SetSel(0,-1);
		return 0;
	}
	
	GetDlgItemText(wParam,strTmp);
	KeyNum.m_strNew = KeyNum.m_strOld = strTmp;
	switch(wParam) 
	{
	case IDC_EDIT1:		
		GetDlgItemText(IDC_STATIC1,KeyNum.m_strTitle);
		break;
	default:
		break;
	}
	if(KeyNum.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	return 0;
}
