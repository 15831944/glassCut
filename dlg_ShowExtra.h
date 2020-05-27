#if !defined(AFX_DLG_SHOWEXTRA_H__F5482CA9_2069_4EEA_9B21_801EB7B866F0__INCLUDED_)
#define AFX_DLG_SHOWEXTRA_H__F5482CA9_2069_4EEA_9B21_801EB7B866F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlg_ShowExtra.h : header file
//
#define EXTRASHOWORIGNX  1024
/////////////////////////////////////////////////////////////////////////////
// Cdlg_ShowExtra dialog
class Cdlg_ShowExtra : public CDialog
{
// Construction
public:
	Cdlg_ShowExtra(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cdlg_ShowExtra)
	enum { IDD = IDD_DIALOG_SHOWEXTRA };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cdlg_ShowExtra)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cdlg_ShowExtra)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int   m_nShowExpandX;//扩展显示器X
	int   m_nShowExpandY;//扩展显示器Y
	int   m_nShowShelf;    //是否显示货架号1显示；0显示厂名
    void SetMaxShow(double fScaleX,double fScaleY);//设置全屏显示的比例
private:   
    CDC MemuDc;//虚拟DC
	double m_dScale;
	TEXTMETRIC m_tm;
	int m_nShelfFont;//画图时客户名称的大小
	void DrawGraph();
	void DrawRect(CDC* pDCMenu,int ox,int oy,int x,int y,int nFill=1);
	void DrawTextOut(int x,int y,const char* cstr,int nFontBig = 22);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_SHOWEXTRA_H__F5482CA9_2069_4EEA_9B21_801EB7B866F0__INCLUDED_)
