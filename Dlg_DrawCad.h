//{{AFX_INCLUDES()
#include "gridcad.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLG_DRAWCAD_H__79F45FE5_6C49_40DF_AA2F_072A4AED9690__INCLUDED_)
#define AFX_DLG_DRAWCAD_H__79F45FE5_6C49_40DF_AA2F_072A4AED9690__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_DrawCad.h : header file
//
#include "EditDoubleClick.h"

/////////////////////////////////////////////////////////////////////////////
// CDlg_DrawCad dialog

class CDlg_DrawCad : public CDialog
{
// Construction
public:
	CDlg_DrawCad(CWnd* pParent = NULL);   // standard constructor
	CImageList bookImageList;	
	void OnOpenFile();		//Cxf代码程序打开.	
// Dialog Data
	//{{AFX_DATA(CDlg_DrawCad)
	enum { IDD = IDD_DIALOG_DRAW_CAD };
	CClrButton	m_clrBMove;
	CClrButton	m_clrBZoom;
	CClrButton	m_clrbGrid2;
	CClrButton	m_clrbGrid;
	CClrButton	m_clrbSpace;
	CClrButton	m_clrbReverse;
	CClrButton	m_clrbUp;
	CClrButton	m_clrbDown;
	CClrButton	m_clrbAgain;
	CClrButton	m_clrbSort;
	CClrButton	m_clrbPickUp;
	CStatic	m_stcBegin;
	CStatic	m_stcEnd;
	CStatic	m_stcMid;
	CEditDoubleClick	m_edtMidY;
	CEditDoubleClick	m_edtMidX;
	CEditDoubleClick	m_edtEndY;
	CEditDoubleClick	m_edtEndX;
	CEditDoubleClick	m_edtBeginY;
	CEditDoubleClick	m_edtBeginX;
	CScrollBar	m_ocxScrollY;
	CScrollBar	m_ocxScrollX;
	CTreeCtrl	m_TreeCtl;
	CGridCAD	m_GridCad;
	double	m_dBeginX;
	double	m_dBeginY;
	double	m_dEndX;
	double	m_dEndY;
	double	m_dMidX;
	double	m_dMidY;
	int		m_nRdoTool;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_DrawCad)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	PGRAPH	m_pGraphDie;	/* 模具图形 */	
	PGRAPH	m_pGraphWork;	/* 工件外形 */	
	PGRAPH	m_pGraphTool;	/* 刀具图形 */	

	SHORT m_unLeft;//向左移动,过了最左边有效
	SHORT m_unRight;//向右移动,过了最右边有效
	SHORT m_unUp;//向上移动,过了最左边有效
	SHORT m_unDown;//向下移动,过了最右边有效
// Implementation
protected:
	
	int		m_nPage;
	BOOL	m_bClickTree;

	void OnInitGridCAD(); 
	void OnInitList(); /* 显示数据 */


	void OnGetCadPos(); 
		
	// Generated message map functions
	//{{AFX_MSG(CDlg_DrawCad)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton8();
	afx_msg void OnButton7();
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangedTreectl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDrawGraphGridcadctrl1();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMovePositionGridcadctrl1();
	afx_msg void OnClickTreectl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSetfocusEditBeginx();
	afx_msg void OnSetfocusEditBeginy();
	afx_msg void OnSetfocusEditMidx();
	afx_msg void OnSetfocusEditMidy();
	afx_msg void OnSetfocusEditEndx();
	afx_msg void OnSetfocusEditEndy();
	afx_msg void OnKillfocusEditPosition();
	afx_msg void OnButtonCs10();
	afx_msg void OnButtonSpace();
	afx_msg void OnButtonGrid();
	afx_msg void OnButtonUp();
	afx_msg void OnButtonDown();
	afx_msg void OnButtonForword();
	afx_msg void OnButtonPickup();
	afx_msg void OnButtonSort();
	afx_msg void OnButtonGrid2();
	afx_msg void OnButtonAgain();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnButtonZoom();
	afx_msg void OnButtonPan();
	afx_msg void OnUpdateDataGridcadctrl();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int		m_nCurrSegmentIndex;
	int		m_nCurrGraphIndex;
	int		m_nScrollMaxPos;
	int		m_nScrollMinPos;

	/* 获取当前图形的起点、终点数据 */
	void GetCurrGraphData(); 
	/* 获取最后图形的起点、终点数据 */
	void GetLastGraphData();
	/* 设置当前图形的起点、终点数据 */
	void SetCurrGraphData();  
	/* 输入数据后，切换到下一个EDIT框 */
	void ChangeFocusEdit(); 

	
	/* 获取当前图形的相关信息 */
	void GetCurrGraphInfo();  

	/* 设置当前图形的相关信息 */
	PGRAPHLIST SetCurrGraphInfo();

	void OnLanguage();

	CUniButton	m_pButton[8];
	void InitButton();

	//根据当前的行数,在上移下移以后调用
	void SetTreeFocus();

	/************************************************************************/
	/* 根据选择的节点选中状态，设置相关节点的选中状态                   */
	/************************************************************************/
	void SetItemCheckState(HTREEITEM item, BOOL bCheck);

	/************************************************************************/
	/* 设置子节点的选中状态                                              */
	/************************************************************************/
	void SetChildCheck(HTREEITEM item, BOOL bCheck);

	/************************************************************************/
	/* 设置父节点选中状态                                                 */
	/************************************************************************/
	void SetParentCheck(HTREEITEM item, BOOL bCheck);


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_DRAWCAD_H__79F45FE5_6C49_40DF_AA2F_072A4AED9690__INCLUDED_)
