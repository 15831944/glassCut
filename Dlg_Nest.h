#if !defined(AFX_DLG_NEST_H__A0CFE7DB_AD47_42F8_86C0_3D6F65C7CEA6__INCLUDED_)
#define AFX_DLG_NEST_H__A0CFE7DB_AD47_42F8_86C0_3D6F65C7CEA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_Nest.h : header file
//

struct	CNestNode
{
	CPoint		ptOffset;
	CPoint		ptCenter;
	char		szCmd[5000];
	CString		strName;
	CRgn		rgnRect;
	CNestNode*	pPrev;
	CNestNode*	pNext;
};

struct CNestNodeHead
{
	char		chName[30];
	int			nNum;
	CNestNode	*pDown;
	CNestNodeHead *pPrev;
	CNestNodeHead *pNext;
};

/////////////////////////////////////////////////////////////////////////////
// CDlg_Nest dialog

class CDlg_Nest : public CDialog
{
// Construction
public:
	CDlg_Nest(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg_Nest();	
	void InitPara();
	CStdioFile filePoint;
	double GetRotateAngle(CPoint ptMouse, double &fBeginAngle, double &fRotateAngle);
	void RotateSelect(double fBeginAngle, double fRotateAngel);
	void GetLibRange(CRgn *rgnLib);
	int Nest(int &nNum, CRgn *rgnNest);
	void AddNest(CString strType, int nNum, CString strCmd);
	void Draw();	
	int partnom;
	int patredit;
	POINT2D m_p2DRect;//设置添加的图形的长宽
// Dialog Data
	//{{AFX_DATA(CDlg_Nest)
	enum { IDD = IDD_DIALOG_NEST };
	CListBox	m_pListNest;
	CListBox	m_pList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_Nest)
	public:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_nNestBaseX, m_nNestBaseY;//2009-4-10
	void OnMovePicture();
	double addY;
	double addX;
	int numberfile;
	int SelectParaName;
	void Showpart();
	double m_fDrawRate;				//记录画图的比例
	int m_nBoardX, m_nBoardY;		//记录钢板的尺寸
	double m_fBorder;				//保存套料时的间距
	void GetCurrentNode(int nNode, CNestNode *pNode);
	int m_nModifyMode;				//保存当前编辑状态，是移动还是旋转0为移动，1为旋转
	CRgn m_rgMove;
	CNestNode* m_pNodeSelect;
	CPoint m_ptCatch;
	int m_nSelect;
	void SaveGCode();		//保存G代码
	void FreeNestNode(); 
	void Ondelpart(); 

	CRgn			m_rgnBoard;		//存储钢板的区域
	CNestNodeHead	*m_pHead;		//记录所有图形链表的头
	CNestNodeHead	*m_pTail;		//记录所有图形链表的尾
	int m_nAddTime;			//记录添加图形的次数
	// Generated message map functions
	//{{AFX_MSG(CDlg_Nest)
	virtual BOOL OnInitDialog();
	afx_msg void OnMoveUP();
	afx_msg void OnMoveDOWN();
	afx_msg void OnMoveLEFT();
	afx_msg void OnMoveRight();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeList1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnButtonCs1();
	afx_msg void OnButtonCs2();
	afx_msg void OnButtonCs3();
	afx_msg void OnButtonCs4();
	afx_msg void OnButtonCs6();
	afx_msg void OnButtonCs8();
	afx_msg void OnButtonCs5();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonCs10();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
	CUniButton	m_pButton[8];
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_NEST_H__A0CFE7DB_AD47_42F8_86C0_3D6F65C7CEA6__INCLUDED_)
