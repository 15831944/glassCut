// Dlg_config.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_config.h"
#include "Dlg_light.h"
#include "dlg_machine.h"
#include "dlg_pass.h"
#include "Dlg_Loading.h"
#include "Dlg_scan.h"
#include "Dlg_Oiling.h"
#include "benderDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_config dialog


CDlg_config::CDlg_config(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_config::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_config)g_stu_pAxisD->sSpareg_stu_pAxisB->sSpare
	m_nDxf = g_stu_pAxisE->sSpare;
	m_nLanguage = g_machinedll.GetLanguage();;
	m_nLoad = g_stu_pAxisC->sSpare;
	m_nPhototube = g_stu_pAxisG->sSpare;
	m_nUnit = g_stu_pAxisH->sSpare;
	m_bTeah1 = g_stu_pAxisA->bSpare;	/* 光电定位 */
	m_bTeah4 = g_stu_pAxisD->bSpare;	/* DXF排序 */
	m_bTeah5 = g_stu_pAxisE->bSpare;	/* 异形优化 */
	m_bTeah7 = g_stu_pAxisG->bSpare;	/* 循环执行 */
	m_bTeah9 = g_stu_pAxisA->bSpareA;	/* 切割注油 */
	m_nSort = g_stu_pAxisD->bSpareA;	/* 排序，最近点还是切入点 */
	m_bMach1 = g_stu_pAxisC->bSpareA;	/* 触摸屏选项 */
	m_nControl = g_stu_pAxisA->sSpare;	/* 控制方式，位置还是速度 */
	m_bMach2 = g_stu_pAxisF->bSpareA;	/* 龙门同步方式 */
	m_bShelf = (BOOL)GetPrivateProfileInt("SHOW","SHELF",0,INIFILE_ADDEXTRA);		//显示货架号
	m_nLabelPos = (BOOL)GetPrivateProfileInt("PRINT","POS",1,INIFILE_ADDEXTRA);	//标签位置
	m_bPrint = (BOOL)GetPrivateProfileInt("PRINT","PRINT",0,INIFILE_ADDEXTRA);		//是否打印标签
	m_bPosNeg = (BOOL)GetPrivateProfileInt("POSNEG","CUTTING",0,INIFILE_ADDEXTRA);	//实心刀头，正反刀切割
	m_nSafeSwitch = GetPrivateProfileInt("SAFE","SAFESWICH",0,INIFILE_ADDEXTRA);//安全光幕
	//}}AFX_DATA_INIT
	pLight = new CDlg_light(this);
	pLoading = new CDlg_Loading(this);
	pOiling = new CDlg_Oiling(this); 

}


void CDlg_config::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_config)
	DDX_Radio(pDX, IDC_RADIO_DXF1, m_nDxf);
	DDX_Radio(pDX, IDC_RADIO_LANGUAGE1, m_nLanguage);
	DDX_Radio(pDX, IDC_RADIO_LOAD1, m_nLoad);
	DDX_Radio(pDX, IDC_RADIO_PHOTOTUBE1, m_nPhototube);
	DDX_Radio(pDX, IDC_RADIO_UNIT1, m_nUnit);
	DDX_Check(pDX, IDC_CHECK_TECH1, m_bTeah1);
	DDX_Check(pDX, IDC_CHECK_TECH4, m_bTeah4);
	DDX_Check(pDX, IDC_CHECK_TECH5, m_bTeah5);
	DDX_Check(pDX, IDC_CHECK_TECH7, m_bTeah7);
	DDX_Check(pDX, IDC_CHECK_TECH9, m_bTeah9);
	DDX_Radio(pDX, IDC_RADIO_SORTSHORT, m_nSort);
	DDX_Check(pDX, IDC_CHECK_MACH1, m_bMach1);
	DDX_Radio(pDX, IDC_RADIO_CONTROLA, m_nControl);
	DDX_Check(pDX, IDC_CHECK_MACH2, m_bMach2);
	DDX_Radio(pDX, IDC_RADIO_SHELF1, m_bShelf);
	DDX_Radio(pDX, IDC_RADIO_SAFEY, m_nLabelPos);
	DDX_Check(pDX, IDC_CHECK_PRINT, m_bPrint);
	DDX_Check(pDX, IDC_CHECK_POSNEG, m_bPosNeg);
	DDX_Radio(pDX, IDC_RADIO_SAFE1, m_nSafeSwitch);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_config, CDialog)
	//{{AFX_MSG_MAP(CDlg_config)
	ON_BN_CLICKED(IDC_BUTTON_F8, OnButtonF8)
	ON_BN_CLICKED(IDC_BUTTON_F1, OnButtonF1)
	ON_BN_CLICKED(IDC_BUTTON_F2, OnButtonF2)
	ON_BN_CLICKED(IDC_BUTTON_F4, OnButtonF4)
	ON_BN_CLICKED(IDC_BUTTON_F5, OnButtonF5)
	ON_BN_CLICKED(IDC_BUTTON_F10, OnButtonF10)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_MESSAGE(WM_LOADING,OnReturnConfig)
	ON_MESSAGE(WM_LIGHT,OnReturnConfig)
	ON_MESSAGE(WM_OILING,OnReturnConfig)
	ON_MESSAGE(WM_SCAN,OnReturnConfig)
	ON_MESSAGE(WM_FATHOM,OnReturnConfig)	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
CDlg_config::~CDlg_config()
{
	delete pLight;
	pLight = NULL;
	delete pLoading;
	pLoading = NULL;
	delete pOiling; 
	pOiling = NULL;
}
// CDlg_config message handlers

BOOL CDlg_config::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetCtlFont(this);
	OnLanguage();
	InitButton();	
	SetWindowPos(CWnd::GetOwner(),0,0,g_screen.x,g_screen.y,SWP_SHOWWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_config::InitButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_SETPRE1);
	//机械参数
	m_pClrButton[0].SetFont(&g_fontStatic);
	m_pClrButton[0].SetBitMapID(IDB_BITMAP_MACH1,IDB_BITMAP_MACH2);	
	m_pClrButton[0].Create(g_strConfig[39][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(5, 705), c, this, IDC_BUTTON_F1); 
 	
	//光电定位
	m_pClrButton[1].SetFont(&g_fontStatic);
	m_pClrButton[1].SetBitMapID(IDB_BITMAP_LIGHTPOS1,IDB_BITMAP_LIGHTPOS2);	
	m_pClrButton[1].Create(g_strConfig[40][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(215, 705), c, this, IDC_BUTTON_F2); 
  	//注油
	m_pClrButton[2].SetFont(&g_fontEdit);
	m_pClrButton[2].SetBitMapID(IDB_BITMAP_OIL1,IDB_BITMAP_OIL2);	
	m_pClrButton[2].Create(g_strConfig[42][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(375, 705), c, this, IDC_BUTTON_F4); 
	//流水切割
	m_pClrButton[3].SetFont(&g_fontEdit);
	m_pClrButton[3].SetBitMapID(IDB_BITMAP_WCUT1,IDB_BITMAP_WCUT2);	
	m_pClrButton[3].Create(g_strConfig[43][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(535, 705), c, this, IDC_BUTTON_F5); 

	//保存
	m_pClrButton[4].SetFont(&g_fontEdit);
	m_pClrButton[4].SetBitMapID(IDB_BITMAP_CSAVE1,IDB_BITMAP_CSAVE2);	
	m_pClrButton[4].Create(g_strConfig[46][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(700, 705), c, this, IDC_BUTTON_F8); 

	//返回
	m_pClrButton[5].SetFont(&g_fontEdit);
	m_pClrButton[5].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pClrButton[5].Create(g_strConfig[19][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(870, 705), c, this, IDC_BUTTON_F10); 

	DeleteObject(c);
	



	m_ChkBox[0].SubclassDlgItem(IDC_CHECK_TECH1, this);
	m_ChkBox[1].SubclassDlgItem(IDC_CHECK_TECH4, this);
	m_ChkBox[2].SubclassDlgItem(IDC_CHECK_TECH5, this);
	m_ChkBox[3].SubclassDlgItem(IDC_CHECK_TECH7, this);
	m_ChkBox[4].SubclassDlgItem(IDC_CHECK_TECH9, this);
	m_ChkBox[5].SubclassDlgItem(IDC_CHECK_MACH1, this);
	m_ChkBox[6].SubclassDlgItem(IDC_CHECK_PRINT, this);
	m_ChkBox[7].SubclassDlgItem(IDC_CHECK_POSNEG, this);

	
	m_RdoBox[0].SubclassDlgItem(IDC_RADIO_PHOTOTUBE1, this);
	m_RdoBox[1].SubclassDlgItem(IDC_RADIO_PHOTOTUBE2, this);
	m_RdoBox[2].SubclassDlgItem(IDC_RADIO_PHOTOTUBE3, this);
	m_RdoBox[3].SubclassDlgItem(IDC_RADIO_PHOTOTUBE4, this);
	m_RdoBox[4].SubclassDlgItem(IDC_RADIO_SORTSHORT, this);
	m_RdoBox[5].SubclassDlgItem(IDC_RADIO_SORTPOINT, this);
	m_RdoBox[6].SubclassDlgItem(IDC_RADIO_DXF1, this);
	m_RdoBox[7].SubclassDlgItem(IDC_RADIO_DXF2, this);
	m_RdoBox[8].SubclassDlgItem(IDC_RADIO_DXF3, this);
	m_RdoBox[9].SubclassDlgItem(IDC_RADIO_LOAD1, this);
	m_RdoBox[10].SubclassDlgItem(IDC_RADIO_LOAD2, this);
	m_RdoBox[11].SubclassDlgItem(IDC_RADIO_LANGUAGE1, this);
	m_RdoBox[12].SubclassDlgItem(IDC_RADIO_LANGUAGE2, this);
	m_RdoBox[13].SubclassDlgItem(IDC_RADIO_LANGUAGE3, this);
	m_RdoBox[14].SubclassDlgItem(IDC_RADIO_UNIT1, this);
	m_RdoBox[15].SubclassDlgItem(IDC_RADIO_UNIT2, this);
	m_RdoBox[16].SubclassDlgItem(IDC_RADIO_CONTROLA, this);
	m_RdoBox[17].SubclassDlgItem(IDC_RADIO_CONTROLB, this); 
	m_RdoBox[18].SubclassDlgItem(IDC_RADIO_SHELF1, this);
	m_RdoBox[19].SubclassDlgItem(IDC_RADIO_SHELF2, this); 
	m_RdoBox[20].SubclassDlgItem(IDC_RADIO_SAFEY, this);
	m_RdoBox[21].SubclassDlgItem(IDC_RADIO_SAFEN, this); 
	m_RdoBox[22].SubclassDlgItem(IDC_RADIO_SAFE1, this);
	m_RdoBox[23].SubclassDlgItem(IDC_RADIO_SAFE2, this); 	
}

void CDlg_config::OnButtonF1()
{
	if(!OnIsHaveDialog())
		return;
	if(g_iPassgrade==2 || g_iPassgrade==3)
	{
        g_iPassgrade = 0;
		dlg_pass pass;
		if(pass.DoModal()==IDOK)
		{
			if(g_iPassgrade>=1)
			{
				dlg_machine  machine;
				machine.DoModal();
			}
		}
	}
	else  if(g_iPassgrade==1)
	{
		dlg_machine  machine;
		machine.DoModal();
	}
}

void CDlg_config::OnButtonF2()/* 光电定位 */
{
	if(!OnIsHaveDialog())
		return;
	if (pLight->GetSafeHwnd()==0)
	{
		pLight->Create(IDD_DIALOG_CONFIG_LIGHT, this);
		OnSetBtnText();
	}
}

void CDlg_config::OnButtonF4()  
{
	if(!OnIsHaveDialog())
		return;
	if (pOiling->GetSafeHwnd()==0)
	{
		pOiling->Create(IDD_DIALOG_CONFIG_OILING, this);
		OnSetBtnText();
	}
}

void CDlg_config::OnButtonF5()  /* 上片台 */
{
	if(!OnIsHaveDialog())
		return;
	if (pLoading->GetSafeHwnd()==0)
	{
		pLoading->Create(IDD_DIALOG_CONFIG_LOADING, this);
		OnSetBtnText();
	}
}

void CDlg_config::OnSetBtnText() 
{
	for (int n=0; n<4; n++)
	{
		m_pClrButton[n].ShowWindow(SW_HIDE);
	}
	SetEnable(FALSE);
}

void CDlg_config::SaveData() 
{
	UpdateData(TRUE);
	g_stu_pAxisE->sSpare = m_nDxf;
	g_stu_pAxisC->sSpare = m_nLoad;
	g_stu_pAxisG->sSpare = m_nPhototube;
	g_stu_pAxisH->sSpare = m_nUnit;
	g_stu_pAxisA->sSpare = m_nControl;	/* 控制方式，位置还是速度 */
	g_stu_pAxisD->bSpareA = m_nSort;	/* 排序，最近点还是切入点 */
	
	g_stu_pAxisA->bSpare = m_bTeah1;	/* 光电定位 */
	g_stu_pAxisD->bSpare = m_bTeah4;	/* DXF排序 */
	g_stu_pAxisE->bSpare = m_bTeah5;
	g_stu_pAxisG->bSpare = m_bTeah7;	/* 循环执行 */
	g_stu_pAxisA->bSpareA = m_bTeah9;	/* 切割注油 */

	g_stu_pAxisC->bSpareA = m_bMach1;	/* 触摸屏选项 */
	
	g_machinedll.SetLanguage(m_nLanguage);
	g_iLanguage = m_nLanguage;
	g_machinedll.ParameterSave((char*)((const char*)(g_strOriginalPathD + "machine.ini")));/* 保存机械参数信息 */
	
	CString strText; 
	strText.Format("%d",(int)m_bShelf);
	WritePrivateProfileString("SHOW","SHELF",strText,INIFILE_ADDEXTRA);
	strText.Format("%d",(int)m_nLabelPos);
	WritePrivateProfileString("PRINT","POS",strText,INIFILE_ADDEXTRA);	
	strText.Format("%d",(int)m_bPrint);
	WritePrivateProfileString("PRINT","PRINT",strText,INIFILE_ADDEXTRA);
	g_Dmcgc.SetLabelInf((int)m_bPrint,(int)m_nLabelPos);
	//正反刀
	strText.Format("%d",(int)m_bPosNeg);
	WritePrivateProfileString("POSNEG","CUTTING",strText,INIFILE_ADDEXTRA);
	g_Dmcgc.SetSolidHead((int)m_bPosNeg);
	//安全光栅
	strText.Format("%d",(int)m_nSafeSwitch);
	WritePrivateProfileString("SAFE","SAFESWICH",strText,INIFILE_ADDEXTRA);
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)AfxGetMainWnd();
    if(pDlg != NULL)
	{
		pDlg->m_nSafeSwich = m_nSafeSwitch;
		//是否打印标签
		if (GetPrivateProfileInt("PRINT","PRINT",0,INIFILE_ADDEXTRA)==0)
		{
			(pDlg->GetDlgItem(IDC_STATICD_LABEDST))->ShowWindow(SW_HIDE);
			(pDlg->GetDlgItem(IDC_EDIT_LABELST))->ShowWindow(SW_HIDE);
		}
		else
		{
			(pDlg->GetDlgItem(IDC_STATICD_LABEDST))->ShowWindow(SW_SHOW);
			(pDlg->GetDlgItem(IDC_EDIT_LABELST))->ShowWindow(SW_SHOW);
		}
	}
}

void CDlg_config::OnButtonF8() 
{
	if (pLight->GetSafeHwnd()!=0)
	{
		for (int n=0; n<6; n++)
		{
			m_pClrButton[n].ShowWindow(SW_SHOW);
		}
		pLight->SendMessage(WM_LIGHT, 0, 1);
	}
	else if(pLoading->GetSafeHwnd()!=0)
	{
		for (int n=0; n<6; n++)
		{
			m_pClrButton[n].ShowWindow(SW_SHOW);
		}
		pLoading->SendMessage(WM_LOADING, 0, 1);
	}	
	else if(pOiling->GetSafeHwnd()!=0)
	{
		for (int n=0; n<6; n++)
		{
			m_pClrButton[n].ShowWindow(SW_SHOW);
		}
		pOiling->SendMessage(WM_OILING, 0, 1);
	}
	else
	{
		SaveData();
		g_iPassgrade = 0;
		CString	str;
		str.Format("%d", g_stu_pAxisA->bSpare);
		CDialog::OnOK();
	}
}

void CDlg_config::OnButtonF10() 
{
	if (pLight->GetSafeHwnd()!=0)
	{
		for (int n=0; n<6; n++)
		{
			m_pClrButton[n].ShowWindow(SW_SHOW);
		}
		pLight->SendMessage(WM_LIGHT, 0, 2);
	}
	else if(pLoading->GetSafeHwnd()!=0)
	{
		for (int n=0; n<6; n++)
		{
			m_pClrButton[n].ShowWindow(SW_SHOW);
		}
		pLoading->SendMessage(WM_LOADING, 0, 2);
	}
	else if(pOiling->GetSafeHwnd()!=0)
	{
		for (int n=0; n<6; n++)
		{
			m_pClrButton[n].ShowWindow(SW_SHOW);
		}
		pOiling->SendMessage(WM_OILING, 0, 2);
	}
	else
	{
		g_iPassgrade = 0;
		CDialog::OnCancel();
	}
}

void CDlg_config::OnLanguage()
{
	for(int index=0; index<AR_CONFIG; index++)
	{
		if(g_strConfig[index][g_iLanguage]=="NULL")		g_strConfig[index][g_iLanguage] = "";
		    SetDlgItemText(atoi(g_strConfig[index][2]), g_strConfig[index][g_iLanguage]);
	}
	if (g_iLanguage == 1)
	{
		SetDlgItemText(IDC_STATIC_SHELF,"Show");
		SetDlgItemText(IDC_RADIO_SHELF1,"Manufact");
		SetDlgItemText(IDC_RADIO_SHELF2,"Shelf");
		SetDlgItemText(IDC_STATIC_LABLE,"Label Pos");
		SetDlgItemText(IDC_RADIO_SAFEY,"Left");
		SetDlgItemText(IDC_RADIO_SAFEN,"Mid");
		SetDlgItemText(IDC_CHECK_PRINT,"labels");
		SetDlgItemText(IDC_CHECK_POSNEG,"Solid Head");
		SetDlgItemText(IDC_STATIC_SAFE,"Safe Protect");
		SetDlgItemText(IDC_RADIO_SAFE1,"Effect");
		SetDlgItemText(IDC_RADIO_SAFE2,"No Effect");
		SetDlgItemText(IDC_RADIO_CONTROLC,"Com");
	}
}

BOOL CDlg_config::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->lParam==VK_ESCAPE||pMsg->wParam==VK_ESCAPE)
		return TRUE;
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
		return TRUE;
 	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CDlg_config::OnReturnConfig(WPARAM wParam, LPARAM lParam) 
{
	if(lParam==6)
	{
		SetEnable(TRUE);
	}
	return 0;
}


void CDlg_config::SetEnable(BOOL bEnable)
{
	int i;
	for(i=0;i<8;i++)
		m_ChkBox[i].EnableWindow(bEnable);
	for(i=0;i<24;i++)
		m_RdoBox[i].EnableWindow(bEnable);
}

BOOL CDlg_config::OnIsHaveDialog() 
{
	BOOL	bDialog = TRUE;
	if (pLight->GetSafeHwnd()!=0)
	{
		bDialog = FALSE;
	}
	if(pLoading->GetSafeHwnd()!=0)
	{
		bDialog = FALSE;
	}
	if(pOiling->GetSafeHwnd()!=0)
	{
		bDialog = FALSE;
	}
	return bDialog;
}

void CDlg_config::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//贴背景图片
	CDC  MemDc;
	CBitmap bitmap;	
	MemDc.CreateCompatibleDC(&dc);
	bitmap.LoadBitmap(IDB_BITMAP_DIALOG);
	CBitmap *pOldBit = MemDc.SelectObject(&bitmap);
	dc.BitBlt(0,0,1024,768,&MemDc,0,0,SRCCOPY);
	MemDc.SelectObject(pOldBit);
	bitmap.DeleteObject();
	MemDc.DeleteDC();
	CDialog::OnPaint();		
	// Do not call CDialog::OnPaint() for painting messages
}

HBRUSH CDlg_config::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
#ifdef POWERLAND
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(RGB(165,198,248));
		return (HBRUSH)GetStockObject(NULL_BRUSH);		
	}
#endif	
	return hbr;
}
