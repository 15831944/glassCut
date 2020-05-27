// ComboGridCtrl.cpp: implementation of the CComboGridCtrl class.
//
// This is a demo of how to override CGridCtrl in order to offer
// other editing capabilities such as a drop down list
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComboGridCtrl.h"
#include "InPlaceList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CComboGridCtrl, CGridCtrl)
    //{{AFX_MSG_MAP(CComboGridCtrl)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComboGridCtrl::CComboGridCtrl()
{
	m_comboBoxStyle=CBS_DISABLENOSCROLL|CBS_SIMPLE;
}

CComboGridCtrl::~CComboGridCtrl()
{
	for(int i=0;i<m_comStrArray.GetSize();i++)
		delete m_comStrArray.GetAt(i).comStr;
}

//////////////////////////////////////////////////////////////////////
// Overrides modified by huangjianxiong at 2003-5-17
//////////////////////////////////////////////////////////////////////

void CComboGridCtrl::CreateInPlaceEditControl(CRect& rect, DWORD dwStyle, UINT nID,
                                              int nRow, int nCol,
                                              LPCTSTR szText, int nChar)
{
	BOOL bComboCol=FALSE;
	COMBOCOL combocol;
	for(int i=0;i<m_comStrArray.GetSize();i++)
	{
		combocol=m_comStrArray.GetAt(i);
		if(combocol.iCol==nCol)
		{
			bComboCol=TRUE;
			break;
		}
	}
	// InPlaceList and auto-deletes itself
	if(bComboCol)
		new CInPlaceList(this, rect,
                     //CBS_DROPDOWNLIST,    // Uncomment for dropdown list style
                     m_comboBoxStyle,          // Uncomment for dropdown style
                     //CBS_SIMPLE,          // Uncomment for simple style
                     nID,                   // ID of control being created
                     nRow, nCol, 
                     *combocol.comStr, szText, nChar);
	else
		CGridCtrl::CreateInPlaceEditControl(rect,dwStyle,nID,nRow,nCol,szText,nChar);
}

//****************************************************************
//	function:make a specified column can be edit by combo select
//	param: 1 int iCol[in]: specify the column
//		   2 CArrayString & comStr[in]:string list
//	return:	BOOL bSuccess
//	remark:	huangjianxiong modify at 2003-5-17
//*****************************************************************
BOOL CComboGridCtrl::AddComboColumn(int iCol, CStringArray &comStr)
{
	if(iCol<GetFixedColumnCount()) return FALSE;
	COMBOCOL col;
	col.iCol=iCol;
	col.comStr=new CStringArray;
	col.comStr->Copy(comStr);
	m_comStrArray.Add(col);
	return TRUE;
}

BOOL CComboGridCtrl::SetItemText(int nRow, int nCol, LPCTSTR str)
{
	int comIndex=IsColumnCombo(nCol);
	if(comIndex!=-1&&nRow>=GetFixedRowCount())
	{
		BOOL bRet;
		COMBOCOL combocol=m_comStrArray.GetAt(comIndex);
		for(int i=0;i<combocol.comStr->GetSize();i++)
			if(combocol.comStr->GetAt(i)==str)
			{
				bRet=CGridCtrl::SetItemText(nRow,nCol,str);
				break;
			}
		return bRet;
	}else
		return CGridCtrl::SetItemText(nRow,nCol,str);
}

int CComboGridCtrl::IsColumnCombo(int nCol)
{
	int  comIndex=-1;
	COMBOCOL combocol;
	for(int i=0;i<m_comStrArray.GetSize();i++)
	{
		combocol=m_comStrArray.GetAt(i);
		if(combocol.iCol==nCol)
		{
			comIndex=i;
			break;
		}
	}
	return comIndex;
}

BOOL CComboGridCtrl::SetItem(GV_ITEM *pItem)
{
   if (!pItem) 
        return FALSE;
    CGridCell* pCell = GetCell(pItem->row, pItem->col);
    if (!pCell) 
        return FALSE;

    if (pItem->mask & GVIF_TEXT)  
	{
		int comIndex=IsColumnCombo(pItem->col);
		BOOL bFind=FALSE;
		if(comIndex!=-1)
		{
			if(pItem->row<GetFixedRowCount())
				bFind=TRUE;
			else
			{
				COMBOCOL combocol=m_comStrArray.GetAt(comIndex);
				for(int i=0;i<combocol.comStr->GetSize();i++)
					if(combocol.comStr->GetAt(i)==pItem->szText)
					{
						bFind=TRUE;
					}
			}
		}
		if(!bFind&&comIndex!=-1) 
			return FALSE;
		else
			pCell->szText=pItem->szText;			
	}
    if (pItem->mask & GVIF_PARAM)  pCell->lParam  = pItem->lParam;
    if (pItem->mask & GVIF_IMAGE)  pCell->iImage  = pItem->iImage;
    if (pItem->mask & GVIF_STATE)  pCell->state   = pItem->state;
    if (pItem->mask & GVIF_FORMAT) pCell->nFormat = pItem->nFormat;
    if (pItem->mask & GVIF_BKCLR)  pCell->crBkClr = pItem->crBkClr;
    if (pItem->mask & GVIF_FGCLR)  pCell->crFgClr = pItem->crFgClr;
    if (pItem->mask & GVIF_FONT)   memcpy(&(pCell->lfFont), &(pItem->lfFont), sizeof(LOGFONT));

    return TRUE;
}

//***************************************************
//	set item text by combobox index
//**************************************************
BOOL CComboGridCtrl::SetComboItemText(int nRow, int nCol, int index)
{
	int comIndex=IsColumnCombo(nCol);
	if(comIndex==-1) return FALSE;
	COMBOCOL combocol=m_comStrArray.GetAt(comIndex);
	if(index>=combocol.comStr->GetSize()) return FALSE;
	return CGridCtrl::SetItemText(nRow,nCol,combocol.comStr->GetAt(index));
}

//********************************************************
//	set combobox style
//********************************************************
void CComboGridCtrl::SetComboBoxStyle(DWORD dwStyle)
{
	m_comboBoxStyle=dwStyle;
}
