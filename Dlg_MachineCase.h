//{{AFX_INCLUDES()
#include "displayctrl.h"
//}}AFX_INCLUDES
#if !defined(AFX_DLG_MACHINECASE_H__26BF1E9B_4CE2_4A03_A220_D5606F84D4BA__INCLUDED_)
#define AFX_DLG_MACHINECASE_H__26BF1E9B_4CE2_4A03_A220_D5606F84D4BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_MachineCase.h : header file
//


#define WM_ALMINPUT		WM_USER+108	/* �����ڵ����룬���͵���Ͻ�����ʾ */
#define WM_ALMOUTPUT	WM_USER+109	/* �����ڵ���������͵���Ͻ�����ʾ */

/////////////////////////////////////////////////////////////////////////////
// CDlg_MachineCase dialog

class CDlg_MachineCase : public CDialog
{
// Construction
public:
	CDlg_MachineCase(CWnd* pParent = NULL);   // standard constructor
	
	int nData[8];
	
// Dialog Data
	//{{AFX_DATA(CDlg_MachineCase)
	enum { IDD = IDD_DIALOG_MACHINE_CASE };
	CListCtrl	m_lstAlarm;
	CCaptionInfo	m_ocxDemo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_MachineCase)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	pPARAALARM		m_pRTAlarm;		/* ʵʱ���� */
	int				m_nAlarmCounts;	/* ʵʱ�������� */
	pALARM			m_pHistoryAlarm;/* ��ʷ���� */
	
	CUniButton	    m_pButton[4];
	CDisplayCtrl	m_ocxDisplay[4];
	
	int		nInput[64];
	int		nOutput[48];
	BOOL	nType;	

	
	/* ��ʼ���б�� */
	void OnInitList(); 

	void OnInitAlarmList(BOOL bCurrAlarm); 

	/* ��ʼ����ʾ�ؼ� */
	void OnInitDisplay(); 

	void OnFirstInput(); /* ����� */
	
	void OnReceiveOut(int base, long nValue, int nGetOut[48]);
	
	void OnReceiveIn(int nBase, int nNum);
	
	int OnGetBinaryInt(int nByte, int nNum);

	void OnDisplayOutput(); /* ����� */
		
	void OnDisplayInput(); /* ����� */
		
	void OnButton2();

	// Generated message map functions
	//{{AFX_MSG(CDlg_MachineCase)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
 	afx_msg void OnButton3();
	afx_msg LRESULT OnStateInput(WPARAM wParam, LPARAM lParam); 
	afx_msg LRESULT OnStateOutput(WPARAM wParam, LPARAM lParam); 
	afx_msg void OnDblClickDisplay1();
	afx_msg void OnButton4();
	afx_msg void OnButtonCs10();
	afx_msg void OnPaint();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	
	void OnLanguage();
	CString OnChangeLange(CString str); 
	void InitButton();
		
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_MACHINECASE_H__26BF1E9B_4CE2_4A03_A220_D5606F84D4BA__INCLUDED_)
