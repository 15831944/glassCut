// AlarmDll.h: interface for the CAlarmDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALARMDLL_H__A59C274F_612B_4E06_BF5B_359F503F3A17__INCLUDED_)
#define AFX_ALARMDLL_H__A59C274F_612B_4E06_BF5B_359F503F3A17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "GeneralAlarm.h"

/*---------------------------------------*/
#define		GRADE_GREEN		0
#define		GRADE_YELLOW	1
#define		GRADE_ORANGE	2
#define		GRADE_RED		3

#define		SELF_ALM_CODE    100    /*自定义报警号基数*/

#define		UNDEFINED_ALARM		 -1		/* 报警号未定义 */
#define		OVERLAP_DEFINED		 -2		/* 重复定义 */
#define		LOW_ALARM_BASE_NUM	 -3		/* 自定义报警号应大于100 */
#define		MULTI_STRING_CH		 -4		/* 汉字说明多于20个字符 */
#define		MULTI_STRING_EN		 -5		/* 英文说明多于40个字符 */

/*---------------------------------------*/

struct tagAlarm
{
	int			nCode;			/* 报警号 */
	char		chTime[40];		/* 报警日期及时间 */
	int			nState;			/* 设置或清除状态 */
	tagAlarm	*pNext;			/* 下一报警 */
	tagAlarm	*pPrev;			/* 上一报警 */
};
typedef struct tagAlarm ALARM, *pALARM;

/* 所有报警列表(通用报警与自定义报警) */
struct tagAlarmList
{
	int				nCode;				/* 报警号 */
	int				nGrade;				/* 报警等级 */
	char			chContentCh[40];	/* 报警内容 */
	char			chContentEn[40];	/* 报警内容 */
	tagAlarmList	*pNext;				/* 下一报警 */
	tagAlarmList	*pPrev;				/* 上一报警 */
};
typedef struct tagAlarmList ALARMLIST, *pALARMLIST;

/* 当前报警的记录内容 */
struct tagParaAlarm
{
	int				nCode;			/* 报警号 */
	int				nGrade;			/* 报警等级 */	
	char			chTime[40];		/* 报警日期及时间 */
	char			Context[40];	/* 报警内容 */
};
typedef struct tagParaAlarm PARAALARM, *pPARAALARM;

class AFX_EXT_CLASS CAlarmDll : public CObject  
{
public:

	CAlarmDll();
	virtual ~CAlarmDll();

	/* 初始化数据库 */
	BOOL InitDB(char* chPath);

	/* 获取当前报警的单独内容的结构指针*/
	pPARAALARM GetSpecifyAlarm(int nCode);

	/* 设置历史报警保留时间 默认为5天 */
	void SetHisAlmTime(int nDay);

	/* 设置报警级别 */
	/* nCode：报警号（是对所有报警列表中的级别进行修改，首先查找节点） */
	/* nGrade：级别 */
	int SetAlarmGrade(int nCode, int nGrade);

	/* 设置当前报警 */
	int SetAlarm(int nCode);

	/* 清除当前报警 */
	int DeleteAlarm(int nCode);

	/* 获取当前报警的第一条报警内容 */
	pPARAALARM GetAlarm();
	
	/* 获取下一条报警内容 */
	pPARAALARM GetNextAlarm();
	
	/* 获取最后一条报警内容 */
	pPARAALARM GetLastAlarm();
	
	/* 获取当前报警计数 */
	int GetAlarmCounts();

	/* 获取历史报警 */
	pALARM GetHistoryAlarm();
	
	/* 设置语言 */
	int SetLanguage(int nLanguage);
	
	/* 释放报警结构 实时报警*/
	void FreeAlarm();
	
	/* 释放历史报警列表结构 释放所有*/
	void FreeHistoryAlarm();
	/*------------------------------------------*/

	/* 获取自定义报警 */
	pALARMLIST GetSelfAlarm();

	/* 获取自定义报警计数 */
	int GetSelfAlarmCounts();

	/* 客户增加自定义报警 */
	int AddSelfDefAlm(int nCode, int nGrade, char *chContentCh, char * chContentEn);

	/* 增加自定义报警 */
	int AddSelfAlarm(pALARMLIST pSelfAlarm);

	/* 删除自定义报警 */
	int DeleteSelfAlarm(pALARMLIST pSelfAlarm);

	/* 删除所有自定义报警 */
	int DeleteSelfAlarms();

	/*------------------------------------------*/

protected:

	_ConnectionPtr m_pCon;	// 连接数据库
	_RecordsetPtr m_pRs;	// 记录集
	int m_Language;			// 中英文语言的设置
	CString m_strDay;

 	pALARM  m_pCurrAlarm;   //当前报警结构指针

 	ALARM	m_CurrAlarm;
	int		m_CurrAlarmCounts;
	ALARM	m_HistoryAlarm;
	int		m_SelfAlarmCounts;

	ALARMLIST	m_SelfAlarmList;
	ALARMLIST   m_GeneralAlarmList;

	PARAALARM	m_CurrentContent;
	
	/* 初始化通用报警 */
	void InitGeneralAlarm();
	
	/* 初始化自定义报警 */
	void InitSelfDefiningAlarm();
	
	/* 初始化历史报警 */
	void InitHistoryAlarm();
	
	/* 增加报警结构 */
	int AddAlarm(int nCode);

	/* 增加报警列表结构 */
	pALARMLIST AddGeneralAlarmList();

	/* 增加自定义报警列表结构 */
	void AddSelfAlarmList(pALARMLIST pSelfAlarm);
	
	/* 释放报警列表结构 释放通用的*/
	void FreeAlarmList();
	
	/* 释放自定义报警列表结构 */
	void FreeSelfAlarmList();

	/* 删除数据库中超过天数的记录 */
	void DeletePastAlarm();
};

#endif // !defined(AFX_ALARMDLL_H__A59C274F_612B_4E06_BF5B_359F503F3A17__INCLUDED_)































































