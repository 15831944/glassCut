// Dlg_Home.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_Home.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Home dialog


CDlg_Home::CDlg_Home(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Home::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Home)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nHome = 0;
}

CDlg_Home::~CDlg_Home()
{
}

void CDlg_Home::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Home)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Home, CDialog)
	//{{AFX_MSG_MAP(CDlg_Home)
	ON_BN_CLICKED(IDC_BUTTON_CS1, OnButtonCs1)
	ON_BN_CLICKED(IDC_BUTTON_CS2, OnButtonCs2)
	ON_BN_CLICKED(IDC_BUTTON_CS3, OnButtonCs3)	
	ON_BN_CLICKED(IDC_BUTTON_CS4, OnButtonCs4)
	ON_BN_CLICKED(IDC_BUTTON_CS5, OnButtonCs5)
	ON_BN_CLICKED(IDC_BUTTON_CS6, OnButtonCs6)
	ON_BN_CLICKED(IDC_BUTTON_CS7, OnButtonCs7)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_Home message handlers

BOOL CDlg_Home::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->wParam==VK_ESCAPE||pMsg->wParam==VK_RETURN)
		return(TRUE);
	if(pMsg->lParam==VK_F4||pMsg->wParam==VK_F4)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlg_Home::OnInitDialog() 
{
	CDialog::OnInitDialog();
	OnInitButton();
	SetWindowPos(CWnd::GetOwner(),0,708,1024,60,SWP_SHOWWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_Home::OnInitButton()
{
	HRGN c;
	
	CString strName[4][2];
    strName[0][0] = "机械零点";
	strName[1][0] = "程序零点";
	strName[2][0] = "同时";
	strName[3][0] = "停止";
	strName[0][1] = "Mach zero";
	strName[1][1] = "Pro zero";
	strName[2][1] = "Simultane";
	strName[3][1] = "Stop";
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP1);
	//机械零点	
	m_pButton[0].SetFont(&g_fontStatic);
	m_pButton[0].SetBitMapID(IDB_BITMAP_PHOME1,IDB_BITMAP_PHOME2);	
	m_pButton[0].Create(strName[0][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(15, 6), c, this, IDC_BUTTON_CS1); 
	//程序零点	
	m_pButton[1].SetFont(&g_fontStatic);
	m_pButton[1].SetBitMapID(IDB_BITMAP_MHOME1,IDB_BITMAP_MHOME2);	
	m_pButton[1].Create(strName[1][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(145, 6), c, this, IDC_BUTTON_CS2); 
	//X	
	m_pButton[2].SetFont(&g_fontEdit);
	m_pButton[2].SetBitMapID(IDB_BITMAP_HOMEX1,IDB_BITMAP_HOMEX2);	
	m_pButton[2].Create("X", WS_CHILD | WS_VISIBLE, CPoint(300, 6), c, this, IDC_BUTTON_CS3); 
	//Y
	m_pButton[3].SetFont(&g_fontEdit);
	m_pButton[3].SetBitMapID(IDB_BITMAP_HOMEX1,IDB_BITMAP_HOMEX2);	
	m_pButton[3].Create("Y", WS_CHILD | WS_VISIBLE, CPoint(430, 6), c, this, IDC_BUTTON_CS4); 
	//C
	m_pButton[4].SetFont(&g_fontEdit);
	m_pButton[4].SetBitMapID(IDB_BITMAP_HOMEX1,IDB_BITMAP_HOMEX2);	
	m_pButton[4].Create("C", WS_CHILD | WS_VISIBLE, CPoint(560, 6), c, this, IDC_BUTTON_CS5); 
	//同时
	m_pButton[5].SetFont(&g_fontEdit);
	m_pButton[5].SetBitMapID(IDB_BITMAP_HOMEX1,IDB_BITMAP_HOMEX2);	
	m_pButton[5].Create(strName[2][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(690, 6), c, this, IDC_BUTTON_CS6); 
	//停止
	m_pButton[6].SetFont(&g_fontEdit);
	m_pButton[6].SetBitMapID(IDB_BITMAP_STOP1,IDB_BITMAP_STOP2);	
	m_pButton[6].Create(strName[3][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(850, 6), c, this, IDC_BUTTON_CS7); 

	DeleteObject(c);
}

void CDlg_Home::OnButtonCs1()//机械零点
{
	m_nHome = 0;
	m_pButton[0].SelectState(IDB_BITMAP_PHOME3);
	m_pButton[1].SelectState(0);
	g_handdll.zoneSpeedSet(g_stu_pAxisA->d_zerospeed,g_stu_pAxisB->d_zerospeed,g_stu_pAxisC->d_zerospeed,g_stu_pAxisD->d_zerospeed);
//	g_handdll.zoneDirSet(g_stu_pAxisA->l_zerodirection,g_stu_pAxisB->l_zerodirection,g_stu_pAxisC->l_zerodirection,g_stu_pAxisD->l_zerodirection);
	g_handdll.zoneOffset(g_stu_pAxisA->d_ZeroOffset,g_stu_pAxisB->d_ZeroOffset,g_stu_pAxisC->d_ZeroOffset,g_stu_pAxisD->d_ZeroOffset); 

}
void CDlg_Home::OnButtonCs2()//程序零点
{
	m_nHome = 1;
	m_pButton[0].SelectState(0);
	m_pButton[1].SelectState(IDB_BITMAP_MHOME3);
	g_handdll.handSpeedSet(g_stu_pAxisA->d_handspeed, g_stu_pAxisB->d_handspeed, g_stu_pAxisC->d_handspeed, g_stu_pAxisD->d_handspeed); 	
}
void CDlg_Home::OnButtonCs3()
{
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
		OnShowMessageBox(22,g_iLanguage,FALSE);
	else
	{
		if(m_nHome==0)			
		{
			char szDmc[80]={0};
			if(g_stu_pAxisF->bSpareA == TRUE)//龙门同步
			{
				CString     filename=g_strOriginalPathC+"Temp.dmc";    
				Secret("C:\\WINDOWS\\system32\\focusB.dll",filename);  //X  
				sprintf(szDmc,filename);				
			}
			else
			{
				strcpy(szDmc,g_strOriginalPathC + "homex.dmc");
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
			g_Controller.Command("ST;WT20;XQ#XHOME");
			
		}
		else    
		{
			char chZero[80] = {0};
			g_Controller.Command("MG homecx&homecy&homecz",chZero,sizeof(chZero));
			if(atoi(chZero) == 1)
				g_Controller.Command("PA0;BGX");
		}
	}
}
void CDlg_Home::OnButtonCs4()
{
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
		OnShowMessageBox(22,g_iLanguage,FALSE);
	else
	{
		if(m_nHome==0)			
		{
			char szDmc[80]={0};
			strcpy(szDmc,g_strOriginalPathC + "homey.dmc");
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
			g_Controller.Command("ST;WT20;XQ#YHOME");
		}
		else
		{
			char chZero[80] = {0};
			g_Controller.Command("MG homecx&homecy&homecz",chZero,sizeof(chZero));
			if(atoi(chZero) == 1)
				g_Controller.Command("PA,0;BGY");
		}
	}			
}
void CDlg_Home::OnButtonCs5()
{
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
		OnShowMessageBox(22,g_iLanguage,FALSE);
	else
	{
		if(m_nHome==0)			
		{
			char szDmc[80]={0};
			strcpy(szDmc,g_strOriginalPathC + "homez.dmc");
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
			g_Controller.Command("ST;WT20;XQ#ZHOME");
		}
		else 
		{
			char chZero[80] = {0};
			g_Controller.Command("MG homecx&homecy&homecz",chZero,sizeof(chZero));
			if(atoi(chZero) == 1)
				g_Controller.Command("PA,,0;BGZ");
		}
	}	
}
void CDlg_Home::OnButtonCs6()
{
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
		if(m_nHome==0)			
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
		else  
		{
			char chZero[80] = {0};
			g_Controller.Command("MG homecx&homecy&homecz",chZero,sizeof(chZero));
	        if(atoi(chZero) == 1)
				g_Controller.Command("PA0,0,0;BGXYZ");
		}
	}	
}
void CDlg_Home::OnButtonCs7()
{
	g_Controller.Command("ST");
	Sleep(40);
	g_Controller.Command("STXYZ");
	if(g_stu_pAxisF->bSpareA == TRUE)//龙门同步
	{
		g_Controller.Command("ST");
		Sleep(50);
		g_Controller.Command("GA,,,CX;GR0,,,1;GM1,,,1");
		Sleep(50);
	}
}

void CDlg_Home::OpenDlgInit()
{
	g_lRc = g_Controller.Command("ST");
	Sleep(40);
	g_lRc = g_Controller.Command("STXYZ");
	g_handdll.handSpeedACSet(g_stu_pAxisA->d_acc, g_stu_pAxisB->d_acc, g_stu_pAxisC->d_acc, g_stu_pAxisD->d_acc); 
	g_handdll.handSpeedDCSet(g_stu_pAxisA->d_dec, g_stu_pAxisB->d_dec, g_stu_pAxisC->d_dec, g_stu_pAxisD->d_dec); 
	OnButtonCs1();//机械零点
}

