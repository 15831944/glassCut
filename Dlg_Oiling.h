#if !defined(AFX_DLG_OILING_H__3EAE4095_1230_4C1E_BD95_399A2AAE9545__INCLUDED_)
#define AFX_DLG_OILING_H__3EAE4095_1230_4C1E_BD95_399A2AAE9545__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Oiling.h : header file
//
#include "EditDoubleClick.h"

#define WM_OILING		WM_USER+116

/////////////////////////////////////////////////////////////////////////////
// CDlg_Oiling dialog

class CDlg_Oiling : public CDialog
{
// Construction
public:
	CDlg_Oiling(CWnd* pParent = NULL);   // standard constructor
	~CDlg_Oiling();
// Dialog Data
	//{{AFX_DATA(CDlg_Oiling)
	enum { IDD = IDD_DIALOG_CONFIG_OILING };
	CEditDoubleClick	m_edtOilOpen;
	CEditDoubleClick	m_edtOilClose;
	double	m_dOilClose;
	double	m_dOilOpen; 
	int		m_bModeOil;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Oiling)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	void OnLanguage();

	// Generated message map functions
	//{{AFX_MSG(CDlg_Oiling)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnOiling(WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBrush m_brush;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_OILING_H__3EAE4095_1230_4C1E_BD95_399A2AAE9545__INCLUDED_)
