// GraphDlg.h : header file
//

#if !defined(AFX_GRAPHDLG_H__A5641234_7BD5_4FA6_B276_32F90D495043__INCLUDED_)
#define AFX_GRAPHDLG_H__A5641234_7BD5_4FA6_B276_32F90D495043__INCLUDED_

#include "MyFrame.h"	// Added by ClassView
#include "GrEditor.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGraphDlg dialog

class CGraphDlg : public CDialog
{
// Construction
public:
	CGraphDlg(CWnd* pParent = NULL);	// standard constructor
	CGrEditor *m_pGrEditor;
// Dialog Data
	//{{AFX_DATA(CGraphDlg)
	enum { IDD = IDD_GRAPH_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	/*返回异形的矩形的大小，即长乘宽*/
	POINT2D OnGetBaseRect(CString strText);
	void InitButton();
	BOOL LoadPictures(LPCTSTR lpszDir, UINT nPicType);

	CMyFrame m_wndPicBrowse;
	CMyFrame m_wndPicClass;
	HICON m_hIcon;
	CUniButton	m_pButton[5];
	// Generated message map functions
	//{{AFX_MSG(CGraphDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnButtonF1();
	afx_msg void OnButtonF2();
	afx_msg void OnButtonF3();
	afx_msg void OnButtonF6();
	afx_msg void OnButtonF10();
	//}}AFX_MSG
	afx_msg LRESULT UsermsgListWndMsg(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	bool	m_bBottero;//由bottero编辑方式进入图库
	bool    m_bRectEdit;//有矩形编辑方式进入图库
	POINT2D m_Rect;    //编辑方式下插入图库图形的最大尺寸


	bool    m_bRtOpt;		//以矩形方式进入
	POINT2D m_p2DRect;		//设置添加的图形的长宽
	char m_cShape[1024];	//存放异形图形编号
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHDLG_H__A5641234_7BD5_4FA6_B276_32F90D495043__INCLUDED_)
