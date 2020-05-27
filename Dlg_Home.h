#if !defined(AFX_DLG_HOME_H__70983A56_C3CC_49F4_BAD7_2473CCA78D12__INCLUDED_)
#define AFX_DLG_HOME_H__70983A56_C3CC_49F4_BAD7_2473CCA78D12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Home.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_Home dialog

class CDlg_Home : public CDialog
{
// Construction
public:
	CDlg_Home(CWnd* pParent = NULL);   // standard constructor
	~CDlg_Home();
    void OpenDlgInit();
// Dialog Data
	//{{AFX_DATA(CDlg_Home)
	enum { IDD = IDD_DIALOG_HOME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Home)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_Home)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCs1();
	afx_msg void OnButtonCs2();
	afx_msg void OnButtonCs3();
	afx_msg void OnButtonCs4();
	afx_msg void OnButtonCs5();
	afx_msg void OnButtonCs6();
	afx_msg void OnButtonCs7();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()    
	int m_nHome;
	CUniButton m_pButton[7];
	void OnInitButton();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_HOME_H__70983A56_C3CC_49F4_BAD7_2473CCA78D12__INCLUDED_)
