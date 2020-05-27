#if !defined(AFX_GREDITOR_H__8246C890_5BE7_43AB_926E_5BF603726E81__INCLUDED_)
#define AFX_GREDITOR_H__8246C890_5BE7_43AB_926E_5BF603726E81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrEditor.h : header file
//
#include "stdafx.h"
#include "bender.h"
#include "grMath.h"
#include "RoundAngle.h"
#include "GrPath.h"
#include "PicWnd.h"
#include "UISetting.h"	// Added by ClassView

#define MAX_UI_SETTINGs			300

/////////////////////////////////////////////////////////////////////////////
// CGrEditor dialog

class CGrEditor : public CDialog
{
// Construction
public:
	CGrEditor(CWnd* pParent=NULL);
	CUISetting* GetUISetting(LPCTSTR lpszIndex);
	void InitUISetting(LPCTSTR lpszIndex);
	void MakeGCodeFile(int nStyle);//0±£´æ;1·¢ËÍ
	void Clean();
	void UpdateGraph();
	void SetGraph(const PIC_ATTR *pPicAttr);
    CString MakeNestCode();
	PIC_ATTR m_picAttr;

	const GR_CLIP& GetClip() { return m_clip; };

// Dialog Data
	//{{AFX_DATA(CGrEditor)
	enum { IDD = IDD_GRAPH_EDITOR };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrEditor)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CUISetting m_uiSettings[MAX_UI_SETTINGs];
	CGrPath m_grPath;
	BOOL OpenFileG(CString strOpenFile);
	void ProcDxf();
	void ProcYixing3();
	void ProcYixing2();
	void ProcYixing1();
	void ProcHexagon();
	void ProcPentagon();
	void ProcRectangle();
	void ProcTriangle();
	void ProcCircle();
	double GetEditValue(CEdit *pEdit);
	BOOL m_bDlgInitialized;
	GR_CLIP m_clip;
	CDC m_dcGraph;
	CRect m_rcGraph;
	void ResetUI();

	// Generated message map functions
	//{{AFX_MSG(CGrEditor)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnKillfocusEditPara01();
	afx_msg void OnKillfocusEditPara02();
	afx_msg void OnKillfocusEditPara03();
	afx_msg void OnKillfocusEditPara04();
	afx_msg void OnKillfocusEditPara05();
	afx_msg void OnKillfocusEditPara06();
	afx_msg void OnKillfocusEditPara07();
	afx_msg void OnKillfocusEditPara08();
	afx_msg void OnKillfocusEditPara09();
	afx_msg void OnKillfocusEditPara10();
	afx_msg void OnKillfocusEditPara11();
	afx_msg void OnKillfocusEditPara12();
	afx_msg void OnKillfocusEditPara13();
	afx_msg void OnKillfocusEditPara14();
	afx_msg void OnKillfocusEditPara15();
	afx_msg void OnKillfocusEDITClipX1();
	afx_msg void OnKillfocusEDITClipX2();
	afx_msg void OnKillfocusEDITClipY1();
	afx_msg void OnKillfocusEDITClipY2();
	afx_msg void OnButtonTest();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GREDITOR_H__8246C890_5BE7_43AB_926E_5BF603726E81__INCLUDED_)
