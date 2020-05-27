// SystemDll.h: interface for the CSystemDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SystemDll_H__8C870958_5B11_4C90_99D0_E7B1ABA6A046__INCLUDED_)
#define AFX_SystemDll_H__8C870958_5B11_4C90_99D0_E7B1ABA6A046__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DmcWin.h"

#define       MAINENCODER                   1         /* �������� */
#define       AUXILIARYENCODER              2         /* ���������� */
#define       MOTORSTATE                    3         /* ���״̬ */
#define       FORWARDSOFTLIMIT              4         /* ���������λ */
#define       REVERSESOFTLIMIT              5         /* ���������λ */
#define       ERRORLIMIT                    6         /* ������� */   
#define       OFFONERROR                    7         /* �Ƿ񳬲� */   
#define       DERIVATIVECONSTANT            8         /* ΢�ֳ��� */
#define       PROPORTIONALCONSTANT          9         /* �������� */
#define       INTEQRATOR                    10        /* ���ֳ��� */   
#define       ACCELERATIONFEEDFORWARD       11        /* ���ٶ�ǰ�� */   
#define       VELOCITYFEEDFORWARD           12        /* �ٶ�ǰ�� */
#define       STEPMOTORSMOOTHING            13        /* �������ƽ�� */
#define       INDEPENDENTTIMECONSTANT       14        /* ����ʱ�䳣����ƽ������ */
struct tagSYS
{
	float            l_MotorType;                       /* ������� */
	long             l_MainEncoder;                     /* �������� */
	long             l_AuxiliaryEncoder;                /* ���������� */
	long             l_MotorState;                      /* ���״̬ */
	long             l_ForwardSoftLimit;                /* ���������λ */
	long             l_ReverseSoftLimit;                /* ���������λ */
	long             l_SampleTime;                      /* ����ʱ�䣨������ */   
	long             l_ErrorLimit;                      /* ������� */   
	long             l_OffOnError;                      /* �Ƿ񳬲� */   
	long             l_ConfigureLimitSwitch;            /* ������λ���أ������� */   
	long             l_ConfigureHomeSwitch;             /* ���û��㿪�أ������� */   
	double           d_DerivativeConstant;              /* ΢�ֳ��� */
	double           d_ProportionalConstant;            /* �������� */
	double           d_Inteqrator;                      /* ���ֳ��� */   
	double           d_AccelerationFeedforward;         /* ���ٶ�ǰ�� */   
	double           d_VelocityFeedforward;             /* �ٶ�ǰ�� */
	double           d_StepMotorSmoothing;              /* �������ƽ�� */
	double           d_IndependentTimeConstant;         /* ����ʱ�䳣����ƽ������ */
	double           d_VectorTimeConstant;              /* ʸ��ʱ�䳣����S���ߣ������� */   
}; 
typedef struct tagSYS SYS, *PSYS;

struct tagSYSCONTROLLER
{
	SYS         s_axis[8];
};
typedef struct tagSYSCONTROLLER SYSCONTROLLER, *PSYSCONTROLLER;


class AFX_EXT_CLASS CSystemDll : public CObject
{
protected:

	SYSCONTROLLER	m_pSysController;
	
	PSYS        psysA,psysB,psysC,psysD,psysE,psysF,psysG,psysH;
	
	double      d_num[8];
	long        l_num[8];
public:
	CSystemDll();
	virtual ~CSystemDll();
/* ע�⣺ */
/* char axis ����дA��B��C��D��E��F��G��H */
/* int axis ����д1��8 */

	void SetController(long nPdmc); 
		
/* ��ȡGalil������Ϣ����������������Ϣд�ڽṹ�� */
PSYSCONTROLLER GetSysinfo();

/* ����-����Galil������Ϣ�����ṹ�е���Ϣ���ڰ忨�� */
/* int axis ����д1��8���ֱ����8���� */
void SetSysinfo(int axis);

/* ��ȡ��Ϣ�е���ֵ,������������ */
/*CString buf ����ķ�����Ϣ��������8��  */
/*d_num[i]  double ����*/
/*l_num[i]  long   ����*/
/*����ֵ�ֱ����d_num[i]��l_num[i]��*/
void OnGetNum(CString buf);

/* ���õ������ */
/* char axis ����дA��B��C��D��E��F��G��H */
/* float type ��1��-1��-2��2��-2.5��2.5 */
void SetMotorType(char axis,float type);

/* ��õ������ */
/* char axis ����дA��B��C��D��E��F��G��H */
/* ����ֵ ��1��-1��-2��2��-2.5��2.5 */
float GetMotorType(char axis);

/* ������������ */
/* 0:ͨ�ò���ı�Ƶ�� */
/* 1:ͨ������ӷ����� */
/* 2:�������ı�Ƶ�� */
/* 3:��������ӷ����� */
/* char axis ����дA��B��C��D��E��F��G��H */
void SetMainEncoder(char axis,long type);

/* ����������� */
/* char axis ����дA��B��C��D��E��F��G��H */
/* ���������������ͣ�0��1��2��3 */
long GetMainEncoder(char axis);

/* ���ø��������� */
/* 0:ͨ�ò���ı�Ƶ�� */
/* 4:ͨ������ӷ����� */
/* 8:�������ı�Ƶ�� */
/* 12:��������ӷ����� */
/* char axis ����дA��B��C��D��E��F��G��H */
void SetAuxiliaryEncoder(char axis,long type);

/* ��ø��������� */
/* char axis ����дA��B��C��D��E��F��G��H */
/* ���������������ͣ�0��4��8��12 */
long GetAuxiliaryEncoder(char axis);

/* ���õ��״̬ */
/* char axis ����дA��B��C��D��E��F��G��H */
/* long state  0���������   1������ض� */
void SetMotorState(char axis,long state);

/* ��õ��״̬ */
/* char axis ����дA��B��C��D��E��F��G��H */
/* ����ֵ  0���������   1������ض� */
long GetMotorState(char axis);

/* �������������λ */
/* char axis ����дA��B��C��D��E��F��G��H */
/* long limit ��ΧΪ-2147483648��2147483647 */
void SetForwardSoftLimit(char axis,long limit);

/* ������������λ */
/* char axis ����дA��B��C��D��E��F��G��H */
/* ����ֵ ��ΧΪ-2147483648��2147483647 */
long GetForwardSoftLimit(char axis);

/* ���ø��������λ */
/* char axis ����дA��B��C��D��E��F��G��H */
/* long limit ��ΧΪ-2147483648��2147483647 */
void SetReverseSoftLimit(char axis,long limit);

/* ��ø��������λ */
/* char axis ����дA��B��C��D��E��F��G��H */
/* ����ֵ ��ΧΪ-2147483648��2147483647 */
long GetReverseSoftLimit(char axis);

/* �������� ER*/
/* char axis ����дA��B��C��D��E��F��G��H */
/* long limit ��ΧΪ1��32767 */
void SetErrorLimit(char axis,long limit);

/* ������� ER*/
/* char axis ����дA��B��C��D��E��F��G��H */
/* ����ֵ ��ΧΪ1��32767 */
long GetErrorLimit(char axis);

/* ���ó������״̬ */
/* char axis ����дA��B��C��D��E��F��G��H */
/* long state  0��û�г���ضϹ��ܣ�1���г���ضϹ��� */
void SetOffOnError(char axis,long state);

/* ��ó������״̬ */
/* char axis ����дA��B��C��D��E��F��G��H */
/* ����ֵ  0��û�г���ضϹ��ܣ�1���г���ضϹ��� */
long GetOffOnError(char axis);

/* ����΢�ֳ��� */
/* char axis ����дA��B��C��D��E��F��G��H */
/* double constant Ϊ0��4095.875*/
void SetDerivativeConstant(char axis,double constant);

/* ���΢�ֳ��� */
/* char axis ����дA��B��C��D��E��F��G��H */
/* ����ֵ Ϊ0��4095.875*/
double GetDerivativeConstant(char axis);

/* ���ñ������� */
/* char axis ����дA��B��C��D��E��F��G��H */
/* double constant Ϊ0��1023.875*/
void SetProportionalConstant(char axis,double constant);

/* ��ñ������� */
/* char axis ����дA��B��C��D��E��F��G��H */
/* ����ֵ Ϊ0��1023.875*/
double GetProportionalConstant(char axis);

/* ���û��ֳ��� */
/* char axis ����дA��B��C��D��E��F��G��H */
/* double constant Ϊ0��2047.875*/
void SetInteqrator(char axis,double constant);

/* ��û��ֳ��� */
/* char axis ����дA��B��C��D��E��F��G��H */
/* ����ֵ Ϊ0��2047.875*/
double GetInteqrator(char axis);

/* ���ü��ٶ�ǰ�� */
/* char axis ����дA��B��C��D��E��F��G��H */
/* double forward  0��8192  �ֱ���Ϊ0.25 */
void SetAccelerationFeedforward(char axis,double forward);

/* ��ü��ٶ�ǰ�� */
/* char axis ����дA��B��C��D��E��F��G��H */
/* ����ֵ  0��8192  �ֱ���Ϊ0.25 */
double GetAccelerationFeedforward(char axis);

/* �����ٶ�ǰ�� */
/* char axis ����дA��B��C��D��E��F��G��H */
/* double forward  0��8191 */
void SetVelocityFeedforward(char axis,double forward);

/* ����ٶ�ǰ�� */
/* char axis ����дA��B��C��D��E��F��G��H */
/* ����ֵ  0��8191 */
double GetVelocityFeedforward(char axis);

/* ���ò������ƽ�� */
/* char axis ����дA��B��C��D��E��F��G��H */
/* double constant Ϊ0.5��16  �ֱ���Ϊ1/32 */
void SetStepMotorSmoothing(char axis,double constant);

/* ��ò������ƽ�� */
/* char axis ����дA��B��C��D��E��F��G��H */
/* ����ֵ Ϊ0.5��16  �ֱ���Ϊ1/32 */
double GetStepMotorSmoothing(char axis);

/* ���ö���ʱ�䳣����ƽ������ */
/* char axis ����дA��B��C��D��E��F��G��H */
/* double constant  Ϊ0.004��1.0   �ֱ���Ϊ1/256 */
void SetIndependentTimeConstant(char axis,double constant);

/* ��ö���ʱ�䳣����ƽ������ */
/* char axis ����дA��B��C��D��E��F��G��H */
/* ����ֵ  Ϊ0.004��1.0   �ֱ���Ϊ1/256 */
double GetIndependentTimeConstant(char axis);

/* ������λ���أ������� */
/* long limit  1������ߵ�ƽ��Ч */
/* long limit  -1������͵�ƽ��Ч */
void SetConfigureLimitSwitch(long limit);

/* �����λ���أ������� */
/* ����ֵ  1������ߵ�ƽ��Ч */
/* ����ֵ  -1������͵�ƽ��Ч */
long GetConfigureLimitSwitch();

/* ���û��㿪�أ������� */
/* long home   1�������˶��ƽ�ԭ�㿪�� */
/* long home   -1�������˶��ƽ�ԭ�㿪�� */
void SetConfigureHomeSwitch(long home);

/* ��û��㿪�أ������� */
/* ����ֵ   1�������˶��ƽ�ԭ�㿪�� */
/* ����ֵ   -1�������˶��ƽ�ԭ�㿪�� */
long GetConfigureHomeSwitch();

/* ���ò���ʱ�䣨������ */
/* long time  Ϊ125��20000  �����ٿؼ� */
/* long time  Ϊ�����ر��ڲ�ʱ�� */
/* �˲���Ӱ���ٶ���Ӽ��ٶ� */
void SetSampleTime(long time);

/* ��ò���ʱ�䣨������ */
/* ����ֵ  Ϊ125��20000  �����ٿؼ� */
/* ����ֵ  Ϊ�����ر��ڲ�ʱ�� */
/* �˲���Ӱ���ٶ���Ӽ��ٶ� */
long GetSampleTime();

/* ����ʸ��ʱ�䳣����S���ߣ������� */
/* double constant 0.004��1 �ֱ���Ϊ1/256 */
void SetVectorTimeConstant(double constant);

/* ���ʸ��ʱ�䳣����S���ߣ������� */
/* ����ֵ 0.004��1 �ֱ���Ϊ1/256 */
double GetVectorTimeConstant();

/* ���忨���������ļ� */
/* int axis ������1��8������1��8�� */
/* CString file  Ҫ�����Ĳ����ļ��� */
/* ����ֵ  1���ļ�����/����ɹ�  0��ʧ�� */
long GetGalilFile(int axis,CString file);

/* ���忨�����ļ�����ִ�� */
/* CString file  Ҫ���صĲ����ļ��� */
/* ����ֵ  0���ļ�����/ִ�гɹ�  ������ʧ�� */
long SetGalilFile(CString file);

/* ��ȡ�忨����A��ṹָ�� */
PSYS GetGalilPointAxis(int i);

/* ���õ������ */
/* int axis ��ʾ�����飬��0��7  �ֱ����1��8�� */
/* float type ��1��-1��-2��2��-2.5��2.5 */
void SetMotorType(int axis,float type[8]);

/* ������������ */
/*#define       MAINENCODER                   1          �������� */
/*#define       AUXILIARYENCODER              2          ���������� */
/*#define       MOTORSTATE                    3          ���״̬ */
/*#define       FORWARDSOFTLIMIT              4          ���������λ */
/*#define       REVERSESOFTLIMIT              5          ���������λ */
/*#define       ERRORLIMIT                    6          ������� */   
/*#define       OFFONERROR                    7          �Ƿ񳬲� */   
/* int axis ��ʾ�����飬��1��8  �ֱ����1��8�� */
void SetGalil_l(int axis,int type,long num[8]);

/* ������������ */
/*#define       DERIVATIVECONSTANT            8          ΢�ֳ��� */
/*#define       PROPORTIONALCONSTANT          9          �������� */
/*#define       INTEQRATOR                    10         ���ֳ��� */   
/*#define       ACCELERATIONFEEDFORWARD       11         ���ٶ�ǰ�� */   
/*#define       VELOCITYFEEDFORWARD           12         �ٶ�ǰ�� */
/*#define       STEPMOTORSMOOTHING            13         �������ƽ�� */
/*#define       INDEPENDENTTIMECONSTANT       14         ����ʱ�䳣����ƽ������ */
/* int axis ��ʾ�����飬��1��8  �ֱ����1��8�� */
void SetGalil_d(int axis,int type,double num[8]);


protected:
	
	CDMCWin     *m_pController;
	long        s_rc;
	char        s_szResponse[512];
	char        s_cmd[80];
	CString     s_szRc;

};

#endif // !defined(AFX_SystemDll_H__8C870958_5B11_4C90_99D0_E7B1ABA6A046__INCLUDED_)
