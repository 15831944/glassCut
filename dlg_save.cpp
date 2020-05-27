// dlg_save.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "dlg_save.h"
#include "Dlg_KeyChar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dlg_save dialog


dlg_save::dlg_save(CWnd* pParent /*=NULL*/)
	: CDialog(dlg_save::IDD, pParent)
{
	//{{AFX_DATA_INIT(dlg_save)
	//}}AFX_DATA_INIT
	strExtName.Empty();
}


void dlg_save::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dlg_save)
	DDX_Control(pDX, IDC_BUTTON8, m_button8);
	DDX_Control(pDX, IDC_BUTTON7, m_button7);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dlg_save, CDialog)
	//{{AFX_MSG_MAP(dlg_save)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dlg_save message handlers

BOOL dlg_save::OnInitDialog() 
{
	CDialog::OnInitDialog();
    OnReSetCtl();	
	m_edit.SetFocus();
	m_button7.SetColour(g_crFontA);
	m_button8.SetColour(g_crFontD);
	OnLanguage();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void dlg_save::OnLanguage()
{
	int   i;
	int		nIndex;
	nIndex = g_iLanguage + 1;

	for(i=0;i<AR_SAVE;i++)
		CWnd::SetDlgItemText(atoi(g_arr_strSave[i][0]),g_arr_strSave[i][nIndex]);
	if (g_iLanguage == 1)
	{
		SetDlgItemText(IDC_STATIC_T,"Please input the name of the file:");
	}
}

void dlg_save::OnButton7() 
{
	CString strTemp;
	CWnd::GetDlgItemText(IDC_EDIT1,strTemp);
	
	if(strTemp=="")
	{
		m_edit.SetFocus();
		return;
	}
	else if(!(strstr(strTemp, strupr((char*)((const char*)strExtName)))||strstr(strTemp, strlwr((char*)((const char*)strExtName)))))
		strTemp = strTemp + strExtName;
	g_strSavefile = strTemp;
	
	CDialog::OnOK();
}

void dlg_save::OnButton8() 
{
	CDialog::OnCancel();
}

void dlg_save::OnReSetCtl()
{
	CRect     rc;
	pWnd[0] = GetDlgItem(IDC_DEMO10CTRL2);
	pWnd[1] = GetDlgItem(IDC_STATIC_T);     pWnd[1]->SetFont(&g_fontStatic);
	pWnd[2] = GetDlgItem(IDC_EDIT1);        pWnd[2]->SetFont(&g_fontEdit);
	pWnd[3] = GetDlgItem(IDC_BUTTON7);      pWnd[3]->SetFont(&g_fontButton);
	pWnd[4] = GetDlgItem(IDC_BUTTON8);      pWnd[4]->SetFont(&g_fontButton);
	
	CWnd::GetClientRect(rc);
    rc = OnReSetRectV(rc);
	CWnd::SetWindowPos(CWnd::GetOwner(),(g_screen.x-rc.right)/2,(g_screen.y-rc.bottom)/2,rc.right,rc.bottom,SWP_SHOWWINDOW);
	for(int i=0;i<5;i++)
	{
		pWnd[i]->GetWindowRect(rc);
        ScreenToClient(rc);
		rc = OnReSetRectV(rc);
		pWnd[i]->MoveWindow(rc.left,rc.top,(rc.right-rc.left),(rc.bottom-rc.top),TRUE);
	}
}

BOOL dlg_save::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->lParam==VK_TAB||pMsg->wParam==VK_TAB)
		return TRUE;
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT dlg_save::OnEditDouble(WPARAM wParam, LPARAM lParam) 
{
	CString				strTmp;
	CDlg_KeyChar		KeyChar;
	
	if(lParam==1)/* ÓÐ´¥ÃþÆÁ */
	{
		((CEdit *)GetDlgItem(wParam))->SetSel(0,-1);
		return 0;
	}
	
	CWnd::GetDlgItemText(wParam,strTmp);
	KeyChar.m_strNew = KeyChar.m_strOld = strTmp;
	switch(wParam) 
	{
	case IDC_EDIT1:		GetDlgItemText(IDC_STATIC_T,KeyChar.m_strTitle);	break;
	default:
		break;
	}
	if(KeyChar.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyChar.m_strNew);
	
	return 0;
}
