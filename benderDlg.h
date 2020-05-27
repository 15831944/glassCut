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

#define MODE_C     3    //�ֶ�
#define MODE_D     4    //����
#define MODE_E     5    //�༭/ͼ��
#define MODE_F     6    //����ɨ��
#define MODE_H     7    //���
#define MODE_A     1    //����У��
#define MODE_MAIN  0    //�Զ�

/* ����С�༭������Ϣ */
#define WM_SMALLEDIT	WM_USER+100
#define WM_3dWnd		WM_USER+101
#define WM_RUNOPTION	WM_USER+102
#define WM_AFFIRM		WM_USER+106
#define WM_INPUT		WM_USER+107	/* �ⲿ������ʱ��������Ϣ */
#define WM_ALMINPUT		WM_USER+108	/* �����ڵ����룬���͵���Ͻ�����ʾ */
#define WM_ALMOUTPUT	WM_USER+109	/* �����ڵ���������͵���Ͻ�����ʾ */

#define WM_SCAN			WM_USER+110	/* ��ɨ�贰�ڷ���Ϣ������ɨ��״̬ */

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
	CDlg_affirm	  *m_pAffirm;/* ��綨λ */
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

	bool    m_bDlgPath; //�ļ�ѡ��Ի���
	bool    m_bShowExtra;
	pShowInf m_pInf;    //СƬ��Ϣ
	int   m_nSafeSwich; //��Ļ
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
	void FileOpen();                              //G��������.
	void GCodeOpen(CString gCode);                //����ת������
	void ResetCS(CString gCode,CString dmcCode);
	void SetManometer(); /* ѹ����ʾ */
	void OnShowLine(); 
	void SetInitAutoSpeed(); /* ���ó�ʼ�Զ�����Ľ����ٶ� */
	void SetAutoRateAdd();   /* �������ʼ� */
	void SetAutoRateSub();   /* �������ʼ� */
	void OnSystemTimer();
	void OnMachineBK();
	long OnProgramBoxG();
	
	void CalculateZoom();//����ȫ����ʾ��Χ
		

	int HardDogCheck();

	void ConvertDxfToGcode();

	void RunTest(int nValue);//����test����Ĺ���

	void DrawBottero();//ˢ��bottero

	//��ʼ��λ����ʾ����
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
	CRect   m_rct;//ʵʱ�켣�ĳߴ�
	CRect   m_rctOrig;//ԭƬ�ĳߴ�
	PDMC	p_stuDmc,pstu_Currdmc;

	SYSTEMTIME		stime_run;	
	double			dTimeA,dTimeB,dTimeC,dTime;
	
	int  m_nTestRun;//�����ڲ���ģʽ
	bool  CheckContinousWork(CString  strWorkName);
	void  OnErnInButton();
	int   OnSetRunState();	/* д����Ƭ̨�ȴ�����λ�� 0д�����1д������*/

	void GetCRRange(double fBaseX,double fBaseY,PDMC pdmc);
	void SetRange(double fx, double fy);
	void OnExit();
	void OnInitGalil();
	void OnInitOCX();
	void OnInitModenessDlg();
	BOOL OnBegoreRunCheck(); /* �������� */
	
	void InitScanPara(); /* ��ʼ��Ѳ�߲��� */
		
	void OnRunWithNoLoad(); /* �������� */
	void OnDirectRun(); /* �������� */		
	void OnRunTimeCount();				/* ��ͼ��ʱ��ͳ�� */
	
	void MachineZeroAlarm(BOOL bLanguage);
	
	//���ܹ�����
	int m_nTimer10;//��ʱ��10����Ĵ���

	int GetHarddogTime(int nFirst);
	void HarddogExit();
	//���ܹ�����
	

    //��ʼ��������ť
	void InitRgnButton();

	//��ʼ������״̬���и�/�����У�run����
	void InitRunState();

	//��ʼ����ʾ��Ϣ
	void InitGridInf();

	//nPreNext:0��ǰ;1���
	//����һ���ļ� 0:û���ҵ�;1:�ҵ���һ��
	int FineFile(int nPreNext);

	/* ע�͹��ܣ�����dmc */
	void WriteOilingDmc();

	//��ȡ��ӡ��ǩ�Ĳ������Ҹ�ֵ��gdmcgc32
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
	void OnCompareBinary(int nBase,int nFirst,int nCecond);//��ͣ��
	void OnCompareInt(int nBase,int nFirst,int nCecond);
	void SendInput(int nBase, int nValue);
	void SendOutput(int nBase, int nValue);
	void OnReadOutput(); /* ����� */

	void OnDisplayOutput(int nCount);	//�Զ��������	

	
	void OnOpenController();//���˶�������
		
	/* ��ʼ���ֶ��µ�ѹ�� */
	void OnInitHandPressure(); 		

	CString			m_strHome;
	CString			m_strDmcAV;
	CString			m_strPressFile;
	CString			m_strBreak;

	BOOL			m_bRunFlag;	

	BOOL            m_bContiueRun;

	BOOL            m_bFile;//FineFile()���ֹ��������ļ�

	BOOL			m_bAffirm;

	bool            m_bNormal;//ͨѶ״̬

	CBrush          m_brush;


/* �����и������ɨ�蹦�� */	
public:
	long  m_nScanTreadID;	
	void  ScanStop();
	void  ScanRun();
	void  ScanSaveGcode();
	void  ScanSavePos(int nFormat);

private:
	
	CScanWork	m_clsScan;
	int   m_nExpandX;//��չ��ʾ��X
	int   m_nExpandY;//��չ��ʾ��Y
    BOOL  m_bExpandShow;//�Ƿ�����չ��ʾ��
    bool  m_bFirstOpen;
	int   m_nOpenLight; // 1:��綨λ�����´�ͼ�� ; 0:ֱ��fileopen��ԭʼͼ��

	bool  m_bEmreStop; //1 ��ͣ����Ҫ���´�ͼ��

    CRITICAL_SECTION m_Section;//�ٽ�������fileopen

	long  m_lTVX;
	long  m_lTVY;
	long  m_lTVZ;

	void OnIniRunVS(long nValue);

	//�õ��Ƿ��ϵ�ػ�е��㣬1�أ�0û�ء�
	int  GetZeroState();

	//��ʼ������λ
	void InitSoftLimit();

	//�õ���չ��ʾ���Ĳ������Ƿ�����չ��ʾ����X Y �ֱ���
    void GetExpandShowInf();

	//��ʾ��չ��ʾ��
	void ShowExpand();

	//������һ��ͼ�ε����ݣ�Ϊ��μӹ�����ʾ��
	void CopyPreShowInf();

	//��ʼ�и����ؼӼ���
	void DownAccDcc();

	//���沣����綨λ�Ժ��ƫ�Ʋ������ϵ������
	void SaveLightPar();
	
	//�õ�������綨λ�Ժ��ƫ�Ʋ������ϵ������
	void GetLightPar();

	//����Ѿ��򿪵�ͼ�κ��и�켣,ɨ��ͱ༭��
	void OnInit2DDrawShow();

	//��ʼ���ٶ���ʾ
	void OnTVShow();

	//����ԭƬ��Ϣ�����ݿ�
	void SaveSheetToMdb();  

	//���ֶ����ļ�ʱ������Ƿ����ļ�����׼���Զ��õ��ӹ�����
	void GetSheetCount();

	//�ӹ���ɺ����Ӽӹ�����������ʾ
	void ModifyProduct();

	//��ʼ�и�ʱ�ѿ�ʼ����ĸ�����Ϊ1
	void SetLabelStart();

	//�ж��ǲ������һƬ�������Ƿ���true
    bool JudgeLastFile();

	//�����
	void DrawRules(CDC *pDC);
//ֻ�������ŷ�ʽѹ��
	//��ʼ������
	void OpenMsCom();
	
	//�رմ���
	void CloseMsCom();
	
	//����ѹ��SendValue:����ѹ��ֵ��SendAddtr:DAͨ��0
	void SetComPress(double SendValue,long SendAddtr=0);
	
	// ���ݵĴ�����
	//////////////////////////////////////////////////////////////////////////
	CString ComWordToHex(int Sendvalue);
	
	CString ComDecToHex(int Sendvalue);
	
	// ���ַ�������CRCУ��õ�����У����
	CString AccountCRCCode(CString CommCRC);
	
	// ��ʮ��������ת��Ϊ��Ӧ��ʮ�������ַ�
	CString NumToHex(int Bnum);
	
	CString ByteToHex(int Onum);
	
	// ��ʮ�������ַ�ת��Ϊ��Ӧ��ʮ��������
	int TranclateHex(char Ccode);		
//ֻ�������ŷ�ʽѹ��

	//ˢ���и��ٶ���ʾ
	void OnPrepare(int wParam);

//������Ϣ
	//����0��ͣ;1X��;2X��3Y��;4Y��;5Z��;6Z��7W��;8W��;9X����;10Y����11Z����;12W����;13�µ�����
    bool m_bAlarm[14];
	//��ʾ����
    void ShowAlarm();

	//�õ�������Ϣ
	void GetAlarm();
//������Ϣ

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BENDERDLG_H__7F102487_41BA_4479_A554_9F97BA094865__INCLUDED_)
