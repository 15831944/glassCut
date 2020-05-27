#if !defined(AFX_DLG_KEYCHAR_H__EBD17BF5_4647_4DAF_837E_C3A67E1933C3__INCLUDED_)
#define AFX_DLG_KEYCHAR_H__EBD17BF5_4647_4DAF_837E_C3A67E1933C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_KeyChar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_KeyChar dialog

class CDlg_KeyChar : public CDialog
{
// Construction
public:
	CDlg_KeyChar(CWnd* pParent = NULL);   // standard constructor

	int		iPage; /* 显示页码 */
	BOOL	m_bIsPsw;
	
// Dialog Data
	//{{AFX_DATA(CDlg_KeyChar)
	enum { IDD = IDD_DIALOG_KEYCHAR };
	CClrButton	m_btnCancel;
	CClrButton	m_btnOk;
	CClrButton	m_btnZ;
	CClrButton	m_btnY;
	CClrButton	m_btnX;
	CClrButton	m_btnW;
	CClrButton	m_btnV;
	CClrButton	m_btnU;
	CClrButton	m_btnT;
	CClrButton	m_btnSub;
	CClrButton	m_btnShiftr;
	CClrButton	m_btnShiftl;
	CClrButton	m_btnSemicolon;
	CClrButton	m_btnS;
	CClrButton	m_btnR;
	CClrButton	m_btnQuotationMark;
	CClrButton	m_btnQ;
	CClrButton	m_btnPoint;
	CClrButton	m_btnP;
	CClrButton	m_btnO;
	CClrButton	m_btnN;
	CClrButton	m_btnM;
	CClrButton	m_btnL;
	CClrButton	m_btnK;
	CClrButton	m_btnJ;
	CClrButton	m_btnIncluder;
	CClrButton	m_btnIncludel;
	CClrButton	m_btnI;
	CClrButton	m_btnH;
	CClrButton	m_btnG;
	CClrButton	m_btnF;
	CClrButton	m_btnEquation;
	CClrButton	m_btnEnter;
	CClrButton	m_btnE;
	CClrButton	m_btnDivide;
	CClrButton	m_btnDirectory;
	CClrButton	m_btnD;
	CClrButton	m_btnComma;
	CClrButton	m_btnC;
	CClrButton	m_btnBackspace;
	CClrButton	m_btnB;
	CClrButton	m_btnA;
	CClrButton	m_btn9;
	CClrButton	m_btn8;
	CClrButton	m_btn7;
	CClrButton	m_btn6;
	CClrButton	m_btn5;
	CClrButton	m_btn4;
	CClrButton	m_btn3;
	CClrButton	m_btn2;
	CClrButton	m_btn1;
	CClrButton	m_btn0;
	CEdit	m_edtNew;
	CString	m_strNew;
	CString	m_strOld;
	CString	m_strTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_KeyChar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_greenbrush,m_yollowbrush,m_redbrush,m_bluebrush;
	void OnButtonFont(); /* 改变窗口字体 */
	void OnLanguage();
		
	// Generated message map functions
	//{{AFX_MSG(CDlg_KeyChar)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton0();
	afx_msg void OnButtonSub();
	afx_msg void OnButtonEquation();
	afx_msg void OnButtonBackspace();
	afx_msg void OnButtonQ();
	afx_msg void OnButtonW();
	afx_msg void OnButtonE();
	afx_msg void OnButtonR();
	afx_msg void OnButtonT();
	afx_msg void OnButtonY();
	afx_msg void OnButtonU();
	afx_msg void OnButtonI();
	afx_msg void OnButtonO();
	afx_msg void OnButtonP();
	afx_msg void OnButtonIncludel();
	afx_msg void OnButtonIncluder();
	afx_msg void OnButtonDirectory();
	afx_msg void OnButtonA();
	afx_msg void OnButtonS();
	afx_msg void OnButtonD();
	afx_msg void OnButtonF();
	afx_msg void OnButtonG();
	afx_msg void OnButtonH();
	afx_msg void OnButtonJ();
	afx_msg void OnButtonK();
	afx_msg void OnButtonL();
	afx_msg void OnButtonSemicolon();
	afx_msg void OnButtonQuotationmark();
	afx_msg void OnButtonEnter();
	afx_msg void OnButtonShiftl();
	afx_msg void OnButtonShiftr();
	afx_msg void OnButtonZ();
	afx_msg void OnButtonX();
	afx_msg void OnButtonC();
	afx_msg void OnButtonV();
	afx_msg void OnButtonB();
	afx_msg void OnButtonN();
	afx_msg void OnButtonM();
	afx_msg void OnButtonComma();
	afx_msg void OnButtonPoint();
	afx_msg void OnButtonDivide();
	virtual void OnCancel();
	afx_msg void OnOk();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_KEYCHAR_H__EBD17BF5_4647_4DAF_837E_C3A67E1933C3__INCLUDED_)
