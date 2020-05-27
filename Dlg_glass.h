#if !defined(AFX_DLG_GLASS_H__F9FA78B3_EE1A_4D7E_A752_0F61D9C87F2B__INCLUDED_)
#define AFX_DLG_GLASS_H__F9FA78B3_EE1A_4D7E_A752_0F61D9C87F2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_glass.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_glass dialog
#include ".\grid\GridCtrl.h"
#include "EditDoubleClick.h"

class CDlg_glass : public CDialog
{
// Construction
public:
	CDlg_glass(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_glass)
	enum { IDD = IDD_DIALOG_GLASS };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_glass)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	int nItem;	
	CImageList	m_ImageList;
	CGridCtrl	m_Grid;
	int m_nMM[12];
	CUniButton   m_pButton[2];

	void InitButton();
	void OnSavePressure();		
	void OnLanguage();
	void OnScale();
	void OnInitGrid(); 
		
	// Generated message map functions
	//{{AFX_MSG(CDlg_glass)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton8();
	afx_msg void OnButton10();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_GLASS_H__F9FA78B3_EE1A_4D7E_A752_0F61D9C87F2B__INCLUDED_)
