//{{AFX_INCLUDES()

//}}AFX_INCLUDES
#if !defined(AFX_DLG_SCAN_H__6A80F200_6FDC_4838_A45B_5554FA04361B__INCLUDED_)
#define AFX_DLG_SCAN_H__6A80F200_6FDC_4838_A45B_5554FA04361B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_scan.h : header file
//

#include "EditDoubleClick.h"
#include "lamp.h"
#define WM_SCAN			WM_USER+110	/* 向扫描窗口发消息，报告扫描状态 */

/////////////////////////////////////////////////////////////////////////////
// CDlg_scan dialog

class CDlg_scan : public CDialog
{
// Construction
public:
	CDlg_scan(CWnd* pParent = NULL);   // standard constructor
    ~CDlg_scan();
	void InitFontLanguage();
// Dialog Data
	//{{AFX_DATA(CDlg_scan)
	enum { IDD = IDD_DIALOG_SCAN };
	CEditDoubleClick	m_edtBeginX;
	CEditDoubleClick	m_edtBeginY;
	CEditDoubleClick	m_edtScanPace;
	CEditDoubleClick	m_edtCenterX;
	CEditDoubleClick	m_edtCenterY;
	CEditDoubleClick	m_edtSpeed;
	double	m_dBeginX;
	double	m_dBeginY;
	double	m_dScanPace;
	CLamp	m_ocxLedScan;
	double	m_dCenterX;
	double	m_dCenterY;
	double	m_dSpeed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_scan)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_scan)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCs1();
	afx_msg void OnButtonCs2();
	afx_msg void OnButtonCs3();
	afx_msg UINT OnScanState(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonCs4();
	afx_msg void OnButtonCs5();
	afx_msg void OnButtonCs6();
	afx_msg void OnButtonCs7();
	afx_msg void OnButtonCs8();
	afx_msg void OnButtonCs9();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
	CUniButton	m_pButton[10];	
	void OnSaveParameter(); 
	void OnCutWindow();
	void InitButton();
public:
	void OnButtonCs10();
	void InitParameter();		
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_SCAN_H__6A80F200_6FDC_4838_A45B_5554FA04361B__INCLUDED_)
