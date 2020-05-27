// Dlg_NestSave.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_NestSave.h"
#include "Dlg_KeyChar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_NestSave dialog


CDlg_NestSave::CDlg_NestSave(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_NestSave::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_NestSave)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_NestSave::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_NestSave)
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_NestSave, CDialog)
	//{{AFX_MSG_MAP(CDlg_NestSave)
	ON_BN_CLICKED(IDC_BUTTONF1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTONF2, OnButton2)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_NestSave message handlers

void CDlg_NestSave::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString strTemp;
	CWnd::GetDlgItemText(IDC_EDIT1,strTemp);
	
	if(strTemp=="")
	{
		m_edit.SetFocus();
		return;
	}
	g_strSavefile = strTemp;
	m_fThick = atof(strTemp);
	CDialog::OnOK();
}

void CDlg_NestSave::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();	
}

BOOL CDlg_NestSave::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if( g_iLanguage == 1)
	{
		SetDlgItemText(IDC_BUTTONF1, "OK");
		SetDlgItemText(IDC_BUTTONF2, "Cancel");
	}
	m_clrButton[0].SubclassDlgItem(IDC_BUTTONF1, this);
	m_clrButton[1].SubclassDlgItem(IDC_BUTTONF2, this);
	m_clrButton[0].SetFont(&g_fontButton);
	m_clrButton[1].SetFont(&g_fontButton);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CDlg_NestSave::OnEditDouble(WPARAM wParam, LPARAM lParam) 
{
	CString				strTmp;
	CDlg_KeyChar		KeyNum;
	
	if(lParam==1)/* ÓÐ´¥ÃþÆÁ */
	{
		((CEdit *)GetDlgItem(wParam))->SetSel(0,-1);
		return 0;
	}
	
	CWnd::GetDlgItemText(wParam,strTmp);
	KeyNum.m_strNew = KeyNum.m_strOld = strTmp;
	switch(wParam) 
	{
	case IDC_EDIT1:		
		//GetDlgItemText(IDC_STATIC1,KeyNum.m_strTitle);			
		break;
	default:																							break;
	}
	if(KeyNum.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	
	return 0;
}
