#if !defined(AFX_DLG_USTLIMIT_H__7A7087FE_B2FC_4FA6_908F_A490DF9DB699__INCLUDED_)
#define AFX_DLG_USTLIMIT_H__7A7087FE_B2FC_4FA6_908F_A490DF9DB699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlg_ustLimit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dlg_ustLimit dialog
#include "EditDoubleClick.h"

class dlg_ustLimit : public CDialog
{
// Construction
public:
	dlg_ustLimit(CWnd* pParent = NULL);   // standard constructor

	void	OnLanguageustLimit();

// Dialog Data
	//{{AFX_DATA(dlg_ustLimit)
	enum { IDD = IDD_DIALOG_USELIMIT };
	CStatic	m_ctrday1;
	CStatic	m_ctrmon1;
	CStatic	m_ctryear1;
	CStatic	m_ctrdate1;
	CStatic	m_ctrdate2;
	CEditDoubleClick	m_edt1;
	CEditDoubleClick	m_edtYear2;
	CEditDoubleClick	m_edtYear1;
	CEditDoubleClick	m_edtMonth1;
	CEditDoubleClick	m_edtDay1;
	CMonthCalCtrl	m_cal;
	//}}AFX_DATA
		
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dlg_ustLimit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnButtonTime(); 
		
	// Generated message map functions
	//{{AFX_MSG(dlg_ustLimit)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonl7();
	afx_msg void OnButtonl8();
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

#endif // !defined(AFX_DLG_USTLIMIT_H__7A7087FE_B2FC_4FA6_908F_A490DF9DB699__INCLUDED_)
