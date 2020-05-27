/*  �ڵ�������ʹ��  */
/*  ��ʾ�̿���ʹ��  */
/*  �ڽ��ȱ�ؼ�ʹ��  */
/*  ��GridCAD�ؼ���ʹ��  */
/*  �սǹ����и�ͼ�ζ������ʼ��ֹ�ٶ� */
/*  2010-3-31���һ���޸�  */

#ifndef DATASTRUCT_H
	#define DATASTRUCT_H

typedef struct tagDOUBLEPOINT
{
	double		x;	/* ����¼��λ�� */
	double		y;
	double		z;
} DOUBLEPOINT;


typedef struct tagCADDATA
{
	DOUBLEPOINT		PointGrid;
	DOUBLEPOINT		PointPara;	/* ����¼��λ�� */
	tagCADDATA		*pNext;
	tagCADDATA		*pPrev;
} CADDATA, *PCADDATA;

typedef struct tagARCINFO
{
	DOUBLEPOINT		PosCenter;		/* Բ�� */
	DOUBLEPOINT		PosIJK;			/* Բ������������� */
	double			dBeginAngle;	/* ��ʼ�Ƕ� */
	double			dEndAngle;		/* ��ֹ�Ƕ� */
	double			dAngleSweep;	/* �н� */
}ARCINFO, *PARCINFO;


typedef struct tagGRAPH
{
	int				nIndex;			/* �ṹ��� */
	char			chLine;			/* ���ͣ�1Ϊֱ�ߣ�2Ϊ˳ʱ��Բ����3Ϊ��ʱ��Բ�� */
	PCADDATA		pPosBegin;		/* ����¼��λ�� */
	PCADDATA		pPosEnd;		/* ����¼��λ�� */
	PCADDATA		pPosMid;		/* ����¼��λ�� */
	PARCINFO		pArcInfo;		/* Բ���������Ϣ */
	double			dBeginSpeed;	/* ��ʼ����ٶ� */
	double			dEndSpeed;		/* ��ֹ����ٶ� */
	tagGRAPH		*Next;
	tagGRAPH		*Prev;
}GRAPH, *PGRAPH;


typedef struct tagGRAPHLIST
{
	int				nSort;			/* �ṹ��� */
	PCADDATA		pCadData;
	PGRAPH			pGraph;			/* ����¼��λ�� */
	int				nSplineStyle;	/* 0���ޣ�1������B�������ߡ�2�����α��������ߡ�3�������ۼ��ҳ����� */
	PCADDATA		pBSplineData;	/* �����������ߵĵ������*/
	int				nTool;			/* ָ������ */
	int				nFeed;			/* ָ�������ٶ� */
	int				nOrder;			/* ָ��˳�� */
	char			chKerfComp;		/* �������� */
	double			dToolSize;		/* �����ߴ� */
	BOOL			bClose;			/* ͼ���Ƿ�պ� */
	tagGRAPHLIST	*Next;
	tagGRAPHLIST	*Prev;
}GRAPHLIST, *PGRAPHLIST; 

#endif
/*===========================================================================*/
