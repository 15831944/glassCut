#if !defined(AFX_DLG_CONFIG_H__480A16B7_4E86_44D5_9E76_0D220C31431E__INCLUDED_)
#define AFX_DLG_CONFIG_H__480A16B7_4E86_44D5_9E76_0D220C31431E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_config.h : header file
//
#define WM_LIGHT		WM_USER+111
#define WM_LOADING		WM_USER+112
#define WM_FATHOM		WM_USER+115
#define WM_OILING		WM_USER+116

class CDlg_light;
class CDlg_Loading;
class CDlg_Fathom;
class CDlg_Oiling;
/////////////////////////////////////////////////////////////////////////////
// CDlg_config dialog

class CDlg_config : public CDialog
{
// Construction
public:
	CDlg_config(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg_config();
	
// Dialog Data
	//{{AFX_DATA(CDlg_config)
	enum { IDD = IDD_DIALOG_CONFIG };
	int		m_nDxf;
	int		m_nLanguage;
	int		m_nLoad;
	int		m_nPhototube;
	int		m_nUnit;
	BOOL	m_bTeah1;
	BOOL	m_bTeah4;
	BOOL	m_bTeah5;
	BOOL	m_bTeah7;
	BOOL	m_bTeah9;
	int		m_nSort;
	BOOL	m_bMach1;
	int		m_nControl;
	BOOL	m_bMach2;
	BOOL	m_bShelf;
	BOOL	m_nLabelPos;
	BOOL    m_bPrint;//打印标签
	BOOL    m_bPosNeg;//实心刀头
	int		m_nSafeSwitch;
	//}}AFX_DATA

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_config)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CDlg_light		*pLight;
	CDlg_Loading	*pLoading;
	CDlg_Oiling		*pOiling; 

	CButton		m_ChkBox[8];
	CButton		m_RdoBox[24];
	
	
	void InitButton();
	void SaveData(); 
	void OnSetBtnText(); 
	void OnLanguage();
	void SetEnable(BOOL bEnable);
	BOOL OnIsHaveDialog(); 
		
	// Generated message map functions
	//{{AFX_MSG(CDlg_config)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonF8();
	afx_msg void OnButtonF1();
	afx_msg void OnButtonF2();
	afx_msg void OnButtonF4();
	afx_msg void OnButtonF5();
	afx_msg void OnButtonF10();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnReturnConfig(WPARAM wParam, LPARAM lParam); 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
	CUniButton		    m_pClrButton[6];
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_CONFIG_H__480A16B7_4E86_44D5_9E76_0D220C31431E__INCLUDED_)
