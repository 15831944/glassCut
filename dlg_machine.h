//{{AFX_INCLUDES()

//}}AFX_INCLUDES
#if !defined(AFX_DLG_MACHINE_H__4C60B352_B145_4A48_BCBF_475F261A9FB4__INCLUDED_)
#define AFX_DLG_MACHINE_H__4C60B352_B145_4A48_BCBF_475F261A9FB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dlg_machine.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// dlg_machine dialog
#include "EditDoubleClick.h"
#include "captioninfo.h"
class dlg_machine : public CDialog
{
// Construction
public:
	dlg_machine(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(dlg_machine)
	enum { IDD = IDD_DIALOG_MACHINE };
	CEditDoubleClick	m_edtPosY;
	CEditDoubleClick	m_editLabelY;
	CEditDoubleClick	m_editLabelX;
	CEditDoubleClick	m_editX2Move;
	CEditDoubleClick	m_edtAccZ;
	CEditDoubleClick	m_edtAccY;
	CEditDoubleClick	m_edtAccX;
	CEditDoubleClick	m_edtAccW;
	CEditDoubleClick	m_edtJourneyRD;
	CEditDoubleClick	m_edtJourneyRC;
	CEditDoubleClick	m_edtJourneyRB;
	CEditDoubleClick	m_edtJourneyRA;
	CEditDoubleClick	m_edtJourneyPD;
	CEditDoubleClick	m_edtJourneyPC;
	CEditDoubleClick	m_edtJourneyPB;
	CEditDoubleClick	m_edtJourneyPA;
	CEditDoubleClick	m_edtDecZ;
	CEditDoubleClick	m_edtDecY;
	CEditDoubleClick	m_edtDecX;
	CEditDoubleClick	m_edtDecW;
	CEditDoubleClick	m_edtPuslZ;
	CEditDoubleClick	m_edtPuslY;
	CEditDoubleClick	m_edtPuslX;
	CEditDoubleClick	m_edtPuslW;
	CEditDoubleClick	m_edtMachineZ;
	CEditDoubleClick	m_edtMachineY;
	CEditDoubleClick	m_edtMachineX;
	CEditDoubleClick	m_edtMachineW;
	CEditDoubleClick	m_edtBKZ;
	CEditDoubleClick	m_edtBKY;
	CEditDoubleClick	m_edtBKX;
	CEditDoubleClick	m_edtBKW;
	long	m_bkw;
	long	m_bkx;
	long	m_bky;
	long	m_bkz;
	double	m_puslw;
	double	m_puslx;
	double	m_pusly;
	double	m_puslz;
	double	m_machineX;
	double	m_machineY;
	CCaptionInfo	m_demo;
	double	m_handx;
	double	m_handy;
	double	m_handz;
	double	m_handw;
	double	m_zonex;
	double	m_zoney;
	double	m_zonez;
	double	m_zonew;
	long	m_journeypx;
	long	m_journeypw;
	long	m_journeypy;
	long	m_journeypz;
	long	m_journeyrw;
	long	m_journeyrx;
	long	m_journeyry;
	long	m_journeyrz;
	double	m_zerooffsetw;
	double	m_zerooffsetx;
	double	m_zerooffsety;
	double	m_zerooffsetz;
	CComboBox	m_directionw;
	CComboBox	m_directionz;
	CComboBox	m_directiony;
	CComboBox	m_directionx;
	CEditDoubleClick	m_editHandW;
	CEditDoubleClick	m_editHandZ;
	CEditDoubleClick	m_editHandY;
	CEditDoubleClick	m_editHandX;
	CEditDoubleClick	m_edtZoneSpeedW;
	CEditDoubleClick	m_edtZoneSpeedZ;
	CEditDoubleClick	m_edtZoneSpeedY;
	CEditDoubleClick	m_edtZoneSpeedX;
	CEditDoubleClick	m_edtZoneOffsetZ;
	CEditDoubleClick	m_edtZoneOffsetY;
	CEditDoubleClick	m_edtZoneOffsetX;
	CEditDoubleClick	m_edtZoneOffsetW;
	double	m_dAccW;
	double	m_dAccX;
	double	m_dAccY;
	double	m_dAccZ;
	double	m_dDecW;
	double	m_dDecX;
	double	m_dDecY;
	double	m_dDecZ;
	double	m_machineZ;
	double	m_machineW;
	int		m_nX2Move;
	int		m_nLabelX;
	int		m_nLabelY;
	int		m_nYGetLabel;
	//}}AFX_DATA
		

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dlg_machine)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	int			diskcheck1[10];
	CString		diskname1[10];
	
	void OnLanguage();
	void SaveData(); 
	
	// Generated message map functions
	//{{AFX_MSG(dlg_machine)
	afx_msg void OnButton1();
	afx_msg void OnButton4();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton8();
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnScale(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButton10();
	afx_msg void OnButton5();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
    CUniButton m_pButton[5];
	void InitButton();
	void OnLimit();
	void OnSuper();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_MACHINE_H__4C60B352_B145_4A48_BCBF_475F261A9FB4__INCLUDED_)





















