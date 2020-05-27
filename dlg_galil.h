#if !defined(AFX_DLG_GALIL_H__D6DB492D_2782_429E_A83A_AA485A42CBBC__INCLUDED_)
#define AFX_DLG_GALIL_H__D6DB492D_2782_429E_A83A_AA485A42CBBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlg_galil.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dlg_galil dialog
#include "EditDoubleClick.h"

class dlg_galil : public CDialog
{
	// Construction
public:
	dlg_galil(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(dlg_galil)
	enum { IDD = IDD_DIALOG_GALIL };
	CEditDoubleClick	m_edtKSE;
	CEditDoubleClick	m_edtKPE;
	CEditDoubleClick	m_edtKIE;
	CEditDoubleClick	m_edtKDE;
	CComboBox	m_oee;
	CComboBox	m_mte;
	CComboBox	m_moe;
	CComboBox	m_cee;
	CComboBox	m_ce2e;
	CEditDoubleClick	m_edtKSZ;
	CEditDoubleClick	m_edtKSY;
	CEditDoubleClick	m_edtKSX;
	CEditDoubleClick	m_edtKSW;
	CEditDoubleClick	m_edtKPZ;
	CEditDoubleClick	m_edtKPY;
	CEditDoubleClick	m_edtKPX;
	CEditDoubleClick	m_edtKPW;
	CEditDoubleClick	m_edtKIZ;
	CEditDoubleClick	m_edtKIY;
	CEditDoubleClick	m_edtKIX;
	CEditDoubleClick	m_edtKIW;
	CEditDoubleClick	m_edtKDZ;
	CEditDoubleClick	m_edtKDY;
	CEditDoubleClick	m_edtKDX;
	CEditDoubleClick	m_edtKDW;
	CComboBox	m_moz;
	CComboBox	m_moy;
	CComboBox	m_mox;
	CComboBox	m_mow;
	CComboBox	m_oez;
	CComboBox	m_oey;
	CComboBox	m_oex;
	CComboBox	m_oew;
	CComboBox	m_mtz;
	CComboBox	m_mty;
	CComboBox	m_mtx;
	CComboBox	m_mtw;
	CComboBox	m_ce2z;
	CComboBox	m_ce2y;
	CComboBox	m_ce2x;
	CComboBox	m_ce2w;
	CComboBox	m_cez;
	CComboBox	m_cey;
	CComboBox	m_cex;
	CComboBox	m_cew;
	//}}AFX_DATA
	
	float dlg_galil::comMT(int i);
	long dlg_galil::comCE(int i,int j);
		
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dlg_galil)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	CUniButton   m_pButton[2];	
	void OnLanguage();
	void InitButton();	
		
	// Generated message map functions
	//{{AFX_MSG(dlg_galil)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton8();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButton10();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_GALIL_H__D6DB492D_2782_429E_A83A_AA485A42CBBC__INCLUDED_)
