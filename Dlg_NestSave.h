#if !defined(AFX_DLG_NESTSAVE_H__F26CEE4C_84A2_49AC_B955_FFB3C32CB475__INCLUDED_)
#define AFX_DLG_NESTSAVE_H__F26CEE4C_84A2_49AC_B955_FFB3C32CB475__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_NestSave.h : header file
//

#include "EditDoubleClick.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_NestSave dialog

class CDlg_NestSave : public CDialog
{
// Construction
public:
	CDlg_NestSave(CWnd* pParent = NULL);   // standard constructor
	double GetThick();
	dlg_save(BOOL bOpen);
	
// Dialog Data
	//{{AFX_DATA(CDlg_NestSave)
	enum { IDD = IDD_DIALOG_NEST_SAVE };
	CEditDoubleClick	m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_NestSave)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	double m_fThick;
	CString m_strTitle;

	CClrButton m_clrButton [2];
	
	// Generated message map functions
	//{{AFX_MSG(CDlg_NestSave)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_NESTSAVE_H__F26CEE4C_84A2_49AC_B955_FFB3C32CB475__INCLUDED_)
