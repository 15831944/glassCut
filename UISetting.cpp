// UISetting.cpp: implementation of the CUISetting class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bender.h"
#include "UISetting.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUISetting::CUISetting()
{
	m_nIndex = (UINT)-1;
	memset(m_paras, 0, sizeof(m_paras));
	m_nParaCount = 0;
}

CUISetting::~CUISetting()
{

}

void CUISetting::AddParaCtrl(LPCTSTR lpszTitle, UINT nCtrlIndex, LPCTSTR lpszRemark, double fDefaultValue/*=100.0*/)
{
	int TitleIDs[15]=
	{
		IDC_STATIC_PARA01, IDC_STATIC_PARA02, IDC_STATIC_PARA03, IDC_STATIC_PARA04, IDC_STATIC_PARA05, 
		IDC_STATIC_PARA06, IDC_STATIC_PARA07, IDC_STATIC_PARA08, IDC_STATIC_PARA09, IDC_STATIC_PARA10,
		IDC_STATIC_PARA11, IDC_STATIC_PARA12, IDC_STATIC_PARA13, IDC_STATIC_PARA14, IDC_STATIC_PARA15
	};
	int EditIDs[15]=
	{
		IDC_EDIT_PARA01, IDC_EDIT_PARA02, IDC_EDIT_PARA03, IDC_EDIT_PARA04, IDC_EDIT_PARA05,
		IDC_EDIT_PARA06, IDC_EDIT_PARA07, IDC_EDIT_PARA08, IDC_EDIT_PARA09, IDC_EDIT_PARA10,
		IDC_EDIT_PARA11, IDC_EDIT_PARA12, IDC_EDIT_PARA13, IDC_EDIT_PARA14, IDC_EDIT_PARA15
	};
	int RemarkIDs[15]=
	{
		IDC_STATIC_REMARK1, IDC_STATIC_REMARK2, IDC_STATIC_REMARK3, IDC_STATIC_REMARK4, IDC_STATIC_REMARK5, 
		IDC_STATIC_REMARK6, IDC_STATIC_REMARK7, IDC_STATIC_REMARK8, IDC_STATIC_REMARK9, IDC_STATIC_REMARK10,
		IDC_STATIC_REMARK11, IDC_STATIC_REMARK12, IDC_STATIC_REMARK13, IDC_STATIC_REMARK14, IDC_STATIC_REMARK15
	};
	GRPARA *para=NULL;
	if(m_nParaCount>=UI_MAX_PARAs)
		return;
	if(nCtrlIndex>=15)
		return;

	para = &(m_paras[m_nParaCount]);
	m_nParaCount++;

	memset(para, 0, sizeof(GRPARA));
	para->nTitleCtrlID = TitleIDs[nCtrlIndex];
	para->nEditCtrlID = EditIDs[nCtrlIndex];
	para->nRemarkCtrlID = RemarkIDs[nCtrlIndex];
	if(lpszTitle)
	{
		strncpy(para->szName, lpszTitle, 32-1);
		strncpy(para->szTitle, lpszTitle, 32-1);
	}
	if(lpszRemark)
	{
		strncpy(para->szRemark, lpszRemark, 32-1);
	}
	para->fValue = fDefaultValue;
}

UINT CUISetting::GetParaCount()
{
	return m_nParaCount;
}

GRPARA* CUISetting::GetUIPara(UINT index)
{
	if(index>=m_nParaCount)
		return NULL;
	return &(m_paras[index]);
}

double CUISetting::GetValue(LPCTSTR lpszName)
{
	int i;
	double fValue;
	fValue=0.0f;
	for(i=0; i<(int)m_nParaCount; i++)
	{
		if(strcmp(m_paras[i].szName, lpszName)==0)
		{
			fValue = m_paras[i].fValue;
			break;
		}
	}
	return fValue;
}

void CUISetting::Reset()
{
	m_nParaCount = 0;
	m_nIndex = 0;
}
