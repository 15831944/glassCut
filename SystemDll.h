// SystemDll.h: interface for the CSystemDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SystemDll_H__8C870958_5B11_4C90_99D0_E7B1ABA6A046__INCLUDED_)
#define AFX_SystemDll_H__8C870958_5B11_4C90_99D0_E7B1ABA6A046__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DmcWin.h"

#define       MAINENCODER                   1         /* 主编码器 */
#define       AUXILIARYENCODER              2         /* 辅助编码器 */
#define       MOTORSTATE                    3         /* 电机状态 */
#define       FORWARDSOFTLIMIT              4         /* 正向软件限位 */
#define       REVERSESOFTLIMIT              5         /* 负向软件限位 */
#define       ERRORLIMIT                    6         /* 误差限制 */   
#define       OFFONERROR                    7         /* 是否超差 */   
#define       DERIVATIVECONSTANT            8         /* 微分常数 */
#define       PROPORTIONALCONSTANT          9         /* 比例常数 */
#define       INTEQRATOR                    10        /* 积分常数 */   
#define       ACCELERATIONFEEDFORWARD       11        /* 加速度前馈 */   
#define       VELOCITYFEEDFORWARD           12        /* 速度前馈 */
#define       STEPMOTORSMOOTHING            13        /* 步进电机平滑 */
#define       INDEPENDENTTIMECONSTANT       14        /* 独立时间常数—平滑操作 */
struct tagSYS
{
	float            l_MotorType;                       /* 电机类型 */
	long             l_MainEncoder;                     /* 主编码器 */
	long             l_AuxiliaryEncoder;                /* 辅助编码器 */
	long             l_MotorState;                      /* 电机状态 */
	long             l_ForwardSoftLimit;                /* 正向软件限位 */
	long             l_ReverseSoftLimit;                /* 负向软件限位 */
	long             l_SampleTime;                      /* 采样时间（单独） */   
	long             l_ErrorLimit;                      /* 误差限制 */   
	long             l_OffOnError;                      /* 是否超差 */   
	long             l_ConfigureLimitSwitch;            /* 配置限位开关（单独） */   
	long             l_ConfigureHomeSwitch;             /* 配置回零开关（单独） */   
	double           d_DerivativeConstant;              /* 微分常数 */
	double           d_ProportionalConstant;            /* 比例常数 */
	double           d_Inteqrator;                      /* 积分常数 */   
	double           d_AccelerationFeedforward;         /* 加速度前馈 */   
	double           d_VelocityFeedforward;             /* 速度前馈 */
	double           d_StepMotorSmoothing;              /* 步进电机平滑 */
	double           d_IndependentTimeConstant;         /* 独立时间常数—平滑操作 */
	double           d_VectorTimeConstant;              /* 矢量时间常数—S曲线（单独） */   
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
/* 注意： */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* int axis 请填写1到8 */

	void SetController(long nPdmc); 
		
/* 获取Galil参数信息，将各个参数的信息写在结构中 */
PSYSCONTROLLER GetSysinfo();

/* 设置-保存Galil参数信息，将结构中的信息设在板卡中 */
/* int axis 请填写1到8，分别代表8个轴 */
void SetSysinfo(int axis);

/* 读取信息中的数值,并放在数组中 */
/*CString buf 命令的返回信息，最多包含8轴  */
/*d_num[i]  double 数组*/
/*l_num[i]  long   数组*/
/*返回值分别放在d_num[i]和l_num[i]中*/
void OnGetNum(CString buf);

/* 设置电机类型 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* float type ：1，-1，-2，2，-2.5，2.5 */
void SetMotorType(char axis,float type);

/* 获得电机类型 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* 返回值 ：1，-1，-2，2，-2.5，2.5 */
float GetMotorType(char axis);

/* 设置主编码器 */
/* 0:通用差分四倍频型 */
/* 1:通用脉冲加方向型 */
/* 2:反向差分四倍频型 */
/* 3:反向脉冲加方向型 */
/* char axis 请填写A、B、C、D、E、F、G、H */
void SetMainEncoder(char axis,long type);

/* 获得主编码器 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* 返回主编码器类型：0、1、2、3 */
long GetMainEncoder(char axis);

/* 设置辅助编码器 */
/* 0:通用差分四倍频型 */
/* 4:通用脉冲加方向型 */
/* 8:反向差分四倍频型 */
/* 12:反向脉冲加方向型 */
/* char axis 请填写A、B、C、D、E、F、G、H */
void SetAuxiliaryEncoder(char axis,long type);

/* 获得辅助编码器 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* 返回主编码器类型：0、4、8、12 */
long GetAuxiliaryEncoder(char axis);

/* 设置电机状态 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* long state  0：电机正常   1：电机关断 */
void SetMotorState(char axis,long state);

/* 获得电机状态 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* 返回值  0：电机正常   1：电机关断 */
long GetMotorState(char axis);

/* 设置正向软件限位 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* long limit 范围为-2147483648到2147483647 */
void SetForwardSoftLimit(char axis,long limit);

/* 获得正向软件限位 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* 返回值 范围为-2147483648到2147483647 */
long GetForwardSoftLimit(char axis);

/* 设置负向软件限位 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* long limit 范围为-2147483648到2147483647 */
void SetReverseSoftLimit(char axis,long limit);

/* 获得负向软件限位 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* 返回值 范围为-2147483648到2147483647 */
long GetReverseSoftLimit(char axis);

/* 设置误差极限 ER*/
/* char axis 请填写A、B、C、D、E、F、G、H */
/* long limit 范围为1到32767 */
void SetErrorLimit(char axis,long limit);

/* 获得误差极限 ER*/
/* char axis 请填写A、B、C、D、E、F、G、H */
/* 返回值 范围为1到32767 */
long GetErrorLimit(char axis);

/* 设置超差报警点状态 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* long state  0：没有超差关断功能，1：有超差关断功能 */
void SetOffOnError(char axis,long state);

/* 获得超差报警点状态 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* 返回值  0：没有超差关断功能，1：有超差关断功能 */
long GetOffOnError(char axis);

/* 设置微分常数 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* double constant 为0到4095.875*/
void SetDerivativeConstant(char axis,double constant);

/* 获得微分常数 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* 返回值 为0到4095.875*/
double GetDerivativeConstant(char axis);

/* 设置比例常数 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* double constant 为0到1023.875*/
void SetProportionalConstant(char axis,double constant);

/* 获得比例常数 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* 返回值 为0到1023.875*/
double GetProportionalConstant(char axis);

/* 设置积分常数 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* double constant 为0到2047.875*/
void SetInteqrator(char axis,double constant);

/* 获得积分常数 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* 返回值 为0到2047.875*/
double GetInteqrator(char axis);

/* 设置加速度前馈 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* double forward  0到8192  分辨率为0.25 */
void SetAccelerationFeedforward(char axis,double forward);

/* 获得加速度前馈 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* 返回值  0到8192  分辨率为0.25 */
double GetAccelerationFeedforward(char axis);

/* 设置速度前馈 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* double forward  0到8191 */
void SetVelocityFeedforward(char axis,double forward);

/* 获得速度前馈 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* 返回值  0到8191 */
double GetVelocityFeedforward(char axis);

/* 设置步进电机平滑 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* double constant 为0.5到16  分辨率为1/32 */
void SetStepMotorSmoothing(char axis,double constant);

/* 获得步进电机平滑 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* 返回值 为0.5到16  分辨率为1/32 */
double GetStepMotorSmoothing(char axis);

/* 设置独立时间常数—平滑操作 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* double constant  为0.004到1.0   分辨率为1/256 */
void SetIndependentTimeConstant(char axis,double constant);

/* 获得独立时间常数—平滑操作 */
/* char axis 请填写A、B、C、D、E、F、G、H */
/* 返回值  为0.004到1.0   分辨率为1/256 */
double GetIndependentTimeConstant(char axis);

/* 配置限位开关（单独） */
/* long limit  1：输入高电平有效 */
/* long limit  -1：输入低电平有效 */
void SetConfigureLimitSwitch(long limit);

/* 获得限位开关（单独） */
/* 返回值  1：输入高电平有效 */
/* 返回值  -1：输入低电平有效 */
long GetConfigureLimitSwitch();

/* 配置回零开关（单独） */
/* long home   1：正向运动逼近原点开关 */
/* long home   -1：反向运动逼近原点开关 */
void SetConfigureHomeSwitch(long home);

/* 获得回零开关（单独） */
/* 返回值   1：正向运动逼近原点开关 */
/* 返回值   -1：反向运动逼近原点开关 */
long GetConfigureHomeSwitch();

/* 设置采样时间（单独） */
/* long time  为125到20000  带快速控件 */
/* long time  为负数关闭内部时钟 */
/* 此参数影响速度与加减速度 */
void SetSampleTime(long time);

/* 获得采样时间（单独） */
/* 返回值  为125到20000  带快速控件 */
/* 返回值  为负数关闭内部时钟 */
/* 此参数影响速度与加减速度 */
long GetSampleTime();

/* 设置矢量时间常数—S曲线（单独） */
/* double constant 0.004到1 分辨率为1/256 */
void SetVectorTimeConstant(double constant);

/* 获得矢量时间常数—S曲线（单独） */
/* 返回值 0.004到1 分辨率为1/256 */
double GetVectorTimeConstant();

/* 将板卡参数导出文件 */
/* int axis 轴数，1到8，代表1到8轴 */
/* CString file  要创建的参数文件名 */
/* 返回值  1：文件创建/保存成功  0：失败 */
long GetGalilFile(int axis,CString file);

/* 将板卡参数文件下载执行 */
/* CString file  要下载的参数文件名 */
/* 返回值  0：文件下载/执行成功  负数：失败 */
long SetGalilFile(CString file);

/* 获取板卡参数A轴结构指针 */
PSYS GetGalilPointAxis(int i);

/* 设置电机类型 */
/* int axis 表示轴数组，从0到7  分别代表1到8轴 */
/* float type ：1，-1，-2，2，-2.5，2.5 */
void SetMotorType(int axis,float type[8]);

/* 设置主编码器 */
/*#define       MAINENCODER                   1          主编码器 */
/*#define       AUXILIARYENCODER              2          辅助编码器 */
/*#define       MOTORSTATE                    3          电机状态 */
/*#define       FORWARDSOFTLIMIT              4          正向软件限位 */
/*#define       REVERSESOFTLIMIT              5          负向软件限位 */
/*#define       ERRORLIMIT                    6          误差限制 */   
/*#define       OFFONERROR                    7          是否超差 */   
/* int axis 表示轴数组，从1到8  分别代表1到8轴 */
void SetGalil_l(int axis,int type,long num[8]);

/* 设置主编码器 */
/*#define       DERIVATIVECONSTANT            8          微分常数 */
/*#define       PROPORTIONALCONSTANT          9          比例常数 */
/*#define       INTEQRATOR                    10         积分常数 */   
/*#define       ACCELERATIONFEEDFORWARD       11         加速度前馈 */   
/*#define       VELOCITYFEEDFORWARD           12         速度前馈 */
/*#define       STEPMOTORSMOOTHING            13         步进电机平滑 */
/*#define       INDEPENDENTTIMECONSTANT       14         独立时间常数—平滑操作 */
/* int axis 表示轴数组，从1到8  分别代表1到8轴 */
void SetGalil_d(int axis,int type,double num[8]);


protected:
	
	CDMCWin     *m_pController;
	long        s_rc;
	char        s_szResponse[512];
	char        s_cmd[80];
	CString     s_szRc;

};

#endif // !defined(AFX_SystemDll_H__8C870958_5B11_4C90_99D0_E7B1ABA6A046__INCLUDED_)
