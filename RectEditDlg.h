#if !defined(AFX_RECTEDITDLG_H__FF7D683D_4502_4433_955F_1C9324137DFD__INCLUDED_)
#define AFX_RECTEDITDLG_H__FF7D683D_4502_4433_955F_1C9324137DFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RectEditDlg.h : header file
//
#include ".\grid\GridCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CRectEditDlg dialog

class CRectEditDlg : public CDialog
{
// Construction
public:
	CRectEditDlg(CWnd* pParent = NULL);   // standard constructor
	~CRectEditDlg();

// Dialog Data
	//{{AFX_DATA(CRectEditDlg)
	enum { IDD = IDD_DIALOG_RECT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRectEditDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRectEditDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnButtonF1();
	afx_msg void OnButtonF2();
	afx_msg void OnButtonF3();
	afx_msg void OnButtonF4();
	afx_msg void OnButtonF5();
	afx_msg void OnCancel();
	afx_msg void OnOK();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CUniButton	m_pButton[7];
	CGridCtrl	m_Grid;
	CImageList	m_ImageList;
	p_stuRectEdit p_FirstRectInf;//矩形数据的头指针
	p_stuRectEdit p_CurrentRectInf;//当前编辑的矩形数据
    double m_dScale;
	void InitButton();
	void AddNewRectInf();
	void AddGrid();
	void DeleRectInf();
	void DeleAllRectInf();
	void OnInitGrid();
	void DrawRectEdit(CDC* pDCMenu);
	void DrawLine(CDC* pDCMenu,int ox,int oy,int x,int y);
	void DrawRect(CDC* pDCMenu,int ox,int oy,int x,int y,int nFill=1);
	void DrawGraph(CDC* pDCMenu,p_stuRectEdit pRectTemp,int nRow,int nCol);
	void SaveGcode();
	//写小片信息
	void WriteLittleInf(FILE *file);

	//合并横线，当前的矩形指针，起点的dx1，终点的dx2. 合并后的。
	//返回0需要不合并，返回1需要合并，返回2本直线不处理,已经被合并过。
	//向左合并，左边舍去
	int CRectEditDlg::CombinationLineX(p_stuRectEdit pEditTemp,double dy,double dx1,double dx2,double &d1,double &d2);

	//合并横线，当前的矩形指针，起点的dy1，终点的dy2. 合并后的。
	//返回0需要不合并，返回1需要合并，返回2本直线不处理,已经被合并过。
	//向上合并，下边舍去
	int CRectEditDlg::CombinationLineY(p_stuRectEdit pEditTemp,double dx,double dy1,double dy2,double &d1,double &d2);

	//判断起点在不在已有的范围内。有返回true
	bool StartPosIsRect(p_stuRectEdit pEditTemp);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECTEDITDLG_H__FF7D683D_4502_4433_955F_1C9324137DFD__INCLUDED_)
