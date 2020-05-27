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
//#define CHAOYANG   //����ע�ͷ�ʽ  
#ifndef POWERLAND
	#define BACKCOLOR               RGB(203,211,237)//�Ի��򱳾���ɫ
#else//ͨ��
	#define BACKCOLOR               RGB(214,226,247)//�Ի��򱳾���ɫ��ǳ(165,198,248)����(146,189,247)
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

//========================================����ÿ�������ж��ٸ�����Ԫ��
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
#define AR_SOFTPASS     5  //������������Ӣ�ĸ���
#define AR_GEIT			11
//=======================================================================


#define WM_SCALE		WM_USER+108/* ��Ӣ�� */

//=============================================����
#define IN_SERVOX_HOME		17	/*���*/
#define IN_SERVOY_HOME		18	/*���*/
#define IN_SERVOZ_HOME		19	/*���*/
#define IN_SERVOW_HOME		20	/*���*/
#define IN_SERVOX_LIMIT		33	/*�ŷ���λ*/
#define IN_SERVOY_LIMIT		34	/*�ŷ���λ*/
#define IN_SERVOZ_LIMIT		35	/*�ŷ���λ*/
#define IN_SERVOW_LIMIT		36	/*�ŷ���λ*/
#define IN_SERVOX_RLIMIT	37	/*����λ*/
#define IN_SERVOY_RLIMIT	38	/*����λ*/
#define IN_SERVOZ_RLIMIT	39	/*����λ*/
#define IN_SERVOW_RLIMIT	40	/*����λ*/

#define IN_EMG_STOP			25	/*��ͣ����*/

#define IN_SERVOX_STATE		29	/*�ŷ�״̬*/
#define IN_SERVOY_STATE		30	/*�ŷ�״̬*/
#define IN_SERVOZ_STATE		31	/*�ŷ�״̬*/
#define IN_SERVOW_STATE		32	/*�ŷ�״̬*/

#define IN_ADDX             41  //X+
#define IN_SUBX             42  //X-
#define IN_ADDY             43  //Y+
#define IN_SUBY             44  //Y-
#define IN_LABEL            45  //��ǩ��Ӧ
#define IN_FANS             46  //����ֶ�����
#define IN_SAFE             47  //��ȫ��դ

#define IN_SERVOX_ALARM		57	/*�ŷ�����*/
#define IN_SERVOY_ALARM		58	
#define IN_SERVOZ_ALARM		59	
#define IN_SERVOW_ALARM		60

//=============================================����㶨��
#define IN_LIGHT			1	/* ��綨λ���� */
#define IN_RUN				3
#define IN_STOP				4
#define IN_BREAK_READY		5	/*��Ƭ̨�����ͣ��������ͨʱ����Ĳ�����������*/
#define IN_FSTSWITCH		6
#define IN_GLASSREADY		7
#define IN_DIEDOWN			8	/* �µ����� */

//=============================================����㶨��
#define OUT_ORIENTATION			1      //��λ�� 
#define OUT_CUT_OILING			2	   //�и���
#define OUT_BEGINSEND			3      //����Ƭ̨�źţ���ʼ���Ͳ���
#define OUT_WIND_RELAY			4      //�����ͣ
#define OUT_OILING				5      //עú��
#define OUT_SENDUPDN			6      //���ʹ�����
#define OUT_TRANSDUCER_FORWARD	7      //��Ƶ������
#define OUT_TRANSDUCER_REVERSE	8      //��Ƶ������
//��Ϊ�м����ʹ��
#define OUT_ZAXIS_DN			31      //c���µ�
#define OUT_ZAXIS_DN1			18      //c���µ�
#define OUT_TRANSDUCER_SPEED	25      //��������
#define OUT_TRANSDUCER_SPEED1	17      //��������
#define OUT_LED_RUN				19      //����
#define OUT_LED_STOP			20      //ֹͣ
//21����ǩ���ڿ���д��
//=======================================================================


//���ܹ���д��ַ��ƫ����
#define USER_SECRET1              0  //��������Ա
#define USER_SECRET2             20  //����Ա1
#define USER_SECRET3             40  //����Ա2
#define TIME_YEAR                60  //����ʱ��
#define TIME_MONTH               80  //����ʱ��
#define TIME_DAY                100  //����ʱ��
#define TIME_SECRET             120  //���ܵ�����
#define TIME_VENDER             140 //���ܵĳ��Һ�
#define CONTROLVER              160 //��������
//�����ӵ����ݱ�����ļ���
//1:��Ƭ̨׼��ʱ�䣨s��
//2:���Բ���뾶
#define INIFILE_ADDEXTRA           "D:\\program files\\GlassCutter\\AddExtra.ini"

#define INIFILE_LASTINF            "D:\\program files\\GlassCutter\\LastInfor.ini"

#define	INIFILE_SCAN               "D:\\program files\\GlassCutter\\Scan.ini"

/////////////////////////////////////////////////////////////////////////////
// CBenderApp:
// See bender.cpp for the implementation of this class
struct tagScanPARA
{	
	double				dScanPace;			/* ɨ�貽�� */
	double				dScanSpeed;			/* �Զ�ɨ���ٶ� */
	double			    dScanBeginPosX;		/* ɨ����ʼ��X */
	double			    dScanBeginPosY;		/* ɨ����ʼ��Y */
	double			    dScanCenterPosX;	/* ɨ���е�X */
	double			    dScanCenterPosY;	/* ɨ���е�Y */
}; 
typedef struct tagPARA SCANPARA, *PSCANPARA;
extern int			g_ndisknum;
extern CString		g_strdiskname[10];
//======�˶�������������
extern  tagScanPARA	 g_ScanPara;
extern  CAlarmDll	g_AlarmDll;
extern  CSystemDll   g_systemdll;
extern  CMachineDll  g_machinedll;
extern  CHandDll     g_handdll;
extern  CCuttingPress    g_CutPress;
extern  CDmcgc       g_Dmcgc;        //CDmcgc��
extern  CDMCWin      g_Controller; //CDMCWin��
extern  PSYS         g_stu_pSysA, g_stu_pSysB, g_stu_pSysC, g_stu_pSysD, g_stu_pSysE;
extern	PCONTROLLER	 g_pstu_control;
extern  PAXIS        g_stu_pAxisA,g_stu_pAxisB,g_stu_pAxisC,g_stu_pAxisD;
extern  PAXIS        g_stu_pAxisE,g_stu_pAxisF,g_stu_pAxisG,g_stu_pAxisH;     /* ��е�������������ļ��� */
extern  long         g_lRc;
extern  USHORT       g_nController;
extern  char         g_szResponse[80];
extern  float        g_fCurrMachineX;
extern  float        g_fCurrMachineY;
extern  float        g_fCurrMachineZ;
//======DMC�ļ���G�����ļ�������
extern  CString      g_strDmcfile,g_strGfile,g_strDxffile;
extern  CString      g_arr_strGline[5110];
extern  CString      g_strShowName;         //���ļ�������pathtwo�е�listʹ�á�
extern  CString      g_strSavefile;         //�����ļ�������dlg_save����ʹ��

//======���嵱�����Զ��ٶȡ��ֶ��ٶȡ��Ӽ��ٵı�����
extern  int  	     g_iMode;   //BUTTON WINDOW������ʾ���
extern  int	         g_iStep;   //��������ʱ�������м�����


//======����ʹ����
extern  CPoint       g_screen;
extern  POINT2D      g_dScale;
extern  CFont        g_fontButton,g_fontStatic,g_fontEdit,g_fontList,g_fontKey,g_fontRP;
extern 	CString      g_strOriginalPathC;		//��װĿ¼���������Ŀ¼��
extern 	CString      g_strOriginalPathD;		//��װĿ¼���������Ŀ¼��
extern 	COLORREF     g_crFontA;					//������ɫ����
extern 	COLORREF     g_crFontC;					//������ɫ����
extern 	COLORREF     g_crFontD;					//������ɫ����
extern  int          g_iIsDxf;					//0�������ļ���1��DXF��2��G���룻
extern  int          g_iPassgrade;				//Ȩ�޼���
extern  int          g_iLanguage;	

extern  CString      g_arr_strBender[AR_BENDER][5],g_arr_strCnc[AR_CNC][5],g_arr_strGalil[AR_GALIL][5],g_arr_strHand[AR_HAND][5],g_arr_strMachine[AR_MACHINE][5],g_arr_strManager[AR_MANAGER][5];
extern  CString      g_arr_strLimit[1][6],g_arr_strMotion[AR_MOTION][5],g_arr_strPass[AR_PASS][5],g_arr_strPath2[AR_PATH2][5],g_arr_strSave[AR_SAVE][5],g_arr_strState[AR_STATE][5];
extern  CString      g_arr_strSuper[AR_SUPER][5];
extern  CString      g_arr_drawcad[AR_DRAWCAD][5];
extern  CString		 g_arr_glass[AR_GLASS][5];
extern  CString		 g_arr_light[AR_LIGHT][5];
extern  CString	     g_arr_lightpos[AR_LIGHTPOS][5];
extern  CString	     g_arr_message[AR_MESSAGE][5];
extern	CString		g_strGraphLib[AR_GRAPHLIB][4];			//ͼ�����
extern	CString		g_strNester[AR_NESTER][4];				//���Ͻ���
extern	CString		g_strNestPara[AR_NESTPARA][4];			//���ϲ�������
extern	CString		g_strPartPara[AR_PARTPARA][4];			//ͼ���������
extern	CString		g_strConfig[AR_CONFIG][4];
extern	CString		g_strLoading[AR_LOADING][4];
extern	CString		g_strFathom[AR_FATHOM][4];
extern	CString		g_strCuttingSize[AR_CUTSIZE][4];
extern	CString		g_strBottero[AR_BOTTERO][4];
extern	CString		g_strOiling[AR_OILING][4];
extern  UINT        g_nProduct;//�ܵļӹ�����
extern  POINT2D		pCoor,pCoorx,pCoory;

extern unsigned char vendorCode[];
extern TRACK       g_ExtraShow;          //��չ��ʾͼ�����ݽṹ
extern pShowInf     g_pShowSmall;          //��չ��ʾԭƬ
extern Cdlg_ShowExtra *     g_pDlgShowExtra; //��չ��ʾ�Ի���
extern double g_dExtraX;                       //��һ����ʾ��x�ߴ�
extern double g_dExtraY;                       //��һ����ʾ��y�ߴ�
extern int g_nTestRun ;//�����ڲ���ģʽ
extern SYSTEMTIME g_stCurrTime;//��ǰ���ܹ�ʱ��
extern int       diskcheck1[10];
extern CString   diskname1[10];
extern int g_nRunState;  //����״̬0�и1�����У�
extern CString g_strExtraFile;//��һ��ͼ�ε��ļ���
extern int g_nGlassNo; //���鲣�� 0��Ƭ��1�п� 2��Ƭ
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
	BOOL			bIsLine;			/* ֱ��ΪTRUE��Բ��ΪFALSE */
	BOOL			bDirect;			/* Բ����˳ʱ��T������ʱ��F��ֱ�ߣ��Ƿ񱻺ϲ�,TRUE �ϲ� */
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
	int             nDraw;          //1��
	int             nNum;           //���к�
	CRect           rect;           //����
	tagRectDraw		*Next;
}; 
typedef struct tagRectDraw RectDraw, *pRectDraw;

struct tagBotteroCommand
{
	int					nIndex;			/* ������� */
	char				chCom;			/* �����ַ� */  
	int					nMultiple;		/* �˷�����ֵ��Ĭ��Ϊ1��0 */
	float				nValue;			/* ������ֵ */
	char				chName[50];		/* ��������Σ��������� */
	float				fTotalDis;		/* �������õ����ܳ��� */
	int                 nDraw;          //����
	pRectDraw           pRect;          //�����Ӧ�Ļ����ε�����
	pSegment			pStuSegment;    
	tagBotteroCommand	*Prev;
	tagBotteroCommand	*Next;
}; 
typedef struct tagBotteroCommand stuBotteroCommand, *p_Command;

struct tagBottero
{
	long				lMaterialX;			/* ԭƬ�ߴ�X */
	long				lMaterialY;			/* ԭƬ�ߴ�Y */   
	long				lModifyX;			/* �ޱ߳ߴ�X */
	long				lModifyY;			/* �ޱ߳ߴ�Y */   
	float				fTop;
	float				fBottom;
	float				fLeft;
	float				fRight;
	tagBotteroCommand	*BtroComm;
}; 
typedef struct tagBottero stuBottero, *p_stuBottero;

struct tagSheetGlass
{
	CString         strRect;//������
	COleDateTime    timeCut;  //�и�ʱ��
	int             nNum;     //����
};
typedef struct tagSheetGlass stuSheetGlass, *p_stuSheetGlass;
struct tagRectEdit
{
	int  nIndex;    //��Ŵ�1��ʼ
	POINT2D dpStart;//����xy����
	POINT2D dpRect; //xy�ĳ���
	int nNumX;      //����
	int nNumY;      //����
	char szGraph[4000];//��������
	POINT2D dpTrim;  //�ޱ�
	tagRectEdit *Prev;
	tagRectEdit	*Next;
};
typedef struct tagRectEdit stuRectEdit, *p_stuRectEdit;


//*************************ʵ��ȫ�ֺ�����
void OnReSetFont();
CRect OnReSetRectV(CRect rc);
void OnCheckPassword(int nFirst);    /* Ȩ����֤ */
double PointToPointAngle(double dBcx,double dBcy,double dEcx,double dEcy);
int OnShowMessageBox(int index,int nLanguage,BOOL iTitle);                //�����ݿ��е�����Ϣ
int OnShowMessageBox(int index,int nLanguage);                //�����ݿ��е�����Ϣ
void OnSoftLimit(double fx,double fy,double bx,double by); /* ����λ����FLBL */
double SaveNPoint(int n, double dVar); /* ����4λС�� */
CPoint ReadMaxSpeed();
 
//���ع�綨λ�ٶȲ���
void SetFindLightSpeed();
int HasWriteValue(CString strValue,hasp_size_t offset);

int HasReadValue(CString &strValue, hasp_size_t offset);

/* �ļ����ļ��еĿ��� */
void CopyDirectory(CString sorPath, CString aimPath);

/* ɾ���ļ��� */
void DeleteDirectory(CString strPath);

CString movediskdir();

int OnIsDisk();                                //�Ƿ����Ƶ�Ӳ��

void GetBitMapRgn(CDC *pDC, HRGN &c,int nID);

void SetCtlFont(CWnd *pWnd);

//�õ��ŷ�����״̬
//1�б�����0û�б���
int  GetServerAlarm();

//GraphDlg
void CreateDC(CDC *pMemDC, CDC *pSrcDC, int width, int height);
void ConvertGraphCoordinate(CDC *pDC);
void ReplaceColor(CDC *pDC, const COLORREF crOld1, const COLORREF crOld2, const COLORREF crNew);
char* GetExePath();
//streamIn�����ļ���streamOut���ܵ��ļ�
void Secret(CString streamIn,CString streamOut);

//ɾ�����ݿ���ʱ�ļ�������в���
void DeleFileLdb();
//****************************************************************************
/*
#define OnShowMessageBox(index,nLanguage)    MessageBox(g_arr_message[index][1],g_arr_message[1][nLanguage],MB_OK);             //�����ݿ��е�����Ϣ
*/
#include "Dlg_Nest.h"

//extern CString g_strSavefile;
extern CString g_strGCodePath;
extern int kind;		//�洢ͼ����һ������˼���ͼ��
extern int sqr[200];		//�洢ÿ����ӵ��������
extern int sqrm[200];		//�洢ÿ����ӵ��������
extern CDlg_Nest m_NestDlg;
extern int g_nRemainderX;//bottero��
extern int g_nRemainderY;//bottero��
extern stuBottero	stuBtro;//bottero��
class CBenderApp : public CWinApp
{
public:
	CBenderApp();
	void ShutDown();
private:
	void GetCurrentDisplayProp(); //��ʾ���ķֱ���
	void OnReSetFont();
	void OnRegSvr32();   
	BOOL OnEWFa();                  //��XPE�е�д����
	BOOL OnEWFb();                  //��XPE�е�д����
	void OnReBoot();                //��XPE�е�д����
	int OnEWF();                   //��XPE�е�д����
	
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
