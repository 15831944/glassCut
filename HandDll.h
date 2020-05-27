// HandDll.h: interface for the CHandDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HANDDLL_H__B469996F_0BE4_4D81_9FAA_867F4C695B19__INCLUDED_)
#define AFX_HANDDLL_H__B469996F_0BE4_4D81_9FAA_867F4C695B19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DmcWin.h"


class AFX_EXT_CLASS CHandDll : public CObject  
{
protected:
	long     handrate;//手动倍率
	
	double   d_handSpeedx,d_handSpeedy,d_handSpeedz,d_handSpeedw;              //手动速度初始值设定
	double   d_zoneSpeedx,d_zoneSpeedy,d_zoneSpeedz,d_zoneSpeedw;              //回零速度初始值设定
	double   m_ResolutionX,m_ResolutionY,m_ResolutionZ,m_ResolutionW;
	int      d_zoneDirx,d_zoneDiry,d_zoneDirz,d_zoneDirw;                      //回零方向固定。
	long     Journey_posiX,Journey_posiY,Journey_posiZ,Journey_posiW;          /* 正向行程 */
	long     Journey_negaX,Journey_negaY,Journey_negaZ,Journey_negaW;          /* 负向行程 */
	double   d_zoneOffSetx,d_zoneOffSety,d_zoneOffSetz,d_zoneOffSetw;

	double   d_handSpeeda,d_handSpeedb,d_handSpeedc,d_handSpeedd;              //手动速度初始值设定
	double   d_zoneSpeeda,d_zoneSpeedb,d_zoneSpeedc,d_zoneSpeedd;              //回零速度初始值设定
	double   m_ResolutionA,m_ResolutionB,m_ResolutionC,m_ResolutionD;
	int      d_zoneDira,d_zoneDirb,d_zoneDirc,d_zoneDird;                      //回零方向固定。
	long     Journey_posiA,Journey_posiB,Journey_posiC,Journey_posiD;          /* 正向行程 */
	long     Journey_negaA,Journey_negaB,Journey_negaC,Journey_negaD;          /* 负向行程 */
	double   d_zoneOffSeta,d_zoneOffSetb,d_zoneOffSetc,d_zoneOffSetd;
	
public:
	CHandDll();
	virtual ~CHandDll();

	void handInit(long nPdmc); 
		
/*double xSpeed,double ySpeed,double zSpeed,double wSpeed ：为用户单位*/
/*函数功能：对各轴的手动速度进行设置，速度值为用户单位*/
	void handSpeedSet(double xSpeed,double ySpeed,double zSpeed,double wSpeed); 
	void handSpeedSet(double xSpeed,double ySpeed,double zSpeed,double wSpeed, double aSpeed,double bSpeed,double cSpeed,double dSpeed); 
		
/*double xSpeed,double ySpeed,double zSpeed,double wSpeed ：为用户单位*/
/*函数功能：对各轴的手动加速度进行设置，速度值为用户单位*/
	void handSpeedACSet(double xSpeed,double ySpeed,double zSpeed,double wSpeed);
	void handSpeedACSet(double xSpeed,double ySpeed,double zSpeed,double wSpeed,double aSpeed,double bSpeed,double cSpeed,double dSpeed);
	
/*double xSpeed,double ySpeed,double zSpeed,double wSpeed ：为用户单位*/
/*函数功能：对各轴的手动减速度进行设置，速度值为用户单位*/
	void handSpeedDCSet(double xSpeed,double ySpeed,double zSpeed,double wSpeed);
	void handSpeedDCSet(double xSpeed,double ySpeed,double zSpeed,double wSpeed,double aSpeed,double bSpeed,double cSpeed,double dSpeed); 
		
/*double xSpeed,double ySpeed,double zSpeed,double wSpeed ：为用户单位*/
/*函数功能：对各轴的回零速度进行设置，速度值为用户单位*/
	void zoneSpeedSet(double xSpeed,double ySpeed,double zSpeed,double wSpeed); 

/*int xDir,int yDir,int zDir,int wDir   为1或-1 */
/*函数功能：对各轴的回零方向进行设置，速度值为用户单位*/
	void zoneDirSet(int xDir,int yDir,int zDir,int wDir); 

/*int xDir,int yDir,int zDir,int wDir   为1或-1 */
/*函数功能：对各轴的回零方向进行设置，速度值为用户单位*/
	void zoneOffset(double xOffSet,double yOffSet,double zOffSet,double wOffSet); 
		
/*double xRes,double yRes,double zRes,double wRes  ：每个用户单位的脉冲数*/
/*函数功能：对各轴的脉冲当量进行设置，即每个用户单位有多少个脉冲*/
	void ResolutionSet(double xRes,double yRes,double zRes,double wRes); 
	void ResolutionSet(double xRes,double yRes,double zRes,double wRes,double aRes,double bRes,double cRes,double dRes); 
		
/*函数功能：手动倍率升高*/
	long handSpeedAdd(); 

/*函数功能：手动倍率降低*/
	long handSpeedSub(); 

/*函数功能：设置手动倍率重置速度*/
	long SetHandRateSpeed(long lRate);                

/*函数功能：返回手动倍率*/
	long GetHandRate();                /* 返回当前的手动倍率 */

/*函数功能：手动速度/速率刷新*/
	void handSpeedRefresh(); 

/*double stepper  步长值，即X轴要增加的数值，为0表示连续移动，直到ST命令*/
/*函数功能：X轴正向移动stepper，*/
	void handAxisAdd(char chAxis,double stepper); 

/*double stepper  步长值，即X轴要增加的数值，为0表示连续移动，直到ST命令*/
/*函数功能：X轴反向移动stepper，*/
	void handAxisSub(char chAxis,double stepper); 

/*int n：第n个输出点*/
/*BOOL is：TURE  SB;   FALSE  CB*/
/*函数功能：将指定的输出点置位或清除*/
	long SetOut(int n,BOOL is);

/*函数功能：获取指定的输出点的状态*/
/*返回值：1  有输出，0  无输出*/
	long GetOut(int n);                //获取输出点的状态;
	
	/*函数功能：获取指定的输出点的状态*/
	/*返回值：1  有输出，0  无输出*/
	long GetGroupOut(int n);                //获取输出点的状态;
	
/*函数功能：获取指定的输入点的状态*/
/*返回值：1  有输入，0  无输入*/
	long GetIn(int n);                 //获取输入点的状态;

	/*函数功能：获取指定的输入点的状态*/
	/*返回值：1  有输入，0  无输入*/
	long GetGroupIn(int n);                 //获取输入点的状态;
	
/*函数功能：运动停止*/
	long OnStop();

	long SetJourneyPositive(long jourX,long jourY,long jourZ,long jourW);      //获得输入点的状态;
	long SetJourneyPositive(long jourX,long jourY,long jourZ,long jourW,long jourA,long jourB,long jourC,long jourD);      //获得输入点的状态;
		
	long SetJourneyNegetive(long jourX,long jourY,long jourZ,long jourW);      //获得输入点的状态;
	long SetJourneyNegetive(long jourX,long jourY,long jourZ,long jourW,long jourA,long jourB,long jourC,long jourD);      //获得输入点的状态;
		
	long Emergency();//急停
		
	long EmergencyState();//急停

    long LForLR(char axis); 

	int GetCommandInt(char *chComm);     //返回整形的命令
	
	double GetCommandFloat(char *chComm); //返回浮点数的命令    

	long GalilCommand(char *chComm);     //只下载命令

	void SwitchOutput(int nOut);     //转换输出点

	
protected:
	
	CDMCWin  *m_pController;
	long     h_rc;
	char     szhResponse[200];
	char     hcmd[80];
	CString  h_szRc;
};

#endif // !defined(AFX_HANDDLL_H__B469996F_0BE4_4D81_9FAA_867F4C695B19__INCLUDED_)
