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
	ofstream	file;//�ļ�ָ��
	BOOL		bModifyFlag;
	int         m_nRemainderX;
	int         m_nRemainderY;
	int         m_nRemainderZ;
	int         m_nRemainderW;
	int         m_nRemainderQ;
	int         m_nRemainderR;


	void begin();//�½��ļ�����ʼд�ļ�
	void limits(float x, float y, float x4, float y4 );//���ƻ�ͼ����
	void zooma();//ȫ����ʾ
	void line(float x0, float y0, float x3, float y3);//��ֱ��
	void Arc(float x0, float y0, float x2, float y2, float x3, float y3);
	void gend();//����д�ļ�
	void OnLanguage();
		
	void OnFreeLastCommand(p_Command stuCommand); 
	void OnFreeCommand(p_Command stuCommand); 
	pSegment OnAddSegment(pSegment stuCurrSegment); 
	p_Command OnAddBotteroCommand(p_Command stuCurrCurr); 
	POINT2D OnGetBiasEndValue(char chCom,pSegment stu_pSegmentX,pSegment stu_pSegmentY,p_Command pCommX,p_Command pCommY,float fValue); /* ��ȡб�߶˵�ֵ */
	POINT2D OnGetBaseRectPoint(pSegment stu_pSegmentX,pSegment stu_pSegmentY,p_Command pCommX,p_Command pCommY);				/* ��ȡ������㣬���������� */
	BOOL CombinationLines(int n,pSegment stu_pSegment);	//�ϲ��ص���
	void CombinationLineX(pSegment pSegment1,pSegment pSegment2);	//��ǰ�ϲ�X�������
	void CombinationLineY(pSegment pSegment1,pSegment pSegment2);	//��ǰ�ϲ�Y�������
	void CombinationAllLines();					//�ϲ��ص���
	void CommandCovAutocadScript();				//����ת��ΪCAD�ű��ļ�
	void CommandCovGcode(int nStyle);						//����ΪG�����ļ�nstyle0:���棻nstyle1����
	POINT2D CommandToolDn(FILE *fileG, int nIndex, pSegment pSegt, p_Command pComm);	//����ΪG�����ļ�
	BOOL CommandIsOnePoint(POINT2D pOld, pSegment pSegt);			//����ΪG�����ļ�
	BOOL OnValidCommand(char ch,float fValue); 
	pSegment GetLastSegment(p_Command pComm);	//������һ�����ݶ�
	POINT2D GetCurrRect();						//��ȡ��ǰ�༭�ľ���
	/*-----------------------------------------------
	CString strCmd����ͼ�⴫������������Ϣ
	-----------------------------------------------*/
	void GetOtherGraph(CString strCmd);			//������ͼ�λ�����ݣ�ת�����ζ�
	/*--------------------------------------------------
	POINT2D p��ͼ�ε�ƫ�ƾ���
	pSegment stuNowSegment��ָ���������׽��
	pSegment stuGraphSegment��ָ��ͼ��������׽��
	--------------------------------------------------*/
	pSegment CDlg_bottero::OnAddOtherGraph(POINT2D p, pSegment stuNowSegment, pSegment stuGraphSegment); 
	/*--------------------------------------------------
	pSegment stuGraphSegment��ָ��ͼ��������׽��
	--------------------------------------------------*/
	void OnFreeGraph(pSegment stuGraphSegment);

	/*�������εľ��εĴ�С�������˿�*/
	POINT2D OnGetBaseRect(CString strText);
	
	void DataShowClear();//��ʾʣ����Ϣ������ȫ����ա�

	//��Ӿ���
	pRectDraw AddBotteroRect(pRectDraw pRectCurr); 

	//дСƬ��Ϣ
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
