// dlg_hand.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "dlg_hand.h"
#include "Dlg_KeyNumber.h"
#include "benderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static double dFlag_pressure = 0.0;
/////////////////////////////////////////////////////////////////////////////
// dlg_hand dialog

dlg_hand::dlg_hand(CWnd* pParent /*=NULL*/)
	: CDialog(dlg_hand::IDD, pParent)
{
	//{{AFX_DATA_INIT(dlg_hand)
	//}}AFX_DATA_INIT
	nStep = 0;
}
dlg_hand::~dlg_hand()
{

}

void dlg_hand::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dlg_hand)
	DDX_Control(pDX, IDC_BUTTON_HAND, m_clrBtnLabel);
	DDX_Control(pDX, IDC_EDITZ, m_ez);
	DDX_Control(pDX, IDC_EDITY, m_ey);
	DDX_Control(pDX, IDC_EDITX, m_ex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dlg_hand, CDialog)
	//{{AFX_MSG_MAP(dlg_hand)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_DIRECTX, OnButtonDirectx)
	ON_BN_CLICKED(IDC_BUTTON_INVERSEX, OnButtonInversex)
	ON_BN_CLICKED(IDC_BUTTON_DIRECTY, OnButtonDirecty)
	ON_BN_CLICKED(IDC_BUTTON_INVERSEY, OnButtonInversey)
	ON_BN_CLICKED(IDC_BUTTON_DIRECTZ, OnButtonDirectz)
	ON_BN_CLICKED(IDC_BUTTON_INVERSEZ, OnButtonInversez)
	ON_BN_CLICKED(IDC_BUTTON_PACE, OnButtonPace)
	ON_MESSAGE(WM_MOUSEDN,OnMouseDn)
	ON_BN_CLICKED(IDC_BUTTON_A1, OnButtonA1)
	ON_BN_CLICKED(IDC_BUTTON_B1, OnButtonB1)
	ON_BN_CLICKED(IDC_BUTTON_C1, OnButtonC1)
	ON_BN_CLICKED(IDC_BUTTON_D1, OnButtonD1)
	ON_BN_CLICKED(IDC_BUTTON_A2, OnButtonA2)
	ON_BN_CLICKED(IDC_BUTTON_B2, OnButtonB2)
	ON_BN_CLICKED(IDC_BUTTON_D2, OnButtonD2)
	ON_BN_CLICKED(IDC_BUTTON_A3, OnButtonA3)
	ON_BN_CLICKED(IDC_BUTTON_C3, OnButtonC3)
	ON_BN_CLICKED(IDC_BUTTON_D3, OnButtonD3)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_BN_CLICKED(IDC_BUTTON_CS8, OnButtonCs8)
	ON_BN_CLICKED(IDC_BUTTON_CS7, OnButtonCs7)
	ON_BN_CLICKED(IDC_BUTTON_CS6, OnButtonCs6)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_HAND, OnButtonHand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dlg_hand message handlers

BOOL dlg_hand::OnInitDialog() 
{
	CDialog::OnInitDialog();

    ((CEdit *)GetDlgItem(IDC_EDITX))->SetFont(&g_fontEdit);
	((CEdit *)GetDlgItem(IDC_EDITY))->SetFont(&g_fontEdit);
	((CEdit *)GetDlgItem(IDC_EDITZ))->SetFont(&g_fontEdit);
	OnCutWindow();
    OnLanguage();	
	OnInitButton();
	// TODO: Add extra initialization here
	m_ex.SetWindowText("0");    	    
	m_ey.SetWindowText("0");    	
	m_ez.SetWindowText("0");
		
	SetWindowPos(CWnd::GetOwner(),0,0,g_screen.x,g_screen.y,SWP_SHOWWINDOW);
	for(int i=0;i<4;i++)
	{
		m_nHandNewBtn[i] = 0;
		m_nHandOldBtn[i] = 0;
	}


	CWnd::SetTimer(1,30,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void dlg_hand::OnInitButton() 
{
	HRGN hrgnHand;
	hrgnHand = CreateRectRgn(0, 0, 58, 50);	
	//Y+
	m_pClrButton[13].HaveBitmap(1);
	m_pClrButton[13].SetFont(&g_fontEdit);
	m_pClrButton[13].SetBitMapID(IDB_BITMAP_DLGHAND1,IDB_BITMAP_DLGHAND2);	
	m_pClrButton[13].Create("Y+", WS_CHILD | WS_VISIBLE, CPoint(802,380), hrgnHand, this, IDC_BUTTON_DIRECTY); 
	//连续	
	m_pClrButton[14].HaveBitmap(1);
	if(g_iLanguage==0)
		m_pClrButton[14].SetFont(&g_fontEdit);
	else
		m_pClrButton[14].SetFont(&g_fontList);
	m_pClrButton[14].SetBitMapID(IDB_BITMAP_DLGHAND1,IDB_BITMAP_DLGHAND2);	
	m_pClrButton[14].Create(m_strCon, WS_CHILD | WS_VISIBLE, CPoint(802,434), hrgnHand, this, IDC_BUTTON_PACE); 
	//Y-	
	m_pClrButton[15].HaveBitmap(1);
	m_pClrButton[15].SetFont(&g_fontEdit);
	m_pClrButton[15].SetBitMapID(IDB_BITMAP_DLGHAND1,IDB_BITMAP_DLGHAND2);		
	m_pClrButton[15].Create("Y-", WS_CHILD | WS_VISIBLE, CPoint(802,488), hrgnHand, this, IDC_BUTTON_INVERSEY); 
 	//X-	
	m_pClrButton[16].HaveBitmap(1);
	m_pClrButton[16].SetFont(&g_fontEdit);
	m_pClrButton[16].SetBitMapID(IDB_BITMAP_DLGHAND1,IDB_BITMAP_DLGHAND2);		
	m_pClrButton[16].Create("X-", WS_CHILD | WS_VISIBLE, CPoint(740,434), hrgnHand, this, IDC_BUTTON_INVERSEX); 
  	//X+	
	m_pClrButton[17].HaveBitmap(1);
	m_pClrButton[17].SetFont(&g_fontEdit);
	m_pClrButton[17].SetBitMapID(IDB_BITMAP_DLGHAND1,IDB_BITMAP_DLGHAND2);		
	m_pClrButton[17].Create("X+", WS_CHILD | WS_VISIBLE, CPoint(864,434), hrgnHand, this, IDC_BUTTON_DIRECTX); 
	//Z+	
	m_pClrButton[10].HaveBitmap(1);
	m_pClrButton[10].SetFont(&g_fontEdit);
	m_pClrButton[10].SetBitMapID(IDB_BITMAP_DLGHAND1,IDB_BITMAP_DLGHAND2);		
	m_pClrButton[10].Create("Z+", WS_CHILD | WS_VISIBLE, CPoint(945,380), hrgnHand, this, IDC_BUTTON_DIRECTZ); 
	//停止	
	m_pClrButton[7].HaveBitmap(1);
	m_pClrButton[7].SetFont(&g_fontEdit);
	m_pClrButton[7].SetBitMapID(IDB_BITMAP_DLGHAND1,IDB_BITMAP_DLGHAND2);		
	m_pClrButton[7].Create(m_strStop, WS_CHILD | WS_VISIBLE, CPoint(945,434), hrgnHand, this, IDC_BUTTON_STOP); 
	//Z-	
	m_pClrButton[6].HaveBitmap(1);
	m_pClrButton[6].SetFont(&g_fontEdit);
	m_pClrButton[6].SetBitMapID(IDB_BITMAP_DLGHAND1,IDB_BITMAP_DLGHAND2);		
	m_pClrButton[6].Create("Z-", WS_CHILD | WS_VISIBLE, CPoint(945,488), hrgnHand, this, IDC_BUTTON_INVERSEZ); 

	DeleteObject(hrgnHand);

	HRGN c;

	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_FORWARD1);
		//根据选项显示传送带相关按钮
	CString str[5][2];
	str[0][0] = "正向";
	str[1][0] = "反向";
	str[2][0] = "慢速";
	str[3][0] = "快速";
	str[4][0] = "升降";
	str[0][1] = "Forward";
	str[1][1] = "Reverse";
	str[2][1] = "Slow";
	str[3][1] = "Fast";
	str[4][1] = " Up/Down";
	
	//正向	
	m_pClrButton[0].SetFont(&g_fontStatic);
	m_pClrButton[0].SetBitMapID(IDB_BITMAP_FORWARD1,IDB_BITMAP_FORWARD2);	
	m_pClrButton[0].Create(str[0][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(5, 714), c, this, IDC_BUTTON_A1); 
	//反向	
	m_pClrButton[1].SetFont(&g_fontStatic);
	m_pClrButton[1].SetBitMapID(IDB_BITMAP_REVERSE1,IDB_BITMAP_REVERSE2);	
	m_pClrButton[1].Create(str[1][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(107, 714), c, this, IDC_BUTTON_B1); 
	//速度1	
	m_pClrButton[2].SetFont(&g_fontStatic);
	m_pClrButton[2].SetBitMapID(IDB_BITMAP_SP11,IDB_BITMAP_SP12);	
	m_pClrButton[2].Create(str[2][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(209, 714), c, this, IDC_BUTTON_C1); 
	//速度2	
	m_pClrButton[3].SetFont(&g_fontStatic);
	m_pClrButton[3].SetBitMapID(IDB_BITMAP_SP21,IDB_BITMAP_SP22);	
	m_pClrButton[3].Create(str[3][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(311, 714), c, this, IDC_BUTTON_D1); 	
	//传送带升降	
	m_pClrButton[4].SetFont(&g_fontStatic);
	m_pClrButton[4].SetBitMapID(IDB_BITMAP_UD1,IDB_BITMAP_UD2);	
	m_pClrButton[4].Create(str[4][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(413, 714), c, this, IDC_BUTTON_D3); 
	CString str1[8][2];
	str1[0][0] = "下刀";
	str1[1][0] = "风机";
	str1[2][0] = "定位块";
	str1[3][0] = "置位";
	str1[4][0] = "运动";
	str1[5][0] = "注油A";
	str1[6][0] = "注油B";
	str1[7][0] = "反运动";
	str1[0][1] = "C-Axis";
	str1[1][1] = "Fan";
	str1[2][1] = "Location";
	str1[3][1] = "Postion";
	str1[4][1] = "Move";
	str1[5][1] = "Oil1";
	str1[6][1] = "Oil2";
	str1[7][1] = " Rev Move";
	//风机启停	
//    if (g_stu_pAxisE->bSpareA==TRUE)
    {
		m_pClrButton[9].SetFont(&g_fontStatic);
		m_pClrButton[9].SetBitMapID(IDB_BITMAP_FANST1,IDB_BITMAP_FANST2);	
		m_pClrButton[9].Create(str1[1][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(515, 714), c, this, IDC_BUTTON_D2); 
	}
	//下刀
	m_pClrButton[5].SetFont(&g_fontStatic);
	m_pClrButton[5].SetBitMapID(IDB_BITMAP_CUD1,IDB_BITMAP_CUD2);	
	m_pClrButton[5].Create(str1[0][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(617, 714), c, this, IDC_BUTTON_A3); 	
	//定位	
	m_pClrButton[8].SetFont(&g_fontStatic);
	m_pClrButton[8].SetBitMapID(IDB_BITMAP_POS1,IDB_BITMAP_POS2);	
	m_pClrButton[8].Create(str1[2][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(719, 714), c, this, IDC_BUTTON_C3); 
	//煤油A
	m_pClrButton[18].SetFont(&g_fontStatic);
	m_pClrButton[18].SetBitMapID(IDB_BITMAP_OILH1,IDB_BITMAP_OILH2);	
	m_pClrButton[18].Create(str1[5][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(821, 714), c, this, IDC_BUTTON_B2); 
	//切割油B
	m_pClrButton[19].SetFont(&g_fontStatic);
	m_pClrButton[19].SetBitMapID(IDB_BITMAP_OILH1,IDB_BITMAP_OILH2);	
	m_pClrButton[19].Create(str1[6][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(923, 714), c, this, IDC_BUTTON_A2); 
	

	//置位	
	m_pClrButton[11].SetFont(&g_fontStatic);
	m_pClrButton[11].SetBitMapID(IDB_BITMAP_SETPOS1,IDB_BITMAP_SETPOS2);	
	m_pClrButton[11].Create(str1[3][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(900, 655), c, this, IDC_BUTTON_CS7); 	
	//运动
	m_pClrButton[12].SetFont(&g_fontStatic);
	m_pClrButton[12].SetBitMapID(IDB_BITMAP_SPORT1,IDB_BITMAP_SPORT2);	
	m_pClrButton[12].Create(str1[4][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(900, 550), c, this, IDC_BUTTON_CS8); 
	//运动返回
	m_pClrButton[20].SetFont(&g_fontStatic);
	m_pClrButton[20].SetBitMapID(IDB_BITMAP_SPORT1,IDB_BITMAP_SPORT2);	
	m_pClrButton[20].Create(str1[7][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(900, 600), c, this, IDC_BUTTON_CS6); 
	DeleteObject(c);
}

void dlg_hand::OnAxisADD(int nStep, int nAxis) 
{
	double dStepper;

	if(nStep==HAND_CON)	    	    dStepper = 0;
	else if(nStep==HAND_01)		    dStepper = 0.1;
	else if(nStep==HAND_1)	    	dStepper = 1;
	else if(nStep==HAND_5)	    	dStepper = 5;
	else if(nStep==HAND_10)		    dStepper = 10;
	else	                     	dStepper = 0;

	if(g_stu_pAxisH->sSpare!=0)		dStepper = dStepper * IN_TO_MM;

	switch (nAxis)
	{
	case HAND_X:
        g_handdll.handAxisAdd('A', dStepper);
		break;
	case HAND_Y:
        g_handdll.handAxisAdd('B', dStepper);
		break;
	case HAND_Z:
        g_handdll.handAxisAdd('C', dStepper);
		break;
	default:
		break;
	}
}
void dlg_hand::OnAxisSUB(int nStep, int nAxis) 
{
	double dStepper;

	if(nStep==HAND_CON)	    	    dStepper = 0;
	else if(nStep==HAND_01)		    dStepper = 0.1;
	else if(nStep==HAND_1)	    	dStepper = 1;
	else if(nStep==HAND_5)	    	dStepper = 5;
	else if(nStep==HAND_10)		    dStepper = 10;
	else	                     	dStepper = 0;

	if(g_stu_pAxisH->sSpare!=0)		dStepper = dStepper * IN_TO_MM;

	switch (nAxis)
	{
	case HAND_X:
        g_handdll.handAxisSub('A', dStepper);
		break;
	case HAND_Y:
        g_handdll.handAxisSub('B', dStepper);
		break;
	case HAND_Z:
        g_handdll.handAxisSub('C', dStepper);
		break;
	default:
		break;
	}
}

BOOL dlg_hand::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->wParam==VK_ESCAPE)
		return(TRUE);
	if(pMsg->lParam==VK_F4||pMsg->wParam==VK_F4)
		return TRUE;
	if(pMsg->wParam==VK_RETURN)
	{
		 if(pMsg->message==WM_KEYUP)
		{
			keybd_event(VK_TAB, 0, 0, 0);                 //换行
			keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);	
		}	
		return TRUE;
	}

	if(pMsg->wParam==VK_HOME||pMsg->wParam==VK_END||pMsg->wParam==VK_NEXT||pMsg->wParam==VK_PRIOR||
		pMsg->wParam==VK_UP||pMsg->wParam==VK_DOWN||pMsg->wParam==VK_LEFT||pMsg->wParam==VK_RIGHT||pMsg->wParam==VK_SPACE)
	{
		if(GetKeyState(pMsg->wParam)<0)
			SendMessage(WM_KEYDOWN, pMsg->wParam, 0);
		else
			SendMessage(WM_KEYUP, pMsg->wParam, 0);
		return TRUE;
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

void dlg_hand::OnLanguage()
{
	int		i;
	int		nIndex;
	nIndex = g_iLanguage + 1;
	
	for(i=0;i<AR_HAND;i++)
	{
		if(g_arr_strHand[i][nIndex]=="NULL")		
			g_arr_strHand[i][nIndex] = "";
		CWnd::SetDlgItemText(atoi(g_arr_strHand[i][0]),g_arr_strHand[i][nIndex]);
	}
	if (g_iLanguage == 1)
	{
		m_strCon = "Cont";
		m_strStop ="Stop" ;
	}
	else
	{
		m_strCon = "连续";
		m_strStop ="停止" ;
	}
}

void dlg_hand::OnSetDP() 
{
	CString strEdtx,strEdty,strEdtz,str;
	double  dEdtx,dEdty,dEdtz;
	char    szCmdx[20],szCmdy[20],szCmdz[20];
	int     i,arr_iCh[3];
	char szRes[80]={0};
	
	for(i=0;i<3;i++)   arr_iCh[i] = 0;
	GetDlgItemText(IDC_EDITX,strEdtx);          if(strEdtx!="")   arr_iCh[0] = 1;
	GetDlgItemText(IDC_EDITY,strEdty);          if(strEdty!="")   arr_iCh[1] = 1;
	GetDlgItemText(IDC_EDITZ,strEdtz);          if(strEdtz!="")   arr_iCh[2] = 1;
	dEdtx = atof(strEdtx)*g_stu_pAxisA->d_pulse_user;     strEdtx.Format("%.0f",dEdtx);
	dEdty = atof(strEdty)*g_stu_pAxisB->d_pulse_user;     strEdty.Format("%.0f",dEdty);
	dEdtz = atof(strEdtz)*g_stu_pAxisC->d_pulse_user;     strEdtz.Format("%.0f",dEdtz);
	strEdtx = "stepx="+strEdtx;
	strEdty = "stepy="+strEdty;
	strEdtz = "stepz="+strEdtz;
	
	strcpy(szCmdx, LPCTSTR(strEdtx));
	strcpy(szCmdy, LPCTSTR(strEdty));
	strcpy(szCmdz, LPCTSTR(strEdtz));
	g_Controller.Command(szCmdx,szRes,sizeof(szRes));    	
	g_Controller.Command(szCmdy,szRes,sizeof(szRes));    	
	g_Controller.Command(szCmdz,szRes,sizeof(szRes));    	
	//==============================================
	CString sztemp;
	g_lRc = g_Controller.Command("RPX",szRes,sizeof(szRes)); 
	g_fCurrMachineX = g_fCurrMachineX + (float)((atof(szRes) - dEdtx)/g_stu_pAxisA->d_pulse_user);
	g_lRc = g_Controller.Command("RPY",szRes,sizeof(szRes));
	g_fCurrMachineY = g_fCurrMachineY + (float)((atof(szRes) - dEdty)/g_stu_pAxisB->d_pulse_user);
	g_lRc = g_Controller.Command("RPZ",szRes,sizeof(szRes));	
	g_fCurrMachineZ = g_fCurrMachineZ + (float)((atof(szRes) - dEdtz)/g_stu_pAxisC->d_pulse_user);
	g_lRc = g_Controller.Command("MachX=1;MachY=1");
	char szCmd[80]={0};
	{
		if(arr_iCh[0])			str = "DPstepx";
		else                    str = "DP";
		if(arr_iCh[1])		    str = str + ",stepy";
		else if(arr_iCh[2])		str = str + ",";
		if(arr_iCh[2])		    str = str + ",stepz";
		strcpy(szCmd, LPCTSTR(str));
		g_Controller.Command(szCmd);
	}
	OnSoftLimit(g_stu_pAxisA->l_Journey_positive - g_fCurrMachineX,
				g_stu_pAxisB->l_Journey_positive - g_fCurrMachineY,
				g_stu_pAxisA->l_Journey_negative - g_fCurrMachineX,
				g_stu_pAxisB->l_Journey_negative - g_fCurrMachineY);
	g_handdll.SetJourneyPositive(g_stu_pAxisA->l_Journey_positive - g_fCurrMachineX, g_stu_pAxisB->l_Journey_positive - g_fCurrMachineY, g_stu_pAxisC->l_Journey_positive, g_stu_pAxisD->l_Journey_positive);
	g_handdll.SetJourneyNegetive(g_stu_pAxisA->l_Journey_negative - g_fCurrMachineX, g_stu_pAxisB->l_Journey_negative - g_fCurrMachineY, g_stu_pAxisC->l_Journey_negative, g_stu_pAxisD->l_Journey_negative);
	m_ex.SetWindowText("0");    	    
	m_ey.SetWindowText("0");    	
	m_ez.SetWindowText("0");
}

LRESULT dlg_hand::OnEditDouble(WPARAM wParam, LPARAM lParam) 
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
	case IDC_EDITX:				KeyNum.m_strTitle = "X";			break;
	case IDC_EDITY:				KeyNum.m_strTitle = "Y";			break;
	case IDC_EDITZ:				KeyNum.m_strTitle = "Z";			break;	
	default:
		break;
	}
	if(KeyNum.DoModal()==IDOK)
	{
		CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);	
	}
 
	
	return 0;
}

void dlg_hand::OnButtonStop() 
{
	g_Controller.Command("ST");
}

void dlg_hand::OnButtonDirectx() 
{
	if(nStep==0)
		g_Controller.Command("STX");
}

void dlg_hand::OnButtonDirecty() 
{
	if(nStep==0)
		g_Controller.Command("STY");
}

void dlg_hand::OnButtonDirectz() 
{
	if(nStep==0)
		g_Controller.Command("STZ");
}

void dlg_hand::OnButtonInversex() 
{
	if(nStep==0)
		g_Controller.Command("STX");
}

void dlg_hand::OnButtonInversey() 
{
	if(nStep==0)
		g_Controller.Command("STY");
}

void dlg_hand::OnButtonInversez() 
{
	if(nStep==0)
		g_Controller.Command("STZ");
}

LRESULT dlg_hand::OnMouseDn(WPARAM wParam, LPARAM lParam) 
{
	switch(wParam) 
	{
	case IDC_BUTTON_DIRECTX:
		OnAxisADD(nStep, HAND_X);			
		break;
	case IDC_BUTTON_INVERSEX:      	
		OnAxisSUB(nStep, HAND_X);			
		break;
	case IDC_BUTTON_DIRECTY:      	
		OnAxisADD(nStep, HAND_Y);			
		break;
	case IDC_BUTTON_INVERSEY:      	
		OnAxisSUB(nStep, HAND_Y);			
		break;
	case IDC_BUTTON_DIRECTZ:      	
		OnAxisADD(nStep, HAND_Z);			
		break;
	case IDC_BUTTON_INVERSEZ:      	
		OnAxisSUB(nStep, HAND_Z);			
		break;
	default:										
		break;
	}
	return 0;
}

void dlg_hand::OnButtonPace() 
{
	if(nStep == HAND_01)
	{
		nStep = HAND_1;				
		m_pClrButton[14].SetWindowText("1");		
	}
	else if(nStep == HAND_1)
	{
		nStep = HAND_5;
		m_pClrButton[14].SetWindowText("5");
	}
	else if(nStep == HAND_5)
	{
		nStep = HAND_10;
		m_pClrButton[14].SetWindowText("10");
	}
	else if(nStep == HAND_10)
	{
		nStep = HAND_CON;
		m_pClrButton[14].SetWindowText(m_strCon);
	}
	else if(nStep == HAND_CON)
	{
		nStep = HAND_01;
		m_pClrButton[14].SetWindowText("0.1");
	}
	m_pClrButton[14].RepeatDraw();
}

void dlg_hand::OnCutWindow()
{
	CPaintDC dc(this); // device context for painting
	dc.BeginPath();	
	dc.MoveTo(720, 363);
	dc.LineTo(1024, 363);	
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

//变频器正
void dlg_hand::OnButtonA1() 
{
	if(g_handdll.GetOut(OUT_TRANSDUCER_FORWARD)==1)	    
	{
		g_handdll.SetOut(OUT_TRANSDUCER_FORWARD,FALSE);
		m_pClrButton[0].SelectState(0);
	}
	else
	{
		g_handdll.SetOut(OUT_TRANSDUCER_REVERSE,FALSE);
		g_handdll.SetOut(OUT_TRANSDUCER_FORWARD,TRUE);
		m_pClrButton[0].SelectState(IDB_BITMAP_FORWARD3);
		m_pClrButton[1].SelectState(0);
	}
}

//变频器负
void dlg_hand::OnButtonB1() 
{
	if(g_handdll.GetOut(OUT_TRANSDUCER_REVERSE)==1)	    
	{
		g_handdll.SetOut(OUT_TRANSDUCER_REVERSE,FALSE);
		m_pClrButton[1].SelectState(0);
	}
	else
	{
		g_handdll.SetOut(OUT_TRANSDUCER_FORWARD,FALSE);
		g_handdll.SetOut(OUT_TRANSDUCER_REVERSE,TRUE);
		m_pClrButton[1].SelectState(IDB_BITMAP_REVERSE3);
		m_pClrButton[0].SelectState(0);
	}
}

//速度1
void dlg_hand::OnButtonC1() 
{
	if(g_stu_pAxisA->sSpare==1)/* 速度方式 */
		g_Controller.Command("MOW");
	g_handdll.SetOut(OUT_TRANSDUCER_SPEED,FALSE);
	g_handdll.SetOut(OUT_TRANSDUCER_SPEED1,FALSE);
	m_pClrButton[2].SelectState(IDB_BITMAP_SP13);
	m_pClrButton[3].SelectState(0);
}

//速度2
void dlg_hand::OnButtonD1() 
{
	if(g_stu_pAxisA->sSpare==1)/* 速度方式 */
		g_Controller.Command("SHW");
	g_handdll.SetOut(OUT_TRANSDUCER_SPEED,TRUE);
	g_handdll.SetOut(OUT_TRANSDUCER_SPEED1,TRUE);
	m_pClrButton[3].SelectState(IDB_BITMAP_SP23);
	m_pClrButton[2].SelectState(0);
}

//风启停
void dlg_hand::OnButtonD2() 
{
	if(g_handdll.GetOut(OUT_WIND_RELAY)==1)	    
	{
		g_handdll.SetOut(OUT_WIND_RELAY,FALSE);
		m_pClrButton[9].SelectState(0);	
	}
	else
	{
		g_handdll.SetOut(OUT_WIND_RELAY,TRUE);
		m_pClrButton[9].SelectState(IDB_BITMAP_FANST3);	
		m_pClrButton[9].SelectState(IDB_BITMAP_FANST3);	
	}
}

//下刀
void dlg_hand::OnButtonA3() 
{
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)AfxGetMainWnd();
	if(g_handdll.GetOut(OUT_ZAXIS_DN)==1)	    
	{
		CString  szPress;
		g_handdll.SetOut(OUT_ZAXIS_DN,FALSE);
		g_handdll.SetOut(OUT_ZAXIS_DN1,FALSE);
		((CBenderDlg *)GetParent())->m_ocxPlanPress.SetValue(g_stu_pAxisF->dSpareC);
		if(pDlg != NULL)
			pDlg->SetAOorOF(g_stu_pAxisF->dSpareC);
		m_pClrButton[5].SelectState(0);	
	}
	else
	{
		CString  szPress;
		g_handdll.SetOut(OUT_ZAXIS_DN,TRUE);
		g_handdll.SetOut(OUT_ZAXIS_DN1,TRUE);
		((CBenderDlg *)GetParent())->m_ocxPlanPress.SetValue(g_stu_pAxisC->dSpareB);
		if(pDlg != NULL)
			pDlg->SetAOorOF(g_stu_pAxisC->dSpareB);
		m_pClrButton[5].SelectState(IDB_BITMAP_CUD3);	
	}
}

//定位
void dlg_hand::OnButtonC3() 
{
	if(g_handdll.GetOut(OUT_ORIENTATION)==1)	    
	{
		g_handdll.SetOut(OUT_ORIENTATION,FALSE);
		m_pClrButton[8].SelectState(0);	
	}
	else
	{
		g_handdll.SetOut(OUT_ORIENTATION,TRUE);
		m_pClrButton[8].SelectState(IDB_BITMAP_POS3);	
	}
}

//传送带
void dlg_hand::OnButtonD3() 
{
	if(g_handdll.GetOut(OUT_SENDUPDN)==1)	    
	{
		g_handdll.SetOut(OUT_SENDUPDN,FALSE);
		m_pClrButton[4].SelectState(0);	
	}
	else
	{
		g_handdll.SetOut(OUT_SENDUPDN,TRUE);
		m_pClrButton[4].SelectState(IDB_BITMAP_UD3);	
	}
}
//切割油B
void dlg_hand::OnButtonA2() 
{
	if(g_handdll.GetOut(OUT_CUT_OILING)==1)	    
	{
		g_handdll.SetOut(OUT_CUT_OILING,FALSE);			
		m_pClrButton[19].SelectState(0);	
#ifdef CHAOYANG
		g_handdll.SetOut(OUT_OILING,FALSE);	
        m_pClrButton[19].SelectState(0);
#endif
	}
	else
	{
		g_handdll.SetOut(OUT_CUT_OILING,TRUE);			
		m_pClrButton[19].SelectState(IDB_BITMAP_OILH3);	
#ifdef CHAOYANG
		g_handdll.SetOut(OUT_OILING,TRUE);
		m_pClrButton[19].SelectState(IDB_BITMAP_OILH3);	
#endif
	}	
}
//煤油A
void dlg_hand::OnButtonB2() 
{	
	if(g_handdll.GetOut(OUT_OILING)==1)	    
	{
		g_handdll.SetOut(OUT_OILING,FALSE);
		m_pClrButton[18].SelectState(0);	
		
	}
	else
	{
		g_handdll.SetOut(OUT_OILING,TRUE);
		m_pClrButton[18].SelectState(IDB_BITMAP_OILH3);	
	}	
	
}
void dlg_hand::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar) 
	{
	case VK_RIGHT:
		OnAxisADD(nStep, HAND_X);			
		break;
	case VK_LEFT:      	
		OnAxisSUB(nStep, HAND_X);			
		break;
	case VK_UP:      	
		OnAxisADD(nStep, HAND_Y);			
		break;
	case VK_DOWN:      	
		OnAxisSUB(nStep, HAND_Y);			
		break;
	case VK_PRIOR:      	
		OnAxisADD(nStep, HAND_Z);			
		break;
	case VK_NEXT:      	
		OnAxisSUB(nStep, HAND_Z);			
		break;
	default:										
		break;
	}
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void dlg_hand::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar) 
	{
	case VK_RIGHT:      	
	case VK_LEFT:      	
		if(nStep==0)
			g_Controller.Command("STX");
		break;
	case VK_UP:      	
	case VK_DOWN:      	
		if(nStep==0)
			g_Controller.Command("STY");
		break;
	case VK_PRIOR:      	
	case VK_NEXT:      	
		if(nStep==0)
			g_Controller.Command("STZ");
		break;
	case VK_HOME:
		OnButtonPace();
		break;
	case VK_END:
		OnButtonStop();
		break;
	default:										
		break;
	}
	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}

//置位
void dlg_hand::OnButtonCs7() 
{
	CDlg_AfxMessage Message;
	Message.bYesNo = TRUE;
	if (g_iLanguage == 0)
	{
		Message.strAfxNO = "取消";
		Message.strAfxYES = "确定";
		Message.strAfxTitle = "提示";
		Message.strAfxMessage = "是否要重新定义程序零点 ?";
	}
	else
	{
		Message.strAfxNO = "NO";
		Message.strAfxYES = "YES";
		Message.strAfxTitle = "Prompt";
		Message.strAfxMessage = "To redefine the program zero point ?";
	}
	if(IDOK == Message.DoModal())
	{
		OnSetDP();
	}
}

//运动
void dlg_hand::OnButtonCs8() 
{
    CString strEdtx,strEdty,strEdtz;
    double  dEdtx,dEdty,dEdtz;
	int     i,arr_iCh[3];
	
	for(i=0;i<3;i++)   arr_iCh[i] = 0;
   	GetDlgItemText(IDC_EDITX,strEdtx);          if(strEdtx!="")   arr_iCh[0] = 1;
   	GetDlgItemText(IDC_EDITY,strEdty);          if(strEdty!="")   arr_iCh[1] = 1;
   	GetDlgItemText(IDC_EDITZ,strEdtz);          if(strEdtz!="")   arr_iCh[2] = 1;
    dEdtx = atof(strEdtx)*g_stu_pAxisA->d_pulse_user;     
    dEdty = atof(strEdty)*g_stu_pAxisB->d_pulse_user;     
    dEdtz = atof(strEdtz)*g_stu_pAxisC->d_pulse_user;     
	if (dEdtx==0 && dEdty==0 && dEdtz==0)
	{
		return;
	}
	
  	//==============================================
	CString str, strBG,strTemp;
	
	if(arr_iCh[0] && dEdtx!=0)
	{
		str.Format("PR%.0f",dEdtx);
		strBG = ";BGX";
	}
	else
	{
		str = "PR";
		strBG = ";BG";
	}
	if(arr_iCh[1] && dEdty!=0)
	{
		strTemp.Format(",%.0f",dEdty);
        str = str + strTemp;
		strBG = strBG + "Y";
	}
	else if(arr_iCh[2] && dEdtz!=0)    
	{
		str = str + ",";
	}
	if(arr_iCh[2] && dEdtz!=0)
	{
		strTemp.Format(",%.0f",dEdtz);
        str = str + strTemp;
		strBG = strBG + "Z";
	}
	char chCmd[80]={0};
	strcpy(chCmd, LPCTSTR(str + strBG));//"PRstepx,stepy,stepz,stepw;BGXYZ"
	g_Controller.Command(chCmd); 
}

//反运动
void dlg_hand::OnButtonCs6()
{
	CString strEdtx,strEdty,strEdtz;
    double  dEdtx,dEdty,dEdtz;
	int     i,arr_iCh[3];
	
	for(i=0;i<3;i++)   arr_iCh[i] = 0;
   	GetDlgItemText(IDC_EDITX,strEdtx);          if(strEdtx!="")   arr_iCh[0] = 1;
   	GetDlgItemText(IDC_EDITY,strEdty);          if(strEdty!="")   arr_iCh[1] = 1;
   	GetDlgItemText(IDC_EDITZ,strEdtz);          if(strEdtz!="")   arr_iCh[2] = 1;
    dEdtx = atof(strEdtx)*g_stu_pAxisA->d_pulse_user;     
    dEdty = atof(strEdty)*g_stu_pAxisB->d_pulse_user;     
    dEdtz = atof(strEdtz)*g_stu_pAxisC->d_pulse_user;     
	if (dEdtx==0 && dEdty==0 && dEdtz==0)
	{
		return;
	}
	
	//==============================================
	CString str, strBG,strTemp;
	
	if(arr_iCh[0] && dEdtx!=0)
	{
		str.Format("PR%.0f",-dEdtx);
		strBG = ";BGX";
	}
	else
	{
		str = "PR";
		strBG = ";BG";
	}
	if(arr_iCh[1] && dEdty!=0)
	{
		strTemp.Format(",%.0f",-dEdty);
        str = str + strTemp;
		strBG = strBG + "Y";
	}
	else if(arr_iCh[2] && dEdtz!=0)    
	{
		str = str + ",";
	}
	if(arr_iCh[2] && dEdtz!=0)
	{
		strTemp.Format(",%.0f",-dEdtz);
        str = str + strTemp;
		strBG = strBG + "Z";
	}
	char chCmd[80]={0};
	strcpy(chCmd, LPCTSTR(str + strBG));//"PRstepx,stepy,stepz,stepw;BGXYZ"
	g_Controller.Command(chCmd); 
} 

void dlg_hand::OpenDlgInit()
{
	g_handdll.ResolutionSet(g_stu_pAxisA->d_pulse_user, g_stu_pAxisB->d_pulse_user, g_stu_pAxisC->d_pulse_user, g_stu_pAxisD->d_pulse_user); 
	g_handdll.handSpeedSet(g_stu_pAxisA->d_handspeed,g_stu_pAxisB->d_handspeed, g_stu_pAxisC->d_handspeed, g_stu_pAxisD->d_handspeed); 
	g_handdll.handSpeedACSet(g_stu_pAxisA->d_acc, g_stu_pAxisB->d_acc, g_stu_pAxisC->d_acc, g_stu_pAxisD->d_acc); 
	g_handdll.handSpeedDCSet(g_stu_pAxisA->d_dec, g_stu_pAxisB->d_dec, g_stu_pAxisC->d_dec, g_stu_pAxisD->d_dec); 
	g_handdll.SetJourneyPositive(g_stu_pAxisA->l_Journey_positive - g_fCurrMachineX, g_stu_pAxisB->l_Journey_positive - g_fCurrMachineY, g_stu_pAxisC->l_Journey_positive, g_stu_pAxisD->l_Journey_positive);
	g_handdll.SetJourneyNegetive(g_stu_pAxisA->l_Journey_negative - g_fCurrMachineX, g_stu_pAxisB->l_Journey_negative - g_fCurrMachineY, g_stu_pAxisC->l_Journey_negative, g_stu_pAxisD->l_Journey_negative);
	if(g_handdll.GetOut(OUT_TRANSDUCER_FORWARD)==1)
		m_pClrButton[0].SelectState(IDB_BITMAP_FORWARD3);
	if(g_handdll.GetOut(OUT_TRANSDUCER_REVERSE)==1)
		m_pClrButton[1].SelectState(IDB_BITMAP_REVERSE3);
	if(g_handdll.GetOut(OUT_TRANSDUCER_SPEED)==1)
	{
		m_pClrButton[3].SelectState(IDB_BITMAP_SP23);
		m_pClrButton[2].SelectState(0);
	}
	else
	{		
		m_pClrButton[2].SelectState(IDB_BITMAP_SP23);
		m_pClrButton[3].SelectState(0);
	}
	if(g_handdll.GetOut(OUT_WIND_RELAY)==1)
		m_pClrButton[9].SelectState(IDB_BITMAP_FANST3);
	if(g_handdll.GetOut(OUT_ZAXIS_DN)==1)
		m_pClrButton[5].SelectState(IDB_BITMAP_CUD3);
	if(g_handdll.GetOut(OUT_ORIENTATION)==1)
		m_pClrButton[8].SelectState(IDB_BITMAP_POS3);
	if(g_handdll.GetOut(OUT_SENDUPDN)==1)
		m_pClrButton[4].SelectState(IDB_BITMAP_UD3);
	if(g_handdll.GetOut(OUT_CUT_OILING)==1)
		m_pClrButton[18].SelectState(IDB_BITMAP_OILH3);
	if(g_handdll.GetOut(OUT_OILING)==1)
		m_pClrButton[19].SelectState(IDB_BITMAP_OILH3);
	//是否打印标签
	if (GetPrivateProfileInt("PRINT","PRINT",0,INIFILE_ADDEXTRA)==0)
	{
		m_clrBtnLabel.ShowWindow(SW_HIDE);
	}
	else
	{
		m_clrBtnLabel.ShowWindow(SW_SHOW);
	}
}
void dlg_hand::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case 1:
		OnErnInput();
		break;
	default:
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}

void dlg_hand::OnErnInput()
{
	m_nHandNewBtn[0] = g_handdll.GetIn(IN_ADDX);
	m_nHandNewBtn[1] = g_handdll.GetIn(IN_SUBX);
	m_nHandNewBtn[2] = g_handdll.GetIn(IN_ADDY);
	m_nHandNewBtn[3] = g_handdll.GetIn(IN_SUBY);
	
	if(m_nHandNewBtn[0] < m_nHandOldBtn[0])
		SendMessage(WM_KEYDOWN, VK_RIGHT, 0);
	else if(m_nHandNewBtn[0] > m_nHandOldBtn[0])
		SendMessage(WM_KEYUP, VK_RIGHT, 0);
	
	if(m_nHandNewBtn[1] < m_nHandOldBtn[1])
		SendMessage(WM_KEYDOWN, VK_LEFT, 0);
	else if(m_nHandNewBtn[1] > m_nHandOldBtn[1])
		SendMessage(WM_KEYUP, VK_LEFT, 0);
	
	if(m_nHandNewBtn[2] < m_nHandOldBtn[2])
		SendMessage(WM_KEYDOWN, VK_UP, 0);
	else if(m_nHandNewBtn[2] > m_nHandOldBtn[2])
		SendMessage(WM_KEYUP, VK_UP, 0);
	
	if(m_nHandNewBtn[3] < m_nHandOldBtn[3])
		SendMessage(WM_KEYDOWN, VK_DOWN, 0);
	else if(m_nHandNewBtn[3] > m_nHandOldBtn[3])
		SendMessage(WM_KEYUP, VK_DOWN, 0);	
	m_nHandOldBtn[0] = m_nHandNewBtn[0];
	m_nHandOldBtn[1] = m_nHandNewBtn[1];
	m_nHandOldBtn[2] = m_nHandNewBtn[2];
	m_nHandOldBtn[3] = m_nHandNewBtn[3];
}

void dlg_hand::OnButtonHand() 
{
	// TODO: Add your control notification handler code here
	if(g_Dmcgc.GetRunflag())     
		return;
	if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1
		||g_handdll.GetCommandFloat((char *)((const char*)"MG_XQ"))>=0.0)	
		OnShowMessageBox(22,g_iLanguage,FALSE);
	else		       
    	g_Dmcgc.HandLabel();

}
