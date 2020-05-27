// MachineDll.h: interface for the CMachineDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MACHINEDLL_H__EFEA823D_EB59_4D6C_96D3_A8693F99F65A__INCLUDED_)
#define AFX_MACHINEDLL_H__EFEA823D_EB59_4D6C_96D3_A8693F99F65A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define PULSE_USER        4  /*脉冲当量              */
#define JOURNEY_POSITIVE  6  /*轴的正向行程          */
#define JOURNEY_NEGATIVE  7  /*轴的反向行程          */
#define BACKLASH          8  /*轴的间隙补偿值        */ 
#define FEED_RATE         16 /*进给速度              */
#define VACC              17 /*进给加速度            */
#define VDEC              18 /*进给减速度            */
#define RAPID_MOVE        19 /*快速定位速度          */
#define ACC               20 /*快速定位加速度        */
#define DEC               21 /*快速定位减速度        */
#define ZEROOFFSET        22 /*回零点偏置            */
#define HANDSPEED         23 /*手动速度              */
#define ZEROSPEED         24 /*回零速度              */
#define ZERODIRECTION     25 /*回零方向              */
#define SSPARE            26 /*备用短整型            */
#define SSPAREA           261 /*备用短整型            */
#define SSPAREB           262 /*备用短整型            */
#define SSPAREC           263 /*备用短整型            */
#define SSPARED           264 /*备用短整型            */
#define SSPAREE           265 /*备用短整型            */
#define LSPARE            27 /*备用长整型            */
#define LSPAREA           271 /*备用长整型            */
#define LSPAREB           272 /*备用长整型            */
#define LSPAREC           273 /*备用长整型            */
#define LSPARED           274 /*备用长整型            */
#define LSPAREE           275 /*备用长整型            */
#define DSPAREA           28 /*备用双精度型          */
#define DSPAREB           29 /*备用双精度型          */
#define DSPAREC           30 /*备用双精度型          */
#define DSPARED           31 /*备用双精度型          */
#define DSPAREE           32 /*备用双精度型          */
#define BSPARE            33 /*备用短整型            */
#define BSPAREA           331 /*备用短整型            */
#define BSPAREB           332 /*备用短整型            */
#define BSPAREC           333 /*备用短整型            */
#define BSPARED           334 /*备用短整型            */
#define BSPAREE           335 /*备用短整型            */


struct tagAXIS
{
	double           d_pulse_user;                       /* 脉冲当量 */   
	long             l_Journey_positive;                 /* 正向行程 */
	long             l_Journey_negative;                 /* 负向行程 */
	long             l_Backlash;                         /* 间隙补偿 */
	double           d_rapid;                            /* 定位速度 */
	double           d_acc;                              /* 定位加速度 */
	double           d_dec;                              /* 定位减速度 */   
	double           d_feedrate;                         /* 进给速度 */   
	double           d_vacc;                             /* 进给加速度 */
	double           d_vdec;                             /* 进给减速度 */ 
	double           d_ZeroOffset;                       /* 零点偏置 */
	double           d_handspeed;                        /* 手动速度 */
	double           d_zerospeed;                        /* 回零速度 */
	long             l_zerodirection;                    /* 回零方向 */
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
	long    language;       //语言选取	
public:
	CMachineDll();
	virtual ~CMachineDll();
	long ParameterRead(char * chPath);

/* 获取命令信息行中的数据，在ParameterRead调用 */
	void OnGetNumber(CString buf); 

/* 将机械参数保存成文件 */
/* CString parfile  要创建的文件名 */
/* 返回值  1：成功   0：失败 */
	long ParameterSave(char * chPath);

/* 返回值 1：成功设置  0：无效设置 */
	long SetMachine_d(int axis,int item,double num[4]);

/* 设置应用程序使用的界面语言 */
	void SetLanguage(long lan);

/* 获取应用程序使用的界面语言 */
/*返回值		1   中文 */
/*返回值        2   英文 */
	long GetLanguage();

/* 获取A轴的机械参数结构 */
	PCONTROLLER GetController();

	long SetMachine_b(int axis,int item,BOOL num);
};

#endif // !defined(AFX_MACHINEDLL_H__EFEA823D_EB59_4D6C_96D3_A8693F99F65A__INCLUDED_)
