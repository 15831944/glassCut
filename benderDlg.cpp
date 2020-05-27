// benderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "benderDlg.h"
#include "dlg_path2.h"
#include "dlg_motion.h"
#include "dlg_pass.h"
#include "dlg_save.h"
#include "Dlg_affirm.h"
#include "Dlg_bottero.h"
#include "Dlg_MachineCase.h"
#include "dlg_ustLimit.h"
#include "RectOptDlg.h"
#include "Dlg_KeyNumber.h"

#include "hasp_api_cpp.h"
#include "errorprinter.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static char COMBILE_DATE[] = __DATE__;
static char COMBILE_TIME[] = __TIME__;
/////////////////////////////////////////////////////////////////////////////
// CBenderDlg dialog

CBenderDlg::CBenderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBenderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBenderDlg)
	m_iSetNum = 1;
	m_iRunNum = 0;
	m_nLabelSt = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_strHome = g_strOriginalPathC + "homeall.dmc";
	m_strDmcAV = g_strOriginalPathC + "homeav.dmc";
	m_strPressFile = g_strOriginalPathD + "Pressure.ini";
	m_strBreak = g_strOriginalPathC + "break.dmc";
	
    iOldStep = 0;      /* �ϵ���λ��¼ */
	strGCodeOpenFile = "";	/* G������ļ�������������ǰ�򿪣� */
	/*  */
	m_bRunFlag = FALSE;
	m_nScanTreadID = 0;
	m_bDlgPath = FALSE;
	m_nTimer10 = 0;
    m_pInf = NULL;
	m_nExpandX = 1024;	
	m_nExpandY = 768;
	m_bExpandShow = FALSE;	
	m_iReadyTime = 0;
	g_pDlgShowExtra = NULL;
	g_dExtraX = .0;
	g_dExtraY = .0;
	g_strExtraFile = "";
	m_bShowExtra = FALSE;
	m_bFirstOpen = TRUE;
	m_pTestDlg = NULL;
	m_pScanDlg = NULL;
	g_nTestRun = 0;
	m_pHomeDlg = NULL;
	m_bContiueRun = FALSE;
	m_bFile = FALSE;
	m_bAffirm = FALSE;
	m_nOpenLight = 0;
	m_bEmreStop = TRUE;
	m_bNormal = true;
	m_nSafeSwich = 0;
	m_lTVX = 0l;
	m_lTVY = 0l;
	m_lTVZ = 0l;
	m_nGlassNo = GetPrivateProfileInt("TURNOVER","GLASSNO",0,INIFILE_ADDEXTRA);
	m_brush.CreateSolidBrush(RGB(165,198,248));
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBenderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBenderDlg)
	DDX_Control(pDX, IDC_EDIT_LABELST, m_editLabSet);
	DDX_Control(pDX, IDC_EDIT2, m_editRunNum);	
	DDX_Control(pDX, IDC_EDIT1, m_editSetNum);
	DDX_Control(pDX, IDC_EDIT_THICK, m_DEditH);
	DDX_Control(pDX, IDC_LIST_GRID, m_listGrid);
	DDX_Control(pDX, IDC_DISPLAY_MAININF, m_ocxDisplay);
	DDX_Control(pDX, IDC_PLANINFOCTRL_SPEED, m_ocxPlanSpeed);
	DDX_Control(pDX, IDC_CAPTIONINFO_TITLE, m_CapTitle);
	DDX_Control(pDX, IDC_LAMP_X, m_LedX);
	DDX_Control(pDX, IDC_LAMP_Y, m_LedY);
	DDX_Control(pDX, IDC_LAMP_Z, m_LedZ);
	DDX_Control(pDX, IDC_CAPTIONINFO_FILENAME, m_captionFile);
	DDX_Control(pDX, IDC_PLANINFO_PRESS,m_ocxPlanPress);
	DDX_Control(pDX, IDC_MSCOMM1, m_MscComm);
	DDX_Control(pDX, IDC_BTN_MIN, m_BtnMin);
	DDX_Radio(pDX, IDC_RADIO1, m_nGlassNo);
	DDX_Text(pDX, IDC_EDIT_LABELST, m_nLabelSt);
	DDX_Control(pDX, IDC_CAPTIONINFO_TITLE2, m_CapTime);
	DDX_Text(pDX, IDC_EDIT1, m_iSetNum);
	DDX_Text(pDX, IDC_EDIT2, m_iRunNum);	
	DDX_Control(pDX, IDC_CAPTIONINFO_TITLE3, m_CapAlarm);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBenderDlg, CDialog)
	//{{AFX_MSG_MAP(CBenderDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_RUN, OnButtonRun)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_OILAB, OnButtonOil)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON_HOME, OnButtonHome)
	ON_BN_CLICKED(IDC_BUTTON_END, OnButtonEnd)
	ON_MESSAGE(WM_RUNOPTION,OnRunOption)
	ON_MESSAGE(WM_AFFIRM,OnAffirm)
	ON_MESSAGE(WM_INPUT,OnMsgInput)
	ON_MESSAGE(WM_DMCGC, OnDMCGC)
	ON_MESSAGE(WM_SENDSCAN, OnFromDllSendScan)
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_SCAN, OnButtonScan)
	ON_BN_CLICKED(IDC_BUTTON_VIEW, OnButtonView)
	ON_BN_CLICKED(IDC_BUTTON_FIRST, OnButtonFirst)
	ON_BN_CLICKED(IDC_BUTTON_PRE, OnButtonPre)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_LAST, OnButtonLast)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonState)
	ON_BN_CLICKED(IDC_BUTTON_PRESSDOWN, OnButtonPressdown)
	ON_BN_CLICKED(IDC_BUTTON_PRESSUP, OnButtonPressup)
	ON_EN_CHANGE(IDC_EDIT_THICK, OnChangeEditThick)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	ON_BN_CLICKED(IDC_BUTTON_BTNSTART,OnButtonBtnStart)
	ON_BN_CLICKED(IDC_BUTTON_BTNSTOP,OnButtonBtnStop)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_LABELST, OnChangeEditLabelst)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CBenderDlg, CDialog)
//{{AFX_EVENTSINK_MAP(CBenderDlg)
	ON_EVENT(CBenderDlg, IDC_PLANINFOCTRL_SPEED, -600 /* Click */, OnClickPlaninfoctrlSpeed, VTS_NONE)
	ON_EVENT(CBenderDlg, IDC_PLANINFO_PRESS, -600 /* Click */, OnClickPlaninfoPress, VTS_NONE)
	ON_EVENT(CBenderDlg, IDC_DISPLAY_MAININF, -601 /* DblClick */, OnDblClickDisplayMaininf, VTS_NONE)
	ON_EVENT(CBenderDlg, IDC_BTN_MIN, -600 /* Click */, OnClickBtnMin, VTS_NONE)
	ON_EVENT(CBenderDlg, IDC_BUTTON_3DDOWN, -600 /* Click */, OnClickButton3ddown, VTS_NONE)
	ON_EVENT(CBenderDlg, IDC_BUTTON_3DUP, -600 /* Click */, OnClickButton3dup, VTS_NONE)
	ON_EVENT(CBenderDlg, IDC_BUTTON_3DLEFT, -600 /* Click */, OnClickButton3dleft, VTS_NONE)
	ON_EVENT(CBenderDlg, IDC_BUTTON_3DRIGHT, -600 /* Click */, OnClickButton3dright, VTS_NONE)
	ON_EVENT(CBenderDlg, IDC_BUTTON_3DPGUP, -600 /* Click */, OnClickButton3dpgup, VTS_NONE)
	ON_EVENT(CBenderDlg, IDC_BUTTON_3DPGDN, -600 /* Click */, OnClickButton3dpgdn, VTS_NONE)
	ON_EVENT(CBenderDlg, IDC_BUTTON_DEFAULT, -600 /* Click */, OnClickButtonDefault, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
CBenderDlg::~CBenderDlg()
{
	if(m_pAffirm->GetSafeHwnd() != 0)/* ��綨λ */
	{
        m_pAffirm->DestroyWindow();
	}
	if (m_pAffirm != NULL)
	{
		delete m_pAffirm;
		m_pAffirm = NULL;
	}
	if(m_pHandDlg->GetSafeHwnd() != 0)
	{
        m_pHandDlg->DestroyWindow();
	}
	if (m_pHandDlg != NULL)
	{
		delete m_pHandDlg;
		m_pHandDlg = NULL;
	}
	if(m_pHomeDlg->GetSafeHwnd() != 0)
	{
        m_pHomeDlg->DestroyWindow();
	}
	if (m_pHomeDlg != NULL)
	{
		delete m_pHomeDlg;
		m_pHomeDlg = NULL;
	}

	if (g_pDlgShowExtra->GetSafeHwnd()!=0)	
	{
		g_pDlgShowExtra->DestroyWindow();
	}
	if (g_pDlgShowExtra != NULL)
	{
		delete g_pDlgShowExtra;
		g_pDlgShowExtra = NULL;
	}

	if (m_pTestDlg->GetSafeHwnd()!=0)	
	{
		m_pTestDlg->DestroyWindow();
	}
	if (m_pTestDlg != NULL)
	{
		delete m_pTestDlg;
		m_pTestDlg = NULL;
	}

	if (m_pScanDlg->GetSafeHwnd()!=0)	
	{
		m_pScanDlg->DestroyWindow();
	}
	if (m_pScanDlg != NULL)
	{
		delete m_pScanDlg;
		m_pScanDlg = NULL;
	}
	if (m_brush.GetSafeHandle())
	{
		m_brush.DeleteObject();
	}
	DeleteCriticalSection(&m_Section);
	
}
// CBenderDlg message handlers

BOOL CBenderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Determine if a window with the class name exists...
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	CWnd *pWnd;
	pWnd = FindWindow(NULL,"PNC2000GC");
	if( pWnd != NULL)
		exit(0);
	SetWindowText("PNC2000GC");	
	InitializeCriticalSection(&m_Section);
	m_PVM.m_nShowShelf=GetPrivateProfileInt("SHOW","SHELF",0,INIFILE_ADDEXTRA);		//��ʾ���ܺ�
	m_PVM.Create(this, CRect(17,260,717,703));//
	OnInitOCX();
	OnSystemTimer();
	InitRgnButton();
	OnOpenController();
	if (g_stu_pAxisF->bSpareA == TRUE || g_stu_pAxisA->sSpare==2)//����ͬ��/���ڷ�ʽ
    {
		OpenMsCom();
    }
	OnInitGalil();
	InitScanPara();
	OnInitInput();
	OnInitModenessDlg();
	GetExpandShowInf();
	if (g_stu_pAxisF->bSpareA == TRUE)
	{
		g_Dmcgc.SetDoubleXW(true);			
	}
	else
	{
		g_Dmcgc.SetDoubleXW(false);
	}
	//==========================================================================
    
	m_iReadyTime = GetPrivateProfileInt("TURNOVER","READYTIME",0,INIFILE_ADDEXTRA);		//��Ƭ̨׼��ʱ��
 	m_nSafeSwich = GetPrivateProfileInt("SAFE","SAFESWICH",1,INIFILE_ADDEXTRA);
	
	//���Բ���뾶	
	CString strPara;		
	GetPrivateProfileString("MOTION","MAXRADIUS","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_ADDEXTRA);
    g_Dmcgc.SetMaxRadius(atof(strPara));
    

	//ʵ�ĵ�ͷ���������и�
	BOOL l_bPosNeg = (BOOL)GetPrivateProfileInt("POSNEG","CUTTING",0,INIFILE_ADDEXTRA);	
	g_Dmcgc.SetSolidHead((int)l_bPosNeg);

	char chFile[MAX_PATH];
	GetPrivateProfileString("FILE","FILENAME","",chFile,MAX_PATH,INIFILE_LASTINF);
	g_strShowName = chFile;

	GetPrivateProfileString("FILE","FILELIST","",chFile,MAX_PATH,INIFILE_LASTINF);
    g_strGfile = chFile;
 	/* ����������ã�����������5�� */
	g_AlarmDll.InitDB((char*)((const char*)"D:\\program files\\GlassCutter"));
	g_AlarmDll.SetHisAlmTime(5);
	g_AlarmDll.AddSelfDefAlm(105, 1, (char*)((const char*)"�µ���λ"), (char*)((const char*)"Tool limit"));
	g_AlarmDll.AddSelfDefAlm(108, 1, (char*)((const char*)"ֹͣ"), (char*)((const char*)"Stop"));
	if (g_stu_pAxisF->bSpareA == TRUE || g_stu_pAxisA->sSpare==2)//����ͬ��/���ڷ�ʽ
	{
		g_AlarmDll.AddSelfDefAlm(106, 1, (char*)((const char*)"ѹ����ʼ��ʧ��"), (char*)((const char*)"Pressure error"));
		if (g_stu_pAxisF->bSpareA == TRUE)
			g_AlarmDll.AddSelfDefAlm(107, 1, (char*)((const char*)"˫�������ϴ�"), (char*)((const char*)"Double Axis Error"));
	}
	InitGridInf();
	CString  TempString = g_strOriginalPathC + "G2DMC.TRN";
    if (g_Dmcgc.ReadTranslationTable((char*)((char*)((const char*)TempString))))
		OnShowMessageBox(24,g_iLanguage,FALSE);
    if(0 == GetPrivateProfileInt("FILE","FILEERROR",1,INIFILE_LASTINF))
	{
       FileOpen();//����ļ���ȷ���Զ����ļ�
	}

    CWnd::SetWindowPos(CWnd::GetOwner(), 0, 0, 1024, 768, SWP_SHOWWINDOW);
	m_main9.SelectState(IDB_BITMAP_AUTO3);
	InitRunState();
	InitPrintLabel();
	SetAOorOF(0.0);//̧��ѹ��
	GetSheetCount();//��ʼ��ͼ�θ���
	MachineZeroAlarm(g_iLanguage);  
	SetTimer(1,110,NULL);
	SetTimer(2,1000,NULL);
	SetTimer(6,70,NULL);//ѹ�� 
	SetTimer(10,1000,NULL);//���ܹ�  
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/* ���˶������� */
void CBenderDlg::OnOpenController()
{
	//ע�������
	CDMCWinRegistry DMCWinRegistry;//ע����
	GALILREGISTRY galilregistry;//ע����Ϣ��ר�����ݽṹ��
	if (DMCWinRegistry.GetGalilRegistryInfo(g_nController, &galilregistry) == DMCERROR_CONTROLLER)
	{
		//��ע����Ϣ
		memset(&galilregistry,0,sizeof(galilregistry));
		CHAR    Model[16]="ww-21x3/2";	
		memcpy(galilregistry.szModel,Model,16);
		galilregistry.ulTimeout = 5000;
		galilregistry.usCommPort = 5000;
		galilregistry.fControllerType = 4;//4:����  1������
		CHAR    PNPHardwareKey[64] = "192.168.0.51";
		memcpy(galilregistry.szPNPHardwareKey,PNPHardwareKey,64);
		
		DMCWinRegistry.AddGalilRegistry(&galilregistry,&g_nController);
	}	
	g_lRc = g_Controller.Open(g_nController, GetSafeHwnd());//�򿪿�����
	if(!g_Controller.IsConnected())
	{
		OnShowMessageBox(14,g_iLanguage,FALSE);
	}
// 	else
// 	{
// 		CString strVersion;
// 		char chResponese[80];
// 		g_Controller.Command("MG_BN", chResponese, sizeof(chResponese));
// 		
// 		if(atoi(chResponese)!=60008)
// 		{
// 			if(!g_iLanguage)    	MessageBox("�������汾���ԣ����빩Ӧ����ϵ��","��ʾ",MB_OK);
// 			else					MessageBox("The Wrong controller version, Connect the provider please!","Hint",MB_OK);
// 			theApp.ShutDown();
// 		}
// 	}
	g_Dmcgc.SetController((long)&g_Controller);
}

/* ��ʼ��Ѳ�߲��� */
void CBenderDlg::InitScanPara() 
{
	CString strPara;		
	GetPrivateProfileString("PARA","SCANSPEED","20",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_SCAN);
	g_ScanPara.dScanSpeed = atof(strPara);

	GetPrivateProfileString("PARA","SCANPACE","5",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_SCAN);
	g_ScanPara.dScanPace = atof(strPara);

	GetPrivateProfileString("PARA","SCANBGX","200",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_SCAN);
	g_ScanPara.dScanBeginPosX = atof(strPara);

	GetPrivateProfileString("PARA","SCANBGY","200",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_SCAN);
	g_ScanPara.dScanBeginPosY = atof(strPara);

	GetPrivateProfileString("PARA","SCANMIDX","500",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_SCAN);
	g_ScanPara.dScanCenterPosX = atof(strPara);

	GetPrivateProfileString("PARA","SCANMIDY","500",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_SCAN);
	g_ScanPara.dScanCenterPosY = atof(strPara);
}

void CBenderDlg::OnInitModenessDlg()
{
	m_pAffirm = new CDlg_affirm(this);/* ��綨λ */
	g_pDlgShowExtra =new Cdlg_ShowExtra(this);
	m_pHandDlg = new dlg_hand(this);
	m_pHomeDlg = new CDlg_Home(this);
	if (m_pTestDlg == NULL)
	{
		m_pTestDlg = new CCTest();
	}
	if (m_pScanDlg == NULL)
	{
		m_pScanDlg = new CDlg_scan();
	}
	
}

void CBenderDlg::OnInitGalil()
{
	g_handdll.handInit((long)(&g_Controller));
	g_systemdll.SetController((long)(&g_Controller));
	g_Controller.Command("CN,-1;CO7;VR1;SH;SB25;SB17");
	
	if(g_stu_pAxisF->bSpareA == TRUE)//����ͬ��
	{
		g_Controller.Command("GA,,,CX;GR0,0,0,1;GM1,,,1;OE1,1,1,1");
	}
	else
	{
		g_Controller.Command("GR0,,,0;OE1,1,1");
	}
	InitSoftLimit();	
	CString sz;
	char szCmd[80]={0};
	int nAdjust = GetPrivateProfileInt("ADJUST","TPWVALUE",0,INIFILE_ADDEXTRA);
	int nX2Move = GetPrivateProfileInt("ADJUST","X2MOVE",0,INIFILE_ADDEXTRA);
	int nLeaveTime = GetPrivateProfileInt("WATER","LEAVETIME",0,INIFILE_ADDEXTRA);
	int nPosTime = GetPrivateProfileInt("LIGHTPAR","POSTIME",2000,INIFILE_ADDEXTRA);
	sprintf(szCmd,"M1=%d;M2=%d;VT%.3f;detime=%.0f;leavet=%d;postime=%d",
		nAdjust,nX2Move,g_stu_pAxisG->dSpareD,g_stu_pAxisF->dSpareE,nLeaveTime,nPosTime);
	g_Controller.Command(szCmd);
	//��ˮ�и�ʹ�������ʱ�䣬Ȼ��ʼ����
	int nUpTime = GetPrivateProfileInt("WATER","UPTIME",0,INIFILE_ADDEXTRA);
    memset(szCmd,0,sizeof(szCmd));
	sprintf(szCmd,"uptime=%d",nUpTime);
	g_Controller.Command(szCmd);

    SetInitAutoSpeed();
	g_handdll.ResolutionSet(g_stu_pAxisA->d_pulse_user, g_stu_pAxisB->d_pulse_user, g_stu_pAxisC->d_pulse_user, g_stu_pAxisD->d_pulse_user); 
	g_handdll.handSpeedSet(g_stu_pAxisA->d_handspeed, g_stu_pAxisB->d_handspeed, g_stu_pAxisC->d_handspeed, g_stu_pAxisD->d_handspeed); 
	g_handdll.handSpeedACSet(g_stu_pAxisA->d_acc, g_stu_pAxisB->d_acc, g_stu_pAxisC->d_acc, g_stu_pAxisD->d_acc); 
	g_handdll.handSpeedDCSet(g_stu_pAxisA->d_dec, g_stu_pAxisB->d_dec, g_stu_pAxisC->d_dec, g_stu_pAxisD->d_dec); 
	g_handdll.SetJourneyPositive(g_stu_pAxisA->l_Journey_positive - g_fCurrMachineX, g_stu_pAxisB->l_Journey_positive - g_fCurrMachineY, g_stu_pAxisC->l_Journey_positive, g_stu_pAxisD->l_Journey_positive);
	g_handdll.SetJourneyNegetive(g_stu_pAxisA->l_Journey_negative - g_fCurrMachineX, g_stu_pAxisB->l_Journey_negative - g_fCurrMachineY, g_stu_pAxisC->l_Journey_negative, g_stu_pAxisD->l_Journey_negative);
    OnMachineBK();/* ִ�м�϶���� */
	g_Dmcgc.SetServoControl(g_stu_pAxisA->sSpare);
	SetFindLightSpeed();
	g_Dmcgc.SetMsgWnd(GetSafeOwner());
	//��ʼ������״̬
	g_Controller.Command("homecx=0;homecy=0;homecz=0;ST;STS;CSS",g_szResponse,sizeof(g_szResponse));
	InitRPShow();
	Sleep(100);
}

void CBenderDlg::OnInitOCX()
{
	CString	str;
	DWORD crBK = BACKCOLOR;

	m_captionFile.SetBmpPathName("D:\\program files\\GlassCutter\\bitmap\\filename.bmp");
    ((CCaptionInfo *)(GetDlgItem(IDC_CAPTIONINFO_CONTROL)))->SetBmpPathName("D:\\program files\\GlassCutter\\bitmap\\gray.bmp");
    ((CCaptionInfo *)(GetDlgItem(IDC_CAPTIONINFO_RUN)))->SetBmpPathName("D:\\program files\\GlassCutter\\bitmap\\gray.bmp");
    ((CCaptionInfo *)(GetDlgItem(IDC_CAPTIONINFO_FILE)))->SetBmpPathName("D:\\program files\\GlassCutter\\bitmap\\gray.bmp");
    ((CCaptionInfo *)(GetDlgItem(IDC_CAPTIONINFO_TITLE)))->SetBmpPathName("D:\\program files\\GlassCutter\\bitmap\\head.bmp");

	if(g_stu_pAxisF->bSpareA == TRUE)//����ͬ��
		m_CapTitle.SetCaption("V6.7.7D");
	else
		m_CapTitle.SetCaption("V6.7.7");


#ifdef POWERLAND
    crBK = RGB(165,198,248);
#endif	
	m_ocxDisplay.SetDisplayCount(6);
	m_ocxDisplay.SetBackColor(crBK);	
	m_LedX.SetRgby(1);//��ɫ
	m_LedY.SetRgby(1);
	m_LedZ.SetRgby(1);

#ifndef POWERLAND
	{    
		m_LedX.SetDisplayBmp(TRUE);
        m_LedY.SetDisplayBmp(TRUE);
        m_LedZ.SetDisplayBmp(TRUE);
	}
#else
	{
		m_LedX.SetDisplayBmp(FALSE);
        m_LedY.SetDisplayBmp(FALSE);
        m_LedZ.SetDisplayBmp(FALSE);
		m_LedX.SetBackColor(crBK);
		m_LedY.SetBackColor(crBK);
		m_LedZ.SetBackColor(crBK);		
	}
#endif
	/* �����ٶȽ����� */   
	m_ocxPlanSpeed.SetMax(120);
    m_ocxPlanSpeed.SetMin(0);
    m_ocxPlanSpeed.SetBackColor(crBK);
	m_ocxPlanSpeed.SetForeColor(RGB(19, 119, 11));//����ǰ����ɫΪī��ɫ
    m_ocxPlanSpeed.SetScaleColor(RGB(117, 36, 58));
    m_ocxPlanSpeed.SetPlanColor(RGB(170, 0, 0));
	m_ocxPlanSpeed.SetValue(100);

	m_ocxPlanPress.SetBackColor(crBK);
	m_ocxPlanPress.SetForeColor(RGB(19, 119, 11));//����ǰ����ɫΪī��ɫ
    m_ocxPlanPress.SetScaleColor(RGB(117, 36, 58));
    m_ocxPlanPress.SetPlanColor(RGB(170, 0, 0));
	g_CutPress.SetPressureFile((char *)((const char*)m_strPressFile));
	g_CutPress.ReadPressure();
//����
	if (g_iLanguage == 0)
	{
		if (g_stu_pAxisH->sSpare==0)
		{
			SetDlgItemText(IDC_CAPTIONINFO_CONTROL,"MSC               λ��[mm]    ����[m/min]");
		} 
		else
		{
			SetDlgItemText(IDC_CAPTIONINFO_CONTROL,"MSC               λ��[in]    ����[in/min]");
		}
		if(g_stu_pAxisF->bSpareA == TRUE)//����ͬ��
		{
			SetDlgItemText(IDC_CAPTIONINFO_RUN,"����״̬    ˫����ʽ         �и�");
		}
		else
		{
	    	SetDlgItemText(IDC_CAPTIONINFO_RUN,"����״̬                     �и�");
		}
		SetDlgItemText(IDC_CAPTIONINFO_FILE,"����״̬               ����");
		m_BtnMin.SetTipMsg("��С��");
		CBtnCtl *pBtnCtl = NULL;
		pBtnCtl = (CBtnCtl *)(GetDlgItem(IDC_BUTTON_3DUP));
		pBtnCtl->SetTipMsg("����");
		pBtnCtl = (CBtnCtl *)(GetDlgItem(IDC_BUTTON_3DDOWN));
		pBtnCtl->SetTipMsg("����");
		pBtnCtl = (CBtnCtl *)(GetDlgItem(IDC_BUTTON_3DLEFT));
		pBtnCtl->SetTipMsg("����");
		pBtnCtl = (CBtnCtl *)(GetDlgItem(IDC_BUTTON_3DRIGHT));
		pBtnCtl->SetTipMsg("����");
		pBtnCtl = (CBtnCtl *)(GetDlgItem(IDC_BUTTON_3DPGUP));
		pBtnCtl->SetTipMsg("�Ŵ�");
		pBtnCtl = (CBtnCtl *)(GetDlgItem(IDC_BUTTON_3DPGDN));
		pBtnCtl->SetTipMsg("��С");
		pBtnCtl = (CBtnCtl *)(GetDlgItem(IDC_BUTTON_DEFAULT));
		pBtnCtl->SetTipMsg("��ԭ");
	} 
	else
	{
		if (g_stu_pAxisH->sSpare==0)
		{
			SetDlgItemText(IDC_CAPTIONINFO_CONTROL,"MSC               POS[mm]     FEED[m/min]");
		} 
		else
		{
			SetDlgItemText(IDC_CAPTIONINFO_CONTROL,"MSC               POS[in]     FEED[in/min]");
		}
		if(g_stu_pAxisF->bSpareA == TRUE)//����ͬ��
		{
			SetDlgItemText(IDC_CAPTIONINFO_RUN,"Run State Dual drive   Cut");
		}
		else
		{
			SetDlgItemText(IDC_CAPTIONINFO_RUN,"Run State              Cut");
		}
		SetDlgItemText(IDC_CAPTIONINFO_FILE,"Work State         Normal");
		m_BtnMin.SetTipMsg("Min");
		CBtnCtl *pBtnCtl = NULL;
		pBtnCtl = (CBtnCtl *)(GetDlgItem(IDC_BUTTON_3DUP));
		pBtnCtl->SetTipMsg("Up");
		pBtnCtl = (CBtnCtl *)(GetDlgItem(IDC_BUTTON_3DDOWN));
		pBtnCtl->SetTipMsg("Down");
		pBtnCtl = (CBtnCtl *)(GetDlgItem(IDC_BUTTON_3DLEFT));
		pBtnCtl->SetTipMsg("Left");
		pBtnCtl = (CBtnCtl *)(GetDlgItem(IDC_BUTTON_3DRIGHT));
		pBtnCtl->SetTipMsg("Right");
		pBtnCtl = (CBtnCtl *)(GetDlgItem(IDC_BUTTON_3DPGUP));
		pBtnCtl->SetTipMsg("Out");
		pBtnCtl = (CBtnCtl *)(GetDlgItem(IDC_BUTTON_3DPGDN));
		pBtnCtl->SetTipMsg("In");
		pBtnCtl = (CBtnCtl *)(GetDlgItem(IDC_BUTTON_DEFAULT));
		pBtnCtl->SetTipMsg("Zoom");

		SetDlgItemText(IDC_RADIO1,"Along");
		SetDlgItemText(IDC_RADIO2,"Double");
		SetDlgItemText(IDC_RADIO3,"Three");
	}
}

void CBenderDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{ 
		//������ͼƬ
 		CPaintDC dc(this);
		CDC  MemDc;
		CBitmap bitmap;	
		MemDc.CreateCompatibleDC(&dc);
		bitmap.LoadBitmap(IDB_BITMAP_BK);
		CBitmap *pOldBit = MemDc.SelectObject(&bitmap);
		if (g_Dmcgc.GetDmcNumber() != NULL)
		{
			DrawRules(&MemDc);
		}
		dc.BitBlt(0,0,1024,768,&MemDc,0,0,SRCCOPY);
		MemDc.SelectObject(pOldBit);
		bitmap.DeleteObject();
	    MemDc.DeleteDC();
		CDialog::OnPaint();
	}
}

void CBenderDlg::OnButton1() /* �ļ� */
{
	if(g_Dmcgc.GetRunflag())     
		return;
	m_bDlgPath = TRUE;//�����ť��ʱ
	FileOpen();
}

void CBenderDlg::OnButton9() //�Զ�
{
	if(g_Dmcgc.GetRunflag())     return;
	if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1)			
	{
		OnShowMessageBox(22,g_iLanguage,FALSE);
		return;
	}	
	if(g_iMode == MODE_C)
	{
		if (m_pHandDlg->GetSafeHwnd()!=0)
		{			
			m_pHandDlg->ShowWindow(SW_HIDE);			
		}	
		m_ocxPlanSpeed.SetValue(g_Dmcgc.GetRate());
		m_ocxPlanPress.SetValue(g_stu_pAxisF->dSpareC);
		SetAOorOF(g_stu_pAxisF->dSpareC);
        g_handdll.SetOut(OUT_ZAXIS_DN,FALSE);
		g_iMode = MODE_MAIN;
		m_main9.SelectState(IDB_BITMAP_AUTO3);
		m_main3.SelectState(0);		
	}
	else if (MODE_D == g_iMode)
	{
		if(g_stu_pAxisF->bSpareA == TRUE)//����ͬ��
		{
			g_Controller.Command("ST");
			Sleep(50);
			g_Controller.Command("GA,,,CX;GR0,,,1;GM1,,,1");
			Sleep(50);
		}
		if (m_pHomeDlg->GetSafeHwnd()!=0)
		{			
			m_pHomeDlg->ShowWindow(SW_HIDE);
			g_iMode = MODE_MAIN;
			m_main9.SelectState(IDB_BITMAP_AUTO3);
			m_main4.SelectState(0);	
			char szResponse[80]={0};
			if (g_fCurrMachineX!=0.0)
			{
				g_Controller.Command("MachX=",szResponse,sizeof(szResponse));
				if (atoi(szResponse) == 0)
				{
					g_fCurrMachineX = 0.0;
				}
			}
			if (g_fCurrMachineY != 0.0)
			{
				g_Controller.Command("MachY=",szResponse,sizeof(szResponse));
				if (atoi(szResponse) == 0)
				{
					g_fCurrMachineY = 0.0;
				}
			}
		}
	}
}

void CBenderDlg::OnButton3() /* �ֶ� */
{
	if(g_Dmcgc.GetRunflag())     return;
	if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1)			
	{
		OnShowMessageBox(22,g_iLanguage,FALSE);
		return;
	}	
	if (MODE_MAIN == g_iMode)
	{
		if (m_pHandDlg->GetSafeHwnd()==0)
		{
			m_pHandDlg->Create(IDD_DIALOG_HAND, this);
		}
		m_pHandDlg->ShowWindow(SW_SHOW);
		g_iMode = MODE_C;
		OnInitHandPressure(); /* ��ʼ���ֶ��µ�ѹ�� */
		m_pHandDlg->OpenDlgInit();
		m_ocxPlanSpeed.SetValue((float)g_handdll.GetHandRate());
		g_handdll.SetHandRateSpeed(g_handdll.GetHandRate());
		m_main3.SelectState(IDB_BITMAP_HAND3);
		m_main9.SelectState(0);		
	}
	else if (MODE_D == g_iMode)
	{
		if(g_stu_pAxisF->bSpareA == TRUE)//����ͬ��
		{
			g_Controller.Command("ST");
			Sleep(50);
			g_Controller.Command("GA,,,CX;GR0,,,1;GM1,,,1");
			Sleep(50);
		}
		if (m_pHandDlg->GetSafeHwnd()==0)
		{
			m_pHandDlg->Create(IDD_DIALOG_HAND, this);
		}
		else
		{
			char szResponse[80]={0};
			if (g_fCurrMachineX!=0.0)
			{
				g_Controller.Command("MachX=",szResponse,sizeof(szResponse));
				if (atoi(szResponse) == 0)
				{
					g_fCurrMachineX = 0.0;
				}
			}
			if (g_fCurrMachineY != 0.0)
			{
				g_Controller.Command("MachY=",szResponse,sizeof(szResponse));
				if (atoi(szResponse) == 0)
				{
					g_fCurrMachineY = 0.0;
				}
			}
		}
		m_pHandDlg->ShowWindow(SW_SHOW);
		g_iMode = MODE_C;
		OnInitHandPressure(); /* ��ʼ���ֶ��µ�ѹ�� */
		m_pHandDlg->OpenDlgInit();
		m_ocxPlanSpeed.SetValue((float)g_handdll.GetHandRate());
		g_handdll.SetHandRateSpeed(g_handdll.GetHandRate());
		if (m_pHomeDlg->GetSafeHwnd()!=0)
		{
			m_pHomeDlg->ShowWindow(SW_HIDE);
		}
		m_main3.SelectState(IDB_BITMAP_HAND3);
		m_main4.SelectState(0);	
	}
}

void CBenderDlg::OnButton4() /* ���� */
{	
	if(g_Dmcgc.GetRunflag())     
		return;
	if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1)			
	{
		OnShowMessageBox(22,g_iLanguage,FALSE);
		return;
	}
	if (m_pHomeDlg->GetSafeHwnd()==0)
	{
		g_iMode = MODE_D;		
		m_pHomeDlg->Create(IDD_DIALOG_HOME, this);
		m_pHomeDlg->OpenDlgInit();
		m_main4.SelectState(IDB_BITMAP_HOME3);
		m_main3.SelectState(0);	
		m_main9.SelectState(0);	
	}
	else
	{
		g_iMode = MODE_D;
		m_pHomeDlg->ShowWindow(SW_SHOW);
		m_pHomeDlg->OpenDlgInit();
		m_main4.SelectState(IDB_BITMAP_HOME3);
		m_main9.SelectState(0);	
	}
	m_ocxPlanSpeed.SetValue(100.0f);
	if (m_pHandDlg->GetSafeHwnd()!=0)
	{
		m_pHandDlg->ShowWindow(SW_HIDE);
		m_main3.SelectState(0);	
	}
}

void CBenderDlg::OnButton5() //����
{
	if(g_Dmcgc.GetRunflag())     
		return;
	CString		strtemp;
	if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1
		||g_handdll.GetCommandFloat((char *)((const char*)"MG_XQ"))>=0.0)	
	{
		OnShowMessageBox(22,g_iLanguage,FALSE);
		return;
	}
	dlg_motion  motion;
	if(motion.DoModal()==IDOK)
	{		
		SetInitAutoSpeed();
		strtemp.Format("%d",g_nProduct);
		m_listGrid.SetItemText(1,1,strtemp);
		SetTimer(4,30,NULL);	
	}
	else
	{
		strtemp.Format("%d",g_nProduct);
		m_listGrid.SetItemText(1,1,strtemp);
	}
}

void CBenderDlg::OnButton6() //�Ż�
{
	if(g_Dmcgc.GetRunflag())     
		return;
	if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1)			
	{
		OnShowMessageBox(22,g_iLanguage,FALSE);
		return;
	}
	if(g_stu_pAxisE->bSpare)/* �Ƿ����Ż����� */
	{
		g_iMode = MODE_E;
// 		CGraphDlg dlg;			
// 		if(IDOK == dlg.DoModal())
// 		{
// 			m_captionFile.SetWindowText(g_strShowName); 
// 			m_bFile = TRUE;
// 			FileOpen();		
// 		}
		CRectOptDlg dlg;
		if (IDOK == dlg.DoModal())
		{
 			m_captionFile.SetWindowText(g_strShowName); 
 			m_bFile = TRUE;
 			FileOpen();		
		}
		g_iMode = MODE_MAIN;			
	}	
}

void CBenderDlg::OnButton7() /* �༭ */
{
	if(g_Dmcgc.GetRunflag())     
		return;
	if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1
		||g_handdll.GetCommandFloat((char *)((const char*)"MG_XQ"))>=0.0)	
	{
		OnShowMessageBox(22,g_iLanguage,FALSE);
		return;
	}
	g_iMode = MODE_E;
	CDlg_bottero	var;
	m_PVM.RestoreDisplay();
	g_Dmcgc.SetGlassPlacePos(0,1,0,0,1,0);
	double dXY = ((double)g_stu_pAxisB->sSpareA/(double)g_stu_pAxisB->sSpareB);//��������
	if (dXY > 1.56)
    {
		m_PVM.SetMaxShow(690.0/g_stu_pAxisB->sSpareA);
    }
	else
	{
		m_PVM.SetMaxShow(430.0/g_stu_pAxisB->sSpareB);
	}
	OnInit2DDrawShow();
	if(IDOK == var.DoModal())
	{
		m_captionFile.SetWindowText(g_strShowName); 
		m_bFile = TRUE;
		FileOpen();
	}
	g_iMode = MODE_MAIN;		
}

//�и�������л�
void CBenderDlg::OnButton8()
{
	if (g_iMode == MODE_MAIN)
	{
		if(g_Dmcgc.GetRunflag())
		{
			if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==0)	
			{
				return;
			}
		}
 
		if (g_nRunState == 1)//������
		{
			g_nRunState = 0;
			g_Dmcgc.SetRunOption(g_nRunState, g_stu_pAxisA->bSpareA);			
			if (g_iLanguage == 0)
			{
				if(g_stu_pAxisF->bSpareA == TRUE)//����ͬ��
				{
					SetDlgItemText(IDC_CAPTIONINFO_RUN,"����״̬    ˫����ʽ         �и�");
				}
				else
				{
					SetDlgItemText(IDC_CAPTIONINFO_RUN,"����״̬                     �и�");
				}
				m_main8.SetWindowText("�и�");
			}
			else
			{
				if(g_stu_pAxisF->bSpareA == TRUE)//����ͬ��
				{
					SetDlgItemText(IDC_CAPTIONINFO_RUN,"Run State Dual drive   Cut");
				}
				else
				{
					SetDlgItemText(IDC_CAPTIONINFO_RUN,"Run State              Cut");
				}
				m_main8.SetWindowText("Cut");
			}
			m_main8.SelectState(NULL);

		}
		else//�и�
		{
			g_nRunState = 1;
			/* ������ʱ,�ص��µ���ע�� */ 
			g_handdll.SetOut(OUT_ZAXIS_DN,FALSE);//C���µ�
			g_handdll.SetOut(OUT_ZAXIS_DN1,FALSE);
			SetAOorOF(g_stu_pAxisF->dSpareC);
			g_handdll.SetOut(OUT_OILING,FALSE);//ע��
			g_handdll.SetOut(OUT_CUT_OILING,FALSE);//�и�ע��	
			g_Dmcgc.SetRunOption(g_nRunState, g_stu_pAxisA->bSpareA);
			if (g_iLanguage == 0)
			{
				if(g_stu_pAxisF->bSpareA == TRUE)//����ͬ��
				{
					SetDlgItemText(IDC_CAPTIONINFO_RUN,"����״̬    ˫����ʽ         ģ��");
				}
				else
				{
					SetDlgItemText(IDC_CAPTIONINFO_RUN,"����״̬                     ģ��");
				}
				m_main8.SetWindowText("ģ��");
			}
			else
			{
				if(g_stu_pAxisF->bSpareA == TRUE)//����ͬ��
				{
					SetDlgItemText(IDC_CAPTIONINFO_RUN,"Run State Dual drive   Demo");
				}
				else
				{
					SetDlgItemText(IDC_CAPTIONINFO_RUN,"Run State              Demo");
				}

				m_main8.SetWindowText("Demo");
			}
			m_main8.SelectState(IDB_BITMAP_NULL3);
		}
	}
}

void CBenderDlg::OnExit()
{
	if(OnShowMessageBox(41,g_iLanguage)==IDYES)
	{
		/* ����λ����FLBL */
		KillTimer(1);				KillTimer(2);		
		KillTimer(3);				KillTimer(6);		
		KillTimer(8);		
		if(g_Dmcgc.GetRunflag())
		{
			g_Dmcgc.OnReset();
			//�޸ĵ��Ժ�ı��ʼ״̬
			g_lRc = g_Controller.Command("OP0,0,0");
		}
		CDialog::OnOK();
	//*	
		BOOL fResult;
		TOKEN_PRIVILEGES tkp;
		HANDLE hToken;   
		
		if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))    
		{   
			AfxMessageBox("OpenProcessToken failed!");   
		}   
		
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid); //��ñ��ػ�Ψһ�ı�ʶ   
		tkp.PrivilegeCount = 1;     
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;    
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,(PTOKEN_PRIVILEGES) NULL, 0); //������õ�Ȩ��   
		
		if (GetLastError() != ERROR_SUCCESS)    
		{   
			AfxMessageBox("AdjustTokenPrivileges enable failed!");   
		}   
		
		fResult =InitiateSystemShutdown(    
			NULL,                                  // Ҫ�صļ�����û���   
			"WINDOWS����0���ػ��������ñ��湤��!",  // ��ʾ����Ϣ   
			0,                                    // �ػ������ʱ��   
			TRUE,                                 // ask user to close apps    
			FALSE);                               //��ΪTRUEΪ������ΪFALSEΪ�ػ�   
		if(!fResult)    
		{    
			AfxMessageBox("InitiateSystemShutdown failed.");    
		}
	}
}

void CBenderDlg::FileOpen()//G��������.
{
    EnterCriticalSection(&m_Section);
	int     nHandOpenFile=0;//ͨ���ֶ��ļ���1
	//�����ť��ʱ
	if (m_bDlgPath)
	{
		m_bDlgPath = FALSE;
		dlg_path2  dlgPath;
		if (IDCANCEL == dlgPath.DoModal())	
		{
			LeaveCriticalSection(&m_Section);
			return;
		}
		nHandOpenFile = 1;
	}
	
	pCoorx.x = 0;		pCoorx.y = 1;
	pCoor.x = 0;		pCoor.y = 0;
	pCoory.x = 1;		pCoory.y = 0;
 	g_Dmcgc.SetCncOption(0);/* ����˫��G���룬Ҫת�� */

	WritePrivateProfileString("FILE","FILENAME",g_strShowName,INIFILE_LASTINF);
	WritePrivateProfileString("FILE","FILELIST",g_strGfile,INIFILE_LASTINF);
	WritePrivateProfileString("FILE","FILEERROR","1",INIFILE_LASTINF);

 	if(strstr(g_strGfile,".dxf")||strstr(g_strGfile,".DXF")||strstr(g_strGfile,".cxf")||strstr(g_strGfile,".CXF"))
	{
		DxftoG.SetSortOrder(g_stu_pAxisD->bSpare, g_stu_pAxisD->bSpareA, (int)g_stu_pAxisE->sSpare);
		int nDxf = DxftoG.SetInputFile((char*)((const char*)g_strGfile));
		
		if(nDxf>0)
		{
			if(!g_iLanguage)
				AfxMessageBox("�汾�Ų��ԣ���ʹ��R12���DXF�ļ���");
			else
				AfxMessageBox("File Version Error,Plase Change To R12 Dxf File!");
			LeaveCriticalSection(&m_Section);
			return;
		}

		if(g_stu_pAxisA->bSpareA)	/* ע�� */
		{
			DxftoG.SetDownOperation("M13\n");
			DxftoG.SetUpOperation("M14\n");
		}
		else						/* ��ע�� */
		{
			DxftoG.SetDownOperation("M09\n");
			DxftoG.SetUpOperation("M10\n");
		}
		if(g_stu_pAxisG->bSpare)	/* �Ƿ��Զ�ѭ�� */
		{
			DxftoG.SetHeadTailHomeOperation("M25\nM23","M24\nM26","G90G00X0Y0Z0\nM99");
		}
		else
		{
			DxftoG.SetHeadTailHomeOperation("M25\nM23","M24\nM26","G90G00X0Y0Z0");
		}
		CString strOpenDxf = g_strGfile;
        g_strGfile = g_strOriginalPathC + "dxf.g";
		DxftoG.SetOutputFile((char*)((const char*)g_strGfile));
    	GCodeOpen(g_strGfile);
		strGCodeOpenFile = g_strGfile;
		m_captionFile.SetWindowText(g_strShowName); 
		g_strGfile = strOpenDxf;

	}
	else if(strstr(g_strGfile,".g")||strstr(g_strGfile,".G"))
	{
		GCodeOpen(g_strGfile);
		strGCodeOpenFile = g_strGfile;
		m_captionFile.SetWindowText(g_strShowName);
	}	
	m_bEmreStop = FALSE;
	WritePrivateProfileString("FILE","FILEERROR","0",INIFILE_LASTINF);
	pstu_Currdmc = g_Dmcgc.GetDmcNumber();

	if(g_stu_pAxisB->bSpare)
	{
		if (!m_bContiueRun)//������ˮ�и��ٴδ��ļ�
		{
			m_iRunNum = 0;
			OnPrepare(3);
		}
		else
		{
			m_bContiueRun = FALSE;
		}
	}
	m_rctOrig = m_rct;//����ԭʼ�ĳߴ�
	CString	str;
	str.Format("%.d * %.d",m_rct.right, m_rct.top);
    m_listGrid.SetItemText(0,1,str);
	if(nHandOpenFile == 1 || m_bFile)
	{
		m_bFile = FALSE;
		CopyPreShowInf(); //������չ��ʾ�����ݽṹ
		ShowExpand();
		if (g_pDlgShowExtra->GetSafeHwnd()!=NULL)
		{
			g_pDlgShowExtra->Invalidate(TRUE);
		}
		GetSheetCount();
	}
	if(m_bFirstOpen)//��һ�δ��ļ�
	{
		CopyPreShowInf(); //������չ��ʾ�����ݽṹ
		ShowExpand();
		m_iSetNum = GetPrivateProfileInt("FILE","TOTAL",1,INIFILE_LASTINF);//�趨�ӹ�����
		m_iRunNum = GetPrivateProfileInt("FILE","PROCESS",0,INIFILE_LASTINF);//����ɼӹ�����
		m_bFirstOpen = FALSE;
	}
	else
	{
		WritePrivateProfileString("RESUME","INTER","0","D:\\Program files\\GlassCutter\\Resume.ini");
	}
	if ((g_stu_pAxisF->bSpareA==TRUE||g_stu_pAxisA->sSpare==2)&& m_MscComm.GetPortOpen() == FALSE)
	{
		g_AlarmDll.SetAlarm(106);
	}
	LeaveCriticalSection(&m_Section);


}

void CBenderDlg::GCodeOpen(CString gCode)  /* G����� */
{
	CString			str;
	int				i;
	
    g_strDmcfile = g_strOriginalPathC+"glass.dmc";
    for(i=0;i<5110;i++)		
	{
		g_arr_strGline[i] = "";
	}	
	ResetCS(gCode,g_strDmcfile);//G����ת��gCode
}

void CBenderDlg::ResetCS(CString gCode,CString dmcCode)  /*  �Զ�����ת�� */
{
	if(g_stu_pAxisA->bSpare)
	{
		g_Dmcgc.SetGlassPlacePos(pCoorx.x,pCoorx.y,pCoor.x,pCoor.y,pCoory.x,pCoory.y);
		//g_Dmcgc.SetGlassPlacePos(0,1,100,100,1,0);
		SaveLightPar();//���沣����綨λ�Ժ��ƫ�Ʋ���
	}
	else						
		g_Dmcgc.SetGlassPlacePos(0,1,0,0,1,0);
	//		g_Dmcgc.SetGlassPlacePos(100,100,100,100,1,1);
	/* ���ø���ѹ�����޸����ɵ�DMC���� */
	PCURRENTSTATE pCurrentState = g_Dmcgc.GetCurrentStatePtr();
    ASSERT(pCurrentState);
    CString  TempString = g_strOriginalPathD + "G2DMC.INI";
    g_Dmcgc.ResetCurrentState((char*)((const char*)TempString));
	
	pCurrentState->chScale = g_stu_pAxisH->sSpare;               //��Ӣ��ת��
	pCurrentState->fResolution.X = g_stu_pAxisA->d_pulse_user;   //���嵱��
	pCurrentState->fResolution.Y = g_stu_pAxisB->d_pulse_user;
	pCurrentState->fResolution.Z = g_stu_pAxisC->d_pulse_user;
	pCurrentState->fFeedRate = g_stu_pAxisA->d_feedrate;         //�岹�ٶ����ٶ�
	pCurrentState->fRapidMoveSpeed = g_stu_pAxisA->d_rapid;      //��λ�ٶ�
	pCurrentState->fAcceleration = g_stu_pAxisA->d_vacc;         //�岹���ٶ�
	pCurrentState->fDeceleration = g_stu_pAxisA->d_vdec;         //�岹���ٶ�
    pCurrentState->usMaxCornerAngle = g_stu_pAxisA->dSpareD;     //���սǽǶ�
	pCurrentState->usCornerAngle = g_stu_pAxisB->dSpareD;        //��С�սǽǶ�
    pCurrentState->fMinCornerSpeed = g_stu_pAxisC->dSpareD;      //��С�ս��ٶ�
    pCurrentState->fMinArcSpeed = g_stu_pAxisD->dSpareD;         //��СԲ���ٶ�
	pCurrentState->fMinArcRadius = g_stu_pAxisE->dSpareD;        //��СԲ���뾶
    pCurrentState->fTangentAxisZeroAngle = g_stu_pAxisF->dSpareD; //����ƫ��
	pCurrentState->usAxes = 2;
	pCurrentState->chPosition = POSITION_ABSOLUTE;		
	g_Dmcgc.SetKnifeOffset(g_stu_pAxisG->dSpareA,g_stu_pAxisH->dSpareA);
	g_Dmcgc.SetAheadDis(g_stu_pAxisC->dSpareE);
	if (!gCode.IsEmpty())
	{
		AfxGetApp()->DoWaitCursor(1);		
		g_Dmcgc.GCodes2DMCs((char*)((const char*)gCode), (char*)((const char*)dmcCode));
		AfxGetApp()->DoWaitCursor(-1);
		WritePrivateProfileString("FILEOPEN","NO","177","D:\\program files\\GlassCutter\\Error.ini");
		OnProgramBoxG();//����켣�ĳߴ�
		WritePrivateProfileString("FILEOPEN","NO","178","D:\\program files\\GlassCutter\\Error.ini");
		CalculateZoom();//ȫ����ʾ
		WritePrivateProfileString("FILEOPEN","NO","179","D:\\program files\\GlassCutter\\Error.ini");
		m_PVM.CalGreen();//���ɻ�ͼ���ݽṹ
		m_PVM.FreeBlocks(); //��άͼ��ˢ��
		WritePrivateProfileString("FILEOPEN","NO","180","D:\\program files\\GlassCutter\\Error.ini");
        if (m_nOpenLight == 0)//���û��Ѳ�߸�����ʾ���ݽṹ
        {
			m_PVM.SaveFileOpenGreen();
        }   	
		if (g_lRc)      return;
		WritePrivateProfileString("FILEOPEN","NO","181","D:\\program files\\GlassCutter\\Error.ini");

	}	
} 

void CBenderDlg::OnTimer(UINT nIDEvent) 
{
	CString				str;
	switch (nIDEvent)
	{
	case 1:    //100    
        OnErnInButton();
		SetManometer();
		OnReadOutput();
		OnTVShow();
		break;
	case 2://1000
		OnSystemTimer();
		ShowAlarm();
		break;
	case 4://���ñ���������ͼ�Σ��ö�ʱ����ֹ���濨
		KillTimer(4);
		FileOpen();
		break;
	case 5:
		OnRunTimeCount();
		break;
	case 6: 
		if(g_iMode == MODE_MAIN)     
		{
			OnShowLine();
		}
		break;
	case 7://������������һƬ��Ƭ���򣬳������ˢ����չ��
		{
			if (g_handdll.EmergencyState()==1)//��ͣ
			{
				KillTimer(7);
				break;
			}
			if (m_bRunFlag==FALSE)
			{
				KillTimer(7);
				break;
			}
			if(g_handdll.GetIn(IN_STOP) == 0)
			{
				KillTimer(7);
				break;
			}			
			int nXQ = g_handdll.GetCommandInt((char *)((const char*)"MG_XQ"));
			if (nXQ < 0)
			{
				KillTimer(7);
				ShowExpand();
				JudgeLastFile();	
			}
			
		}
		break;
	case 10://���ܹ�
	    /*
	    m_nTimer10++;
	    		if(m_nTimer10 == 60)//Ĭ����60
	    		{
	    			KillTimer(10);
	    			GetHarddogTime(0);			    			
	    		}*/
	    
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CBenderDlg::SetManometer() /*ѹ����ʾ */
{
    char chRes[80]={0};
	LONG lControl = g_Controller.Command("ao=",chRes,sizeof(chRes));
	if (g_iLanguage == 0)
	{
		if(lControl == 0)
		{   
			if (!m_bNormal)
			{
				m_bNormal = true;
				SetDlgItemText(IDC_CAPTIONINFO_FILE,"����״̬           ����");
				((CCaptionInfo*)GetDlgItem(IDC_CAPTIONINFO_FILE))->SetForeColor(RGB(0,0,0));
			}
		}
		else
		{
			if (m_bNormal)
			{
				m_bNormal = false;
				SetDlgItemText(IDC_CAPTIONINFO_FILE,"����״̬       ͨ�Ŵ���");
				((CCaptionInfo*)GetDlgItem(IDC_CAPTIONINFO_FILE))->SetForeColor(RGB(255,0,0));
			}
		}
	} 
	else
	{
		if(lControl == 0)
		{
			if (!m_bNormal)
			{
				m_bNormal = true;
				SetDlgItemText(IDC_CAPTIONINFO_FILE,"Work State         Normal");
				((CCaptionInfo*)GetDlgItem(IDC_CAPTIONINFO_FILE))->SetForeColor(RGB(0,0,0));
			}
		}
		else
		{
			if (m_bNormal)
			{
				m_bNormal = false;
				SetDlgItemText(IDC_CAPTIONINFO_FILE,"Work State         Error");
				((CCaptionInfo*)GetDlgItem(IDC_CAPTIONINFO_FILE))->SetForeColor(RGB(255,0,0));
			}
		}
	}    
	int	nAo = atof(chRes) * 100;
	int nPre = m_ocxPlanPress.GetPlanValue() * 100;
	if(nAo!=nPre)
	    m_ocxPlanPress.SetPlanValue((float)atof(chRes));
}

BOOL CBenderDlg::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following block was added by the ToolTips component.
	if(pMsg->lParam==VK_ESCAPE||pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->lParam==VK_TAB||pMsg->wParam==VK_TAB)
		GetDlgItem(IDC_EDIT_THICK)->SetFocus();
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
		return TRUE;
	
	return CDialog::PreTranslateMessage(pMsg);	// CG: This was added by the ToolTips component.
}

void CBenderDlg::OnButtonStop() /* ����ֹͣ */
{  
	if(m_bAffirm && m_pAffirm->GetSafeHwnd()!=0)
	{
		m_bAffirm = FALSE;
		m_pAffirm->OnEndFind();
	}
	else 
	{
		m_UbtPause.SelectState(NULL);
		g_iStep = 0;
		m_bRunFlag = FALSE;
		g_Controller.Command("ST;STS;CSS");
		char szCmd[80]={0};
		sprintf(szCmd,"OP0,%d",0x0109);
		g_Controller.Command(szCmd);
		SetAOorOF(g_stu_pAxisF->dSpareC);
		if(g_Dmcgc.GetRunflag())
			g_Dmcgc.OnReset();
		if(g_Dmcgc.GetRunflag())
			Sleep(100);
		m_listGrid.SetItemText(2,1,"00:00:00");
		g_Controller.Command("ST;STS");		
		g_Controller.Command(szCmd);	
		SetAOorOF(g_stu_pAxisF->dSpareC);
		g_handdll.SetOut(OUT_LED_RUN,FALSE);
		g_handdll.SetOut(OUT_LED_STOP,TRUE);
	}
	g_lRc = g_Controller.Command("STXYZ");
	g_Controller.Command("ST;STS;CSS");
}

void CBenderDlg::OnButtonRun() /* �������� */
{
	if(1 == m_nSafeSwich)
	{
		if (1 == int(g_handdll.GetIn(IN_SAFE)))
		{	
			if (g_iLanguage == 0)
			{
				MessageBox("��Ļ����������");
			} 
			else
			{
				MessageBox("Safe Switch Closed");
			}
			return;
		}			
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
			Message.strAfxYES ="ȷ��";
			Message.strAfxTitle ="�ŷ�����";
			Message.strAfxMessage ="��ȫ���ϵ磬���������豸��";
		} 
		Message.DoModal(); 	
		return;
	}		
	
	if(g_Dmcgc.GetPauseflag())
	{
		g_Dmcgc.OnContinue();
		g_handdll.SetOut(OUT_LED_RUN,TRUE);
		g_handdll.SetOut(OUT_LED_STOP,FALSE);
		m_UbtPause.SelectState(NULL);
		return;
	}
	if(g_Dmcgc.GetRunflag())	
		return;
    
	if(OnBegoreRunCheck())
	{		 
		if(g_iMode == MODE_MAIN)
		{
			if(g_stu_pAxisB->bSpare)/* ��Ƭ̨ѡ�� ����ˮ���и�*/
			{
				if(g_stu_pAxisC->sSpare==0) //������Ƭ
					g_Dmcgc.SetDmcFilename(g_strOriginalPathC + "BeforeRun.dmc");
				else
				{
					if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
					{
						g_Dmcgc.SetDmcFilename(g_strOriginalPathC + "RBeforeRun.dmc");
					}
					else
					{
						g_Dmcgc.SetDmcFilename(g_strOriginalPathC + "RBeforeRun2143.dmc");
					}					
				} 
				if((!g_handdll.GetIn(IN_FSTSWITCH))&&g_handdll.GetCommandInt((char *)((const char*)"ebreak="))==1)//��һƬ���в���
				{
					if(0 == OnSetRunState())			/* д����Ƭ̨�ȴ�����λ�� */
						return;
					m_bRunFlag = TRUE;
					if(OnBegoreRunCheck())
					{
						if(g_stu_pAxisA->bSpare && m_bRunFlag)/* ��綨λ */
						{
							m_pAffirm->m_dLength = m_rct.right;
							m_pAffirm->m_dHeight = m_rct.top;
							if(m_pAffirm->GetSafeHwnd()==0)
							{
								m_pAffirm->Create(IDD_DIALOG_AFFIRM, this);	
								m_bAffirm = TRUE;
							}
						}	
						else
						{
							if((g_iMode == MODE_MAIN) && m_bRunFlag)
							{
								OnDirectRun();
							}
						}
					}	
				}
				else if(g_handdll.GetIn(IN_GLASSREADY))
				{  
					if (m_iReadyTime>0)
					{
						g_Dmcgc.SetReadyTime(m_iReadyTime);
						g_Dmcgc.OnTurnOver();//��Ƭ̨׼���ź�ʱ��ȴ�����
					}
					else
					{
						OnShowMessageBox(49,g_iLanguage,TRUE);			
					}
				}
				else
				{
					if(0 == OnSetRunState())			/* д����Ƭ̨�ȴ�����λ�� */
						return;
					m_bRunFlag = TRUE;
					g_Dmcgc.SetLoadGlass(g_stu_pAxisB->bSpare);/* ����Ƭ̨ */
				}
			}
			else	//û��ѡ����ˮ�и�
			{				
				if(0 == OnSetRunState())			/* д����Ƭ̨�ȴ�����λ�� */
					return;
				m_bRunFlag = TRUE;
				if(OnBegoreRunCheck())
				{
					if(g_stu_pAxisA->bSpare && m_bRunFlag)/* ��綨λ */
					{
						m_pAffirm->m_dLength = m_rct.right;
						m_pAffirm->m_dHeight = m_rct.top;
						if(m_pAffirm->GetSafeHwnd()==0)
						{
							m_pAffirm->Create(IDD_DIALOG_AFFIRM, this);	
							m_bAffirm = TRUE;
						}
					}	
					else
					{
						if((g_iMode == MODE_MAIN) && m_bRunFlag)
						{
							OnDirectRun();
						}
					}
				}					
			}		
		}
	}
}

void CBenderDlg::OnDirectRun() /* �������� */
{
	/* ���ø���ѹ�����޸����ɵ�DMC���� */

	double	bend_dPress[12];
	long	bend_iTimer[5];
	double	bend_dRadius[2];
	PPRESSURE	pCurrUseThickness;	
	
	
	if(g_stu_pAxisA->sSpareA<1 || g_stu_pAxisA->sSpareA > 30)
	{
		pCurrUseThickness = g_CutPress.GetPressure(4);
		g_stu_pAxisA->sSpareA = 4;
	}
	else
		pCurrUseThickness = g_CutPress.GetPressure(g_stu_pAxisA->sSpareA);
	
	if(pCurrUseThickness != NULL)
	{
		bend_dPress[0] = pCurrUseThickness->dLineAddPress;/* ֱ�߼�ѹ */
		bend_dPress[1] = pCurrUseThickness->dArcAddPress;/* Բ����ѹ */
		bend_dPress[2] = pCurrUseThickness->dToolDown;/* �µ���ѹ */
		bend_dPress[3] = pCurrUseThickness->dPressXAdd;
		bend_dPress[4] = pCurrUseThickness->dPressYAdd;
		bend_dPress[5] = pCurrUseThickness->dPressSmall;
		bend_dPress[6] = pCurrUseThickness->dPressMidle;
		bend_dPress[7] = pCurrUseThickness->dPressBig;
		bend_dPress[8] = pCurrUseThickness->dPressXSub;
		bend_dPress[9] = pCurrUseThickness->dPressYSub;
		bend_dPress[10] = pCurrUseThickness->dToolUp;/* ̧����ѹ */	
		bend_dPress[11] = pCurrUseThickness->dPressSlant;/* �岹��ѹ */	
		bend_iTimer[0] = (long)pCurrUseThickness->nLineAddTime;
		bend_iTimer[1] = (long)pCurrUseThickness->nArcAddTime;
		bend_iTimer[2] = (long)pCurrUseThickness->nToolDelay;
		bend_iTimer[3] = (long)pCurrUseThickness->nUpDelay;
		bend_iTimer[4] = (long)pCurrUseThickness->nAfterUpDelay;
		bend_dRadius[0] = pCurrUseThickness->dRadiusSmall;
		bend_dRadius[1] = pCurrUseThickness->dRadiusBig;
	}
	else
	{
		bend_dPress[0] = 0.0;/* ֱ�߼�ѹ */
		bend_dPress[1] = 0.0;/* Բ����ѹ */
		bend_dPress[2] = 0.0;/* �µ���ѹ */
		bend_dPress[3] = 0.0;
		bend_dPress[4] = 0.0;
		bend_dPress[5] = 0.0;
		bend_dPress[6] = 0.0;
		bend_dPress[7] = 0.0;
		bend_dPress[8] = 0.0;
		bend_dPress[9] = 0.0;
		bend_dPress[10] = 0.0;/* ̧����ѹ */	
		bend_dPress[11] = 0.0;/* �岹��ѹ */	
		bend_iTimer[0] = 0;
		bend_iTimer[1] = 0;
		bend_iTimer[2] = 0;
		bend_iTimer[3] = 0;
		bend_iTimer[4] = 0;
		bend_dRadius[0] = 0;
		bend_dRadius[1] = 0;
	}	
	g_Dmcgc.SetGlassPress(bend_dPress,bend_iTimer,bend_dRadius); /* ����ѹ�� */
	g_Dmcgc.OnGlassCal();
		
	/*����Ԥ����*/
	PDMC    pdmc;
	int		i = 0;
	CString		strSpeed;
	for(pdmc=g_Dmcgc.GetDmcNumber();pdmc;)///paA->d_pulse_user
	{
		g_arr_strGline[i].Format("%s",pdmc->szLineG);		
		pdmc = pdmc->Next;
		i++;
	}
	m_iRunNum++;/* �Զ��ӹ���������1 �ӹ�����ʾ������*/
	SaveSheetToMdb();//����ԭƬ���ݿ� 
	/*����Ԥ����*/
	OnRunWithNoLoad();
}

void CBenderDlg::OnRunWithNoLoad() /* �������� */
{

	if(g_Dmcgc.GetRunflag())	return;//û�д��ļ����򷵻�
	m_PVM.ErasureTracks();
	if(!OnProgramBoxG())        return;
		
	GetLocalTime(&stime_run);// system time    GetSystemTime
	dTimeA = stime_run.wHour;
	dTimeB = stime_run.wMinute;
	dTimeC = stime_run.wSecond;
	dTime = stime_run.wHour*3600 + stime_run.wMinute*60 + stime_run.wSecond;
	pstu_Currdmc = g_Dmcgc.GetDmcNumber();
	
	g_lRc = g_Controller.Command("ST;STS");
	SetTimer(5,1000,NULL);
	DownAccDcc();
	SetLabelStart();
	g_Dmcgc.OnRun();
	g_handdll.SetOut(OUT_LED_RUN,TRUE);
	g_handdll.SetOut(OUT_LED_STOP,FALSE);
}

BOOL CBenderDlg::OnBegoreRunCheck() /* �������� */
{
	if(g_strGfile=="")						
		return FALSE;//û�д��ļ����򷵻�
	if(g_handdll.EmergencyState()==1)		
		return FALSE;
	if(1 == m_nSafeSwich)
	{
		if (1 == int(g_handdll.GetIn(IN_SAFE)))
		{	
			if (g_iLanguage == 0)
			{
				MessageBox("��Ļ����������");
			} 
			else
			{
				MessageBox("Safe Switch Closed");
			}
			return FALSE;
		}			
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
			Message.strAfxYES ="ȷ��";
			Message.strAfxTitle ="�ŷ�����";
			Message.strAfxMessage ="��ȫ���ϵ磬���������豸��";
		} 
		Message.DoModal(); 	
		return FALSE;
	}	
	if(g_iMode == MODE_MAIN || g_nTestRun ==1)
		return TRUE;
	else
		return FALSE;

}

void CBenderDlg::OnButtonPause() /* ������ͣ */
{
//����
//	SaveSheetToMdb();//����ԭƬ���ݿ� 
//  return;
	if(g_Dmcgc.GetRunflag())
	{
		if(g_handdll.GetCommandFloat((char *)((const char*)"MG_XQ"))>=0.0)
		{
			OnButtonStop();		
			return;
		}
		else
		{
			if(g_Dmcgc.GetPauseflag())   
			{			
				return;
			}		
			g_Dmcgc.OnPause();
			char szCmd[80]={0};
			sprintf(szCmd,"OP0,%d",0x0109);
			g_Controller.Command(szCmd);
			g_handdll.SetOut(OUT_LED_RUN,FALSE);
			g_handdll.SetOut(OUT_LED_STOP,TRUE);
			m_UbtPause.SelectState(IDB_BITMAP_NULL3);
		}		
	}

}

void CBenderDlg::OnButtonOil()
{
	CString strOil;	
	if (g_stu_pAxisH->bSpareE==FALSE)
	{
		g_stu_pAxisH->bSpareE = TRUE;
		if (g_iLanguage == 0)
			strOil = "ע��B";
		else
			strOil = "Oil B";
	}
	else
	{
		g_stu_pAxisH->bSpareE = FALSE;
		if (g_iLanguage == 0)
			strOil = "ע��A";
		else
			strOil = "Oil A";
	}
	m_UbtOilAB.SetWindowText(strOil);
	m_UbtOilAB.RepeatDraw();
	g_machinedll.ParameterSave((char*)((const char*)(g_strOriginalPathD + "machine.ini")));/* �����е������Ϣ */
}

void CBenderDlg::OnShowLine() /* ������ʾ������ʱ���� */
{
	CString  sztmp;
	if(g_Dmcgc.GetPauseflag())
		return;

	if(!g_Dmcgc.GetRunflag())			
	{
		g_handdll.SetOut(OUT_LED_RUN,FALSE);
		g_handdll.SetOut(OUT_LED_STOP,TRUE);
		g_iStep = iOldStep = 0;
	}
	else
	{
		g_iStep = g_Dmcgc.GetRunLine()+g_Dmcgc.GetLM()-511;
	   	for(p_stuDmc=pstu_Currdmc;p_stuDmc;)///paA->d_pulse_user
		{	if(!g_Dmcgc.GetRunflag())	
		      return;
			if(p_stuDmc->number==g_iStep)
			{
				if(!strstr(p_stuDmc->szVector,"VM"))
				{
					if(p_stuDmc->comG=='G')
					{
						if(p_stuDmc->dPress>0)
						{
							if(g_nRunState == 0)
							{
								SetAOorOF(p_stuDmc->dPress);
							}
						}

					}
				}
				break;
			}
			else if(p_stuDmc->number>g_iStep)
				p_stuDmc = p_stuDmc->Prev;
			else
				p_stuDmc = p_stuDmc->Next;
		}
		pstu_Currdmc = p_stuDmc;
		if(iOldStep==g_iStep)       return;	
		iOldStep = g_iStep;         /* ��¼�ϵ���λ */
	}
}

void CBenderDlg::SetInitAutoSpeed() /* ���ó�ʼ�Զ�����Ľ����ٶ� */
{
	g_Dmcgc.SetServoControl(g_stu_pAxisA->sSpare);
	g_Dmcgc.SetFeedMotion(g_stu_pAxisB->d_feedrate,g_stu_pAxisB->d_vacc,g_stu_pAxisB->d_vdec);
	g_Dmcgc.SetLocationMotion(g_stu_pAxisC->d_vacc,g_stu_pAxisC->d_vdec);
	g_Dmcgc.SetInterpolation(g_stu_pAxisA->d_vacc,g_stu_pAxisA->d_vdec);
}

void CBenderDlg::SetAutoRateAdd() /* �������ʼ� */
{
	long    lRate;
	lRate = (int)m_ocxPlanSpeed.GetValue();
	if(lRate<120)
	{
		if (g_iMode == MODE_MAIN)
		{
			int     i;
			double  dNumsp[3];
			for(i=0;i<3;i++)
			{
				dNumsp[i] = g_pstu_control->axis[i].d_rapid * g_pstu_control->axis[i].d_pulse_user;
			}
			g_Dmcgc.SetRate(lRate+10,dNumsp);
		}
		else  if (g_iMode == MODE_C)
		{
			g_handdll.handSpeedAdd();
		}
		m_ocxPlanSpeed.SetValue((float)(lRate+10.0));	
	}	
}

void CBenderDlg::SetAutoRateSub() /* �������ʼ� */
{
	long    lRate;
	lRate = (int)m_ocxPlanSpeed.GetValue();
	if(lRate>10)
	{
		if (g_iMode == MODE_MAIN)
		{
			double  dNumsp[3];
			int     i;
			for(i=0;i<3;i++)
			{
				dNumsp[i] = g_pstu_control->axis[i].d_rapid * g_pstu_control->axis[i].d_pulse_user;
			}
			g_Dmcgc.SetRate(lRate-10,dNumsp);
		}
		else if(g_iMode == MODE_C)
		{
			g_handdll.handSpeedSub();
		}
		m_ocxPlanSpeed.SetValue((float)(lRate-10.0));
	}	
}

void CBenderDlg::OnSystemTimer()
{
	SYSTEMTIME st;
	CString		strDate, strTime;	
	GetLocalTime(&st);
	strTime.Format("%02d:%02d:%02d",st.wHour, st.wMinute, st.wSecond);
	m_CapTime.SetCaption(strTime);  

}

int CBenderDlg::OnSingleInput()
{
	int		nVar = 0;
	int		nGetIn[8];
	int		i;
	char    szRes[80]={0};
	for(i=0; i<8; i++)
	{
		if(i<4)
		{
			nGetIn[i] = 0;
		}
		else
		{
			switch(i) 
			{
			case 4:
				g_Controller.Command("MG_HMX",szRes,sizeof(szRes));
				nGetIn[i] = atoi(szRes);
				break;
			case 5:
				g_Controller.Command("MG_HMY",szRes,sizeof(szRes));
				nGetIn[i] = atoi(szRes);
				break;
			case 6:
				g_Controller.Command("MG_HMZ",szRes,sizeof(szRes));
				nGetIn[i] = atoi(szRes);
				break;
			case 7:
				g_Controller.Command("MG_HMW",szRes,sizeof(szRes));
				nGetIn[i] = atoi(szRes);
				break;
			default:
				break;
			}
		}
		nVar += (long)(pow(2, i) * nGetIn[i]);
	}
	return nVar;
}

int CBenderDlg::OnSingleLFR()
{
	int		nVar = 0;
	int		nGetIn[8];
	int		i;
	char    szRes[80] = {0};
	for(i=0; i<8; i++)
	{
		if(i<4)
		{
			switch(i) 
			{
			case 0:
				g_Controller.Command("MG_LFX",szRes,sizeof(szRes));
				nGetIn[i] = atoi(szRes);
				break;
			case 1:
				g_Controller.Command("MG_LFY",szRes,sizeof(szRes));
				nGetIn[i] = atoi(szRes);
				break;
			case 2:
				g_Controller.Command("MG_LFZ",szRes,sizeof(szRes));
				nGetIn[i] = atoi(szRes);
				break;
			case 3:
				g_Controller.Command("MG_LFW",szRes,sizeof(szRes));
				nGetIn[i] = atoi(szRes);
				break;
			default:
				break;
			}
		}
		else
		{
			switch(i) 
			{
			case 4:
				g_Controller.Command("MG_LRX",szRes,sizeof(szRes));
				nGetIn[i] = atoi(szRes);
				break;
			case 5:
				g_Controller.Command("MG_LRY",szRes,sizeof(szRes));
				nGetIn[i] = atoi(szRes);
				break;
			case 6:
				g_Controller.Command("MG_LRZ",szRes,sizeof(szRes));
				nGetIn[i] = atoi(szRes);
				break;
			case 7:
				g_Controller.Command("MG_LRW",szRes,sizeof(szRes));
				nGetIn[i] = atoi(szRes);
				break;
			default:
				break;
			}
		}
		nVar += (long)(pow(2, i) * nGetIn[i]);
	}
	return nVar;
}

int CBenderDlg::OnSingleMO()
{
	int		nVar = 0;
	int		nGetIn[4];
	int		i;
	//��ʹ��Ϊ1
	char szRes[80]={0};
	g_Controller.Command("MG_MOX",szRes,sizeof(szRes));
	nGetIn[0] = atoi(szRes);
	g_Controller.Command("MG_MOY",szRes,sizeof(szRes));
	nGetIn[1] = atoi(szRes);
	g_Controller.Command("MG_MOZ",szRes,sizeof(szRes));
	nGetIn[2] = atoi(szRes);
	//����ͬ��
	if(g_stu_pAxisF->bSpareA == TRUE)
	{
		g_Controller.Command("MG_MOW",szRes,sizeof(szRes));
		nGetIn[3] = atoi(szRes);
	}
	else
	{
        nGetIn[3] = 0;
	}
	for(i=0; i<4; i++)
	{
		nVar += (long)(pow(2, i) * nGetIn[i]);
	}
	return nVar;
}

void CBenderDlg::OnInitInput()
{
	nOldInput[3] = g_handdll.GetGroupIn(5);//41-48
	if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
	{
// ����ͬ�� 
	if(g_stu_pAxisF->bSpareA == TRUE)
        nOldInput[4] = 240;	// INPUT 57-64 �����ŷ����� 57��58��59.60
	else
		nOldInput[4] = 248;	// INPUT 57-64 �����ŷ����� 57��58��59.
	}
	if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
		nOldInput[5] = 240;	//����
	else
        nOldInput[5] = 112;	//w�����ŷ�����
	nOldInput[6] = OnSingleLFR();
	nOldInput[7] = g_handdll.GetGroupIn(0);
	nOldInput[8] = g_handdll.EmergencyState();
	nOldInput[9] = 0;
//	GetAlarm();
	CString	strOutputName[6][2];
	if (g_iLanguage == 0)
	{
		strOutputName[0][0] = "ע��";
		strOutputName[1][0] = "���ʹ�����";
		strOutputName[2][0] = "���ʹ�����";
		strOutputName[3][0] = "�ٶ�1";
		strOutputName[4][0] = "C���µ�";
		strOutputName[5][0] = "��Ƭ̨����";
	}
	else
	{
		strOutputName[0][1] = "Cut Oil";
		strOutputName[1][1] = "Conveyer Belt Rise";
		strOutputName[2][1] = "Conveyer Belt Forward";
		strOutputName[3][1] = "Speed 1";
		strOutputName[4][1] = "C Down";
		strOutputName[5][1] = "Platform Start";
	}
	for(int nIndex=0; nIndex<6; nIndex++)
	{
		m_ocxDisplay.SetDisplayName(nIndex+1, strOutputName[nIndex][g_iLanguage]);
	}	
}

/* ��ʹ����24������㣬�ֺ����鲻���ѯ */
void CBenderDlg::OnErnInButton()
{	
	nNewInput[3] = g_handdll.GetGroupIn(5);//41-48
	if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
		nNewInput[4] = g_handdll.GetGroupIn(7);	//57-64
	nNewInput[5] = OnSingleInput();	//�������λ 
	nNewInput[6] = OnSingleLFR();
	nNewInput[7] = g_handdll.GetGroupIn(0);//0-8
	nNewInput[8] = g_handdll.EmergencyState();
	nNewInput[9] = OnSingleMO();
	OnCompareInput(IN_SERVOX_HOME-5, nOldInput[5], nNewInput[5]);
	OnCompareInput(IN_SERVOX_LIMIT-1 , nOldInput[6], nNewInput[6]);
	OnCompareInput(IN_LIGHT-1, nOldInput[7], nNewInput[7]);
	OnCompareInput(40, nOldInput[3], nNewInput[3]);
	OnCompareInput(56, nOldInput[4], nNewInput[4]);
	OnCompareBinary(IN_EMG_STOP,nOldInput[8],nNewInput[8]);
	OnCompareInput(IN_SERVOX_STATE-1, nOldInput[9], nNewInput[9]);

	for(int i=3;i<10;i++)
		nOldInput[i] = nNewInput[i];

	GetAlarm();

}

LRESULT CBenderDlg::OnMsgInput(WPARAM wParam, LPARAM lParam) 
{ 
	CString stut;
	if(wParam>0)		/* �����ش���,��ţ̌�� */
	{
		switch(lParam) 
		{
		case IN_EMG_STOP:
			OnButtonStop();/* ����г���ִ�У�����ֹͣ���� */
			break;
		case IN_BREAK_READY:		/*IN_BREAK_READY		��Ƭ̨�����ͣ��������ͨʱ����Ĳ�����������*/
			/* ��Ƭ̨����DMC�ļ� */
			if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1
				||g_handdll.GetCommandFloat((char *)((const char*)"MG_XQ"))>=0.0)	
			{
				break;
			}
			if (g_iMode == MODE_MAIN)
			{
				if(!g_stu_pAxisB->bSpare)//û����ˮ���и�
				{
					if(!g_Dmcgc.GetRunflag())
					{
						char szDmc[80]={0};
						strcpy(szDmc,m_strBreak);
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
								Message.strAfxYES ="ȷ��";
								Message.strAfxTitle ="����������";
								Message.strAfxMessage ="��ȫ���ϵ磬���������豸��";
							} 
							Message.DoModal(); 	
							break;
						}
						g_Controller.Command("ST;WT20;XQ#BREAK");
					}					
				}
			}
			break;
		case IN_SERVOW_HOME:
			if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
				break;
            OnButtonStop();/* ����г���ִ�У�����ֹͣ���� */
			g_Controller.WaitForMotionComplete("XYZ");
			g_Controller.Command("MOXYZ");
		    Sleep(30);
			g_Controller.Command("MOXYZ");
			m_LedX.SetRgby(0);//��ɫ
			m_LedY.SetRgby(0);
			m_LedZ.SetRgby(0);
			g_Controller.Command("ST;STS;CSS;homecx=0;homecy=0;homecz=0");
			break;
		case IN_SERVOX_ALARM://X�ŷ�����
			if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
			{
				OnButtonStop();/* ����г���ִ�У�����ֹͣ���� */
				m_LedX.SetRgby(0);//��ɫ
				g_AlarmDll.SetAlarm(AXIS_X_SERVOALARM);
				g_Controller.Command("ST;STS;CSS;homecx=0;homecy=0;homecz=0");
			}
            break;
		case IN_SERVOY_ALARM://Y�ŷ�����
			if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
			{
				OnButtonStop();/* ����г���ִ�У�����ֹͣ���� */
				m_LedY.SetRgby(0);//��ɫ
				g_AlarmDll.SetAlarm(AXIS_Y_SERVOALARM);
				g_Controller.Command("ST;STS;CSS;homecx=0;homecy=0;homecz=0");
			}
            break;
		case IN_SERVOZ_ALARM://Z�ŷ�����
			if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
			{
				OnButtonStop();/* ����г���ִ�У�����ֹͣ���� */
				m_LedZ.SetRgby(0);//��ɫ
				g_AlarmDll.SetAlarm(AXIS_Z_SERVOALARM);
				g_Controller.Command("ST;STS;CSS;homecx=0;homecy=0;homecz=0");
			}
            break;
		case IN_SERVOW_ALARM://W�ŷ�����
			if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
			{
				//����ͬ��
				if(g_stu_pAxisF->bSpareA == TRUE)
				{
					OnButtonStop();/* ����г���ִ�У�����ֹͣ���� */
					m_LedX.SetRgby(0);//��ɫ
					g_AlarmDll.SetAlarm(AXIS_W_SERVOALARM);
					g_Controller.Command("ST;STS;CSS;homecx=0;homecy=0;homecz=0");
				}				
			}
            break;
		default:							
			break;
		}
	}
	else				/* �½��ش�����ť���� */
	{
		switch(lParam) 
		{
		case IN_EMG_STOP:
			{
				g_Controller.Command("ST;STS;CSS;homecx=0;homecy=0;homecz=0");
				if (0 == GetServerAlarm())//û���ŷ�������ʹ��
				{
                    g_Controller.Command("SH");
				}
				m_bEmreStop = TRUE;
			}
			break;
		case IN_BREAK_READY:		/*IN_BREAK_READY		��Ƭ̨�����ͣ��������ͨʱ����Ĳ�����������*/	
			break;
		case IN_SERVOX_ALARM://X�ŷ�����
			if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
			{
				//����ͬ��
				if(g_stu_pAxisF->bSpareA == TRUE)
				{
					if(g_handdll.GetIn(IN_SERVOW_ALARM) == 0)
						m_LedX.SetRgby(1);//��ɫ
				}
				else
				{
					m_LedX.SetRgby(1);//��ɫ
				}
				g_AlarmDll.DeleteAlarm(AXIS_X_SERVOALARM);				
			}
            break;
		case IN_SERVOY_ALARM://Y�ŷ�����
			if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
			{				
				m_LedY.SetRgby(1);//��ɫ
				g_AlarmDll.DeleteAlarm(AXIS_Y_SERVOALARM);				
			}
            break;
		case IN_SERVOZ_ALARM://Z�ŷ�����
			if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
			{
				m_LedZ.SetRgby(1);//��ɫ
				g_AlarmDll.DeleteAlarm(AXIS_Z_SERVOALARM);
			}
			break;
		case IN_SERVOW_ALARM://W�ŷ�����
			if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
			{
				//����ͬ��
				if(g_stu_pAxisF->bSpareA == TRUE)
				{
					if(g_handdll.GetIn(IN_SERVOX_ALARM) == 0)
						m_LedX.SetRgby(1);//��ɫ
					g_AlarmDll.DeleteAlarm(AXIS_W_SERVOALARM);
				}				
			}
            break;            	
		default:							
			break;
		}
	}	
	if(wParam>0)		/* �����ش���,��ţ̌�� */
	{
		switch(lParam) 
		{
		case IN_SERVOX_LIMIT:
			m_LedX.SetRgby(1);//��ɫ
			g_AlarmDll.DeleteAlarm(AXIS_X_FORVARDLIMIT);
			break;
		case IN_SERVOY_LIMIT:
			m_LedY.SetRgby(1);
			g_AlarmDll.DeleteAlarm(AXIS_Y_FORVARDLIMIT);
			break;		
		case IN_SERVOX_RLIMIT://��ɫ
			m_LedX.SetRgby(1);
			g_AlarmDll.DeleteAlarm(AXIS_X_REVERSELIMIT);
			break;
		case IN_SERVOY_RLIMIT:
			m_LedY.SetRgby(1);
			g_AlarmDll.DeleteAlarm(AXIS_Y_REVERSELIMIT);
			break;				
		case IN_SERVOX_STATE:
			OnButtonStop();
			m_LedX.SetRgby(4);
			break;
		case IN_SERVOY_STATE:
			OnButtonStop();
			m_LedY.SetRgby(4);
			break;	
		case IN_SERVOZ_STATE:
			OnButtonStop();
			m_LedZ.SetRgby(4);
			break;			
		case IN_SERVOW_STATE:
			if(g_stu_pAxisF->bSpareA == TRUE)//����ͬ��
			{
				OnButtonStop();
				m_LedX.SetRgby(4);
			}
			break;
		case IN_RUN:/* ���� */
			if(g_handdll.EmergencyState()==1)		
				break;
			if(g_iMode == MODE_MAIN && g_stu_pAxisB->bSpare && m_bRunFlag && m_bShowExtra)//����ˮ���и�
			{
				m_bShowExtra = FALSE;
				ShowExpand();
			}
			if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1
				||g_handdll.GetCommandFloat((char *)((const char*)"MG_XQ"))>=0.0)	
			{
				if(g_Dmcgc.GetPauseflag()==0)
					break;
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
					Message.strAfxYES ="ȷ��";
					Message.strAfxTitle ="�ŷ�����";
					Message.strAfxMessage ="��ȫ���ϵ磬���������豸��";
				} 
				Message.DoModal(); 		
				break;
			}
			if(OnSingleMO() > 0)
				break;
			if(g_iMode != MODE_MAIN)
				break;			
			if (GetZeroState() == 0)
			{
				MachineZeroAlarm(g_iLanguage);  
				break;
			}
			if (m_bEmreStop)
			{
                CDlg_AfxMessage Message;
				Message.bYesNo = FALSE;
				if (g_iLanguage == 0)
				{
					Message.strAfxYES = g_arr_message[44][1];
					Message.strAfxTitle = g_arr_message[1][1];
					Message.strAfxMessage = "�����´򿪼ӹ��ļ�!";
				}
				else
				{
					Message.strAfxYES = g_arr_message[44][2];
					Message.strAfxTitle = g_arr_message[1][2];
					Message.strAfxMessage = "Please open the file again";
				}
				Message.DoModal();
				break;
			}
			
			if(g_Dmcgc.GetRunflag()==1)
			{
				if(g_Dmcgc.GetPauseflag()==0)
					break;
			}			
			if (g_nTestRun == 1 && m_pTestDlg->GetSafeHwnd() != NULL)
			{
                RunTest(m_pTestDlg->m_nTestType);
				break;
			}			
			g_Dmcgc.SetOilingOption(g_stu_pAxisG->dSpareE, g_stu_pAxisH->dSpareE, m_strDmcAV); 
			WriteOilingDmc();
    		g_Controller.Command("ebreak=1");/* �������и�ĵ�һƬ */			
			OnButtonRun();
			break;
		case IN_STOP:		/* ֹͣ */
			g_AlarmDll.SetAlarm(108);
			OnButtonStop();
			g_AlarmDll.DeleteAlarm(108);			
			break;
		case IN_DIEDOWN:		/*IN_DIEDOWN		/ *�µ�����* /*/
			g_AlarmDll.DeleteAlarm(105);			
			break;
		case IN_SAFE:        //��ȫ��դ
			if(1 == m_nSafeSwich && g_handdll.GetCommandFloat((char *)((const char*)"MG_XQ"))<0.0)
                OnButtonPause();
			break;
		default:							
			break;
		}
	}
	else				/* �½��ش�����ť���� */
	{
		switch(lParam) 
		{
		case IN_SERVOX_LIMIT:
 			OnButtonStop();
			m_LedX.SetRgby(2);
			g_AlarmDll.SetAlarm(AXIS_X_FORVARDLIMIT);
			break;
		case IN_SERVOY_LIMIT:
			OnButtonStop();
			m_LedY.SetRgby(2);
			g_AlarmDll.SetAlarm(AXIS_Y_FORVARDLIMIT);
			break;		
		case IN_SERVOX_RLIMIT:
			OnButtonStop();
			m_LedX.SetRgby(2);
			g_AlarmDll.SetAlarm(AXIS_X_REVERSELIMIT);
			break;
		case IN_SERVOY_RLIMIT:
			OnButtonStop();
			m_LedY.SetRgby(2);
			g_AlarmDll.SetAlarm(AXIS_Y_REVERSELIMIT);
			break;		
		case IN_SERVOX_STATE:
			if(g_stu_pAxisF->bSpareA == TRUE)//����ͬ��
			{
				//��ʹ��Ϊ1
				char szRes[80]={0};
				g_Controller.Command("MG_MOW",szRes,sizeof(szRes));
				if (atoi(szRes) == 0)
				{
					m_LedX.SetRgby(1);
				}
			}
			else
			{
				m_LedX.SetRgby(1);
			}
			break;
		case IN_SERVOY_STATE:
			m_LedY.SetRgby(1);
			break;			
		case IN_SERVOZ_STATE:
			m_LedZ.SetRgby(1);
			break;		
		case IN_SERVOW_STATE:
			if(g_stu_pAxisF->bSpareA == TRUE)//����ͬ��
			{
				//��ʹ��Ϊ1
				char szRes[80]={0};
				g_Controller.Command("MG_MOX",szRes,sizeof(szRes));
				if (atoi(szRes) == 0)
				{
					m_LedX.SetRgby(1);
				}
			}
			break;
		case IN_DIEDOWN:		/*IN_DIEDOWN			/ *�µ�����* /*/
			OnButtonStop();
			g_AlarmDll.SetAlarm(105);
			break;
		case IN_FANS:
			if(g_Dmcgc.GetRunflag() == 1
				||g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1
				||g_handdll.GetCommandFloat((char *)((const char*)"MG_XQ"))>=0.0)	
				break;
			g_handdll.SwitchOutput(OUT_WIND_RELAY); 
			break;
		default:							
			break;
		}
	}
	return 0;
}

void CBenderDlg::OnCompareInput(int nBase, int nOld, int nNew)
{
	if(nOld!=nNew)
	{
		if(nOld>=0)
		{
			OnCompareInt(nBase, nOld, nNew);
			SendInput(nBase, nNew);
		}
	}
}

void CBenderDlg::SendInput(int nBase, int nValue)
{
	CWnd *pDlg;
	pDlg = FindWindow(NULL, "CASE");
	if(pDlg)
		pDlg->SendMessage(WM_ALMINPUT,  nBase, 255 - nValue);/* ��ν��ַ�����������״̬ȡ�� */
}

void CBenderDlg::OnReadOutput() /* ����� */
{	
	nOldOutput[0] = nNewOutput[0];				/* 1��16 */
	nOldOutput[1] = nNewOutput[1];				/* 17��32 */
	nNewOutput[0] = g_handdll.GetGroupOut(0);	/* 1��16 */
	nNewOutput[1] = g_handdll.GetGroupOut(1);	/* 17��32 */	
	if(nOldOutput[0]!=nNewOutput[0] || nOldOutput[1]!=nNewOutput[1])
	{
		SendOutput(0, nNewOutput[0]);		
		SendOutput(16, nNewOutput[1]);		
		OnDisplayOutput(6);
	}
}

void CBenderDlg::OnDisplayOutput(int nCount) /* �Զ�������� */
{

	long			lDisplay = 0;
	int				nGetOut[6];
	CString			strOutputName;	
	int nOilB = nNewOutput[0] & 0x0002 ? 1 : 0;
	int nOilA = nNewOutput[0] & 0x0010 ? 1 : 0;
	nGetOut[0] = nOilB | nOilA;
	nGetOut[1] = nNewOutput[0] & 0x0020 ? 1 : 0;
	nGetOut[2] = nNewOutput[0] & 0x0040 ? 1 : 0;
	nGetOut[3] = nNewOutput[1] & 0x0100 ? 1 : 0;//�ٶ�
	nGetOut[4] = nNewOutput[1] & 0x4000 ? 1 : 0;
	nGetOut[5] = nNewOutput[0] & 0x0004 ? 1 : 0;
	
	for(int i=0; i<nCount; i++)		
		lDisplay += (long)(pow(2,i) * nGetOut[i]);

	m_ocxDisplay.SetDisplayData(lDisplay);
}

void CBenderDlg::SendOutput(int nBase, int nValue)
{
	CWnd *pDlg;
	pDlg = FindWindow(NULL, "CASE");
	if(pDlg)
		pDlg->SendMessage(WM_ALMOUTPUT, nBase, nValue);/* ��ν��ַ������� */
}


void CBenderDlg::OnCompareInt(int nBase,int nFirst,int nCecond)
{
	CString		strP;
	int		i,nPosition;
	char	chP[10],chB[10];
	if(nFirst<0||nFirst>255||nCecond<0||nCecond>255)
		return;
	nPosition = nFirst ^ nCecond;
	itoa(nPosition + 256, chP, 2);
	itoa(nCecond + 256, chB, 2);
	for(i=1;i<9;i++)
	{
		if(chP[i]=='1')
		{
			if(chB[i]=='1')/* Ϊ������ */
			{
				PostMessage(WM_INPUT, 1, nBase + 9 - i);
			}
			else					/* Ϊ�½��� */
			{
				SendMessage(WM_INPUT, 0, nBase + 9 - i);
			}
		}
	}
}

//��ͣ��
void CBenderDlg::OnCompareBinary(int nBase,int nFirst,int nCecond)
{	
	if(nFirst<0||nFirst>1||nCecond<0||nCecond>1||nFirst==nCecond)
		return;
	if(nFirst<nCecond)/* Ϊ������ */
	{
		SendMessage(WM_INPUT, 1, nBase);				
	}
	else					/* Ϊ�½��� */
	{
		SendMessage(WM_INPUT, 0, nBase);				
	}
}

long CBenderDlg::OnProgramBoxG()
{
	PDMC    pdmc;
	double  dbaseX,dbaseY;
	m_rct.left = 0;        m_rct.right = 0;
	m_rct.bottom = 0;      m_rct.top = 0;
	for(pdmc=g_Dmcgc.GetDmcNumber();pdmc;)///paA->d_pulse_user
	{
		if(strstr(pdmc->command,"CR"))
		{
			GetCRRange(dbaseX,dbaseY, pdmc);
			if(pdmc->usProPos.X<m_rct.left)       m_rct.left = (long)pdmc->usProPos.X;
			if(pdmc->usProPos.X>m_rct.right)      m_rct.right = (long)pdmc->usProPos.X;
			if(pdmc->usProPos.Y<m_rct.bottom)     m_rct.bottom = (long)pdmc->usProPos.Y;
			if(pdmc->usProPos.Y>m_rct.top)        m_rct.top = (long)pdmc->usProPos.Y;
			dbaseX = pdmc->usProPos.X;
			dbaseY = pdmc->usProPos.Y;
		}
		else if(strstr(pdmc->command,"VP")||strstr(pdmc->command,"LI"))
		{
			if(pdmc->usProPos.X<m_rct.left)       m_rct.left = (long)pdmc->usProPos.X;
			if(pdmc->usProPos.X>m_rct.right)      m_rct.right = (long)pdmc->usProPos.X;
			if(pdmc->usProPos.Y<m_rct.bottom)     m_rct.bottom = (long)pdmc->usProPos.Y;
			if(pdmc->usProPos.Y>m_rct.top)        m_rct.top = (long)pdmc->usProPos.Y;
			dbaseX = pdmc->usProPos.X;
			dbaseY = pdmc->usProPos.Y;
		}
		pdmc = pdmc->Next;
	}
	if((m_rct.right - m_rct.left)>(long)g_stu_pAxisA->dSpareA||(m_rct.top - m_rct.bottom)>(long)g_stu_pAxisB->dSpareA)
	{
		OnShowMessageBox(38,g_iLanguage,FALSE);
		return 0;
	}
	else if(m_rct.left<g_stu_pAxisA->l_Journey_negative - g_fCurrMachineX
		||m_rct.right>g_stu_pAxisA->l_Journey_positive  - g_fCurrMachineX
		||m_rct.bottom<g_stu_pAxisB->l_Journey_negative  - g_fCurrMachineY
		||m_rct.top>g_stu_pAxisB->l_Journey_positive - g_fCurrMachineY)
	{
		OnShowMessageBox(39,g_iLanguage,FALSE);
		return 0;
	}
	else
		return 1;
}

void CBenderDlg::OnMachineBK()/* ��϶���������ƫ�� */
{
	CString  szStr,szStrA,szStrB,szStrC;
	if(g_stu_pAxisA->l_Backlash>=0||g_stu_pAxisB->l_Backlash>=0||g_stu_pAxisC->l_Backlash>=0)
	{
		szStrA.Format("%d",g_stu_pAxisA->l_Backlash);
		szStrB.Format("%d",g_stu_pAxisB->l_Backlash);
		szStrC.Format("%d",g_stu_pAxisC->l_Backlash);
        szStr = "BH" + szStrA + "," + szStrB + "," + szStrC;
		char szCmd[80]={0};
		strcpy(szCmd,LPCTSTR(szStr));
		g_lRc = g_Controller.Command(szCmd);
 	}
}

void CBenderDlg::OnButton10() 
{
	if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1
		||g_handdll.GetCommandFloat((char *)((const char*)"MG_XQ"))>=0.0)	
	{
		OnShowMessageBox(22,g_iLanguage,FALSE);
		return;
	}
    
	if(OnShowMessageBox(41,g_iLanguage)==IDNO)
		return;
	KillTimer(1);				
	KillTimer(2);		
	//KillTimer(3);			
	KillTimer(6);		
	KillTimer(10);
	OnButtonStop();
	if(g_Dmcgc.GetRunflag())
	{
		OnButtonStop();
		Sleep(100);
	}
	g_Controller.Command("OP0,0,0");
	if (g_stu_pAxisF->bSpareA == TRUE)//���ŷ�ʽ
    {
		CloseMsCom();
    }
	keybd_event(VK_MENU, 0, 0, 0); 
	Sleep(10);
	keybd_event(VK_F4, 0, 0, 0); 
	keybd_event(VK_F4, 0, KEYEVENTF_KEYUP, 0); 
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); 
	PostMessage(WM_CLOSE,0,0);
    CDialog::OnOK();
}

void CBenderDlg::OnRunTimeCount() /* ʱ��ͳ����ͼ�� */
{
	CString     strRunTime;
	SYSTEMTIME  timeTemp; 
	
	if(g_Dmcgc.GetRunflag()) /* ����Զ����б�־ */	
	{
		GetLocalTime(&timeTemp);// system time    GetSystemTime
		dTimeA = timeTemp.wHour;
		dTimeB = timeTemp.wMinute;
		dTimeC = timeTemp.wSecond;
		long lSecond = (long)(dTimeA*3600+dTimeB*60+dTimeC - dTime);
		strRunTime.Format("%02d:%02d:%02d",(long)(lSecond/3600),(long)((lSecond - (lSecond/3600)*3600)/60),(long)(lSecond%60));
		m_listGrid.SetItemText(2,1,strRunTime);
	}
	else
	{
		KillTimer(5);
	}
}

void CBenderDlg::OnButtonHome() 
{
	if(g_iMode == MODE_MAIN)
	{
		if(g_Dmcgc.GetPauseflag())        
			return;
		SetAutoRateAdd();
	}
	else if(g_iMode == MODE_C)
	{
		if (m_pHandDlg->GetSafeHwnd()!=NULL)
		{
			SetAutoRateAdd();
		}
	}
}

void CBenderDlg::OnButtonEnd()
{
	if(g_iMode == MODE_MAIN)
	{
		if(g_Dmcgc.GetPauseflag())        
			return;
		SetAutoRateSub();
	}
	else if(g_iMode == MODE_C)
	{
		if (m_pHandDlg->GetSafeHwnd()!=NULL)
		{
			SetAutoRateSub();
		}
	}
}

LRESULT CBenderDlg::OnRunOption(WPARAM wParam, LPARAM lParam) 
{ 
	switch(wParam) 
	{
	case 2:/* �趨���� */	
		m_iSetNum = (int)lParam;			
		break;
	case 3:/* �ӹ����� */	
		m_iRunNum = (int)lParam;		
		break;
	case 4://��Ƭ̨׼��ʱ��
         m_iReadyTime = (int)lParam;
		break;
	default:	
		break;
	}
	return 0;
}

/* д����Ƭ̨�ȴ�����λ�� 0д�����1д������*/
int CBenderDlg::OnSetRunState()	
{
	CString		strHit;
    LONG l_Rec;
	char szCmd[80] = {0};
	if(g_stu_pAxisA->lSpareA<=0)		strHit.Format("hitx=%d",1);
	else				strHit.Format("hitx=%d",(long)(g_stu_pAxisA->lSpareA * g_stu_pAxisA->d_pulse_user));
	strcpy(szCmd,LPCTSTR(strHit));
	l_Rec = g_Controller.Command(szCmd);
	if (l_Rec != 0)
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
			Message.strAfxYES ="ȷ��";
			Message.strAfxTitle ="����������";
			Message.strAfxMessage ="��ȫ���ϵ磬���������豸��";
		} 
		Message.DoModal(); 	
		return 0;
	}
	if(g_stu_pAxisB->lSpareA<=0)		strHit.Format("hity=%d",1);
	else				strHit.Format("hity=%d",(long)(g_stu_pAxisB->lSpareA * g_stu_pAxisB->d_pulse_user));
	strcpy(szCmd,LPCTSTR(strHit));
	l_Rec = g_Controller.Command(szCmd);
	if (l_Rec != 0)
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
			Message.strAfxYES ="ȷ��";
			Message.strAfxTitle ="����������";
			Message.strAfxMessage ="��ȫ���ϵ磬���������豸��";
		} 
		Message.DoModal(); 	
		return 0;
	}
	return 1;

}

void CBenderDlg::GetCRRange(double fBaseX,double fBaseY,PDMC pdmc)
{
	int nRadiusAngle,nAngleEnd;
	double dRadius;

	nRadiusAngle = (int)(pdmc->usBAngle);//��ʼ
	nAngleEnd = (int)(pdmc->usEAngle);//�н�
	dRadius = pdmc->usRadius / g_stu_pAxisA->d_pulse_user;
	double fCenterX = fBaseX - dRadius * cos((pdmc->usBAngle)*3.1415926/180.0);
	double fCenterY = fBaseY - dRadius * sin((pdmc->usBAngle)*3.1415926/180.0);
	if( pdmc->usEAngle < 0 )	//�����˳ʱ��
	{
		if( pdmc->usBAngle+pdmc->usEAngle <= 0.0)								//����������
		{
			SetRange(fCenterX+dRadius,fCenterY);
		}
		if( (pdmc->usBAngle > 90.0 && nRadiusAngle+nAngleEnd < 90.0) 
			|| nRadiusAngle+nAngleEnd <= -270.0)	//�������90��
		{
			SetRange(fCenterX,fCenterY+dRadius);
		}
		if( (pdmc->usBAngle > 180.0 && nRadiusAngle+nAngleEnd < 180.0) 
			|| nRadiusAngle+nAngleEnd <= -180.0)//�������180��
		{
			SetRange(fCenterX-dRadius,fCenterY);
		}
		if( (pdmc->usBAngle > 270.0 && (nRadiusAngle+nAngleEnd) < 270.0) 
			|| nRadiusAngle+nAngleEnd <= -90.0)//�������270��
		{
			SetRange(fCenterX,fCenterY-dRadius);
		}
	}
	else				//�������ʱ��
	{
		if( pdmc->usBAngle+pdmc->usEAngle >= 360.0)								//����������
		{
			SetRange(fCenterX+dRadius,fCenterY);
		}
		if( (pdmc->usBAngle < 90.0 && (nRadiusAngle+nAngleEnd)> 90.0) 
			|| nRadiusAngle+nAngleEnd >= 450.0)	//�������90��
		{
			SetRange(fCenterX,fCenterY+dRadius);
		}
		if( (pdmc->usBAngle < 180.0 && (nRadiusAngle+nAngleEnd)%360 > 180.0) 
			|| nRadiusAngle+nAngleEnd >= 540.0)//�������180��
		{
			SetRange(fCenterX-dRadius,fCenterY);
		}
		if( (pdmc->usBAngle < 270.0 && (nRadiusAngle+nAngleEnd)%360 > 270.0)  
			|| nRadiusAngle+nAngleEnd >= 630.0)//�������270��
		{
			SetRange(fCenterX,fCenterY-dRadius);
		}
	}
}

void CBenderDlg::SetRange(double fx, double fy)
{
	if(fx<m_rct.left)       m_rct.left = (long)fx;
	if(fx>m_rct.right)      m_rct.right = (long)fx;
	if(fy<m_rct.bottom)     m_rct.bottom = (long)fy;
	if(fy>m_rct.top)        m_rct.top = (long)fy;
}

LRESULT CBenderDlg::OnAffirm(WPARAM wParam, LPARAM lParam) 
{

	if(1 == m_nSafeSwich)
	{
		if (1 == int(g_handdll.GetIn(IN_SAFE)))
		{	
			if (g_iLanguage == 0)
			{
				MessageBox("��Ļ����������");
			} 
			else
			{
				MessageBox("Safe Switch Closed");
			}
			return FALSE;
		}			
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
			Message.strAfxYES ="ȷ��";
			Message.strAfxTitle ="�ŷ�����";
			Message.strAfxMessage ="��ȫ���ϵ磬���������豸��";
		} 
		Message.DoModal();	
		return FALSE;
	}		
	if(lParam==1)
	{
		for(int i=0;i<5110;i++)		
		{
			g_arr_strGline[i] = "";
		}
		m_nOpenLight = 1;
		ResetCS(strGCodeOpenFile, g_strDmcfile);//G����ת��gCode
        m_nOpenLight = 0;
		Sleep(100);
		if(m_bRunFlag)
			OnDirectRun();
	}
	else
	{
		if(!g_iLanguage)	
			AfxMessageBox("û�м�⵽������");
		else				
			AfxMessageBox("Can not find glass!");
	}
	return 0;
}

void CBenderDlg::OnOk()
{

}

void CBenderDlg::OnCancel()
{
#ifdef _DEBUG
	CDialog::OnCancel();
#endif
}

UINT CBenderDlg::OnDMCGC(WPARAM wParam,LPARAM lParam)
{
	if(wParam == 0)
	{
		switch(lParam) 
		{		
		case 2:/* ��Ƭ��ɺ���� */
			{
                //�ж��Ƿ�����ӹ�
				//���������Ǵ��ͣ�nRunOrTranĬ��0������1������2.
				int nRunOrTran = g_handdll.GetCommandInt((char *)((const char*)"runortr="));
                if(nRunOrTran == 1 || nRunOrTran == 0)//�����ӹ�
				{
					if(OnBegoreRunCheck())
					{
						if(g_stu_pAxisA->bSpare && m_bRunFlag)/* ��綨λ */
						{
							m_pAffirm->m_dLength = m_rct.right;
							m_pAffirm->m_dHeight = m_rct.top;
							if(m_pAffirm->GetSafeHwnd()==0)
							{
								m_pAffirm->Create(IDD_DIALOG_AFFIRM, this);	
								m_bAffirm = TRUE;
							}
						}	
						else
						{
							if((g_iMode == MODE_MAIN) && m_bRunFlag)
							{
								OnDirectRun();
							}
						}
					}		
				}
				else if (nRunOrTran == 2)//������ֹͣ�ӹ���������Ҫ��ͼ
				{
					if(m_iRunNum<m_iSetNum)
					{
						OnPrepare(3);
						m_bContiueRun = TRUE;
						FileOpen();					
					}
					else
					{
						m_iRunNum = 0;
						OnPrepare(3);
						//�ж��Ƿ���ϵ���ļ�
						if (CheckContinousWork(g_strShowName))
						{					
							CopyPreShowInf(); //������չ��ʾ�����ݽṹ
							FileOpen();
							ShowExpand();		
						}
						else//û�м���Ҫ�ӹ����ļ�
						{
							CopyPreShowInf(); //������չ��ʾ�����ݽṹ
							ShowExpand();
							JudgeLastFile();
						}	
					}
				}		
			}			
			break;
		case 3:/* �ӹ���ϣ��������������������������������һ�μӹ� */
			g_Controller.Command("ST;WT20");
			KillTimer(5);		
			WritePrivateProfileString("FILE","FILETIME",m_listGrid.GetItemText(2,1),INIFILE_LASTINF);
			m_listGrid.SetItemText(2,1,"00:00:00");
			ModifyProduct();
			m_PVM.ErasureTracks();
			//����У׼
			if (g_stu_pAxisF->bSpareA == TRUE)
			{
				int nRun = g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ|_BGW)"));
                //int n = 0;//ʱ�䷶Χ2000
				while (nRun == 1)
				{
					Sleep(50);
					if (g_handdll.EmergencyState()==1)//��ͣ
					   break;
					nRun = g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ|_BGW)"));
				}
				Sleep(200);
				int nError = g_handdll.GetCommandInt((char *)((const char*)"MG(_IPX-_IPW"));
				if (abs(nError)>5)//�����
				{
					if (abs(nError)>300)//���������
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
							Message.strAfxYES ="ȷ��";
							Message.strAfxTitle ="����ƫ�����";
							Message.strAfxMessage ="����ƫ����������»ػ�е���!";
						} 
						Message.DoModal();
						m_bRunFlag = FALSE;
						break;
					}
					else
					{
						char   cmd[80]={0};
						sprintf(cmd,"GM0,,,0;GR0,,,0;WT100;SP,,,10000;PR,,,%d;BGW;AMW",nError);
						//MessageBox(cmd);
						g_Controller.Command(cmd);
						//g_Controller.WaitForMotionComplete("W");
						int nRun = g_handdll.GetCommandInt((char *)((const char*)"MG_BGW"));
						while (nRun == 1)
						{
							Sleep(50);
							nRun = g_handdll.GetCommandInt((char *)((const char*)"MG_BGW"));
						}
						Sleep(200);
						g_Controller.Command("GM1,,,1;GA,,,CX;GR0,,,1");
					}
				}
				
			}//����У׼
			if (g_nTestRun == 1)//����ǲ����иֱ�ӷ��ء�
			{
				m_bRunFlag = FALSE;
				break;
			}
			if(g_stu_pAxisB->bSpare)//��ˮ���и�
			{ 
 				if(m_iRunNum<m_iSetNum)
				{
					//if(m_iRunNum == 1)
					{
						CopyPreShowInf(); //������չ��ʾ�����ݽṹ
						m_bShowExtra = TRUE;
					}
					OnPrepare(3);
					g_Controller.Command("ebreak=0");/* ���ǵ�һ�鲣�� */
                    m_bContiueRun = TRUE;
					FileOpen();
					OnButtonRun();
				}
				else
				{
					m_iRunNum = 0;
					OnPrepare(3);
					//�ж��Ƿ���ϵ���ļ�
					if (CheckContinousWork(g_strShowName))
					{
						CopyPreShowInf(); //������չ��ʾ�����ݽṹ
						FileOpen();
						m_bShowExtra = TRUE;
						g_Controller.Command("ebreak=0");/* ���ǵ�һ�鲣�� */
						OnButtonRun(); 
					}
					else
					{
						CopyPreShowInf(); //������չ��ʾ�����ݽṹ						
						CString str;
						if(g_stu_pAxisC->sSpare==0)
							str = g_strOriginalPathC + "BehindRun.dmc";
						else
							str = g_strOriginalPathC + "RBehindRun.dmc";
                        char szDmc[80]={0};
						strcpy(szDmc,str);
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
								Message.strAfxYES ="ȷ��";
								Message.strAfxTitle ="����������";
								Message.strAfxMessage ="��ȫ���ϵ磬���������豸��";
							} 
							Message.DoModal(); 	
							return 0;
						}
						g_Controller.Command("ST;WT20;XQ#BEHRUN");
                        SetTimer(7,100,NULL);//������������һƬ��Ƭ���򣬳������ˢ����չ��
  					}	
				}
			}
			else //����ˮ�и� Ϊ�˵�ͼ
			{
				if(m_iRunNum<m_iSetNum)
				{
					OnPrepare(3);			
                    FileOpen();					
				}
				else
				{
					m_iRunNum = 0;
					OnPrepare(3);
					//�ж��Ƿ���ϵ���ļ�
					if (CheckContinousWork(g_strShowName))
					{					
						CopyPreShowInf(); //������չ��ʾ�����ݽṹ
						FileOpen();
						ShowExpand();		
					}
					else//û�м���Ҫ�ӹ����ļ�
					{
						CopyPreShowInf(); //������չ��ʾ�����ݽṹ
						ShowExpand();
						JudgeLastFile();
					}	
				}
			}
			break;
		default:
			break;
		}
	}
	else if (wParam == 1)//��Ƭ̨׼��
	{
		if (lParam == 0)
		{
			if(OnShowMessageBox(49,g_iLanguage,TRUE))
				return 0;
		}
		else
		{
			if(0 == OnSetRunState())			/* д����Ƭ̨�ȴ�����λ�� */
				return 0;
			m_bRunFlag = TRUE;
			g_Dmcgc.SetLoadGlass(g_stu_pAxisB->bSpare);/* ����Ƭ̨ */
		}
	}
	else if (wParam == 2)//ѭ���и�ͼ��ˢ��
	{
		m_PVM.ErasureTracks();
	}  
	else if (wParam == 3)
	{
		double dPress = double((long)lParam/100.0);
		SetAOorOF(dPress);
	}
	return 0L;
}
/* ��ʼ���ֶ��µ�ѹ�� */
void CBenderDlg::OnInitHandPressure() 
{
	PPRESSURE	pCurrUseThickness;
	if(g_stu_pAxisA->sSpareA<1 || g_stu_pAxisA->sSpareA > 30)
	{
		pCurrUseThickness = g_CutPress.GetPressure(4);
		g_stu_pAxisA->sSpareA = 4;
	}
	else
		pCurrUseThickness = g_CutPress.GetPressure(g_stu_pAxisA->sSpareA);
    if (pCurrUseThickness != NULL )
    {
		g_stu_pAxisF->dSpareC = pCurrUseThickness->dToolUp;
		g_stu_pAxisC->dSpareB = pCurrUseThickness->dToolDown;
		m_ocxPlanPress.SetValue(pCurrUseThickness->dToolDown);
    }
}


//=======================================================================================
//====================================����ɨ��ɨ�蹦����=====================================
//=====================================����ɨ�蹦����====================================

void CBenderDlg::OnIniRunVS(long nValue)
{
	CString	strGalil;
	strGalil.Format("VS%d", (long)(nValue * g_stu_pAxisA->d_pulse_user));
	g_Controller.Command(strGalil.GetBuffer(0));
}

void CBenderDlg::ScanRun()
{
	m_clsScan.SetPDmcWin((long)&g_Controller);
	m_clsScan.SetWindow(FindWindow(NULL, "PNC2000GC"));
	m_clsScan.SetIncludeRect(0, 500, 500, 0);
	m_clsScan.SetResolution(g_stu_pAxisA->d_pulse_user, g_stu_pAxisB->d_pulse_user);
	m_clsScan.SetCenterPoint(g_ScanPara.dScanCenterPosX, g_ScanPara.dScanCenterPosY);
	m_clsScan.SetStartPoint(g_ScanPara.dScanBeginPosX, g_ScanPara.dScanBeginPosY);
	m_clsScan.SetScanPace(g_ScanPara.dScanPace);	
	OnIniRunVS(g_ScanPara.dScanSpeed);
	m_clsScan.SetScanDistance(5, 5); 
	m_nScanTreadID = m_clsScan.Run();	
}

void CBenderDlg::ScanStop()
{
	pScanPosition pScanData;
	
	m_clsScan.Stop();
	m_nScanTreadID = 0;
	
	pScanData = m_clsScan.GetScanData();
}

bool CBenderDlg::GetScanRun()
{
	return m_clsScan.GetRunState();
}
void CBenderDlg::ScanSaveGcode()
{
	CString   strFilename;
	dlg_save  dlgSave;
	
	dlgSave.strExtName = ".g";
	if (IDCANCEL == dlgSave.DoModal())  return;
	
	strFilename = g_strOriginalPathD+"gcode\\"+g_strSavefile;
	g_strSavefile = "";	
	m_clsScan.SaveScanFile2G((char*)((const char*)strFilename));
}

UINT CBenderDlg::OnFromDllSendScan(WPARAM wParam, LPARAM lParam)
{
	BOOL	b;
	CWnd	*pDlgScan;

	pDlgScan = FindWindow(NULL, "SCAN");
	if(pDlgScan)
		pDlgScan->SendMessage(WM_SCAN, wParam, lParam);
	
	if(lParam==0)
	{
		Sleep(20);
		b = PostThreadMessage(m_nScanTreadID, WM_SCANNEXT, 0, 0);
	}
	return 0;
}

//=====================================����ɨ��ɨ�蹦����====================================
//=======================================================================================
//=======================================================================================

void CBenderDlg::ScanSavePos(int nFormat)
{
	CString   strFilename;
	dlg_save  dlgSave;
	
	if(1 == nFormat) //.cid
	{
		dlgSave.strExtName = ".cid";
	}
	else if (2 == nFormat)//.dxf
	{
		dlgSave.strExtName = ".dxf";
	}
	if (IDCANCEL == dlgSave.DoModal())  return;
	if (1 == nFormat)
	{
		strFilename = g_strOriginalPathD+"gcode\\"+g_strSavefile;
	} 
	else if (2 == nFormat)//.dxf
	{
		strFilename = g_strOriginalPathD+"dxf\\"+g_strSavefile;
	}
	g_strSavefile = "";
	m_clsScan.SaveScanPosition((char*)((const char*)strFilename), nFormat);
}

bool CBenderDlg::CheckContinousWork(CString  strWorkName)
{

	bool bContinous = FALSE;
	CString strPreName,strBackName;
	CString strNametype;
	CString strFilePath,strFilePathWork;
	int nPos;
	int nSheet;
	int nCount;
	
	//////check Name type .g or .dxf or .cxf ;
	nPos = strWorkName.Find('.');
    strNametype = strWorkName.Mid(nPos+1);
	if (strNametype == "dxf" || strNametype == "DXF")
	{
		strFilePath = g_strOriginalPathD + "dxf\\*.d*";
		strFilePathWork = g_strOriginalPathD + "dxf\\";
	}
	else if (strNametype == "cxf" || strNametype == "CXF")
	{
		strFilePath = g_strOriginalPathD + "glass\\*.c*";
		strFilePathWork = g_strOriginalPathD + "glass\\";
	}
	else if (strNametype == "g" || strNametype == "G")
	{
		//����༶g�����ļ�Ŀ¼
		int nNum = g_strGfile.ReverseFind('\\');
		int nLength = g_strGfile.GetLength();
		if (nNum>nLength || nNum<0)
		{
			return bContinous;
		}
		strFilePathWork = g_strGfile.Left(nNum+1);
		strFilePath = strFilePathWork + "*.g";
	}
	else
	{
		return bContinous;
	}
    
	////// find the file and check if bcontinous
	//preName
	nPos = strWorkName.FindOneOf("_");
	if (nPos == (-1))
	{
		return bContinous;
	}
	else
	{
		strPreName = strWorkName.Left(nPos);
	}
	//Sheet
	CString strTemp= strWorkName.Mid(nPos+1);
	nPos = strTemp.FindOneOf("_");
	if (nPos == (-1))
	{
		return bContinous;
	}
	else
	{
		nSheet = atoi(strTemp.Left(nPos));
	}
    //BackName
	strTemp = strTemp.Mid(nPos+1);
	nPos = strTemp.FindOneOf("_");
	if (nPos == (-1))
	{
		return bContinous;
	}

	strBackName = strTemp.Mid(nPos+1);
	////////////////////////////////////////////

	CFileFind cFinder;
	BOOL bWorking = FALSE;
	bWorking = cFinder.FindFile(_T(strFilePath));  //�����ļ��ĺ�׺��
	
    while (bWorking)
    {
        bWorking = cFinder.FindNextFile();
		strTemp ="";
		//strprename
		strTemp = cFinder.GetFileName();
		nPos = strTemp.FindOneOf("_");
		if (nPos != (-1))
		{
			if(strPreName == strTemp.Left(nPos))
			{ 
				//sheet
				strTemp = strTemp.Mid(nPos+1);
				nPos = strTemp.FindOneOf("_");
				if (nPos != -1)
				{
					CString sz = strTemp.Left(nPos);
					if ((nSheet + 1) == atoi(strTemp.Left(nPos)))
					{  
						//nCount
						strTemp = strTemp.Mid(nPos+1);
						nPos = strTemp.FindOneOf("_");
						if (nPos != (-1))
						{   
							nCount = atoi(strTemp.Left(nPos));
							strTemp = strTemp.Mid(nPos +1);
							if (strBackName == strTemp)
							{
								bContinous = TRUE; 
								if(m_nGlassNo == 2)
									m_iSetNum = nCount*3;
								else if(m_nGlassNo == 1)
									m_iSetNum = nCount*2;
								else
									m_iSetNum = nCount;
								OnPrepare(2);
								m_bDlgPath = FALSE;
								g_strShowName = cFinder.GetFileName();
								g_strGfile = strFilePathWork + g_strShowName;						
							}
						}
					}
				}
			}
		}
	}
	return bContinous;
}

void CBenderDlg::MachineZeroAlarm(BOOL bLanguage)
{
	
	CDlg_AfxMessage  Message;
	Message.bYesNo = FALSE;
	if(bLanguage)
	{
		Message.strAfxYES ="OK";
		Message.strAfxTitle ="Machine Zero";
		Message.strAfxMessage ="Please run machine zero first !";
	}
	else
	{
		Message.strAfxYES ="ȷ��";
		Message.strAfxTitle ="��е����";
		Message.strAfxMessage ="���Ƚ��л�е���㣡";
	} 
	Message.DoModal(); 
}

int CBenderDlg::HardDogCheck()
{ 		
	haspStatus status; 
	Chasp hasp2(ChaspFeature::defaultFeature());
	status = hasp2.login(vendorCode);
	if (!HASP_SUCCEEDED(status))
    {  
		HarddogExit();
        return 1;
    }	
	std::string infoTemplate ="<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
		"<haspformat root=\"haspscope\">"
		"<hasp>"
		"<attribute name=\"id\" />"
		"</hasp>"
		"</haspformat>";
	
    //The output of the getInfo call
    std::string resultingScope;
    status = hasp2.getSessionInfo(infoTemplate, resultingScope); 
    if (!HASP_SUCCEEDED(status))
    { 
		
		HarddogExit();
        return 1;
    }	
    if (HASP_SUCCEEDED(status))
        hasp2.logout(); 
	return 0;	
}

int CBenderDlg::GetHarddogTime(int nFirst)
{ 
	haspStatus status; 
	Chasp hasp1(ChaspFeature::defaultFeature());
	status = hasp1.login(vendorCode);
	if (!HASP_SUCCEEDED(status))
    {  
		for (int n=0; n<3; n++)
		{
			Sleep(100);
			status = hasp1.login(vendorCode);
			if (HASP_SUCCEEDED(status))
			{
				break;
			}
		}
		if (!HASP_SUCCEEDED(status))
		{
			HarddogExit();
			return 1;
		}
    }	
    ChaspTime haspTime;
	unsigned int day, month, year, hour, minute, second;
    status = hasp1.getRtc(haspTime); 
    if (HASP_SUCCEEDED(status))
	{ 
		hasp_hasptime_to_datetime(haspTime, &day, &month, &year, &hour, &minute, &second);
	}
	else
	{
		Sleep(100);
		status = hasp1.getRtc(haspTime);
		if (HASP_SUCCEEDED(status))
		{
			hasp_hasptime_to_datetime(haspTime, &day, &month, &year, &hour, &minute, &second);
		}
		else
		{
			HarddogExit();
			return 1;
		}
	}
	
    if (HASP_SUCCEEDED(status))
        hasp1.logout();
	
	g_stCurrTime.wYear = year;
	g_stCurrTime.wMonth = month;
	g_stCurrTime.wDay = day;
	g_stCurrTime.wHour = 0;
	g_stCurrTime.wMinute = 0;
	g_stCurrTime.wSecond = 0;

	for (int i=0; i<6;i++)
	{
        g_arr_strLimit[0][i] = "0";
	}
	HasReadValue(g_arr_strLimit[0][0],TIME_YEAR);//���ܵ�ʱ��
	HasReadValue(g_arr_strLimit[0][1],TIME_MONTH);//���ܵ�ʱ��
	HasReadValue(g_arr_strLimit[0][2],TIME_DAY);//���ܵ�ʱ��
	HasReadValue(g_arr_strLimit[0][3],TIME_SECRET);//���ܵ�����
	HasReadValue(g_arr_strLimit[0][4],TIME_VENDER);//���ܵĳ��Һ�
	HasReadValue(g_arr_strLimit[0][5],CONTROLVER);//��������
	if (g_arr_strLimit[0][5] != "0")
	{
		char chVersion[80]={0};
		LONG lReg = g_Controller.Command("MG_BN", chVersion, sizeof(chVersion));
		if(lReg == 0)
		{
			if(atoi(g_arr_strLimit[0][5]) != atoi(chVersion))
			{
				if(!g_iLanguage)    	MessageBox("�������ͼ��ܹ���ƥ�䣬���빩Ӧ����ϵ��","��ʾ",MB_OK);
				else					MessageBox("The Wrong controller version with the secret, Connect the provider please!","Hint",MB_OK);
				OnButtonStop();
				theApp.ShutDown();
			}
		}
	}
	OnCheckPassword(nFirst);
	return 0;
}
void CBenderDlg::HarddogExit()
{
	KillTimer(1);				
	KillTimer(2);		
//	KillTimer(3);				
	KillTimer(6);		
	KillTimer(8);
	KillTimer(10);	
	OnButtonStop();
	if (g_stu_pAxisF->bSpareA == TRUE)//���ŷ�ʽ
    {
		CloseMsCom();
    }
	if(g_iLanguage)
	{
		AfxMessageBox("hard lock error");
	}
	else
	{
		AfxMessageBox("���ܹ�����");
	}
//	CDialog::OnOK();
//	exit(2);
	PostMessage(WM_CLOSE,0,0);
}

//����ȫ����ʾ��Χ
void CBenderDlg::CalculateZoom()
{
    m_pInf = g_Dmcgc.GetShowInf();
	if (m_pInf->nX>0 && m_pInf->nY>0)
	{
        SetRange(m_pInf->nX,m_pInf->nY);
		m_PVM.SetAdditionInf(m_pInf);
	}
	double dXY = ((double)m_rct.right/(double)m_rct.top);
	if (dXY > 1.56)
    {
		m_PVM.SetMaxShow(690.0/m_rct.right);
    }
	else
	{
		m_PVM.SetMaxShow(430.0/m_rct.top);
	}

}

//�õ��Ƿ��ϵ�ػ�е��㣬1�أ�0û�ء�
int  CBenderDlg::GetZeroState()
{
//	return 1;
    char chZero[80] = {0};
	g_Controller.Command("MG homecx&homecy&homecz",chZero,sizeof(chZero));
	return atoi(chZero);
}

//��ʼ������λ
void CBenderDlg::InitSoftLimit()
{
	g_lRc = g_Controller.Command("MachX=1;MachY=1");
	g_Controller.Command("FL2147483647,2147483647;BL-2147483647,-2147483647");
	CString		strTemp;
    char szCmd[80]={0};
	strTemp.Format("nSFLX=%.0f;nSFLY=%.0f",
		g_stu_pAxisA->l_Journey_positive * g_stu_pAxisA->d_pulse_user,
		g_stu_pAxisB->l_Journey_positive * g_stu_pAxisB->d_pulse_user);
	strcpy(szCmd,LPCTSTR(strTemp));
	LONG l_Rec = g_Controller.Command(szCmd);
	if (l_Rec != 0)
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
			Message.strAfxYES ="ȷ��";
			Message.strAfxTitle ="����������";
			Message.strAfxMessage ="��ȫ���ϵ磬���������豸��";
		} 
		Message.DoModal(); 	
		return ;
	}
	strTemp.Format("nSBLX=%.0f;nSBLY=%.0f",
		g_stu_pAxisA->l_Journey_negative * g_stu_pAxisA->d_pulse_user,
		g_stu_pAxisB->l_Journey_negative * g_stu_pAxisB->d_pulse_user);
	strcpy(szCmd,LPCTSTR(strTemp));
	l_Rec = g_Controller.Command(szCmd);
	if (l_Rec != 0)
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
			Message.strAfxYES ="ȷ��";
			Message.strAfxTitle ="����������";
			Message.strAfxMessage ="��ȫ���ϵ磬���������豸��";
		} 
		Message.DoModal(); 	
		return ;
	}

}

//�õ���չ��ʾ���Ĳ������Ƿ�����չ��ʾ����X Y �ֱ���
void CBenderDlg::GetExpandShowInf()
{
	m_nExpandX = GetSystemMetrics(78);	
	m_nExpandY = GetSystemMetrics(79);
	if (m_nExpandX>1024 || m_nExpandY>768)
	{
		m_bExpandShow = TRUE;
		g_pDlgShowExtra->m_nShowExpandX = m_nExpandX - 1024;
		g_pDlgShowExtra->m_nShowExpandY = m_nExpandY;
	}
}

//��ʾ��չ��ʾ��
void CBenderDlg::ShowExpand()
{
	if (m_bExpandShow)
	{
		if (g_pDlgShowExtra != NULL)
		{
			g_pDlgShowExtra->SetMaxShow(g_dExtraX,g_dExtraY);	
			if (g_pDlgShowExtra->GetSafeHwnd()==0)
			{
				g_pDlgShowExtra->Create(IDD_DIALOG_SHOWEXTRA, this);
			}
			else
			{
				g_pDlgShowExtra->ShowWindow(SW_SHOW);//SW_HIDE
			}
			if (g_pDlgShowExtra->GetSafeHwnd()!=NULL)
			{
				g_pDlgShowExtra->Invalidate(TRUE);
			}
			this->SetFocus();
		}
	}	
}
//������һ��ͼ�ε����ݣ�Ϊ��μӹ�����ʾ��
void CBenderDlg::CopyPreShowInf()
{
	if (m_bExpandShow && g_pDlgShowExtra != NULL)
	{	
		m_PVM.AddExtraShowData();
		g_Dmcgc.CopyExtraSmall();
		g_pShowSmall = g_Dmcgc.GetExtraSmall();
		g_dExtraX = (double)m_rct.right;
		g_dExtraY = (double)m_rct.top;
		m_captionFile.GetWindowText(g_strExtraFile);
	}
}

void CBenderDlg::ConvertDxfToGcode()
{
	DxftoG.SetSortOrder(g_stu_pAxisD->bSpare, g_stu_pAxisD->bSpareA, (int)g_stu_pAxisE->sSpare);
	int nDxf = DxftoG.SetInputFile((char*)((const char*)g_strGfile));
	if(nDxf>0)
	{
		if(!g_iLanguage)
			AfxMessageBox("�汾�Ų��ԣ���ʹ��R12���DXF�ļ���");
		else
			AfxMessageBox("File Version Error,Plase Change To R12 Dxf File!");
		return;
	}	
	DxftoG.SetDownOperation("M13\n");
	DxftoG.SetUpOperation("M14\n");
	
	DxftoG.SetHeadTailHomeOperation("","","");
	
	g_strGfile = g_strOriginalPathC + "dxf.g";
	DxftoG.SetOutputFile((char*)((const char*)g_strGfile));
}

//����test����Ĺ���
void CBenderDlg::RunTest(int nValue)
{
	if(g_Dmcgc.GetPauseflag())
	{
		g_Dmcgc.OnContinue();
		g_handdll.SetOut(OUT_LED_RUN,TRUE);
		g_handdll.SetOut(OUT_LED_STOP,FALSE);
		m_UbtPause.SelectState(NULL);
		return;
	}
	if(g_Dmcgc.GetRunflag())	
		return;//û�д��ļ����򷵻�
	
	g_Dmcgc.SetOilingOption(g_stu_pAxisG->dSpareE, g_stu_pAxisH->dSpareE,m_strDmcAV); 
    WriteOilingDmc();		
	if(OnBegoreRunCheck())
	{
		if (nValue != 6)
		{
			if(0 == OnSetRunState())			/* д����Ƭ̨�ȴ�����λ�� */
				return;
			m_bRunFlag = TRUE;
			OnDirectRun();
		}
		else
		{
			m_bRunFlag = TRUE;
			m_pAffirm->m_dLength = m_rct.right;
			m_pAffirm->m_dHeight = m_rct.top;
			if(m_pAffirm->GetSafeHwnd()==0)
			{
				m_pAffirm->Create(IDD_DIALOG_AFFIRM, this);				
			}			
		}
	}
}

//��ʼ�и����ؼӼ���
void CBenderDlg::DownAccDcc()
{
	char szCmd[80]={0};
	sprintf(szCmd,"VA%.0f;VD%.0f",
		g_stu_pAxisA->d_vacc * g_stu_pAxisA->d_pulse_user,
		g_stu_pAxisA->d_vdec * g_stu_pAxisA->d_pulse_user);						
	g_Controller.Command(szCmd);
}
void CBenderDlg::OnClickPlaninfoctrlSpeed() 
{
	// TODO: Add your control notification handler code here
	if (g_iMode == MODE_MAIN || g_iMode == MODE_C)
	{
		int iIndex = (int)m_ocxPlanSpeed.GetClickIndex();
		if (iIndex>0 && iIndex<130)
		{
			m_ocxPlanSpeed.SetValue((float)iIndex);	
			if(g_iMode == MODE_MAIN)
			{
				double  dNumsp[3];
				int     i;	
				for(i=0;i<3;i++)
				{
					dNumsp[i] = g_pstu_control->axis[i].d_rapid * g_pstu_control->axis[i].d_pulse_user;
				}
				g_Dmcgc.SetRate((long)iIndex,dNumsp); 
			}
			else if (g_iMode == MODE_C)
			{
				g_handdll.SetHandRateSpeed((long)iIndex);
			}
		}	
	}
}

//���沣����綨λ�Ժ��ƫ�Ʋ������ϵ������
void CBenderDlg::SaveLightPar()
{
    CString strText;
	strText.Format("%.4f",pCoorx.x);
	WritePrivateProfileString("RESUME","COORXX",strText,"D:\\Program files\\GlassCutter\\Resume.ini");
	strText.Format("%.4f",pCoorx.y);
	WritePrivateProfileString("RESUME","COORXY",strText,"D:\\Program files\\GlassCutter\\Resume.ini");
	strText.Format("%.4f",pCoor.x);
	WritePrivateProfileString("RESUME","COORX",strText,"D:\\Program files\\GlassCutter\\Resume.ini");
	strText.Format("%.4f",pCoor.y);
	WritePrivateProfileString("RESUME","COORY",strText,"D:\\Program files\\GlassCutter\\Resume.ini");
	strText.Format("%.4f",pCoory.x);
	WritePrivateProfileString("RESUME","COORYX",strText,"D:\\Program files\\GlassCutter\\Resume.ini");
	strText.Format("%.4f",pCoory.y);
	WritePrivateProfileString("RESUME","COORYY",strText,"D:\\Program files\\GlassCutter\\Resume.ini");
}

//�õ�������綨λ�Ժ��ƫ�Ʋ������ϵ������
void CBenderDlg::GetLightPar()
{
	CString strPara;
	GetPrivateProfileString("RESUME","COORXX","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,"D:\\Program files\\GlassCutter\\Resume.ini");
	pCoorx.x = atof(strPara);
	GetPrivateProfileString("RESUME","COORXY","1.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,"D:\\Program files\\GlassCutter\\Resume.ini");
	pCoorx.y = atof(strPara);
	GetPrivateProfileString("RESUME","COORX","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,"D:\\Program files\\GlassCutter\\Resume.ini");
	pCoor.x = atof(strPara);
	GetPrivateProfileString("RESUME","COORY","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,"D:\\Program files\\GlassCutter\\Resume.ini");
	pCoor.y = atof(strPara);
	GetPrivateProfileString("RESUME","COORYX","1.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,"D:\\Program files\\GlassCutter\\Resume.ini");
	pCoory.x = atof(strPara);
	GetPrivateProfileString("RESUME","COORYY","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,"D:\\Program files\\GlassCutter\\Resume.ini");
	pCoory.y = atof(strPara);
}

//��ʼ��������ť
void CBenderDlg::InitRgnButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_ZEOR1);	
	

//�ļ�
	m_main1.SetFont(&g_fontButton);
	m_main1.SetBitMapID(IDB_BITMAP_FILE1,IDB_BITMAP_FILE2);	
	m_main1.Create(g_arr_strBender[8][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(20, 714), c, this, IDC_BUTTON1); 
//�༭  	
	m_main7.SetFont(&g_fontButton);
	m_main7.SetBitMapID(IDB_BITMAP_EDIT1,IDB_BITMAP_EDIT2);	
	m_main7.Create(g_arr_strBender[18][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(165, 714), c, this, IDC_BUTTON7); 
//�Ż�
	if(g_stu_pAxisE->bSpare)/* �Ƿ��������Ż����� */
	{
		m_main6.SetFont(&g_fontButton);
		m_main6.SetBitMapID(IDB_BITMAP_GRAP1,IDB_BITMAP_GRAP2);	
		m_main6.Create(g_arr_strBender[17][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(310, 714), c, this, IDC_BUTTON6); 
	}
//����	
	m_main5.SetFont(&g_fontButton);
	m_main5.SetBitMapID(IDB_BITMAP_SETTING1,IDB_BITMAP_SETTING2);	
	m_main5.Create(g_arr_strBender[16][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(455, 714), c, this, IDC_BUTTON5); 
//����
	CString str[2];
	str[0] =  "����";
	str[1] = "Start";
	m_mainStart.SetFont(&g_fontButton);
	m_mainStart.SetBitMapID(IDB_BITMAP_STRAT1,IDB_BITMAP_STRAT2);	
	m_mainStart.Create(str[g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(600, 714), c, this, IDC_BUTTON_BTNSTART); 
//ֹͣ
	str[0] =  "ֹͣ";
	str[1] = "Stop";
	m_mainStop.SetFont(&g_fontButton);
	m_mainStop.SetBitMapID(IDB_BITMAP_STOP1,IDB_BITMAP_STOP2);	
	m_mainStop.Create(str[g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(745, 714), c, this, IDC_BUTTON_BTNSTOP); 
	
//�˳�	
	m_main10.SetFont(&g_fontButton);
	m_main10.SetBitMapID(IDB_BITMAP_CLOSE1,IDB_BITMAP_CLOSE2);	
	m_main10.Create(g_arr_strBender[7][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(890, 714), c, this, IDC_BUTTON10); 

//�Զ�
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_FORWARD1);
	m_main9.SetFont(&g_fontEdit);
	m_main9.SetBitMapID(IDB_BITMAP_AUTO1,IDB_BITMAP_AUTO2);	
	m_main9.Create(g_arr_strBender[2][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(722, 310), c, this, IDC_BUTTON9);
//�ֶ�	
	m_main3.SetFont(&g_fontEdit);
	m_main3.SetBitMapID(IDB_BITMAP_HAND1,IDB_BITMAP_HAND2);	
	m_main3.Create(g_arr_strBender[14][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(824, 310), c, this, IDC_BUTTON3); 	
//����
	m_main4.SetFont(&g_fontEdit);
	m_main4.SetBitMapID(IDB_BITMAP_HOME1,IDB_BITMAP_HOME2);	
	m_main4.Create(g_arr_strBender[15][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(923, 310), c, this, IDC_BUTTON4); 
	
	DeleteObject(c);

//С��ť
	HRGN r; 
	r = CreateRectRgn(0, 0, 59, 30);
//�и�
	m_main8.SetFont(&g_fontList);
	m_main8.HaveBitmap(1);
	m_main8.SetBitMapID(IDB_BITMAP_NULL2,IDB_BITMAP_NULL1);	
	m_main8.Create(g_arr_strBender[9][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(2, 210), r, this, IDC_BUTTON8);
//���  
	m_main2.SetFont(&g_fontList);
	m_main2.HaveBitmap(1);
	m_main2.SetBitMapID(IDB_BITMAP_NULL2,IDB_BITMAP_NULL1);	
	m_main2.Create(g_arr_strBender[13][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(61, 210), r, this, IDC_BUTTON2);
//ɨ��
	m_UbtnScan.SetFont(&g_fontList);
	m_UbtnScan.HaveBitmap(1);
	m_UbtnScan.SetBitMapID(IDB_BITMAP_NULL2,IDB_BITMAP_NULL1);	
	m_UbtnScan.Create(g_arr_strBender[6][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(120, 210), r, this, IDC_BUTTON_SCAN);
//����
	m_UbtnTest.SetFont(&g_fontList);
	m_UbtnTest.HaveBitmap(1);
	m_UbtnTest.SetBitMapID(IDB_BITMAP_NULL2,IDB_BITMAP_NULL1);	
	m_UbtnTest.Create(g_arr_strBender[10][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(179, 210), r, this, IDC_BUTTON_TEST);	
//��ˮ
	if (g_stu_pAxisB->bSpare == TRUE)
	{
		
		if (g_iLanguage == 0)
			str[0] = "����";
		else
			str[1] = "Line";
	}
	else
	{		
		if (g_iLanguage == 0)
			str[0] = "����";
		else
			str[1] = "Along";
	}	
	m_UbtWater.SetFont(&g_fontList);
	m_UbtWater.HaveBitmap(1);
	m_UbtWater.SetBitMapID(IDB_BITMAP_NULL2,IDB_BITMAP_NULL1);
	m_UbtWater.Create(str[g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(356, 210), r, this, IDC_BUTTON_VIEW);
	if (g_stu_pAxisB->bSpare == TRUE)
	{
		
		m_UbtWater.SelectState(NULL);
	}
	else
	{		
		m_UbtWater.SelectState(IDB_BITMAP_NULL3);
	}
//��ͣ
	m_UbtPause.SetFont(&g_fontList);
	m_UbtPause.HaveBitmap(1);
	m_UbtPause.SetBitMapID(IDB_BITMAP_NULL2,IDB_BITMAP_NULL1);	
	m_UbtPause.Create(g_arr_strBender[4][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(297, 210), r, this, IDC_BUTTON_PAUSE);
	
//��ת��
	CString strOil;
	if (g_iLanguage == 0)
	{
		if (g_stu_pAxisH->bSpareE==FALSE)
		{
			strOil = "ע��A";
		}
		else
		{
			strOil = "ע��B";
		}
	}
	else
	{
		if (g_stu_pAxisH->bSpareE==FALSE)
		{
			strOil = "Oil A";
		}
		else
		{
			strOil = "Oil B";
		}
	}
	m_UbtOilAB.SetFont(&g_fontList);
	m_UbtOilAB.HaveBitmap(1);
	m_UbtOilAB.SetBitMapID(IDB_BITMAP_NULL2,IDB_BITMAP_NULL1);	
	m_UbtOilAB.Create(strOil, WS_CHILD | WS_VISIBLE, CPoint(238, 210), r, this, IDC_BUTTON_OILAB);
	DeleteObject(r);

//С��ť
	HRGN g; 

#ifdef POWERLAND
	g = CreateEllipticRgn(0,0,30,30);
#else
	g = CreateRectRgn(0,0,28,28);//����
#endif	 

//FIRST
	m_UbtFirst.SetBitMapID(IDB_BITMAP_FIRST2,IDB_BITMAP_FIRST1);	
	m_UbtFirst.Create("", WS_CHILD | WS_VISIBLE, CPoint(416, 212), g, this, IDC_BUTTON_FIRST);
//PRE
	m_UbtPre.SetBitMapID(IDB_BITMAP_PRE2,IDB_BITMAP_PRE1);	
	m_UbtPre.Create("", WS_CHILD | WS_VISIBLE, CPoint(446, 212), g, this, IDC_BUTTON_PRE);
//NEXT
	m_UntNext.SetBitMapID(IDB_BITMAP_NEXT2,IDB_BITMAP_NEXT1);	
	m_UntNext.Create("", WS_CHILD | WS_VISIBLE, CPoint(658, 212), g, this, IDC_BUTTON_NEXT);
//LAST
	m_UbtLast.SetBitMapID(IDB_BITMAP_LAST2,IDB_BITMAP_LAST1);	
	m_UbtLast.Create("", WS_CHILD | WS_VISIBLE, CPoint(688, 212), g, this, IDC_BUTTON_LAST);
	DeleteObject(g);

//�ٶ�ѹ��
	HRGN n; 
	n = CreateRectRgn(0, 0, 0, 0); 
//speed down
	GetBitMapRgn(GetDC(),n,IDB_BITMAP_SPDW1);
	m_btnHome.SetBitMapID(IDB_BITMAP_SPDW1,IDB_BITMAP_SPDW2);	
	m_btnHome.Create("", WS_CHILD | WS_VISIBLE, CPoint(375, 95), n, this, IDC_BUTTON_END);
//press down
	m_UbnPressDn.SetBitMapID(IDB_BITMAP_SPDW1,IDB_BITMAP_SPDW2);	
	m_UbnPressDn.Create("", WS_CHILD | WS_VISIBLE, CPoint(375, 155), n, this, IDC_BUTTON_PRESSDOWN);
//speed up
	GetBitMapRgn(GetDC(),n,IDB_BITMAP_SPUP1);
	m_btnEnd.SetBitMapID(IDB_BITMAP_SPUP1,IDB_BITMAP_SPUP2);	
	m_btnEnd.Create("", WS_CHILD | WS_VISIBLE, CPoint(673, 95), n, this, IDC_BUTTON_HOME);
//press up
	m_UbnPressUp.SetBitMapID(IDB_BITMAP_SPUP1,IDB_BITMAP_SPUP2);	
	m_UbnPressUp.Create("", WS_CHILD | WS_VISIBLE, CPoint(673, 155), n, this, IDC_BUTTON_PRESSUP);
	DeleteObject(n);
}

void CBenderDlg::OnButtonTest() 
{
	// TODO: Add your control notification handler code here

	if(g_Dmcgc.GetRunflag())	
		return;
	if (g_iMode == MODE_MAIN)
	{
		if (g_nTestRun == 0)
		{
			if(m_pTestDlg->GetSafeHwnd() == NULL)
			{
				m_pTestDlg->Create(IDD_DIALOG_TEST, this);
			}				
			g_nTestRun = 1;
			m_UbtnTest.SelectState(IDB_BITMAP_NULL3);			
		}
		else
		{
			if(m_pTestDlg->GetSafeHwnd() != NULL)
			{
				m_pTestDlg->DestroyWindow();			
				g_nTestRun = 0;
				m_UbtnTest.SelectState(NULL);			
			}			
		}		
	}

}

void CBenderDlg::OnButtonScan() 
{
	if(g_Dmcgc.GetRunflag())	
		return;
	if (g_iMode == MODE_MAIN)
	{
		m_UbtnTest.SelectState(NULL);    		
		OnInit2DDrawShow();
		g_iMode = MODE_F;
		if(m_pScanDlg->GetSafeHwnd() == NULL)
		{
			m_pScanDlg->InitParameter();
			m_pScanDlg->Create(IDD_DIALOG_SCAN, this);
		}
		m_UbtnScan.SelectState(IDB_BITMAP_NULL3); 		
		m_main9.SelectState(NULL);
	}
	else if(g_iMode == MODE_F)
	{
		if(m_pScanDlg->GetSafeHwnd() != NULL)
		{
			m_pScanDlg->OnButtonCs10();
			m_pScanDlg->DestroyWindow();			
			m_UbtnScan.SelectState(NULL);
			m_main9.SelectState(IDB_BITMAP_AUTO3);
			g_iMode = MODE_MAIN;
		}
	}
}

void CBenderDlg::OnButtonView() 
{
	// TODO: Add your control notification handler code here
	CString str;	
	if (g_stu_pAxisB->bSpare==FALSE)
	{
		g_stu_pAxisB->bSpare = TRUE;
		if (g_iLanguage == 0)
			str = "����";
		else
			str = "Line";
		m_UbtWater.SelectState(NULL);
	}
	else
	{
		g_stu_pAxisB->bSpare = FALSE;
		if (g_iLanguage == 0)
			str = "����";
		else
			str = "Along";
		m_UbtWater.SelectState(IDB_BITMAP_NULL3);
	}
	m_UbtWater.SetWindowText(str);
	m_UbtWater.RepeatDraw();	
	g_machinedll.ParameterSave((char*)((const char*)(g_strOriginalPathD + "machine.ini")));/* �����е������Ϣ */
}

void CBenderDlg::OnButtonFirst() 
{
	if(g_Dmcgc.GetRunflag())     
		return;
	if (g_iMode == MODE_F)
	{
		return;
	}
	if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1)			
	{
		OnShowMessageBox(22,g_iLanguage,FALSE);
		return;
	}
	FineFile(2);
}

void CBenderDlg::OnButtonPre() 
{
	if(g_Dmcgc.GetRunflag())     
		return;
	if (g_iMode == MODE_F)
	{
		return;
	}
	if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1)			
	{
		OnShowMessageBox(22,g_iLanguage,FALSE);
		return;
	}
	FineFile(0);
}

void CBenderDlg::OnButtonNext() 
{
	if(g_Dmcgc.GetRunflag())     
		return;
	if (g_iMode == MODE_F)
	{
		return;
	}
	if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1)			
	{
		OnShowMessageBox(22,g_iLanguage,FALSE);
		return;
	}
	FineFile(1);
}

void CBenderDlg::OnButtonLast() 
{
	if(g_Dmcgc.GetRunflag())     
		return;
	if (g_iMode == MODE_F)
	{
		return;
	}
	if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1)			
	{
		OnShowMessageBox(22,g_iLanguage,FALSE);
		return;
	}
	FineFile(3);
}

//��ʼ������״̬���и�/�����У�run����
void CBenderDlg::InitRunState()
{
	g_Dmcgc.SetRunOption(g_nRunState, g_stu_pAxisA->bSpareA);
}

void CBenderDlg::OnClickPlaninfoPress() 
{
	// TODO: Add your control notification handler code here
	if (g_iMode == MODE_C && m_pHandDlg->GetSafeHwnd()!=NULL)
	{
		float iIndex = (int)m_ocxPlanPress.GetClickIndex();
		m_ocxPlanPress.SetValue(iIndex);
		SetAOorOF(iIndex);		
	}	
}

void CBenderDlg::OnButtonState() 
{
	// TODO: Add your control notification handler code here
	CDlg_MachineCase	DlgState;
	for(int i=0;i<8;i++)
	{
		DlgState.nData[i] = 255 - nNewInput[i];/* �Ƶ�״̬ȡ�� */
	}
	int iMode =  g_iMode; 
	g_iMode = MODE_H;
	DlgState.DoModal();
	g_iMode = iMode;

}

//��ʼ����ʾ��Ϣ
void CBenderDlg::InitGridInf()
{
#ifndef POWERLAND
	m_listGrid.SetBkColor(BACKCOLOR);
	m_listGrid.SetTextBkColor(BACKCOLOR);
#else
	m_listGrid.SetBkColor(RGB(214,226,247));
	m_listGrid.SetTextBkColor(RGB(214,226,247));
#endif
	m_listGrid.SetFont(&g_fontEdit);
	int a = m_listGrid.GetExtendedStyle();
	m_listGrid.SetExtendedStyle(LVS_EX_GRIDLINES&(~LVS_EX_ONECLICKACTIVATE));
    m_listGrid.SetRowHeigt(30);
	m_listGrid.InsertColumn(0,"",LVCFMT_CENTER,140,1);
	m_listGrid.InsertColumn(1,"",LVCFMT_CENTER,152,1);
    m_listGrid.InsertItem(0,g_arr_strBender[1][g_iLanguage]);
    m_listGrid.InsertItem(1,g_arr_strBender[0][g_iLanguage]);
	m_listGrid.InsertItem(2,g_arr_strBender[5][g_iLanguage]);
    m_listGrid.SetItemText(2,1,"00:00:00");
	CString   strtemp;
	g_nProduct = GetPrivateProfileInt("FILE","PRODUCT",0,INIFILE_LASTINF);//�ܵļӹ�����
	strtemp.Format("%d",g_nProduct);
    m_listGrid.SetItemText(1,1,strtemp); 
	CStatic *pStatic = (CStatic *)GetDlgItem(IDC_STATIC_THICK);
	if(g_iLanguage==1)
		pStatic->SetWindowText("Glass Thick"); 
	pStatic->SetFont(&g_fontStatic);

 	pStatic = (CStatic *)GetDlgItem(IDC_STATIC_THICK);
 	pStatic ->SetFont(&g_fontStatic);
 	pStatic = (CStatic *)GetDlgItem(IDC_STATICD);
 	pStatic ->SetFont(&g_fontStatic);
 	pStatic = (CStatic *)GetDlgItem(IDC_STATICD_LABEDST);
 	pStatic ->SetFont(&g_fontStatic);

	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_THICK);
	pEdit->SetFont(&g_fontEdit);

	g_stu_pAxisA->sSpareA = GetPrivateProfileInt("GLASSTHICK","THICK",0,INIFILE_ADDEXTRA);		//���
	strtemp.Format("%d",g_stu_pAxisA->sSpareA);
    pEdit->SetWindowText(strtemp);

	m_iSetNum = GetPrivateProfileInt("FILE","TOTAL",1,INIFILE_LASTINF);//�趨�ӹ�����
	pEdit = (CEdit *)GetDlgItem(IDC_EDIT1);
	pEdit->SetFont(&g_fontEdit);	
	strtemp.Format("%d",m_iSetNum);
    pEdit->SetWindowText(strtemp);

	m_iRunNum = GetPrivateProfileInt("FILE","PROCESS",0,INIFILE_LASTINF);//����ɼӹ�����
	pEdit = (CEdit *)GetDlgItem(IDC_EDIT2);
	pEdit->SetFont(&g_fontEdit);	
	strtemp.Format("%d",m_iRunNum);
    pEdit->SetWindowText(strtemp);

	m_nLabelSt = GetPrivateProfileInt("PRINT","LABELSTART",1,INIFILE_ADDEXTRA);
	pEdit = (CEdit *)GetDlgItem(IDC_EDIT_LABELST);
	pEdit->SetFont(&g_fontEdit);	
	strtemp.Format("%d",m_nLabelSt);
    pEdit->SetWindowText(strtemp);
	g_Dmcgc.SetLabelStartNum(m_nLabelSt);

	if (g_iLanguage ==1)
	{
		SetDlgItemText(IDC_STATICC,"Quantity Set");
		SetDlgItemText(IDC_STATICD,"Completed");
		SetDlgItemText(IDC_STATICD_LABEDST,"Label Start");
	}
	//�Ƿ��ӡ��ǩ
	if (GetPrivateProfileInt("PRINT","PRINT",0,INIFILE_ADDEXTRA)==0)
	{
		GetDlgItem(IDC_STATICD_LABEDST)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_LABELST)->ShowWindow(SW_HIDE);
	}    
}

void CBenderDlg::OnButtonPressdown() 
{
	// TODO: Add your control notification handler code here
	if (g_iMode == MODE_C && m_pHandDlg->GetSafeHwnd()!=NULL)
	{
		double	dAo;
		CString	strAo;
		char szRes[80]={80};
		g_Controller.Command("ao=",szRes,sizeof(szRes));
		dAo = atof(szRes);
		if(dAo>=0.1)	dAo = dAo - 0.1;
		m_ocxPlanPress.SetValue(dAo);
		SetAOorOF(dAo);	
	}
}

void CBenderDlg::OnButtonPressup() 
{
	if (g_iMode == MODE_C && m_pHandDlg->GetSafeHwnd()!=NULL)
	{
		double	dAo;
		CString	strAo;
		char szRes[80]={80};
		g_Controller.Command("ao=",szRes,sizeof(szRes));
		dAo = atof(szRes);
		if(dAo<4.0)	dAo = dAo + 0.1;
		m_ocxPlanPress.SetValue(dAo);
		SetAOorOF(dAo);		
	}
}
//nPreNext:0��ǰ1��;1���1��;2��һ��;3���һ��
//����һ���ļ� 0:û���ҵ�;1:�ҵ���һ��
int CBenderDlg::FineFile(int nPreNext)
{
	CString strPreName,strBackName;
	CString strNametype;
	CString strFilePath,strFilePathWork;//ͬһĿ¼�������ļ��������ļ���
	int nPos;
	int nSheet;	
	//check Name type .g 
	nPos = g_strShowName.ReverseFind('.');
    strNametype = g_strShowName.Mid(nPos+1);
	if (strNametype == "g" || strNametype == "G")
	{
		//����༶g�����ļ�Ŀ¼
		int nNum = g_strGfile.ReverseFind('\\');
		int nLength = g_strGfile.GetLength();
		if (nNum>nLength || nNum<0)
		{
			return 0;
		}
		strFilePathWork = g_strGfile.Left(nNum+1);		
	}
	else
	{
		return 0;
	}
    
	////// find the file and check if bcontinous
	//preName
	CString strWorkName = g_strShowName;
	int nNum = 0;//��_���ĸ���
	for (int n=0;n<strWorkName.GetLength();n++)
	{
		if (strWorkName.GetAt(n) == '_')
		{
			nNum++;
		}
	}
	if (nNum<4)
	{
        return 0;
	}
	nPos = strWorkName.Find("_");//M0000002_1_1_3660_2440.g
	strPreName = strWorkName.Left(nPos);//M0000002
	//�ļ���������
	CString strTemp= strWorkName.Mid(nPos+1);//1_1_3660_2440.g
	nPos = strTemp.Find("_");
	if (nPos == (-1))
	{
		return 0;
	}
	else
	{
		nSheet = atoi(strTemp.Left(nPos));
	}
    //BackName
	strTemp = strTemp.Mid(nPos+1);//1_3660_2440.g
	nPos = strTemp.Find("_");
	if (nPos == (-1))
	{
		return 0;
	}

	strBackName = strTemp.Mid(nPos+1);//3660_2440.g
	////////////////////////////////////////////
	if (nPreNext == 0 || nPreNext == 2)
	{
		nSheet--;
		if (nSheet<1)
		{
			return 0;
		}
	}
	else if (nPreNext == 1 || nPreNext == 3)
	{
		nSheet++;
	}
	strFilePath.Format("%s_*_*_%s",strPreName,strBackName);
	CFileFind cFinder;
	BOOL bWorking = FALSE;
	bWorking = cFinder.FindFile(_T(strFilePathWork + strFilePath)); 	
	int nFind = 0;
	CString strFindFile;//��ʱ���ļ���
	while (bWorking)
	{
		if (nPreNext == 0 || nPreNext == 1)
		{
			bWorking = cFinder.FindNextFile();
			strFindFile = cFinder.GetFileName();
			int n = strFindFile.Find("_");
			if (n>-1)
			{
			   int i = atoi(strFindFile.Mid(n+1)); 
               if(i == nSheet)
			   {				   
				   g_strShowName = cFinder.GetFileName();
				   g_strGfile = strFilePathWork + g_strShowName;
				   nFind = 1;
				   break;
			   }
			   else
			   {				   
				   continue;
			   }
			}
			else
				return 0;
		}
		bWorking = cFinder.FindNextFile();
		strFindFile = cFinder.GetFileName();
		int n = strFindFile.Find("_");
		if (n>-1)
		{
			int i = atoi(strFindFile.Mid(n+1));
			if (nPreNext == 2)
			{
				if (i<=nSheet)
				{
					g_strShowName = cFinder.GetFileName();
					g_strGfile = strFilePathWork + g_strShowName;
					nFind = 1;
					//������
					nSheet = i;
					nSheet--;
					if (nSheet<1)
					{
						break;
					}
					continue;
				}
			}
			else if (nPreNext == 3)
			{
				if (i>=nSheet)
				{
					g_strShowName = cFinder.GetFileName();
					g_strGfile = strFilePathWork + g_strShowName;
					nFind = 1;
					//������
					nSheet = i;
					nSheet++;
				}
				continue;
			}		
		}		
	}
	if (nFind == 1)
	{
		m_bDlgPath = FALSE;
		m_bFile = TRUE;
		FileOpen();
		m_bFile = FALSE;
		return 1;
	}
    return 0;
}

void CBenderDlg::OnDblClickDisplayMaininf() 
{
	if (m_ocxDisplay.GetDbClickNum() == 1)
	{
		if (g_stu_pAxisH->bSpareE)//�и�ע��B 
		{
			if(g_handdll.GetOut(OUT_CUT_OILING)==1)	    
			{
				g_handdll.SetOut(OUT_CUT_OILING,FALSE);			
#ifdef CHAOYANG
				g_handdll.SetOut(OUT_OILING,FALSE);	
#endif
			}
			else
			{
				g_handdll.SetOut(OUT_CUT_OILING,TRUE);			
#ifdef CHAOYANG
				g_handdll.SetOut(OUT_OILING,TRUE);	
#endif
			}
		}
		else//ú��ע��A 
		{
			if(g_handdll.GetOut(OUT_OILING)==1)	    
			{
				g_handdll.SetOut(OUT_OILING,FALSE);
			}
			else
			{
				g_handdll.SetOut(OUT_OILING,TRUE);
			}
		}	
	}
}

//����Ѿ��򿪵�ͼ�κ��и�켣
void CBenderDlg::OnInit2DDrawShow() 
{
	m_PVM.FreeBlocks();
	m_PVM.FreeGreens();
	g_Dmcgc.FreeDmc();
	m_PVM.Invalidate(TRUE);
	g_strGfile=="";
	m_captionFile.SetWindowText("");
}

//ˢ��bottero
void CBenderDlg::DrawBottero()
{
	double dXY = ((double)g_stu_pAxisB->sSpareA/(double)g_stu_pAxisB->sSpareB);//��������
	if (dXY > 1.56)
    {
		m_PVM.SetMaxShow(690.0/g_stu_pAxisB->sSpareA);
    }
	else
	{
		m_PVM.SetMaxShow(430.0/g_stu_pAxisB->sSpareB);
	}
	m_PVM.Invalidate();
}

//��ʼ��λ����ʾ����
void CBenderDlg::InitRPShow()
{
	GetDlgItem(IDC_STATIC_RPX)->SetFont(&g_fontRP);
	GetDlgItem(IDC_STATIC_RPY)->SetFont(&g_fontRP);
	GetDlgItem(IDC_STATIC_RPZ)->SetFont(&g_fontRP);	
	GetDlgItem(IDC_STATIC_TVX)->SetFont(&g_fontRP);
	GetDlgItem(IDC_STATIC_TVY)->SetFont(&g_fontRP);
	GetDlgItem(IDC_STATIC_TVZ)->SetFont(&g_fontRP);
}

//��ʼ���ٶ���ʾ
void CBenderDlg::OnTVShow()
{
	//TV
	double   glfx,glfy,glfz;
	CString strRes; 
	char szResponse[30]={0};
	int nPos;
	double x_pos,y_pos,z_pos;
	glfx = 0.0;
	glfy = 0.0;
	glfz = 0.0;

	LONG lRc = g_Controller.Command("TVABC",szResponse,sizeof(szResponse));
	if (lRc != 0)
	{
		return;
	}
	x_pos = (long)atoi(szResponse);
	strRes.Format("%s",szResponse);
	nPos = strRes.Find(',');			
	if( nPos != -1)
	{
		strRes = strRes.Mid(nPos+1);
		y_pos = (long)atoi(strRes);	
		nPos = strRes.Find(',');	
		if(nPos!=-1)
			z_pos = (long)atoi(strRes.Mid(nPos+1));
		
	}
	if(m_lTVX==(long)x_pos && m_lTVY==(long)y_pos && m_lTVZ==(long)z_pos)
		return ;
	
	m_lTVX = (long)x_pos;
	m_lTVY = (long)y_pos;
	m_lTVZ = (long)z_pos;
	
	glfx = x_pos / g_stu_pAxisA->d_pulse_user / 1000.0 * 60;
	glfy = y_pos / g_stu_pAxisB->d_pulse_user / 1000.0 * 60;
	glfz = z_pos / g_stu_pAxisC->d_pulse_user / 1000.0 * 60;
	if(g_stu_pAxisH->sSpare==1)
	{
		glfx = glfx / IN_TO_MM;
		glfy = glfy / IN_TO_MM;
		glfz = glfz / IN_TO_MM;
	}
	strRes.Format("%.2f",glfx);
	SetDlgItemText(IDC_STATIC_TVX,strRes);
	strRes.Format("%.2f",glfy);
	SetDlgItemText(IDC_STATIC_TVY,strRes);
	strRes.Format("%.2f",glfz);
	SetDlgItemText(IDC_STATIC_TVZ,strRes);	
}

void CBenderDlg::OnChangeEditThick() 
{
	CString strText;
	GetDlgItemText(IDC_EDIT_THICK,strText);
    g_stu_pAxisA->sSpareA = atoi(strText);
	strText.Format("%d",g_stu_pAxisA->sSpareA);
	WritePrivateProfileString("GLASSTHICK","THICK",strText,INIFILE_ADDEXTRA);
}

//����ԭƬ��Ϣ�����ݿ�
void CBenderDlg::SaveSheetToMdb()
{
	::CoInitialize(NULL);
	int i = 0;
	HRESULT hr;  
	_ConnectionPtr pConSheet = NULL;   //ADOӦ�����ݿ��ļ�
	try
	{
		hr = pConSheet.CreateInstance(__uuidof(Connection));
		if(SUCCEEDED(hr))
		{
			pConSheet->Open("Provider=MSDASQL.1;Persist Security Info=False;Data Source=sheet","","",NULL);			
		}
	}	
	catch(_com_error e)
	{
		CString strErrorMessage;
		strErrorMessage.Format("�������ݿ�ʧ�ܣ�\r\n������Ϣ%s",e.ErrorMessage());
		MessageBox(strErrorMessage);
		if (pConSheet != NULL)
		{
			pConSheet = NULL;
			::CoUninitialize();//�ͷ�COM����
		}
		return ;
	}

	_RecordsetPtr  pRecSheet;   
	CString str;
	stuSheetGlass stuData;
	stuData.timeCut = COleDateTime::GetCurrentTime();
	stuData.strRect.Format("%d*%d*%d",m_rctOrig.right,m_rctOrig.top,g_stu_pAxisA->sSpareA);
	str.Format("select * from sheet where glass = '%s' and [date] between format('%d-%d-%d','yyyy-mm-dd') and format('%d-%d-%d 23:59:59','yyyy-mm-dd hh:mm:ss')",
		stuData.strRect,stuData.timeCut.GetYear(),stuData.timeCut.GetMonth(),stuData.timeCut.GetDay(),stuData.timeCut.GetYear(),stuData.timeCut.GetMonth(),stuData.timeCut.GetDay());
    char ch[200]={0};
	strcpy(ch,str);
	try
	{
		pRecSheet.CreateInstance(__uuidof(Recordset));
		pRecSheet->Open(ch,pConSheet.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		CString strErrorMessage;
		strErrorMessage.Format("��ѯȡ�ü�¼��ʧ��!\r\n������Ϣ%s",e.ErrorMessage());
		MessageBox(strErrorMessage);
		if (pConSheet != NULL)
		{
			pConSheet->Close();
			pConSheet = NULL;
			::CoUninitialize();//�ͷ�COM����
		}
		return ;
	}
	if(pRecSheet==NULL||pRecSheet->adoEOF)
	{
        stuData.nNum = 1;
		pRecSheet->AddNew();  //�������Զ�����
		pRecSheet->PutCollect(_variant_t((long)0),_variant_t(stuData.timeCut));
		pRecSheet->PutCollect(_variant_t((long)1),_variant_t(stuData.strRect));
		pRecSheet->PutCollect(_variant_t((long)2),_variant_t((long)stuData.nNum));
    	pRecSheet->Update();
	}
	else
	{
  		_variant_t var;
		var = pRecSheet->GetCollect("num");
        stuData.nNum = var.lVal;
		pRecSheet->PutCollect(_variant_t((long)2),_variant_t((long)(stuData.nNum+1)));
		pRecSheet->Update();
	}
	pRecSheet->Close();
	pRecSheet = NULL;
	if (pConSheet != NULL)
	{
		pConSheet->Close();
		pConSheet = NULL;
		::CoUninitialize();//�ͷ�COM����
	}
}

HBRUSH CBenderDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);	

#ifdef POWERLAND
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID()==IDC_RADIO1 || pWnd->GetDlgCtrlID()==IDC_RADIO2
			||pWnd->GetDlgCtrlID()==IDC_RADIO3 || pWnd->GetDlgCtrlID()==IDC_STATIC_THICK
			||pWnd->GetDlgCtrlID()==IDC_STATICC||pWnd->GetDlgCtrlID()==IDC_STATICD
			||pWnd->GetDlgCtrlID()==IDC_STATICD_LABEDST)
		{
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);
		} 
        else
		{
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)m_brush.GetSafeHandle();
		}

	}    
#else
	if (pWnd->GetDlgCtrlID()==IDC_RADIO1 || pWnd->GetDlgCtrlID()==IDC_RADIO2
		||pWnd->GetDlgCtrlID()==IDC_RADIO3 || pWnd->GetDlgCtrlID()==IDC_STATIC_THICK
		||pWnd->GetDlgCtrlID()==IDC_STATICC||pWnd->GetDlgCtrlID()==IDC_STATICD
		||pWnd->GetDlgCtrlID()==IDC_STATICD_LABEDST)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}  
#endif				
	return hbr;
}

/* ע�͹��ܣ�����dmc */
void CBenderDlg::WriteOilingDmc() 
{
	FILE	*fAV;
	
	fAV = fopen((char *)((const char*)m_strDmcAV), "wt");//fseek rewind������ʹ��
	
	fprintf(fAV,"#AV\n");
	fprintf(fAV,"AV avon\n");
    if (g_stu_pAxisH->bSpareE)//�и�ע��
	{
		fprintf(fAV,"SB%d\n", OUT_CUT_OILING);
#ifdef CHAOYANG
		fprintf(fAV,"SB%d\n", OUT_OILING);
#endif		
	}
	else
	{
		fprintf(fAV,"SB%d\n", OUT_OILING);
		
		
	}
	fprintf(fAV,"AV avoff\n");
    if (g_stu_pAxisH->bSpareE)//�и�ע��
	{
		fprintf(fAV,"CB%d\n", OUT_CUT_OILING);
#ifdef CHAOYANG
		fprintf(fAV,"CB%d\n", OUT_OILING);
#endif
	}
	else
	{
		fprintf(fAV,"CB%d\n", OUT_OILING);
	}
	fprintf(fAV,"EN\n");
	fclose(fAV);
}

LRESULT CBenderDlg::OnEditDouble(WPARAM wParam, LPARAM lParam) 
{
	CString				strTmp;
	CDlg_KeyNumber		KeyNum;
	
	if(lParam==1)/* �д����� */
	{
		((CEdit *)GetDlgItem(wParam))->SetSel(0,-1);
		return 0;
	}
	CWnd::GetDlgItemText(wParam,strTmp);
	KeyNum.m_strNew = KeyNum.m_strOld = strTmp;	
	if(KeyNum.DoModal()==IDOK)
	{
		CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	}	
	return 0;
}

//���ֶ����ļ�ʱ������Ƿ����ļ�����׼���Զ��õ��ӹ�����
void CBenderDlg::GetSheetCount()
{
	int nPos = g_strShowName.ReverseFind('.');
    CString strNametype = g_strShowName.Mid(nPos+1);
	if (strNametype == "g" || strNametype == "G")
	{
		CString strWorkName = g_strShowName.Left(nPos);
		int nNum = 0;//��_���ĸ���
		int nIndex = 0;//�ַ��ĸ���
		for (int n=0;n<strWorkName.GetLength();n++)
		{
			if (strWorkName.GetAt(n) == '_')
			{
				nNum++;
				if(nNum == 2)//�ڶ��������Ǽӹ�����
					nIndex = n;
			}
		}
		if (nNum == 4 && nIndex != 0)//�ļ����ϸ�
		{
			int nCount = atoi(strWorkName.Mid(nIndex+1));
			if (nCount>0)
			{
				if(m_nGlassNo == 2)
					m_iSetNum = nCount*3;
				else if(m_nGlassNo == 1)
					m_iSetNum = nCount*2;
				else
                    m_iSetNum = nCount;
				OnPrepare(2);
			}
		}		
	}
}

//�ӹ���ɺ����Ӽӹ�����������ʾ
void CBenderDlg::ModifyProduct()
{
	CString strText;
	g_nProduct++;
	strText.Format("%d",(int)g_nProduct);//�ܵļӹ�����
	WritePrivateProfileString("FILE","PRODUCT",strText,INIFILE_LASTINF);
    m_listGrid.SetItemText(1,1,strText);
}

//��ȡ��ӡ��ǩ�Ĳ������Ҹ�ֵ��gdmcgc32
void CBenderDlg::InitPrintLabel()
{
	BOOL l_bPrint = (BOOL)GetPrivateProfileInt("PRINT","PRINT",0,INIFILE_ADDEXTRA);		//�Ƿ��ӡ��ǩ
	BOOL l_nLabelPos = (BOOL)GetPrivateProfileInt("PRINT","POS",1,INIFILE_ADDEXTRA);	//��ǩλ��
	g_Dmcgc.SetLabelInf((int)l_bPrint,(int)l_nLabelPos);
	int l_nLabelWT = GetPrivateProfileInt("PRINT","LABELTIME",2000,INIFILE_ADDEXTRA);
    g_Dmcgc.SetLabelTime(l_nLabelWT);
//��ǩ�ͻ�ͷƫ��,ȡ��ǩλ��Y
	int l_nLabelPosX = GetPrivateProfileInt("PRINT","LABELPOSX",0,INIFILE_ADDEXTRA);
	int l_nLabelPosY = GetPrivateProfileInt("PRINT","LABELPOSY",0,INIFILE_ADDEXTRA);
	int l_nPaperY = GetPrivateProfileInt("PRINT","PAPERY",100,INIFILE_ADDEXTRA); 
	g_Dmcgc.SetLabelPos(l_nLabelPosX,l_nLabelPosY,l_nPaperY);
}

//��ʼ�и�ʱ�ѿ�ʼ����ĸ�����Ϊ1
void CBenderDlg::SetLabelStart()
{
	if (GetPrivateProfileInt("PRINT","PRINT",0,INIFILE_ADDEXTRA)==1)
	{
		WritePrivateProfileString("PRINT","LABELSTART","1",INIFILE_ADDEXTRA);
		g_Dmcgc.SetLabelStartNum(1);
		SetDlgItemText(IDC_EDIT_LABELST,"1");
	}
}

//�ж��ǲ������һƬ�������Ƿ���true
bool CBenderDlg::JudgeLastFile()
{
	CString strPreName,strBackName;
	CString strNametype;
	CString strFilePath,strFilePathWork;//ͬһĿ¼�������ļ��������ļ���
	int nPos;
	int nSheet;	
	//check Name type .g 
	nPos = g_strShowName.ReverseFind('.');
    strNametype = g_strShowName.Mid(nPos+1);
	if (strNametype == "g" || strNametype == "G")
	{
		//����༶g�����ļ�Ŀ¼
		int nNum = g_strGfile.ReverseFind('\\');
		int nLength = g_strGfile.GetLength();
		if (nNum>nLength || nNum<0)
		{
			return false;
		}
		strFilePathWork = g_strGfile.Left(nNum+1);		
	}
	else
	{
		return false;
	}
    
	////// find the file and check if bcontinous
	//preName
	CString strWorkName = g_strShowName;
	int nNum = 0;//��_���ĸ���
	for (int n=0;n<strWorkName.GetLength();n++)
	{
		if (strWorkName.GetAt(n) == '_')
		{
			nNum++;
		}
	}
	if (nNum<4)
	{
        return false;
	}
	nPos = strWorkName.Find("_");//M0000002_1_1_3660_2440.g
	strPreName = strWorkName.Left(nPos);//M0000002
	//�ļ���������
	CString strTemp= strWorkName.Mid(nPos+1);//1_1_3660_2440.g
	nPos = strTemp.Find("_");
	if (nPos == (-1))
	{
		return false;
	}
	else
	{
		nSheet = atoi(strTemp.Left(nPos));
	}
    //BackName
	strTemp = strTemp.Mid(nPos+1);//1_3660_2440.g
	nPos = strTemp.Find("_");
	if (nPos == (-1))
	{
		return false;
	}	
	strBackName = strTemp.Mid(nPos+1);//3660_2440.g
	strFilePath.Format("%s_%d_*_%s",strPreName,nSheet+1,strBackName);
	CFileFind cFinder;
	BOOL bWorking = FALSE;
	bWorking = cFinder.FindFile(_T(strFilePathWork + strFilePath)); 	
	int nFind = 0;
	CString strFindFile;//��ʱ���ļ���
	if (bWorking == FALSE)
	{
		CDlg_AfxMessage  Message;
		Message.bYesNo = FALSE;
		if(g_iLanguage==1)
		{
			Message.strAfxYES ="OK";
			Message.strAfxTitle ="Inf";
			Message.strAfxMessage ="The Last One!";
		}
		else
		{
			Message.strAfxYES ="ȷ��";
			Message.strAfxTitle ="��ʾ";
			Message.strAfxMessage ="ϵ���ļ��ӹ����!";
		} 
		Message.DoModal(); 		
	}
	return false;
}

//�����	m_PVM.Create(this, CRect(17,260,717,703));//
void CBenderDlg::DrawRules(CDC *pDC)
{
	CPen penWhite,*pOldPen;
	penWhite.CreatePen(PS_SOLID,1,RGB(255,255,255));
    pOldPen = pDC->SelectObject(&penWhite);
	CFont   font1,font2; 
	font1.CreateFont(14,5,900,0,FW_MEDIUM,0,0,0,ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_ROMAN, "Times New Roman");  	   
	font2.CreateFont(14,5,0,0,FW_MEDIUM,0,0,0,ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_ROMAN, "Times New Roman");  	   
	CFont *pOldFont = (CFont *)pDC->SelectObject(&font1);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	double dMaxY = m_PVM.m_dZoom*m_rct.top+m_PVM.m_dBaseY-3;//������ص�
    double dAverage = dMaxY;//ÿһ�ݵ�����
	int    nNumY = 1;	
    while(dAverage>80)	
	{
		
		dAverage = dMaxY/nNumY;
        nNumY++;
	}
	if (nNumY == 1)
	{
		nNumY++;
	}
    for (int n=0; n<nNumY; n++)
    {
		int nPos = 697-int(n*dAverage+0.5);
		if (nPos>703 || nPos<260)
		{
			break;
		}
		pDC->MoveTo(13,nPos);
		pDC->LineTo(17,nPos);
		if (n == 0)
		{
			pDC->SetTextAlign(TA_LEFT|TA_BOTTOM);
		}
		else if (n == nNumY-1)
		{
			pDC->SetTextAlign(TA_RIGHT|TA_BOTTOM);
		}		
		else
		{
			pDC->SetTextAlign(TA_CENTER|TA_BOTTOM);
		}
		CString str;
		str.Format("%d",int((n*dAverage-(m_PVM.m_dBaseY-3))/m_PVM.m_dZoom+0.5));
		pDC->TextOut(15,nPos,str);
    }

	pDC->SelectObject(&font2);
	double dMaxX = m_PVM.m_dZoom*m_rct.right+m_PVM.m_dBaseX-3;//������ص�
    dAverage = dMaxX;//ÿһ�ݵ�����
	int    nNumX = 1;	
    while(dAverage>80)	
	{
		
		dAverage = dMaxX/nNumX;
        nNumX++;
	}
	if (nNumX == 1)
	{
		nNumX++;
	}
    for (n=0; n<nNumX; n++)
    {
		int nPos = int(17+3+n*dAverage+0.5);
		if (nPos>710 || nPos<18)
		{
			break;
		}
		pDC->MoveTo(nPos,256);
		pDC->LineTo(nPos,260);
		if (n == 0)
		{
			pDC->SetTextAlign(TA_LEFT|TA_BOTTOM);
		}	
		else if (n == nNumX-1)
		{
			pDC->SetTextAlign(TA_RIGHT|TA_BOTTOM);
		}
		else
		{
			pDC->SetTextAlign(TA_CENTER|TA_BOTTOM);
		}
		CString str;
		str.Format("%d",int((n*dAverage-(m_PVM.m_dBaseX-3))/m_PVM.m_dZoom+0.5));
		pDC->TextOut(nPos,258,str);
    } 
	pDC->SelectObject(pOldPen);
	penWhite.DeleteObject();
	pDC->SelectObject(pOldFont);
	font1.DeleteObject();
	font2.DeleteObject();
}

//��ʼ������
void CBenderDlg::OpenMsCom()
{
	m_MscComm.SetCommPort(1);       //ѡ��com1
	if(m_MscComm.GetPortOpen())
	{
		m_MscComm.SetPortOpen(FALSE);
		m_MscComm.SetPortOpen(TRUE);//�򿪴���
		
	}	
	if( !m_MscComm.GetPortOpen())
		m_MscComm.SetPortOpen(TRUE);//�򿪴���
	else
		AfxMessageBox("cannot open Pressure port");
	m_MscComm.SetSettings("115200,N,8,1"); 
	m_MscComm.SetRThreshold(1); 
	m_MscComm.SetInputMode(1);
	m_MscComm.SetDTREnable(TRUE);
	m_MscComm.SetRTSEnable(TRUE);
	m_MscComm.SetInputLen(0);  //���õ�ǰ���������ݳ���Ϊ0
	m_MscComm.GetInput();//��Ԥ���������������������
}

//�رմ���
void CBenderDlg::CloseMsCom()
{
	try
	{
		if(m_MscComm.GetPortOpen())
		{
			m_MscComm.SetPortOpen(FALSE);
		}	
	}
	catch(CException *e)
	{
		e->ReportError();
		e->Delete();
	}
}
//����ѹ��SendValue:����ѹ��ֵ��SendAddtr:DAͨ��0
void CBenderDlg::SetComPress(double SendValue,long SendAddtr)
{
	if (SendValue>=0.0 && SendValue<=9.9)
	{
		CString valuetemple, addtrtemple, crctemple, strallvalue = "";
		CByteArray hexdata;	
		CString strstart=":%";//:@дDA
		CString strend="&!";	
		long lSendValue = long(0xFFFF*(SendValue+10)/20);
		valuetemple = ComWordToHex(lSendValue);	//ʮ����ת���ɰ�λʮ������
		addtrtemple = ComDecToHex(SendAddtr);	//ʮ����ת������λʮ�����Ƶ�ַ	
		crctemple = AccountCRCCode("25" + valuetemple+addtrtemple);
		strallvalue = strstart + addtrtemple + valuetemple + crctemple + strend;
		//ComString2Hex(strallvalue,hexdata);
		m_MscComm.SetOutput(COleVariant(strallvalue));
		Sleep(20);	
	}
}

// ���ݵĴ�����
//////////////////////////////////////////////////////////////////////////
CString CBenderDlg::ComWordToHex(int Sendvalue)
{
	int valueHexhigh,valueHexlow;
	valueHexhigh=Sendvalue/65536;
	valueHexlow=Sendvalue%65536;
	return (ComDecToHex(valueHexhigh) + ComDecToHex(valueHexlow));
}

CString CBenderDlg::ComDecToHex(int Sendvalue)
{
	int valueHexhigh,valueHexlow;
	valueHexhigh=Sendvalue/256;
	valueHexlow=Sendvalue%256;
	return (ByteToHex(valueHexhigh) + ByteToHex(valueHexlow));
}

// ���ַ�������CRCУ��õ�����У����
CString CBenderDlg::AccountCRCCode(CString CommCRC)
{
	int crcCodeH=0,crcCodeL=0,nCarry=0;	//��λ����λ����λ���λ��λ
    CString crcCode;
	
	for (int i = 0; i <= CommCRC.GetLength()/2 - 1; i++)
	{
		crcCodeL +=  TranclateHex(CommCRC.GetAt(2*i+1));
	}	
	
	if(crcCodeL>15)
	{
		nCarry = crcCodeL/16;
		crcCodeL=crcCodeL%16;		
		crcCodeH=crcCodeH+nCarry;
	}
	for (int j = 0; j <= CommCRC.GetLength()/2 -1; j++)
	{
		crcCodeH +=  TranclateHex(CommCRC.GetAt(2*j));
	}
	if(crcCodeH>15)
		crcCodeH=crcCodeH%16;
	crcCodeL=15-crcCodeL;
	crcCodeH=15-crcCodeH;
	crcCodeL=crcCodeL+1;
	if(crcCodeL>15)
		crcCodeH=crcCodeH+1;
	//  	crcCodeL=crcCodeL-16;
	if(crcCodeH>15)
		crcCodeH=crcCodeH%16;	
	crcCode=NumToHex(crcCodeH)+NumToHex(crcCodeL);
	return crcCode;
}

CString CBenderDlg::ByteToHex(int Onum)
{
	int bHigh,bLow;
	CString strbytehigh,strbytelow;
	bHigh=Onum/16;
	bLow=Onum%16;
    strbytehigh=NumToHex(bHigh);
	strbytelow=NumToHex(bLow);
	return(strbytehigh+strbytelow);
}

// ��ʮ��������ת��Ϊ��Ӧ��ʮ�������ַ�
CString CBenderDlg::NumToHex(int Bnum)
{
    CString Hexnum="0";
	char Bytechar='A';
	if(Bnum>=0&&Bnum<=9)
        Hexnum.Format("%d",Bnum);
	if(Bnum>=10&&Bnum<=15)
	{
		Bytechar=Bnum-10+Bytechar;
		Hexnum.Format("%c",Bytechar);
	}
	return Hexnum;
}

// ��ʮ�������ַ�ת��Ϊ��Ӧ��ʮ��������
int CBenderDlg::TranclateHex(char Ccode)
{
	int HexData;
	switch(Ccode) {
	case '0':
		HexData=0;
		break;
	case '1':
		HexData=1;
		break;
	case '2':
		HexData=2;
		break;
	case '3':
		HexData=3;
		break;
	case '4':
		HexData=4;
		break;
	case '5':
		HexData=5;
		break;
	case '6':
		HexData=6;
		break;
	case '7':
		HexData=7;
		break;
	case '8':
		HexData=8;
		break;
	case '9':
		HexData=9;
		break;
	case 'A':
		HexData=10;
		break;
	case 'B':
		HexData=11;
		break;
	case 'C':
		HexData=12;
		break;
	case 'D':
		HexData=13;
		break;
	case 'E':
		HexData=14;
		break;
	case 'F':
		HexData=15;
		break;
	default:
		break;
	}	
	return HexData;
}

long CBenderDlg::SetAOorOF(double dVar) /* ����4λС�� */
{
	CString	strPress;
	if(dVar>10.0 || dVar<-0.01)
		return -1;
	if(g_stu_pAxisF->bSpareA == TRUE || g_stu_pAxisA->sSpare==2)//����ͬ��/���ڷ�ʽ
	{
		SetComPress(dVar);
		char szCmd[80]={0};
		sprintf(szCmd,"ao=%.2f",dVar);
		g_Controller.Command(szCmd);
		Sleep(30);
		SetComPress(dVar);
	}
	else 
	{
		char szCmd[80]={0};
		if(g_stu_pAxisA->sSpare==0)/* λ�÷�ʽ */
		{
			sprintf(szCmd,"AO%.2f;ao=%.2f;AO%.2f", dVar,dVar,dVar);/* ̧��ѹ�� */
		}
		else if(g_stu_pAxisA->sSpare==1)/* �ٶȷ�ʽ */
		{
			sprintf(szCmd,"OF,,,%.2f;ao=%.2f", dVar, dVar);/* ̧��ѹ�� */
		}
		g_Controller.Command(szCmd);
		Sleep(20);
		g_Controller.Command(szCmd);
	}	
	return 0;
}

void CBenderDlg::OnClickBtnMin() 
{
	if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1
		||g_handdll.GetCommandFloat((char *)((const char*)"MG_XQ"))>=0.0)	
	{
		;
	}
	else
	{
		this->ShowWindow(SW_MINIMIZE);
	}
}

//��ť����
void CBenderDlg::OnButtonBtnStart() 
{
	if(g_handdll.EmergencyState()==1)		
		return;
	if(g_handdll.GetCommandInt((char *)((const char*)"MG(_BGX|_BGY|_BGZ)"))==1
		||g_handdll.GetCommandFloat((char *)((const char*)"MG_XQ"))>=0.0)	
	{
		if(g_Dmcgc.GetPauseflag()==0)
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
			Message.strAfxYES ="ȷ��";
			Message.strAfxTitle ="�ŷ�����";
			Message.strAfxMessage ="��ȫ���ϵ磬���������豸��";
		} 
		Message.DoModal(); 		
		return;
	}
	if(OnSingleMO() > 0)
		return;
	if(g_iMode != MODE_MAIN)
		return;			
	if (GetZeroState() == 0)
	{
		MachineZeroAlarm(g_iLanguage);  
		return;
	}
	if (m_bEmreStop)
	{
		CDlg_AfxMessage Message;
		Message.bYesNo = FALSE;
		if (g_iLanguage == 0)
		{
			Message.strAfxYES = g_arr_message[44][1];
			Message.strAfxTitle = g_arr_message[1][1];
			Message.strAfxMessage = "�����´򿪼ӹ��ļ�!";
		}
		else
		{
			Message.strAfxYES = g_arr_message[44][2];
			Message.strAfxTitle = g_arr_message[1][2];
			Message.strAfxMessage = "Please open the file again";
		}
		Message.DoModal();
		return;
	}
	
	if(g_Dmcgc.GetRunflag()==1)
	{
		if(g_Dmcgc.GetPauseflag()==0)
			return;
	}			
	if (g_nTestRun == 1 && m_pTestDlg->GetSafeHwnd() != NULL)
	{
		RunTest(m_pTestDlg->m_nTestType);
		return;
	}			
	g_Dmcgc.SetOilingOption(g_stu_pAxisG->dSpareE, g_stu_pAxisH->dSpareE, m_strDmcAV); 
	WriteOilingDmc();
	g_Controller.Command("ebreak=1");/* �������и�ĵ�һƬ */			
	OnButtonRun();
}

//��ťֹͣ
void CBenderDlg::OnButtonBtnStop() 
{
	g_AlarmDll.SetAlarm(108);
	OnButtonStop();
	g_AlarmDll.DeleteAlarm(108);	
}

void CBenderDlg::OnClickButton3ddown() 
{
	m_PVM.MoveDown();
}

void CBenderDlg::OnClickButton3dup() 
{
	m_PVM.MoveUp();	
}

void CBenderDlg::OnClickButton3dleft() 
{
	m_PVM.MoveLeft();	
}

void CBenderDlg::OnClickButton3dright() 
{
	m_PVM.MoveRight();	
}

void CBenderDlg::OnClickButton3dpgup() 
{
	m_PVM.ZoomIn();	
}

void CBenderDlg::OnClickButton3dpgdn() 
{
	m_PVM.ZoomOut();	
}

void CBenderDlg::OnClickButtonDefault() 
{
	m_PVM.RestoreDisplay();	
}

void CBenderDlg::OnRadio1() 
{
	UpdateData();
	if (m_nGlassNo == 2)
	{
		WritePrivateProfileString("TURNOVER","GLASSNO","2",INIFILE_ADDEXTRA);
	}
	else if (m_nGlassNo == 1)
	{
		WritePrivateProfileString("TURNOVER","GLASSNO","1",INIFILE_ADDEXTRA);
	}
	else
	{
		WritePrivateProfileString("TURNOVER","GLASSNO","0",INIFILE_ADDEXTRA);
	}  	
}

void CBenderDlg::OnRadio2() 
{
	UpdateData();
	if (m_nGlassNo == 2)
	{
		WritePrivateProfileString("TURNOVER","GLASSNO","2",INIFILE_ADDEXTRA);
	}
	else if (m_nGlassNo == 1)
	{
		WritePrivateProfileString("TURNOVER","GLASSNO","1",INIFILE_ADDEXTRA);
	}
	else
	{
		WritePrivateProfileString("TURNOVER","GLASSNO","0",INIFILE_ADDEXTRA);
	}	   	
}

void CBenderDlg::OnRadio3() 
{
	UpdateData();
	if (m_nGlassNo == 2)
	{
		WritePrivateProfileString("TURNOVER","GLASSNO","2",INIFILE_ADDEXTRA);
	}
	else if (m_nGlassNo == 1)
	{
		WritePrivateProfileString("TURNOVER","GLASSNO","1",INIFILE_ADDEXTRA);
	}
	else
	{
		WritePrivateProfileString("TURNOVER","GLASSNO","0",INIFILE_ADDEXTRA);
	}	   	
}

void CBenderDlg::OnChangeEdit1() 
{
	UpdateData(TRUE);
	CString strText;
	strText.Format("%d",(int)m_iSetNum);
	WritePrivateProfileString("FILE","TOTAL",strText,INIFILE_LASTINF);	
}

void CBenderDlg::OnChangeEdit2() 
{
	UpdateData(TRUE);
	CString strText;
	strText.Format("%d",(int)m_iRunNum);
	WritePrivateProfileString("FILE","PROCESS",strText,INIFILE_LASTINF);
}

void CBenderDlg::OnChangeEditLabelst() 
{
	UpdateData(TRUE);
	CString strText;
	strText.Format("%d",m_nLabelSt);
	WritePrivateProfileString("PRINT","LABELSTART",strText,INIFILE_ADDEXTRA);
	g_Dmcgc.SetLabelStartNum(m_nLabelSt);	
}

//ˢ���и��ٶ���ʾ
void CBenderDlg::OnPrepare(int wParam) 
{ 
	CString strText;
	switch(wParam) 
	{
	case 2:/* �趨���� */	
		{			
			strText.Format("%d",m_iSetNum);
			SetDlgItemText(IDC_EDIT1,strText);
			WritePrivateProfileString("FILE","TOTAL",strText,INIFILE_LASTINF);
		}
		break;
	case 3:/* �ӹ����� */
		{
			strText.Format("%d",m_iRunNum);
			SetDlgItemText(IDC_EDIT2,strText);
			WritePrivateProfileString("FILE","PROCESS",strText,INIFILE_LASTINF);
		}
		break;
	default:																		
		break;
	}
}

//��ʾ����
void CBenderDlg::ShowAlarm()
{
	if (m_bAlarm[0])
	{   
		if(g_iLanguage==0)
			m_CapAlarm.SetCaption("��ͣ");
		else
			m_CapAlarm.SetCaption("Emergency");
	}
	else if (m_bAlarm[1])
	{
		if(g_iLanguage==0)
			m_CapAlarm.SetCaption("X��������λ");
		else
			m_CapAlarm.SetCaption("X-axis reverse");
	}
	else if (m_bAlarm[2])
	{
		if(g_iLanguage==0)
			m_CapAlarm.SetCaption("X�Ḻ����λ");
		else
			m_CapAlarm.SetCaption("X-axis forward");
	}
	else if (m_bAlarm[3])
	{
		if(g_iLanguage==0)
			m_CapAlarm.SetCaption("Y��������λ");
		else
			m_CapAlarm.SetCaption("Y-axis reverse");
	}
	else if (m_bAlarm[4])
	{
		if(g_iLanguage==0)
			m_CapAlarm.SetCaption("Y�Ḻ����λ");
		else
			m_CapAlarm.SetCaption("Y-axis forward");
	}
	else if (m_bAlarm[7] && g_stu_pAxisF->bSpareA == TRUE)
	{
		if(g_iLanguage==0)
			m_CapAlarm.SetCaption("W��������λ");
		else
			m_CapAlarm.SetCaption("Y-axis reverse");
	}
	else if (m_bAlarm[8] && g_stu_pAxisF->bSpareA == TRUE)
	{
		if(g_iLanguage==0)
			m_CapAlarm.SetCaption("W�Ḻ����λ");
		else
			m_CapAlarm.SetCaption("Y-axis forward");
	}
	else if (m_bAlarm[9])
	{
		if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
		{
			if(g_iLanguage==0)
				m_CapAlarm.SetCaption("X���ŷ�����");
			else
				m_CapAlarm.SetCaption("X-axis servo");
		}
		else
		{
			if(g_iLanguage==0)
				m_CapAlarm.SetCaption("�ŷ�����");
			else
				m_CapAlarm.SetCaption("axis servo");
		}
	}
	else if (m_bAlarm[10])
	{
		if(g_iLanguage==0)
			m_CapAlarm.SetCaption("Y���ŷ�����");
		else
			m_CapAlarm.SetCaption("Y-axis servo");
	}
	else if (m_bAlarm[11])
	{
		if(g_iLanguage==0)
			m_CapAlarm.SetCaption("Z���ŷ�����");
		else
			m_CapAlarm.SetCaption("Z-axis servo");
	}
	else if (m_bAlarm[12] && g_stu_pAxisF->bSpareA == TRUE)
	{
		if(g_iLanguage==0)
			m_CapAlarm.SetCaption("W���ŷ�����");
		else
			m_CapAlarm.SetCaption("W-axis servo");
	}
	else if (m_bAlarm[13])
	{
		if(g_iLanguage==0)
			m_CapAlarm.SetCaption("�µ�����");
		else
			m_CapAlarm.SetCaption("Tool limit");
	}
	else
	{
		m_CapAlarm.SetCaption("");
	}
}

//�õ�������Ϣ
void CBenderDlg::GetAlarm()
{
    m_bAlarm[0] = nOldInput[8] & 0x0001 ? 1 : 0;//��ͣ
    m_bAlarm[1] = nOldInput[6] & 0x0001 ? 0 : 1;//��λ
	m_bAlarm[3] = nOldInput[6] & 0x0002 ? 0 : 1;
	m_bAlarm[5] = 0;
	m_bAlarm[7] = nOldInput[6] & 0x0008 ? 0 : 1;
	m_bAlarm[2] = nOldInput[6] & 0x0010 ? 0 : 1;
	m_bAlarm[4] = nOldInput[6] & 0x0020 ? 0 : 1;
	m_bAlarm[6] = 0;
	m_bAlarm[8] = nOldInput[6] & 0x0080 ? 0 : 1;
    if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
	{
		m_bAlarm[9] = nOldInput[4] & 0x0001 ?  1 : 0;
		m_bAlarm[10] = nOldInput[4] & 0x0002 ? 1 : 0;
		m_bAlarm[11] = nOldInput[4] & 0x0004 ? 1 : 0;
		m_bAlarm[12] = nOldInput[4] & 0x0008 ? 1 : 0;
	}
	else
	{
        m_bAlarm[9] = nOldInput[5] & 0x0001 ?  0 : 1;
		m_bAlarm[10] = 0;
		m_bAlarm[11] = 0;
		m_bAlarm[12] = 0;

	}
	m_bAlarm[13] = nOldInput[7] & 0x0080 ? 0 : 1;
}
