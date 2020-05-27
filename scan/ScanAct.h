// ScanAct.h: interface for the CScanAct class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCANACT_H__1124C7D3_CCD2_4626_BC55_E529151C81D8__INCLUDED_)
#define AFX_SCANACT_H__1124C7D3_CCD2_4626_BC55_E529151C81D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define PIE  3.1415926

#define SCAN_DIRECTION_CCW	FALSE	/* 逆时针 */
#define SCAN_DIRECTION_CW	TRUE	/* 顺时针 */

struct CCalPos 
{
	double			dPosX;
	double			dPosY;
};
typedef struct CCalPos CalPos, *pCalPos;

struct CScanPosition 
{
	CalPos			pos;
	CScanPosition	*pNext;
	CScanPosition	*pPrev;
};
typedef struct CScanPosition ScanPosition, *pScanPosition;


class  CScanAct : public CObject  
{
public:
	CScanAct();
	virtual ~CScanAct();

	
	CDMCWin			*m_pDmcWin;
	CWnd			*m_pWnd;
	UINT			nMsg;
	pScanPosition	m_pCurrScanPos;	/* 扫描结果的首结点 */
	CalPos			m_Begin;		/* 找寻扫描点的起点 */
	CalPos			m_Center;		/* 找寻扫描点的中心点 */
	CScanPosition	m_ScanPos;
	double			m_dScanPace;	/* 扫描步长 */
	double			m_dTempScanPace;	/* 临时扫描步长 */
	double			m_dDegreeCoor;	/* 坐标系角度 */
	
	CalPos			m_ZeroPos;		/* 找寻扫描点的起点 */
	int             m_nInterrupt;   //代替IO中断
	/* 设置锁存功能 */
	void SetArmLatch();

	/* 设置中断使能 */
	void SetEnableInterrupt();

	/* 保存数据点为G代码 */
	void SavePositions2G(char * chFileName);	

	/* 设置加工工艺，根据工艺写G code and DXF */
	void SetProcessingTechnic(BOOL bOiling, BOOL bFans, BOOL bLoopAround);

	/* 设置脉冲当量 */
	void SetResolution(double dResX, double dResY);

	/* 设置每伏电压的速度 */
	void SetVoltSpeed(double dVoltX, double dVoltY);

	/* 增加一个数据点 */
	pScanPosition SetHeadPosition(pScanPosition pHead);

	/* 增加一个数据点 */
	pScanPosition AddPosition(pScanPosition pLast);
	
	/* 释放所有数据点 */
	void FreePosition();

	/* 命令执行 */
	int RunCommand(CString strRunComm);

	/* 走到某个位置命令 */
	void RunGotoPosCommand(pCalPos pDis);

	/* 用圆弧，走到某个位置命令 */
	void RunGotoArcCommand(double dRadius, pCalPos pDis);
		
	/* 停止运行，等待运动完成 */
	void RunStopandWait(CString str);

	/* 判断锁存状态，是否锁存成功 */
	int GetArmLatch();
	
	/* 计算、估计下一个扫描点的位置，根据步长 */
	int CalNextScanPos(pScanPosition pNewPos, pCalPos pPos);

	/* 计算起点，到达起点后，设置使能 d找不到每次多走0.5毫米*/
	int CalBegin(pScanPosition pNewPos, pCalPos pPos,double d);
	
	/* 计算终点，设置使能，从起点走向终点，进行找点锁存 */
	int CalEnd(pScanPosition pNewPos, pCalPos pPos);
	
	/* 设置起点，也叫玻璃中点，第一点从零向此方向找寻 */
	void SetStartPos(pCalPos pPos);

	/* 向主窗口发送消息，报告找起点情况 */
	void DllSendMessgeToDialog(int nMsg, int nWParam, int nLParam, CWnd *pWnd);
	
	/* 判断输入点是否有效 */
	int JudgementInput(int nInput); 

	/* 走圆，返回有玻璃的点，（逆时针），确定玻璃大方向 */
	void RunCircleCommand(pCalPos pStart, pCalPos pCenter);
	
	/* 等待运动完成 */
	void WaitingMotionComplete(CString str); 

	/* 设置扫描点左右的距离 */
	void SetScanDistance(long nInSide, long nOutSide);
	
	/* 获取两点之间的距离 */
	double GetDistance(pCalPos pos1, pCalPos pos2);
	
	/* 命令执行 */
	int RunCommandInt(CString strRunComm);

	//当走到下一点时候没有触发中断，计算另一个方向上的点
	int	CalAnotherPoint(pCalPos pPos, pCalPos pTempPos, pCalPos pAnother);

	/* 保存数据点 */
	void SavePositions(char * chFileName, int InFormat);

	//调整步长大小
	void AdjustScanPace(pScanPosition pNewPos);



protected:

	char		chCmd[80];
	long		nRc;
	char		chResponse[80];
	long		nInside;
	long		nOutside;
	
	
	CalPos          m_CurrPos;/* 暂存当前位置 */
	
	BOOL bOil;
	BOOL bFan;
	BOOL bLoop;
	
	double	m_dResolutionX;
	double	m_dResolutionY;
	double	m_dVoltSpeedX;
	double	m_dVoltSpeedY;
	
	
	/* 获取锁存位置 */
	double GetReportLatched(char chAxis);
	
	/* 清除锁存功能 */
	void ClearArmLatch();
	

	/* 对采集的数据点进行后期处理 */
	void DataProcess();

	ofstream	file;//文件指针

	void begin(CString strFile);//新建文件，开始写文件
	void limits(double x, double y, double x4, double y4 );//控制绘图界限
	void zooma();//全屏显示
	void line(double x0, double y0, double x3, double y3);//画直线
	void Arc(double x0, double y0, double x2, double y2, double x3, double y3);
	void gend();//结束写文件

	/* 等待输入点断开 */
	void WaitingInputInvalid(CString strAM, int nInput); 

		
	/* 命令执行 */
	double RunCommandDouble(CString strRunComm);
	
	/* Calculate the angle between points */
	double PointAngleTo(pScanPosition pBegin, pScanPosition pEnd);
	
	/* Calculate the angle between points */
	double PointAngleTo(pCalPos pBegin, pCalPos pEnd);
		
	/* 获取当前位置 */
	void GetCurrPosition(pCalPos pCurrPos);
	
	/* Calculate the traverse angle of an arc segment */
	/* CCW为逆时针，CW为顺时针 */
	double CalculateTraverseAngle(BOOL bDirect, double dBeginAngle, double dEndAngle);

	/* 根据直线的斜率，计算刀补后的直线 */
	/* 计算直线的左刀补或右刀补，作为扫描的起点或终点 */
	int GetCompPoint(int nKerfComp, double dToolSize, CalPos LineBegin, CalPos LineEnd, pCalPos pLineEnd);

	/* 计算两点之间的斜率 */
	int Cal_Slope(CalPos LineBegin, CalPos LineEnd, pCalPos pSlope);

	/* 根据中心点与起始点，计算起始点前面的理论点，用于计算起点的左右刀补 */
	int Cal_PrevBegin(CalPos LineCenter, CalPos LineBegin, pCalPos pPrevBegin);

	/* 根据中心点与起始点，计算起始点前面的理论点，用于计算起点的左右刀补 */
	int Cal_PrevEnd(CalPos LineCenter, CalPos LineBegin, pCalPos pPrevBegin);

};

#endif // !defined(AFX_SCANACT_H__1124C7D3_CCD2_4626_BC55_E529151C81D8__INCLUDED_)
