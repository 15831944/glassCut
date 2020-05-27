//{{AFX_INCLUDES()

//}}AFX_INCLUDES
#if !defined(AFX_DLG_MOTION_H__0B0F003E_A48B_4384_8FA7_9936A2A983DA__INCLUDED_)
#define AFX_DLG_MOTION_H__0B0F003E_A48B_4384_8FA7_9936A2A983DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlg_motion.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dlg_motion dialog
#include "EditDoubleClick.h"

class dlg_motion : public CDialog
{
// Construction
public:
	dlg_motion(CWnd* pParent = NULL);   // standard constructor
	int          iLanguage;
	
// Dialog Data
	//{{AFX_DATA(dlg_motion)
	enum { IDD = IDD_DIALOG_MOTION };
	CEditDoubleClick	m_editMaxRadius;
	CEditDoubleClick	m_editLocationDCC;
	CEditDoubleClick	m_editLocationACC;
	CEditDoubleClick	m_editFeedDec;
	CEditDoubleClick	m_editFeedAcc2;
	CEditDoubleClick	m_EditFeed;
	CEditDoubleClick	m_edtvt;
	CEditDoubleClick	m_edtEllispeScale;
	CEditDoubleClick	m_edtRapidMove;
	CEditDoubleClick	m_edtFeedVdec;
	CEditDoubleClick	m_edtFeedVacc;
	CEditDoubleClick	m_edtFeedMove;
	CEditDoubleClick	m_edtTangent;
	CEditDoubleClick	m_edtMinRadius;
	CEditDoubleClick	m_edtMinCornerSp;
	CEditDoubleClick	m_edtMinCorner;
	CEditDoubleClick	m_edtMinArcSp;
	CEditDoubleClick	m_edtMaxCorner;
	CEditDoubleClick	m_edtCenterY;
	CEditDoubleClick	m_edtCenterX;
	double	m_dFeedMove;
	double	m_dFeedVacc;
	double	m_dFeedVdec;
	double	m_dRapidMove;
	double	m_vt;
	double	m_dFeed;
	double	m_dFeedAcc2;
	double	m_dFeedDec2;
	double	m_dLocationACC;
	double	m_dLocationDCC;
	double	m_dPlineSp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dlg_motion)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	
	void OnLanguage();
	void OnChange();
	
	// Generated message map functions
	//{{AFX_MSG(dlg_motion)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonOk();
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnScale(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButton10();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:	
	CUniButton	m_pButton[7];
	/* 输入数据后，切换到下一个EDIT框 */
	void ChangeFocusEdit();
	void InitButton();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_MOTION_H__0B0F003E_A48B_4384_8FA7_9936A2A983DA__INCLUDED_)
