#if !defined(AFX_DLG_KEYNUMBER_H__376E4502_0C23_4AC6_82D0_C344AD124B1E__INCLUDED_)
#define AFX_DLG_KEYNUMBER_H__376E4502_0C23_4AC6_82D0_C344AD124B1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_KeyNumber.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_KeyNumber dialog

class CDlg_KeyNumber : public CDialog
{
// Construction
public:
	CDlg_KeyNumber(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_KeyNumber)
	enum { IDD = IDD_DIALOG_KEYNUMBER };
	CClrButton	m_btn13;
	CClrButton	m_btn12;
	CClrButton	m_btn11;
	CClrButton	m_btnDel;
	CClrButton	m_btnBK;
	CClrButton	m_btn9;
	CClrButton	m_btn8;
	CClrButton	m_btn7;
	CClrButton	m_btn6;
	CClrButton	m_btn5;
	CClrButton	m_btn4;
	CClrButton	m_btn3;
	CClrButton	m_btn2;
	CClrButton	m_btn1;
	CClrButton	m_btn0;
	CClrButton	m_btnCancel;
	CClrButton	m_btnOk;
	CEdit	m_edtNew;
	CString	m_strNew;
	CString	m_strOld;
	CString	m_strTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_KeyNumber)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void OnButtonFont(); /* 改变窗口字体 */
	CBrush m_greenbrush,m_yollowbrush,m_redbrush,m_bluebrush;

	void OnLanguage();
		
	// Generated message map functions
	//{{AFX_MSG(CDlg_KeyNumber)
	afx_msg void OnButton10();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButtonBk();
	afx_msg void OnButton12();
	afx_msg void OnButtonDel();
	afx_msg void OnBtnOk();
	virtual void OnCancel();
	afx_msg void OnButton11();
	afx_msg void OnButton13();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_KEYNUMBER_H__376E4502_0C23_4AC6_82D0_C344AD124B1E__INCLUDED_)
