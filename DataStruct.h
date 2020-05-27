/*  在刀补库中使用  */
/*  在示教库中使用  */
/*  在进度表控件使用  */
/*  在GridCAD控件中使用  */
/*  拐角过度中给图形段添加起始终止速度 */
/*  2010-3-31最后一次修改  */

#ifndef DATASTRUCT_H
	#define DATASTRUCT_H

typedef struct tagDOUBLEPOINT
{
	double		x;	/* 鼠标记录的位置 */
	double		y;
	double		z;
} DOUBLEPOINT;


typedef struct tagCADDATA
{
	DOUBLEPOINT		PointGrid;
	DOUBLEPOINT		PointPara;	/* 鼠标记录的位置 */
	tagCADDATA		*pNext;
	tagCADDATA		*pPrev;
} CADDATA, *PCADDATA;

typedef struct tagARCINFO
{
	DOUBLEPOINT		PosCenter;		/* 圆心 */
	DOUBLEPOINT		PosIJK;			/* 圆心相对起点的增量 */
	double			dBeginAngle;	/* 起始角度 */
	double			dEndAngle;		/* 终止角度 */
	double			dAngleSweep;	/* 夹角 */
}ARCINFO, *PARCINFO;


typedef struct tagGRAPH
{
	int				nIndex;			/* 结构序号 */
	char			chLine;			/* 类型：1为直线，2为顺时针圆弧，3为逆时针圆弧 */
	PCADDATA		pPosBegin;		/* 鼠标记录的位置 */
	PCADDATA		pPosEnd;		/* 鼠标记录的位置 */
	PCADDATA		pPosMid;		/* 鼠标记录的位置 */
	PARCINFO		pArcInfo;		/* 圆弧的相关信息 */
	double			dBeginSpeed;	/* 开始点的速度 */
	double			dEndSpeed;		/* 终止点的速度 */
	tagGRAPH		*Next;
	tagGRAPH		*Prev;
}GRAPH, *PGRAPH;


typedef struct tagGRAPHLIST
{
	int				nSort;			/* 结构序号 */
	PCADDATA		pCadData;
	PGRAPH			pGraph;			/* 鼠标记录的位置 */
	int				nSplineStyle;	/* 0：无；1：二次B样条曲线、2：二次贝塞尔曲线、3：二次累加弦长曲线 */
	PCADDATA		pBSplineData;	/* 保存样条曲线的点的数据*/
	int				nTool;			/* 指定刀具 */
	int				nFeed;			/* 指定进给速度 */
	int				nOrder;			/* 指定顺序 */
	char			chKerfComp;		/* 刀补类型 */
	double			dToolSize;		/* 刀补尺寸 */
	BOOL			bClose;			/* 图形是否闭合 */
	tagGRAPHLIST	*Next;
	tagGRAPHLIST	*Prev;
}GRAPHLIST, *PGRAPHLIST; 

#endif
/*===========================================================================*/
