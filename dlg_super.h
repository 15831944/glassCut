//{{AFX_INCLUDES()
#include "captioninfo.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLG_SUPER_H__6274682A_53A0_4ECB_9120_91BB943DE82E__INCLUDED_)
#define AFX_DLG_SUPER_H__6274682A_53A0_4ECB_9120_91BB943DE82E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlg_super.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dlg_super dialog
#include "EditDoubleClick.h"

class dlg_super : public CDialog
{
// Construction
public:
	dlg_super(CWnd* pParent = NULL);   // standard constructor
 	CString pass0,pass1,pass2;
	
	void OnLanguage();		
	
	// Dialog Data
	//{{AFX_DATA(dlg_super)
	enum { IDD = IDD_SYS_SUPER };
	CStatic	m_s3;
	CStatic	m_s2;
	CStatic	m_s1;
	CEditDoubleClick	m_e6;
	CEditDoubleClick	m_e5;
	CEditDoubleClick	m_e4;
	CEditDoubleClick	m_e3;
	CEditDoubleClick	m_e2;
	CEditDoubleClick	m_e1;
	CCaptionInfo	m_demo;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dlg_super)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(dlg_super)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtons7();
	afx_msg void OnButtons8();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CUniButton   m_pButton[2];
	void InitButton();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_SUPER_H__6274682A_53A0_4ECB_9120_91BB943DE82E__INCLUDED_)
