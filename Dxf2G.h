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

//�������ֱ��
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
//��������岹
struct tagSect
{
	int				nSect;
	POSITION		m_pos;	/* �岹����� */
	int				nLayer;	/* ֱ�ߵ���ɫ */
	tagSect			*Next;
	tagSect			*Prev;
};
typedef struct tagSect Sect, *PSect;

//��������岹
struct tagObList
{
	int				nIndex;		/* �岹���� */
	Position		m_posBegin;	/* �岹����� */
	Position		m_posEnd;	/* �岹���յ� */
	PSect			m_Sect;		/* һ�������Ĳ岹 */
	BOOL			bClose;		/* �Ƿ�պϣ�TRUE���պϣ�FALSE�����պ� */
	int				ndirect;	/* �պ�˳ʱ�룺-1���պ���ʱ�룺1�����պϣ�0 */
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
	
	Position m_Point[2000];//�����洢�ļ��еĵ�

	int m_nPoint;	//��¼һ���ж��ٸ���
	int m_nRuler;
	
	float	m_fPutDegree;
	
	/* wzh */
	Position m_positionEnd;		//wjl,��¼��һ��ͼ�εĽ���λ��
	/* wzh */
	
    int         m_iMaxLayer;
	CObList		m_EntityList;  //ͼԪ��������
	ObList		m_stuObList;		/* �Բ岹Ϊ��λ�����ݽṹ */
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
	//ʽ��
	POSITION GetBasePoint(Position relPoint,double fEndAngle, BOOL nSeprate=FALSE);
	/*�õ���ǰͼ�����С��*/
	POSITION GetMinPoint(int layer,Position relPoint);


	double GetDis(Position pos1, Position pos2);
	double GetDis(double x1, double y1, double x2, double y2);
	//����·������ļ�
	void SettleByLeastDis();	/* ����̾������� */
	void SettleByDxfPoint();	/* ��DXFͼ�λ������� */
	
	
	int Sort();
	void SortPoint();	/* ��DXFͼ���еĵ����������� */
	void SortVPPoint();	/* ��CObList�е���������Ϊ�Բ岹Ϊ��λ�����ݽṹ */
	void Sort_CW();		//˳ʱ��
	void Sort_CCW();	//��ʱ��
	void Sort_Color();	//����ɫ

	int outGCode(char * chPath);
	int OutGlassGCode(char * chPath);
	

	PObList AddObList(PObList pCurr);	//����һ���ṹ
	PObList DeleteObList(PObList pOblist);  //����һ���ṹ
	void FreeObList();                      //��������ʱ�������չ��Ĳ���ȫ��ɾ��
	PSect AddSect(PSect pCurr);			//����һ������
	//* �պ�˳ʱ�룺-1���պ���ʱ�룺1�����պϣ�0;�жϲ���ȫ׼ȷ�����һ����֤ */
	int GetDirect(PSect pHeadSect);		
	/* ��������ĽǶ� */
	double PointToPointAngle(double dBeginX,double dBeginY,double dEndX,double dEndY);
	/* Calculate the traverse angle of an arc segment */
	double CalculateTraverseAngle(int nType, double fBeginAngle, double fEndAngle);
	/* ��ת���ͼ�� */
	void ReverseSect(PObList pTempObList);
	/* �ϲ����нṹ����ӵ����� */


	
	void CombinationData();
	/* ��ȡ��һ������յĽṹ */
	PObList GetNextNoCloseOblist(PObList pCurr);
	/* �ж��Ƿ�����ӵ� */
	int JudgeConnect(PObList pFirst, PObList pSecond);
	/* ��ȡ���һ��PSect��� */
	PSect GetLastSect(PObList pCurr);
	/* ������������ӵĲ岹�ϲ�Ϊһ�� */
	PObList CombinationOblist(int nConn, PObList pFirst, PObList pSecond);
		
	CString m_strDown;
	CString m_strUp;
	CString m_strHead;
	CString m_strTail;
	CString m_strHome;
	BOOL    m_nSort;/* �Ƿ�ʹ������1��ʹ�ã�0������ */
	int		m_iWay; /* 0:��ɫ�����̣��棻�죺˳ʱ�룩��1����ʱ�룻2��˳ʱ�� */
	int		m_nSortBy; /* 0:����㣻1������� */
	double  m_dFeedrate;
	double	m_dScale;
};

#endif // !defined(AFX_DXF2G1_H__630BA899_C69D_4A84_9A80_7D8E04E3674E__INCLUDED_)
