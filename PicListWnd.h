#if !defined(AFX_PICLISTWND_H__BB81801B_8397_4C7A_978B_0176BE1EC31E__INCLUDED_)
#define AFX_PICLISTWND_H__BB81801B_8397_4C7A_978B_0176BE1EC31E__INCLUDED_

#include "PicWnd.h"
#include "afxTempl.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PicListWnd.h : header file
//

typedef	CList<DWORD, DWORD&>	LIST_PICWIN;

/////////////////////////////////////////////////////////////////////////////
// CPicListWnd window

class CPicListWnd : public CWnd
{
// Construction
public:
	CPicListWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicListWnd)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	CPicWnd* ListPicWndGetFocusWnd();
	UINT RetrieveItemRow(UINT nIndex);
	UINT RetrieveItemColumn(UINT nIndex);
	UINT ListPicWndGetCount();
	CPicWnd* ListPicWndGetAt(int nWndIndex);
	UINT GetItemHeight();
	BOOL Initialize(UINT nColumns=1);
	int ListPicWndGetFocus();
	void ListPicWndSetFocus(UINT nWndIndex);
	void ListPicWndRemoveAll();
	CPicWnd *ListPicWndAddNew(PIC_ATTR &attr);
	virtual ~CPicListWnd();

	// Generated message map functions
protected:
	SIZE m_sizeItem;
	UINT m_nColumns;
	int m_nFocusIndex;
	LIST_PICWIN m_lstPicWnd;
	void ListPicWndPlace(UINT nPicWnd, CPicWnd *pPicWnd);
	//{{AFX_MSG(CPicListWnd)
	afx_msg void OnDestroy();
	afx_msg LRESULT UsermsgPicWndMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIVESCANSETWIN_H__BB81801B_8397_4C7A_978B_0176BE1EC31E__INCLUDED_)
