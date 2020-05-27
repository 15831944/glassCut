#if !defined(AFX_DLG_NESTNUM_H__622F9B30_DB09_48BD_9436_73F14BF8CDF1__INCLUDED_)
#define AFX_DLG_NESTNUM_H__622F9B30_DB09_48BD_9436_73F14BF8CDF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_NestNum.h : header file
//
#include "EditDoubleClick.h"

/////////////////////////////////////////////////////////////////////////////
// CDlg_NestNum dialog

class CDlg_NestNum : public CDialog
{
// Construction
public:
	CDlg_NestNum(CWnd* pParent = NULL);   // standard constructor
	void OnCancel();
	void OnOK();
	int GetNum();
	
// Dialog Data
	//{{AFX_DATA(CDlg_NestNum)
	enum { IDD = IDD_DIALOG_NESTNUM };
	CStatic	m_stcNum;
	int		m_nSetNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_NestNum)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CClrButton m_clrButton[2];
	CEditDoubleClick m_pEdit[2];
	int m_nNum;
	// Generated message map functions
	//{{AFX_MSG(CDlg_NestNum)
	afx_msg void OnButtonOk();
	afx_msg void OnButtonCancel();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_NESTNUM_H__622F9B30_DB09_48BD_9436_73F14BF8CDF1__INCLUDED_)
