#if !defined(AFX_CTEST_H__3AB7861B_D066_4868_B980_2FBFA0AC3293__INCLUDED_)
#define AFX_CTEST_H__3AB7861B_D066_4868_B980_2FBFA0AC3293__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CTest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCTest dialog

class CCTest : public CDialog
{
// Construction
public:
	CCTest(CWnd* pParent = NULL);   // standard constructor
	~CCTest();
	int		m_nTestType;

// Dialog Data
	//{{AFX_DATA(CCTest)
	enum { IDD = IDD_DIALOG_TEST };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCTest)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio9();
	afx_msg void OnRadio10();
	afx_msg void OnRadio11();
	afx_msg void OnRadio12();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void Onlanguge();
	void WriteCatercorner();//根据机床尺寸写对角线测试的g代码
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTEST_H__3AB7861B_D066_4868_B980_2FBFA0AC3293__INCLUDED_)
