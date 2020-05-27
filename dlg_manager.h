//{{AFX_INCLUDES()
#include "captioninfo.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLG_MANAGER_H__9B22727F_8AEA_4F17_A1B6_3D0D1BDABF00__INCLUDED_)
#define AFX_DLG_MANAGER_H__9B22727F_8AEA_4F17_A1B6_3D0D1BDABF00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlg_manager.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dlg_manager dialog

class dlg_manager : public CDialog
{
// Construction
public:
	dlg_manager(CWnd* pParent = NULL);   // standard constructor
//    CFileManager    cFile;
// Dialog Data
	//{{AFX_DATA(dlg_manager)
	enum { IDD = IDD_DIALOG_FILEMANAGER };
	CListCtrl	m_remove;
	CListCtrl	m_disk;
	CCaptionInfo	m_demo;
	//}}AFX_DATA

	int       focus;
	
	void OnButtonRefresh(); 
		
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dlg_manager)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void OnLanguage();
	void OnFileShow();                             //显示优盘文件
	CString FindFile1();
	CString FindFile2();

    CString   filename;
	
		
	// Generated message map functions
	//{{AFX_MSG(dlg_manager)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnClickListdisk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListremove(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton10();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
    CUniButton		m_pButton[8];
	void InitButton();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_MANAGER_H__9B22727F_8AEA_4F17_A1B6_3D0D1BDABF00__INCLUDED_)
