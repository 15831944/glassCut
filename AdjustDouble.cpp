// AdjustDouble.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "AdjustDouble.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdjustDouble dialog


CAdjustDouble::CAdjustDouble(CWnd* pParent /*=NULL*/)
	: CDialog(CAdjustDouble::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdjustDouble)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAdjustDouble::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdjustDouble)
	DDX_Control(pDX, IDOK, m_CbSet);
	DDX_Control(pDX, IDCANCEL, m_CbBack);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_CbStop);
	DDX_Control(pDX, IDC_BUTTON_START, m_CbStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdjustDouble, CDialog)
	//{{AFX_MSG_MAP(CAdjustDouble)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdjustDouble message handlers

BOOL CAdjustDouble::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	GetDlgItem(IDC_STATIC_TPX1)->SetFont(&g_fontRP);
	GetDlgItem(IDC_STATIC_TPX2)->SetFont(&g_fontRP);	
	GetDlgItem(IDC_STATIC_X1)->SetFont(&g_fontRP);
	GetDlgItem(IDC_STATIC_X2)->SetFont(&g_fontRP);
	AdjustInitGalil();
	SetTimer(1,160,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//得到两门轴的tp值
void CAdjustDouble::GetDoubleTP()
{
	char szResponse[30]={0};
	int nPos;
	long x_pos,y_pos;
	CString strRes;
//	g_Controller.Command("RPXW",szResponse,sizeof(szResponse));//开环
	g_Controller.Command("IP?,,,?",szResponse,sizeof(szResponse));//闭环
	x_pos = (long)atoi(szResponse);
	strRes.Format("%s",szResponse);
	nPos = strRes.Find(',');			
	if( nPos != -1)
	{
		strRes = strRes.Mid(nPos+1);
		y_pos = (long)atoi(strRes);
	}
	strRes.Format("%d",x_pos);
	SetDlgItemText(IDC_STATIC_TPX1,strRes);
	strRes.Format("%d",y_pos);
	SetDlgItemText(IDC_STATIC_TPX2,strRes);
}

void CAdjustDouble::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	g_Controller.Command("XQ#ADJUST");
}

//初始化校正用的速度，加速度，程序下载
void CAdjustDouble::AdjustInitGalil()
{	
	CString     filename=g_strOriginalPathC+"Temp.dmc";    
	Secret("C:\\WINDOWS\\system32\\focusA.dll",filename);    
	char szPath[80];
	sprintf(szPath,filename);
	g_lRc = g_Controller.Command("ST");
	g_Controller.DownloadFile(szPath);
	Sleep(40);
	g_lRc = g_Controller.Command("ST");
	::DeleteFile(filename); 	
	g_handdll.handSpeedACSet(g_stu_pAxisA->d_acc, g_stu_pAxisB->d_acc, g_stu_pAxisC->d_acc, g_stu_pAxisD->d_acc); 
	g_handdll.handSpeedDCSet(g_stu_pAxisA->d_dec, g_stu_pAxisB->d_dec, g_stu_pAxisC->d_dec, g_stu_pAxisD->d_dec); 	
	g_handdll.zoneSpeedSet(g_stu_pAxisA->d_zerospeed,g_stu_pAxisB->d_zerospeed,g_stu_pAxisC->d_zerospeed,g_stu_pAxisD->d_zerospeed);
}

void CAdjustDouble::OnTimer(UINT nIDEvent) 
{
	GetDoubleTP();
	CDialog::OnTimer(nIDEvent);
}

void CAdjustDouble::OnButtonStop() 
{
	g_Controller.Command("ST");	
}

void CAdjustDouble::OnOK() 
{
	CString strCheck;
	char szRes[80];	
	g_Controller.Command("MG_IPW",szRes,sizeof(szRes));	
	strCheck.Format("%d",atoi(szRes));
	WritePrivateProfileString("ADJUST","TPWVALUE",strCheck,INIFILE_ADDEXTRA);
    strCheck.Format("M1=%d",atoi(szRes));
	g_Controller.Command(strCheck.GetBuffer(0));
}

void CAdjustDouble::OnCancel() 
{
	// TODO: Add extra cleanup here	
	CDialog::OnCancel();
}
