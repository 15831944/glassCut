// Dlg_Loading.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_Loading.h"
#include "Dlg_KeyNumber.h"
#include "benderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Loading dialog


CDlg_Loading::CDlg_Loading(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Loading::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Loading)
	m_nWaitX = g_stu_pAxisA->lSpareA;
	m_nWaitY = g_stu_pAxisB->lSpareA;
	m_nTimeDelay = g_stu_pAxisF->dSpareE;
	m_nLeaveTime = GetPrivateProfileInt("WATER","LEAVETIME",0,INIFILE_ADDEXTRA);
	m_lLabelWT = GetPrivateProfileInt("PRINT","LABELTIME",2000,INIFILE_ADDEXTRA);
	m_unUpWT = GetPrivateProfileInt("WATER","UPTIME",0,INIFILE_ADDEXTRA);
	m_nReadyTime = GetPrivateProfileInt("TURNOVER","READYTIME",0,INIFILE_ADDEXTRA);
	//}}AFX_DATA_INIT
	m_brush.CreateSolidBrush(RGB(165,198,248));
}
 
CDlg_Loading::~CDlg_Loading()
{
	if (m_brush.GetSafeHandle())
	{
		m_brush.DeleteObject();
	}
}

void CDlg_Loading::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Loading)
	DDX_Control(pDX, IDC_EDIT3, m_editReady);
	DDX_Control(pDX, IDC_EDIT_UPTIME, m_editUpWT);
	DDX_Control(pDX, IDC_EDIT_LABELWT, m_editLabel);
	DDX_Control(pDX, IDC_EDIT_DelayTime2, m_edtLeaveTime);
	DDX_Control(pDX, IDC_EDIT_DelayTime, m_edtDelayTime);
	DDX_Control(pDX, IDC_EDIT_WAITY, m_edtWaitY);
	DDX_Control(pDX, IDC_EDIT_WAITX, m_edtWaitX);
	DDX_Text(pDX, IDC_EDIT_WAITX, m_nWaitX);
	DDX_Text(pDX, IDC_EDIT_WAITY, m_nWaitY);
	DDX_Text(pDX, IDC_EDIT_DelayTime, m_nTimeDelay);
	DDX_Text(pDX, IDC_EDIT_DelayTime2, m_nLeaveTime);
	DDX_Text(pDX, IDC_EDIT_LABELWT, m_lLabelWT);
	DDX_Text(pDX, IDC_EDIT_UPTIME, m_unUpWT);
	DDX_Text(pDX, IDC_EDIT3, m_nReadyTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Loading, CDialog)
	//{{AFX_MSG_MAP(CDlg_Loading)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_MESSAGE(WM_LOADING,OnLoading)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_Loading message handlers

BOOL CDlg_Loading::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetCtlFont(this);	
	OnLanguage();
	SetWindowPos(&CWnd::wndTopMost,394,306,575,340,SWP_SHOWWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_Loading::OnButton7() 
{
	char szCmdx[80];
	CString stemp;
	UpdateData(TRUE);
	g_stu_pAxisA->lSpareA = m_nWaitX;
	g_stu_pAxisB->lSpareA = m_nWaitY;
	g_stu_pAxisF->dSpareE = m_nTimeDelay;
	g_machinedll.ParameterSave((char*)((const char*)(g_strOriginalPathD + "machine.ini")));/* 保存机械参数信息 */
	//上片延时.下片延时
	CString str;
	str.Format("%d",m_nLeaveTime);
	WritePrivateProfileString("WATER","LEAVETIME",str,INIFILE_ADDEXTRA);
	//流水切割传送带上升的时间，然后开始传送
	str.Format("%d",m_unUpWT);
	WritePrivateProfileString("WATER","UPTIME",str,INIFILE_ADDEXTRA);

	stemp.Format("detime=%.0f;leavet=%d;uptime==%d",m_nTimeDelay,m_nLeaveTime,m_unUpWT);
   	strcpy(szCmdx, LPCTSTR(stemp));
	g_Controller.Command(szCmdx); 

    //贴标签延时时间
	str.Format("%d",m_lLabelWT);
	WritePrivateProfileString("PRINT","LABELTIME",str,INIFILE_ADDEXTRA);
    g_Dmcgc.SetLabelTime((int)m_lLabelWT);
	GetParent()->SendMessage(WM_LOADING, 0, 6);
    //上片台准备时间
	CString strText;
	strText.Format("%d",(int)m_nReadyTime);
	WritePrivateProfileString("TURNOVER","READYTIME",strText,INIFILE_ADDEXTRA);
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)AfxGetMainWnd();
    if(pDlg != NULL)
	{
		pDlg->m_iReadyTime = m_nReadyTime;
	}

	CDialog::DestroyWindow();
}

void CDlg_Loading::OnButton8()
{
	GetParent()->SendMessage(WM_LOADING, 0, 6);
	CDialog::DestroyWindow();
}

LRESULT CDlg_Loading::OnLoading(WPARAM wParam, LPARAM lParam) 
{
	if(lParam==1)
		OnButton7();
	else if(lParam==2)
		OnButton8();
	return 0;
}

void CDlg_Loading::OnLanguage()
{
	for(int i=0;i<AR_LOADING;i++)
		SetDlgItemText(atoi(g_strLoading[i][2]),g_strLoading[i][g_iLanguage]);

	if (1 == g_iLanguage)
	{
		GetDlgItem(IDC_STATIC_Delay)->SetWindowText("Upper Delay (ms)");		
		GetDlgItem(IDC_STATIC_LeaveDelay)->SetWindowText("Leave Delay (ms)");		
		GetDlgItem(IDC_STATIC_LABELWT)->SetWindowText("Label Delay (ms)");
		GetDlgItem(IDC_EDIT3)->SetWindowText("Ready Times(s)");
	}
}

LRESULT CDlg_Loading::OnEditDouble(WPARAM wParam, LPARAM lParam) 
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
	case IDC_EDIT_WAITX:				GetDlgItemText(IDC_STATIC1,KeyNum.m_strTitle);		break;
	case IDC_EDIT_WAITY:				GetDlgItemText(IDC_STATIC2,KeyNum.m_strTitle);		break;
	case IDC_EDIT_DelayTime:			GetDlgItemText(IDC_STATIC_Delay,KeyNum.m_strTitle);	break;
	default:
		break;
	}
	if(KeyNum.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	
	return 0;
}

BOOL CDlg_Loading::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->lParam==VK_ESCAPE||pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

HBRUSH CDlg_Loading::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
