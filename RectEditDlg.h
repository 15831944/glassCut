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
	p_stuRectEdit p_FirstRectInf;//�������ݵ�ͷָ��
	p_stuRectEdit p_CurrentRectInf;//��ǰ�༭�ľ�������
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
	//дСƬ��Ϣ
	void WriteLittleInf(FILE *file);

	//�ϲ����ߣ���ǰ�ľ���ָ�룬����dx1���յ��dx2. �ϲ���ġ�
	//����0��Ҫ���ϲ�������1��Ҫ�ϲ�������2��ֱ�߲�����,�Ѿ����ϲ�����
	//����ϲ��������ȥ
	int CRectEditDlg::CombinationLineX(p_stuRectEdit pEditTemp,double dy,double dx1,double dx2,double &d1,double &d2);

	//�ϲ����ߣ���ǰ�ľ���ָ�룬����dy1���յ��dy2. �ϲ���ġ�
	//����0��Ҫ���ϲ�������1��Ҫ�ϲ�������2��ֱ�߲�����,�Ѿ����ϲ�����
	//���Ϻϲ����±���ȥ
	int CRectEditDlg::CombinationLineY(p_stuRectEdit pEditTemp,double dx,double dy1,double dy2,double &d1,double &d2);

	//�ж�����ڲ������еķ�Χ�ڡ��з���true
	bool StartPosIsRect(p_stuRectEdit pEditTemp);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECTEDITDLG_H__FF7D683D_4502_4433_955F_1C9324137DFD__INCLUDED_)
