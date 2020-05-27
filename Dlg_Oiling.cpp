// Dlg_Oiling.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_Oiling.h"
#include "Dlg_KeyNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Oiling dialog


CDlg_Oiling::CDlg_Oiling(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Oiling::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Oiling)
	m_dOilClose = g_stu_pAxisH->dSpareE; 
	m_dOilOpen = g_stu_pAxisG->dSpareE;
	m_bModeOil = g_stu_pAxisH->bSpareE;
	//}}AFX_DATA_INIT
	m_brush.CreateSolidBrush(RGB(165,198,248));
}

CDlg_Oiling::~CDlg_Oiling()
{
	if (m_brush.GetSafeHandle())
	{
		m_brush.DeleteObject();
	}
}

void CDlg_Oiling::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Oiling)
	DDX_Control(pDX, IDC_EDIT_OILOPEN, m_edtOilOpen);
	DDX_Control(pDX, IDC_EDIT_OILCLOSE, m_edtOilClose);
	DDX_Text(pDX, IDC_EDIT_OILCLOSE, m_dOilClose);
	DDX_Text(pDX, IDC_EDIT_OILOPEN, m_dOilOpen); 
	DDX_Radio(pDX, IDC_RADIO_COAL, m_bModeOil);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Oiling, CDialog)
	//{{AFX_MSG_MAP(CDlg_Oiling)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	ON_MESSAGE(WM_OILING,OnOiling)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_Oiling message handlers

BOOL CDlg_Oiling::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetCtlFont(this);
	OnLanguage();
	
	SetWindowPos(&CWnd::wndTopMost,394,306,575,340,SWP_SHOWWINDOW);
	
	m_edtOilOpen.SetFont(&g_fontEdit);
	m_edtOilClose.SetFont(&g_fontEdit);
	// TODO: Add extra initialization here

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_Oiling::OnButton7() 
{
	UpdateData(TRUE);
	g_stu_pAxisG->dSpareE = m_dOilOpen;
	g_stu_pAxisH->dSpareE = m_dOilClose;
	g_stu_pAxisH->bSpareE = m_bModeOil;
	g_machinedll.ParameterSave((char*)((const char*)(g_strOriginalPathD + "machine.ini")));/* 保存机械参数信息 */
	GetParent()->SendMessage(WM_OILING, 0, 6);
	CDialog::DestroyWindow();
}

void CDlg_Oiling::OnButton8() 
{
	GetParent()->SendMessage(WM_OILING, 0, 6);
	CDialog::DestroyWindow();
}

LRESULT CDlg_Oiling::OnEditDouble(WPARAM wParam, LPARAM lParam) 
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
	switch(wParam) 
	{
	case IDC_EDIT_OILOPEN:				GetDlgItemText(IDC_STATIC1,KeyNum.m_strTitle);		break;
	case IDC_EDIT_OILCLOSE:				GetDlgItemText(IDC_STATIC2,KeyNum.m_strTitle);		break;
	default:
		break;
	}
	if(KeyNum.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	
	return 0;
}

LRESULT CDlg_Oiling::OnOiling(WPARAM wParam, LPARAM lParam) 
{
	if(lParam==1)
		OnButton7();
	else if(lParam==2)
		OnButton8();
	return 0;
}

void CDlg_Oiling::OnLanguage()
{
	for(int i=0;i<AR_OILING;i++)
		SetDlgItemText(atoi(g_strOiling[i][2]),g_strOiling[i][g_iLanguage]);
	
	if (1 == g_iLanguage)
	{
		GetDlgItem(IDC_STATIC_OilMode)->SetWindowText("Oil Mode");
		GetDlgItem(IDC_RADIO_COAL)->SetWindowText("Oil A");
		GetDlgItem(IDC_RADIO_CUTOIL)->SetWindowText("Oil B");
	}
}

BOOL CDlg_Oiling::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->lParam==VK_ESCAPE||pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
		return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}


HBRUSH CDlg_Oiling::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
#ifdef POWERLAND
	if (nCtlColor==CTLCOLOR_DLG||nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)m_brush.GetSafeHandle();		
	}
#endif
	return hbr;
}
