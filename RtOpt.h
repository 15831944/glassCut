// RtOpt.h: interface for the CRtOpt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTOPT_H__B4B357DD_CC73_43BD_AAEC_49D441B705F7__INCLUDED_)
#define AFX_RTOPT_H__B4B357DD_CC73_43BD_AAEC_49D441B705F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include <math.h>

class CRptPoint;
class CRptRect;
class CRptEdge;
class CRptTrim;
class CRptLine;
class CRptShape;
class CRptDmsn;
class CRptRaw;
class CRawRect;
class CNoRect;
class CRestRect;
class CRptDgm;
//浮点数比较大小
const double minest = 0.01;
const int MAX = 5000;

class AFX_EXT_CLASS CRtOpt
{
public:
	CRtOpt();
	virtual ~CRtOpt();
	//初始化原始链表(将从Dll外部传入的链表元素保存在m_pLstRaw和m_pLstPro中)
	void InitRawList(CList<CRptRaw*, CRptRaw*>& lstRaw);
	void InitProList(CList<CRptDmsn*, CRptDmsn*>& lstPro);
	//获取每版图形排列的链表
	CList<CRptDgm*, CRptDgm*>* GetDgmList();
	CList<CRptRaw*, CRptRaw*>* GetRawList();
	CList<CRptDmsn*, CRptDmsn*>* GetDmsnList();

	//获取切割方式
	int		GetCutMean() { return m_nCutMean; }				
	//设置切割方式
	int 	SetCutMean(int nMean)	
	{
		ASSERT( nMean==1 || nMean==0 );
		if ( nMean==0 && nMean==1 ) 
		{
			m_nCutMean = nMean;
			return 0;	//设置成功
		}
		else
			return -1;	//设置失败
	}

	//优化图形 
	int Arrange();		//返回1表示原片数目不够,2表示m_pLstRawEach链表的头元素POSITION为空
	
	//生成G代码
	BSTR WriteGCode(CString strFileName);
	
	//生成异形G代码
	CString GenShapeGCode( CString strCmd, CRptShape shape, CRawRect rtRaw );
	
	//旋转异形
	CString RotateSelect(double fBeginAngle, double fRotateAngel, CRptRect rt, CString strCmd);		

	//计算整体优化率
	double GetUtil();

	//清空链表元素，指向链表的指针不置空
	void Clear();

	//打印函数
	void print(CList<CRptRaw*, CRptRaw*>* pLst, int idx);
	void print(CList<CRptDmsn*, CRptDmsn*>* pLst, int idx = -1);
	void print(CList<CRptDgm*, CRptDgm*>* pLst, int idx);

private:
	void Sort(CList<CRptDmsn*, CRptDmsn*>* pLstPro);							//对成品矩形进行排序
	void SwapPro(CList<CRptDmsn*, CRptDmsn*>* pLstPro);							//对lstPro链表中宽大于长的元素，交换长和宽
	BOOL Elicitation(CRawRect *pRtRaw, POSITION posPro);						//在每张原片上排列矩形
	void LayRect(CRawRect *pRtRaw, POSITION posPro, int nMean, int num);		//在矩形rt上面以nMean方式排列num个dmsn图形
	
	int  BigEngh(CRptRect rt, CRptDmsn dmsn, double dMinDis, int nMean, int num);		//一个原片能不能排下以nMean方式来排列num片小片，并且与边缘的距离不小于dMinDis,此函数暂未使用		
	int	 LayMean(CRptRect rt, CRptDmsn dmsn, double dMinDis, int& nRtNum);				//确定在矩形rt上怎样排列dmsn图形可以得到与边缘距离最小（考虑最小距离）

	void HandleRestMatrl(CRawRect* pRtRaw, POSITION posPro, int nMean, int num);

	BOOL BigEnghSomePro(CRawRect rtRaw);			//rtRaw如果可以排列的下m_pLstProRt中某个矩形的话，返回TRUE，否则返回FALSE

	void AddToLstRest(CRawRect *pRtRawA);			//将pRtRawA添加m_pRtRest链表中

	void RemoveLstPro();							//将m_pLstProRt链表中数目为0的元素删除

	void FillRectOnRawA(CRawRect *pRtRawA);			//在余料pRtRawA上排列矩形

	void FormLnTrack(CRawRect l_rtRaw, int nMean=0);	//形成切割路径,0表示单向切割，1表示双向

	BOOL DelGCodeFile(CString strDir, int nDepth, CString strProName);	//删除同项目名的G代码头文件

	int  GetRtRawNum();								//获取原片数量

	BOOL IsSameTrack(CList<CRptLine*, CRptLine*>* lstTrack, POSITION& posSame);		//查看此原片上切割轨迹和已存在的版面的轨迹相同
	BOOL IsSameRtLay(CList<CNoRect*, CNoRect*>* lstRtLay, POSITION& posSame);		//查看此原片上切割轨迹和已存在的版面的矩形相同(定位号也必须相同才算相同)

	void ArraySortX(CRptLine* arr, int cnt);		//对CRptLine数组中元素按X从小到大(从左到右)排序
	void ArraySortY(CRptLine* arr, int cnt);		//对CRptLine数组中元素按Y从大到小(从下到上、从低到高)排序 

	void ArraySortYB2T(CRptLine* arr, int cnt);		//对CRptLine数组中元素按Y从小到大(从低到高)排序 

	//正反刀，就近
	void ArraySortNearX(CRptLine* arr, int& cnt, CRawRect l_rtRaw);		
	POSITION MinXDisByPt(CRptPoint pt, CList<CRptLine*, CRptLine*>& lstLine, BOOL bFlag);
	void ArraySortNearY(CRptLine* arr, int& cnt, CRawRect l_rtRaw);
	POSITION MinYDisByPt(CRptPoint pt, CList<CRptLine*, CRptLine*>& lstLine, BOOL bFlag);

	void AddDgmToLst(CRptDgm *pDgm);				//向m_pLstDgm链表中添加版面

	static BOOL LE(const double& x, const double& y) { return (x<y||fabs(x-y)<minest); }
	static BOOL GE(const double& x, const double& y) { return (x>y||fabs(x-y)<minest); }

	//初始化排列链表(将原始链表中元素“复制”一份放入m_pLstRawRt和m_pLstProRt中，
	//顺便建立排列过程中需要的m_pRtLay,m_pRtRest,m_pLnTrack以及保存结果的m_pLstDgm)
	void InitLst();
	void CopyLst(CList<CRptRaw*, CRptRaw*>* m_pLstRaw);
	void CopyLst(CList<CRptDmsn*, CRptDmsn*>* m_pLstPro);
	//销毁此次矩形排列中使用的链表即m_pLstRawRt, m_pLstProRt, m_pRtLay, m_pRtRest, m_pLnTrack
	void DestroyLst();
	
	void DelLst(CList<CRawRect*, CRawRect*>* pLstRawRt);	//销毁m_pLstRawEach也是用的此函数
	void DelLst(CList<CRptDmsn*, CRptDmsn*>* m_pLstProRt);
	void DelLst(CList<CNoRect*,	 CNoRect*>*	 m_pRtLay);
	void DelLst(CList<CRptDgm*, CRptDgm*>*   pLstDgm);
	void DelLst(CList<CRptLine*, CRptLine*>* pLnTrack);
	
private:
	int m_nCutMean;		//切割方式:0单向切割1双向切割，默认单向
	//成员变量
	CList<CRptRaw*, CRptRaw*>*		m_pLstRaw;		//原片信息链表
	CList<CRptDmsn*, CRptDmsn*>*	m_pLstPro;		//成品信息链表

	//一种算法需下面一套以下链表
	//优化前：
	CList<CRawRect*, CRawRect*>*	m_pLstRawRt;	//原片矩形链表		（已实现）
	CList<CRptDmsn*, CRptDmsn*>*	m_pLstProRt;	//成品矩形链表		（已实现）
	//优化中：
public:
	CList<CRawRect*, CRawRect*>*	m_pLstRawEach;	//临时原片链表		（已实现）
	CList<CNoRect*,	 CNoRect*>*		m_pRtLay;		//已排列矩形件链表  （已实现）
	CList<CRawRect*, CRawRect*>*	m_pRtRest;		//余料链表			（已实现）
	CList<CRptLine*, CRptLine*>*	m_pLnTrack;		//切割路径链表		（已实现）
	//优化后：
	//将m_pRtLay、m_pRtRest、m_pLnTrack的指针放入m_pLstDgm中，形成m_pLstDgm
	CList<CRptDgm*,  CRptDgm*>*		m_pLstDgm;		//版面链表			（已实现）

	//日志文件
	CStdioFile m_flLog;
	CString m_strLogFileName;
};

class CRptPoint
{
public:
	double x;					//x轴坐标
	double y;					//y轴坐标
public:
	CRptPoint( ) { }
	CRptPoint( double xx, double yy ) { x = xx;	y = yy; }
	CRptPoint( const CRptPoint& pt ) { x = pt.x; y = pt.y; }
	CRptPoint& operator=(const CRptPoint& pt) {	x = pt.x;	y = pt.y; return *this; }
	//重载==运算符
	BOOL operator ==( CRptPoint point ) const
	{
		BOOL bFlag = FALSE;
		if ( fabs(x-point.x)<minest && fabs(y-point.y)<minest ) 
		{
			bFlag = TRUE;
		}
		return bFlag;
	}
	//重载!=运算符
	BOOL operator !=( CRptPoint point ) const
	{
		BOOL bFlag = TRUE;
		if ( fabs(x-point.x)<minest && fabs(y-point.y)<minest ) 
		{
			bFlag = FALSE;
		}
		return bFlag;
	}
};

class CRptLine
{
public:
	CRptPoint ptStart;			//切割起点
	CRptPoint ptEnd;			//切割终点
public:
	CRptLine( ) { };
	CRptLine( CRptPoint ptInitStart, CRptPoint ptInitEnd ) { ptStart = ptInitStart; ptEnd = ptInitEnd; }
	CRptLine( const CRptLine& line ) { ptStart = line.ptStart; ptEnd = line.ptEnd; }
	CRptLine& operator=(const CRptLine& line) { ptStart = line.ptStart; ptEnd = line.ptEnd; return *this; }

	//重载==运算符
	/*
	BOOL operator ==( const CRptLine& line ) const
	{
		BOOL bFlag = FALSE;
		if ( fabs(ptStart.x-line.ptStart.x)<minest && fabs(ptStart.x-line.ptStart.x)<minest ) 
		{
			bFlag = TRUE;
		}
		return bFlag;
	}
	*/
};

//自定义矩形
class CRptRect : public CObject
{
public:
	double left;				
	double top;
	double right;
	double bottom;
public:
	CRptRect( ) { }
	CRptRect( CRptPoint ptStart, CRptPoint ptEnd ) { left = ptStart.x; top = ptStart.y; right = ptEnd.x; bottom = ptEnd.y; }
	CRptRect( double l, double t, double r, double b ) { left = l; top = t; right = r; bottom = b; }
	CRptRect( const CRptRect& rt) {	left = rt.left; top = rt.top; right = rt.right; bottom = rt.bottom; }
	CRptRect& operator=(const CRptRect& rt) { left = rt.left; top = rt.top; right = rt.right; bottom = rt.bottom; return *this; }
	//重载->运算符
	//const CRptRect* operator->() const { return this; }
	//重载<=运算符
	double Width() const		{ return fabs(left-right); }
	double Height() const	{ return fabs(top-bottom); }
	CRptPoint BottomRight()	{ return CRptPoint(right, bottom); }
	CRptPoint TopLeft()		{ return CRptPoint(left, top); }
	static BOOL LE(const double& x, const double& y) { return (x<y||fabs(x-y)<minest); }
	static BOOL GE(const double& x, const double& y) { return (x>y||fabs(x-y)<minest); }

	BOOL PtOnRect( CRptPoint pt ) const 
	{ 
		BOOL bFlag = FALSE;
		if (  GE(pt.x, left) && LE(pt.x,right) && fabs(pt.y-top)<=minest || \
			( GE(pt.x, left) && LE(pt.x, right)) && fabs(pt.y-bottom)<=minest ||  \
			( GE(pt.y, bottom) && LE(pt.y,top)) && fabs(pt.x-left)<=minest || \
			( GE(pt.y, bottom) && LE(pt.y,top)) && fabs(pt.x-right)<=minest ) 
		{
			bFlag = TRUE;
		}
		return bFlag;
	} 

	//向上为正的坐标系
	BOOL LnOnUpRect( CRptLine line ) const 
	{ 
		BOOL bFlag = FALSE;
		if ( 
			 //line和矩形上边重合或是其一部分top
			 (fabs(line.ptStart.x-left)<minest||line.ptStart.x>left)/*line.ptStart.x>=left*/ && \
			 (fabs(line.ptStart.x-right)<minest||line.ptStart.x<right)/*line.ptStart.x<=right*/ && \
			 fabs(line.ptStart.y-top)<minest && \

			 (fabs(line.ptEnd.x-left)<minest||line.ptEnd.x>left)/*line.ptEnd.x>=left*/ && \
			 (fabs(line.ptEnd.x-right)<minest||line.ptEnd.x<right)/*line.ptEnd.x<=right*/ && \
			 fabs(line.ptEnd.y-top)<minest || \
				
			 //line和矩形下边重合或是其一部分bottom
			 (fabs(line.ptStart.x-left)<minest||line.ptStart.x>left)/*line.ptStart.x>=left*/ && \
			 (fabs(line.ptStart.x-right)<minest||line.ptStart.x<right)/*line.ptStart.x<=right*/ && \
			 fabs(line.ptStart.y-bottom)<minest && \
			 
			 (fabs(line.ptEnd.x-left)<minest||line.ptEnd.x>left)/*line.ptEnd.x>=left*/ && \
			 (fabs(line.ptEnd.x-right)<minest||line.ptEnd.x<right)/*line.ptEnd.x<=right*/ && \
			 fabs(line.ptEnd.y-bottom)<minest || \

			 //line和矩形左边重合或是其一部分bottom
			 (fabs(line.ptStart.y-bottom)<minest||line.ptStart.y<bottom)/*line.ptStart.y<=bottom*/ && \
			 (fabs(line.ptStart.y-top)<minest||line.ptStart.y>top)/*line.ptStart.y>=top*/ && \
			 fabs(line.ptStart.x-left)<minest &&

			 (fabs(line.ptEnd.y-bottom)<minest||line.ptEnd.y<bottom)/*line.ptEnd.y<=bottom*/ && \
			 (fabs(line.ptEnd.y-top)<minest||line.ptEnd.y>top)/*line.ptEnd.y>=top*/ && \
			 fabs(line.ptEnd.x-left)<minest || \

			 //line和矩形右边重合或是其一部分bottom
			 (fabs(line.ptStart.y-bottom)<minest||line.ptStart.y<bottom)/*line.ptStart.y<=bottom*/ && \
			 (fabs(line.ptStart.y-top)<minest||line.ptStart.y>top)/*line.ptStart.y>=top*/ && \
			 fabs(line.ptStart.x-right)<minest &&
			 
			 (fabs(line.ptEnd.y-bottom)<minest||line.ptEnd.y<bottom)/*line.ptEnd.y<=bottom*/ && \
			 (fabs(line.ptEnd.y-top)<minest||line.ptEnd.y>top)/*line.ptEnd.y>=top*/ && \
			 fabs(line.ptEnd.x-right)<minest
			 ) 
		{
			bFlag = TRUE;
		}
		return bFlag;
	} 
	

	//向下为正的坐标系
	BOOL LnOnDownRect( CRptLine line ) const 
	{ 
		BOOL bFlag = FALSE;
		if ( 
			//line和矩形上边重合或是其一部分top
			(fabs(line.ptStart.x-left)<minest||line.ptStart.x>left)/*line.ptStart.x>=left*/ && \
			(fabs(line.ptStart.x-right)<minest||line.ptStart.x<right)/*line.ptStart.x<=right*/ && \
			fabs(line.ptStart.y-top)<minest && \
			
			(fabs(line.ptEnd.x-left)<minest||line.ptEnd.x>left)/*line.ptEnd.x>=left*/ && \
			(fabs(line.ptEnd.x-right)<minest||line.ptEnd.x<right)/*line.ptEnd.x<=right*/ && \
			fabs(line.ptEnd.y-top)<minest || \
			
			//line和矩形下边重合或是其一部分bottom
			(fabs(line.ptStart.x-left)<minest||line.ptStart.x>left)/*line.ptStart.x>=left*/ && \
			(fabs(line.ptStart.x-right)<minest||line.ptStart.x<right)/*line.ptStart.x<=right*/ && \
			fabs(line.ptStart.y-bottom)<minest && \
			
			(fabs(line.ptEnd.x-left)<minest||line.ptEnd.x>left)/*line.ptEnd.x>=left*/ && \
			(fabs(line.ptEnd.x-right)<minest||line.ptEnd.x<right)/*line.ptEnd.x<=right*/ && \
			fabs(line.ptEnd.y-bottom)<minest || \
			
			//line和矩形左边重合或是其一部分bottom
			(fabs(line.ptStart.y-bottom)<minest||line.ptStart.y>bottom)/*line.ptStart.y<=bottom*/ && \
			(fabs(line.ptStart.y-top)<minest||line.ptStart.y<top)/*line.ptStart.y>=top*/ && \
			fabs(line.ptStart.x-left)<minest &&
			
			(fabs(line.ptEnd.y-bottom)<minest||line.ptEnd.y>bottom)/*line.ptEnd.y<=bottom*/ && \
			(fabs(line.ptEnd.y-top)<minest||line.ptEnd.y<top)/*line.ptEnd.y>=top*/ && \
			fabs(line.ptEnd.x-left)<minest || \
			
			//line和矩形右边重合或是其一部分bottom
			(fabs(line.ptStart.y-bottom)<minest||line.ptStart.y>bottom)/*line.ptStart.y<=bottom*/ && \
			(fabs(line.ptStart.y-top)<minest||line.ptStart.y<top)/*line.ptStart.y>=top*/ && \
			fabs(line.ptStart.x-right)<minest &&
			
			(fabs(line.ptEnd.y-bottom)<minest||line.ptEnd.y>bottom)/*line.ptEnd.y<=bottom*/ && \
			(fabs(line.ptEnd.y-top)<minest||line.ptEnd.y<top)/*line.ptEnd.y>=top*/ && \
			fabs(line.ptEnd.x-right)<minest
			/*
			line.ptStart.x>=left && line.ptStart.x<=right && fabs(line.ptStart.y-top)<minest &&
			line.ptEnd.x>=left && line.ptEnd.x<=right && fabs(line.ptEnd.y-top)<minest || \
			
			line.ptStart.x>=left && line.ptStart.x<=right && fabs(line.ptStart.y-bottom)<minest &&
			line.ptEnd.x>=left && line.ptEnd.x<=right && fabs(line.ptEnd.y-bottom)<minest || \
			
			line.ptStart.y>=bottom && line.ptStart.y<=top && fabs(line.ptStart.x-left)<minest &&
			line.ptEnd.y>=bottom && line.ptEnd.y<=top && fabs(line.ptEnd.x-left)<minest || \
			
			line.ptStart.y>=bottom && line.ptStart.y<=top && fabs(line.ptStart.x-right)<minest &&
			line.ptEnd.y>=bottom && line.ptEnd.y<=top && fabs(line.ptEnd.x-right)<minest 
			*/
			) 
		{
			bFlag = TRUE;
		}
		return bFlag;
	} 

	//将rt2和rt1矩形合并，结果存入rt1
	static BOOL Combine( CRptRect& rt1, CRptRect rt2 ) 
	{ 
		BOOL bFlag = FALSE;
		if (fabs(rt1.top-rt2.top) < minest && fabs(rt1.bottom-rt2.bottom) < minest && fabs(rt1.right-rt2.left) < minest) 
		{
			rt1.right = rt2.right;
			bFlag = TRUE;
		}
		if (fabs(rt1.left-rt2.left) < minest && fabs(rt1.right-rt2.right) < minest && fabs(rt1.bottom-rt2.top) < minest) 
		{
			rt1.bottom = rt2.bottom;
			bFlag = TRUE;
		}
		return bFlag;
	}
};

//磨边结构
class CRptEdge
{
public:
	double	left;				//左边磨边量
	double  bottom;				//下边磨边量（下边：是指视觉上的下边）
	double  right;				//右边磨边量
	double  top;				//上边磨边量
public:
	CRptEdge( ) { }
	CRptEdge( double l, double t, double r, double b ) { left = l; top = t; right = r; bottom = b; }
	CRptEdge( const CRptEdge& edge) {	left = edge.left; top = edge.top; right = edge.right; bottom = edge.bottom; }
	CRptEdge& operator=(const CRptEdge& edge) { left = edge.left; top = edge.top; right = edge.right; bottom = edge.bottom; \
		return *this; }
	//重载->运算符
	//CRptEdge* operator->( ) { return this; }
};	

class CRptTrim : public CObject
{
public:
	double	left;				//左边修边量
	double  bottom;				//下边修边量（下边：是指视觉上的下边）
	double  right;				//右边修边量
	double  top;				//上边修边量
public:
	CRptTrim( ) { }
	CRptTrim( double l, double t, double r, double b ) { left = l; top = t; right = r; bottom = b; }
	CRptTrim( const CRptTrim& trm) {	left = trm.left; top = trm.top; right = trm.right; bottom = trm.bottom; }
	CRptTrim& operator=(const CRptTrim& trm) { left = trm.left; top = trm.top; right = trm.right; bottom = trm.bottom; return *this; }
	//重载->运算符
	//CRptTrim* operator->( ) { return this; }
};


//异形结构
class CRptShape
{
public://当旋转时异形中心点ptCenter要变(正方形当然就不会变，但是也当做变了计算)，摆放方式bOriLay要变,矩形框rtHolder要变
	CRptPoint	ptOffset;			//异形基准点
	CRptPoint	ptCenter;			//异形中心点
	CRptTrim	trm;				//异形修边
	CString		strName;			//异形编号
	CString		strShape;			//异形
	CRptRect	rtHolder;			//容纳异形的矩形框
	BOOL		bChanged;			//是否按库中原样摆放异形
public:
	CRptShape( ) { };
	CRptShape( CRptPoint ptoffset, CRptPoint ptcenter, CRptTrim initTrm, CString strname, CString strShp, CRptRect rtholder, BOOL bflag ) { \
		ptOffset = ptoffset; ptCenter = ptcenter; trm = initTrm; strName = strname; strShape = strShp; rtHolder = rtholder; bChanged = bflag; }
	CRptShape( const CRptShape& shp ) { ptOffset = shp.ptOffset; ptCenter = shp.ptCenter; trm = shp.trm; \
		strName = shp.strName; strShape = shp.strShape; rtHolder = shp.rtHolder; bChanged = shp.bChanged; }
	//CString Rotate(double fBeginAngle, double fRotateAngel, const CRptShape& shp);		//旋转异形
	//void Move(double x, double y) {	ptOffset.x += x; ptOffset.y += y; ptCenter.x += x; ptCenter.y += y;	}		//平移
};

//成品异形结构
class CRptShpDmsn
{
public:
	double		dLen;			   //异形所在矩形的长
	double		dWid;		       //异形所在矩形的宽
	CRptTrim	trm;			   //异形的修边
	CString		strName;		   //异形的编号,类似于“5-105”
	CString		strShapeDmsn;	   //异形的绘制信息
	BOOL		bInit;			   //图库中矩形的摆放模式:横向长>宽 TRUE；纵向长<=宽 FALSE
	BOOL		bChanged;		   //异形在原片上的排列方式（用这个参数和bInit作比较，就可以判断出异形是否需要旋转）
public:
	CRptShpDmsn( ) { }
	CRptShpDmsn( double len, double wid, CRptTrim initTrm, CString name, CString strShpDmsn, BOOL binit, BOOL bFlag ) { dLen, dWid = wid, \
		trm = initTrm; strName = name; strShapeDmsn = strShpDmsn; bInit = binit; bChanged = bFlag; }
	CRptShpDmsn( const CRptShpDmsn& shpDmsn ) { dLen = shpDmsn.dLen; dWid = shpDmsn.dWid; trm = shpDmsn.trm; strName = shpDmsn.strName;	\
		strShapeDmsn = shpDmsn.strShapeDmsn; bInit = shpDmsn.bInit; bChanged = shpDmsn.bChanged; }
	CString RotateShape( double fBeginAngle, double fRotateAngel, const CString& strShape );
};

//成品矩形结构
class CRptDmsn
{
public:
	int				nLocNoDmsn;		 //定位号
	double			dLenDmsn;		 //长度
	double			dWidDmsn;		 //宽度
	int				nNumDmsn;		 //数量
	CRptEdge		edDmsn;			 //磨边
	BOOL			bShape;			 //是否异形				（新添加）
	CRptShpDmsn		shapeDmsn;		 //异形结构				（新添加）
	CString			strCustName;	 //客户名
	CString			strOrderNo;		 //订单号
	CString			strExplntn;		 //注释
public:
	CRptDmsn( ) { }
	CRptDmsn( int locNo, double len, double wid, int num, CRptEdge edge, BOOL flag, CRptShpDmsn shpdmsn, CString custName, CString orderNo, CString explntn ) : \
		nLocNoDmsn(locNo), dLenDmsn(len), dWidDmsn(wid), nNumDmsn(num), edDmsn(edge), bShape(flag), shapeDmsn(shpdmsn), strCustName(custName), strOrderNo(orderNo), \
		strExplntn(explntn)
	{
	}
	CRptDmsn( const CRptDmsn& dmsn ) 
	{ 
		nLocNoDmsn  = dmsn.nLocNoDmsn;
		dLenDmsn    = dmsn.dLenDmsn;
		dWidDmsn    = dmsn.dWidDmsn;
		nNumDmsn    = dmsn.nNumDmsn;
		edDmsn	    = dmsn.edDmsn;
		bShape		= dmsn.bShape;
		shapeDmsn   = dmsn.shapeDmsn;
		strCustName = dmsn.strCustName;
		strOrderNo  = dmsn.strOrderNo;
		strExplntn  = dmsn.strExplntn;
	}
	//重载->运算符
	//CRptDmsn* operator->( ) { return this; }
};

//原片矩形结构
class CRptRaw
{
public:
	double		dLenRaw;		 //长度
	double		dWidRaw;		 //宽度
	int			nNum;		     //原片数量
	CRptTrim	trm;			 //修边信息
	double		dMinDis;		 //最小距离
	double		dSafeDis;		 //安全下刀距离

public:
	CRptRaw( ) { }
	CRptRaw( double len, double wid, int num, CRptTrim trmm, double minDis, double safeDis) { dLenRaw = len; dWidRaw = wid; \
		nNum = num; trm = trmm; dMinDis = minDis; dSafeDis = safeDis; }
	CRptRaw( const CRptRaw& raw ) { dLenRaw = raw.dLenRaw; dWidRaw = raw.dWidRaw; trm = raw.trm; dMinDis = raw.dMinDis; \
		dSafeDis = raw.dSafeDis; nNum = raw.nNum; }
	CRptRaw& operator=( const CRptRaw& raw ) { dLenRaw = raw.dLenRaw; dWidRaw = raw.dWidRaw; nNum = raw.nNum; trm = raw.trm; \
		dMinDis = raw.dMinDis; dSafeDis = raw.dSafeDis;  return *this; }
};

class CRawRect
{
public:
	CRptRect	rt;				 //原片矩形
	int			nNum;		     //原片数量
	CRptTrim	trm;			 //修边信息
	double		dMinDis;		 //最小距离
	double		dSafeDis;		 //安全下刀距离
public:
	CRawRect( ) { }
	CRawRect( CRptRect initRt, int num, CRptTrim trmm, double minDis, double safeDis) { rt = initRt; nNum = num; trm = trmm; dMinDis = minDis; dSafeDis = safeDis; }
	CRawRect( const CRawRect& raw ) { rt = raw.rt; trm = raw.trm; dMinDis = raw.dMinDis; dSafeDis = raw.dSafeDis; nNum = raw.nNum; }
	CRawRect& operator=( const CRawRect& raw ) { rt = raw.rt; nNum = raw.nNum; trm = raw.trm; dMinDis = raw.dMinDis; dSafeDis = raw.dSafeDis;  return *this; }
};

//成品矩形
class CNoRect
{
public:
	CRptEdge edge;  			 //磨边信息
	CRptRect rt;				 //位置信息
	int nLocNo;					 //定位号
	BOOL	bShape;				 //是否异形				（新添加)
	CRptShape shape;			 //异形信息				（新添加）	
	CString strCustName;		 //客户名
	CString strOrderNo;			 //订单号
	CString strExplntn;			 //注释
public:
	CNoRect( ) { }
	CNoRect( CRptEdge initEdge, CRptRect initRt, int initLocNo, BOOL flag, CRptShape shp, CString custName, CString orderNo, CString explntn) : \
		edge(initEdge), rt(initRt), nLocNo(initLocNo), bShape(flag), shape(shp), strCustName(custName), strOrderNo(orderNo), strExplntn(explntn)
	{
	}
	CNoRect( const CNoRect& rtNoRect)
	{
		edge = rtNoRect.edge;
		rt = rtNoRect.rt;
		nLocNo = rtNoRect.nLocNo;
		bShape = rtNoRect.bShape;
		shape = rtNoRect.shape;
		strCustName = rtNoRect.strCustName;
		strOrderNo = rtNoRect.strOrderNo;
		strExplntn = rtNoRect.strExplntn;
	}
	CNoRect& operator=( const CNoRect& rtNoRect )
	{
		edge = rtNoRect.edge;
		rt = rtNoRect.rt;
		nLocNo = rtNoRect.nLocNo;
		bShape = rtNoRect.bShape;
		shape = rtNoRect.shape;
		strCustName = rtNoRect.strCustName;
		strOrderNo = rtNoRect.strOrderNo;
		strExplntn = rtNoRect.strExplntn;
		return *this;
	}
};

class CRestRect
{
public:
	int nNo;					 //编号
	CRptRect rt;				 //位置信息					
public:
	CRestRect(int no, CRptRect initRt) : nNo(no), rt(initRt) { }
	CRestRect( const CRestRect& rtRest ) { nNo = rtRest.nNo; rt = rtRest.rt; }
	CRestRect& operator=( const CRestRect& rtRest ){ nNo = rtRest.nNo; rt = rtRest.rt; }
};

//排版方案图
class CRptDgm
{
public:
	int			nDgmNo;							//图号
	int			nCutTimes;						//切割次数
	CRawRect	rtRaw;							//原片尺寸
	double utilization;							//利用率
	CList<CNoRect*, CNoRect*>*	 pRtLay;		//已排列矩形件链表
	CList<CRawRect*, CRawRect*>* pRtRest;		//余料链表
	CList<CRptLine*, CRptLine*>* pLnTrack;		//切割路径链表
public:
	CRptDgm( ) { }
	CRptDgm( int dgmNo, int cutTimes, CRawRect raw, double util = 0.0, CList<CNoRect*, CNoRect*>*	 pRtLay = NULL, \
		CList<CRawRect*, CRawRect*>* pRtRest = NULL, CList<CRptLine*, CRptLine*>* pLnTrack = NULL) 
	{
		this->nDgmNo		= dgmNo, 
		this->nCutTimes		= cutTimes, 
		this->rtRaw			= raw, 
		this->utilization	= util; 
		this->pRtLay		= pRtLay;
		this->pRtRest		= pRtRest;
		this->pLnTrack		= pLnTrack;
	}

	//计算每张原片优化率
	double GetUtilization() 
	{
		double dEfficient = 0.0;
		double dUsedArea = 0.0;
		//累加使用面积，然后除以总面积
		POSITION pos = pRtLay->GetHeadPosition();
		CNoRect *pNoRt = NULL;
		while (pos != NULL) 
		{
			pNoRt = (CNoRect*)pRtLay->GetAt(pos);
			dUsedArea += pNoRt->rt.Width() * pNoRt->rt.Height();
			pRtLay->GetNext( pos );
		}
		//除数不能为0
		ASSERT( fabs(rtRaw.rt.Width()*rtRaw.rt.Height() - 0.0) > pow(10, -3) );
		dEfficient = dUsedArea / ( rtRaw.rt.Width()*rtRaw.rt.Height() );
		return dEfficient;
	}
};


#endif // !defined(AFX_RTOPT_H__B4B357DD_CC73_43BD_AAEC_49D441B705F7__INCLUDED_)
