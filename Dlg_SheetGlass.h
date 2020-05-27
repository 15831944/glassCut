#if !defined(AFX_Dlg_SHEETGLASS_H__2192C4F7_05ED_4B2F_8C71_94BD812B3509__INCLUDED_)
#define AFX_Dlg_SHEETGLASS_H__2192C4F7_05ED_4B2F_8C71_94BD812B3509__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_SheetGlass.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSheetGlass dialog
#include ".\grid\GridCtrl.h"
#include <vector>
using namespace std;
class CDlg_SheetGlass : public CDialog
{
// Construction
public:
	CDlg_SheetGlass(CWnd* pParent = NULL);   // standard constructor
	~CDlg_SheetGlass();
// Dialog Data
	//{{AFX_DATA(CDlg_SheetGlass)
	enum { IDD = IDD_DIALOG_SHEETGLASS };
	CGridCtrl m_GridSheet;
	CTime	m_oleTimeStart;
	CTime	m_oleTimeEnd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_SheetGlass)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	_ConnectionPtr m_pConSheet;   //ADO应用数据库文件
	CUniButton	m_pButton[4];
	vector<stuSheetGlass> m_vtGlassSheet;//原片信息
	void OnLanguage();
	void OnInitGrid(); 
	void InitDataAdo();
	void InitButton();

	void ReadDatabase();//读数据库记录
	_RecordsetPtr SearchRec(char *chRec);	
	void SortData();//数据库排序
	// Generated message map functions
	//{{AFX_MSG(CDlg_SheetGlass)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();	
	afx_msg void OnButton2();	
	afx_msg void OnButton8();	
	afx_msg void OnButton10();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Dlg_SHEETGLASS_H__2192C4F7_05ED_4B2F_8C71_94BD812B3509__INCLUDED_)
