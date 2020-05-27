// Dlg_light.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_light.h"
#include "Dlg_KeyNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_light dialog


CDlg_light::CDlg_light(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_light::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_light)
	m_lCoorX1 = g_stu_pAxisA->lSpare;
	m_lCoorX2 = g_stu_pAxisB->lSpare;
	m_lCoorY = g_stu_pAxisC->lSpare;
	m_lCoorY1 = g_stu_pAxisD->lSpare;
	m_lCoorY2 = g_stu_pAxisE->lSpare;
	m_lCoorX = g_stu_pAxisF->lSpare;
	m_lStartX = g_stu_pAxisG->lSpare;
	m_lStartY = g_stu_pAxisH->lSpare;
	m_lSpeedX = g_stu_pAxisA->lSpareE;
	m_lSpeedY = g_stu_pAxisB->lSpareE;
	m_dLightX = g_stu_pAxisA->dSpareE;
	m_dLightY = g_stu_pAxisB->dSpareE;
	m_lACCX = g_stu_pAxisE->d_vacc;
	m_lACCY = g_stu_pAxisF->d_vacc;
	m_lDECX = g_stu_pAxisE->d_vdec;
	m_lDECY = g_stu_pAxisF->d_vdec;
	m_lPosTime = GetPrivateProfileInt("LIGHTPAR","POSTIME",2000,INIFILE_ADDEXTRA);
	//}}AFX_DATA_INIT
	m_brush.CreateSolidBrush(RGB(165,198,248));
}

CDlg_light::~CDlg_light()
{
	if (m_brush.GetSafeHandle())
	{
		m_brush.DeleteObject();
	}
}

void CDlg_light::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_light)
	DDX_Control(pDX, IDC_EDIT_POSTIME, m_editPosTime);
	DDX_Control(pDX, IDC_EDIT_DECY, m_editDECY);
	DDX_Control(pDX, IDC_EDIT_DECX, m_editDECX);
	DDX_Control(pDX, IDC_EDIT_ACCY, m_editACCY);
	DDX_Control(pDX, IDC_EDIT_ACCX, m_editACCX);
	DDX_Control(pDX, IDC_EDIT_LIGHTY, m_edtLightY);
	DDX_Control(pDX, IDC_EDIT_LIGHTX, m_edtLightX);
	DDX_Control(pDX, IDC_EDIT_Y2, m_edtY2);
	DDX_Control(pDX, IDC_EDIT_Y1, m_edtY1);
	DDX_Control(pDX, IDC_EDIT_Y, m_edtY);
	DDX_Control(pDX, IDC_EDIT_X2, m_edtX2);
	DDX_Control(pDX, IDC_EDIT_X1, m_edtX1);
	DDX_Control(pDX, IDC_EDIT_X, m_edtX);
	DDX_Control(pDX, IDC_EDIT_STARTY, m_edtStartY);
	DDX_Control(pDX, IDC_EDIT_STARTX, m_edtStartX);
	DDX_Control(pDX, IDC_EDIT_SPEEDY, m_edtSpeedY);
	DDX_Control(pDX, IDC_EDIT_SPEEDX, m_edtSpeedX);
	DDX_Control(pDX, IDC_BUTTON8, m_btnF8);
	DDX_Control(pDX, IDC_BUTTON7, m_btnF7);
	DDX_Text(pDX, IDC_EDIT_X1, m_lCoorX1);
	DDX_Text(pDX, IDC_EDIT_X2, m_lCoorX2);
	DDX_Text(pDX, IDC_EDIT_Y, m_lCoorY);
	DDX_Text(pDX, IDC_EDIT_Y1, m_lCoorY1);
	DDX_Text(pDX, IDC_EDIT_Y2, m_lCoorY2);
	DDX_Text(pDX, IDC_EDIT_X, m_lCoorX);
	DDX_Text(pDX, IDC_EDIT_STARTX, m_lStartX);
	DDX_Text(pDX, IDC_EDIT_STARTY, m_lStartY);
	DDX_Text(pDX, IDC_EDIT_SPEEDX, m_lSpeedX);
	DDX_Text(pDX, IDC_EDIT_SPEEDY, m_lSpeedY);
	DDX_Text(pDX, IDC_EDIT_LIGHTX, m_dLightX);
	DDX_Text(pDX, IDC_EDIT_LIGHTY, m_dLightY);
	DDX_Text(pDX, IDC_EDIT_ACCX, m_lACCX);
	DDX_Text(pDX, IDC_EDIT_ACCY, m_lACCY);
	DDX_Text(pDX, IDC_EDIT_DECX, m_lDECX);
	DDX_Text(pDX, IDC_EDIT_DECY, m_lDECY);
	DDX_Text(pDX, IDC_EDIT_POSTIME, m_lPosTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_light, CDialog)
	//{{AFX_MSG_MAP(CDlg_light)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_EN_CHANGE(IDC_EDIT_X1, OnChangeEditX1)
	ON_EN_CHANGE(IDC_EDIT_X2, OnChangeEditX2)
	ON_EN_CHANGE(IDC_EDIT_Y, OnChangeEditY)
	ON_EN_CHANGE(IDC_EDIT_Y1, OnChangeEditY1)
	ON_EN_CHANGE(IDC_EDIT_Y2, OnChangeEditY2)
	ON_EN_CHANGE(IDC_EDIT_X, OnChangeEditX)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	ON_MESSAGE(WM_LIGHT,OnLight)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_light message handlers

BOOL CDlg_light::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	CenterWindow();
	SetCtlFont(this);
	OnLanguage();
	CWnd::SetWindowPos(&CWnd::wndTopMost,394,306,575,340,SWP_SHOWWINDOW);
	// TODO: Add extra initialization here
	if (g_stu_pAxisH->sSpare==0)	/* 公制 */
	{
		m_lStartX = g_stu_pAxisG->lSpare;
		m_lStartY = g_stu_pAxisH->lSpare;
		m_dLightX = g_stu_pAxisA->dSpareE;
		m_dLightY = g_stu_pAxisB->dSpareE;
		m_lACCX = (long)g_stu_pAxisE->d_vacc;
		m_lACCY = (long)g_stu_pAxisF->d_vacc;
		m_lDECX = (long)g_stu_pAxisE->d_vdec;
		m_lDECY = (long)g_stu_pAxisF->d_vdec;

	}
	else
	{
		m_lStartX = (long)(g_stu_pAxisG->lSpare * MM_TO_IN);
		m_lStartY = (long)(g_stu_pAxisH->lSpare * MM_TO_IN);
		m_dLightX = SaveNPoint(4, g_stu_pAxisA->dSpareE * MM_TO_IN);
		m_dLightY = SaveNPoint(4, g_stu_pAxisB->dSpareE * MM_TO_IN);
		m_lACCX = (long)(g_stu_pAxisE->d_vacc * MM_TO_IN);
		m_lACCY = (long)(g_stu_pAxisF->d_vacc * MM_TO_IN);
		m_lDECX = (long)(g_stu_pAxisE->d_vdec * MM_TO_IN);
		m_lDECY = (long)(g_stu_pAxisF->d_vdec * MM_TO_IN);

	}
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_light::OnButton7() 
{
	UpdateData(TRUE);
	g_stu_pAxisA->lSpare = m_lCoorX1;
	g_stu_pAxisB->lSpare = m_lCoorX2;
	g_stu_pAxisC->lSpare = m_lCoorY;
	g_stu_pAxisD->lSpare = m_lCoorY1;
	g_stu_pAxisE->lSpare = m_lCoorY2;
	g_stu_pAxisF->lSpare = m_lCoorX;
	if (g_stu_pAxisH->sSpare==0)	/* 公制 */
	{
		g_stu_pAxisG->lSpare = m_lStartX;
		g_stu_pAxisH->lSpare = m_lStartY;
		g_stu_pAxisA->dSpareE = m_dLightX;
		g_stu_pAxisB->dSpareE = m_dLightY;
		g_stu_pAxisA->lSpareE = m_lSpeedX;
		g_stu_pAxisB->lSpareE = m_lSpeedY;
		g_stu_pAxisE->d_vacc = (double)m_lACCX;
		g_stu_pAxisF->d_vacc = (double)m_lACCY;
		g_stu_pAxisE->d_vdec = (double)m_lDECX;
		g_stu_pAxisF->d_vdec = (double)m_lDECY;
	}
	else
	{
		g_stu_pAxisG->lSpare = (long)(m_lStartX * IN_TO_MM);
		g_stu_pAxisH->lSpare = (long)(m_lStartY * IN_TO_MM);
		g_stu_pAxisA->dSpareE = m_dLightX * IN_TO_MM;
		g_stu_pAxisB->dSpareE = m_dLightY * IN_TO_MM;
		g_stu_pAxisA->lSpareE = (long)(m_lSpeedX * IN_TO_MM);
		g_stu_pAxisB->lSpareE = (long)(m_lSpeedY * IN_TO_MM);
		g_stu_pAxisE->d_vacc =  m_lACCX * IN_TO_MM;
		g_stu_pAxisF->d_vacc =  m_lACCY * IN_TO_MM;
		g_stu_pAxisE->d_vdec =  m_lDECX * IN_TO_MM;
		g_stu_pAxisF->d_vdec =  m_lDECY * IN_TO_MM;

	}
	g_machinedll.ParameterSave((char*)((const char*)(g_strOriginalPathD + "machine.ini")));/* 保存机械参数信息 */
	GetParent()->SendMessage(WM_LIGHT, 0, 6);
	SetFindLightSpeed();

	//定位块时间
	CString strText;
	strText.Format("%d",m_lPosTime);
	WritePrivateProfileString("LIGHTPAR","POSTIME",strText,INIFILE_ADDEXTRA);
	char szCmd[80]={0};    
	sprintf(szCmd,"postime=%d",m_lPosTime);
    g_Controller.Command(szCmd);
	CDialog::DestroyWindow();
}

void CDlg_light::OnButton8() 
{
	GetParent()->SendMessage(WM_LIGHT, 0, 6);
	CDialog::DestroyWindow();
}

void CDlg_light::OnChangeEditX1() 
{
	OnChangeEdit(IDC_EDIT_X1);
}

void CDlg_light::OnChangeEditX2() 
{
	OnChangeEdit(IDC_EDIT_X2);
}

void CDlg_light::OnChangeEditY() 
{
	OnChangeEdit(IDC_EDIT_Y);
}

void CDlg_light::OnChangeEdit(int iEdit) 
{
	CString    strTemp;
	int        i,iLengh;
	char       ch;
	CWnd::GetDlgItemText(iEdit,strTemp);
	if(strTemp.IsEmpty())		SetDlgItemText(iEdit,"50");
	if( atoi(strTemp)>100 || atoi(strTemp)<=0 )		SetDlgItemText(iEdit,"50");
	iLengh = strTemp.GetLength();
	for(i=0;i<iLengh;i++)
	{
		ch = strTemp.GetAt(i);
		if(!(isdigit(ch)||ch=='.'))		SetDlgItemText(iEdit,"50");
	}
}

void CDlg_light::OnChangeEditY1() 
{
	OnChangeEdit(IDC_EDIT_Y1);
}

void CDlg_light::OnChangeEditY2() 
{
	OnChangeEdit(IDC_EDIT_Y2);
}

void CDlg_light::OnChangeEditX() 
{
	OnChangeEdit(IDC_EDIT_X);
}

LRESULT CDlg_light::OnEditDouble(WPARAM wParam, LPARAM lParam) 
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
	case IDC_EDIT_X1:			GetDlgItemText(IDC_STATIC5,KeyNum.m_strTitle);	break;
	case IDC_EDIT_X2:			GetDlgItemText(IDC_STATIC6,KeyNum.m_strTitle);	break;
	case IDC_EDIT_Y:			GetDlgItemText(IDC_STATIC7,KeyNum.m_strTitle);	break;
	case IDC_EDIT_Y1:			GetDlgItemText(IDC_STATIC8,KeyNum.m_strTitle);	break;
	case IDC_EDIT_Y2:			GetDlgItemText(IDC_STATIC9,KeyNum.m_strTitle);	break;
	case IDC_EDIT_X:			GetDlgItemText(IDC_STATIC10,KeyNum.m_strTitle);	break;
	case IDC_EDIT_STARTX:		GetDlgItemText(IDC_STATIC11,KeyNum.m_strTitle);	break;
	case IDC_EDIT_STARTY:		GetDlgItemText(IDC_STATIC12,KeyNum.m_strTitle);	break;
	default:
		break;
	}
	if(KeyNum.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	
	return 0;
}

LRESULT CDlg_light::OnLight(WPARAM wParam, LPARAM lParam) 
{
	if(lParam==1)
		OnButton7();
	else if(lParam==2)
		OnButton8();
	
	return 0;
}

void CDlg_light::OnLanguage()
{
	int   i;
	int		nIndex;
	nIndex = g_iLanguage + 1;

	for(i=0;i<AR_LIGHT;i++)
		SetDlgItemText(atoi(g_arr_light[i][0]),g_arr_light[i][nIndex]);
	if(g_iLanguage == 1)
	{
		SetDlgItemText(IDC_STATIC_POSTIME,"POS TIME(ms)");
	}
}

BOOL CDlg_light::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->lParam==VK_ESCAPE||pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

HBRUSH CDlg_light::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
