#if !defined(AFX_DLG_BACKUP_H__F9CC9814_B5DB_4B0D_A766_99ADA688BE8C__INCLUDED_)
#define AFX_DLG_BACKUP_H__F9CC9814_B5DB_4B0D_A766_99ADA688BE8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_BackUp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_BackUp dialog

class CDlg_BackUp : public CDialog
{
// Construction
public:
	CDlg_BackUp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg_BackUp)
	enum { IDD = IDD_DIALOG_BACKUP };
	CClrButton	m_clrBtn2;
	CClrButton	m_clrBtnCancel;
	CClrButton	m_clrBtn4;
	CClrButton	m_clrBtn3;
	CClrButton	m_clrBtn1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_BackUp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg_BackUp)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton14();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	CString		m_strParaCopyPath;
	CString		m_strParaBuckupPath;


	/* ���������ݵ����ص��ļ��� */
	void OnParaBuckup(); 
	
	/* �����������ص��ļ��н��лָ� */
	void OnParaRenew(); 
	
	/* ���������ݵ�USB�豸 */
	void OnUsbParaBuckup(); 
	
	/* ��������USB�豸���лָ� */
	void OnUsbParaRenew(); 

	/* �ж��ļ����Ƿ���� */
	BOOL FolderExist(CString strPath); 

	/* ���Ŀ¼�е����� */
	void DeleteDirectoryContext(CString strPath);


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_BACKUP_H__F9CC9814_B5DB_4B0D_A766_99ADA688BE8C__INCLUDED_)
