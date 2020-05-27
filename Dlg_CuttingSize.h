#if !defined(AFX_DLG_CUTTINGSIZE_H__753F4407_4B11_4163_B304_21860661D727__INCLUDED_)
#define AFX_DLG_CUTTINGSIZE_H__753F4407_4B11_4163_B304_21860661D727__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_CuttingSize.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CDlg_CuttingSize dialog
#include "EditDoubleClick.h"

class CDlg_CuttingSize : public CDialog
{
// Construction
public:
	CDlg_CuttingSize(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CDlg_CuttingSize)
	enum { IDD = IDD_DIALOG_CUTTINGSIZE };
	CEditDoubleClick	m_edtSavedown;	
	CEditDoubleClick	m_edtSizeE;
	CEditDoubleClick	m_edtSizeD;
	CEditDoubleClick	m_edtSizeC;
	CEditDoubleClick	m_edtSizeB;
	CEditDoubleClick	m_edtSizeA;
	CEditDoubleClick	m_edtDxfD;
	CEditDoubleClick	m_edtDxfC;
	CEditDoubleClick	m_edtDxfB;
	CEditDoubleClick	m_edtDxfA;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_CuttingSize)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CUniButton m_pButton[2];
	
	void OnLanguage();
	void OnReSetCtl();
	void InitButton();
	// Generated message map functions
	//{{AFX_MSG(CDlg_CuttingSize)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonF8();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnScale(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonF10();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()		
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_CUTTINGSIZE_H__753F4407_4B11_4163_B304_21860661D727__INCLUDED_)
