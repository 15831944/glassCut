// ScanWork.h: interface for the CScanWork class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCANWORK_H__2C6535FE_64A2_45B5_B1DD_BF0419DF413F__INCLUDED_)
#define AFX_SCANWORK_H__2C6535FE_64A2_45B5_B1DD_BF0419DF413F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ScanAct.h"


#define WM_SCANSEND		WM_USER+131	/* ���������ڷ�����Ϣ */
#define WM_SCANNEXT		WM_USER+132	/* ���������ڷ�����Ϣ */
#define WM_SENDSCAN		WM_USER+133	/* �������ڷ�����Ϣ������״̬ */


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


/* �Զ��������� */
UINT SendCommand(LPVOID pParam);

/*-------------------------------------------------------------------------*/
class AFX_EXT_CLASS CScanWork : public CObject 
{
public:
	CScanWork();
	virtual ~CScanWork();

	//��������������ָ��
	void SetPDmcWin(long pDmc);	

	//���������ڵ�ָ��
	void SetWindow(CWnd *pWnd);		
	
	//���ð�������Ƭ�ľ���
	void SetIncludeRect(double dTop, double dBottom, double dLeft, double dRight);

	//���ò����Ĵ�����ĵ�
	void SetCenterPoint(double dCenterX, double dCenterY);

	//����ɨ�����
	void SetStartPoint(double dStartX, double dStartY);

	//����ɨ����
	void SetScanPace(double dPace);

	/* XY����������ļн� */
	void SetScanCoorDegree(double dDegree);

	/* ����ʱҪ���������㣬����ײ��ģ�� */
	void SetScanZeroPos(double dZeroX, double dZeroY);
	
	/* ����ɨ������ҵľ��� */
	void SetScanDistance(long nInSide, long nOutSide);
	
	long Run();
	void Stop();
	void SaveScanFile2G(char * chFileName);

	//InFormat=1 cid;InFormat=2 dxf
	void SaveScanPosition(char * chFileName,int InFormat);
	
	/* ���üӹ����գ����ݹ���дG code and DXF */
	void SetProcessingTechnic(BOOL bOiling, BOOL bFans, BOOL bLoopAround);
	/* ��ȡ�ӹ����� */
	pScanPosition GetScanData();
	
	/* �������嵱�� */
	void SetResolution(double dResX, double dResY);
	
	/* ����ÿ����ѹ���ٶ� */
	void SetVoltSpeed(double dVoltX, double dVoltY);

	//����ɨ���״̬
	bool GetRunState();
	
protected:
	
	CScanThreadInfo	m_ScanInfo;
	CScanAct		clsScanAct;
	CWinThread		*m_Thread;
};

#endif // !defined(AFX_SCANWORK_H__2C6535FE_64A2_45B5_B1DD_BF0419DF413F__INCLUDED_)
