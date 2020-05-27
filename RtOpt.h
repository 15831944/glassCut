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
//�������Ƚϴ�С
const double minest = 0.01;
const int MAX = 5000;

class AFX_EXT_CLASS CRtOpt
{
public:
	CRtOpt();
	virtual ~CRtOpt();
	//��ʼ��ԭʼ����(����Dll�ⲿ���������Ԫ�ر�����m_pLstRaw��m_pLstPro��)
	void InitRawList(CList<CRptRaw*, CRptRaw*>& lstRaw);
	void InitProList(CList<CRptDmsn*, CRptDmsn*>& lstPro);
	//��ȡÿ��ͼ�����е�����
	CList<CRptDgm*, CRptDgm*>* GetDgmList();
	CList<CRptRaw*, CRptRaw*>* GetRawList();
	CList<CRptDmsn*, CRptDmsn*>* GetDmsnList();

	//��ȡ�иʽ
	int		GetCutMean() { return m_nCutMean; }				
	//�����иʽ
	int 	SetCutMean(int nMean)	
	{
		ASSERT( nMean==1 || nMean==0 );
		if ( nMean==0 && nMean==1 ) 
		{
			m_nCutMean = nMean;
			return 0;	//���óɹ�
		}
		else
			return -1;	//����ʧ��
	}

	//�Ż�ͼ�� 
	int Arrange();		//����1��ʾԭƬ��Ŀ����,2��ʾm_pLstRawEach�����ͷԪ��POSITIONΪ��
	
	//����G����
	BSTR WriteGCode(CString strFileName);
	
	//��������G����
	CString GenShapeGCode( CString strCmd, CRptShape shape, CRawRect rtRaw );
	
	//��ת����
	CString RotateSelect(double fBeginAngle, double fRotateAngel, CRptRect rt, CString strCmd);		

	//���������Ż���
	double GetUtil();

	//�������Ԫ�أ�ָ�������ָ�벻�ÿ�
	void Clear();

	//��ӡ����
	void print(CList<CRptRaw*, CRptRaw*>* pLst, int idx);
	void print(CList<CRptDmsn*, CRptDmsn*>* pLst, int idx = -1);
	void print(CList<CRptDgm*, CRptDgm*>* pLst, int idx);

private:
	void Sort(CList<CRptDmsn*, CRptDmsn*>* pLstPro);							//�Գ�Ʒ���ν�������
	void SwapPro(CList<CRptDmsn*, CRptDmsn*>* pLstPro);							//��lstPro�����п���ڳ���Ԫ�أ��������Ϳ�
	BOOL Elicitation(CRawRect *pRtRaw, POSITION posPro);						//��ÿ��ԭƬ�����о���
	void LayRect(CRawRect *pRtRaw, POSITION posPro, int nMean, int num);		//�ھ���rt������nMean��ʽ����num��dmsnͼ��
	
	int  BigEngh(CRptRect rt, CRptDmsn dmsn, double dMinDis, int nMean, int num);		//һ��ԭƬ�ܲ���������nMean��ʽ������numƬСƬ���������Ե�ľ��벻С��dMinDis,�˺�����δʹ��		
	int	 LayMean(CRptRect rt, CRptDmsn dmsn, double dMinDis, int& nRtNum);				//ȷ���ھ���rt����������dmsnͼ�ο��Եõ����Ե������С��������С���룩

	void HandleRestMatrl(CRawRect* pRtRaw, POSITION posPro, int nMean, int num);

	BOOL BigEnghSomePro(CRawRect rtRaw);			//rtRaw����������е���m_pLstProRt��ĳ�����εĻ�������TRUE�����򷵻�FALSE

	void AddToLstRest(CRawRect *pRtRawA);			//��pRtRawA���m_pRtRest������

	void RemoveLstPro();							//��m_pLstProRt��������ĿΪ0��Ԫ��ɾ��

	void FillRectOnRawA(CRawRect *pRtRawA);			//������pRtRawA�����о���

	void FormLnTrack(CRawRect l_rtRaw, int nMean=0);	//�γ��и�·��,0��ʾ�����и1��ʾ˫��

	BOOL DelGCodeFile(CString strDir, int nDepth, CString strProName);	//ɾ��ͬ��Ŀ����G����ͷ�ļ�

	int  GetRtRawNum();								//��ȡԭƬ����

	BOOL IsSameTrack(CList<CRptLine*, CRptLine*>* lstTrack, POSITION& posSame);		//�鿴��ԭƬ���и�켣���Ѵ��ڵİ���Ĺ켣��ͬ
	BOOL IsSameRtLay(CList<CNoRect*, CNoRect*>* lstRtLay, POSITION& posSame);		//�鿴��ԭƬ���и�켣���Ѵ��ڵİ���ľ�����ͬ(��λ��Ҳ������ͬ������ͬ)

	void ArraySortX(CRptLine* arr, int cnt);		//��CRptLine������Ԫ�ذ�X��С����(������)����
	void ArraySortY(CRptLine* arr, int cnt);		//��CRptLine������Ԫ�ذ�Y�Ӵ�С(���µ��ϡ��ӵ͵���)���� 

	void ArraySortYB2T(CRptLine* arr, int cnt);		//��CRptLine������Ԫ�ذ�Y��С����(�ӵ͵���)���� 

	//���������ͽ�
	void ArraySortNearX(CRptLine* arr, int& cnt, CRawRect l_rtRaw);		
	POSITION MinXDisByPt(CRptPoint pt, CList<CRptLine*, CRptLine*>& lstLine, BOOL bFlag);
	void ArraySortNearY(CRptLine* arr, int& cnt, CRawRect l_rtRaw);
	POSITION MinYDisByPt(CRptPoint pt, CList<CRptLine*, CRptLine*>& lstLine, BOOL bFlag);

	void AddDgmToLst(CRptDgm *pDgm);				//��m_pLstDgm��������Ӱ���

	static BOOL LE(const double& x, const double& y) { return (x<y||fabs(x-y)<minest); }
	static BOOL GE(const double& x, const double& y) { return (x>y||fabs(x-y)<minest); }

	//��ʼ����������(��ԭʼ������Ԫ�ء����ơ�һ�ݷ���m_pLstRawRt��m_pLstProRt�У�
	//˳�㽨�����й�������Ҫ��m_pRtLay,m_pRtRest,m_pLnTrack�Լ���������m_pLstDgm)
	void InitLst();
	void CopyLst(CList<CRptRaw*, CRptRaw*>* m_pLstRaw);
	void CopyLst(CList<CRptDmsn*, CRptDmsn*>* m_pLstPro);
	//���ٴ˴ξ���������ʹ�õ�����m_pLstRawRt, m_pLstProRt, m_pRtLay, m_pRtRest, m_pLnTrack
	void DestroyLst();
	
	void DelLst(CList<CRawRect*, CRawRect*>* pLstRawRt);	//����m_pLstRawEachҲ���õĴ˺���
	void DelLst(CList<CRptDmsn*, CRptDmsn*>* m_pLstProRt);
	void DelLst(CList<CNoRect*,	 CNoRect*>*	 m_pRtLay);
	void DelLst(CList<CRptDgm*, CRptDgm*>*   pLstDgm);
	void DelLst(CList<CRptLine*, CRptLine*>* pLnTrack);
	
private:
	int m_nCutMean;		//�иʽ:0�����и�1˫���иĬ�ϵ���
	//��Ա����
	CList<CRptRaw*, CRptRaw*>*		m_pLstRaw;		//ԭƬ��Ϣ����
	CList<CRptDmsn*, CRptDmsn*>*	m_pLstPro;		//��Ʒ��Ϣ����

	//һ���㷨������һ����������
	//�Ż�ǰ��
	CList<CRawRect*, CRawRect*>*	m_pLstRawRt;	//ԭƬ��������		����ʵ�֣�
	CList<CRptDmsn*, CRptDmsn*>*	m_pLstProRt;	//��Ʒ��������		����ʵ�֣�
	//�Ż��У�
public:
	CList<CRawRect*, CRawRect*>*	m_pLstRawEach;	//��ʱԭƬ����		����ʵ�֣�
	CList<CNoRect*,	 CNoRect*>*		m_pRtLay;		//�����о��μ�����  ����ʵ�֣�
	CList<CRawRect*, CRawRect*>*	m_pRtRest;		//��������			����ʵ�֣�
	CList<CRptLine*, CRptLine*>*	m_pLnTrack;		//�и�·������		����ʵ�֣�
	//�Ż���
	//��m_pRtLay��m_pRtRest��m_pLnTrack��ָ�����m_pLstDgm�У��γ�m_pLstDgm
	CList<CRptDgm*,  CRptDgm*>*		m_pLstDgm;		//��������			����ʵ�֣�

	//��־�ļ�
	CStdioFile m_flLog;
	CString m_strLogFileName;
};

class CRptPoint
{
public:
	double x;					//x������
	double y;					//y������
public:
	CRptPoint( ) { }
	CRptPoint( double xx, double yy ) { x = xx;	y = yy; }
	CRptPoint( const CRptPoint& pt ) { x = pt.x; y = pt.y; }
	CRptPoint& operator=(const CRptPoint& pt) {	x = pt.x;	y = pt.y; return *this; }
	//����==�����
	BOOL operator ==( CRptPoint point ) const
	{
		BOOL bFlag = FALSE;
		if ( fabs(x-point.x)<minest && fabs(y-point.y)<minest ) 
		{
			bFlag = TRUE;
		}
		return bFlag;
	}
	//����!=�����
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
	CRptPoint ptStart;			//�и����
	CRptPoint ptEnd;			//�и��յ�
public:
	CRptLine( ) { };
	CRptLine( CRptPoint ptInitStart, CRptPoint ptInitEnd ) { ptStart = ptInitStart; ptEnd = ptInitEnd; }
	CRptLine( const CRptLine& line ) { ptStart = line.ptStart; ptEnd = line.ptEnd; }
	CRptLine& operator=(const CRptLine& line) { ptStart = line.ptStart; ptEnd = line.ptEnd; return *this; }

	//����==�����
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

//�Զ������
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
	//����->�����
	//const CRptRect* operator->() const { return this; }
	//����<=�����
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

	//����Ϊ��������ϵ
	BOOL LnOnUpRect( CRptLine line ) const 
	{ 
		BOOL bFlag = FALSE;
		if ( 
			 //line�;����ϱ��غϻ�����һ����top
			 (fabs(line.ptStart.x-left)<minest||line.ptStart.x>left)/*line.ptStart.x>=left*/ && \
			 (fabs(line.ptStart.x-right)<minest||line.ptStart.x<right)/*line.ptStart.x<=right*/ && \
			 fabs(line.ptStart.y-top)<minest && \

			 (fabs(line.ptEnd.x-left)<minest||line.ptEnd.x>left)/*line.ptEnd.x>=left*/ && \
			 (fabs(line.ptEnd.x-right)<minest||line.ptEnd.x<right)/*line.ptEnd.x<=right*/ && \
			 fabs(line.ptEnd.y-top)<minest || \
				
			 //line�;����±��غϻ�����һ����bottom
			 (fabs(line.ptStart.x-left)<minest||line.ptStart.x>left)/*line.ptStart.x>=left*/ && \
			 (fabs(line.ptStart.x-right)<minest||line.ptStart.x<right)/*line.ptStart.x<=right*/ && \
			 fabs(line.ptStart.y-bottom)<minest && \
			 
			 (fabs(line.ptEnd.x-left)<minest||line.ptEnd.x>left)/*line.ptEnd.x>=left*/ && \
			 (fabs(line.ptEnd.x-right)<minest||line.ptEnd.x<right)/*line.ptEnd.x<=right*/ && \
			 fabs(line.ptEnd.y-bottom)<minest || \

			 //line�;�������غϻ�����һ����bottom
			 (fabs(line.ptStart.y-bottom)<minest||line.ptStart.y<bottom)/*line.ptStart.y<=bottom*/ && \
			 (fabs(line.ptStart.y-top)<minest||line.ptStart.y>top)/*line.ptStart.y>=top*/ && \
			 fabs(line.ptStart.x-left)<minest &&

			 (fabs(line.ptEnd.y-bottom)<minest||line.ptEnd.y<bottom)/*line.ptEnd.y<=bottom*/ && \
			 (fabs(line.ptEnd.y-top)<minest||line.ptEnd.y>top)/*line.ptEnd.y>=top*/ && \
			 fabs(line.ptEnd.x-left)<minest || \

			 //line�;����ұ��غϻ�����һ����bottom
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
	

	//����Ϊ��������ϵ
	BOOL LnOnDownRect( CRptLine line ) const 
	{ 
		BOOL bFlag = FALSE;
		if ( 
			//line�;����ϱ��غϻ�����һ����top
			(fabs(line.ptStart.x-left)<minest||line.ptStart.x>left)/*line.ptStart.x>=left*/ && \
			(fabs(line.ptStart.x-right)<minest||line.ptStart.x<right)/*line.ptStart.x<=right*/ && \
			fabs(line.ptStart.y-top)<minest && \
			
			(fabs(line.ptEnd.x-left)<minest||line.ptEnd.x>left)/*line.ptEnd.x>=left*/ && \
			(fabs(line.ptEnd.x-right)<minest||line.ptEnd.x<right)/*line.ptEnd.x<=right*/ && \
			fabs(line.ptEnd.y-top)<minest || \
			
			//line�;����±��غϻ�����һ����bottom
			(fabs(line.ptStart.x-left)<minest||line.ptStart.x>left)/*line.ptStart.x>=left*/ && \
			(fabs(line.ptStart.x-right)<minest||line.ptStart.x<right)/*line.ptStart.x<=right*/ && \
			fabs(line.ptStart.y-bottom)<minest && \
			
			(fabs(line.ptEnd.x-left)<minest||line.ptEnd.x>left)/*line.ptEnd.x>=left*/ && \
			(fabs(line.ptEnd.x-right)<minest||line.ptEnd.x<right)/*line.ptEnd.x<=right*/ && \
			fabs(line.ptEnd.y-bottom)<minest || \
			
			//line�;�������غϻ�����һ����bottom
			(fabs(line.ptStart.y-bottom)<minest||line.ptStart.y>bottom)/*line.ptStart.y<=bottom*/ && \
			(fabs(line.ptStart.y-top)<minest||line.ptStart.y<top)/*line.ptStart.y>=top*/ && \
			fabs(line.ptStart.x-left)<minest &&
			
			(fabs(line.ptEnd.y-bottom)<minest||line.ptEnd.y>bottom)/*line.ptEnd.y<=bottom*/ && \
			(fabs(line.ptEnd.y-top)<minest||line.ptEnd.y<top)/*line.ptEnd.y>=top*/ && \
			fabs(line.ptEnd.x-left)<minest || \
			
			//line�;����ұ��غϻ�����һ����bottom
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

	//��rt2��rt1���κϲ����������rt1
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

//ĥ�߽ṹ
class CRptEdge
{
public:
	double	left;				//���ĥ����
	double  bottom;				//�±�ĥ�������±ߣ���ָ�Ӿ��ϵ��±ߣ�
	double  right;				//�ұ�ĥ����
	double  top;				//�ϱ�ĥ����
public:
	CRptEdge( ) { }
	CRptEdge( double l, double t, double r, double b ) { left = l; top = t; right = r; bottom = b; }
	CRptEdge( const CRptEdge& edge) {	left = edge.left; top = edge.top; right = edge.right; bottom = edge.bottom; }
	CRptEdge& operator=(const CRptEdge& edge) { left = edge.left; top = edge.top; right = edge.right; bottom = edge.bottom; \
		return *this; }
	//����->�����
	//CRptEdge* operator->( ) { return this; }
};	

class CRptTrim : public CObject
{
public:
	double	left;				//����ޱ���
	double  bottom;				//�±��ޱ������±ߣ���ָ�Ӿ��ϵ��±ߣ�
	double  right;				//�ұ��ޱ���
	double  top;				//�ϱ��ޱ���
public:
	CRptTrim( ) { }
	CRptTrim( double l, double t, double r, double b ) { left = l; top = t; right = r; bottom = b; }
	CRptTrim( const CRptTrim& trm) {	left = trm.left; top = trm.top; right = trm.right; bottom = trm.bottom; }
	CRptTrim& operator=(const CRptTrim& trm) { left = trm.left; top = trm.top; right = trm.right; bottom = trm.bottom; return *this; }
	//����->�����
	//CRptTrim* operator->( ) { return this; }
};


//���νṹ
class CRptShape
{
public://����תʱ�������ĵ�ptCenterҪ��(�����ε�Ȼ�Ͳ���䣬����Ҳ�������˼���)���ڷŷ�ʽbOriLayҪ��,���ο�rtHolderҪ��
	CRptPoint	ptOffset;			//���λ�׼��
	CRptPoint	ptCenter;			//�������ĵ�
	CRptTrim	trm;				//�����ޱ�
	CString		strName;			//���α��
	CString		strShape;			//����
	CRptRect	rtHolder;			//�������εľ��ο�
	BOOL		bChanged;			//�Ƿ񰴿���ԭ���ڷ�����
public:
	CRptShape( ) { };
	CRptShape( CRptPoint ptoffset, CRptPoint ptcenter, CRptTrim initTrm, CString strname, CString strShp, CRptRect rtholder, BOOL bflag ) { \
		ptOffset = ptoffset; ptCenter = ptcenter; trm = initTrm; strName = strname; strShape = strShp; rtHolder = rtholder; bChanged = bflag; }
	CRptShape( const CRptShape& shp ) { ptOffset = shp.ptOffset; ptCenter = shp.ptCenter; trm = shp.trm; \
		strName = shp.strName; strShape = shp.strShape; rtHolder = shp.rtHolder; bChanged = shp.bChanged; }
	//CString Rotate(double fBeginAngle, double fRotateAngel, const CRptShape& shp);		//��ת����
	//void Move(double x, double y) {	ptOffset.x += x; ptOffset.y += y; ptCenter.x += x; ptCenter.y += y;	}		//ƽ��
};

//��Ʒ���νṹ
class CRptShpDmsn
{
public:
	double		dLen;			   //�������ھ��εĳ�
	double		dWid;		       //�������ھ��εĿ�
	CRptTrim	trm;			   //���ε��ޱ�
	CString		strName;		   //���εı��,�����ڡ�5-105��
	CString		strShapeDmsn;	   //���εĻ�����Ϣ
	BOOL		bInit;			   //ͼ���о��εİڷ�ģʽ:����>�� TRUE������<=�� FALSE
	BOOL		bChanged;		   //������ԭƬ�ϵ����з�ʽ�������������bInit���Ƚϣ��Ϳ����жϳ������Ƿ���Ҫ��ת��
public:
	CRptShpDmsn( ) { }
	CRptShpDmsn( double len, double wid, CRptTrim initTrm, CString name, CString strShpDmsn, BOOL binit, BOOL bFlag ) { dLen, dWid = wid, \
		trm = initTrm; strName = name; strShapeDmsn = strShpDmsn; bInit = binit; bChanged = bFlag; }
	CRptShpDmsn( const CRptShpDmsn& shpDmsn ) { dLen = shpDmsn.dLen; dWid = shpDmsn.dWid; trm = shpDmsn.trm; strName = shpDmsn.strName;	\
		strShapeDmsn = shpDmsn.strShapeDmsn; bInit = shpDmsn.bInit; bChanged = shpDmsn.bChanged; }
	CString RotateShape( double fBeginAngle, double fRotateAngel, const CString& strShape );
};

//��Ʒ���νṹ
class CRptDmsn
{
public:
	int				nLocNoDmsn;		 //��λ��
	double			dLenDmsn;		 //����
	double			dWidDmsn;		 //���
	int				nNumDmsn;		 //����
	CRptEdge		edDmsn;			 //ĥ��
	BOOL			bShape;			 //�Ƿ�����				������ӣ�
	CRptShpDmsn		shapeDmsn;		 //���νṹ				������ӣ�
	CString			strCustName;	 //�ͻ���
	CString			strOrderNo;		 //������
	CString			strExplntn;		 //ע��
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
	//����->�����
	//CRptDmsn* operator->( ) { return this; }
};

//ԭƬ���νṹ
class CRptRaw
{
public:
	double		dLenRaw;		 //����
	double		dWidRaw;		 //���
	int			nNum;		     //ԭƬ����
	CRptTrim	trm;			 //�ޱ���Ϣ
	double		dMinDis;		 //��С����
	double		dSafeDis;		 //��ȫ�µ�����

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
	CRptRect	rt;				 //ԭƬ����
	int			nNum;		     //ԭƬ����
	CRptTrim	trm;			 //�ޱ���Ϣ
	double		dMinDis;		 //��С����
	double		dSafeDis;		 //��ȫ�µ�����
public:
	CRawRect( ) { }
	CRawRect( CRptRect initRt, int num, CRptTrim trmm, double minDis, double safeDis) { rt = initRt; nNum = num; trm = trmm; dMinDis = minDis; dSafeDis = safeDis; }
	CRawRect( const CRawRect& raw ) { rt = raw.rt; trm = raw.trm; dMinDis = raw.dMinDis; dSafeDis = raw.dSafeDis; nNum = raw.nNum; }
	CRawRect& operator=( const CRawRect& raw ) { rt = raw.rt; nNum = raw.nNum; trm = raw.trm; dMinDis = raw.dMinDis; dSafeDis = raw.dSafeDis;  return *this; }
};

//��Ʒ����
class CNoRect
{
public:
	CRptEdge edge;  			 //ĥ����Ϣ
	CRptRect rt;				 //λ����Ϣ
	int nLocNo;					 //��λ��
	BOOL	bShape;				 //�Ƿ�����				�������)
	CRptShape shape;			 //������Ϣ				������ӣ�	
	CString strCustName;		 //�ͻ���
	CString strOrderNo;			 //������
	CString strExplntn;			 //ע��
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
	int nNo;					 //���
	CRptRect rt;				 //λ����Ϣ					
public:
	CRestRect(int no, CRptRect initRt) : nNo(no), rt(initRt) { }
	CRestRect( const CRestRect& rtRest ) { nNo = rtRest.nNo; rt = rtRest.rt; }
	CRestRect& operator=( const CRestRect& rtRest ){ nNo = rtRest.nNo; rt = rtRest.rt; }
};

//�Ű淽��ͼ
class CRptDgm
{
public:
	int			nDgmNo;							//ͼ��
	int			nCutTimes;						//�и����
	CRawRect	rtRaw;							//ԭƬ�ߴ�
	double utilization;							//������
	CList<CNoRect*, CNoRect*>*	 pRtLay;		//�����о��μ�����
	CList<CRawRect*, CRawRect*>* pRtRest;		//��������
	CList<CRptLine*, CRptLine*>* pLnTrack;		//�и�·������
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

	//����ÿ��ԭƬ�Ż���
	double GetUtilization() 
	{
		double dEfficient = 0.0;
		double dUsedArea = 0.0;
		//�ۼ�ʹ�������Ȼ����������
		POSITION pos = pRtLay->GetHeadPosition();
		CNoRect *pNoRt = NULL;
		while (pos != NULL) 
		{
			pNoRt = (CNoRect*)pRtLay->GetAt(pos);
			dUsedArea += pNoRt->rt.Width() * pNoRt->rt.Height();
			pRtLay->GetNext( pos );
		}
		//��������Ϊ0
		ASSERT( fabs(rtRaw.rt.Width()*rtRaw.rt.Height() - 0.0) > pow(10, -3) );
		dEfficient = dUsedArea / ( rtRaw.rt.Width()*rtRaw.rt.Height() );
		return dEfficient;
	}
};


#endif // !defined(AFX_RTOPT_H__B4B357DD_CC73_43BD_AAEC_49D441B705F7__INCLUDED_)
