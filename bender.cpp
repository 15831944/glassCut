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



int       g_ndisknum = 0;                                     //磁盘操作相关参数
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
CDmcgc       g_Dmcgc;        //CDmcgc类
CDMCWin      g_Controller;
PSYS         g_stu_pSysA,g_stu_pSysB,g_stu_pSysC,g_stu_pSysD,g_stu_pSysE;			/* 系统板卡参数 */
PCONTROLLER	 g_pstu_control;
PAXIS        g_stu_pAxisA,g_stu_pAxisB,g_stu_pAxisC,g_stu_pAxisD;		/* 机械参数，保存在文件内 */
PAXIS        g_stu_pAxisE,g_stu_pAxisF,g_stu_pAxisG,g_stu_pAxisH;		/* 机械参数，保存在文件内 */
long         g_lRc;
USHORT       g_nController = 1;
char         g_szResponse[80];
float        g_fCurrMachineX = 0.0;  //机械零点和程序零点的相对位置
float        g_fCurrMachineY = 0.0;  //机械零点和程序零点的相对位置
float        g_fCurrMachineZ = 0.0;  //机械零点和程序零点的相对位置

//======DMC文件与G代码文件变量区
CString      g_strDmcfile="";
CString      g_strGfile="";
CString      g_strDxffile="";
CString      g_arr_strGline[5110];
CString      g_strShowName;         //打开文件名，在pathtwo中的list使用。
CString      g_strSavefile;         //保存文件名，在dlg_save里面使用


int	         g_iMode = 0;                           //界面类型
int	         g_iStep = 0;                           //程序运行时，程序行计数。

//======界面使用区
CPoint     g_screen;
POINT2D    g_dScale;
CFont      g_fontButton,g_fontStatic,g_fontEdit,g_fontList,g_fontKey,g_fontRP;
CString    g_strOriginalPathC = "c:\\program files\\GlassCutter\\";//初装目录（软件工作目录）
CString    g_strOriginalPathD = "d:\\program files\\GlassCutter\\";//初装目录（软件工作目录）
COLORREF   g_crFontA = RGB(0,0,0);                //基本颜色定义
COLORREF   g_crFontC = RGB(0,255,0);              //基本颜色定义  绿色
COLORREF   g_crFontD = RGB(255,0,0);              //基本颜色定义  红色
int        g_iIsDxf = 0;//0：参数文件；1：DXF；2：G代码；
int        g_iPassgrade = 0;                          //权限级别
int        g_iLanguage = 0;                         /* 0:中文 1:英文 */
CString    g_arr_strBender[AR_BENDER][5],g_arr_strCnc[AR_CNC][5],g_arr_strGalil[AR_GALIL][5],g_arr_strHand[AR_HAND][5],g_arr_strMachine[AR_MACHINE][5],g_arr_strManager[AR_MANAGER][5];
CString    g_arr_strLimit[1][6],g_arr_strMotion[AR_MOTION][5],g_arr_strPass[AR_PASS][5],g_arr_strPath2[AR_PATH2][5],g_arr_strSave[AR_SAVE][5],g_arr_strState[AR_STATE][5];
CString    g_arr_strSuper[AR_SUPER][5];
CString    g_arr_drawcad[AR_DRAWCAD][5];
CString    g_arr_glass[AR_GLASS][5];
CString	   g_arr_light[AR_LIGHT][5];
CString	   g_arr_lightpos[AR_LIGHTPOS][5];
CString	   g_arr_message[AR_MESSAGE][5];
CString		g_strGraphLib[AR_GRAPHLIB][4];			//图库界面
CString		g_strNester[AR_NESTER][4];				//套料界面
CString		g_strNestPara[AR_NESTPARA][4];			//套料参数界面
CString		g_strPartPara[AR_PARTPARA][4];			//图库参数界面
CString		g_strConfig[AR_CONFIG][4];
CString		g_strLoading[AR_LOADING][4];
CString		g_strFathom[AR_FATHOM][4];
CString		g_strCuttingSize[AR_CUTSIZE][4];
CString		g_strBottero[AR_BOTTERO][4];
CString		g_strOiling[AR_OILING][4];
UINT        g_nProduct = 0;//总的加工个数

POINT2D		pCoor,pCoorx,pCoory;/* 玻璃毛片放置位置 垂直的交点，X轴方向一点，Y轴方向一点*/
//****************************************************************************

SYSTEMTIME			g_stCurrTime;
int       diskcheck1[10];
CString   diskname1[10];
//*************************实用全局函数类
//CString g_strSavefile;
CString g_strGCodePath = "D:\\Program Files\\GlassCutter\\GraphLib\\";
int kind;		//存储图库中一共添加了几次图形
int sqr[200];		//存储每次添加的零件类型
int sqrm[200];		//存储每次添加的零件个数
CDlg_Nest m_NestDlg;
int g_nRemainderX = 0;//bottero用
int g_nRemainderY = 0;//bottero用
stuBottero	stuBtro;//bottero用
TRACK       g_ExtraShow;               //扩展显示图形数据结构
pShowInf    g_pShowSmall;               //扩展显示原片

Cdlg_ShowExtra *     g_pDlgShowExtra; //扩展显示对话框
double g_dExtraX;                       //上一个显示的x尺寸
double g_dExtraY;                       //上一个显示的y尺寸
int g_nTestRun = 0;//运行在测试模式
int g_nRunState = 0;  //工作状态0切割；1空运行；
CString g_strExtraFile;//上一个图形的文件名
int g_nGlassNo = 0; //几块玻璃 0单片，1中空 2三片
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

	if(OnEWF()<0)     //检查写保护状态
	{
		OnEWFa();
		OnReBoot();
	}

	DeleFileLdb();
    g_machinedll.ParameterRead((char*)((const char*)(g_strOriginalPathD + "machine.ini")));/* 读取机械参数信息 */
	g_pstu_control = g_machinedll.GetController();	
	g_stu_pAxisA = &(g_pstu_control->axis[0]);	    g_stu_pAxisB = &(g_pstu_control->axis[1]);
	g_stu_pAxisC = &(g_pstu_control->axis[2]);	    g_stu_pAxisD = &(g_pstu_control->axis[3]);
	g_stu_pAxisE = &(g_pstu_control->axis[4]);	    g_stu_pAxisF = &(g_pstu_control->axis[5]);
	g_stu_pAxisG = &(g_pstu_control->axis[6]);	    g_stu_pAxisH = &(g_pstu_control->axis[7]);
    g_iLanguage = g_machinedll.GetLanguage();
	g_stu_pAxisF->bSpareA = TRUE;//龙门同步
//	g_stu_pAxisF->bSpareA = FALSE;//单驱

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	GetCurrentDisplayProp(); //显示器的分辨率	

//*************************************注册数据源名
	//*************************************注册数据源名
	//工艺数据库
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
    _ConnectionPtr m_pCon;   //ADO应用
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
		errormessage.Format( "连接数据失败!\n错误信息:%s ",   e.ErrorMessage()); 
		AfxMessageBox(errormessage); 
		return   FALSE; 
	} 


	//创建并打开记录集对象
	////===============================================================13
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from Message",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF && i<AR_MESSAGE)//
	{
		//获得第一条记录
		g_arr_message[i][0] = (char*)_bstr_t(m_pRec->GetCollect("序号"));
		g_arr_message[i][1] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_arr_message[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_message[i][3] = (char*)_bstr_t(m_pRec->GetCollect("其它"));
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
		//获得第一条记录
		g_arr_strBender[i][0] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
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
		//获得第一条记录
		g_arr_strCnc[i][0] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_arr_strCnc[i][1] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_arr_strCnc[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strCnc[i][3] = (char*)_bstr_t(m_pRec->GetCollect("其它"));
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
		//获得第一条记录
		g_arr_strManager[i][0] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_arr_strManager[i][1] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_arr_strManager[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strManager[i][3] = (char*)_bstr_t(m_pRec->GetCollect("其它"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================运动控制器
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_galil",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_GALIL)
	{
		//获得第一条记录
		g_arr_strGalil[i][0] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_arr_strGalil[i][1] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_arr_strGalil[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
//		g_arr_strGalil[i][3] = (char*)_bstr_t(m_pRec->GetCollect("其它"));
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
		//获得第一条记录
		g_arr_strHand[i][0] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_arr_strHand[i][1] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_arr_strHand[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strHand[i][3] = (char*)_bstr_t(m_pRec->GetCollect("其它"));
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
		//获得第一条记录
		g_arr_strMachine[i][0] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_arr_strMachine[i][1] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_arr_strMachine[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strMachine[i][3] = (char*)_bstr_t(m_pRec->GetCollect("其它"));
//		g_arr_strMachine[i][4] = (char*)_bstr_t(m_pRec->GetCollect("备注"));
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
		//获得第一条记录
		g_arr_strMotion[i][0] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_arr_strMotion[i][1] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_arr_strMotion[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strMotion[i][3] = (char*)_bstr_t(m_pRec->GetCollect("其它"));
		g_arr_strMotion[i][4] = (char*)_bstr_t(m_pRec->GetCollect("备注"));
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
		//获得第一条记录
		g_arr_strPath2[i][0] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_arr_strPath2[i][1] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_arr_strPath2[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strPath2[i][3] = (char*)_bstr_t(m_pRec->GetCollect("其它"));
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
		//获得第一条记录
		g_arr_strState[i][0] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_arr_strState[i][1] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
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
		//获得第一条记录
		g_arr_strPass[i][0] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_arr_strPass[i][1] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_arr_strPass[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strPass[i][3] = (char*)_bstr_t(m_pRec->GetCollect("其它"));
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
		//获得第一条记录
		g_arr_light[i][0] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_arr_light[i][1] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_arr_light[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_light[i][3] = (char*)_bstr_t(m_pRec->GetCollect("其它"));
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
		//获得第一条记录
		g_arr_strSave[i][0] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_arr_strSave[i][1] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_arr_strSave[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strSave[i][3] = (char*)_bstr_t(m_pRec->GetCollect("其它"));
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
		//获得第一条记录
		g_arr_strSuper[i][0] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_arr_strSuper[i][1] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_arr_strSuper[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_strSuper[i][3] = (char*)_bstr_t(m_pRec->GetCollect("其它"));
		g_arr_strSuper[i][4] = (char*)_bstr_t(m_pRec->GetCollect("备注"));
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
		//获得第一条记录
		g_arr_drawcad[i][2] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_arr_drawcad[i][0] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
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
		//获得第一条记录
		g_arr_glass[i][0] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_arr_glass[i][1] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_arr_glass[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_glass[i][3] = (char*)_bstr_t(m_pRec->GetCollect("其它"));
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
		//获得第一条记录
		g_arr_lightpos[i][0] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_arr_lightpos[i][1] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_arr_lightpos[i][2] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		g_arr_lightpos[i][3] = (char*)_bstr_t(m_pRec->GetCollect("其它"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================图库
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from GraphLib",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_DEFINEIO)
	{
		//获得第一条记录
		g_strGraphLib[i][2] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_strGraphLib[i][0] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_strGraphLib[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================图形库参数
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from PartPara",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_PARTPARA)
	{
		//获得第一条记录
		g_strPartPara[i][2] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_strPartPara[i][0] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_strPartPara[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================套料参数
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from NestPara",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_NESTPARA)
	{
		//获得第一条记录
		g_strNestPara[i][2] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_strNestPara[i][0] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_strNestPara[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================套料
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from Nester",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_DEFINEIO)
	{
		//获得第一条记录
		g_strNester[i][2] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_strNester[i][0] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_strNester[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================系统配置
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_config",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_CONFIG)
	{
		//获得第一条记录
		g_strConfig[i][2] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_strConfig[i][0] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_strConfig[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================上片台相关
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_loading",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_LOADING)
	{
		//获得第一条记录
		g_strLoading[i][2] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_strLoading[i][0] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_strLoading[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================上片台相关
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_oiling",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_OILING)
	{
		//获得第一条记录
		g_strOiling[i][2] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_strOiling[i][0] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_strOiling[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================测厚窗口g_strCuttingSize
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_thickness",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_LOADING)
	{
		//获得第一条记录
		g_strFathom[i][2] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_strFathom[i][0] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_strFathom[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;
	////===============================================================玻璃尺寸dlg_bottero
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_cutsize",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_CUTSIZE)
	{
		//获得第一条记录
		g_strCuttingSize[i][2] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_strCuttingSize[i][0] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_strCuttingSize[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}
	m_pRec = NULL;

	////===============================================================玻璃尺寸
    m_pRec.CreateInstance(__uuidof(Recordset));
    m_pRec->Open("select* from dlg_bottero",m_pCon.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	m_pRec->MoveFirst();
	i = 0;
	while (!m_pRec->adoEOF&&i<AR_BOTTERO)
	{
		//获得第一条记录
		g_strBottero[i][2] = (char*)_bstr_t(m_pRec->GetCollect("类型"));
		g_strBottero[i][0] = (char*)_bstr_t(m_pRec->GetCollect("中文"));
		g_strBottero[i][1] = (char*)_bstr_t(m_pRec->GetCollect("English"));
		m_pRec->MoveNext();
		i++;
	}	
	m_pRec = NULL;
	////===============================================================

	m_pCon = NULL;	
	
    OnReSetFont();
	
    OnRegSvr32();/* 注册控件 */

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

void CBenderApp::GetCurrentDisplayProp() //显示器的分辨率
{	
	g_screen.x = 1024;
	g_screen.y = 768;
	g_dScale.x = 1.28;
	g_dScale.y = 1.28;
}

void CBenderApp::OnReSetFont()    /* 软件字体统一设定 1024*768*/
{
	if(!g_iLanguage)
	{
		g_fontButton.CreateFont(20,0,0,0,FW_MEDIUM,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("宋体"));
		g_fontStatic.CreateFont(16,0,0,0,FW_LIGHT,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("宋体"));
		g_fontEdit.CreateFont(18,0,0,0,FW_LIGHT,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("宋体"));
		g_fontList.CreateFont(15,0,0,0,FW_LIGHT,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("宋体"));
		g_fontKey.CreateFont(32,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("宋体"));
	    g_fontRP.CreateFont(28,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("Times New Roman"));
	}
	else if(g_iLanguage==1)
	{
		g_fontButton.CreateFont(18,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("宋体"));
		g_fontStatic.CreateFont(16,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("宋体"));
		g_fontEdit.CreateFont(17,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("宋体"));
		g_fontList.CreateFont(15,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("宋体"));
		g_fontKey.CreateFont(19,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("宋体"));
		g_fontRP.CreateFont(28,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("Times New Roman"));
	}
	else
	{
		g_fontButton.CreateFont(15,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("宋体"));
		g_fontStatic.CreateFont(16,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("Arial"));
		g_fontEdit.CreateFont(17,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("Arial"));
		g_fontList.CreateFont(18,0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_STROKE_PRECIS,CLIP_STROKE_PRECIS,DRAFT_QUALITY,VARIABLE_PITCH|FF_SWISS,_T("宋体"));
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
	//装载ActiveX控件  
	HINSTANCE hInstance = LoadLibrary(strFileName); 
	if (hInstance == NULL)  
	{     
		OnShowMessageBox(17,g_iLanguage,FALSE);
//		AfxMessageBox("不能载入Dll/OCX文件!\nCan't find Dll/OCX files!");     
		return; 
	} 
	//取得注册函数DllRegisterServer地址 
	lpFunc = GetProcAddress(hInstance,_T("DllRegisterServer"));  
	//调用注册函数DllRegisterServer 
	if(lpFunc!=NULL)  
	{       
		if(FAILED((*lpFunc)()))   
		{       
			OnShowMessageBox(18,g_iLanguage,FALSE);
			//释放资源
			FreeLibrary(hInstance);          
			return;     
		}     
	}
	else  	OnShowMessageBox(18,g_iLanguage,FALSE);
	//===================================================================
    strFileName = g_strOriginalPathC + "Lamp.ocx";	
	//装载ActiveX控件  
	hInstance = LoadLibrary(strFileName); 
	if (hInstance == NULL)  
	{     
		OnShowMessageBox(17,g_iLanguage,FALSE);
		return; 
	} 
	//取得注册函数DllRegisterServer地址 
	lpFunc = GetProcAddress(hInstance,_T("DllRegisterServer"));  
	//调用注册函数DllRegisterServer 
	if(lpFunc!=NULL)  
	{       
		if(FAILED((*lpFunc)()))   
		{       
			OnShowMessageBox(18,g_iLanguage,FALSE);
			//释放资源
			FreeLibrary(hInstance);          
			return;     
		}     
	}
	else  	OnShowMessageBox(18,g_iLanguage,FALSE);
    strFileName = g_strOriginalPathC + "GridCAD.ocx";	
	//装载ActiveX控件  
	hInstance = LoadLibrary(strFileName); 
	if (hInstance == NULL)  
	{     
		OnShowMessageBox(17,g_iLanguage,FALSE);
		return; 
	} 
	//取得注册函数DllRegisterServer地址 
	lpFunc = GetProcAddress(hInstance,_T("DllRegisterServer"));  
	//调用注册函数DllRegisterServer 
	if(lpFunc!=NULL)  
	{       
		if(FAILED((*lpFunc)()))   
		{       
			OnShowMessageBox(18,g_iLanguage,FALSE);
			//释放资源
			FreeLibrary(hInstance);          
			return;     
		}     
	}
	else  	OnShowMessageBox(18,g_iLanguage,FALSE);	
	//===================================================================    
    strFileName = g_strOriginalPathC + "DisplayCtrl.ocx";	
	//装载ActiveX控件  
	hInstance = LoadLibrary(strFileName); 
	if (hInstance == NULL)  
	{     
		OnShowMessageBox(17,g_iLanguage,FALSE);
		return; 
	} 
	//取得注册函数DllRegisterServer地址 
	lpFunc = GetProcAddress(hInstance,_T("DllRegisterServer"));  
	//调用注册函数DllRegisterServer 
	if(lpFunc!=NULL)  
	{       
		if(FAILED((*lpFunc)()))   
		{       
			OnShowMessageBox(18,g_iLanguage,FALSE);
			//释放资源
			FreeLibrary(hInstance);          
			return;     
		}     
	}
	else  	OnShowMessageBox(18,g_iLanguage,FALSE);	
	//===================================================================
    strFileName = g_strOriginalPathC + "PlanInfo.ocx";	
	//装载ActiveX控件  
	hInstance = LoadLibrary(strFileName); 
	if (hInstance == NULL)  
	{     
		OnShowMessageBox(17,g_iLanguage,FALSE);
		return; 
	} 
	//取得注册函数DllRegisterServer地址 
	lpFunc = GetProcAddress(hInstance,_T("DllRegisterServer"));  
	//调用注册函数DllRegisterServer 
	if(lpFunc!=NULL)  
	{       
		if(FAILED((*lpFunc)()))   
		{       
			OnShowMessageBox(18,g_iLanguage,FALSE);
			//释放资源
			FreeLibrary(hInstance);          
			return;     
		}     
	}
	else  	OnShowMessageBox(18,g_iLanguage,FALSE);	
	//===================================================================
    strFileName = g_strOriginalPathC + "MSCOMM32.OCX";	
	//装载ActiveX控件  
	hInstance = LoadLibrary(strFileName); 
	if (hInstance == NULL)  
	{     
		OnShowMessageBox(17,g_iLanguage,FALSE);
		return; 
	} 
	//取得注册函数DllRegisterServer地址 
	lpFunc = GetProcAddress(hInstance,_T("DllRegisterServer"));  
	//调用注册函数DllRegisterServer 
	if(lpFunc!=NULL)  
	{       
		if(FAILED((*lpFunc)()))   
		{       
			OnShowMessageBox(18,g_iLanguage,FALSE);
			//释放资源
			FreeLibrary(hInstance);          
			return;     
		}     
	}
	else  	OnShowMessageBox(18,g_iLanguage,FALSE);	
	//===================================================================
    strFileName = g_strOriginalPathC + "BtnCtl.ocx";	
	//装载ActiveX控件  
	hInstance = LoadLibrary(strFileName); 
	if (hInstance == NULL)  
	{     
		OnShowMessageBox(17,g_iLanguage,FALSE);
		return; 
	} 
	//取得注册函数DllRegisterServer地址 
	lpFunc = GetProcAddress(hInstance,_T("DllRegisterServer"));  
	//调用注册函数DllRegisterServer 
	if(lpFunc!=NULL)  
	{       
		if(FAILED((*lpFunc)()))   
		{       
			OnShowMessageBox(18,g_iLanguage,FALSE);
			//释放资源
			FreeLibrary(hInstance);          
			return;     
		}     
	}
	else  	OnShowMessageBox(18,g_iLanguage,FALSE);	

}
BOOL CBenderApp::OnEWFa()                //在XPE中的写保护
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

BOOL CBenderApp::OnEWFb()                //在XPE中的写保护
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

void CBenderApp::OnReBoot()                //在XPE中的写保护
{
	HANDLE hToken; 
	TOKEN_PRIVILEGES tkp; 
	
	// Get a token for this process. 
	
	if (!OpenProcessToken(GetCurrentProcess(), 
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		OnShowMessageBox(19,g_iLanguage,FALSE);
//	AfxMessageBox("OpenProcessToken Error！"); 
	
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
//	AfxMessageBox("AdjustTokenPrivileges Error！"); 
	
	// Shut down the system and force all applications to close. 
	
	if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0)) 
		OnShowMessageBox(21,g_iLanguage,FALSE);
}

int CBenderApp::OnEWF()                //在XPE中的写保护
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
			c = -1;/*当前写保护状态：未保护*/
		}
		else
		{
			c = 1;/*当前写保护状态：  保护*/
		}
		
        b = EwfMgrClose(handle);
	}
	else
	{
		c = 0;/*无法得知保护状态！*/
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

void OnCheckPassword(int nFirst)    /* 权限验证 第一次开机0，启动后为1*/
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


int OnShowMessageBox(int index,int nLanguage,BOOL iTitle)                //在数据库中调用信息
{
	CDlg_AfxMessage  Message;
	Message.bYesNo = FALSE;
	switch(nLanguage) 
	{
	case 0:/* 中文 */
		Message.strAfxMessage = g_arr_message[index][1];
		Message.strAfxYES = g_arr_message[44][1];
		if(iTitle)	Message.strAfxTitle = g_arr_message[1][1];
		else		Message.strAfxTitle = g_arr_message[0][1];/* 错误 */
		break;
	case 1:/* 英文 */
		Message.strAfxMessage = g_arr_message[index][2];
		Message.strAfxYES = g_arr_message[44][2];
		if(iTitle)	Message.strAfxTitle = g_arr_message[1][2];
		else		Message.strAfxTitle = g_arr_message[0][2];
		break;
	case 2:/* 其它 */
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

int OnShowMessageBox(int index,int nLanguage)                //在数据库中调用信息
{
	int  i = 0;
	CDlg_AfxMessage  Message;
	Message.bYesNo = TRUE;
	switch(nLanguage) 
	{
	case 0:/* 中文 */
		Message.strAfxMessage = g_arr_message[index][1];
		Message.strAfxTitle = g_arr_message[1][1];
		Message.strAfxYES = g_arr_message[45][1];
		Message.strAfxNO = g_arr_message[46][1];
		break;
	case 1:/* 英文 */
		Message.strAfxMessage = g_arr_message[index][2];
		Message.strAfxTitle = g_arr_message[1][2];
		Message.strAfxYES = g_arr_message[45][2];
		Message.strAfxNO = g_arr_message[46][2];
		break;
	case 2:/* 其它 */
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

void OnSoftLimit(double fx,double fy,double bx,double by) /* 软限位设置FLBL */
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
			Message.strAfxYES ="确定";
			Message.strAfxTitle ="控制器错误";
			Message.strAfxMessage ="请全部断电，重新启动设备！";
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
			Message.strAfxYES ="确定";
			Message.strAfxTitle ="控制器错误";
			Message.strAfxMessage ="请全部断电，重新启动设备！";
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

double SaveNPoint(int n, double dVar) /* 保留4位小数 */
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

//下载光电定位速度参数
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
	
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid); //获得本地机唯一的标识   
	tkp.PrivilegeCount = 1;     
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;    
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,(PTOKEN_PRIVILEGES) NULL, 0); //调整获得的权限   
	
	if (GetLastError() != ERROR_SUCCESS)    
	{   
		AfxMessageBox("AdjustTokenPrivileges enable failed!");   
	}   
	
	fResult =InitiateSystemShutdown(    
		NULL,                                  // 要关的计算机用户名   
		"WINDOWS将在0秒后关机，请做好保存工作!",  // 显示的消息   
		0,                                    // 关机所需的时间   
		TRUE,                                 // ask user to close apps    
		TRUE);                               //设为TRUE为重起，设为FALSE为关机   
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
			AfxMessageBox("加密狗出错");
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

/* 文件夹间的拷贝 */
void CopyDirectory(CString sorPath, CString aimPath)
{
	CFileFind cFind;
	BOOL bFind;
	
	BOOL re = CreateDirectory(aimPath, NULL);
	
	bFind = cFind.FindFile(sorPath+"\\*.*");
	while(bFind) 
	{
		bFind = cFind.FindNextFile();
		if (cFind.IsDirectory() && !cFind.IsDots() && !cFind.IsHidden())//是文件夹
		{  
			CopyDirectory(sorPath+"\\"+cFind.GetFileName(), aimPath+"\\"+cFind.GetFileName());
		}
		else
		{
			CopyFile(sorPath+"\\"+cFind.GetFileName(), aimPath+"\\"+cFind.GetFileName(),FALSE);
		}
	}
}

/* 删除文件夹 */
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
	find.Close();//一定先关闭这个,在移除删除文件夹
	::RemoveDirectory(strPath);
}


CString movediskdir()
{
    CFileFind   finder;
    int         i = 0;
	CString     root[10] = {"D:\\","E:\\","F:\\","G:\\","H:\\","I:\\","J:\\","K:\\","L:\\","M:\\",};
	CString     s_dir;
	
	while(GetDriveType(root[i])!=DRIVE_REMOVABLE&&i<9)     //查找可移动磁盘
		i++;
	s_dir = root[i];
	if(i==9&&GetDriveType(root[9])!=DRIVE_REMOVABLE)
	{
		s_dir = "";
		if(OnIsDisk()==0)
		{
			return s_dir;                                  //找不到移动盘，返回
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


int OnIsDisk()                                //是否有移到硬盘
{
	int        i,j;
    int        n = 0,m = 0;
	CString    root[10] = {"D:\\","E:\\","F:\\","G:\\","H:\\","I:\\","J:\\","K:\\","L:\\","M:\\"};
	
	for(i=0;i<10;i++)
	{
		if(GetDriveType(root[i])==DRIVE_FIXED)             //有几个本地磁盘
		{
			diskcheck1[i] = DRIVE_FIXED;
			diskname1[i] = root[i];
			n++;
		}
		else if(GetDriveType(root[i])==DRIVE_REMOVABLE)    //有几个移动磁盘
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
	if(g_ndisknum!=n)                                         //disknum是在程序启动后，一次性赋值。不再改动!
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
	//创建与传入DC兼容的临时DC 
	memDC.CreateCompatibleDC(pDC); 
	HRGN hrgn;
	hrgn = CreateRectRgn(0, 0, 0, 0);
	CombineRgn(c,c,hrgn,RGN_AND);
	DeleteObject(hrgn);
	CBitmap cBitmap;
	cBitmap.LoadBitmap(nID);
	memDC.SelectObject(&cBitmap); 
	BITMAP   bit;       
    cBitmap.GetBitmap   (&bit);//取得位图参数，这里要用到位图的长和宽        
	int   y; 
	for(y=0; y<bit.bmHeight; y++) 
	{ 
        CRgn rgnTemp;  //保存临时region 
		
		int iX = 0; 
		do 
		{ 
			//跳过透明色找到下一个非透明色的点. 
			while   (iX<=bit.bmWidth && memDC.GetPixel(iX,y)==RGB(255,255,255)) 
				iX++; 
			
			//记住这个起始点 
			int   iLeftX = iX; 
			
			//寻找下个透明色的点 
			while   (iX<=bit.bmWidth && memDC.GetPixel(iX,y)!=RGB(255,255,255)) 
				iX++; 
			
			//创建一个包含起点与重点间高为1像素的临时“region” 
			rgnTemp.CreateRectRgn(iLeftX,y,iX,y+1); 
			
			//合并到主 "region ". 
			CombineRgn(c,c,rgnTemp,RGN_OR); 
			
			//删除临时 "region ",否则下次创建时和出错 
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
        GetClassName(pCtlWnd->GetSafeHwnd(), cClassName, 255);//获取控件的类名
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

//创建一个内存DC
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


//将图片垂直翻转
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
//获取软件的运行目录，保证返回一个不为空的指针
static char s_exePath[MAX_PATH]="\0";
char* GetExePath()
{
	CString cs;
	cs=GetCommandLine();
	if(cs.GetAt(0)=='"')
		cs=cs.Right(cs.GetLength()-1);
	int pos=cs.ReverseFind('\\');
	if(pos>0)
		cs=cs.Left(pos+1);//保留反斜杠
	strncpy(s_exePath, cs, MAX_PATH-1);
	return s_exePath;
}

//得到伺服报警状态
//1有报警，0没有报警
int  GetServerAlarm()
{
//	return 0;
	CString strAlarm;
	if (g_stu_pAxisA->sSpare==0 || g_stu_pAxisA->sSpare==2)//位置方式\串口
	{		
		if(g_stu_pAxisF->bSpareA == TRUE)//龙门同步
			strAlarm = "MG(@IN[57])|(@IN[58])|(@IN[59]|(@IN[60])";
		else
			strAlarm = "MG(@IN[57])|(@IN[58])|(@IN[59])";
	}
	else//速度方式
	{
		strAlarm = "MG_HMW";
	}
	if (0 == g_handdll.GetCommandInt((char *)((const char*)strAlarm)))
	{
		return 0;//没有伺服报警合
	}
	else
	{
		return 1;
	}
}

//streamIn加密文件；streamOut解密的文件
void Secret(CString streamIn,CString streamOut)
{
	FILE   *fileOut, *fileIn;   
	// char   string[]   =   "This   is   a   test";   
	char   msg[80];
	fileIn =  fopen(streamIn,   "r"); 
	if (fileIn == NULL)
	{
		AfxMessageBox("打开文件错误");
		return;
	}
	fileOut = fopen(streamOut,"w"); //解密后的文件，和中间文件同目录。
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

//删除数据库临时文件，如果有产生
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
			AfxMessageBox("数据库临时文件删除错误");
		}
	}
    find.Close();
	re = find.FindFile("D:\\program files\\GlassCutter\\Sheet.ldb");
	if (re == TRUE)
	{
		re = find.FindNextFile();		
		if(FALSE == ::DeleteFile(find.GetFilePath()))
		{
			AfxMessageBox("数据库临时文件删除错误");
		}
	}
	find.Close();
}