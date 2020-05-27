// OrangeListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "OrangeListCtrl.h"


// COrangeListCtrl

IMPLEMENT_DYNAMIC(COrangeListCtrl, CListCtrl)

COrangeListCtrl::COrangeListCtrl()
{
	m_nRowHeight=0;
}

COrangeListCtrl::~COrangeListCtrl()
{
}


BEGIN_MESSAGE_MAP(COrangeListCtrl, CListCtrl)
	ON_WM_MEASUREITEM()
	ON_WM_MEASUREITEM_REFLECT()
END_MESSAGE_MAP()



// COrangeListCtrl 消息处理程序



void COrangeListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  添加您的代码以绘制指定项
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC); 

	LVITEM lvi = {0}; 
	lvi.mask = LVIF_STATE;
	lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED ; 
	lvi.iItem = lpDrawItemStruct->itemID; 
	BOOL bGet = GetItem(&lvi); 

	CRect rcBack = lpDrawItemStruct->rcItem; 


	pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT)); 
	pDC->FillRect(rcBack, &CBrush(GetBkColor()));	 
	


	//绘制文本
	CString strText=L""; 
	CRect rcItem; 
	if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) 
	{ 
		for (int i = 0; i < GetHeaderCtrl()-> GetItemCount();i++)
		{ 			
			if ( !GetSubItemRect(lpDrawItemStruct->itemID, i, LVIR_LABEL, rcItem )) 
				continue; 
			strText = GetItemText( lpDrawItemStruct->itemID, i );

			pDC->DrawText(strText,strText.GetLength(), &rcItem, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		} 
	}

}

void COrangeListCtrl::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ModifyStyle(0,LVS_OWNERDRAWFIXED);
	CListCtrl::PreSubclassWindow();

}

void COrangeListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if (m_nRowHeight>0)
	{
		lpMeasureItemStruct->itemHeight = m_nRowHeight;
	}
}
void COrangeListCtrl::SetRowHeigt(int nHeight)
{
	m_nRowHeight = nHeight;

	CRect rcWin;
	GetWindowRect(&rcWin);
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}

void COrangeListCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

