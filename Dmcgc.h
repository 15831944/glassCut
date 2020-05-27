// Dmcgc.h: interface for the CDmcgc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMCGC_H__C74A9F7D_4E5A_4492_A09C_CA3211DD3C34__INCLUDED_)
#define AFX_DMCGC_H__C74A9F7D_4E5A_4492_A09C_CA3211DD3C34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Dmcwin.h"	/* 控制器 */
#ifndef min
   #define min(x,y) ((((x)<(y))?(x):(y)))
#endif
#define MIN min

#ifndef max
   #define max(x,y) ((((x)>(y))?(x):(y)))
#endif
#define MAX max

/* 定义与主窗口交换信息 */
#define WM_DMCGC		WM_USER+199	/* 主窗口的输出，发送到诊断进行显示 */

/* Test pointer, return integer */
#define ASSERTI(p) if(!p)return(ERROR_NULLARGUMENT)
/* Test pointer, return NULL */
#define ASSERTP(p) if(!p)return(NULL)

/* Used to determine file I/O buffer size */
#define  LINE_SIZE   128

#define  DMC_LINE_SIZE 80

#define  IN_TO_MM    ((double)25.4)
#define  MM_TO_IN    ((double).03937)

/* Non-fatal return codes */
#define  RC_NOERROR                 0
#define  RC_REUSEBLOCK              1
#define  RC_ENDPROGRAM              2


#define  ERROR_FILENOTOPEN          -2
#define  ERROR_MEMORY               -5
#define  ERROR_TOKENERROR           -6
#define  ERROR_CODENOTFOUND         -8
#define  ERROR_INVALIDPROPERTY      -9
#define  ERROR_INVALIDVALUE         -10
#define  ERROR_NULLARGUMENT         -12
#define  ERROR_INVALIDCOMMANDTYPE   -13
#define  ERROR_ARCINVALID           -14
#define  ERROR_LINEINVALID          -15  

/* Definitions used for current block structure */
#define  COMMAND_INDEPENDENT           0                                        
#define  COMMAND_MOTION_ARC            1
#define  COMMAND_MOTION_LINE           2
#define  COMMAND_IN                    17
#define  COMMAND_MM                    18


#define  DIRECTION_CW                  0
#define  DIRECTION_CCW                 1

/* Definitions used for current state structure */

#define  POSITION_ABSOLUTE 0
#define  POSITION_RELATIVE 1

#define  SCALE_IN          1
#define  SCALE_MM          0

#define  PLANE_XY          0


#ifndef  M_PI
#define  M_PI     acos(-1)
#endif

//====================================================
/* 定义坐标系 */
struct tagCOORDINATE
{
	double     X;
	double     Y;
	double     Z;	
}; 
typedef struct tagCOORDINATE COORDINATE, *PCOORDINATE;

/* This structure keeps track of the current G or M code program line */
typedef struct tagLINEINFO
{
	unsigned long  usLineNumber;
	char           szLine[LINE_SIZE];
} LINEINFO, * PLINEINFO;

/* This structure defines a command block */
struct tagBLOCK
{
	unsigned char  chPrefix;			/* 'G' or 'M' */
	unsigned short usCode;				/* Numeric code */
	unsigned short usCommandType;
	void           *pMotionSegment;		/* ARC, LINE */
	unsigned long  usBlockNumber;
	unsigned long  usLineNumber;
	char           szLine[DMC_LINE_SIZE];
	char		   chRotateFlag;		/* CNC文件，双向切割时是否转刀 */
	long           usIndex;				/* Numeric code */
	struct tagBLOCK  *Next;				/* Next block */
	struct tagBLOCK  *Prev;				/* Previous block */   
}; 
typedef struct tagBLOCK BLOCK, *PBLOCK;

/* This structure defines the translation table schema */
typedef struct tagTRANSTABLE
{
	unsigned char  chPrefix;         /* 'G' or 'M' */
	unsigned short usCode;           /* Numeric code */
	unsigned short usCommandType;   
	char szDMC[DMC_LINE_SIZE];       /* The corresponding DMC command(s) */
} TRANSTABLE, * PTRANSTABLE;


/* This structure defines a cicular arc segment (part of a command block) */
typedef struct tagARC
{
	unsigned char  chScale;              /* 0 = inches, 1 = millimeters */
	unsigned char  chPlane;   
	unsigned char  chPosition;           /* 0 = relative, 1 = absolute */   
	unsigned char  chDirection;          /* 0 = CW, 1 = CCW */   
	COORDINATE     fBegin;
	COORDINATE     fEnd;
	double         fCenterI;             
	double         fCenterJ;
	double         fRadius;               //单位mm
	double         fBeginAngle;
	double         fEndAngle;
	double         fTraverseAngle;
	double         fFeed;                 //加工速度MM/S
} ARC, * PARC;

/* This structure defines a linear segment (part of a command block) */
typedef struct tagLINE
{
	unsigned char  chScale;              /* 0 = inches, 1 = millimeters */
	unsigned char  chPlane;
	unsigned char  chPosition;           /* 0 = relative, 1 = absolute */   
	COORDINATE     fBegin;
	COORDINATE     fEnd;
	double         fFeed;                //加工速度MM/S
} LINE, * PLINE;

/* This structure defines the current state */
typedef struct tagCURRENTSTATE
{
   unsigned short  usAxes;                     /* Number of axes specified at start-up */
   unsigned char   chPosition;                 /* 0 = relative, 1 = absolute */
   unsigned char   chScale;                    /* 0 = inches, 1 = millimeters */
   unsigned char   chPlane;                    /* 0 = XY, 1 = ZX, 2 = XY */
   unsigned char   chCurrentGCode;
   unsigned char   chSegmentOpen;              /* Has a motion segment been started? */
   unsigned char   chVMMode;
   COORDINATE      fResolution;
   double          fAcceleration;
   double          fDeceleration;   
   double          fRapidMoveSpeed;            //定位速度
   double          fFeedRate;                  //插补速度
   double          fMinCornerSpeed;            /* Min. speed for corners */
   double          fMinArcSpeed;               /* Min. speed for arcs with a radius < fMinArcRadius */
   double          fMinArcRadius;              /* Arcs with a radius below this value are subject to fArcMinSpeed */
   COORDINATE      fMachinePos;                /* Absolute machine position */
   COORDINATE      fCurrentPos;                /* Current working position */
   COORDINATE      fOffsetG92;                 /* Offset defined by G92 */
   COORDINATE      fOriginForVM;               /* Position defined by start of VM */
   double          fTangentAxisZeroAngle;
   double          fArc2LineIncrement;         /* For arc to line conversion */
   unsigned short  usLineSize;                 /* For record-oriented G code files */
   unsigned short  usCornerAngle;
   unsigned short  usMaxCornerAngle;   
   unsigned short  usSegmentCounter;
   BLOCK           *pBlocks;
   unsigned long   usAllocatedBlocks;
   TRANSTABLE      *pTransTable;
   unsigned short  usTransTableRecords;   
   LINEINFO        LineInfo;                   /* For diagnostics, error reporting */
   char            *pAVAction;
   double          lSpare1;
   double          lSpare2;
} CURRENTSTATE,  *PCURRENTSTATE;

CURRENTSTATE CurrentState;

/* 自动库转入 */
//====================================================
#define  LONG_COMMAND               40     /* 双字符命令长度 */
#define  LONG_LINE                  80     /* 命令行长度 */


struct tag2DPoint
{
	double x;
	double y;
}; 
typedef struct tag2DPoint Point2D,*pPoint2D;

//显示小片信息
struct tagSmallInf
{
	int nSizeX;             //代表这个小片X方向尺寸
	int nSizeY;             //代表这个小片Y方向尺寸
	int nOX;            //代表这个小片左下角X坐标
	int nOY;            //代表这个小片左下角Y坐标
	CString strSizeX;   //代表显示的X值
	CString strSizeY;   //代表显示的Y值
	CString strName;	//代表这个小片的客户名
	CString strNum;     //代表定位号
	CString strShelf;   //代表货架,如果是余片显示*
	tagSmallInf *pNext;	
};
typedef struct tagSmallInf SmallInf,*pSmallInf;

//显示原片信息包括小片信息
struct tagShowInf
{
	int nX;                 //原片X方向尺寸
    int nY;                 //原片Y方向尺寸
    int nCutX1;             //代表原片X1修边
	int nCutY1;	            //代表原片Y1修边
	int nCutX2;	            //代表原片X2修边
	int nCutY2;             //代表原片Y2修边
	int nCount;             //代表原片数量
	int nVersions;	        //代表当前版号
	int nCurrentVersions;	//代表总版号
	CString strStuff;       //代表材料
	CString strStorage;	    //代表这个原片的货架号
	tagSmallInf   *pShowSmall;//小片信息
};
typedef struct tagShowInf ShowInf,*pShowInf;

/* 执行上片过程 */
UINT SendLoadGlass(LPVOID pParam);//

/* 测厚执行函数 */
UINT SendThickness(LPVOID pParam);//
/* 启动后执行函数 */
UINT SendCommand(LPVOID pParam);//

//掉电恢复继续加工
UINT SendCommandContinue(LPVOID pParam);//

/* 上片台准备等待 */
UINT SendTurnOver(LPVOID pParam);//

/* 手动里贴标签 */
UINT SendHandLabel(LPVOID pParam);//

struct tagDMC
{
	long           number;                          /* 行号，行数（G代码） */
	char           command[LONG_COMMAND];           /* DMC 命令类型 */
	char           comG;                            /* 命令类型 G 或 M */
	int            comGNo;                          /* G 或 M 的序号 */
	char           szLine[LONG_LINE];               /* 转换出来的DMC命令行 */
	char           szLineG[LONG_LINE];              /* 原始的G代码的命令行 */
	char           chVM;                            /* 是否有  VM  命令 */
	char           chVE;                            /* 是否有  VE  命令 */
	char           szVector[LONG_COMMAND];          /* VM  命令的内容 */
	char           szVTEnd[LONG_COMMAND];           /* VE  命令的内容 */
	char           szVTAMS[LONG_COMMAND];           /* AM  命令的内容 */
	char           chPosType;                       /* 位置类型 相对或绝对 */
	char           chVMOpen;                        /* 插补是否已打开 */
	char           chVMMode;                        /* 插补模式 LM 或 VM */
	char           chPlane;                         /* 平面 ：0 = XY, 1 = ZX, 2 = XY */
	char		   chRotateFlag;					/* CNC文件，双向切割时是否转刀 */
	COORDINATE     usComPos;                        /* 程序X 值 */   
	COORDINATE     usProPos;                        /* 程序X 位置 */   
	COORDINATE     usOrigin;                        /* 矢量X 原点位置 */   
	double         usRadius;                        /* 半径 单位脉冲*/
	double         usBAngle;                        /* 圆弧起始角度 */   
	double         usEAngle;                        /* 夹角，正为 逆ubt时针，负为顺时针*/
	double         dPress;                          /* 切割压力值，由读进的参数计算 */
	double         fVectorLenth;					/* 每段的矢量长度mm */
	double         fVectorTotal;					/* 总的矢量长度mm */
	double         dStartSpeed;                     //起始速度 mm/s
	double         dEndSpeed;                       //终止速度 mm/s
	double         dStartAngle;                     //起始角度[0-360）
	double         dEndAngle;                       //圆弧终止角度
	struct  tagDMC *Next;                           /* Next block */
	struct  tagDMC *Prev;                           /* Previous block */
}; 
typedef struct tagDMC DMC, *PDMC;

extern CDMCWin *    m_pController;
extern long        a_rc;
extern long        auto_runline;                    
extern long        auto_runflag;                    
extern long        auto_pauseflag;                  
extern PDMC        pfirstDmc;
extern PDMC        pcurrDmc;                        /* DMC结构指针,pbackDmc用于回退功能 */
extern DMC         currDmc;                         /* DMC结构 */
extern PDMC        pbackDmc;                        /* DMC结构指针,pbackDmc用于回退功能 */
extern PDMC        pcurrRunDmc;                     /* DMC结构指针,pcurrRunDmc用于当前运行DMC结构功能 */
extern CString     strVM;
/* 玻璃切割中，压力相关参数 */
extern double		g_dPress[12];		/* 加压，起点压，直线、圆弧正常压 */
extern long			g_iTimer[5];		/* 直线加压时间，圆弧加压时间,下刀延迟时间,抬刀延迟时间*/
extern double		g_dRadius[2];		/* 两个半径，分圆弧三段压力 */
extern int          iRunOption;			/* 切割-演示 */

extern int          iRunKnife;          //注油
extern long			iDelayTime;			/* 切割时的下刀延迟 */
extern int          iCncRotate;			/* CNC文件，双向切割时是否转刀 */
extern double		dCenterX,dCenterY;	/* 刀具偏心值 */
extern double		dGlassKnifeRadius,dGlassKnifeAngle;		/* 偏心半径与0度时的偏心角度 */
extern Point2D		g_px,g_po,g_py;		/* 玻璃放置位置 */
extern double		g_dGlassAngle;		/* 玻璃偏置角度 */
/* 玻璃切割中，压力相关参数 */
extern int          g_nCutMode;         //1切割
extern bool         g_bDoubleXW;        //龙门
struct CMotionAVInfo 
{
	char	FileAV[100];
	double	dAVOpen;
	double  dAVClose;
};
class CDmcgc;
struct CDownloadThreadInfo 
{
	char			file1[100];//dmc上片
	int             iReadyTime;
	Point2D			fBegin;			/* 整个循环体的起点 */
	Point2D			fEnd;			/* 整个循环体的终点 */
	CMotionAVInfo	Oiling;			/* 注油功能，要在运动中开关阀 */
	int				nServoControl;	/* 伺服控制方式 */
	BOOL			bLoadGlass;		/* 是否需要上片 */
	CWnd			*pWnd;
	double          dFeed;           //切割单轴运动时速度。
	double          dFeedAcc;        //切割单轴运动时加速度。
	double          dFeedDec;        //切割单轴运动时减速度。
	double          dLocationAcc;           //定位运动时加速度。
	double          dLocationDcc;           //定位运动时减速度。
	double          dInterpolationAcc;        //插补运动时加速度。
	double          dInterpolationDec;        //插补运动时减速度。
	int             nErrorAngle;              //单轴速度和插补速度的区别角度
	int             nOffset;
	int             nLabel;           //1打印标签
	BOOL            bSolidHead;       //1实心刀头，正反刀切割
	CDmcgc*         pDmcgc;           //主类          
};

long CheckArc(double x0,double y0,double r,double sd,double sendd,double tpx,double tpy); 
double PointAngleTo(double dBcx,double dBcy,double dEcx,double dEcy);
long CheckLine(double x0,double y0,double x1,double y1,double tpx,double tpy); /* 起点，终点，暂停点 */
int WaitingMotionComplete(CString str);				/* 等待运动完成 */
void RunAvOption(double dAvOn, double dAvOff, double dTotal);	/* 下载AV数值 */
/* 命令执行 */
int RunCommand(CString strRunComm);
void WaitingTimeComplete(CString str);              /* 等待时间到达 */
void WaitingPressTimeBgsComplete(CWnd *pCwnd,double dPress,long addTime); /* 等待压力到达;加压延时addPress */
int WaitingXQMotionComplete();
int Round(double dValue);//四舍五入

//================================================================
class AFX_EXT_CLASS CRunCommand : public CObject
{
public:
	CRunCommand();
	virtual ~CRunCommand();
	
	/* 命令执行 */
	int RunCommand(CString strRunComm);
	
	/* 命令执行 */
	float RunCommandfloat(CString strRunComm);
	
	/* 走到某个位置命令 */
	void RunGotoPosCommand(double dDisX, double dDisY, double dDisZ, double dSpeed, double dAcc, double dDec);
	
	/* 走到某个位置命令 */
	void RunGotoPosCommand(double dDisX, double dDisY, double dSpeed, double dAcc, double dDec);
	
	/* Z轴走到某个位置命令 */
	void RunGotoZPosCommand(double dDisZ, double dDelaysupply, double dSpeed, double dAcc, double dDec);
	
	PDMC GetBehindG00(PDMC pRunDmc); /* 保留4位小数 */		
	
};
//================================================================
//====================================================
class AFX_EXT_CLASS CDmcgc : public CObject
{
public:
	CDmcgc();
	virtual ~CDmcgc();
public:
	CDownloadThreadInfo m_DownloadThreadInfo;
	CString   strDMC;
/* ---------------------------------------------------------------------------------
   ResetCurrentState
   Reset the CURRENTSTATE structure to its original or default state
   char*             pszSetupFileName  : if not NULL, reload the set-up file
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int ResetCurrentState(char * pszSetupFileName);

/* ---------------------------------------------------------------------------------
   Translate G codes to DMC commands from a G code file
   char*             pszGCodeFileName  : G code file name
   char*             pszDMCFileName    : DMC commands file name
   short             chAppendDMCFile   : append or replace DMC commands file
   returns RC_NOERROR if successful, < 0 if unsucessful 
   主程序调用
   --------------------------------------------------------------------------------- */
int GCodes2DMCs(char * pszGCodeFileName, char * pszDMCFileName);

   
/* ---------------------------------------------------------------------------------
   Translate all G codes to blocks from a G code file
   FILE*             fileGCode         : file pointer to G code file
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int GCodes2Blocks(FILE * fileGCode);

/* ---------------------------------------------------------------------------------
   One G code to one block using buffered translation
   char*             pszGCode          : pointer to null-terminated string containing G code
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int GCode2Block(char * pszGCode);

/* ---------------------------------------------------------------------------------
   Translate all blocks to DMC commands
   FILE*             fileDMC           : pointer to DMC commands file
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int Blocks2DMCs();

/* ---------------------------------------------------------------------------------
   Read the translation table into memory
   char*             pszTransTableFileName   : translation table file name
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int ReadTranslationTable(char * pszTransTableFileName);

/* ---------------------------------------------------------------------------------
   Parse a translation table record
   char*             pszBuffer         : pointer to null-terminated string containing
                                         translation table record
   PTRANSTABLE       pTransTable       : pointer to TRANSTABLE structure (output)
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int ParseTransTableRecord(char * pszBuffer, PTRANSTABLE pTransTable);

/* ---------------------------------------------------------------------------------
   Parse a G code - this is the main G code parsing routine
   char*             pszBuffer         : pointer to null-terminated string containing G code
   PBLOCK            pBlock            : pointer to BLOCK structure (output)
   returns RC_NOERROR or RC_REUSEBLOCK if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int ParseGCode(char * pszBuffer, BLOCK * pBlock);

/* ---------------------------------------------------------------------------------
   ScanLine
   Scan a line for a G or M code
   char*             pszBuffer         : pointer to null-terminated string containing G code
   unsigned short*   pusCharacters     : starting position of next G or M code in the
                                         buffer (output)
   returns 1 if found, 0 if not found  
   --------------------------------------------------------------------------------- */
int ScanLine(char * pszBuffer, unsigned short * pusCharacters);


/* ---------------------------------------------------------------------------------
   RemoveComments
   Remove comments from a line in a G code file
   char*             pszBuffer         : pointer to null-terminated string containing G code
   returns nothing  
   --------------------------------------------------------------------------------- */
void RemoveComments(char * pszBuffer);

/* ---------------------------------------------------------------------------------
   Get the next token in the buffer
   Note: this function will modify the input buffer
   char*             pszBuffer         : pointer to buffer
   int*              psOffset          : offset of start of token scan (output)
   returns pointer to token if successful, NULL if unsucessful  
   --------------------------------------------------------------------------------- */
char * GetNextToken(char * pszBuffer, int * psOffset);                           

/* ---------------------------------------------------------------------------------
   Get a floating-point number from a buffer marked by a character token
   char*             pszBuffer         : pointer to buffer
   char              chToken           : character token
   double*           pFloat            : floating-point number returned (output)
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int GetFloatTokenFromChar(char * pszBuffer, char chToken, double * pFloat);

/* ---------------------------------------------------------------------------------
   Returns the index of the DMC command for a given G or M code
   unsigned char     chPrefix       : prefix of code ('G' or 'M')
   unsigned short    usCode         : numeric code
   returns >= 0 if successful, -1 if unsucessful  
   --------------------------------------------------------------------------------- */
int GetTransTableIndex(unsigned char chPrefix, unsigned short usCode);

/* ---------------------------------------------------------------------------------
   Block to DMC translation
   FILE*             fileDMC           : pointer to DMC commands file
   PBLOCK            pBlock            : pointer to BLOCK structure
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int Block2DMC(PBLOCK pBlock);

/* ---------------------------------------------------------------------------------
   Begin a series of motion segments
   FILE*             fileDMC           : pointer to DMC commands file
   PBLOCK            pBlock            : pointer to BLOCK structure
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int BeginDMCSegment(PBLOCK pBlock);

/* ---------------------------------------------------------------------------------
   End a series of motion segments
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int EndDMCSegment();

/* ---------------------------------------------------------------------------------
   Calculate arc motion segment attributes
   PARC              pArc              : pointer to ARC structure (output)
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int CalculateArcAttributes(PARC pArc);

/* ---------------------------------------------------------------------------------
   Calculate line motion segment attributes
   PLINE             pLine             : pointer to LINE structure (output)
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int CalculateLineAttributes(PLINE pLine,PBLOCK pBlock);

/* ---------------------------------------------------------------------------------
   Allocate and create an arc motion segment
   char*             pszBuffer         : pointer to input line
   PBLOCK            pBlock            : pointer to BLOCK structure
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int CreateArc(char * pszBuffer, BLOCK * pBlock);

/* ---------------------------------------------------------------------------------
   Construct a DMC command for an arc motion segment
   PBLOCK            pBlock            : pointer to BLOCK structure
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int ConstructArc(PBLOCK pBlock);


/* ---------------------------------------------------------------------------------
   Allocate and create a DMC command for a line motion segment
   char             *pszBuffer         : pointer to input line
   PBLOCK            pBlock            : pointer to BLOCK structure
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int CreateLine(char * pszBuffer, BLOCK * pBlock);

/* ---------------------------------------------------------------------------------
   Construct a DMC command for a line motion segment
   PBLOCK            pBlock            : pointer to BLOCK structure
   returns RC_NOERROR if successful, < 0 if unsucessful  
   --------------------------------------------------------------------------------- */
int ConstructLine(PBLOCK pBlock);


/* ---------------------------------------------------------------------------------
   Build motion segments from raw data stored in blocks
   returns 1 if subroutines found, 0 if not found 
   附直线圆弧的数据
   --------------------------------------------------------------------------------- */
int BuildMotionSegments(void);

/* ---------------------------------------------------------------------------------
   Calculate the traverse angle of an arc segment   
   PARC              pArc              : pointer to ARC structure
   returns traverse angle    
   --------------------------------------------------------------------------------- */
double CalculateTraverseAngle(ARC * pArc);   

/* ---------------------------------------------------------------------------------
   Get a potiner the global CURRENTSTATE structure
   returns PCURRENTSTATE   
   --------------------------------------------------------------------------------- */
CURRENTSTATE * GetCurrentStatePtr(void);  

void  *DMC_FALLOC(unsigned int usSize);
void  DMC_FFREE(void * pObject);

/* Linked list functions */
BLOCK  *AddBlock();
BLOCK  *InsertBlockAfter(PBLOCK pInsertAfter);
BLOCK  *InsertBlockBefore(PBLOCK pInsertBefore);
void   FreeBlocks(void);
/* Calculate the angle between points */
double  PointAngleTo(pPoint2D pPoint1, pPoint2D pPoint2);
int		CheckCornerAngle(PBLOCK pBlockHead);//角度大于最大拐角角度增加抬刀过程
double	Block2BlockAngles(PBLOCK pBlock1, PBLOCK pBlock2);
double	LineIncomingAngle(PLINE pLine);
double	LineOutgoingAngle(PLINE pLine);
double	ArcIncomingAngle(PARC pArc);
double	ArcOutgoingAngle(PARC pArc);
int  AddUpperBlock(PBLOCK pBlock1);//增加抬刀


//切割单轴运动时速度,加速度，减速度
void  SetFeedMotion(double dSpeed,double dAcc,double dDec);

//插补运动时加速度，减速度
void  SetInterpolation(double dAcc,double dDec);

//定位运动时加减速度
void  SetLocationMotion(double dSpeedX,double dSpeedY);

//设置圆弧最大半径
void SetMaxRadius(double dValue);

//设置控制器指针
void SetController(long lController);

/* 自动库转入 */
//======================================================================
protected:
	char        acmd[80];
	char        szaResponse[200];
	long        sp[8];
	double      vr;
	ShowInf     m_ShowInf;     //从G代码中读出的显示原片信息
	ShowInf     m_ExtraSmall;  //扩展显示原片信息
	double m_dMaxArcRadius;
	int    m_nLabelPos;        //1打印标签中间；0打印左下角
    int    m_nLabelTime;       //打印time
	int    m_nLabelStart;      //开始的num
	int    m_nLabelPosX;       //标签头相对于机头距离X
	int    m_nLabelPosY;       //标签头相对于机头距离Y
	int    m_nPaperPosY;       //取标签Y轴的位置
	//把dmc写成文件
	int  WritDmcToFile(char FAR* pszDMCFileName);
//规划速度
	double m_AheadDis;//前馈距离

	//规划切割速度
	void  PlanningSpeed();

	//根据圆弧半径计算单个圆弧的速度
    void  CalcSingleCircleSpeed(PDMC pDmc);

    //通过单位向量计算两个插补的节点的拐角速度
	//前馈第一步,
	//参数当前插补  
	void  SetDirectVectorSpeed(PDMC pdmc1);

	//计算夹角的速度
	double CalcAngleSpeed(double dAngle);

	PDMC BlocksDmcBlock(char VMOpen,PBLOCK pBlock,CString str); 
    

public:
	void FreeDmc();                      //更换工件时，将所照过的部分全都删节
	PDMC GetDmcNumber();                     /* 获得自动库的DMC结构数据 */
	long GetRate();                          /* 获得进给倍率 */
	long OnContinue();
	long OnPause();
	long OnReset();
	/* 计算玻璃相关参数 */
	void OnGlassCal(); 
	void OnRun();
	void OnRunContinue(); 
	long SetRate(long rate,double sp[3]);  /* 设置进给倍率 */
	long GetRunLine();					
	long GetRunflag();                  
	long GetPauseflag();                
	long GetLM();		

	long SetGlassPress(double dPress[12],long iTimer[5],double dRadius[2]);
	/* 玻璃切割压力运算 */
	long SetGlassCal(); 
	/* 空运行选项与注油选项 */
    void SetRunOption(int iOption,int iKnife); 
	/* 玻璃切割中的偏心补偿，刀具是旋转的 */
	void SetKnifeOffset(double dX,double dY); 
	/* 计算直线的偏移 */
	void SetKnifeOffsetLine(PLINE pLine); 
	/* 计算圆弧的偏移 */
	void SetKnifeOffsetArc(PARC pArc); 
	/* 建立玻璃切割时，刀心偏移，端点及圆半径等变化后的运动段 */
	int BuildGlassOffsetMotionSegments(void);
	/* 设置玻璃放置位置 */
	void SetGlassPlacePos(double px_x,double px_y,double po_x,double po_y,double py_x,double py_y); 
	/* 点改变后的位置 */
	long SetGlassPointPos(pPoint2D p); 
	/* CNC文件双向切割不转刀时调用 */
	char SetKnifeOffsetLineNoRotate(PLINE pLine); 
	/* 设置CNC文件是否是双向切割，且不使用排序 */
	void SetCncOption(int iOption); 
	/* 直线大于或等于180度，设定不转刀标志 */
	char SetCncFlagOption(PLINE pLine); 
	/**/
	/* 注油功能，要在运动中开关阀 */
	void SetOilingOption(double dAvOpen, double dAvClose, CString FileAV); 

	void SetDmcFilename(CString dmc1);//上片dmc
	void SetServoControl(int nServo);
	void SetMsgWnd(CWnd *pWnd);
	void SetLoadGlass(BOOL bLoadGlass);
    pShowInf GetShowInf();//主界面得到需要显示的信息	
    pShowInf GetExtraSmall();//主界面得到需要扩展显示的信息

	//解析G代码文件里的显示信息，赋给数据结构
    //返回值0：不是显示信息。1；是显示信息
    int ParseShow(CString str);

	void FreeShowInf();

	pSmallInf AddShowSmallInf();
    
	void CopyExtraSmall();

	void FreeExtraSmall();

	void SetReadyTime(int iTime);//设置上片台准备时间
	
    void OnTurnOver();	 //上片台准备时间判断

	//在画小片尺寸的时候考虑玻璃在定位后的起点坐标X,坐标Y，旋转的角度
	void GetGlassPos(double &posX,double &posY,double &posAngle);
	
	int GetRunState();//切玻璃1g_nCutMode;     
	
	void SetDoubleXW(bool bXW);//1为龙门

	void SetAheadDis(double dDis);//设置前馈算法前馈距离mm

	//打印标签功能是否有效及打印的位置
	void SetLabelInf(int nLable, int nPos);

	//打印标签延时时间ms
	void SetLabelTime(int nTime);

	//打印标签开始的打印个数
	void SetLabelStartNum(int nStartNum);

	//贴标签 返回0贴标签正常；返回1贴标签故障
	int RunLabel();

	//实心刀头，正反刀切割
	void SetSolidHead(BOOL bSolid);

	//手动打标签，启动线程
    void HandLabel();

	//标签相对于机头的距离,取标签位置Y
	void SetLabelPos(int nX,int nY,int nPaper);
};

#endif // !defined(AFX_DMCGC_H__C74A9F7D_4E5A_4492_A09C_CA3211DD3C34__INCLUDED_)
