// UISetting.h: interface for the CUISetting class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UISETTING_H__CBF62533_1619_4DD5_BAED_434194E453C3__INCLUDED_)
#define AFX_UISETTING_H__CBF62533_1619_4DD5_BAED_434194E453C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct tagGraphParameter
{
	char szName[32];
	int  nTitleCtrlID;
	int  nEditCtrlID;
	int  nRemarkCtrlID;
	char szTitle[32];
	char szRemark[32];
	double fValue;
} GRPARA;

class CUISetting  
{
public:
	void Reset();
	double GetValue(LPCTSTR lpszName);
	GRPARA* GetUIPara(UINT index);
	UINT GetParaCount();
	void AddParaCtrl(LPCTSTR lpszTitle, UINT nCtrlIndex, LPCTSTR lpszRemark, double fDefaultValue=100.0);
	enum { UI_MAX_PARAs=15 };
	UINT    m_nIndex;
	CUISetting();
	virtual ~CUISetting();

protected:
	GRPARA  m_paras[UI_MAX_PARAs];
	UINT	m_nParaCount;
};

#endif // !defined(AFX_UISETTING_H__CBF62533_1619_4DD5_BAED_434194E453C3__INCLUDED_)
