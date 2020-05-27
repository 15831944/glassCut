// bender.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "bender.h"
#include "benderDlg.h"
#include "dlg_sn.h"
#include "Dlg_AfxMessage.h"
#include "hasp_api_cpp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



int       g_ndisknum = 0;                                     //���̲�����ز���
int       g_ndiskcheck[10];
CString   g_strdiskname[10];
/////////////////////////////////////////////////////////////////////////////
// CBenderApp

tagScanPARA	 g_ScanPara;

CAlarmDll	 g_AlarmDll;
CSystemDll   g_systemdll;
CMachineDll  g_machinedll;
CHandDll     g_handdll;
CCuttingPress    g_CutPress;
CDmcgc       g_Dmcgc;        //CDmcgc��
CDMCWin      g_Controller;
PSYS         g_stu_pSysA,g_stu_pSysB,g_stu_pSysC,g_stu_pSysD,g_stu_pSysE;			/* ϵͳ�忨���� */
PCONTROLLER	 g_pstu_control;
PAXIS        g_stu_pAxisA,g_stu_pAxisB,g_stu_pAxisC,g_stu_pAxisD;		/* ��е�������������ļ��� */
PAXIS        g_stu_pAxisE,g_stu_pAxisF,g_stu_pAxisG,g_stu_pAxisH;		/* ��е�������������ļ��� */
long         g_lRc;
USHORT       g_nController = 1;
char         g_szResponse[80];
float        g_fCurrMachineX = 0.0;  //��е���ͳ����������λ��
float        g_fCurrMachineY = 0.0;  //��е���ͳ����������λ��
float        g_fCurrMachineZ = 0.0;  //��е���ͳ����������λ��

//======DMC�ļ���G�����ļ�������
CString      g_strDmcfile="";
CString      g_strGfile="";
CString      g_strDxffile="";
CString      g_arr_strGline[5110];
CString      g_strShowName;         //���ļ�������pathtwo�е�listʹ�á�
CString      g_strSavefile;         //�����ļ�������dlg_save����ʹ��


int	         g_iMode = 0;                           //��������
int	         g_iStep = 0;                           //��������ʱ�������м�����

//======����ʹ����
CPoint     g_screen;
POINT2D    g_dScale;
CFont      g_fontButton,g_fontStatic,g_fontEdit,g_fontList,g_fontKey,g_fontRP;
CString    g_strOriginalPathC = "c:\\program files\\GlassCutter\\";//��װĿ¼���������Ŀ¼��
CString    g_strOriginalPathD = "d:\\program files\\GlassCutter\\";//��װĿ¼���������Ŀ¼��
COLORREF   g_crFontA = RGB(0,0,0);                //������ɫ����
COLORREF   g_crFontC = RGB(0,255,0);              //������ɫ����  ��ɫ
COLORREF   g_crFontD = RGB(255,0,0);              //������ɫ����  ��ɫ
int        g_iIsDxf = 0;//0�������ļ���1��DXF��2��G���룻
int        g_iPassgrade = 0;                          //Ȩ�޼���
int        g_iLanguage = 0;                         /* 0:���� 1:Ӣ�� */
CString    g_arr_strBender[AR_BENDER][5],g_arr_strCnc[AR_CNC][5],g_arr_strGalil[AR_GALIL][5],g_arr_strHand[AR_HAND][5],g_arr_strMachine[AR_MACHINE][5],g_arr_strManager[AR_MANAGER][5];
CString    g_arr_strLimit[1][6],g_arr_strMotion[AR_MOTION][5],g_arr_strPass[AR_PASS][5],g_arr_strPath2[AR_PATH2][5],g_arr_strSave[AR_SAVE][5],g_arr_strState[AR_STATE][5];
CString    g_arr_strSuper[AR_SUPER][5];
CString    g_arr_drawcad[AR_DRAWCAD][5];
CString    g_arr_glass[AR_GLASS][5];
CString	   g_arr_light[AR_LIGHT][5];
CString	   g_arr_lightpos[AR_LIGHTPOS][5];
CString	   g_arr_message[AR_MESSAGE][5];
CString		g_strGraphLib[AR_GRAPHLIB][4];			//ͼ�����
CString		g_strNester[AR_NESTER][4];				//���Ͻ���
CString		g_strNestPara[AR_NESTPARA][4];			//���ϲ�������
CString		g_strPartPara[AR_PARTPARA][4];			//ͼ���������
CString		g_strConfig[AR_CONFIG][4];
CString		g_strLoading[AR_LOADING][4];
CString		g_strFathom[AR_FATHOM][4];
CString		g_strCuttingSize[AR_CUTSIZE][4];
CString		g_strBottero[AR_BOTTERO][4];
CString		g_strOiling[AR_OILING][4];
UINT        g_nProduct = 0;//�ܵļӹ�����

POINT2D		pCoor,pCoorx,pCoory;/* ����ëƬ����λ�� ��ֱ�Ľ��㣬X�᷽��һ�㣬Y�᷽��һ��*/
//****************************************************************************

SYSTEMTIME			g_stCurrTime;
int       diskcheck1[10];
CString   diskname1[10];
//*************************ʵ��ȫ�ֺ�����
//CString g_strSavefile;
CString g_strGCodePath = "D:\\Program Files\\GlassCutter\\GraphLib\\";
int kind;		//�洢ͼ����һ������˼���ͼ��
int sqr[200];		//�洢ÿ����ӵ��������
int sqrm[200];		//�洢ÿ����ӵ��������
CDlg_Nest m_NestDlg;
int g_nRemainderX = 0;//bottero��
int g_nRemainderY = 0;//bottero��
stuBottero	stuBtro;//bottero��
TRACK       g_ExtraShow;               //��չ��ʾͼ�����ݽṹ
pShowInf    g_pShowSmall;               //��չ��ʾԭƬ

Cdlg_ShowExtra *     g_pDlgShowExtra; //��չ��ʾ�Ի���
double g_dExtraX;                       //��һ����ʾ��x�ߴ�
double g_dExtraY;                       //��һ����ʾ��y�ߴ�
int g_nTestRun = 0;//�����ڲ���ģʽ
int g_nRunState = 0;  //����״̬0�и1�����У�
CString g_strExtraFile;//��һ��ͼ�ε��ļ���
int g_nGlassNo = 0; //���鲣�� 0��Ƭ��1�п� 2��Ƭ
unsigned char vendorCode[] =
"PNAgfskStYP1LttUQg+4QPtBMh5lqLudDvHdWPCL3BhLYpmFWSnCar6NlTchP5Y8SO2em0cEY1MPsDr2yEO4OEpRRS2RhflX0zc+lk2i3IU9V2QQDGi4K35IsPTk/qp0rnJ7hYyi0bQER6nFCvh9XUILVDnfmd0ga1SueUoBlwNxwrFtvkN49GwnwTxXF68Y17GdpQWX5X+6LYLVZRYoouDKq8ePcp07MYqIGi4WWTNe4kmsm0kp0DdoFKi3zPojNKu6kVQYx6/0cEs6wclD5bMmRFNk2zCtXpXdm04SJ2uZfRHDXqrsxrmTQKBbAR6SNGj6qcC3SYcInt2KfG3VPQF6x4a2BSyhXcdphjkKDLZjDSyJgTwQwsAzRoHRMRRE0pA3FWKsBBrx7YD/5yxHudQeXY+8Weg8wSKPwW7Reh0FRf8XHw94Mn0HTZ4PegRyPPAxY/ZZIElAdCQ9Q/z7T1Z+La94lbQG0YXdEKRoZZ2pdmXUIZzgKQVcdGK6I1OM9ErGqHI+tzIsrHLHlpzWxoWavrwgsbDODjQ+V+1n5r/px2j1Wiw1MiXyEgeGZG0S2UvaLAWvt2+gFKbSqtyyybnqHQUHmHiYEQpjTMfpsAKMVowdGFdF370TQEW5Yfto7Ks/mBvt91X0NIXsFedCdrQGSzqciMwEePDp5iwjtk0STV6h1U5/X584y8445mF8sSlJVWNEhPuTv0A5FxVGWej0Y6GSvl1Cr91lIzwVQWCb3dGePUGHIXMQIFZlkmFE3i6ukR3A5LqzyLm8q14TZHJRVi9X9EnrOxJ1MqoaDtJeZbjT9hCbRFrHFqigFNWMuLtVPDVZ8dTPJiayRA9n7dSn09tlavxcs8n411QGhBLhr2pnIqdR/LJ1ef1uyjhtKMOm05C/Zt8jNhd3RUdGAo4E7DxqSLLWukmgHkJP85w=";

BEGIN_MESSAGE_MAP(CBenderApp, CWinApp)
	//{{AFX_MSG_MAP(CBenderApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
//	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBenderApp construction

CBenderApp::CBenderApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBenderApp object

CBenderApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBenderApp initialization

BOOL CBenderApp::InitInstance()
{
	AfxEnableControlContainer();
	SetDialogBkColor(BACKCOLOR,RGB(0,0,0));
	CoInitialize(NULL);

	if(OnEWF()<0)     //���д����״̬
	{
		OnEWFa();
		OnReBoot();
	}

	DeleFileLdb();
    g_machinedll.ParameterRead((char*)((const char*)(g_strOriginalPathD + "machine.ini")));/* ��ȡ��е������Ϣ */
	g_pstu_control = g_machinedll.GetController();	
	g_stu_pAxisA = &(g_pstu_control->axis[0]);	    g_stu_pAxisB = &(g_pstu_control->axis[1]);
	g_stu_pAxisC = &(g_pstu_control->axis[2]);	    g_stu_pAxisD = &(g_pstu_control->axis[3]);
	g_stu_pAxisE = &(g_pstu_control->axis[4]);	    g_stu_pAxisF = &(g_pstu_control->axis[5]);
	g_stu_pAxisG = &(g_pstu_control->axis[6]);	    g_stu_pAxisH = &(g_pstu_control->axis[7]);
    g_iLanguage = g_machinedll.GetLanguage();
	g_stu_pAxisF->bSpareA = TRUE;//����ͬ��
//	g_stu_pAxisF->bSpareA = FALSE;//����

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	GetCurrentDisplayProp(); //��ʾ���ķֱ���	

//*************************************ע������Դ��
	//*************************************ע������Դ��
	//�������ݿ�
	BOOL datare = SQLConfigDataSource(NULL,ODBC_ADD_DSN,"Microsoft Access Driver (*.mdb)",
		"DSN=sheet\0"
		"DBQ=d:\\Program Files\\GlassCutter\\Sheet.mdb\0"
		"DEFAULTDIR=D:\\Program Files\\GlassCutter\0\0");

//*
    datare = SQLConfigDataSource(NULL,ODBC_ADD_DSN,"Microsoft Access Driver (*.mdb)",
		"DSN=galil\0"
		"DBQ=c:\\Program Files\\GlassCutter\\Galil.power\0"
		"DEFAULTDIR=c:\\program files\\GlassCutter\0\0");	 
//*/
    _ConnectionPtr m_pCon;   //ADOӦ��
	_RecordsetPtr  m_pRec;
//================================================================================================
	::CoInitialize(NULL);

	CString str_temp;
	int i = 0;
	m_pCon.CreateInstance(__uuidof(Connection));

	try   
	{
		m_pCon->Open("Provider=MSDASQL.1;Persist Security Info=False;Data Source=galil","","",NULL);
	}

	catch(_com_error e)
	{
		CString   errormessage; 
		errormessage.Format( "��������ʧ��!\n������Ϣ:%s ",   e.ErrorMessage()); 
		AfxMessageBox(errormessage); 
		return   FALSE; 
	} 


	//�������򿪼�¼������
	////===============================================================13
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from Message",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF && i<AR_MESSAGE)//
	{
		//��õ�һ����¼
		g_arr_message[i][0] = (char*)_bstr_t(m_pRec->GetCollect("���"));
		g_arr_message[i][1] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_message[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_message[i][3] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================1
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from benderDlg",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_BENDER)
	{
		//��õ�һ����¼
		g_arr_strBender[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strBender[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================2
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_key",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_CNC)
	{
		//��õ�һ����¼
		g_arr_strCnc[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strCnc[i][1] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strCnc[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strCnc[i][3] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================3
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_manager",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_MANAGER)
	{
		//��õ�һ����¼
		g_arr_strManager[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strManager[i][1] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strManager[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strManager[i][3] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================�˶�������
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_galil",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_GALIL)
	{
		//��õ�һ����¼
		g_arr_strGalil[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strGalil[i][1] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strGalil[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
//		g_arr_strGalil[i][3] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================5
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_hand",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_HAND)
	{
		//��õ�һ����¼
		g_arr_strHand[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strHand[i][1] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strHand[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strHand[i][3] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================6
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_machine",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_MACHINE)
	{
		//��õ�һ����¼
		g_arr_strMachine[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strMachine[i][1] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strMachine[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strMachine[i][3] = (char*)_bstr_t(m_pRec->GetCollect("����"));
//		g_arr_strMachine[i][4] = (char*)_bstr_t(m_pRec->GetCollect("��ע"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================7
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_motion",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_MOTION)
	{
		//��õ�һ����¼
		g_arr_strMotion[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strMotion[i][1] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strMotion[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strMotion[i][3] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strMotion[i][4] = (char*)_bstr_t(m_pRec->GetCollect("��ע"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================8
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_path2",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_PATH2)
	{
		//��õ�һ����¼
		g_arr_strPath2[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strPath2[i][1] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strPath2[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strPath2[i][3] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================9
    m_pRec.CreateInstance(__uuidof(Recordset));
	m_pRec->Open("select* from dlg_machinecase",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_STATE)
	{
		//��õ�һ����¼
		g_arr_strState[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strState[i][1] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strState[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================10
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_pass",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_PASS)
	{
		//��õ�һ����¼
		g_arr_strPass[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strPass[i][1] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strPass[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strPass[i][3] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================11
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_light",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_LIGHT)
	{
		//��õ�һ����¼
		g_arr_light[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_light[i][1] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_light[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_light[i][3] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================12
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_save",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_SAVE)
	{
		//��õ�һ����¼
		g_arr_strSave[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strSave[i][1] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strSave[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strSave[i][3] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================15
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_super",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_SUPER)//
	{
		//��õ�һ����¼
		g_arr_strSuper[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strSuper[i][1] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strSuper[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strSuper[i][3] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_strSuper[i][4] = (char*)_bstr_t(m_pRec->GetCollect("��ע"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================16
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_drawcad",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_DRAWCAD)//
	{
		//��õ�һ����¼
		g_arr_drawcad[i][2] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_drawcad[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_drawcad[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================17
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_glass",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_GLASS)//
	{
		//��õ�һ����¼
		g_arr_glass[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_glass[i][1] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_glass[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_glass[i][3] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================18
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_lightpos",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_LIGHTPOS)//
	{
		//��õ�һ����¼
		g_arr_lightpos[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_lightpos[i][1] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_arr_lightpos[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_lightpos[i][3] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================ͼ��
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from GraphLib",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_DEFINEIO)
	{
		//��õ�һ����¼
		g_strGraphLib[i][2] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strGraphLib[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strGraphLib[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================ͼ�ο����
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from PartPara",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_PARTPARA)
	{
		//��õ�һ����¼
		g_strPartPara[i][2] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strPartPara[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strPartPara[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================���ϲ���
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from NestPara",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_NESTPARA)
	{
		//��õ�һ����¼
		g_strNestPara[i][2] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strNestPara[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strNestPara[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================����
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from Nester",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_DEFINEIO)
	{
		//��õ�һ����¼
		g_strNester[i][2] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strNester[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strNester[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================ϵͳ����
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_config",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_CONFIG)
	{
		//��õ�һ����¼
		g_strConfig[i][2] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strConfig[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strConfig[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================��Ƭ̨���
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_loading",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_LOADING)
	{
		//��õ�һ����¼
		g_strLoading[i][2] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strLoading[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strLoading[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================��Ƭ̨���
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_oiling",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_OILING)
	{
		//��õ�һ����¼
		g_strOiling[i][2] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strOiling[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strOiling[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================��񴰿�g_strCuttingSize
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_thickness",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_LOADING)
	{
		//��õ�һ����¼
		g_strFathom[i][2] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strFathom[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strFathom[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================�����ߴ�dlg_bottero
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_cutsize",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_CUTSIZE)
	{
		//��õ�һ����¼
		g_strCuttingSize[i][2] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strCuttingSize[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strCuttingSize[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;

	////===============================================================�����ߴ�
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_bottero",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_BOTTERO)
	{
		//��õ�һ����¼
		g_strBottero[i][2] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strBottero[i][0] = (char*)_bstr_t(m_pRec->GetCollect("����"));
		g_strBottero[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}	
	m_pRec = NULL;
	////===============================================================

	m_pCon = NULL;	
	
    OnReSetFont();
	
    OnRegSvr32();/* ע��ؼ� */

	CBenderDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}	
	HANDLE hProcess = theApp.m_hThread;	
	if (hProcess == NULL)
	{
		return FALSE;
	}
	else
	{
	    TerminateProcess(hProcess,0);		
	}	
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CBenderApp::GetCurrentDisplayProp() //��ʾ���ķֱ���
{	
	g_screen.x = 1024;
	g_screen.y = 768;
	g_dScale.x = 1.28;
	g_dScale.y = 1.28;
}

void CBenderApp::OnReSetFont()    /* �������ͳһ�趨 1024*768*/
{
	if(!g_iLanguage)
	{
		g_fontButton.CreateFont(20,0,0,0,FW_MEDIUM,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		g_fontStatic.CreateFont(16,0,0,0,FW_LIGHT,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		g_fontEdit.CreateFont(18,0,0,0,FW_LIGHT,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		g_fontList.CreateFont(15,0,0,0,FW_LIGHT,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		g_fontKey.CreateFont(32,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
	    g_fontRP.CreateFont(28,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("Times New Roman"));
	}
	else if(g_iLanguage==1)
	{
		g_fontButton.CreateFont(18,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		g_fontStatic.CreateFont(16,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		g_fontEdit.CreateFont(17,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		g_fontList.CreateFont(15,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		g_fontKey.CreateFont(19,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		g_fontRP.CreateFont(28,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("Times New Roman"));
	}
	else
	{
		g_fontButton.CreateFont(15,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		g_fontStatic.CreateFont(16,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("Arial"));
		g_fontEdit.CreateFont(17,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("Arial"));
		g_fontList.CreateFont(18,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("����"));
		g_fontKey.CreateFont(19,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("Arial"));
		g_fontRP.CreateFont(28,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("Times New Roman"));
	}
}
void CBenderApp::OnRegSvr32()   
{
	CString strFileName;
	FARPROC lpFunc;  
	//===================================================================
    strFileName = g_strOriginalPathC + "CaptionInfo.ocx";	
	//װ��ActiveX�ؼ�  
	HINSTANCE hInstance = LoadLibrary(strFileName); 
	if (hInstance == NULL)  
	{     
		OnShowMessageBox(17,g_iLanguage,FALSE);
//		AfxMessageBox("��������Dll/OCX�ļ�!\nCan't find Dll/OCX files!");     
		return; 
	} 
	//ȡ��ע�ắ��DllRegisterServer��ַ 
	lpFunc = GetProcAddress(hInstance,_T("DllRegisterServer"));  
	//����ע�ắ��DllRegisterServer 
	if(lpFunc!=NULL)  
	{       
		if(FAILED((*lpFunc)()))   
		{       
			OnShowMessageBox(18,g_iLanguage,FALSE);
			//�ͷ���Դ
			FreeLibrary(hInstance);          
			return;     
		}     
	}
	else  	OnShowMessageBox(18,g_iLanguage,FALSE);
	//===================================================================
    strFileName = g_strOriginalPathC + "Lamp.ocx";	
	//װ��ActiveX�ؼ�  
	hInstance = LoadLibrary(strFileName); 
	if (hInstance == NULL)  
	{     
		OnShowMessageBox(17,g_iLanguage,FALSE);
		return; 
	} 
	//ȡ��ע�ắ��DllRegisterServer��ַ 
	lpFunc = GetProcAddress(hInstance,_T("DllRegisterServer"));  
	//����ע�ắ��DllRegisterServer 
	if(lpFunc!=NULL)  
	{       
		if(FAILED((*lpFunc)()))   
		{       
			OnShowMessageBox(18,g_iLanguage,FALSE);
			//�ͷ���Դ
			FreeLibrary(hInstance);          
			return;     
		}     
	}
	else  	OnShowMessageBox(18,g_iLanguage,FALSE);
    strFileName = g_strOriginalPathC + "GridCAD.ocx";	
	//װ��ActiveX�ؼ�  
	hInstance = LoadLibrary(strFileName); 
	if (hInstance == NULL)  
	{     
		OnShowMessageBox(17,g_iLanguage,FALSE);
		return; 
	} 
	//ȡ��ע�ắ��DllRegisterServer��ַ 
	lpFunc = GetProcAddress(hInstance,_T("DllRegisterServer"));  
	//����ע�ắ��DllRegisterServer 
	if(lpFunc!=NULL)  
	{       
		if(FAILED((*lpFunc)()))   
		{       
			OnShowMessageBox(18,g_iLanguage,FALSE);
			//�ͷ���Դ
			FreeLibrary(hInstance);          
			return;     
		}     
	}
	else  	OnShowMessageBox(18,g_iLanguage,FALSE);	
	//===================================================================    
    strFileName = g_strOriginalPathC + "DisplayCtrl.ocx";	
	//װ��ActiveX�ؼ�  
	hInstance = LoadLibrary(strFileName); 
	if (hInstance == NULL)  
	{     
		OnShowMessageBox(17,g_iLanguage,FALSE);
		return; 
	} 
	//ȡ��ע�ắ��DllRegisterServer��ַ 
	lpFunc = GetProcAddress(hInstance,_T("DllRegisterServer"));  
	//����ע�ắ��DllRegisterServer 
	if(lpFunc!=NULL)  
	{       
		if(FAILED((*lpFunc)()))   
		{       
			OnShowMessageBox(18,g_iLanguage,FALSE);
			//�ͷ���Դ
			FreeLibrary(hInstance);          
			return;     
		}     
	}
	else  	OnShowMessageBox(18,g_iLanguage,FALSE);	
	//===================================================================
    strFileName = g_strOriginalPathC + "PlanInfo.ocx";	
	//װ��ActiveX�ؼ�  
	hInstance = LoadLibrary(strFileName); 
	if (hInstance == NULL)  
	{     
		OnShowMessageBox(17,g_iLanguage,FALSE);
		return; 
	} 
	//ȡ��ע�ắ��DllRegisterServer��ַ 
	lpFunc = GetProcAddress(hInstance,_T("DllRegisterServer"));  
	//����ע�ắ��DllRegisterServer 
	if(lpFunc!=NULL)  
	{       
		if(FAILED((*lpFunc)()))   
		{       
			OnShowMessageBox(18,g_iLanguage,FALSE);
			//�ͷ���Դ
			FreeLibrary(hInstance);          
			return;     
		}     
	}
	else  	OnShowMessageBox(18,g_iLanguage,FALSE);	
	//===================================================================
    strFileName = g_strOriginalPathC + "MSCOMM32.OCX";	
	//װ��ActiveX�ؼ�  
	hInstance = LoadLibrary(strFileName); 
	if (hInstance == NULL)  
	{     
		OnShowMessageBox(17,g_iLanguage,FALSE);
		return; 
	} 
	//ȡ��ע�ắ��DllRegisterServer��ַ 
	lpFunc = GetProcAddress(hInstance,_T("DllRegisterServer"));  
	//����ע�ắ��DllRegisterServer 
	if(lpFunc!=NULL)  
	{       
		if(FAILED((*lpFunc)()))   
		{       
			OnShowMessageBox(18,g_iLanguage,FALSE);
			//�ͷ���Դ
			FreeLibrary(hInstance);          
			return;     
		}     
	}
	else  	OnShowMessageBox(18,g_iLanguage,FALSE);	
	//===================================================================
    strFileName = g_strOriginalPathC + "BtnCtl.ocx";	
	//װ��ActiveX�ؼ�  
	hInstance = LoadLibrary(strFileName); 
	if (hInstance == NULL)  
	{     
		OnShowMessageBox(17,g_iLanguage,FALSE);
		return; 
	} 
	//ȡ��ע�ắ��DllRegisterServer��ַ 
	lpFunc = GetProcAddress(hInstance,_T("DllRegisterServer"));  
	//����ע�ắ��DllRegisterServer 
	if(lpFunc!=NULL)  
	{       
		if(FAILED((*lpFunc)()))   
		{       
			OnShowMessageBox(18,g_iLanguage,FALSE);
			//�ͷ���Դ
			FreeLibrary(hInstance);          
			return;     
		}     
	}
	else  	OnShowMessageBox(18,g_iLanguage,FALSE);	

}
BOOL CBenderApp::OnEWFa()                //��XPE�е�д����
{
	CString    volume;
	BOOL       b,c;
    HANDLE     handle;
	PEWF_VOLUME_NAME_ENTRY   p_volume;
    PEWF_VOLUME_CONFIG       ewfcon;
	
	c = FALSE;
	p_volume = EwfMgrGetProtectedVolumeList();
	b = EwfMgrVolumeNameListIsEmpty(p_volume);	
	if(!b)
	{
		handle = EwfMgrOpenProtected(p_volume->Name);    //IN LPCWSTR lpVolume
		ewfcon = EwfMgrGetProtectedVolumeConfig(handle);
		if(ewfcon->State==EWF_DISABLED)
		{
			c = EwfMgrEnable(handle);
			c = EwfMgrCommit(handle);
		}
        b = EwfMgrClose(handle);
	}
	return c;
}

BOOL CBenderApp::OnEWFb()                //��XPE�е�д����
{
	CString    volume;
	BOOL       b,c;
    HANDLE     handle;
	PEWF_VOLUME_NAME_ENTRY   p_volume;
    PEWF_VOLUME_CONFIG       ewfcon;
	
	c = FALSE;
	p_volume = EwfMgrGetProtectedVolumeList();
	b = EwfMgrVolumeNameListIsEmpty(p_volume);	
	if(!b)
	{
		handle = EwfMgrOpenProtected(p_volume->Name);    //IN LPCWSTR lpVolume
		ewfcon = EwfMgrGetProtectedVolumeConfig(handle);
		if(ewfcon->State==EWF_ENABLED)
		{
			c = EwfMgrCommitAndDisableLive(handle);
		}
        b = EwfMgrClose(handle);
	}
	return c;
}

void CBenderApp::OnReBoot()                //��XPE�е�д����
{
	HANDLE hToken; 
	TOKEN_PRIVILEGES tkp; 
	
	// Get a token for this process. 
	
	if (!OpenProcessToken(GetCurrentProcess(), 
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		OnShowMessageBox(19,g_iLanguage,FALSE);
//	AfxMessageBox("OpenProcessToken Error��"); 
	
	// Get the LUID for the shutdown privilege. 
	
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
		&tkp.Privileges[0].Luid); 
	
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	
	// Get the shutdown privilege for this process. 
	
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
		(PTOKEN_PRIVILEGES)NULL, 0); 
	
	// Cannot test the return value of AdjustTokenPrivileges. 
	
	if (GetLastError() != ERROR_SUCCESS) 
		OnShowMessageBox(20,g_iLanguage,FALSE);
//	AfxMessageBox("AdjustTokenPrivileges Error��"); 
	
	// Shut down the system and force all applications to close. 
	
	if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0)) 
		OnShowMessageBox(21,g_iLanguage,FALSE);
}

int CBenderApp::OnEWF()                //��XPE�е�д����
{
	CString    volume;
	BOOL       b,c;
    HANDLE     handle;
	PEWF_VOLUME_NAME_ENTRY   p_volume;
    PEWF_VOLUME_CONFIG       ewfcon;
	
	c = 0;
	p_volume = EwfMgrGetProtectedVolumeList();
	b = EwfMgrVolumeNameListIsEmpty(p_volume);	
	if(!b)
	{
		handle = EwfMgrOpenProtected(p_volume->Name);    //IN LPCWSTR lpVolume
		ewfcon = EwfMgrGetProtectedVolumeConfig(handle);
		if(ewfcon->State==EWF_DISABLED)
		{
			c = -1;/*��ǰд����״̬��δ����*/
		}
		else
		{
			c = 1;/*��ǰд����״̬��  ����*/
		}
		
        b = EwfMgrClose(handle);
	}
	else
	{
		c = 0;/*�޷���֪����״̬��*/
	}
	return c;
}

CRect OnReSetRectV(CRect rc)
{
	
	rc.left = (long)(rc.left*1.28);
	rc.top = (long)(rc.top*1.28);
	rc.bottom = (long)(rc.bottom*1.28);
	rc.right = (long)(rc.right*1.28);	
	return rc;
}

void OnCheckPassword(int nFirst)    /* Ȩ����֤ ��һ�ο���0��������Ϊ1*/
{
	if(!g_arr_strLimit[0][3].IsEmpty())
	{			
		long     day;
		CTime CurrTime;
		CurrTime = g_stCurrTime;
		CTime LimitTime(atoi(g_arr_strLimit[0][0]),atoi(g_arr_strLimit[0][1]),atoi(g_arr_strLimit[0][2]),0,0,0);
		CTimeSpan  SpanTime = LimitTime - CurrTime  ;
		day = SpanTime.GetDays();
		if (nFirst == 0)
		{
			if (day < 10)
			{
				dlg_sn   sn;
				sn.m_nDayHead = day;				
				sn.DoModal();
			}
		}
		else
		{
			if (day < 0)
			{
				dlg_sn   sn;
				sn.m_nDayHead = day;				
				sn.DoModal();
			}
		}
	}	
}

/* Calculate the angle between points */
double PointToPointAngle(double dBcx,double dBcy,double dEcx,double dEcy)
{
	double   angle;
	double   dx = dEcx - dBcx;
	double   dy = dEcy - dBcy;
	
	if (dx == 0)
	{
		if (dy > 0)			       angle = 90;
		else		    	       angle = 270;
	}
	else if (dy == 0)
	{
		if (dx > 0)			       angle = 0;
		else     			       angle = 180;
	}
	else
	{
		if (dy == 0 && dx == 0)	   angle = 0;
		else   		        	   angle = (180/M_PI) * (atan2(dy, dx));
		
		if (angle < 0)			   angle += 360;      
		else if (angle > 360)      angle -= 360;
	}
	
	return angle;
}


int OnShowMessageBox(int index,int nLanguage,BOOL iTitle)                //�����ݿ��е�����Ϣ
{
	CDlg_AfxMessage  Message;
	Message.bYesNo = FALSE;
	switch(nLanguage) 
	{
	case 0:/* ���� */
		Message.strAfxMessage = g_arr_message[index][1];
		Message.strAfxYES = g_arr_message[44][1];
		if(iTitle)	Message.strAfxTitle = g_arr_message[1][1];
		else		Message.strAfxTitle = g_arr_message[0][1];/* ���� */
		break;
	case 1:/* Ӣ�� */
		Message.strAfxMessage = g_arr_message[index][2];
		Message.strAfxYES = g_arr_message[44][2];
		if(iTitle)	Message.strAfxTitle = g_arr_message[1][2];
		else		Message.strAfxTitle = g_arr_message[0][2];
		break;
	case 2:/* ���� */
		Message.strAfxMessage = g_arr_message[index][3];
		Message.strAfxYES = g_arr_message[44][3];
		if(iTitle)	Message.strAfxTitle = g_arr_message[1][3];
		else		Message.strAfxTitle = g_arr_message[0][3];
		break;
	default:
		break;
	}
	if(Message.DoModal()==IDOK)		return IDYES;
	else							return IDNO;
}

int OnShowMessageBox(int index,int nLanguage)                //�����ݿ��е�����Ϣ
{
	int  i = 0;
	CDlg_AfxMessage  Message;
	Message.bYesNo = TRUE;
	switch(nLanguage) 
	{
	case 0:/* ���� */
		Message.strAfxMessage = g_arr_message[index][1];
		Message.strAfxTitle = g_arr_message[1][1];
		Message.strAfxYES = g_arr_message[45][1];
		Message.strAfxNO = g_arr_message[46][1];
		break;
	case 1:/* Ӣ�� */
		Message.strAfxMessage = g_arr_message[index][2];
		Message.strAfxTitle = g_arr_message[1][2];
		Message.strAfxYES = g_arr_message[45][2];
		Message.strAfxNO = g_arr_message[46][2];
		break;
	case 2:/* ���� */
		Message.strAfxMessage = g_arr_message[index][3];
		Message.strAfxTitle = g_arr_message[1][3];
		Message.strAfxYES = g_arr_message[45][3];
		Message.strAfxNO = g_arr_message[46][3];
		break;
	default:
		break;
	}
	if(Message.DoModal()==IDOK)		return IDYES;
	else							return IDNO;
}

void OnSoftLimit(double fx,double fy,double bx,double by) /* ����λ����FLBL */
{
	CString		strTemp;
	char szRes[80]={0};
	strTemp.Format("FL%.0f,%.0f",fx * g_stu_pAxisA->d_pulse_user,fy * g_stu_pAxisB->d_pulse_user);
	strcpy(szRes,LPCTSTR(strTemp));
	LONG l_Rec = g_Controller.Command(szRes);
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
	strTemp.Format("BL%.0f,%.0f",bx * g_stu_pAxisA->d_pulse_user,by * g_stu_pAxisB->d_pulse_user);
	strcpy(szRes,LPCTSTR(strTemp));
	l_Rec = g_Controller.Command(szRes);
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

	ofstream fileOut("D:\\Program Files\\GlassCutter\\softLimit.txt", ios::out);	
	fileOut << fx << endl;
	fileOut << fy << endl;
	fileOut << bx << endl;
	fileOut << by << endl;	
	fileOut.close();
	
}

double SaveNPoint(int n, double dVar) /* ����4λС�� */
{
	long	nVar;
	long	nDecuple;
	double	dResult;
	switch(n) 
	{
	case 0:		nDecuple = 1;		break;
	case 1:		nDecuple = 10;		break;
	case 2:		nDecuple = 100;		break;
	case 3:		nDecuple = 1000;	break;
	case 4:		nDecuple = 10000;	break;
	default:	nDecuple = 10000;	break;
	}
	nVar = (long)(dVar * nDecuple);
	dResult = (double)(nVar*1.0/nDecuple);
	return dResult;
}

CPoint ReadMaxSpeed() 
{
	CPoint	p;
	ifstream fileIn("C:\\Program Files\\GlassCutter\\feed.txt", ios::in);
	
	fileIn >> p.x;
	fileIn >> p.y;
	
	fileIn.close();
	return p;
}

//���ع�綨λ�ٶȲ���
void SetFindLightSpeed()
{
	char szCmd[80]={0};
	sprintf(szCmd,"lightspx=%d;lightacx=%d;lightdcx=%d", (long)(g_stu_pAxisA->lSpareE * g_stu_pAxisA->d_pulse_user),
		(long)(g_stu_pAxisE->d_vacc * g_stu_pAxisA->d_pulse_user),
		(long)(g_stu_pAxisE->d_vdec * g_stu_pAxisA->d_pulse_user));
	g_Controller.Command(szCmd);
    memset(szCmd,0,sizeof(szCmd));
	sprintf(szCmd,"lightspy=%d;lightacy=%d;lightdcy=%d", (long)(g_stu_pAxisB->lSpareE * g_stu_pAxisB->d_pulse_user),
			(long)(g_stu_pAxisF->d_vacc * g_stu_pAxisA->d_pulse_user),
			(long)(g_stu_pAxisF->d_vdec * g_stu_pAxisA->d_pulse_user));
	g_Controller.Command(szCmd);
}

void CBenderApp::ShutDown()
{
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
		TRUE);                               //��ΪTRUEΪ������ΪFALSEΪ�ػ�   
	if(!fResult)    
	{    
		AfxMessageBox("InitiateSystemShutdown failed.");    
	}
	
}

int HasWriteValue(CString strValue,hasp_size_t offset)
{
	haspStatus status; 
	Chasp hasp4(ChaspFeature::defaultFeature());
	status = hasp4.login(vendorCode);
	const int size = 15;
	if(strValue.GetLength()>size)
	{
		strValue = strValue.Left(size);
	}

	ChaspFile file = hasp4.getFile(ChaspFile::fileReadWrite);	
	file.setFilePos(offset);
	status = file.write((const unsigned char*)strValue.GetBuffer(0), size);	
	if (status != HASP_STATUS_OK)
	{
		if(g_iLanguage)
		{
			AfxMessageBox("hard lock error");
		}
		else
		{
			AfxMessageBox("���ܹ�����");
		}
		return 1;
	}
	hasp4.logout();
    return HASP_STATUS_OK;
}

int HasReadValue(CString &strValue, hasp_size_t offset)
{

	haspStatus status; 
	Chasp hasp3(ChaspFeature::defaultFeature());
	status = hasp3.login(vendorCode);
	if (!HASP_SUCCEEDED(status))
    {  
       return 0;
    }
	const int size = 15;
	ChaspFile file = hasp3.getFile(ChaspFile::fileReadWrite);
	unsigned char data[size];
	memset(data,'\0',size);
	file.setFilePos(offset);
	status = file.read(data, size);
	
	if (!HASP_SUCCEEDED(status))
	{
		return 0;
	}
	strValue.Format("%s",data);
	if(strValue.IsEmpty())
	{
		strValue = "";
	}
	else if(data[0] == 0 )
	{
        strValue = "";
	}
    hasp3.logout();
    return 1;

}

/* �ļ��м�Ŀ��� */
void CopyDirectory(CString sorPath, CString aimPath)
{
	CFileFind cFind;
	BOOL bFind;
	
	BOOL re = CreateDirectory(aimPath, NULL);
	
	bFind = cFind.FindFile(sorPath+"\\*.*");
	while(bFind) 
	{
		bFind = cFind.FindNextFile();
		if (cFind.IsDirectory() && !cFind.IsDots() && !cFind.IsHidden())//���ļ���
		{  
			CopyDirectory(sorPath+"\\"+cFind.GetFileName(), aimPath+"\\"+cFind.GetFileName());
		}
		else
		{
			CopyFile(sorPath+"\\"+cFind.GetFileName(), aimPath+"\\"+cFind.GetFileName(),FALSE);
		}
	}
}

/* ɾ���ļ��� */
void DeleteDirectory(CString strPath)
{
	CFileFind find;
	BOOL re;
	re = find.FindFile(strPath + "\\*.*");
	while (re)
	{
		re = find.FindNextFile();
		if (find.IsDirectory())
		{
			if (!find.IsDots())
			{
				DeleteDirectory(find.GetFilePath());
			}
		}
		else
		{
			::DeleteFile(find.GetFilePath());
		}
	}
	find.Close();//һ���ȹر����,���Ƴ�ɾ���ļ���
	::RemoveDirectory(strPath);
}


CString movediskdir()
{
    CFileFind   finder;
    int         i = 0;
	CString     root[10] = {"D:\\","E:\\","F:\\","G:\\","H:\\","I:\\","J:\\","K:\\","L:\\","M:\\",};
	CString     s_dir;
	
	while(GetDriveType(root[i])!=DRIVE_REMOVABLE&&i<9)     //���ҿ��ƶ�����
		i++;
	s_dir = root[i];
	if(i==9&&GetDriveType(root[9])!=DRIVE_REMOVABLE)
	{
		s_dir = "";
		if(OnIsDisk()==0)
		{
			return s_dir;                                  //�Ҳ����ƶ��̣�����
		}
		else
		{
			for(i=0;i<10;i++)
				if(diskcheck1[i] == DRIVE_FIXED)
					s_dir = diskname1[i];
		}
	}
	
	return s_dir;
}


int OnIsDisk()                                //�Ƿ����Ƶ�Ӳ��
{
	int        i,j;
    int        n = 0,m = 0;
	CString    root[10] = {"D:\\","E:\\","F:\\","G:\\","H:\\","I:\\","J:\\","K:\\","L:\\","M:\\"};
	
	for(i=0;i<10;i++)
	{
		if(GetDriveType(root[i])==DRIVE_FIXED)             //�м������ش���
		{
			diskcheck1[i] = DRIVE_FIXED;
			diskname1[i] = root[i];
			n++;
		}
		else if(GetDriveType(root[i])==DRIVE_REMOVABLE)    //�м����ƶ�����
		{
			diskcheck1[i] = DRIVE_REMOVABLE;
			diskname1[i] = root[i];
			m++;
		}
		else
		{
			diskcheck1[i] = DRIVE_UNKNOWN;
			diskname1[i] = "";
		}
	}
	if(g_ndisknum!=n)                                         //disknum���ڳ���������һ���Ը�ֵ�����ٸĶ�!
	{
		for(i=0;i<10;i++)
			for(j=0;j<10;j++)
			{
				if(diskname1[i]!=""&&diskname1[i]==g_strdiskname[j])
				{
					diskcheck1[i] = DRIVE_UNKNOWN;
					diskname1[i] = "";
				}
			}
			n = 0;
			for(i=0;i<10;i++)
			{
				if(diskcheck1[i]==DRIVE_FIXED)
					n++;
			}
			return n;
	}
	else
		return 0;
}

void GetBitMapRgn(CDC *pDC, HRGN &c,int nID)
{	
	CDC   memDC; 
	//�����봫��DC���ݵ���ʱDC 
	memDC.CreateCompatibleDC(pDC); 
	HRGN hrgn;
	hrgn = CreateRectRgn(0, 0, 0, 0);
	CombineRgn(c,c,hrgn,RGN_AND);
	DeleteObject(hrgn);
	CBitmap cBitmap;
	cBitmap.LoadBitmap(nID);
	memDC.SelectObject(&cBitmap); 
	BITMAP   bit;       
    cBitmap.GetBitmap   (&bit);//ȡ��λͼ����������Ҫ�õ�λͼ�ĳ��Ϳ�        
	int   y; 
	for(y=0; y<bit.bmHeight; y++) 
	{ 
        CRgn rgnTemp;  //������ʱregion 
		
		int iX = 0; 
		do 
		{ 
			//����͸��ɫ�ҵ���һ����͸��ɫ�ĵ�. 
			while   (iX<=bit.bmWidth && memDC.GetPixel(iX,y)==RGB(255,255,255)) 
				iX++; 
			
			//��ס�����ʼ�� 
			int   iLeftX = iX; 
			
			//Ѱ���¸�͸��ɫ�ĵ� 
			while   (iX<=bit.bmWidth && memDC.GetPixel(iX,y)!=RGB(255,255,255)) 
				iX++; 
			
			//����һ������������ص���Ϊ1���ص���ʱ��region�� 
			rgnTemp.CreateRectRgn(iLeftX,y,iX,y+1); 
			
			//�ϲ����� "region ". 
			CombineRgn(c,c,rgnTemp,RGN_OR); 
			
			//ɾ����ʱ "region ",�����´δ���ʱ�ͳ��� 
			rgnTemp.DeleteObject(); 
		}while(iX<bit.bmWidth); 
	}	
}

void SetCtlFont(CWnd *pWnd)
{
	char cClassName[255];
	CWnd* pCtlWnd = pWnd->GetWindow(GW_CHILD);
    while(pCtlWnd != NULL) 
    { 
        GetClassName(pCtlWnd->GetSafeHwnd(), cClassName, 255);//��ȡ�ؼ�������
		if(strstr(cClassName, "Button") || strstr(cClassName, "Static")|| strstr(cClassName, "ComboBox"))
		{			
			pCtlWnd->SetFont(&g_fontStatic);
		}
		else  if(strstr(cClassName, "Edit")||strstr(cClassName, "SysDateTimePick32"))
		{
			pCtlWnd->SetFont(&g_fontEdit);
		}

		pCtlWnd = pCtlWnd->GetWindow(GW_HWNDNEXT); 
	}
}

//����һ���ڴ�DC
void CreateDC(CDC *pMemDC, CDC *pSrcDC, int width, int height)
{
	CBitmap bmp, *pOldBmp=NULL;
	BOOL bToCreate;

	if(!pSrcDC)	return;
	if(!pMemDC)	return;
	
	bToCreate = TRUE;
	if(pMemDC->m_hDC)
	{
		CRect rdc;
		pMemDC->GetClipBox(&rdc);
		if(rdc.Width()==width && rdc.Height()==height)
			bToCreate=FALSE;
		else
			pMemDC->DeleteDC();
	}
	if(bToCreate)
	{
		if(pMemDC->CreateCompatibleDC(pSrcDC))
		{
			if(bmp.CreateCompatibleBitmap(pSrcDC, width, height))
			{
				pOldBmp = pMemDC->SelectObject(&bmp);
				if(pOldBmp && pOldBmp->m_hObject)
					pOldBmp->DeleteObject();
				bmp.DeleteObject();
			}
		}
	}
}


//��ͼƬ��ֱ��ת
void ConvertGraphCoordinate(CDC *pDC)
{
	CRect rc;
	int row, col, x, y, length;
	COLORREF temp;
	CBitmap *pBmp=NULL;
	if(!pDC)	return;
	pBmp=pDC->GetCurrentBitmap();
	if(!pBmp)	return;
	pDC->GetClipBox(&rc);
	row = rc.Height();
	col = rc.Width();
	length=row*col*sizeof(COLORREF);

	COLORREF *colors=NULL;
	BYTE *bits=new BYTE[length];
	if(bits)
	{
		length = pBmp->GetBitmapBits(length, bits);
		colors = (COLORREF*)bits;
		for(y=0; y<(row/2); y++)
		{
			for(x=0; x<col; x++)
			{
				temp = colors[y*col+x];
				colors[y*col+x] = colors[(row-1-y)*col+x];
				colors[(row-1-y)*col+x] = temp;
			}
		}
		pBmp->SetBitmapBits(length, bits);
		delete colors;
	}
}

#define RGB_R(rgb)	((BYTE)((rgb>> 0)&0xFF))
#define RGB_G(rgb)	((BYTE)((rgb>> 8)&0xFF))
#define RGB_B(rgb)	((BYTE)((rgb>>16)&0xFF))
void ReplaceColor(CDC *pDC, const COLORREF crOld1, const COLORREF crOld2, const COLORREF crNew)
{
	CRect rc;
	int row, col, x, y, length;
	COLORREF temp;
	CBitmap *pBmp=NULL;
	BYTE r, g, b, r1, g1, b1, r2, g2, b2;
	if(!pDC)	return;
	pBmp=pDC->GetCurrentBitmap();
	if(!pBmp)	return;
	pDC->GetClipBox(&rc);
	row = rc.Height();
	col = rc.Width();
	length=row*col*sizeof(COLORREF);

	r1 = RGB_R(crOld1);
	g1 = RGB_G(crOld1);
	b1 = RGB_B(crOld1);
	r2 = RGB_R(crOld2);
	g2 = RGB_G(crOld2);
	b2 = RGB_B(crOld2);


	COLORREF *colors=NULL;
	BYTE *bits=new BYTE[length];
	if(bits)
	{
		length = pBmp->GetBitmapBits(length, bits);
		colors = (COLORREF*)bits;
		for(y=0; y<row; y++)
		{
			for(x=0; x<col; x++)
			{
				temp = colors[y*col+x];
				r = RGB_R(temp);
				g = RGB_G(temp);
				b = RGB_B(temp);
				if((r>r1&&r<=r2) && (g>g1&&g<=g2) && (b>b1&&b<=b2))
				{
					colors[y*col+x]=crNew;
				}
			}
		}
		pBmp->SetBitmapBits(length, bits);
		delete colors;
	}
}
//��ȡ���������Ŀ¼����֤����һ����Ϊ�յ�ָ��
static char s_exePath[MAX_PATH]="\0";
char* GetExePath()
{
	CString cs;
	cs=GetCommandLine();
	if(cs.GetAt(0)=='"')
		cs=cs.Right(cs.GetLength()-1);
	int pos=cs.ReverseFind('\\');
	if(pos>0)
		cs=cs.Left(pos+1);//������б��
	strncpy(s_exePath, cs, MAX_PATH-1);
	return s_exePath;
}

//�õ��ŷ�����״̬
//1�б�����0û�б���
int  GetServerAlarm()
{
//	return 0;
	CString strAlarm;
	if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//λ�÷�ʽ\����
	{		
		if(g_stu_pAxisF->bSpareA == TRUE)//����ͬ��
			strAlarm = "MG(@IN[57])|(@IN[58])|(@IN[59]|(@IN[60])";
		else
			strAlarm = "MG(@IN[57])|(@IN[58])|(@IN[59])";
	}
	else//�ٶȷ�ʽ
	{
		strAlarm = "MG_HMW";
	}
	if (0 == g_handdll.GetCommandInt((char *)((const char*)strAlarm)))
	{
		return 0;//û���ŷ�������
	}
	else
	{
		return 1;
	}
}

//streamIn�����ļ���streamOut���ܵ��ļ�
void Secret(CString streamIn,CString streamOut)
{
	FILE   *fileOut, *fileIn;   
	// char   string[]   =   "This   is   a   test";   
	char   msg[80];
	fileIn =  fopen(streamIn,   "r"); 
	if (fileIn == NULL)
	{
		AfxMessageBox("���ļ�����");
		return;
	}
	fileOut = fopen(streamOut,"w"); //���ܺ���ļ������м��ļ�ͬĿ¼��
	char str[80];
	while (fgets(msg,80, fileIn))
	{
		memset(str,0,sizeof(str));
		for (int j=0;j<=80-1;j++)
		{	
			if (msg[j] == 0x0A)
			{
				str[j] = msg[j];	
				break;
			}
			str[j] = 0xff-msg[j];				
		}
		fwrite(str,   strlen(str),   1,   fileOut);   
	}     
	fclose(fileIn);   
	fclose(fileOut); 	
}

//ɾ�����ݿ���ʱ�ļ�������в���
void DeleFileLdb()
{
	CFileFind find;
	BOOL re;
	re = find.FindFile("D:\\program files\\GlassCutter\\AlarmDB.ldb");
	if (re == TRUE)
	{
		re = find.FindNextFile();		
		if(FALSE == ::DeleteFile(find.GetFilePath()))
		{
			AfxMessageBox("���ݿ���ʱ�ļ�ɾ������");
		}
	}
    find.Close();
	re = find.FindFile("D:\\program files\\GlassCutter\\Sheet.ldb");
	if (re == TRUE)
	{
		re = find.FindNextFile();		
		if(FALSE == ::DeleteFile(find.GetFilePath()))
		{
			AfxMessageBox("���ݿ���ʱ�ļ�ɾ������");
		}
	}
	find.Close();
}