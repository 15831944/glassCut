// Dlg_AfxMessage.cpp : implementation file
//

#include "stdafx.h"
#include "Bender.h"
#include "Dlg_AfxMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_AfxMessage dialog


CDlg_AfxMessage::CDlg_AfxMessage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_AfxMessage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_AfxMessage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_AfxMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_AfxMessage)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_AfxMessage, CDialog)
	//{{AFX_MSG_MAP(CDlg_AfxMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_AfxMessage message handlers

void CDlg_AfxMessage::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CDlg_AfxMessage::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CDlg_AfxMessage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CWnd *top;
	top = (CWnd*)GetDlgItem(IDD_DIALOG_AFXMESSAGE);
	CWnd::SetWindowPos(top,170,200,462,202,SWP_SHOWWINDOW);
	// TODO: Add extra initialization here
	CStatic	*pStatic;
	pStatic = (CStatic*)GetDlgItem(IDC_STATIC_AFX);
	pStatic->SetFont(&g_fontStatic);
	CWnd::SetDlgItemText(IDC_STATIC_AFX,strAfxMessage);
	CWnd::SetDlgItemText(IDC_CAPTIONINFOCTRL1,strAfxTitle);
	GetDlgItem(IDOK)->SetFont(&g_fontStatic);
	GetDlgItem(IDCANCEL)->SetFont(&g_fontStatic);
	CWnd::SetDlgItemText(IDOK,strAfxYES);
	CWnd::SetDlgItemText(IDCANCEL,strAfxNO);
	if(!bYesNo)
	{
		CButton  *pbtn;
		pbtn = (CButton*)GetDlgItem(IDCANCEL);
		pbtn->ShowWindow(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

