#if !defined(AFX_RECTOPTDLG_H__C732FF22_CE8B_40D2_9211_95CC68CDB381__INCLUDED_)
#define AFX_RECTOPTDLG_H__C732FF22_CE8B_40D2_9211_95CC68CDB381__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RectOptDlg.h : header file
//
#include ".\\grid\\GridCtrl.h"
#include "RtOpt.h"
#include "Bender.h"
#include "EditDoubleClick.h"
/////////////////////////////////////////////////////////////////////////////
// CRectOptDlg dialog

class CRectOptDlg : public CDialog
{
// Construction
public:
	CRectOptDlg(CWnd* pParent = NULL);   // standard constructor
	~CRectOptDlg();
// Dialog Data
	//{{AFX_DATA(CRectOptDlg)
	enum { IDD = IDD_DIALOG_RECTOPT };
	CEditDoubleClick	m_DEdit8;
	CEditDoubleClick	m_DEdit7;
	CEditDoubleClick	m_DEdit6;
	CEditDoubleClick	m_DEdit5;
	CEditDoubleClick	m_DEdit4;
	CEditDoubleClick	m_DEdit3;
	CEditDoubleClick	m_DEdit2;
	CEditDoubleClick	m_DEdit12;
	CEditDoubleClick	m_DEdit11;
	CEditDoubleClick	m_DEdit10;
	CEditDoubleClick	m_DEdit1;
	CClrButton	m_ClrBtnExcel;
	CString	m_strGrind;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRectOptDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRectOptDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnButtonF1();
	afx_msg void OnButtonF2();
	afx_msg void OnButtonF3();
	afx_msg void OnButtonF4();
	afx_msg void OnButtonF5();
	afx_msg void OnBtnDisplay();
	afx_msg void OnBtnNext();
	afx_msg void OnBtnPrev();
	afx_msg void OnBtnGrap();
	afx_msg void OnBtnSend();
	afx_msg void OnChangeEdit10();
	afx_msg void OnBtnExcel();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CBrush m_bkBrush;				//背景画刷		
	double m_dScale;				//显示比例	
	CUniButton	m_pButton[10];		//按钮数组
	p_stuRectEdit p_FirstRectInf;	//矩形数据的头指针
	p_stuRectEdit p_CurrentRectInf; //当前编辑的矩形数据
	void DrawRect(CDC* pDCMenu,int ox,int oy,int x,int y,int nFill=1);//绘制矩形
	void OnLanguage();
	//保存原片信息
	void WriteEditInf();
	//初始化原片信息
	void InitSheetPar();

public:
	void InitButton();				//初始化按钮	
	void AddNewRectInf();			//为GridCtrl控件添加新的一行矩形信息
	void OnInitGrid();				//初始化GridCtrl控件
	void AddGrid();					//向窗口中添加GridCtrl控件
	void DeleRectInf();				//删除当索引指向的矩形信息
	void DeleAllRectInf();			//删除GridCtrl控件所有的矩形信息
	void DrawArrowhead(CDC *pDC, CGrPoint &ptBgn, CGrPoint &ptEnd);			//画箭头
	void LineRevolve(GR_LINE &output, CGrPoint ptCenter, CGrPoint ptRef, double fSweepArc, double fRadius);		//解析直线

	void DrawShape(CDC *pDC, CString strCmd, CRptRect rt);//画异形
	CString RotateSelect(double fBeginAngle, double fRotateAngel, CRptRect rt, CString strCmd);		//旋转异形

	//添加dll时要增加的变量
	CRtOpt m_RtOptDll;				//动态链接库变量
	int m_nIndexCurrDgm;			//当前显示图在链表中的索引
	CRect m_rtDisplay;				//显示矩形排列信息的矩形
	BOOL InitData();				//初始化矩形排列信息
	CGridCtrl	m_Grid;				//mfcGridCtrl控件
	CString m_strRawLen;			//原片长
	CString m_strRawWid;			//原片宽
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECTOPTDLG_H__C732FF22_CE8B_40D2_9211_95CC68CDB381__INCLUDED_)
