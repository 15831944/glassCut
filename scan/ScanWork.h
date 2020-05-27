// ScanWork.h: interface for the CScanWork class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCANWORK_H__2C6535FE_64A2_45B5_B1DD_BF0419DF413F__INCLUDED_)
#define AFX_SCANWORK_H__2C6535FE_64A2_45B5_B1DD_BF0419DF413F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ScanAct.h"


#define WM_SCANSEND		WM_USER+131	/* 接收主窗口发送消息 */
#define WM_SCANNEXT		WM_USER+132	/* 接收主窗口发送消息 */
#define WM_SENDSCAN		WM_USER+133	/* 向主窗口发送消息，报告状态 */


struct CScanThreadInfo 
{
	BOOL		bRun;
	CScanAct	*pScanAct;
	double		dRight;
	double		dLeft;
	double		dTop;
	double		dBottom;
	double		dCenterX;
	double		dCenterY;
	bool        bRuning;
};


/* 自动测量过程 */
UINT SendCommand(LPVOID pParam);

/*-------------------------------------------------------------------------*/
class AFX_EXT_CLASS CScanWork : public CObject 
{
public:
	CScanWork();
	virtual ~CScanWork();

	//传进来控制器的指针
	void SetPDmcWin(long pDmc);	

	//传进来窗口的指针
	void SetWindow(CWnd *pWnd);		
	
	//设置包含玻璃片的矩形
	void SetIncludeRect(double dTop, double dBottom, double dLeft, double dRight);

	//设置玻璃的大概中心点
	void SetCenterPoint(double dCenterX, double dCenterY);

	//设置扫描起点
	void SetStartPoint(double dStartX, double dStartY);

	//设置扫描间距
	void SetScanPace(double dPace);

	/* XY两轴正半轴的夹角 */
	void SetScanCoorDegree(double dDegree);

	/* 回零时要经过换刀点，以免撞到模具 */
	void SetScanZeroPos(double dZeroX, double dZeroY);
	
	/* 设置扫描点左右的距离 */
	void SetScanDistance(long nInSide, long nOutSide);
	
	long Run();
	void Stop();
	void SaveScanFile2G(char * chFileName);

	//InFormat=1 cid;InFormat=2 dxf
	void SaveScanPosition(char * chFileName,int InFormat);
	
	/* 设置加工工艺，根据工艺写G code and DXF */
	void SetProcessingTechnic(BOOL bOiling, BOOL bFans, BOOL bLoopAround);
	/* 获取加工数据 */
	pScanPosition GetScanData();
	
	/* 设置脉冲当量 */
	void SetResolution(double dResX, double dResY);
	
	/* 设置每伏电压的速度 */
	void SetVoltSpeed(double dVoltX, double dVoltY);

	//返回扫描的状态
	bool GetRunState();
	
protected:
	
	CScanThreadInfo	m_ScanInfo;
	CScanAct		clsScanAct;
	CWinThread		*m_Thread;
};

#endif // !defined(AFX_SCANWORK_H__2C6535FE_64A2_45B5_B1DD_BF0419DF413F__INCLUDED_)
