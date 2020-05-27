//{{AFX_INCLUDES()
#include "captioninfo.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLG_SN_H__D2C1E9BA_9180_4EB3_B507_A3603F1B203F__INCLUDED_)
#define AFX_DLG_SN_H__D2C1E9BA_9180_4EB3_B507_A3603F1B203F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlg_sn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dlg_sn dialog
#include "EditDoubleClick.h"

class dlg_sn : public CDialog
{
// Construction
public:
	dlg_sn(CWnd* pParent = NULL);   // standard constructor
	void CheckNum(); //显示验证次数
    _ConnectionPtr m_pCon;   //ADO应用
	_RecordsetPtr m_pRec;
	int m_nDayHead;
// Dialog Data
	//{{AFX_DATA(dlg_sn)
	enum { IDD = IDD_DIALOG_SN };
	CClrButton	m_button9;
	CStatic	m_checksta;
	CEditDoubleClick	m_edtSn;
	CClrButton	m_button8;
	CClrButton	m_button7;
	CCaptionInfo	m_caption;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dlg_sn)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd  *pWnd[7];
	int m_nState;//判断是到期了。
	void OnReSetCtl();
	void OnCancelPassword(); 
	void OnLanguage();	
    void OnModityLimit(int nYear,int nMonth, int nDay);
	// Generated message map functions
	//{{AFX_MSG(dlg_sn)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButton9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_SN_H__D2C1E9BA_9180_4EB3_B507_A3603F1B203F__INCLUDED_)
