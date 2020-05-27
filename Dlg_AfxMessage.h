#if !defined(AFX_DLG_AFXMESSAGE_H__F2D5182E_14AB_49DF_984F_1FB35D085867__INCLUDED_)
#define AFX_DLG_AFXMESSAGE_H__F2D5182E_14AB_49DF_984F_1FB35D085867__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_AfxMessage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_AfxMessage dialog

class CDlg_AfxMessage : public CDialog
{
// Construction
public:
	CDlg_AfxMessage(CWnd* pParent = NULL);   // standard constructor

	CString		strAfxMessage;
	CString		strAfxTitle;
	CString		strAfxYES;
	CString		strAfxNO;
	BOOL		bYesNo;
	
// Dialog Data
	//{{AFX_DATA(CDlg_AfxMessage)
	enum { IDD = IDD_DIALOG_AFXMESSAGE };
	CClrButton	m_btnOk;
	CClrButton	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_AfxMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_AfxMessage)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_AFXMESSAGE_H__F2D5182E_14AB_49DF_984F_1FB35D085867__INCLUDED_)
