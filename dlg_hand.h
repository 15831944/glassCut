//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_DLG_HAND_H__2A0E9D11_17D5_42A8_BB58_4D5A449597E8__INCLUDED_)
#define AFX_DLG_HAND_H__2A0E9D11_17D5_42A8_BB58_4D5A449597E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlg_hand.h : header file
//
#include "EditDoubleClick.h"

/////////////////////////////////////////////////////////////////////////////
// dlg_hand dialog

class dlg_hand : public CDialog
{
// Construction
public:
	dlg_hand(CWnd* pParent = NULL);   // standard constructor
    dlg_hand::~dlg_hand();
	
    void OnAxisADD(int nStep, int nAxis); 
    void OnAxisSUB(int nStep, int nAxis); 
	void OnSetDP();   /* ÷√Œª */
	void OpenDlgInit();	
	
// Dialog Data
	//{{AFX_DATA(dlg_hand)
	enum { IDD = IDD_DIALOG_HAND };
	CClrButton	m_clrBtnLabel;
	CEditDoubleClick	m_ez;
	CEditDoubleClick	m_ey;
	CEditDoubleClick	m_ex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dlg_hand)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void  OnLanguage();
	void  OnInitButton(); 
	void  OnCutWindow();
	void  OnErnInput();
    CUniButton	m_pClrButton[21];
	CString		m_strCon;
	CString		m_strStop;
	int			nStep;
	int 	    m_nHandNewBtn[4];
	int 	    m_nHandOldBtn[4];


	// Generated message map functions
	//{{AFX_MSG(dlg_hand)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonStop();
	afx_msg void OnButtonDirectx();
	afx_msg void OnButtonInversex();
	afx_msg void OnButtonDirecty();
	afx_msg void OnButtonInversey();
	afx_msg void OnButtonDirectz();
	afx_msg void OnButtonInversez();
	afx_msg void OnButtonPace();
	afx_msg LRESULT OnMouseDn(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonA1();
	afx_msg void OnButtonB1();
	afx_msg void OnButtonC1();
	afx_msg void OnButtonD1();
	afx_msg void OnButtonA2();
	afx_msg void OnButtonB2();	
	afx_msg void OnButtonD2();
	afx_msg void OnButtonA3();
	afx_msg void OnButtonC3();
	afx_msg void OnButtonD3();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnButtonCs8();
	afx_msg void OnButtonCs7();
	afx_msg void OnButtonCs6();	
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonHand();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_HAND_H__2A0E9D11_17D5_42A8_BB58_4D5A449597E8__INCLUDED_)










































