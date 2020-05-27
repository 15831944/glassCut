#ifndef _STRUCTDEF_H_
#define _STRUCTDEF_H_
#include <afxtempl.h>
#include "stdafx.h"
namespace Feng
{
	//���μ��ߴ�ṹ��
	typedef struct tagDimension
	{
		int nLen;	//���μ���
		int nWid;	//���μ���
		int nNum;	//����
		int nLocNo;	//��λ��
		int trimLeft;
		int trimRight;
		int trimTop;
		int trimBottom;
		CString strCustName;//�ͻ���
		CString strOrderNo;	//������
		CString strExplntn;	//ע��
	}Dimension;

	//�и�·���ṹ��
	typedef struct tagLine
	{
		CPoint ptStart;	//�и����
		CPoint ptEnd;	//�и��յ�
	}CLine;

	//�и�·����������ֵ�ṹ��
	typedef struct tagIndex
	{
		int nIndexRow;
		int nIndexCol;
	}Index;

	//�ޱ߽ṹ��
	typedef struct tagTrim
	{		
		int	left;	//����ޱ���
		int top;	//�±߱��ޱ������±ߣ���ָ�Ӿ��ϵ��±ߣ�
		int right;	//�ұ��ޱ���
		int bottom; //�ϱ��ޱ���
	}Trim;

	typedef struct tagRawRect
	{
		Trim  *trim;
		CRect *rect;	//ԭƬ����
		int	  nMinEdge;	//��С������
		int num;		//ԭƬ����
	}CRawRect;

	//�����о���
	typedef struct tagNoRect
	{
		Trim *trim;
		CRect *rect;
		int nLocNo;
		CString strCustName;//�ͻ���
		CString strOrderNo;	//������
		CString strExplntn;	//ע��
	}CNoRect;

	//�Ű淽��ͼ
	typedef struct tagDiagram
	{
		int no;							//ͼ��
		int cutTimes;					//�и����
		CRawRect *pRtRaw;				//ԭƬ�ߴ�(���Ϳ�)
		double utilization;             //������
		CList<CNoRect*, CNoRect*>* pRtLay;	//�����о��μ�����
		CList<CRect*, CRect*>* pRtRest;	//��������,�ݲ�ʵ��,�����Ժ��Ƕ�Ƭ�������о��μ�����
		CList<CLine*, CLine*>* pLnTrack;//�и�·������
	}Diagram;

	//�����еĳ�������
	const int MAX = 2000;			//�и�·����������ֵ
	const int MAX_NUM = 10;			//�����Ʒ��
	const int MAX_CAPACITY = 5000;	//�������
	//const double g_dZoom = 7.25;	//ͼ����ʾ����
	const int MAX_TRACK = 100000;	//�и�켣����ʱ������ַ�����Ĵ�С
	const int MAX_LST_NUM = 100;	//ԭ����������(ԭƬ������)

	//������Ϣ
	enum
	{
		/*
		int RAW_RECT_NUM_BELOW_ZERO = 10;	//ԭƬ��ĿС����
		int RAW_RECT_NOT_ENOUGH;			//���о��μ���ԭƬ��Ŀ����
		*/
	};
}
#endif
