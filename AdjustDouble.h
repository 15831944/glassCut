#if !defined(AFX_ADJUSTDOUBLE_H__DD27455E_40FC_4159_9F2F_8C799C3BC854__INCLUDED_)
#define AFX_ADJUSTDOUBLE_H__DD27455E_40FC_4159_9F2F_8C799C3BC854__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdjustDouble.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdjustDouble dialog

class CAdjustDouble : public CDialog
{
// Construction
public:
	CAdjustDouble(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAdjustDouble)
	enum { IDD = IDD_DIALOG_ADJUSTDOUBLE };
	CClrButton	m_CbSet;
	CClrButton	m_CbBack;
	CClrButton	m_CbStop;
	CClrButton	m_CbStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdjustDouble)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAdjustDouble)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonStart();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonStop();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//得到两门轴的tp值
	void GetDoubleTP();

	//初始化校正用的速度，加速度，程序下载
    void AdjustInitGalil();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADJUSTDOUBLE_H__DD27455E_40FC_4159_9F2F_8C799C3BC854__INCLUDED_)
