// ScanAct.h: interface for the CScanAct class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCANACT_H__1124C7D3_CCD2_4626_BC55_E529151C81D8__INCLUDED_)
#define AFX_SCANACT_H__1124C7D3_CCD2_4626_BC55_E529151C81D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define PIE  3.1415926

#define SCAN_DIRECTION_CCW	FALSE	/* ��ʱ�� */
#define SCAN_DIRECTION_CW	TRUE	/* ˳ʱ�� */

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
	pScanPosition	m_pCurrScanPos;	/* ɨ�������׽�� */
	CalPos			m_Begin;		/* ��Ѱɨ������� */
	CalPos			m_Center;		/* ��Ѱɨ�������ĵ� */
	CScanPosition	m_ScanPos;
	double			m_dScanPace;	/* ɨ�貽�� */
	double			m_dTempScanPace;	/* ��ʱɨ�貽�� */
	double			m_dDegreeCoor;	/* ����ϵ�Ƕ� */
	
	CalPos			m_ZeroPos;		/* ��Ѱɨ������� */
	int             m_nInterrupt;   //����IO�ж�
	/* �������湦�� */
	void SetArmLatch();

	/* �����ж�ʹ�� */
	void SetEnableInterrupt();

	/* �������ݵ�ΪG���� */
	void SavePositions2G(char * chFileName);	

	/* ���üӹ����գ����ݹ���дG code and DXF */
	void SetProcessingTechnic(BOOL bOiling, BOOL bFans, BOOL bLoopAround);

	/* �������嵱�� */
	void SetResolution(double dResX, double dResY);

	/* ����ÿ����ѹ���ٶ� */
	void SetVoltSpeed(double dVoltX, double dVoltY);

	/* ����һ�����ݵ� */
	pScanPosition SetHeadPosition(pScanPosition pHead);

	/* ����һ�����ݵ� */
	pScanPosition AddPosition(pScanPosition pLast);
	
	/* �ͷ��������ݵ� */
	void FreePosition();

	/* ����ִ�� */
	int RunCommand(CString strRunComm);

	/* �ߵ�ĳ��λ������ */
	void RunGotoPosCommand(pCalPos pDis);

	/* ��Բ�����ߵ�ĳ��λ������ */
	void RunGotoArcCommand(double dRadius, pCalPos pDis);
		
	/* ֹͣ���У��ȴ��˶���� */
	void RunStopandWait(CString str);

	/* �ж�����״̬���Ƿ�����ɹ� */
	int GetArmLatch();
	
	/* ���㡢������һ��ɨ����λ�ã����ݲ��� */
	int CalNextScanPos(pScanPosition pNewPos, pCalPos pPos);

	/* ������㣬������������ʹ�� d�Ҳ���ÿ�ζ���0.5����*/
	int CalBegin(pScanPosition pNewPos, pCalPos pPos,double d);
	
	/* �����յ㣬����ʹ�ܣ�����������յ㣬�����ҵ����� */
	int CalEnd(pScanPosition pNewPos, pCalPos pPos);
	
	/* ������㣬Ҳ�в����е㣬��һ�������˷�����Ѱ */
	void SetStartPos(pCalPos pPos);

	/* �������ڷ�����Ϣ�������������� */
	void DllSendMessgeToDialog(int nMsg, int nWParam, int nLParam, CWnd *pWnd);
	
	/* �ж�������Ƿ���Ч */
	int JudgementInput(int nInput); 

	/* ��Բ�������в����ĵ㣬����ʱ�룩��ȷ���������� */
	void RunCircleCommand(pCalPos pStart, pCalPos pCenter);
	
	/* �ȴ��˶���� */
	void WaitingMotionComplete(CString str); 

	/* ����ɨ������ҵľ��� */
	void SetScanDistance(long nInSide, long nOutSide);
	
	/* ��ȡ����֮��ľ��� */
	double GetDistance(pCalPos pos1, pCalPos pos2);
	
	/* ����ִ�� */
	int RunCommandInt(CString strRunComm);

	//���ߵ���һ��ʱ��û�д����жϣ�������һ�������ϵĵ�
	int	CalAnotherPoint(pCalPos pPos, pCalPos pTempPos, pCalPos pAnother);

	/* �������ݵ� */
	void SavePositions(char * chFileName, int InFormat);

	//����������С
	void AdjustScanPace(pScanPosition pNewPos);



protected:

	char		chCmd[80];
	long		nRc;
	char		chResponse[80];
	long		nInside;
	long		nOutside;
	
	
	CalPos          m_CurrPos;/* �ݴ浱ǰλ�� */
	
	BOOL bOil;
	BOOL bFan;
	BOOL bLoop;
	
	double	m_dResolutionX;
	double	m_dResolutionY;
	double	m_dVoltSpeedX;
	double	m_dVoltSpeedY;
	
	
	/* ��ȡ����λ�� */
	double GetReportLatched(char chAxis);
	
	/* ������湦�� */
	void ClearArmLatch();
	

	/* �Բɼ������ݵ���к��ڴ��� */
	void DataProcess();

	ofstream	file;//�ļ�ָ��

	void begin(CString strFile);//�½��ļ�����ʼд�ļ�
	void limits(double x, double y, double x4, double y4 );//���ƻ�ͼ����
	void zooma();//ȫ����ʾ
	void line(double x0, double y0, double x3, double y3);//��ֱ��
	void Arc(double x0, double y0, double x2, double y2, double x3, double y3);
	void gend();//����д�ļ�

	/* �ȴ������Ͽ� */
	void WaitingInputInvalid(CString strAM, int nInput); 

		
	/* ����ִ�� */
	double RunCommandDouble(CString strRunComm);
	
	/* Calculate the angle between points */
	double PointAngleTo(pScanPosition pBegin, pScanPosition pEnd);
	
	/* Calculate the angle between points */
	double PointAngleTo(pCalPos pBegin, pCalPos pEnd);
		
	/* ��ȡ��ǰλ�� */
	void GetCurrPosition(pCalPos pCurrPos);
	
	/* Calculate the traverse angle of an arc segment */
	/* CCWΪ��ʱ�룬CWΪ˳ʱ�� */
	double CalculateTraverseAngle(BOOL bDirect, double dBeginAngle, double dEndAngle);

	/* ����ֱ�ߵ�б�ʣ����㵶�����ֱ�� */
	/* ����ֱ�ߵ��󵶲����ҵ�������Ϊɨ��������յ� */
	int GetCompPoint(int nKerfComp, double dToolSize, CalPos LineBegin, CalPos LineEnd, pCalPos pLineEnd);

	/* ��������֮���б�� */
	int Cal_Slope(CalPos LineBegin, CalPos LineEnd, pCalPos pSlope);

	/* �������ĵ�����ʼ�㣬������ʼ��ǰ������۵㣬���ڼ����������ҵ��� */
	int Cal_PrevBegin(CalPos LineCenter, CalPos LineBegin, pCalPos pPrevBegin);

	/* �������ĵ�����ʼ�㣬������ʼ��ǰ������۵㣬���ڼ����������ҵ��� */
	int Cal_PrevEnd(CalPos LineCenter, CalPos LineBegin, pCalPos pPrevBegin);

};

#endif // !defined(AFX_SCANACT_H__1124C7D3_CCD2_4626_BC55_E529151C81D8__INCLUDED_)
