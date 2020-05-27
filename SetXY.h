#if !defined(AFX_SETXY_H__0BB55E3A_2FDB_49FC_8392_348A1203B629__INCLUDED_)
#define AFX_SETXY_H__0BB55E3A_2FDB_49FC_8392_348A1203B629__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetXY.h : header file
//
#include "EditDoubleClick.h"
/////////////////////////////////////////////////////////////////////////////
// CSetXY dialog

class CSetXY : public CDialog
{
// Construction
public:
	CSetXY(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetXY)
	enum { IDD = IDD_DIALOG_XY };
	CClrButton	m_clrBCancel;
	CClrButton	m_clrBOk;
	CEditDoubleClick	m_editY;
	CEditDoubleClick	m_editX;
	double	m_dX;
	double	m_dY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetXY)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetXY)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETXY_H__0BB55E3A_2FDB_49FC_8392_348A1203B629__INCLUDED_)
