//{{AFX_INCLUDES()
#include "captioninfo.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLG_PASS_H__B7898E85_A940_4A5C_B057_61AA96A4F487__INCLUDED_)
#define AFX_DLG_PASS_H__B7898E85_A940_4A5C_B057_61AA96A4F487__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlg_pass.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dlg_pass dialog
#include "EditDoubleClick.h"

class dlg_pass : public CDialog
{
	// Construction
public:
	dlg_pass(CWnd* pParent = NULL);   // standard constructor
	~dlg_pass();
    _ConnectionPtr m_pCon;   //ADO”¶”√
	_RecordsetPtr  m_pRec;
	CString        strPass0,strPass1,strPass2;
	
	// Dialog Data
	//{{AFX_DATA(dlg_pass)
	enum { IDD = IDD_SYS_PASS };
	CEditDoubleClick	m_edtPass;
	CClrButton	m_can2;
	CClrButton	m_ok;
	CClrButton	m_can;
	CCaptionInfo	m_demo;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dlg_pass)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	CBrush m_greenbrush,m_yollowbrush,m_redbrush,m_bluebrush;
	CWnd   *pWnd[6];

	void dlg_pass::OnLanguage();
	void dlg_pass::OnReSetCtl();
		
	// Generated message map functions
	//{{AFX_MSG(dlg_pass)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_PASS_H__B7898E85_A940_4A5C_B057_61AA96A4F487__INCLUDED_)
