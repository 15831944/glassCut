// SetXY.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "SetXY.h"
#include "Dlg_KeyNumber.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetXY dialog


CSetXY::CSetXY(CWnd* pParent /*=NULL*/)
	: CDialog(CSetXY::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetXY)
	m_dX = 0.0;
	m_dY = 0.0;
	//}}AFX_DATA_INIT
}


void CSetXY::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetXY)
	DDX_Control(pDX, IDCANCEL, m_clrBCancel);
	DDX_Control(pDX, IDOK, m_clrBOk);
	DDX_Control(pDX, IDC_EDIT_Y, m_editY);
	DDX_Control(pDX, IDC_EDIT_X, m_editX);
	DDX_Text(pDX, IDC_EDIT_X, m_dX);
	DDX_Text(pDX, IDC_EDIT_Y, m_dY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetXY, CDialog)
	//{{AFX_MSG_MAP(CSetXY)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetXY message handlers

void CSetXY::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CSetXY::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

LRESULT CSetXY::OnEditDouble(WPARAM wParam, LPARAM lParam) 
{
	CString				strTmp;
	CDlg_KeyNumber		KeyNum;
	
	if(lParam==1)/* ÓÐ´¥ÃþÆÁ */
	{
		((CEdit *)GetDlgItem(wParam))->SetSel(0,-1);
		return 0;
	}
	
	CWnd::GetDlgItemText(wParam,strTmp);
	KeyNum.m_strNew = KeyNum.m_strOld = strTmp;
	if(KeyNum.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	
	return 0;
}