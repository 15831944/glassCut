// EditDoubleClick.cpp : implementation file
//

#include "stdafx.h"
#include "Bender.h"
#include "EditDoubleClick.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditDoubleClick

CEditDoubleClick::CEditDoubleClick()
{
	strTip = "";
}

CEditDoubleClick::~CEditDoubleClick()
{
}


BEGIN_MESSAGE_MAP(CEditDoubleClick, CEdit)
	//{{AFX_MSG_MAP(CEditDoubleClick)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditDoubleClick message handlers

void CEditDoubleClick::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CEdit::OnLButtonDblClk(nFlags, point);
}

void CEditDoubleClick::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(g_stu_pAxisC->bSpareA)
		GetParentOwner()->PostMessage(WM_EDITDOUBLE,GetDlgCtrlID(), 0);
	else
		GetParentOwner()->PostMessage(WM_EDITDOUBLE,GetDlgCtrlID(), 1);
	CEdit::OnLButtonUp(nFlags, point);
}
