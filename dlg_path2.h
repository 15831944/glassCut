#if !defined(AFX_DLG_PATH2_H__0CBCABCB_3954_44F5_BBDA_8DDF4C6D0E50__INCLUDED_)
#define AFX_DLG_PATH2_H__0CBCABCB_3954_44F5_BBDA_8DDF4C6D0E50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlg_path2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dlg_path2 dialog

#include "EditDoubleClick.h"
#include "ReadGcode.h"
class dlg_path2 : public CDialog
{
	// Construction
public:
	dlg_path2(CWnd* pParent = NULL);   // standard constructor
	
	CString m_strFilename;//当前选择的文件名
	int     m_iStyle;//0:cxf;1:dxf;2:gcode.
	CString m_strFilePath;//中间的文件夹目录
	
	// Dialog Data
	//{{AFX_DATA(dlg_path2)
	enum { IDD = IDD_DIALOG_PATHTWO };
	CListBox	m_ListGcode;
	CListCtrl	m_list;
	CString	    m_file;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dlg_path2)
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	void OnLanguage();
	void OnReSetCtl();	
	void GotoFowardMenu();//返回上级目录		
	// Generated message map functions
	//{{AFX_MSG(dlg_path2)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton7();
	afx_msg void OnButton5();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton10();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
	CImageList m_img;
	CUniButton	m_pButton[7];
	CString m_strHeadShow;
	CString m_strFileShow;//文件目录用于显示Gcode用
	CReadGcode m_ReadGcode;//G代码读取处理类
	void InitButton();
	void ProcessGcodeInf();//得到G代码的文本，画图信息,显示并画图
	void ShowListGcode();//显示G代码文本信息
	void DrawGcode(CDC *pMenuDc);//画图

	//将圆弧打碎成小线段,并画图，解决直接画圆的精度丢失
    //pMenuDc:画图用虚拟dc；arc:圆弧信息；interval:画图比例
	void BreakDrawArc(CDC *pMenuDc, tagArc arc, double dScale);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_PATH2_H__0CBCABCB_3954_44F5_BBDA_8DDF4C6D0E50__INCLUDED_)
