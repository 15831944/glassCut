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

	CBrush m_bkBrush;				//������ˢ		
	double m_dScale;				//��ʾ����	
	CUniButton	m_pButton[10];		//��ť����
	p_stuRectEdit p_FirstRectInf;	//�������ݵ�ͷָ��
	p_stuRectEdit p_CurrentRectInf; //��ǰ�༭�ľ�������
	void DrawRect(CDC* pDCMenu,int ox,int oy,int x,int y,int nFill=1);//���ƾ���
	void OnLanguage();
	//����ԭƬ��Ϣ
	void WriteEditInf();
	//��ʼ��ԭƬ��Ϣ
	void InitSheetPar();

public:
	void InitButton();				//��ʼ����ť	
	void AddNewRectInf();			//ΪGridCtrl�ؼ�����µ�һ�о�����Ϣ
	void OnInitGrid();				//��ʼ��GridCtrl�ؼ�
	void AddGrid();					//�򴰿������GridCtrl�ؼ�
	void DeleRectInf();				//ɾ��������ָ��ľ�����Ϣ
	void DeleAllRectInf();			//ɾ��GridCtrl�ؼ����еľ�����Ϣ
	void DrawArrowhead(CDC *pDC, CGrPoint &ptBgn, CGrPoint &ptEnd);			//����ͷ
	void LineRevolve(GR_LINE &output, CGrPoint ptCenter, CGrPoint ptRef, double fSweepArc, double fRadius);		//����ֱ��

	void DrawShape(CDC *pDC, CString strCmd, CRptRect rt);//������
	CString RotateSelect(double fBeginAngle, double fRotateAngel, CRptRect rt, CString strCmd);		//��ת����

	//���dllʱҪ���ӵı���
	CRtOpt m_RtOptDll;				//��̬���ӿ����
	int m_nIndexCurrDgm;			//��ǰ��ʾͼ�������е�����
	CRect m_rtDisplay;				//��ʾ����������Ϣ�ľ���
	BOOL InitData();				//��ʼ������������Ϣ
	CGridCtrl	m_Grid;				//mfcGridCtrl�ؼ�
	CString m_strRawLen;			//ԭƬ��
	CString m_strRawWid;			//ԭƬ��
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECTOPTDLG_H__C732FF22_CE8B_40D2_9211_95CC68CDB381__INCLUDED_)
