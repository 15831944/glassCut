// Dlg_NestSize.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_NestSize.h"
#include "Dlg_KeyNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_NestSize dialog


CDlg_NestSize::CDlg_NestSize(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_NestSize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_NestSize)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_NestSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_NestSize)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_NestSize, CDialog)
	//{{AFX_MSG_MAP(CDlg_NestSize)
	ON_BN_CLICKED(IDC_BUTTON_CS8, OnButtonCs8)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	ON_BN_CLICKED(IDC_BUTTON_CS10, OnButtonCs10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_NestSize message handlers

BOOL CDlg_NestSize::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	OnLanguage();
	// TODO: Add extra initializat
	InitValue();
	
	HRGN c;
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_PARA1);	
	m_pButton[0].SetFont(&g_fontEdit);
	m_pButton[0].SetBitMapID(IDB_BITMAP_SAVE1,IDB_BITMAP_SAVE2);	
	m_pButton[0].Create(g_strNestPara[1][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(640, 705), c, this, IDC_BUTTON_CS8); 
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[1].Create(g_strNestPara[6][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(850, 705), c, this, IDC_BUTTON_CS10); 
	DeleteObject(c);

  
	m_pEdit[0].SubclassDlgItem(IDC_EDIT1, this);
	m_pEdit[1].SubclassDlgItem(IDC_EDIT2, this);
	m_pEdit[2].SubclassDlgItem(IDC_EDIT3, this);
	m_pEdit[0].SetFont(&g_fontEdit);
	m_pEdit[1].SetFont(&g_fontEdit);
	m_pEdit[2].SetFont(&g_fontEdit);
	SetWindowPos(CWnd::GetOwner(),0,0,g_screen.x,g_screen.y,SWP_SHOWWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_NestSize::InitValue()
{
	CString strValue;
	
	GetPrivateProfileString("NESTPARA","BORDER","0.00",strValue.GetBuffer(MAX_PATH),MAX_PATH,g_strGCodePath + "NestPara.ini");
	SetDlgItemText(IDC_EDIT1,strValue);
	
	GetPrivateProfileString("NESTPARA","SIZEX","0.00",strValue.GetBuffer(MAX_PATH),MAX_PATH,g_strGCodePath + "NestPara.ini");
	SetDlgItemText(IDC_EDIT2,strValue);
	
	GetPrivateProfileString("NESTPARA","SIZEY","0.00",strValue.GetBuffer(MAX_PATH),MAX_PATH,g_strGCodePath + "NestPara.ini");
	SetDlgItemText(IDC_EDIT3,strValue);
}

void CDlg_NestSize::SaveValue()
{
	CString strValue;
	
	GetDlgItemText(IDC_EDIT1, strValue);
	WritePrivateProfileString("NESTPARA","BORDER",strValue,g_strGCodePath + "NestPara.ini");
	
	GetDlgItemText(IDC_EDIT2, strValue);
	WritePrivateProfileString("NESTPARA","SIZEX",strValue,g_strGCodePath + "NestPara.ini");
	
	GetDlgItemText(IDC_EDIT3, strValue);
	WritePrivateProfileString("NESTPARA","SIZEY",strValue,g_strGCodePath + "NestPara.ini");
}

void CDlg_NestSize::OnButtonCs8() 
{
	SaveValue();
	
	CDialog::OnOK();
}

void CDlg_NestSize::OnButtonCs10() 
{
	CDialog::OnCancel();
}

BOOL CDlg_NestSize::PreTranslateMessage(MSG* pMsg) 
{		
	if(pMsg->lParam==VK_TAB||pMsg->wParam==VK_TAB)
		return TRUE;
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
		return TRUE;
		// TODO: Add your specialized code here and/or call the base class
	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CDlg_NestSize::OnEditDouble(WPARAM wParam, LPARAM lParam)
{
	CString			strTmp;
	CDlg_KeyNumber	KeyNum;
	
	if(lParam==1)/* ÓÐ´¥ÃþÆÁ */
	{
		((CEdit *)GetDlgItem(wParam))->SetSel(0,-1);
		return 0;
	}
	
	GetDlgItemText(wParam,strTmp);
	KeyNum.m_strNew = KeyNum.m_strOld = strTmp;
	switch(wParam) 
	{
	case IDC_EDIT1:		
		GetDlgItemText(IDC_STATIC1,KeyNum.m_strTitle);			
		break;
	case IDC_EDIT2:		
		GetDlgItemText(IDC_STATIC2,KeyNum.m_strTitle);			
		break;
	case IDC_EDIT3:		
		GetDlgItemText(IDC_STATIC3,KeyNum.m_strTitle);			
		break;
	default:
		break;
	}
	if(KeyNum.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	return 0;
}

void CDlg_NestSize::OnLanguage()
{
	for(int index=0; index<AR_NESTPARA; index++)
	{
        if(g_strNestPara[index][g_iLanguage] == "NULL")
			g_strNestPara[index][g_iLanguage] = "";
		SetDlgItemText(atoi(g_strNestPara[index][2]), g_strNestPara[index][g_iLanguage]);
	}
}
