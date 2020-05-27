// MachineDll.h: interface for the CMachineDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MACHINEDLL_H__EFEA823D_EB59_4D6C_96D3_A8693F99F65A__INCLUDED_)
#define AFX_MACHINEDLL_H__EFEA823D_EB59_4D6C_96D3_A8693F99F65A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define PULSE_USER        4  /*���嵱��              */
#define JOURNEY_POSITIVE  6  /*��������г�          */
#define JOURNEY_NEGATIVE  7  /*��ķ����г�          */
#define BACKLASH          8  /*��ļ�϶����ֵ        */ 
#define FEED_RATE         16 /*�����ٶ�              */
#define VACC              17 /*�������ٶ�            */
#define VDEC              18 /*�������ٶ�            */
#define RAPID_MOVE        19 /*���ٶ�λ�ٶ�          */
#define ACC               20 /*���ٶ�λ���ٶ�        */
#define DEC               21 /*���ٶ�λ���ٶ�        */
#define ZEROOFFSET        22 /*�����ƫ��            */
#define HANDSPEED         23 /*�ֶ��ٶ�              */
#define ZEROSPEED         24 /*�����ٶ�              */
#define ZERODIRECTION     25 /*���㷽��              */
#define SSPARE            26 /*���ö�����            */
#define SSPAREA           261 /*���ö�����            */
#define SSPAREB           262 /*���ö�����            */
#define SSPAREC           263 /*���ö�����            */
#define SSPARED           264 /*���ö�����            */
#define SSPAREE           265 /*���ö�����            */
#define LSPARE            27 /*���ó�����            */
#define LSPAREA           271 /*���ó�����            */
#define LSPAREB           272 /*���ó�����            */
#define LSPAREC           273 /*���ó�����            */
#define LSPARED           274 /*���ó�����            */
#define LSPAREE           275 /*���ó�����            */
#define DSPAREA           28 /*����˫������          */
#define DSPAREB           29 /*����˫������          */
#define DSPAREC           30 /*����˫������          */
#define DSPARED           31 /*����˫������          */
#define DSPAREE           32 /*����˫������          */
#define BSPARE            33 /*���ö�����            */
#define BSPAREA           331 /*���ö�����            */
#define BSPAREB           332 /*���ö�����            */
#define BSPAREC           333 /*���ö�����            */
#define BSPARED           334 /*���ö�����            */
#define BSPAREE           335 /*���ö�����            */


struct tagAXIS
{
	double           d_pulse_user;                       /* ���嵱�� */   
	long             l_Journey_positive;                 /* �����г� */
	long             l_Journey_negative;                 /* �����г� */
	long             l_Backlash;                         /* ��϶���� */
	double           d_rapid;                            /* ��λ�ٶ� */
	double           d_acc;                              /* ��λ���ٶ� */
	double           d_dec;                              /* ��λ���ٶ� */   
	double           d_feedrate;                         /* �����ٶ� */   
	double           d_vacc;                             /* �������ٶ� */
	double           d_vdec;                             /* �������ٶ� */ 
	double           d_ZeroOffset;                       /* ���ƫ�� */
	double           d_handspeed;                        /* �ֶ��ٶ� */
	double           d_zerospeed;                        /* �����ٶ� */
	long             l_zerodirection;                    /* ���㷽�� */
	BOOL			bSpare;
	BOOL			bSpareA;
	BOOL			bSpareB;
	BOOL			bSpareC;
	BOOL			bSpareD;
	BOOL			bSpareE;
	short int        sSpare;
	short int        sSpareA;
	short int        sSpareB;
	short int        sSpareC;
	short int        sSpareD;
	short int        sSpareE;
	long             lSpare;
	long             lSpareA;
	long             lSpareB;
	long             lSpareC;
	long             lSpareD;
	long             lSpareE;
	double           dSpareA;
	double           dSpareB;
	double           dSpareC;
	double           dSpareD;
	double           dSpareE;
}; 
typedef struct tagAXIS AXIS, *PAXIS;


struct tagCONTROLLER
{
	AXIS		axis[8];
};
typedef struct tagCONTROLLER CONTROLLER, *PCONTROLLER;

class AFX_EXT_CLASS CMachineDll : public CObject  
{
protected:
	CONTROLLER	controller;

	double  d_number[8];
	long    l_number[8];
	long    language;       //����ѡȡ	
public:
	CMachineDll();
	virtual ~CMachineDll();
	long ParameterRead(char * chPath);

/* ��ȡ������Ϣ���е����ݣ���ParameterRead���� */
	void OnGetNumber(CString buf); 

/* ����е����������ļ� */
/* CString parfile  Ҫ�������ļ��� */
/* ����ֵ  1���ɹ�   0��ʧ�� */
	long ParameterSave(char * chPath);

/* ����ֵ 1���ɹ�����  0����Ч���� */
	long SetMachine_d(int axis,int item,double num[4]);

/* ����Ӧ�ó���ʹ�õĽ������� */
	void SetLanguage(long lan);

/* ��ȡӦ�ó���ʹ�õĽ������� */
/*����ֵ		1   ���� */
/*����ֵ        2   Ӣ�� */
	long GetLanguage();

/* ��ȡA��Ļ�е�����ṹ */
	PCONTROLLER GetController();

	long SetMachine_b(int axis,int item,BOOL num);
};

#endif // !defined(AFX_MACHINEDLL_H__EFEA823D_EB59_4D6C_96D3_A8693F99F65A__INCLUDED_)
