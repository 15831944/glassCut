//{{AFX_INCLUDES()


//}}AFX_INCLUDES
#if !defined(AFX_DLG_AFFIRM_H__FB9DED44_C697_48E7_AC53_8691F904B2D9__INCLUDED_)
#define AFX_DLG_AFFIRM_H__FB9DED44_C697_48E7_AC53_8691F904B2D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_affirm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_affirm dialog
#include "benderDlg.h"
#include "EditDoubleClick.h"
#include "lamp.h"

class CDlg_affirm : public CDialog
{
// Construction
public:
	CDlg_affirm(CWnd* pParent = NULL);   // standard constructor
	
	double		dHeight;
	double		dLength;
	double		m_dLength;
	double		m_dHeight;
	long		m_lCoorX1;
	long		m_lCoorX2;
	long		m_lCoorY;
	void OnEndFind(); /* 停止寻边 */


				
// Dialog Data
	//{{AFX_DATA(CDlg_affirm)
	enum { IDD = IDD_DIALOG_AFFIRM };
	CString	m_strInfo;
	CLamp	m_ocxDisplay;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_affirm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	double		dSlantingAngle;
	long		lScale;
	CWinThread* m_handThread;
	long		lDisplay;

	POINT2D		p1,p2,p3;
	
	

	void OnLanguage();
	POINT2D OnCalcPoint(POINT2D p1,POINT2D p2,POINT2D p3); /* 计算点垂直于直线的交点 */
	CPoint SetGlassPointPos(CPoint p); 
	void OnButtonTimer(); 
	void OnBeginFind(); 

	
	// Generated message map functions
	//{{AFX_MSG(CDlg_affirm)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_AFFIRM_H__FB9DED44_C697_48E7_AC53_8691F904B2D9__INCLUDED_)





















