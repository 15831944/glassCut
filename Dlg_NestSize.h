#if !defined(AFX_DLG_NESTSIZE_H__4E86450B_C213_4385_9FF3_D3AABB587357__INCLUDED_)
#define AFX_DLG_NESTSIZE_H__4E86450B_C213_4385_9FF3_D3AABB587357__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_NestSize.h : header file
//

#include "EditDoubleClick.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg_NestSize dialog

class CDlg_NestSize : public CDialog
{
// Construction
public:
	CDlg_NestSize(CWnd* pParent = NULL);   // standard constructor

	void OnLanguage();
	void SaveValue();
	void InitValue();//初始化控件的值1
	
// Dialog Data
	//{{AFX_DATA(CDlg_NestSize)
	enum { IDD = IDD_DIALOG_NESTSIZE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_NestSize)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEditDoubleClick m_pEdit[3];
	// Generated message map functions
	//{{AFX_MSG(CDlg_NestSize)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCs7();
	afx_msg void OnButtonCs8();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonCs10();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
	CUniButton	m_pButton[2];
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_NESTSIZE_H__4E86450B_C213_4385_9FF3_D3AABB587357__INCLUDED_)
