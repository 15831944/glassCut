#if !defined(AFX_DLG_BOTTERO_H__23C980FC_597D_4B0D_A59E_5CB38007075B__INCLUDED_)
#define AFX_DLG_BOTTERO_H__23C980FC_597D_4B0D_A59E_5CB38007075B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_bottero.h : header file
//
#include "EditDoubleClick.h"

/////////////////////////////////////////////////////////////////////////////
// CDlg_bottero dialog

class CDlg_bottero : public CDialog
{
// Construction
public:
	CDlg_bottero(CWnd* pParent = NULL);   // standard constructor
	void InitButton();
	void InitBtro();
		
// Dialog Data
	//{{AFX_DATA(CDlg_bottero)
	enum { IDD = IDD_DIALOG_BOTTERO };
	CEditDoubleClick	m_edtValue;
	CClrButton	m_btnUpdate;
	CListCtrl	m_lstBottero;
	CString	m_strCommValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_bottero)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CUniButton	m_pButton[7];
	
	p_Command	pFirstComm, pCurrComm, pLastComm;
	p_Command	pCommX,pCommY,pCommZ,pCommW,pCommQ,pCommR;
	CString		strCommand,strOldComm;
	float		fOldValue;
	int			nCountComm;
	int			nClickComm;
	float		fValueX,fValueY,fValueZ,fValueW,fValueQ,fValueR;
	ofstream	file;//文件指针
	BOOL		bModifyFlag;
	int         m_nRemainderX;
	int         m_nRemainderY;
	int         m_nRemainderZ;
	int         m_nRemainderW;
	int         m_nRemainderQ;
	int         m_nRemainderR;


	void begin();//新建文件，开始写文件
	void limits(float x, float y, float x4, float y4 );//控制绘图界限
	void zooma();//全屏显示
	void line(float x0, float y0, float x3, float y3);//画直线
	void Arc(float x0, float y0, float x2, float y2, float x3, float y3);
	void gend();//结束写文件
	void OnLanguage();
		
	void OnFreeLastCommand(p_Command stuCommand); 
	void OnFreeCommand(p_Command stuCommand); 
	pSegment OnAddSegment(pSegment stuCurrSegment); 
	p_Command OnAddBotteroCommand(p_Command stuCurrCurr); 
	POINT2D OnGetBiasEndValue(char chCom,pSegment stu_pSegmentX,pSegment stu_pSegmentY,p_Command pCommX,p_Command pCommY,float fValue); /* 获取斜线端点值 */
	POINT2D OnGetBaseRectPoint(pSegment stu_pSegmentX,pSegment stu_pSegmentY,p_Command pCommX,p_Command pCommY);				/* 获取矩形起点，用来画异形 */
	BOOL CombinationLines(int n,pSegment stu_pSegment);	//合并重刀线
	void CombinationLineX(pSegment pSegment1,pSegment pSegment2);	//向前合并X方向的线
	void CombinationLineY(pSegment pSegment1,pSegment pSegment2);	//向前合并Y方向的线
	void CombinationAllLines();					//合并重刀线
	void CommandCovAutocadScript();				//命令转换为CAD脚本文件
	void CommandCovGcode(int nStyle);						//保存为G代码文件nstyle0:保存；nstyle1发送
	POINT2D CommandToolDn(FILE *fileG, int nIndex, pSegment pSegt, p_Command pComm);	//保存为G代码文件
	BOOL CommandIsOnePoint(POINT2D pOld, pSegment pSegt);			//保存为G代码文件
	BOOL OnValidCommand(char ch,float fValue); 
	pSegment GetLastSegment(p_Command pComm);	//获得最后一个数据段
	POINT2D GetCurrRect();						//获取当前编辑的矩形
	/*-----------------------------------------------
	CString strCmd：从图库传过来的异形信息
	-----------------------------------------------*/
	void GetOtherGraph(CString strCmd);			//从异形图形获得数据，转成异形段
	/*--------------------------------------------------
	POINT2D p：图形的偏移距离
	pSegment stuNowSegment：指定拷贝的首结点
	pSegment stuGraphSegment：指定图形链表的首结点
	--------------------------------------------------*/
	pSegment CDlg_bottero::OnAddOtherGraph(POINT2D p, pSegment stuNowSegment, pSegment stuGraphSegment); 
	/*--------------------------------------------------
	pSegment stuGraphSegment：指定图形链表的首结点
	--------------------------------------------------*/
	void OnFreeGraph(pSegment stuGraphSegment);

	/*返回异形的矩形的大小，即长乘宽*/
	POINT2D OnGetBaseRect(CString strText);
	
	void DataShowClear();//显示剩余信息的数据全部清空。

	//添加矩形
	pRectDraw AddBotteroRect(pRectDraw pRectCurr); 

	//写小片信息
	void WriteLittleInf(FILE *file);
	// Generated message map functions
	//{{AFX_MSG(CDlg_bottero)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListBottero(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonUpdateA();
	afx_msg void OnButtonF1();
	afx_msg void OnButtonF2();
	afx_msg void OnButtonF3();
	afx_msg void OnButtonF4();
	afx_msg void OnButtonF5();
	afx_msg void OnButtonF6();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg LRESULT OnEditDouble(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonF10();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void  OnCutWindow();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_BOTTERO_H__23C980FC_597D_4B0D_A59E_5CB38007075B__INCLUDED_)
