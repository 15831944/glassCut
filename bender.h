// bender.h : main header file for the BENDER application
//

#if !defined(AFX_BENDER_H__219CE647_90FD_4800_8D96_0313BC05A5BF__INCLUDED_)
#define AFX_BENDER_H__219CE647_90FD_4800_8D96_0313BC05A5BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#pragma warning( disable: 4786 4244)
#include "resource.h"		// main symbols

#include "hasp_api.h"
#include "2DDraw.h"
#include "dlg_ShowExtra.h"
#include "Dlg_AfxMessage.h"
#define POWERLAND 
//#define CHAOYANG   //控制注油方式  
#ifndef POWERLAND
	#define BACKCOLOR               RGB(203,211,237)//对话框背景颜色
#else//通用
	#define BACKCOLOR               RGB(214,226,247)//对话框背景颜色较浅(165,198,248)较深(146,189,247)
#endif
//=======================================================================
#define HAND_CON   0
#define HAND_01    1
#define HAND_1     2
#define HAND_5     5
#define HAND_10    10

//=======================================================================
#define HAND_X     0
#define HAND_Y     1
#define HAND_Z     2

//========================================定义每个界面有多少个语言元素
#define AR_BENDER     20
#define AR_CNC         4
#define AR_GALIL      19
#define AR_HAND       2
#define AR_MACHINE    21
#define AR_MANAGER    12
#define AR_MOTION     25
#define AR_PASS        5
#define AR_PATH2      10
#define AR_SAVE        4
#define AR_STATE       9
#define AR_ZERO       13
#define AR_PAGE        5
#define AR_DRAWCAD    14
#define AR_GLASS       3
#define AR_SUPER      16
#define AR_LIGHT	  17
#define AR_MESSAGE	  51
#define AR_LIGHTPOS	  17
#define AR_DEFINEIO		43
#define AR_GRAPHLIB		 5
#define AR_NESTER		 9
#define AR_NESTPARA		 7
#define AR_PARTPARA		 3
#define AR_CONFIG		47
#define AR_LOADING		3
#define AR_OILING		3
#define AR_FATHOM		3
#define AR_CUTSIZE		18
#define AR_BOTTERO		8
#define AR_SOFTPASS     5  //软件密码界面中英文个数
#define AR_GEIT			11
//=======================================================================


#define WM_SCALE		WM_USER+108/* 公英制 */

//=============================================输入
#define IN_SERVOX_HOME		17	/*零点*/
#define IN_SERVOY_HOME		18	/*零点*/
#define IN_SERVOZ_HOME		19	/*零点*/
#define IN_SERVOW_HOME		20	/*零点*/
#define IN_SERVOX_LIMIT		33	/*伺服限位*/
#define IN_SERVOY_LIMIT		34	/*伺服限位*/
#define IN_SERVOZ_LIMIT		35	/*伺服限位*/
#define IN_SERVOW_LIMIT		36	/*伺服限位*/
#define IN_SERVOX_RLIMIT	37	/*负限位*/
#define IN_SERVOY_RLIMIT	38	/*负限位*/
#define IN_SERVOZ_RLIMIT	39	/*负限位*/
#define IN_SERVOW_RLIMIT	40	/*负限位*/

#define IN_EMG_STOP			25	/*急停开关*/

#define IN_SERVOX_STATE		29	/*伺服状态*/
#define IN_SERVOY_STATE		30	/*伺服状态*/
#define IN_SERVOZ_STATE		31	/*伺服状态*/
#define IN_SERVOW_STATE		32	/*伺服状态*/

#define IN_ADDX             41  //X+
#define IN_SUBX             42  //X-
#define IN_ADDY             43  //Y+
#define IN_SUBY             44  //Y-
#define IN_LABEL            45  //标签感应
#define IN_FANS             46  //风机手动控制
#define IN_SAFE             47  //安全光栅

#define IN_SERVOX_ALARM		57	/*伺服报警*/
#define IN_SERVOY_ALARM		58	
#define IN_SERVOZ_ALARM		59	
#define IN_SERVOW_ALARM		60

//=============================================输入点定义
#define IN_LIGHT			1	/* 光电定位开关 */
#define IN_RUN				3
#define IN_STOP				4
#define IN_BREAK_READY		5	/*分片台允许传送，该输入接通时切完的玻璃允许传出。*/
#define IN_FSTSWITCH		6
#define IN_GLASSREADY		7
#define IN_DIEDOWN			8	/* 下刀输入 */

//=============================================输出点定义
#define OUT_ORIENTATION			1      //定位柱 
#define OUT_CUT_OILING			2	   //切割油
#define OUT_BEGINSEND			3      //给上片台信号，开始传送玻璃
#define OUT_WIND_RELAY			4      //风机启停
#define OUT_OILING				5      //注煤油
#define OUT_SENDUPDN			6      //传送带升降
#define OUT_TRANSDUCER_FORWARD	7      //变频器正向
#define OUT_TRANSDUCER_REVERSE	8      //变频器反向
//作为中间变量使用
#define OUT_ZAXIS_DN			31      //c轴下刀
#define OUT_ZAXIS_DN1			18      //c轴下刀
#define OUT_TRANSDUCER_SPEED	25      //快速慢速
#define OUT_TRANSDUCER_SPEED1	17      //快速慢速
#define OUT_LED_RUN				19      //启动
#define OUT_LED_STOP			20      //停止
//21贴标签，在库中写死
//=======================================================================


//加密狗读写地址的偏移量
#define USER_SECRET1              0  //超级管理员
#define USER_SECRET2             20  //管理员1
#define USER_SECRET3             40  //管理员2
#define TIME_YEAR                60  //加密时间
#define TIME_MONTH               80  //加密时间
#define TIME_DAY                100  //加密时间
#define TIME_SECRET             120  //加密的密码
#define TIME_VENDER             140 //加密的厂家号
#define CONTROLVER              160 //控制器号
//新增加的数据保存的文件名
//1:上片台准备时间（s）
//2:最大圆弧半径
#define INIFILE_ADDEXTRA           "D:\\program files\\GlassCutter\\AddExtra.ini"

#define INIFILE_LASTINF            "D:\\program files\\GlassCutter\\LastInfor.ini"

#define	INIFILE_SCAN               "D:\\program files\\GlassCutter\\Scan.ini"

/////////////////////////////////////////////////////////////////////////////
// CBenderApp:
// See bender.cpp for the implementation of this class
struct tagScanPARA
{	
	double				dScanPace;			/* 扫描步长 */
	double				dScanSpeed;			/* 自动扫描速度 */
	double			    dScanBeginPosX;		/* 扫描起始点X */
	double			    dScanBeginPosY;		/* 扫描起始点Y */
	double			    dScanCenterPosX;	/* 扫描中点X */
	double			    dScanCenterPosY;	/* 扫描中点Y */
}; 
typedef struct tagPARA SCANPARA, *PSCANPARA;
extern int			g_ndisknum;
extern CString		g_strdiskname[10];
//======运动控制器变量区
extern  tagScanPARA	 g_ScanPara;
extern  CAlarmDll	g_AlarmDll;
extern  CSystemDll   g_systemdll;
extern  CMachineDll  g_machinedll;
extern  CHandDll     g_handdll;
extern  CCuttingPress    g_CutPress;
extern  CDmcgc       g_Dmcgc;        //CDmcgc类
extern  CDMCWin      g_Controller; //CDMCWin类
extern  PSYS         g_stu_pSysA, g_stu_pSysB, g_stu_pSysC, g_stu_pSysD, g_stu_pSysE;
extern	PCONTROLLER	 g_pstu_control;
extern  PAXIS        g_stu_pAxisA,g_stu_pAxisB,g_stu_pAxisC,g_stu_pAxisD;
extern  PAXIS        g_stu_pAxisE,g_stu_pAxisF,g_stu_pAxisG,g_stu_pAxisH;     /* 机械参数，保存在文件内 */
extern  long         g_lRc;
extern  USHORT       g_nController;
extern  char         g_szResponse[80];
extern  float        g_fCurrMachineX;
extern  float        g_fCurrMachineY;
extern  float        g_fCurrMachineZ;
//======DMC文件与G代码文件变量区
extern  CString      g_strDmcfile,g_strGfile,g_strDxffile;
extern  CString      g_arr_strGline[5110];
extern  CString      g_strShowName;         //打开文件名，在pathtwo中的list使用。
extern  CString      g_strSavefile;         //保存文件名，在dlg_save里面使用

//======脉冲当量、自动速度、手动速度、加减速的变量区
extern  int  	     g_iMode;   //BUTTON WINDOW按键显示类别。
extern  int	         g_iStep;   //程序运行时，程序行计数。


//======界面使用区
extern  CPoint       g_screen;
extern  POINT2D      g_dScale;
extern  CFont        g_fontButton,g_fontStatic,g_fontEdit,g_fontList,g_fontKey,g_fontRP;
extern 	CString      g_strOriginalPathC;		//初装目录（软件工作目录）
extern 	CString      g_strOriginalPathD;		//初装目录（软件工作目录）
extern 	COLORREF     g_crFontA;					//基本颜色定义
extern 	COLORREF     g_crFontC;					//基本颜色定义
extern 	COLORREF     g_crFontD;					//基本颜色定义
extern  int          g_iIsDxf;					//0：参数文件；1：DXF；2：G代码；
extern  int          g_iPassgrade;				//权限级别
extern  int          g_iLanguage;	

extern  CString      g_arr_strBender[AR_BENDER][5],g_arr_strCnc[AR_CNC][5],g_arr_strGalil[AR_GALIL][5],g_arr_strHand[AR_HAND][5],g_arr_strMachine[AR_MACHINE][5],g_arr_strManager[AR_MANAGER][5];
extern  CString      g_arr_strLimit[1][6],g_arr_strMotion[AR_MOTION][5],g_arr_strPass[AR_PASS][5],g_arr_strPath2[AR_PATH2][5],g_arr_strSave[AR_SAVE][5],g_arr_strState[AR_STATE][5];
extern  CString      g_arr_strSuper[AR_SUPER][5];
extern  CString      g_arr_drawcad[AR_DRAWCAD][5];
extern  CString		 g_arr_glass[AR_GLASS][5];
extern  CString		 g_arr_light[AR_LIGHT][5];
extern  CString	     g_arr_lightpos[AR_LIGHTPOS][5];
extern  CString	     g_arr_message[AR_MESSAGE][5];
extern	CString		g_strGraphLib[AR_GRAPHLIB][4];			//图库界面
extern	CString		g_strNester[AR_NESTER][4];				//套料界面
extern	CString		g_strNestPara[AR_NESTPARA][4];			//套料参数界面
extern	CString		g_strPartPara[AR_PARTPARA][4];			//图库参数界面
extern	CString		g_strConfig[AR_CONFIG][4];
extern	CString		g_strLoading[AR_LOADING][4];
extern	CString		g_strFathom[AR_FATHOM][4];
extern	CString		g_strCuttingSize[AR_CUTSIZE][4];
extern	CString		g_strBottero[AR_BOTTERO][4];
extern	CString		g_strOiling[AR_OILING][4];
extern  UINT        g_nProduct;//总的加工个数
extern  POINT2D		pCoor,pCoorx,pCoory;

extern unsigned char vendorCode[];
extern TRACK       g_ExtraShow;          //扩展显示图形数据结构
extern pShowInf     g_pShowSmall;          //扩展显示原片
extern Cdlg_ShowExtra *     g_pDlgShowExtra; //扩展显示对话框
extern double g_dExtraX;                       //上一个显示的x尺寸
extern double g_dExtraY;                       //上一个显示的y尺寸
extern int g_nTestRun ;//运行在测试模式
extern SYSTEMTIME g_stCurrTime;//当前加密狗时间
extern int       diskcheck1[10];
extern CString   diskname1[10];
extern int g_nRunState;  //工作状态0切割；1空运行；
extern CString g_strExtraFile;//上一个图形的文件名
extern int g_nGlassNo; //几块玻璃 0单片，1中空 2三片
struct tagSegmentARC
{
	float			fRadius;
	float			fBeginAngle;
	float			fSweepAngle;
	float			fCenterX;
	float			fCenterY;
}; 
typedef struct tagSegmentARC SegARC, *pSegARC;

struct tagSegment
{
	BOOL			bIsLine;			/* 直线为TRUE，圆弧为FALSE */
	BOOL			bDirect;			/* 圆弧：顺时针T还是逆时针F；直线：是否被合并,TRUE 合并 */
	float			fBeginX;
	float			fBeginY;
	float			fEndX;
	float			fEndY;
	tagSegmentARC	*pSegArc;
	tagSegment		*Prev;
	tagSegment		*Next;
}; 
typedef struct tagSegment Segment, *pSegment;

struct tagRectDraw
{
	int             nDraw;          //1画
	int             nNum;           //序列号
	CRect           rect;           //矩形
	tagRectDraw		*Next;
}; 
typedef struct tagRectDraw RectDraw, *pRectDraw;

struct tagBotteroCommand
{
	int					nIndex;			/* 命令序号 */
	char				chCom;			/* 命令字符 */  
	int					nMultiple;		/* 乘法器数值，默认为1或0 */
	float				nValue;			/* 命令数值 */
	char				chName[50];		/* 如果是异形，异形名称 */
	float				fTotalDis;		/* 此命令用掉的总长度 */
	int                 nDraw;          //画过
	pRectDraw           pRect;          //命令对应的画矩形的链表
	pSegment			pStuSegment;    
	tagBotteroCommand	*Prev;
	tagBotteroCommand	*Next;
}; 
typedef struct tagBotteroCommand stuBotteroCommand, *p_Command;

struct tagBottero
{
	long				lMaterialX;			/* 原片尺寸X */
	long				lMaterialY;			/* 原片尺寸Y */   
	long				lModifyX;			/* 修边尺寸X */
	long				lModifyY;			/* 修边尺寸Y */   
	float				fTop;
	float				fBottom;
	float				fLeft;
	float				fRight;
	tagBotteroCommand	*BtroComm;
}; 
typedef struct tagBottero stuBottero, *p_stuBottero;

struct tagSheetGlass
{
	CString         strRect;//长宽厚度
	COleDateTime    timeCut;  //切割时间
	int             nNum;     //次数
};
typedef struct tagSheetGlass stuSheetGlass, *p_stuSheetGlass;
struct tagRectEdit
{
	int  nIndex;    //序号从1开始
	POINT2D dpStart;//起点的xy坐标
	POINT2D dpRect; //xy的长度
	int nNumX;      //行数
	int nNumY;      //列数
	char szGraph[4000];//异性命令
	POINT2D dpTrim;  //修边
	tagRectEdit *Prev;
	tagRectEdit	*Next;
};
typedef struct tagRectEdit stuRectEdit, *p_stuRectEdit;


//*************************实用全局函数类
void OnReSetFont();
CRect OnReSetRectV(CRect rc);
void OnCheckPassword(int nFirst);    /* 权限验证 */
double PointToPointAngle(double dBcx,double dBcy,double dEcx,double dEcy);
int OnShowMessageBox(int index,int nLanguage,BOOL iTitle);                //在数据库中调用信息
int OnShowMessageBox(int index,int nLanguage);                //在数据库中调用信息
void OnSoftLimit(double fx,double fy,double bx,double by); /* 软限位设置FLBL */
double SaveNPoint(int n, double dVar); /* 保留4位小数 */
CPoint ReadMaxSpeed();
 
//下载光电定位速度参数
void SetFindLightSpeed();
int HasWriteValue(CString strValue,hasp_size_t offset);

int HasReadValue(CString &strValue, hasp_size_t offset);

/* 文件或文件夹的拷贝 */
void CopyDirectory(CString sorPath, CString aimPath);

/* 删除文件夹 */
void DeleteDirectory(CString strPath);

CString movediskdir();

int OnIsDisk();                                //是否有移到硬盘

void GetBitMapRgn(CDC *pDC, HRGN &c,int nID);

void SetCtlFont(CWnd *pWnd);

//得到伺服报警状态
//1有报警，0没有报警
int  GetServerAlarm();

//GraphDlg
void CreateDC(CDC *pMemDC, CDC *pSrcDC, int width, int height);
void ConvertGraphCoordinate(CDC *pDC);
void ReplaceColor(CDC *pDC, const COLORREF crOld1, const COLORREF crOld2, const COLORREF crNew);
char* GetExePath();
//streamIn加密文件；streamOut解密的文件
void Secret(CString streamIn,CString streamOut);

//删除数据库临时文件，如果有产生
void DeleFileLdb();
//****************************************************************************
/*
#define OnShowMessageBox(index,nLanguage)    MessageBox(g_arr_message[index][1],g_arr_message[1][nLanguage],MB_OK);             //在数据库中调用信息
*/
#include "Dlg_Nest.h"

//extern CString g_strSavefile;
extern CString g_strGCodePath;
extern int kind;		//存储图库中一共添加了几次图形
extern int sqr[200];		//存储每次添加的零件类型
extern int sqrm[200];		//存储每次添加的零件个数
extern CDlg_Nest m_NestDlg;
extern int g_nRemainderX;//bottero用
extern int g_nRemainderY;//bottero用
extern stuBottero	stuBtro;//bottero用
class CBenderApp : public CWinApp
{
public:
	CBenderApp();
	void ShutDown();
private:
	void GetCurrentDisplayProp(); //显示器的分辨率
	void OnReSetFont();
	void OnRegSvr32();   
	BOOL OnEWFa();                  //在XPE中的写保护
	BOOL OnEWFb();                  //在XPE中的写保护
	void OnReBoot();                //在XPE中的写保护
	int OnEWF();                   //在XPE中的写保护
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBenderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBenderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern  CBenderApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BENDER_H__219CE647_90FD_4800_8D96_0313BC05A5BF__INCLUDED_)
