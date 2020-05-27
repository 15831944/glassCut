// Dlg_scan.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_scan.h"
#include "benderDlg.h"
#include "Dlg_KeyNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_scan dialog


CDlg_scan::CDlg_scan(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_scan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_scan)
	//}}AFX_DATA_INIT
}

CDlg_scan::~CDlg_scan()
{

}

void CDlg_scan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_scan)
	DDX_Control(pDX, IDC_EDIT_BEGINX, m_edtBeginX);
	DDX_Control(pDX, IDC_EDIT_BEGINY, m_edtBeginY);
	DDX_Control(pDX, IDC_EDIT_PACE, m_edtScanPace);
	DDX_Control(pDX, IDC_EDIT_CENTERX, m_edtCenterX);
	DDX_Control(pDX, IDC_EDIT_CENTERY, m_edtCenterY);
	DDX_Control(pDX, IDC_EDIT_SPEED, m_edtSpeed);
	DDX_Text(pDX, IDC_EDIT_BEGINX, m_dBeginX);
	DDX_Text(pDX, IDC_EDIT_BEGINY, m_dBeginY);
	DDX_Text(pDX, IDC_EDIT_PACE, m_dScanPace);
	DDX_Control(pDX, IDC_LEDCTRL1, m_ocxLedScan);
	DDX_Text(pDX, IDC_EDIT_CENTERX, m_dCenterX);
	DDX_Text(pDX, IDC_EDIT_CENTERY, m_dCenterY);
	DDX_Text(pDX, IDC_EDIT_SPEED, m_dSpeed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_scan, CDialog)
	//{{AFX_MSG_MAP(CDlg_scan)
	ON_BN_CLICKED(IDC_BUTTON_CS1, OnButtonCs1)
	ON_BN_CLICKED(IDC_BUTTON_CS2, OnButtonCs2)
	ON_BN_CLICKED(IDC_BUTTON_CS3, OnButtonCs3)
	ON_MESSAGE(WM_SCAN, OnScanState)
	ON_BN_CLICKED(IDC_BUTTON_CS4, OnButtonCs4)
	ON_BN_CLICKED(IDC_BUTTON_CS5, OnButtonCs5)
	ON_BN_CLICKED(IDC_BUTTON_CS6, OnButtonCs6)
	ON_BN_CLICKED(IDC_BUTTON_CS7, OnButtonCs7)
	ON_BN_CLICKED(IDC_BUTTON_CS8, OnButtonCs8)
	ON_BN_CLICKED(IDC_BUTTON_CS9, OnButtonCs9)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_scan message handlers

BOOL CDlg_scan::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText("SCAN");
	DWORD crBK = BACKCOLOR;
	m_ocxLedScan.SetBackColor(crBK);
	InitButton();
	OnCutWindow();	   
	InitFontLanguage();
	SetWindowPos(CWnd::GetOwner(),0,0,g_screen.x,g_screen.y,SWP_SHOWWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_scan::OnButtonCs1() 
{
	
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)GetParent(); 
	
	//*************清除已经打开的图形 ******************************
	pDlg->m_PVM.FreeBlocks();
	g_Controller.Command("VS500");
	m_ocxLedScan.SetRgby(2);/* 绿色 */
	if(!pDlg->GetScanRun())
	{
//		MessageBox("run");
		pDlg->ScanRun();
	}
}

void CDlg_scan::OnButtonCs2() 
{
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)GetParent(); 

	if(pDlg->GetScanRun()) //停止运动
	{
		return;
	}
	if (1 == GetServerAlarm())
	{	
		CDlg_AfxMessage  Message;
		Message.bYesNo = FALSE;
		if(g_iLanguage==1)
		{
			Message.strAfxYES ="OK";
			Message.strAfxTitle ="Servor Alm";
			Message.strAfxMessage ="Servor Alm !";
		}
		else
		{
			Message.strAfxYES ="确定";
			Message.strAfxTitle ="伺服报警";
			Message.strAfxMessage ="请全部断电，重新启动设备！";
		} 
		Message.DoModal(); 	
		return;
	}	
	if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1
		||g_handdll.GetCommandFloat((char *)((const char*)"MG_XQ"))>=0.0)	
	{
		OnShowMessageBox(22,g_iLanguage,FALSE);
	}
	else
	{
		char szDmc[80]={0};
		if(g_stu_pAxisF->bSpareA == TRUE)//龙门同步
		{
			CString     filename=g_strOriginalPathC+"Temp.dmc";    
			Secret("C:\\WINDOWS\\system32\\focusC.dll",filename);  //XYZ  
			sprintf(szDmc,filename);				
		}
		else
		{
			strcpy(szDmc,g_strOriginalPathC + "homeall.dmc");
		}
		LONG lRc = 0;
		lRc = g_Controller.DownloadFile(szDmc);
		if (lRc != 0)
		{
			CDlg_AfxMessage  Message;
			Message.bYesNo = FALSE;
			if(g_iLanguage==1)
			{
				Message.strAfxYES ="OK";
				Message.strAfxTitle ="Error";
				Message.strAfxMessage ="Control error !";
			}
			else
			{
				Message.strAfxYES ="确定";
				Message.strAfxTitle ="控制器错误";
				Message.strAfxMessage ="请全部断电，重新启动设备！";
			} 
			Message.DoModal(); 	
			return;
		}
		g_Controller.Command("ST;WT20;XQ#HOME");
	}	
}

void CDlg_scan::OnButtonCs3() 
{
	if (g_handdll.GetCommandFloat("MG_XQ")>=0.0)
	{
		g_Controller.Command("ST");
	}
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)GetParent();
	if(pDlg->GetScanRun())
		pDlg->ScanStop();
}

void CDlg_scan::OnButtonCs4() //PNT 格式
{
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)GetParent();
	if(pDlg->GetScanRun()) //停止运动
		pDlg->ScanStop();
	
	pDlg->ScanSavePos(2);//dxf 格式
}

void CDlg_scan::OnButtonCs5() 
{
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)GetParent();
	if(pDlg->GetScanRun()) //停止运动
		pDlg->ScanStop();
	
	pDlg->ScanSavePos(1);//cid 格式
}

void CDlg_scan::OnButtonCs6() 
{
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)GetParent();
	if(pDlg->GetScanRun()) //停止运动
		pDlg->ScanStop();
	pDlg->ScanSaveGcode();

}

UINT CDlg_scan::OnScanState(WPARAM wParam, LPARAM lParam)
{
	if (0 == g_iLanguage) 
	{
		if(lParam==1)
		{
			m_ocxLedScan.SetRgby(4);/* 黄色 */
			SetDlgItemText(IDC_STATIC_SCAN, "回退");
		}
		else
		{
			m_ocxLedScan.SetRgby(2);/* 绿色 */
			SetDlgItemText(IDC_STATIC_SCAN, "前进");
		}
	}
	else
	{
		if(lParam==1)
		{
			m_ocxLedScan.SetRgby(4);/* 黄色 */
			SetDlgItemText(IDC_STATIC_SCAN, "Backward");
		}
		else
		{
			m_ocxLedScan.SetRgby(2);/* 绿色 */
			SetDlgItemText(IDC_STATIC_SCAN, "Forward");
		}
	}
	
	return 0;
}

void CDlg_scan::OnSaveParameter() 
{
	g_ScanPara.dScanBeginPosX = m_dBeginX;
	g_ScanPara.dScanBeginPosY = m_dBeginY;
	g_ScanPara.dScanPace = m_dScanPace;
	g_ScanPara.dScanCenterPosX = m_dCenterX;
	g_ScanPara.dScanCenterPosY = m_dCenterY;
	g_ScanPara.dScanSpeed = m_dSpeed;	
	CString szStr;
	szStr.Format("%.0f",g_ScanPara.dScanSpeed);
	WritePrivateProfileString("PARA","SCANSPEED",szStr,INIFILE_SCAN);
	szStr.Format("%.0f",g_ScanPara.dScanPace);
	WritePrivateProfileString("PARA","SCANPACE",szStr,INIFILE_SCAN);
	szStr.Format("%.0f",g_ScanPara.dScanBeginPosX);
	WritePrivateProfileString("PARA","SCANBGX",szStr,INIFILE_SCAN);
	szStr.Format("%.0f",g_ScanPara.dScanBeginPosY);
	WritePrivateProfileString("PARA","SCANBGY",szStr,INIFILE_SCAN);
	szStr.Format("%.0f",g_ScanPara.dScanCenterPosX);
	WritePrivateProfileString("PARA","SCANMIDX",szStr,INIFILE_SCAN);
	szStr.Format("%.0f",g_ScanPara.dScanCenterPosY);
	WritePrivateProfileString("PARA","SCANMIDY",szStr,INIFILE_SCAN);
}

void CDlg_scan::OnCutWindow()
{
	CPaintDC dc(this); // device context for painting
	dc.BeginPath();	
	dc.MoveTo(720, 363);
	dc.LineTo(922, 363);	
	dc.LineTo(922, 311);
	dc.LineTo(1024, 311);	
	dc.LineTo(1024, 768);
	dc.LineTo(0, 768); 
	dc.LineTo(0, 708);  
	dc.LineTo(720, 708);  
	dc.LineTo(720, 363);  	
	dc.EndPath();	
	CRgn	rgnWin;
	rgnWin.CreateFromPath(&dc);
	SetWindowRgn((HRGN)rgnWin, TRUE);
	if(rgnWin.m_hObject != NULL)
		rgnWin.DeleteObject();
	DeleteDC(dc);
}

void CDlg_scan::OnButtonCs7() 
{
	UpdateData(TRUE);
	OnSaveParameter();
}

BOOL CDlg_scan::PreTranslateMessage(MSG* pMsg) 
{ 	
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
		return TRUE;
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlg_scan::OnButtonCs10() 
{  
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)GetParent();
	if(pDlg->GetScanRun()) //停止运动
		pDlg->ScanStop();
		//*************清除已经打开的图形 ******************************
	pDlg->m_PVM.FreeBlocks();
	m_pButton[9].SelectState(NULL);	
}

void CDlg_scan::OnButtonCs8() // Cad-Way
{
	ShellExecute(NULL,"open","D:\\Opty-Way\\CadWay.exe",NULL,"D:\\Opty-Way\\",SW_SHOWNORMAL);// Cad-Way
}

void CDlg_scan::OnButtonCs9() // Edit-Way
{
	ShellExecute(NULL,"open","D:\\Opty-Way\\EditWay.exe",NULL,"D:\\Opty-Way\\",SW_SHOWMAXIMIZED);// Cad-Way
}
void CDlg_scan::InitFontLanguage()
{
	if (g_iLanguage) 
	{
		GetDlgItem(IDC_STATIC_SCAN_SPEED)->SetWindowText("Speed");
		GetDlgItem(IDC_STATIC_SCAN_PACE)->SetWindowText("Step Length");
		GetDlgItem(IDC_STATIC_SCAN_BEGINX)->SetWindowText("Start Point X");
		GetDlgItem(IDC_STATIC_SCAN_BEGINY)->SetWindowText("Start Point Y");
		GetDlgItem(IDC_STATIC_SCAN_CENTERX)->SetWindowText("Middle Point X");
		GetDlgItem(IDC_STATIC_SCAN_CENTERY)->SetWindowText("Middle Point Y");
		SetDlgItemText(IDC_STATIC_SCAN, "Advancing");
	}
}


LRESULT CDlg_scan::OnEditDouble(WPARAM wParam, LPARAM lParam) 
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
	case IDC_EDIT_SPEED:		GetDlgItemText(IDC_STATIC_SCAN_SPEED,KeyNum.m_strTitle);		break;
	case IDC_EDIT_PACE:			GetDlgItemText(IDC_STATIC_SCAN_PACE,KeyNum.m_strTitle);			break;
	case IDC_EDIT_BEGINX:		GetDlgItemText(IDC_STATIC_SCAN_BEGINX,KeyNum.m_strTitle);		break;
	case IDC_EDIT_BEGINY:		GetDlgItemText(IDC_STATIC_SCAN_BEGINY,KeyNum.m_strTitle);		break;
	case IDC_EDIT_CENTERX:		GetDlgItemText(IDC_STATIC_SCAN_CENTERX,KeyNum.m_strTitle);		break;
	case IDC_EDIT_CENTERY:		GetDlgItemText(IDC_STATIC_SCAN_CENTERY,KeyNum.m_strTitle);		break;
	default:																				break;
	}
	if(KeyNum.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	
	return 0;
}

void CDlg_scan::InitButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_STOP1);
	CString strLanguage[5][2];
	strLanguage[0][0]="启动";
	strLanguage[1][0]="停止";
	strLanguage[2][0]="保存参数";
	strLanguage[3][0]="返回";
	strLanguage[4][0]="回零";
	strLanguage[0][1]="Start";
	strLanguage[1][1]="Stop";
	strLanguage[2][1]="Save Par";
	strLanguage[3][1]="Back";
	strLanguage[4][1]="Home";
	
	//启动	
	m_pButton[0].SetFont(&g_fontEdit);
	m_pButton[0].SetBitMapID(IDB_BITMAP_STRAT1,IDB_BITMAP_STRAT2);	
	m_pButton[0].Create(strLanguage[0][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(2, 714), c, this, IDC_BUTTON_CS1); 
	//停止	
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_STOP1,IDB_BITMAP_STOP2);	
	m_pButton[1].Create(strLanguage[1][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(127, 714), c, this, IDC_BUTTON_CS3); 
	//DXF 格式	
	m_pButton[2].SetFont(&g_fontEdit);
	m_pButton[2].SetBitMapID(IDB_BITMAP_CSAVE1,IDB_BITMAP_CSAVE2);	
	m_pButton[2].Create("DXF", WS_CHILD | WS_VISIBLE, CPoint(260, 714), c, this, IDC_BUTTON_CS4); 
	//CID 格式	
	m_pButton[3].SetFont(&g_fontEdit);
	m_pButton[3].SetBitMapID(IDB_BITMAP_CSAVE1,IDB_BITMAP_CSAVE2);	
	m_pButton[3].Create("GID", WS_CHILD | WS_VISIBLE, CPoint(385, 714), c, this, IDC_BUTTON_CS5); 
	//G 格式	
	m_pButton[4].SetFont(&g_fontEdit);
	m_pButton[4].SetBitMapID(IDB_BITMAP_CSAVE1,IDB_BITMAP_CSAVE2);	
	m_pButton[4].Create("G CODE", WS_CHILD | WS_VISIBLE, CPoint(510, 714), c, this, IDC_BUTTON_CS6); 
	
// 	//保存参数	
	m_pButton[5].SetFont(&g_fontStatic);
	m_pButton[5].SetBitMapID(IDB_BITMAP_SAVEPAR1,IDB_BITMAP_SAVEPAR2);	
	m_pButton[5].Create(strLanguage[2][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(900, 714), c, this, IDC_BUTTON_CS7); 
	//cadway	
	m_pButton[6].SetBitMapID(IDB_BITMAP_CADWAY1,IDB_BITMAP_CADWAY2);	
	m_pButton[6].Create("", WS_CHILD | WS_VISIBLE, CPoint(643, 714), c, this, IDC_BUTTON_CS8); 
	//editway	
	m_pButton[7].SetBitMapID(IDB_BITMAP_EDITWAY1,IDB_BITMAP_EDITWAY2);	
	m_pButton[7].Create("", WS_CHILD | WS_VISIBLE, CPoint(768, 714), c, this, IDC_BUTTON_CS9); 

// 	//返回	
// 	m_pButton[8].SetFont(&g_fontEdit);
// 	m_pButton[8].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
// 	m_pButton[8].Create(strLanguage[3][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(900, 714), c, this, IDC_BUTTON_CS10); 
	
	//回零	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_HOME1);
	m_pButton[9].SetFont(&g_fontEdit);
	m_pButton[9].SetBitMapID(IDB_BITMAP_HOME1,IDB_BITMAP_HOME2);	
	m_pButton[9].Create(strLanguage[4][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(923, 310), c, this, IDC_BUTTON_CS2); 
    m_pButton[9].SelectState(IDB_BITMAP_HOME3);
	DeleteObject(c);
}

void CDlg_scan::InitParameter()
{
	m_dBeginX = g_ScanPara.dScanBeginPosX;
	m_dBeginY = g_ScanPara.dScanBeginPosY;
	m_dScanPace = g_ScanPara.dScanPace;
	m_dCenterX = g_ScanPara.dScanCenterPosX;
	m_dCenterY = g_ScanPara.dScanCenterPosY;
	m_dSpeed = g_ScanPara.dScanSpeed;
	
}
