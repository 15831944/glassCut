#if !defined(AFX_DLG_LIGHT_H__DEE3F8EA_F0D5_4E8B_BD2C_5BBCDEF9DE7B__INCLUDED_)
#define AFX_DLG_LIGHT_H__DEE3F8EA_F0D5_4E8B_BD2C_5BBCDEF9DE7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_light.h : header file
//

#define WM_LIGHT		WM_USER+111

/////////////////////////////////////////////////////////////////////////////
// CDlg_light dialog
#include "EditDoubleClick.h"

class CDlg_light : public CDialog
{
// Construction
public:
	CDlg_light(CWnd* pParent = NULL);   // standard constructor
	~CDlg_light();
// Dialog Data
	//{{AFX_DATA(CDlg_light)
	enum { IDD = IDD_DIALOG_CONFIG_LIGHT };
	CEditDoubleClick	m_editPosTime;
	CEditDoubleClick	m_editDECY;
	CEditDoubleClick	m_editDECX;
	CEditDoubleClick	m_editACCY;
	CEditDoubleClick	m_editACCX;
	CEditDoubleClick	m_edtLightY;
	CEditDoubleClick	m_edtLightX;
	CEditDoubleClick	m_edtY2;
	CEditDoubleClick	m_edtY1;
	CEditDoubleClick	m_edtY;
	CEditDoubleClick	m_edtX2;
	CEditDoubleClick	m_edtX1;
	CEditDoubleClick	m_edtX;
	CEditDoubleClick	m_edtStartY;
	CEditDoubleClick	m_edtStartX;
	CEditDoubleClick	m_edtSpeedY;
	CEditDoubleClick	m_edtSpeedX;
	CClrButton	m_btnF8;
	CClrButton	m_btnF7;
	long		m_lCoorX1;
	long		m_lCoorX2;
	long		m_lCoorY;
	long	m_lCoorY1;
	long	m_lCoorY2;
	long	m_lCoorX;
	long	m_lStartX;
	long	m_lStartY;
	long	m_lSpeedX;
	long	m_lSpeedY;
	double	m_dLightX;
	double	m_dLightY;
	long	m_lACCX;
	long	m_lACCY;
	long	m_lDECX;
	long	m_lDECY;
	long	m_lPosTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_light)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void OnChangeEdit(int iEdit); 
	void OnLanguage();

	
	// Generated message map functions
	//{{AFX_MSG(CDlg_light)
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnChangeEditX1();
	afx_msg void OnChangeEditX2();
	afx_msg void OnChangeEditY();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditY1();
	afx_msg void OnChangeEditY2();
	afx_msg void OnChangeEditX();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLight(WPARAM wParam, LPARAM lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBrush m_brush;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_LIGHT_H__DEE3F8EA_F0D5_4E8B_BD2C_5BBCDEF9DE7B__INCLUDED_)
