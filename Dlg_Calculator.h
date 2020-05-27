#if !defined(AFX_DLG_CALCULATOR_H__07647891_D94B_4D66_A64C_84F84331DC37__INCLUDED_)
#define AFX_DLG_CALCULATOR_H__07647891_D94B_4D66_A64C_84F84331DC37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Calculator.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CDlg_Calculator dialog

class CDlg_Calculator : public CDialog
{
// Construction
public:
	CDlg_Calculator(CWnd* pParent = NULL);   // standard constructor
	~CDlg_Calculator();
	void OnLanguage();
	
// Dialog Data
	//{{AFX_DATA(CDlg_Calculator)
	enum { IDD = IDD_DIALOG_CALCULATOR };
	CEdit	m_edtServoSp;
	CEdit	m_edtMachineSp;
	CClrButton	m_btnOK;
	CClrButton	m_btnCancel;
	CEdit	m_edtCalCode;
	CEdit	m_edtCode;
	CEdit	m_edtCalMo;
	CEdit	m_edtCalDe;
	long	m_nCalCode;
	long	m_nCode;
	long	m_nCalDenominator;
	long	m_nCalMolecule;
	double	m_dDistance;
	double	m_dPulse;
	int		m_nMode;
	CString	m_strHit;
	long	m_nMachineSp;
	long	m_nServoSp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Calculator)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	struct tagRadio
	{
		double	dMole;/* ·Ö×Ó */
		double	dDeno;/* ·ÖÄ¸ */
		long	nMole;
		long	nDeno;
	}; 
	typedef struct tagRadio Radio, *PRadio;
	

	CBrush m_brush;

	CString	strCode;
	CString	strDistance;
	CString	strPulse;
	CString	strBtnCal;
	CString	strBtnOk;
	CString	strRotate;
	
	void OnToLong(PRadio pVar); 
	void OnToLowestTerms(PRadio pVar); 
		
	// Generated message map functions
	//{{AFX_MSG(CDlg_Calculator)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnSetfocusEditCode();
	afx_msg void OnSetfocusEditDistance();
	afx_msg void OnSetfocusEditPulse();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSetfocusEditServosp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_CALCULATOR_H__07647891_D94B_4D66_A64C_84F84331DC37__INCLUDED_)





















