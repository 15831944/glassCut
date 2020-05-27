#if !defined(AFX_TABDLG_H__55E3D853_22AF_41F9_A054_71449CB04488__INCLUDED_)
#define AFX_TABDLG_H__55E3D853_22AF_41F9_A054_71449CB04488__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabDlg.h : header file
//
#include "RectOptDlg.h"
#include "PrintFrame.h"
/////////////////////////////////////////////////////////////////////////////
// CTabDlg dialog

class CTabDlg : public CDialog
{
// Construction
public:
	CTabDlg(CWnd* pParent = NULL);   // standard constructor

	void DrawTab(CDC *pDC, int i, CList<CNoRect, CNoRect>& lstRt);
	void DrawReport(CDC *pDC, CPrintInfo* pInfo);	//画报表
	void DrawTab(CDC *pDC, int nStart, int nEnd,  CList<CNoRect, CNoRect>& lstRt);	//画标签
	void SubTractNoRect(CList<CNoRect, CNoRect>& lstRt);	//获取排列好的矩形链表
	int statProdCount(int* num, CList<CRptDgm*, CRptDgm*>& lstDgm);		//统计矩形种类数
	void DrawThumbNail(CDC *pDC, CPoint ptThdGrd,int cnt, int nDgmIndex, CRectOptDlg *pRtOptDlg, CPrintInfo* pInfo);	//画缩略图
	void DrawThumbNail(CDC *pDC, CPoint ptThdGrd, int nDgmIndex, CRectOptDlg *pRtOptDlg, CPrintInfo* pInfo);	//画缩略图
	void DrawThrdGrid(CDC *pDC, CPoint ptThdGrd,CRectOptDlg *pRtOptDlg, int cnt, int* num, int nPage);
	void DrawThrdGrid(CDC *pDC, CPrintInfo* pInfo, int cnt, int nPage);

	void DrawShape(CDC *pDC, CString strCmd, CRptRect rt, CPoint ptOri, CRptDgm *pDgm, double g_dZoom);
	CString RotateSelect(double fBeginAngle, double fRotateAngel, CRptRect rt, CString strCmd);

// Dialog Data
	//{{AFX_DATA(CTabDlg)
	enum { IDD = IDD_DIALOG_TAB };
	CClrButton	m_clrBtnTabPreView;
	CClrButton	m_clrBtnSave;
	CClrButton	m_clrBtnExit;
	CClrButton	m_clrBtnTabPnt;
	CClrButton	m_clrBtnDisplay;
	CClrButton	m_clrBtnPNT;
	CClrButton	m_clrBtnPreView;
	CButton	m_btnA4;
	UINT	m_nFont;
	int		m_nTabLen;
	int		m_nTabWid;
	int		m_nRow;
	int		m_nCol;
	double	m_dLen;
	double	m_dWid;
	double	m_dMarinL;
	double	m_dMarinT;
	double	m_dRowSpace;
	double	m_dColSpace;
	double	m_dMarinB;
	double	m_dMarinR;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CRect m_rtDisplay;	//STATIC控件所在区域
	BOOL m_bBtnState;	//打印和预览是否按下
	CSize m_szA4;		//A4纸的大小
	CRect m_rtA4;		//A4纸在STATIC控件上的位置
	CSize m_szGrid;		//Report中表格的尺寸
	CPoint m_ptOri;		//标签在A4纸上起始点
	CFont m_fntTitle;	//Report中“方案汇总”所使用的字体
	CFont m_fntWord;	//Report中汉字使用的字体
	int m_nReportPage;	//Report要打印的页数
	long m_lDgmCnt;		//Report中缩略图的个数
	CFont m_fntRepDigit;//Report中数字所使用的字体
	double m_dScale;	//Tab中标签与打印的A4纸的比例
	double m_dZoom;		//Report中生成图形和A4纸的比例
	CFont m_fntContent;	//Tab中所有打印字符所使用的字体
	CPen m_penBorder;	//Report和Tab中划线所使用的画笔
	int m_nPage;		//Tab打印的页数
	int m_nSelect;		//为了区别打印Report还是Tab的标志
	int m_nLineHeight;	//Report中的行高度

	CSize m_szTab;		//标签纸大小
	double m_dRatio;	//Tab中标签和标签纸的比例

	double m_dAcc;

	int m_num[1000];
	int m_nCnt;

	// Generated message map functions
	//{{AFX_MSG(CTabDlg)
	afx_msg void OnBtnDisplay();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnExit();
	afx_msg void OnTabPreview();
	afx_msg void OnRepPreview();
	afx_msg void OnRepPnt();
	afx_msg void OnTabPnt();
	afx_msg void OnA4();
	afx_msg void OnTab();
	afx_msg void OnParamSave();
	//}}AFX_MSG
	//打印所需函数
	LRESULT OnBeginPrinting(WPARAM wParam,LPARAM lParam);
	LRESULT OnEndPrinting(WPARAM wParam,LPARAM lParam);
	LRESULT OnMyPrint(WPARAM wParam,LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()
	void OnLanguage();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABDLG_H__55E3D853_22AF_41F9_A054_71449CB04488__INCLUDED_)
