// CuttingPress.h: interface for the CCuttingPress class.
//
//////////////////////////////////////////////////////////////////////
//5.0.0.1 ��Ӳ岹ѹ�� 2013.6.18
#if !defined(AFX_CUTTINGPRESS_H__A0B85E53_1AC7_41DE_AC8A_9480D481950F__INCLUDED_)
#define AFX_CUTTINGPRESS_H__A0B85E53_1AC7_41DE_AC8A_9480D481950F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TIMES	1000


struct tagPRESSURE
{
	int				nThickness;			/* ��� */
	double          dToolDown;			/* �µ���ѹ */
	double          dToolUp;			/* �ϵ���ѹ */   
	double          dLineAddPress;		/* ֱ�߼�ѹ */
	double          dPressXAdd;			/* X����ѹ�� */
	double          dPressXSub;			/* X����ѹ�� */   
	double          dPressYAdd;			/* Y����ѹ�� */
	double          dPressYSub;			/* Y����ѹ�� */
	double          dPressSlant;        /* б�߲岹ѹ�� */
	double          dArcAddPress;		/* Բ����ѹ */
	double			dPressSmall;		/* СԲ����ѹ */
	double			dPressMidle;		/* ��Բ����ѹ */
	double			dPressBig;			/* ��Բ����ѹ */
	double			dRadiusSmall;		/* СԲ���뾶 */
	double			dRadiusBig;			/* ��Բ���뾶 */
	int				nArcAddTime;		/* Բ����ѹʱ�� */
	int				nLineAddTime;		/* ֱ�߼�ѹʱ�� */
	int				nToolDelay;			/* �µ��ӳ�ʱ�� */
	int             nUpDelay;           /* ̧���ӳ�ʱ�� */ 
	int             nAfterUpDelay;      //̧�����ӳ�ʱ��
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
