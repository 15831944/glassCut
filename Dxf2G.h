// Dxf2G1.h: interface for the CDxf2G class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DXF2G1_H__630BA899_C69D_4A84_9A80_7D8E04E3674E__INCLUDED_)
#define AFX_DXF2G1_H__630BA899_C69D_4A84_9A80_7D8E04E3674E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Entity.h"

extern COLORREF				g_CurColor ;
extern int					g_CurLineStyle ;
extern int					g_CurLineWidth ;
extern int                  g_CurLineLayer ;
#ifndef COORDINATE
#define COORDINATE 1
#endif

//定义参数直线
struct tagPOINT6D
{
	double      x1;
	double      y1;
	double      x2;
	double      y2;
	double      x3;
	double      y3;
};
typedef struct tagPOINT6D POINT6D, *PPOINT6D;
/*-----------------------------------------------------------------*/
//定义参数插补
struct tagSect
{
	int				nSect;
	POSITION		m_pos;	/* 插补的起点 */
	int				nLayer;	/* 直线的颜色 */
	tagSect			*Next;
	tagSect			*Prev;
};
typedef struct tagSect Sect, *PSect;

//定义参数插补
struct tagObList
{
	int				nIndex;		/* 插补计数 */
	Position		m_posBegin;	/* 插补的起点 */
	Position		m_posEnd;	/* 插补的终点 */
	PSect			m_Sect;		/* 一个完整的插补 */
	BOOL			bClose;		/* 是否闭合，TRUE：闭合，FALSE：不闭合 */
	int				ndirect;	/* 闭合顺时针：-1，闭合逆时针：1，不闭合：0 */
	tagObList		*Next;
	tagObList		*Prev;
};
typedef struct tagObList ObList, *PObList;

struct tagENBLOCK
{
	double      dxBasepoint;
	double      dyBasepoint;
	double      dzBasepoint;
	CString		strBlockName;
	CObList		m_BlockList;
	
	tagENBLOCK	*pNext;
	tagENBLOCK	*pPrev;
};
typedef struct tagENBLOCK ENBLOCK, *PENBLOCK;
/*-----------------------------------------------------------------*/

class AFX_EXT_CLASS CDxf2G : public CObject  
{
public:		
	int SetOutputFile(char * chPath);
	int SetInputFile(char * chPath);
	void SetDownOperation(char *chDown);
	void SetUpOperation(char *chUp);
	void SetHeadTailHomeOperation(char * chHead,char * chTail,char * chHome);
	void SetSortOrder(BOOL bSort, BOOL bSortBy, int iWay);
	
	CDxf2G();
	virtual ~CDxf2G();

protected:	
	
	Position m_Point[2000];//用来存储文件中的点

	int m_nPoint;	//记录一共有多少个点
	int m_nRuler;
	
	float	m_fPutDegree;
	
	/* wzh */
	Position m_positionEnd;		//wjl,记录上一层图形的结束位置
	/* wzh */
	
    int         m_iMaxLayer;
	CObList		m_EntityList;  //图元对象链表
	ObList		m_stuObList;		/* 以插补为单位的数据结构 */
	PENBLOCK	m_pDxfBlock;

	int GetEdition(FILE * fp);
	void switchType(FILE * fp);
	void readCircle(FILE *fp);
	void readArc(FILE *fp);
	void readLine(FILE * fp);
	void readPoint(FILE *fp);
	void ReadPolyLine(FILE *fp);
	void ReadRuler(FILE *fp);

	void ReadBlock(FILE *fp);
	PENBLOCK AddDxfBlock();
	void readBlockCircle(FILE *fp, CObList* m_List);
	void readBlockArc(FILE *fp, CObList* m_List);
	void readBlockLine(FILE * fp, CObList* m_List);
	void readBlockPoint(FILE *fp, CObList* m_List);
	void ReadBlockPolyLine(FILE *fp, CObList* m_List);
	void FindInsertBlock(FILE *fp);
	void InsertBlock(Position &pointinsert,char * chBlockName);
	void FreeBlock();
	
	void switchTypeCNC(char * chPath);
	void readLineCNC(POINT6D  Number);
	void readArcCNC(POINT6D  Number);
	POINT6D OnGetNumber(CString strData); 
	//式样
	POSITION GetBasePoint(Position relPoint,double fEndAngle, BOOL nSeprate=FALSE);
	/*得到当前图层的最小点*/
	POSITION GetMinPoint(int layer,Position relPoint);


	double GetDis(Position pos1, Position pos2);
	double GetDis(double x1, double y1, double x2, double y2);
	//最优路径输出文件
	void SettleByLeastDis();	/* 按最短距离排序 */
	void SettleByDxfPoint();	/* 按DXF图形画点排序 */
	
	
	int Sort();
	void SortPoint();	/* 对DXF图形中的点进行最近排序 */
	void SortVPPoint();	/* 将CObList中的数据整理为以插补为单位的数据结构 */
	void Sort_CW();		//顺时针
	void Sort_CCW();	//逆时针
	void Sort_Color();	//按颜色

	int outGCode(char * chPath);
	int OutGlassGCode(char * chPath);
	

	PObList AddObList(PObList pCurr);	//增加一个结构
	PObList DeleteObList(PObList pOblist);  //增加一个结构
	void FreeObList();                      //更换工件时，将所照过的部分全都删节
	PSect AddSect(PSect pCurr);			//增加一个记区
	//* 闭合顺时针：-1，闭合逆时针：1，不闭合：0;判断不完全准确，需进一步验证 */
	int GetDirect(PSect pHeadSect);		
	/* 计算两点的角度 */
	double PointToPointAngle(double dBeginX,double dBeginY,double dEndX,double dEndY);
	/* Calculate the traverse angle of an arc segment */
	double CalculateTraverseAngle(int nType, double fBeginAngle, double fEndAngle);
	/* 反转封闭图形 */
	void ReverseSect(PObList pTempObList);
	/* 合并所有结构中相接的数据 */


	
	void CombinationData();
	/* 获取下一个不封闭的结构 */
	PObList GetNextNoCloseOblist(PObList pCurr);
	/* 判断是否是相接的 */
	int JudgeConnect(PObList pFirst, PObList pSecond);
	/* 获取最后一个PSect结点 */
	PSect GetLastSect(PObList pCurr);
	/* 将两个本来相接的插补合并为一个 */
	PObList CombinationOblist(int nConn, PObList pFirst, PObList pSecond);
		
	CString m_strDown;
	CString m_strUp;
	CString m_strHead;
	CString m_strTail;
	CString m_strHome;
	BOOL    m_nSort;/* 是否使用排序；1：使用，0：不用 */
	int		m_iWay; /* 0:颜色排序（绿：逆；红：顺时针）；1：逆时针；2：顺时针 */
	int		m_nSortBy; /* 0:最近点；1：切入点 */
	double  m_dFeedrate;
	double	m_dScale;
};

#endif // !defined(AFX_DXF2G1_H__630BA899_C69D_4A84_9A80_7D8E04E3674E__INCLUDED_)
