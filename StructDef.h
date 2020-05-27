#ifndef _STRUCTDEF_H_
#define _STRUCTDEF_H_
#include <afxtempl.h>
#include "stdafx.h"
namespace Feng
{
	//矩形件尺寸结构体
	typedef struct tagDimension
	{
		int nLen;	//矩形件长
		int nWid;	//矩形件宽
		int nNum;	//数量
		int nLocNo;	//定位号
		int trimLeft;
		int trimRight;
		int trimTop;
		int trimBottom;
		CString strCustName;//客户名
		CString strOrderNo;	//订单号
		CString strExplntn;	//注释
	}Dimension;

	//切割路径结构体
	typedef struct tagLine
	{
		CPoint ptStart;	//切割起点
		CPoint ptEnd;	//切割终点
	}CLine;

	//切割路径数组索引值结构体
	typedef struct tagIndex
	{
		int nIndexRow;
		int nIndexCol;
	}Index;

	//修边结构体
	typedef struct tagTrim
	{		
		int	left;	//左边修边量
		int top;	//下边边修边量（下边：是指视觉上的下边）
		int right;	//右边修边量
		int bottom; //上边修变量
	}Trim;

	typedef struct tagRawRect
	{
		Trim  *trim;
		CRect *rect;	//原片矩形
		int	  nMinEdge;	//最小留边量
		int num;		//原片数量
	}CRawRect;

	//已排列矩形
	typedef struct tagNoRect
	{
		Trim *trim;
		CRect *rect;
		int nLocNo;
		CString strCustName;//客户名
		CString strOrderNo;	//订单号
		CString strExplntn;	//注释
	}CNoRect;

	//排版方案图
	typedef struct tagDiagram
	{
		int no;							//图号
		int cutTimes;					//切割次数
		CRawRect *pRtRaw;				//原片尺寸(长和宽)
		double utilization;             //利用率
		CList<CNoRect*, CNoRect*>* pRtLay;	//已排列矩形件链表
		CList<CRect*, CRect*>* pRtRest;	//余料链表,暂不实现,用于以后考虑多片交叉排列矩形件来用
		CList<CLine*, CLine*>* pLnTrack;//切割路径链表
	}Diagram;

	//程序中的常量定义
	const int MAX = 2000;			//切割路径数组的最大值
	const int MAX_NUM = 10;			//最大物品数
	const int MAX_CAPACITY = 5000;	//最大容量
	//const double g_dZoom = 7.25;	//图形显示比例
	const int MAX_TRACK = 100000;	//切割轨迹生成时申请的字符数组的大小
	const int MAX_LST_NUM = 100;	//原料链表数量(原片的数量)

	//错误信息
	enum
	{
		/*
		int RAW_RECT_NUM_BELOW_ZERO = 10;	//原片数目小于零
		int RAW_RECT_NOT_ENOUGH;			//排列矩形件后原片数目不够
		*/
	};
}
#endif
