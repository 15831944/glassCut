#if !defined(AFX_DLG_LOADING_H__B1BE6527_52A7_4FC4_9C52_318C1AC6993D__INCLUDED_)
#define AFX_DLG_LOADING_H__B1BE6527_52A7_4FC4_9C52_318C1AC6993D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Loading.h : header file
//

#define WM_LOADING		WM_USER+112

/////////////////////////////////////////////////////////////////////////////
// CDlg_Loading dialog
#include "EditDoubleClick.h"

class CDlg_Loading : public CDialog
{
// Construction
public:
	CDlg_Loading(CWnd* pParent = NULL);   // standard constructor
	~CDlg_Loading();
// Dialog Data
	//{{AFX_DATA(CDlg_Loading)
	enum { IDD = IDD_DIALOG_CONFIG_LOADING };
	CEditDoubleClick	m_editReady;
	CEditDoubleClick	m_editUpWT;
	CEditDoubleClick	m_editLabel;
	CEditDoubleClick	m_edtLeaveTime;
	CEditDoubleClick	m_edtDelayTime;
	CEditDoubleClick	m_edtWaitY;
	CEditDoubleClick	m_edtWaitX;
	long	m_nWaitX;
	long	m_nWaitY;
	double	m_nTimeDelay;
	int		m_nLeaveTime;
	long	m_lLabelWT;
	UINT	m_unUpWT;
	int		m_nReadyTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Loading)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void OnLanguage();

	// Generated message map functions
	//{{AFX_MSG(CDlg_Loading)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg LRESULT OnLoading(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBrush m_brush;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_LOADING_H__B1BE6527_52A7_4FC4_9C52_318C1AC6993D__INCLUDED_)
