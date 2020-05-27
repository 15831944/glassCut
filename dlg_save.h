#if !defined(AFX_DLG_SAVE_H__81E8B679_9F9D_4DAB_A849_B26E92894D13__INCLUDED_)
#define AFX_DLG_SAVE_H__81E8B679_9F9D_4DAB_A849_B26E92894D13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlg_save.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dlg_save dialog
#include "EditDoubleClick.h"

class dlg_save : public CDialog
{
// Construction
public:
	dlg_save(CWnd* pParent = NULL);   // standard constructor

	CString	strExtName;

// Dialog Data
	//{{AFX_DATA(dlg_save)
	enum { IDD = IDD_DIALOG_SAVE };
	CClrButton	m_button8;
	CClrButton	m_button7;
	CEditDoubleClick	m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dlg_save)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd     *pWnd[6];

	void OnLanguage();
	void OnReSetCtl();
		
	// Generated message map functions
	//{{AFX_MSG(dlg_save)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_SAVE_H__81E8B679_9F9D_4DAB_A849_B26E92894D13__INCLUDED_)
