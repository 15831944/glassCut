// CuttingPress.h: interface for the CCuttingPress class.
//
//////////////////////////////////////////////////////////////////////
//5.0.0.1 添加插补压力 2013.6.18
#if !defined(AFX_CUTTINGPRESS_H__A0B85E53_1AC7_41DE_AC8A_9480D481950F__INCLUDED_)
#define AFX_CUTTINGPRESS_H__A0B85E53_1AC7_41DE_AC8A_9480D481950F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TIMES	1000


struct tagPRESSURE
{
	int				nThickness;			/* 厚度 */
	double          dToolDown;			/* 下刀刀压 */
	double          dToolUp;			/* 上刀刀压 */   
	double          dLineAddPress;		/* 直线加压 */
	double          dPressXAdd;			/* X正向压力 */
	double          dPressXSub;			/* X负向压力 */   
	double          dPressYAdd;			/* Y正向压力 */
	double          dPressYSub;			/* Y负向压力 */
	double          dPressSlant;        /* 斜线插补压力 */
	double          dArcAddPress;		/* 圆弧加压 */
	double			dPressSmall;		/* 小圆弧刀压 */
	double			dPressMidle;		/* 中圆弧刀压 */
	double			dPressBig;			/* 大圆弧刀压 */
	double			dRadiusSmall;		/* 小圆弧半径 */
	double			dRadiusBig;			/* 大圆弧半径 */
	int				nArcAddTime;		/* 圆弧加压时间 */
	int				nLineAddTime;		/* 直线加压时间 */
	int				nToolDelay;			/* 下刀延迟时间 */
	int             nUpDelay;           /* 抬刀延迟时间 */ 
	int             nAfterUpDelay;      //抬刀后延迟时间
	tagPRESSURE		*pNext;
	tagPRESSURE		*pPrev;
}; 
typedef struct tagPRESSURE PRESSURE, *PPRESSURE;


class AFX_EXT_CLASS CCuttingPress  : public CObject
{
public:
	CCuttingPress();
	virtual ~CCuttingPress();

	void SetPressureFile(char * chFile);
	PPRESSURE ReadPressure();
	void SavePressure();
	void SavePressure(int nThickness);
	PPRESSURE GetPressure(int nThickness);
	PPRESSURE GetHeadPressure();
	

protected:
	CString		strFile;
	PRESSURE	Pressure;

	PPRESSURE AddTagPressure(PPRESSURE pCurr);
	void FreeTagPressure();
		
};

#endif // !defined(AFX_CUTTINGPRESS_H__A0B85E53_1AC7_41DE_AC8A_9480D481950F__INCLUDED_)
