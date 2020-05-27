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
	void DrawReport(CDC *pDC, CPrintInfo* pInfo);	//������
	void DrawTab(CDC *pDC, int nStart, int nEnd,  CList<CNoRect, CNoRect>& lstRt);	//����ǩ
	void SubTractNoRect(CList<CNoRect, CNoRect>& lstRt);	//��ȡ���кõľ�������
	int statProdCount(int* num, CList<CRptDgm*, CRptDgm*>& lstDgm);		//ͳ�ƾ���������
	void DrawThumbNail(CDC *pDC, CPoint ptThdGrd,int cnt, int nDgmIndex, CRectOptDlg *pRtOptDlg, CPrintInfo* pInfo);	//������ͼ
	void DrawThumbNail(CDC *pDC, CPoint ptThdGrd, int nDgmIndex, CRectOptDlg *pRtOptDlg, CPrintInfo* pInfo);	//������ͼ
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
	CRect m_rtDisplay;	//STATIC�ؼ���������
	BOOL m_bBtnState;	//��ӡ��Ԥ���Ƿ���
	CSize m_szA4;		//A4ֽ�Ĵ�С
	CRect m_rtA4;		//A4ֽ��STATIC�ؼ��ϵ�λ��
	CSize m_szGrid;		//Report�б��ĳߴ�
	CPoint m_ptOri;		//��ǩ��A4ֽ����ʼ��
	CFont m_fntTitle;	//Report�С��������ܡ���ʹ�õ�����
	CFont m_fntWord;	//Report�к���ʹ�õ�����
	int m_nReportPage;	//ReportҪ��ӡ��ҳ��
	long m_lDgmCnt;		//Report������ͼ�ĸ���
	CFont m_fntRepDigit;//Report��������ʹ�õ�����
	double m_dScale;	//Tab�б�ǩ���ӡ��A4ֽ�ı���
	double m_dZoom;		//Report������ͼ�κ�A4ֽ�ı���
	CFont m_fntContent;	//Tab�����д�ӡ�ַ���ʹ�õ�����
	CPen m_penBorder;	//Report��Tab�л�����ʹ�õĻ���
	int m_nPage;		//Tab��ӡ��ҳ��
	int m_nSelect;		//Ϊ�������ӡReport����Tab�ı�־
	int m_nLineHeight;	//Report�е��и߶�

	CSize m_szTab;		//��ǩֽ��С
	double m_dRatio;	//Tab�б�ǩ�ͱ�ǩֽ�ı���

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
	//��ӡ���躯��
	LRESULT OnBeginPrinting(WPARAM wParam,LPARAM lParam);
	LRESULT OnEndPrinting(WPARAM wParam,LPARAM lParam);
	LRESULT OnMyPrint(WPARAM wParam,LPARAM lParam);
	
	DECLARE_MESSAGE_MAP()
	void OnLanguage();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABDLG_H__55E3D853_22AF_41F9_A054_71449CB04488__INCLUDED_)
