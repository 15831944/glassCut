#if !defined(AFX_EDITDOUBLECLICK_H__D8F985EB_6318_4237_BFA0_76D8B658D5D3__INCLUDED_)
#define AFX_EDITDOUBLECLICK_H__D8F985EB_6318_4237_BFA0_76D8B658D5D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDoubleClick.h : header file
//
#define   WM_EDITDOUBLE     WM_USER+101

/////////////////////////////////////////////////////////////////////////////
// CEditDoubleClick window

class CEditDoubleClick : public CEdit
{
// Construction
public:
	CEditDoubleClick();

// Attributes
public:

	CString		strTip;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditDoubleClick)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditDoubleClick();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditDoubleClick)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDOUBLECLICK_H__D8F985EB_6318_4237_BFA0_76D8B658D5D3__INCLUDED_)
