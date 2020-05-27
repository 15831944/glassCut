// ComboGridCtrl.h: interface for the CComboGridCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMBOGRIDCTRL_H__EC89C9C0_01A5_11D2_AB4A_5C7377000000__INCLUDED_)
#define AFX_COMBOGRIDCTRL_H__EC89C9C0_01A5_11D2_AB4A_5C7377000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GridCtrl.h"
#include "afxtempl.h"

typedef struct _combocol{
	int iCol;
	CStringArray *comStr;
}COMBOCOL;

class CComboGridCtrl : public CGridCtrl  
{
public:
	void SetComboBoxStyle(DWORD dwStyle);
	BOOL SetComboItemText(int nRow,int nCol,int index);
	virtual BOOL SetItem(GV_ITEM *pItem);
	virtual BOOL SetItemText(int nRow, int nCol, LPCTSTR str);
	BOOL AddComboColumn(int iCol,CStringArray &comStr);
	CComboGridCtrl();
	virtual ~CComboGridCtrl();

protected:
    virtual void CreateInPlaceEditControl(CRect& rect, DWORD dwStyle, UINT nID,
                                          int nRow, int nCol, LPCTSTR szText, int nChar);

    //{{AFX_MSG(CComboGridCtrl)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
	int IsColumnCombo(int nCol);
	CArray<COMBOCOL,COMBOCOL&> m_comStrArray;
	DWORD	m_comboBoxStyle;
};

#endif // !defined(AFX_COMBOGRIDCTRL_H__EC89C9C0_01A5_11D2_AB4A_5C7377000000__INCLUDED_)
