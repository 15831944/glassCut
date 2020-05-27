// dlg_sn.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "dlg_sn.h"
#include "Dlg_KeyChar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dlg_sn dialog

 
dlg_sn::dlg_sn(CWnd* pParent /*=NULL*/)
	: CDialog(dlg_sn::IDD, pParent)
{
	//{{AFX_DATA_INIT(dlg_sn)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nDayHead = 0;
	m_nState = 0; 
}


void dlg_sn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dlg_sn)
	DDX_Control(pDX, IDC_BUTTON9, m_button9);
	DDX_Control(pDX, IDC_STATIC1, m_checksta);
	DDX_Control(pDX, IDC_EDIT1, m_edtSn);
	DDX_Control(pDX, IDC_BUTTON8, m_button8);
	DDX_Control(pDX, IDC_BUTTON7, m_button7);
	DDX_Control(pDX, IDC_DEMO10CTRL1, m_caption);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dlg_sn, CDialog)
	//{{AFX_MSG_MAP(dlg_sn)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dlg_sn message handlers 
BOOL dlg_sn::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();
	m_button7.SetColour(g_crFontC);
	m_button8.SetColour(g_crFontD);
	m_button9.SetColour(g_crFontC);
	OnReSetCtl();
	// TODO: Add extra initialization here
	CheckNum();
	OnLanguage();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL dlg_sn::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->lParam==VK_ESCAPE||pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->lParam==VK_F4||pMsg->wParam==VK_F4)
		return TRUE;
	if(pMsg->lParam==VK_TAB||pMsg->wParam==VK_TAB)
		return TRUE;
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void dlg_sn::OnReSetCtl()
{
	CRect     rc;
	pWnd[0] = GetDlgItem(IDC_DEMO10CTRL1);
	pWnd[1] = GetDlgItem(IDC_STATIC1);         pWnd[1]->SetFont(&g_fontStatic);
	pWnd[2] = GetDlgItem(IDC_EDIT1);           pWnd[2]->SetFont(&g_fontEdit);
	pWnd[3] = GetDlgItem(IDC_BUTTON7);         pWnd[3]->SetFont(&g_fontButton);
	pWnd[4] = GetDlgItem(IDC_BUTTON8);         pWnd[4]->SetFont(&g_fontButton);
	pWnd[5] = GetDlgItem(IDC_BUTTON9);         pWnd[5]->SetFont(&g_fontButton);

}

void dlg_sn::OnButton7() 
{
	CString szTemp;
	CWnd::GetDlgItemText(IDC_EDIT1,szTemp);
	if (szTemp.GetLength()>13)
	{
		OnButton9();
		return;
	}
	if(szTemp==g_arr_strLimit[0][3])
	{
		OnCancelPassword();
	}
	else
	{
		return;
	}	
	CDialog::OnOK(); 
}

void dlg_sn::OnButton8() 
{ 
	//	exit(2);
	//*	
	if (m_nState == 0)
	{
        CDialog::OnCancel();
		return;
	}
	HANDLE hToken; 
	TOKEN_PRIVILEGES tkp; 
	
	
	if (!OpenProcessToken(GetCurrentProcess(),          // Get a token for this process. 
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		MessageBox("OpenProcessToken","",MB_OK); 
	
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); // Get the LUID for the shutdown privilege. 
	
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0); // Get the shutdown privilege for this process. 
	
	if (GetLastError() != ERROR_SUCCESS) 
		MessageBox("AdjustTokenPrivileges","",MB_OK); 
	
	if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0)) 
		MessageBox("ExitWindowsEx","",MB_OK); 
	//*/
//	CDialog::OnCancel();
}

void dlg_sn::OnCancelPassword() 
{
	HasWriteValue("",TIME_SECRET);
}

LRESULT dlg_sn::OnEditDouble(WPARAM wParam, LPARAM lParam) 
{
	CString				strTmp;
	CDlg_KeyChar		KeyChar;
	
	if(lParam==1)/* 有触摸屏 */
	{
		((CEdit *)GetDlgItem(wParam))->SetSel(0,-1);
		return 0;
	}
	
	CWnd::GetDlgItemText(wParam,strTmp);
	KeyChar.m_strNew = KeyChar.m_strOld = strTmp;
// 	switch(wParam) 
// 	{
// 	case IDC_EDIT1:	GetDlgItemText(IDC_STATIC1,KeyChar.m_strTitle);	break;
// 	default:
// 		break;
// 	}
	if(KeyChar.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyChar.m_strNew);
	
	return 0;
}

void dlg_sn::CheckNum()
{ 
	if (m_nDayHead < 10)
	{
		CString checkstr = "";
		if (g_iLanguage == 0)
		{
			checkstr.Format("  离到期日期还剩%d天,请与厂家联系!",m_nDayHead);
		}
		else if (g_iLanguage == 1)
		{
			checkstr.Format("  remain %d days,Connect the provider please!!",m_nDayHead);
		}
		m_checksta.SetWindowText(checkstr);
		if (m_nDayHead < 0 )
		{
			if (g_iLanguage == 0)
			{
				checkstr.Format("  使用日期已到,请与厂家联系!",m_nDayHead);
			}
			else if (g_iLanguage == 1)
			{
				checkstr.Format("  Time out.,Connect the provider please!!",m_nDayHead);
			}
			m_checksta.SetWindowText(checkstr);
			m_nState = 1;//到期
		}
	}
}

void dlg_sn::OnLanguage()
{
	if (g_iLanguage == 0)
	{
		if (m_nState == 1)
		{
			SetDlgItemText(IDC_BUTTON8,"关机");
		}
		else
		{
			SetDlgItemText(IDC_BUTTON8,"返回");
		}
	}
	else if (g_iLanguage == 1)
	{
		if (m_nState == 1)
		{
			SetDlgItemText(IDC_BUTTON8,"Shutdown");
		}
		else
		{
			SetDlgItemText(IDC_BUTTON8,"return");
		}
		SetDlgItemText(IDC_DEMO10CTRL1,"Checking");
		SetDlgItemText(IDC_BUTTON9,"Delay");
		SetDlgItemText(IDC_BUTTON7,"OK");

	}
}	

void dlg_sn::OnButton9() 
{
	// TODO: Add your control notification handler code here
	CString szTemp,szBase;
	CWnd::GetDlgItemText(IDC_EDIT1,szTemp);
	szBase = g_arr_strLimit[0][4];
    if (szTemp.IsEmpty()||szBase.IsEmpty())
    {
		return;
    }
	int nMax[10][4]={{164,166,170,167},{170,168,167,165},{169,168,166,164},{165,170,169,169},{167,164,168,170},
					{166,170,170,168},{167,167,165,164},{170,168,166,167},{168,167,165,170},{167,167,165,170}
					}; 
	char  msg[80] = {0};   
	int a = szTemp.GetLength();
	int nRand = szTemp.GetAt(a-1) - 48;
	if (nRand<0 || nRand>10)
	{
		return;
	}
    a--;
	for (int i = 0; i<a; i++)
	{
		int nBase = nMax[nRand][0];
		if (i%4 == 1)
		{
			nBase = nMax[nRand][1];
		}
		else if (i%4 == 2)
		{
			nBase = nMax[nRand][2];
		}
		else if (i%4 == 3)
		{
			nBase = nMax[nRand][3];
		}
		msg[i] = nBase - szTemp.GetAt(i);	
	}
	CString str;
	str.Format("%s",msg);
	CString strRev=str;
	int n = 0;
	int j = 0;
	for (int m=0; ; m++)
	{
		j = 2 * m;  
		if (j>=a)
		{
			break;
		}
		strRev.SetAt(j,str.GetAt(n));
		n++;
		
	}
	for (m=0; ; m++)
	{
		j = 2 * m + 1;  
		if (j>=a)
		{
			break;
		}
		strRev.SetAt(j,str.GetAt(n));
		n++;			
	}
    //比较信息
	if(!g_Controller.IsConnected())
		g_lRc = g_Controller.Open(g_nController, GetSafeHwnd());//打开控制器
	if(!g_Controller.IsConnected())
		return;
	char chSeir[80];
	g_lRc = g_Controller.Command("MG_BN", chSeir, sizeof(chSeir));
	CString strSecret;
	strSecret.Format("%s%d",szBase,atoi(chSeir));
	int nInf = strSecret.GetLength();
	int nNum = 0;
	if (nInf > strRev.GetLength())
	{
		if (g_iLanguage == 0)
		{
			MessageBox("输入的信息有误,错误代码1");
		}
		else
		{
			MessageBox("error");
		}
		return;    
	}
	for(; nNum<nInf;  nNum++)
	{
		if (strSecret.GetAt(nNum) != strRev.GetAt(nNum))
		{
			if (g_iLanguage == 0)
			{
				MessageBox("输入的信息有误，错误代码2");
			}
			else
			{
				MessageBox("error");
			}
			return;           
		}		
	}
	int nYear = strtol(strRev.Mid(nNum,4),NULL,16);
	int nMonth = strtol(strRev.Mid(nNum+4,2),NULL,16);
	int nDay = strtol(strRev.Mid(nNum+6,4),NULL,16);
	if (nYear>2010 && nYear<2030
		&&nMonth>0 && nMonth<13
		&&nDay>0 && nDay<32)
	{
        OnModityLimit(nYear,nMonth,nDay);
	}
	
}
 
void dlg_sn::OnModityLimit(int nYear,int nMonth, int nDay)
{
	CString tmp;
	tmp.Format("%d",nYear);
	HasWriteValue(tmp,TIME_YEAR);		
	tmp.Format("%d",nMonth);
	HasWriteValue(tmp,TIME_MONTH);
	tmp.Format("%d",nDay);
	HasWriteValue(tmp,TIME_DAY);	
	CTime CurrTime;
	CurrTime = g_stCurrTime;
	CTime LimitTime(nYear,nMonth,nDay,0,0,0);
	CTimeSpan  SpanTime = LimitTime - CurrTime  ;
	int day = SpanTime.GetDays(); 
    if (day>=0)
    {
 	    CDialog::OnOK();   
	}

}
