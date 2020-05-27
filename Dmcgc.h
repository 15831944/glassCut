// Dmcgc.h: interface for the CDmcgc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMCGC_H__C74A9F7D_4E5A_4492_A09C_CA3211DD3C34__INCLUDED_)
#define AFX_DMCGC_H__C74A9F7D_4E5A_4492_A09C_CA3211DD3C34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Dmcwin.h"	/* ������ */
#ifndef min
   #define min(x,y) ((((x)<(y))?(x):(y)))
#endif
#define MIN min

#ifndef max
   #define max(x,y) ((((x)>(y))?(x):(y)))
#endif
#define MAX max

/* �����������ڽ�����Ϣ */
#define WM_DMCGC		WM_USER+199	/* �����ڵ���������͵���Ͻ�����ʾ */

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
/* ��������ϵ */
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
	char		   chRotateFlag;		/* CNC�ļ���˫���и�ʱ�Ƿ�ת�� */
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
	double         fRadius;               //��λmm
	double         fBeginAngle;
	double         fEndAngle;
	double         fTraverseAngle;
	double         fFeed;                 //�ӹ��ٶ�MM/S
} ARC, * PARC;

/* This structure defines a linear segment (part of a command block) */
typedef struct tagLINE
{
	unsigned char  chScale;              /* 0 = inches, 1 = millimeters */
	unsigned char  chPlane;
	unsigned char  chPosition;           /* 0 = relative, 1 = absolute */   
	COORDINATE     fBegin;
	COORDINATE     fEnd;
	double         fFeed;                //�ӹ��ٶ�MM/S
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
   double          fRapidMoveSpeed;            //��λ�ٶ�
   double          fFeedRate;                  //�岹�ٶ�
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

/* �Զ���ת�� */
//====================================================
#define  LONG_COMMAND               40     /* ˫�ַ������ */
#define  LONG_LINE                  80     /* �����г��� */


struct tag2DPoint
{
	double x;
	double y;
}; 
typedef struct tag2DPoint Point2D,*pPoint2D;

//��ʾСƬ��Ϣ
struct tagSmallInf
{
	int nSizeX;             //�������СƬX����ߴ�
	int nSizeY;             //�������СƬY����ߴ�
	int nOX;            //�������СƬ���½�X����
	int nOY;            //�������СƬ���½�Y����
	CString strSizeX;   //������ʾ��Xֵ
	CString strSizeY;   //������ʾ��Yֵ
	CString strName;	//�������СƬ�Ŀͻ���
	CString strNum;     //����λ��
	CString strShelf;   //�������,�������Ƭ��ʾ*
	tagSmallInf *pNext;	
};
typedef struct tagSmallInf SmallInf,*pSmallInf;

//��ʾԭƬ��Ϣ����СƬ��Ϣ
struct tagShowInf
{
	int nX;                 //ԭƬX����ߴ�
    int nY;                 //ԭƬY����ߴ�
    int nCutX1;             //����ԭƬX1�ޱ�
	int nCutY1;	            //����ԭƬY1�ޱ�
	int nCutX2;	            //����ԭƬX2�ޱ�
	int nCutY2;             //����ԭƬY2�ޱ�
	int nCount;             //����ԭƬ����
	int nVersions;	        //����ǰ���
	int nCurrentVersions;	//�����ܰ��
	CString strStuff;       //�������
	CString strStorage;	    //�������ԭƬ�Ļ��ܺ�
	tagSmallInf   *pShowSmall;//СƬ��Ϣ
};
typedef struct tagShowInf ShowInf,*pShowInf;

/* ִ����Ƭ���� */
UINT SendLoadGlass(LPVOID pParam);//

/* ���ִ�к��� */
UINT SendThickness(LPVOID pParam);//
/* ������ִ�к��� */
UINT SendCommand(LPVOID pParam);//

//����ָ������ӹ�
UINT SendCommandContinue(LPVOID pParam);//

/* ��Ƭ̨׼���ȴ� */
UINT SendTurnOver(LPVOID pParam);//

/* �ֶ�������ǩ */
UINT SendHandLabel(LPVOID pParam);//

struct tagDMC
{
	long           number;                          /* �кţ�������G���룩 */
	char           command[LONG_COMMAND];           /* DMC �������� */
	char           comG;                            /* �������� G �� M */
	int            comGNo;                          /* G �� M ����� */
	char           szLine[LONG_LINE];               /* ת��������DMC������ */
	char           szLineG[LONG_LINE];              /* ԭʼ��G����������� */
	char           chVM;                            /* �Ƿ���  VM  ���� */
	char           chVE;                            /* �Ƿ���  VE  ���� */
	char           szVector[LONG_COMMAND];          /* VM  ��������� */
	char           szVTEnd[LONG_COMMAND];           /* VE  ��������� */
	char           szVTAMS[LONG_COMMAND];           /* AM  ��������� */
	char           chPosType;                       /* λ������ ��Ի���� */
	char           chVMOpen;                        /* �岹�Ƿ��Ѵ� */
	char           chVMMode;                        /* �岹ģʽ LM �� VM */
	char           chPlane;                         /* ƽ�� ��0 = XY, 1 = ZX, 2 = XY */
	char		   chRotateFlag;					/* CNC�ļ���˫���и�ʱ�Ƿ�ת�� */
	COORDINATE     usComPos;                        /* ����X ֵ */   
	COORDINATE     usProPos;                        /* ����X λ�� */   
	COORDINATE     usOrigin;                        /* ʸ��X ԭ��λ�� */   
	double         usRadius;                        /* �뾶 ��λ����*/
	double         usBAngle;                        /* Բ����ʼ�Ƕ� */   
	double         usEAngle;                        /* �нǣ���Ϊ ��ubtʱ�룬��Ϊ˳ʱ��*/
	double         dPress;                          /* �и�ѹ��ֵ���ɶ����Ĳ������� */
	double         fVectorLenth;					/* ÿ�ε�ʸ������mm */
	double         fVectorTotal;					/* �ܵ�ʸ������mm */
	double         dStartSpeed;                     //��ʼ�ٶ� mm/s
	double         dEndSpeed;                       //��ֹ�ٶ� mm/s
	double         dStartAngle;                     //��ʼ�Ƕ�[0-360��
	double         dEndAngle;                       //Բ����ֹ�Ƕ�
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
extern PDMC        pcurrDmc;                        /* DMC�ṹָ��,pbackDmc���ڻ��˹��� */
extern DMC         currDmc;                         /* DMC�ṹ */
extern PDMC        pbackDmc;                        /* DMC�ṹָ��,pbackDmc���ڻ��˹��� */
extern PDMC        pcurrRunDmc;                     /* DMC�ṹָ��,pcurrRunDmc���ڵ�ǰ����DMC�ṹ���� */
extern CString     strVM;
/* �����и��У�ѹ����ز��� */
extern double		g_dPress[12];		/* ��ѹ�����ѹ��ֱ�ߡ�Բ������ѹ */
extern long			g_iTimer[5];		/* ֱ�߼�ѹʱ�䣬Բ����ѹʱ��,�µ��ӳ�ʱ��,̧���ӳ�ʱ��*/
extern double		g_dRadius[2];		/* �����뾶����Բ������ѹ�� */
extern int          iRunOption;			/* �и�-��ʾ */

extern int          iRunKnife;          //ע��
extern long			iDelayTime;			/* �и�ʱ���µ��ӳ� */
extern int          iCncRotate;			/* CNC�ļ���˫���и�ʱ�Ƿ�ת�� */
extern double		dCenterX,dCenterY;	/* ����ƫ��ֵ */
extern double		dGlassKnifeRadius,dGlassKnifeAngle;		/* ƫ�İ뾶��0��ʱ��ƫ�ĽǶ� */
extern Point2D		g_px,g_po,g_py;		/* ��������λ�� */
extern double		g_dGlassAngle;		/* ����ƫ�ýǶ� */
/* �����и��У�ѹ����ز��� */
extern int          g_nCutMode;         //1�и�
extern bool         g_bDoubleXW;        //����
struct CMotionAVInfo 
{
	char	FileAV[100];
	double	dAVOpen;
	double  dAVClose;
};
class CDmcgc;
struct CDownloadThreadInfo 
{
	char			file1[100];//dmc��Ƭ
	int             iReadyTime;
	Point2D			fBegin;			/* ����ѭ�������� */
	Point2D			fEnd;			/* ����ѭ������յ� */
	CMotionAVInfo	Oiling;			/* ע�͹��ܣ�Ҫ���˶��п��ط� */
	int				nServoControl;	/* �ŷ����Ʒ�ʽ */
	BOOL			bLoadGlass;		/* �Ƿ���Ҫ��Ƭ */
	CWnd			*pWnd;
	double          dFeed;           //�и���˶�ʱ�ٶȡ�
	double          dFeedAcc;        //�и���˶�ʱ���ٶȡ�
	double          dFeedDec;        //�и���˶�ʱ���ٶȡ�
	double          dLocationAcc;           //��λ�˶�ʱ���ٶȡ�
	double          dLocationDcc;           //��λ�˶�ʱ���ٶȡ�
	double          dInterpolationAcc;        //�岹�˶�ʱ���ٶȡ�
	double          dInterpolationDec;        //�岹�˶�ʱ���ٶȡ�
	int             nErrorAngle;              //�����ٶȺͲ岹�ٶȵ�����Ƕ�
	int             nOffset;
	int             nLabel;           //1��ӡ��ǩ
	BOOL            bSolidHead;       //1ʵ�ĵ�ͷ���������и�
	CDmcgc*         pDmcgc;           //����          
};

long CheckArc(double x0,double y0,double r,double sd,double sendd,double tpx,double tpy); 
double PointAngleTo(double dBcx,double dBcy,double dEcx,double dEcy);
long CheckLine(double x0,double y0,double x1,double y1,double tpx,double tpy); /* ��㣬�յ㣬��ͣ�� */
int WaitingMotionComplete(CString str);				/* �ȴ��˶���� */
void RunAvOption(double dAvOn, double dAvOff, double dTotal);	/* ����AV��ֵ */
/* ����ִ�� */
int RunCommand(CString strRunComm);
void WaitingTimeComplete(CString str);              /* �ȴ�ʱ�䵽�� */
void WaitingPressTimeBgsComplete(CWnd *pCwnd,double dPress,long addTime); /* �ȴ�ѹ������;��ѹ��ʱaddPress */
int WaitingXQMotionComplete();
int Round(double dValue);//��������

//================================================================
class AFX_EXT_CLASS CRunCommand : public CObject
{
public:
	CRunCommand();
	virtual ~CRunCommand();
	
	/* ����ִ�� */
	int RunCommand(CString strRunComm);
	
	/* ����ִ�� */
	float RunCommandfloat(CString strRunComm);
	
	/* �ߵ�ĳ��λ������ */
	void RunGotoPosCommand(double dDisX, double dDisY, double dDisZ, double dSpeed, double dAcc, double dDec);
	
	/* �ߵ�ĳ��λ������ */
	void RunGotoPosCommand(double dDisX, double dDisY, double dSpeed, double dAcc, double dDec);
	
	/* Z���ߵ�ĳ��λ������ */
	void RunGotoZPosCommand(double dDisZ, double dDelaysupply, double dSpeed, double dAcc, double dDec);
	
	PDMC GetBehindG00(PDMC pRunDmc); /* ����4λС�� */		
	
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
   ���������
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
   ��ֱ��Բ��������
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
int		CheckCornerAngle(PBLOCK pBlockHead);//�Ƕȴ������սǽǶ�����̧������
double	Block2BlockAngles(PBLOCK pBlock1, PBLOCK pBlock2);
double	LineIncomingAngle(PLINE pLine);
double	LineOutgoingAngle(PLINE pLine);
double	ArcIncomingAngle(PARC pArc);
double	ArcOutgoingAngle(PARC pArc);
int  AddUpperBlock(PBLOCK pBlock1);//����̧��


//�и���˶�ʱ�ٶ�,���ٶȣ����ٶ�
void  SetFeedMotion(double dSpeed,double dAcc,double dDec);

//�岹�˶�ʱ���ٶȣ����ٶ�
void  SetInterpolation(double dAcc,double dDec);

//��λ�˶�ʱ�Ӽ��ٶ�
void  SetLocationMotion(double dSpeedX,double dSpeedY);

//����Բ�����뾶
void SetMaxRadius(double dValue);

//���ÿ�����ָ��
void SetController(long lController);

/* �Զ���ת�� */
//======================================================================
protected:
	char        acmd[80];
	char        szaResponse[200];
	long        sp[8];
	double      vr;
	ShowInf     m_ShowInf;     //��G�����ж�������ʾԭƬ��Ϣ
	ShowInf     m_ExtraSmall;  //��չ��ʾԭƬ��Ϣ
	double m_dMaxArcRadius;
	int    m_nLabelPos;        //1��ӡ��ǩ�м䣻0��ӡ���½�
    int    m_nLabelTime;       //��ӡtime
	int    m_nLabelStart;      //��ʼ��num
	int    m_nLabelPosX;       //��ǩͷ����ڻ�ͷ����X
	int    m_nLabelPosY;       //��ǩͷ����ڻ�ͷ����Y
	int    m_nPaperPosY;       //ȡ��ǩY���λ��
	//��dmcд���ļ�
	int  WritDmcToFile(char FAR* pszDMCFileName);
//�滮�ٶ�
	double m_AheadDis;//ǰ������

	//�滮�и��ٶ�
	void  PlanningSpeed();

	//����Բ���뾶���㵥��Բ�����ٶ�
    void  CalcSingleCircleSpeed(PDMC pDmc);

    //ͨ����λ�������������岹�Ľڵ�Ĺս��ٶ�
	//ǰ����һ��,
	//������ǰ�岹  
	void  SetDirectVectorSpeed(PDMC pdmc1);

	//����нǵ��ٶ�
	double CalcAngleSpeed(double dAngle);

	PDMC BlocksDmcBlock(char VMOpen,PBLOCK pBlock,CString str); 
    

public:
	void FreeDmc();                      //��������ʱ�������չ��Ĳ���ȫ��ɾ��
	PDMC GetDmcNumber();                     /* ����Զ����DMC�ṹ���� */
	long GetRate();                          /* ��ý������� */
	long OnContinue();
	long OnPause();
	long OnReset();
	/* ���㲣����ز��� */
	void OnGlassCal(); 
	void OnRun();
	void OnRunContinue(); 
	long SetRate(long rate,double sp[3]);  /* ���ý������� */
	long GetRunLine();					
	long GetRunflag();                  
	long GetPauseflag();                
	long GetLM();		

	long SetGlassPress(double dPress[12],long iTimer[5],double dRadius[2]);
	/* �����и�ѹ������ */
	long SetGlassCal(); 
	/* ������ѡ����ע��ѡ�� */
    void SetRunOption(int iOption,int iKnife); 
	/* �����и��е�ƫ�Ĳ�������������ת�� */
	void SetKnifeOffset(double dX,double dY); 
	/* ����ֱ�ߵ�ƫ�� */
	void SetKnifeOffsetLine(PLINE pLine); 
	/* ����Բ����ƫ�� */
	void SetKnifeOffsetArc(PARC pArc); 
	/* ���������и�ʱ������ƫ�ƣ��˵㼰Բ�뾶�ȱ仯����˶��� */
	int BuildGlassOffsetMotionSegments(void);
	/* ���ò�������λ�� */
	void SetGlassPlacePos(double px_x,double px_y,double po_x,double po_y,double py_x,double py_y); 
	/* ��ı���λ�� */
	long SetGlassPointPos(pPoint2D p); 
	/* CNC�ļ�˫���иת��ʱ���� */
	char SetKnifeOffsetLineNoRotate(PLINE pLine); 
	/* ����CNC�ļ��Ƿ���˫���и�Ҳ�ʹ������ */
	void SetCncOption(int iOption); 
	/* ֱ�ߴ��ڻ����180�ȣ��趨��ת����־ */
	char SetCncFlagOption(PLINE pLine); 
	/**/
	/* ע�͹��ܣ�Ҫ���˶��п��ط� */
	void SetOilingOption(double dAvOpen, double dAvClose, CString FileAV); 

	void SetDmcFilename(CString dmc1);//��Ƭdmc
	void SetServoControl(int nServo);
	void SetMsgWnd(CWnd *pWnd);
	void SetLoadGlass(BOOL bLoadGlass);
    pShowInf GetShowInf();//������õ���Ҫ��ʾ����Ϣ	
    pShowInf GetExtraSmall();//������õ���Ҫ��չ��ʾ����Ϣ

	//����G�����ļ������ʾ��Ϣ���������ݽṹ
    //����ֵ0��������ʾ��Ϣ��1������ʾ��Ϣ
    int ParseShow(CString str);

	void FreeShowInf();

	pSmallInf AddShowSmallInf();
    
	void CopyExtraSmall();

	void FreeExtraSmall();

	void SetReadyTime(int iTime);//������Ƭ̨׼��ʱ��
	
    void OnTurnOver();	 //��Ƭ̨׼��ʱ���ж�

	//�ڻ�СƬ�ߴ��ʱ���ǲ����ڶ�λ����������X,����Y����ת�ĽǶ�
	void GetGlassPos(double &posX,double &posY,double &posAngle);
	
	int GetRunState();//�в���1g_nCutMode;     
	
	void SetDoubleXW(bool bXW);//1Ϊ����

	void SetAheadDis(double dDis);//����ǰ���㷨ǰ������mm

	//��ӡ��ǩ�����Ƿ���Ч����ӡ��λ��
	void SetLabelInf(int nLable, int nPos);

	//��ӡ��ǩ��ʱʱ��ms
	void SetLabelTime(int nTime);

	//��ӡ��ǩ��ʼ�Ĵ�ӡ����
	void SetLabelStartNum(int nStartNum);

	//����ǩ ����0����ǩ����������1����ǩ����
	int RunLabel();

	//ʵ�ĵ�ͷ���������и�
	void SetSolidHead(BOOL bSolid);

	//�ֶ����ǩ�������߳�
    void HandLabel();

	//��ǩ����ڻ�ͷ�ľ���,ȡ��ǩλ��Y
	void SetLabelPos(int nX,int nY,int nPaper);
};

#endif // !defined(AFX_DMCGC_H__C74A9F7D_4E5A_4492_A09C_CA3211DD3C34__INCLUDED_)
