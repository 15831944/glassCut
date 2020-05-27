#if !defined(AFX_MYFRAME_H__97652D04_EA4B_41ED_A280_FAFD6DB9CFE3__INCLUDED_)
#define AFX_MYFRAME_H__97652D04_EA4B_41ED_A280_FAFD6DB9CFE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyFrame.h : header file
//

#include "PicListWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CMyFrame window

class CMyFrame : public CWnd
{
// Construction
public:
	CPicWnd *PicWndAddNew(PIC_ATTR &attr);	
	void PicWndRemoveAll();	
	void PicWndSetFocus(UINT nWndIndex);
	int  PicWndGetFocus();

	CMyFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyFrame)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	CPicListWnd* GetPicListWnd();
	UINT PicWndGetCount();

	void ItemEnsureVisable(UINT nWnd);
	CPicWnd* PicWndGetAt(int nWndIndex);
	void Clean();
	BOOL Initialize(UINT nColumns=1);
	virtual ~CMyFrame();

	// Generated message map functions
protected:
	void ResetVScrollbar();
	void SetVScrollPos(int nPos);
    SCROLLINFO  m_siV;	
	CPicListWnd m_wndPicList;
	//{{AFX_MSG(CMyFrame)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGIONWND_H__97652D04_EA4B_41ED_A280_FAFD6DB9CFE3__INCLUDED_)
