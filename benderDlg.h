// benderDlg.h : header file
//
//{{AFX_INCLUDES()
#include "displayctrl.h"
#include "planinfo.h"
#include "captioninfo.h"
#include "lamp.h"
#include "OrangeListCtrl.h"
#include "mscomm.h"
#include "btnctl.h"
//}}AFX_INCLUDES

#if !defined(AFX_BENDERDLG_H__7F102487_41BA_4479_A554_9F97BA094865__INCLUDED_)
#define AFX_BENDERDLG_H__7F102487_41BA_4479_A554_9F97BA094865__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include ".\SCAN\ScanAct.h"
#include ".\SCAN\ScanWork.h"
#include "dlg_hand.h"
#include "Dlg_Home.h"
#include "CTest.h"
#include "Dlg_scan.h"

#define MODE_C     3    //手动
#define MODE_D     4    //回零
#define MODE_E     5    //编辑/图库
#define MODE_F     6    //异性扫描
#define MODE_H     7    //诊断
#define MODE_A     1    //龙门校正
#define MODE_MAIN  0    //自动

/* 定义小编辑窗口消息 */
#define WM_SMALLEDIT	WM_USER+100
#define WM_3dWnd		WM_USER+101
#define WM_RUNOPTION	WM_USER+102
#define WM_AFFIRM		WM_USER+106
#define WM_INPUT		WM_USER+107	/* 外部有输入时，发送消息 */
#define WM_ALMINPUT		WM_USER+108	/* 主窗口的输入，发送到诊断进行显示 */
#define WM_ALMOUTPUT	WM_USER+109	/* 主窗口的输出，发送到诊断进行显示 */

#define WM_SCAN			WM_USER+110	/* 向扫描窗口发消息，报告扫描状态 */

class CDlg_affirm;

/////////////////////////////////////////////////////////////////////////////
// CBenderDlg dialog


class CBenderDlg : public CDialog
{
// Construction
public:
	CBenderDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CBenderDlg();
	void OnCancel();
	void OnOk();

	C2DDraw	  m_PVM;
	dlg_hand  *m_pHandDlg;
	CDlg_Home  *m_pHomeDlg;
	CDlg_affirm	  *m_pAffirm;/* 光电定位 */
	CCTest *m_pTestDlg;
	CDlg_scan *m_pScanDlg;
	int    iOldStep;
	CString   strNullityLine;
	CString   strGCodeOpenFile;	
    CDxf2G   DxftoG;
	int 	 nNewInput[10];
	int 	 nOldInput[10];
	int 	 nNewOutput[2];
	int 	 nOldOutput[2];	

	bool    m_bDlgPath; //文件选择对话框。
	bool    m_bShowExtra;
	pShowInf m_pInf;    //小片信息
	int   m_nSafeSwich; //光幕
	int	  m_iSetNum,m_iRunNum,m_iReadyTime;

	// Dialog Data
	//{{AFX_DATA(CBenderDlg)
	enum { IDD = IDD_BENDER_DIALOG };
	CEditDoubleClick	m_editLabSet;
	CEditDoubleClick	m_editRunNum;
	CEditDoubleClick	m_editSetNum;
	CEditDoubleClick	m_DEditH;
	COrangeListCtrl	m_listGrid;
	CUniButton	m_UbtOilAB;
	CUniButton	m_UbtPause;
	CUniButton	m_UbtPre;
	CUniButton	m_UntNext;
	CUniButton	m_UbtLast;
	CUniButton	m_UbtFirst;
	CUniButton	m_UbtWater;
	CUniButton	m_UbtnTest;
	CUniButton	m_UbtnScan;
	CUniButton	m_btnDefault;
	CUniButton	m_btn3dUp;
	CUniButton	m_btn3dDown;
	CUniButton	m_btn3dLeft;
	CUniButton	m_btn3dRight;
	CUniButton	m_btn3dPgup;
	CUniButton	m_btn3dPgdn;
	CUniButton	m_btnHome;
	CUniButton	m_btnEnd;
	CUniButton	m_main8;
	CUniButton	m_main7;
	CUniButton	m_main6;
	CUniButton	m_main5;
	CUniButton	m_main9;
	CUniButton	m_main10;
	CUniButton	m_main4;
	CUniButton	m_main3;
	CUniButton	m_main2;
	CUniButton	m_main1;
	CUniButton	m_mainStart;
	CUniButton	m_mainStop;
	CDisplayCtrl	m_ocxDisplay;
	CPlanInfo	m_ocxPlanSpeed;
	CCaptionInfo	m_CapTitle;
	CLamp	m_LedX;
	CLamp	m_LedY;
	CLamp	m_LedZ;
	CCaptionInfo	m_captionFile;
	CPlanInfo	m_ocxPlanPress;
	CUniButton  m_UbnPressDn;
	CUniButton  m_UbnPressUp;
	CMSComm	m_MscComm;
	CBtnCtl	m_BtnMin;
	int		m_nGlassNo;
	int		m_nLabelSt;
	CCaptionInfo	m_CapTime;
	CCaptionInfo	m_CapAlarm;
	//}}AFX_DATA
	void FileOpen();                              //G代码程序打开.
	void GCodeOpen(CString gCode);                //进行转换处理
	void ResetCS(CString gCode,CString dmcCode);
	void SetManometer(); /* 压力显示 */
	void OnShowLine(); 
	void SetInitAutoSpeed(); /* 设置初始自动程序的进给速度 */
	void SetAutoRateAdd();   /* 进给倍率加 */
	void SetAutoRateSub();   /* 进给倍率减 */
	void OnSystemTimer();
	void OnMachineBK();
	long OnProgramBoxG();
	
	void CalculateZoom();//计算全屏显示范围
		

	int HardDogCheck();

	void ConvertDxfToGcode();

	void RunTest(int nValue);//运行test里面的功能

	void DrawBottero();//刷新bottero

	//初始化位置显示字体
	void InitRPShow();

	bool GetScanRun();

	long SetAOorOF(double dVar); 

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBenderDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON   m_hIcon;
	CRect   m_rct;//实时轨迹的尺寸
	CRect   m_rctOrig;//原片的尺寸
	PDMC	p_stuDmc,pstu_Currdmc;

	SYSTEMTIME		stime_run;	
	double			dTimeA,dTimeB,dTimeC,dTime;
	
	int  m_nTestRun;//运行在测试模式
	bool  CheckContinousWork(CString  strWorkName);
	void  OnErnInButton();
	int   OnSetRunState();	/* 写入上片台等待玻璃位置 0写入错误；1写入正常*/

	void GetCRRange(double fBaseX,double fBaseY,PDMC pdmc);
	void SetRange(double fx, double fy);
	void OnExit();
	void OnInitGalil();
	void OnInitOCX();
	void OnInitModenessDlg();
	BOOL OnBegoreRunCheck(); /* 程序运行 */
	
	void InitScanPara(); /* 初始化巡边参数 */
		
	void OnRunWithNoLoad(); /* 程序运行 */
	void OnDirectRun(); /* 程序运行 */		
	void OnRunTimeCount();				/* 跑图形时间统计 */
	
	void MachineZeroAlarm(BOOL bLanguage);
	
	//加密狗加密
	int m_nTimer10;//定时器10进入的次数

	int GetHarddogTime(int nFirst);
	void HarddogExit();
	//加密狗加密
	

    //初始化不规则按钮
	void InitRgnButton();

	//初始化工作状态：切割/空运行，run界面
	void InitRunState();

	//初始化显示信息
	void InitGridInf();

	//nPreNext:0向前;1向后
	//找下一个文件 0:没有找到;1:找到下一个
	int FineFile(int nPreNext);

	/* 注油功能，保存dmc */
	void WriteOilingDmc();

	//读取打印标签的参数并且赋值给gdmcgc32
	void InitPrintLabel();
	// Generated message map functions
	//{{AFX_MSG(CBenderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonStop();
	afx_msg void OnButtonRun();
	afx_msg void OnButtonPause();
	afx_msg void OnButtonOil();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton10();
	afx_msg void OnButtonHome();
	afx_msg void OnButtonEnd();
	afx_msg LRESULT OnRunOption(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnAffirm(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnMsgInput(WPARAM wParam, LPARAM lParam);
	afx_msg UINT OnDMCGC(WPARAM wParam,LPARAM lParam);
	afx_msg UINT OnFromDllSendScan(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClickPlaninfoctrlSpeed();
	afx_msg void OnButtonTest();
	afx_msg void OnButtonScan();
	afx_msg void OnButtonView();
	afx_msg void OnButtonFirst();
	afx_msg void OnButtonPre();
	afx_msg void OnButtonNext();
	afx_msg void OnButtonLast();
	afx_msg void OnClickPlaninfoPress();
	afx_msg void OnButtonState();
	afx_msg void OnButtonPressdown();
	afx_msg void OnButtonPressup();
	afx_msg void OnDblClickDisplayMaininf();
	afx_msg void OnChangeEditThick();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClickBtnMin();
	afx_msg void OnButtonBtnStart();
	afx_msg void OnButtonBtnStop();
	afx_msg void OnClickButton3ddown();
	afx_msg void OnClickButton3dup();
	afx_msg void OnClickButton3dleft();
	afx_msg void OnClickButton3dright();
	afx_msg void OnClickButton3dpgup();
	afx_msg void OnClickButton3dpgdn();
	afx_msg void OnClickButtonDefault();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEditLabelst();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
private:
	void OnInitInput();
	int OnSingleInput();
	int OnSingleLFR();
	int OnSingleMO();
	void OnCompareInput(int nBase, int nOld, int nNew);
	void OnCompareBinary(int nBase,int nFirst,int nCecond);//急停用
	void OnCompareInt(int nBase,int nFirst,int nCecond);
	void SendInput(int nBase, int nValue);
	void SendOutput(int nBase, int nValue);
	void OnReadOutput(); /* 输出点 */

	void OnDisplayOutput(int nCount);	//自定义输出点	

	
	void OnOpenController();//打开运动控制器
		
	/* 初始化手动下刀压力 */
	void OnInitHandPressure(); 		

	CString			m_strHome;
	CString			m_strDmcAV;
	CString			m_strPressFile;
	CString			m_strBreak;

	BOOL			m_bRunFlag;	

	BOOL            m_bContiueRun;

	BOOL            m_bFile;//FineFile()等手工操作打开文件

	BOOL			m_bAffirm;

	bool            m_bNormal;//通讯状态

	CBrush          m_brush;


/* 玻璃切割的异形扫描功能 */	
public:
	long  m_nScanTreadID;	
	void  ScanStop();
	void  ScanRun();
	void  ScanSaveGcode();
	void  ScanSavePos(int nFormat);

private:
	
	CScanWork	m_clsScan;
	int   m_nExpandX;//扩展显示器X
	int   m_nExpandY;//扩展显示器Y
    BOOL  m_bExpandShow;//是否有扩展显示器
    bool  m_bFirstOpen;
	int   m_nOpenLight; // 1:光电定位后，重新打开图形 ; 0:直接fileopen打开原始图形

	bool  m_bEmreStop; //1 急停后，需要重新打开图形

    CRITICAL_SECTION m_Section;//临界区控制fileopen

	long  m_lTVX;
	long  m_lTVY;
	long  m_lTVZ;

	void OnIniRunVS(long nValue);

	//得到是否上电回机械零点，1回；0没回。
	int  GetZeroState();

	//初始化软限位
	void InitSoftLimit();

	//得到扩展显示器的参数，是否有扩展显示器，X Y 分辨率
    void GetExpandShowInf();

	//显示扩展显示器
	void ShowExpand();

	//复制这一个图形的数据，为这次加工完显示用
	void CopyPreShowInf();

	//开始切割下载加减速
	void DownAccDcc();

	//保存玻璃光电定位以后的偏移参数，断电记忆用
	void SaveLightPar();
	
	//得到玻璃光电定位以后的偏移参数，断电记忆用
	void GetLightPar();

	//清除已经打开的图形和切割轨迹,扫描和编辑用
	void OnInit2DDrawShow();

	//初始化速度显示
	void OnTVShow();

	//保存原片信息到数据库
	void SaveSheetToMdb();  

	//在手动打开文件时，如果是符合文件名标准的自动得到加工个数
	void GetSheetCount();

	//加工完成后增加加工个数保存显示
	void ModifyProduct();

	//开始切割时把开始贴标的个数设为1
	void SetLabelStart();

	//判断是不是最后一片玻璃；是返回true
    bool JudgeLastFile();

	//画标尺
	void DrawRules(CDC *pDC);
//只用于龙门方式压力
	//初始化串口
	void OpenMsCom();
	
	//关闭串口
	void CloseMsCom();
	
	//下载压力SendValue:参数压力值和SendAddtr:DA通道0
	void SetComPress(double SendValue,long SendAddtr=0);
	
	// 数据的处理函数
	//////////////////////////////////////////////////////////////////////////
	CString ComWordToHex(int Sendvalue);
	
	CString ComDecToHex(int Sendvalue);
	
	// 对字符串进行CRC校验得到两们校验码
	CString AccountCRCCode(CString CommCRC);
	
	// 把十进制数据转换为相应的十六进制字符
	CString NumToHex(int Bnum);
	
	CString ByteToHex(int Onum);
	
	// 把十六进制字符转换为相应的十进制数据
	int TranclateHex(char Ccode);		
//只用于龙门方式压力

	//刷新切割速度显示
	void OnPrepare(int wParam);

//报警信息
	//报警0急停;1X正;2X负3Y正;4Y负;5Z正;6Z负7W正;8W负;9X报警;10Y报警11Z报警;12W报警;13下刀保护
    bool m_bAlarm[14];
	//显示报警
    void ShowAlarm();

	//得到报警信息
	void GetAlarm();
//报警信息

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BENDERDLG_H__7F102487_41BA_4479_A554_9F97BA094865__INCLUDED_)
