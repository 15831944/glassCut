// Dlg_CuttingSize.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_CuttingSize.h"
#include "Dlg_KeyNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_CuttingSize dialog


CDlg_CuttingSize::CDlg_CuttingSize(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_CuttingSize::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_CuttingSize)
	//}}AFX_DATA_INIT
}


void CDlg_CuttingSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_CuttingSize)
	DDX_Control(pDX, IDC_EDIT_SAFEDOWN, m_edtSavedown);
	DDX_Control(pDX, IDC_EDIT_SIZEE, m_edtSizeE);
	DDX_Control(pDX, IDC_EDIT_SIZED, m_edtSizeD);
	DDX_Control(pDX, IDC_EDIT_SIZEC, m_edtSizeC);
	DDX_Control(pDX, IDC_EDIT_SIZEB, m_edtSizeB);
	DDX_Control(pDX, IDC_EDIT_SIZEA, m_edtSizeA);
	DDX_Control(pDX, IDC_EDIT_DXFD, m_edtDxfD);
	DDX_Control(pDX, IDC_EDIT_DXFC, m_edtDxfC);
	DDX_Control(pDX, IDC_EDIT_DXFB, m_edtDxfB);
	DDX_Control(pDX, IDC_EDIT_DXFA, m_edtDxfA);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_CuttingSize, CDialog)
	//{{AFX_MSG_MAP(CDlg_CuttingSize)
	ON_BN_CLICKED(IDC_BUTTON_F8, OnButtonF8)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	ON_MESSAGE(WM_SCALE,OnScale)
	ON_BN_CLICKED(IDC_BUTTON_F10, OnButtonF10)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_CuttingSize message handlers

BOOL CDlg_CuttingSize::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString		strTemp;
	OnLanguage();
	OnReSetCtl();
	InitButton();
	// TODO: Add extra initialization here
	if (g_stu_pAxisH->sSpare==1)	/* 英制 */
		SendMessage(WM_SCALE, 0, g_stu_pAxisH->sSpare);
	else
	{
		strTemp.Format("%d", g_stu_pAxisB->sSpareA);		SetDlgItemText(IDC_EDIT_SIZEA, strTemp);
		strTemp.Format("%d", g_stu_pAxisB->sSpareB);		SetDlgItemText(IDC_EDIT_SIZEB, strTemp);
		strTemp.Format("%d", g_stu_pAxisB->sSpareC);		SetDlgItemText(IDC_EDIT_SIZEC, strTemp);
		strTemp.Format("%d", g_stu_pAxisB->sSpareD);		SetDlgItemText(IDC_EDIT_SIZED, strTemp);
		strTemp.Format("%d", g_stu_pAxisB->sSpareE);		SetDlgItemText(IDC_EDIT_SIZEE, strTemp);
		
		strTemp.Format("%d", g_stu_pAxisC->sSpareA);		SetDlgItemText(IDC_EDIT_DXFA, strTemp);
		strTemp.Format("%d", g_stu_pAxisC->sSpareB);		SetDlgItemText(IDC_EDIT_DXFB, strTemp);
		strTemp.Format("%d", g_stu_pAxisC->sSpareC);		SetDlgItemText(IDC_EDIT_DXFC, strTemp);
		strTemp.Format("%d", g_stu_pAxisC->sSpareD);		SetDlgItemText(IDC_EDIT_DXFD, strTemp);
		/* 安全距离处理 */
		strTemp.Format("%.0f", g_stu_pAxisH->dSpareC);		SetDlgItemText(IDC_EDIT_SAFEDOWN, strTemp);	 
	}
	SetWindowPos(&CWnd::wndTop, 0, 0, 1024, 768, SWP_SHOWWINDOW);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_CuttingSize::OnButtonF8() /* 保存参数 */
{
	//	g_stu_pAxisH->dSpareC = m_machineZ;/* 安全距离 */
	CString		strTemp;
 	if(g_stu_pAxisH->sSpare==0)	/* 公制 */
	{
		GetDlgItemText(IDC_EDIT_SIZEA,strTemp);			
		if (atoi(strTemp) > g_stu_pAxisA->dSpareA)
		{
			if (g_iLanguage == 0)
				MessageBox("原片长度大于机台尺寸.");
			else
				MessageBox("Glass length is more than the size.");
			return;
		}
		g_stu_pAxisB->sSpareA = atoi(strTemp);

		GetDlgItemText(IDC_EDIT_SIZEB,strTemp);	
		if (atoi(strTemp) > g_stu_pAxisB->dSpareA)
		{
			if (g_iLanguage == 0)
				MessageBox("原片宽度大于机台尺寸.");
			else
				MessageBox("Glass length is more than the size.");
			return;
		}		
		g_stu_pAxisB->sSpareB = atoi(strTemp);

		GetDlgItemText(IDC_EDIT_SIZEC,strTemp);		g_stu_pAxisB->sSpareC = atoi(strTemp);
		GetDlgItemText(IDC_EDIT_SIZED,strTemp);		g_stu_pAxisB->sSpareD = atoi(strTemp);
		GetDlgItemText(IDC_EDIT_SIZEE,strTemp);		g_stu_pAxisB->sSpareE = atoi(strTemp);
		
		GetDlgItemText(IDC_EDIT_DXFA,strTemp);		g_stu_pAxisC->sSpareA = atoi(strTemp);
		GetDlgItemText(IDC_EDIT_DXFB,strTemp);		g_stu_pAxisC->sSpareB = atoi(strTemp);
		GetDlgItemText(IDC_EDIT_DXFC,strTemp);		g_stu_pAxisC->sSpareC = atoi(strTemp);
		GetDlgItemText(IDC_EDIT_DXFD,strTemp);		g_stu_pAxisC->sSpareD = atoi(strTemp);
		/* 安全距离 */
		GetDlgItemText(IDC_EDIT_SAFEDOWN,strTemp);	g_stu_pAxisH->dSpareC = atof(strTemp);		
	}
	else						/* 英制 */
	{
		GetDlgItemText(IDC_EDIT_SIZEA,strTemp);	
		if (atoi(strTemp) * IN_TO_MM > g_stu_pAxisA->dSpareA)
		{
			if (g_iLanguage == 0)
				MessageBox("原片长度大于机台尺寸.");
			else
				MessageBox("Glass length is more than the size.");
			return;
		}		
		g_stu_pAxisB->sSpareA = (short int)(atof(strTemp) * IN_TO_MM);
		GetDlgItemText(IDC_EDIT_SIZEB,strTemp);	
		if (atoi(strTemp)  * IN_TO_MM> g_stu_pAxisB->dSpareA)
		{
			if (g_iLanguage == 0)
				MessageBox("原片宽度大于机台尺寸.");
			else
				MessageBox("Glass length is more than the size.");
			return;
		}				

		g_stu_pAxisB->sSpareB = (short int)(atof(strTemp) * IN_TO_MM);
		GetDlgItemText(IDC_EDIT_SIZEC,strTemp);		g_stu_pAxisB->sSpareC = (short int)(atof(strTemp) * IN_TO_MM);
		GetDlgItemText(IDC_EDIT_SIZED,strTemp);		g_stu_pAxisB->sSpareD = (short int)(atof(strTemp) * IN_TO_MM);
		GetDlgItemText(IDC_EDIT_SIZEE,strTemp);		g_stu_pAxisB->sSpareE = (short int)(atof(strTemp) * IN_TO_MM);
		
		GetDlgItemText(IDC_EDIT_DXFA,strTemp);		g_stu_pAxisC->sSpareA = (short int)(atof(strTemp) * IN_TO_MM);
		GetDlgItemText(IDC_EDIT_DXFB,strTemp);		g_stu_pAxisC->sSpareB = (short int)(atof(strTemp) * IN_TO_MM);
		GetDlgItemText(IDC_EDIT_DXFC,strTemp);		g_stu_pAxisC->sSpareC = (short int)(atof(strTemp) * IN_TO_MM);
		GetDlgItemText(IDC_EDIT_DXFD,strTemp);		g_stu_pAxisC->sSpareD = (short int)(atof(strTemp) * IN_TO_MM);
		
		/* 安全距离 */
		GetDlgItemText(IDC_EDIT_SAFEDOWN,strTemp);	g_stu_pAxisH->dSpareC = (short int)(atof(strTemp) * IN_TO_MM);
	}
	g_machinedll.ParameterSave((char*)((const char*)(g_strOriginalPathD + "machine.ini")));/* 保存机械参数信息 */
    g_iPassgrade = 0;
//	CDialog::DestroyWindow();
	CDialog::OnOK();
}

LRESULT CDlg_CuttingSize::OnEditDouble(WPARAM wParam, LPARAM lParam) 
{
	CString				strTmp;
	CDlg_KeyNumber		KeyNum;
	
	if(lParam==1)/* 有触摸屏 */
	{
		((CEdit *)GetDlgItem(wParam))->SetSel(0,-1);
		return 0;
	}

	CWnd::GetDlgItemText(wParam,strTmp);
	KeyNum.m_strNew = KeyNum.m_strOld = strTmp;
	switch(wParam) 
	{
	case IDC_EDIT_SIZEA:		GetDlgItemText(IDC_STATIC_SIZEA,KeyNum.m_strTitle);		break;
	case IDC_EDIT_SIZEB:		GetDlgItemText(IDC_STATIC_SIZEB,KeyNum.m_strTitle);		break;
	case IDC_EDIT_SIZEC:		GetDlgItemText(IDC_STATIC_SIZEC,KeyNum.m_strTitle);		break;
	case IDC_EDIT_SIZED:		GetDlgItemText(IDC_STATIC_SIZED,KeyNum.m_strTitle);		break;
	case IDC_EDIT_SIZEE:		GetDlgItemText(IDC_STATIC_SIZEE,KeyNum.m_strTitle);		break;
	case IDC_EDIT_DXFA:			GetDlgItemText(IDC_STATIC_DXFA,KeyNum.m_strTitle);		break;
	case IDC_EDIT_DXFB:			GetDlgItemText(IDC_STATIC_DXFB,KeyNum.m_strTitle);		break;
	case IDC_EDIT_DXFC:			GetDlgItemText(IDC_STATIC_DXFC,KeyNum.m_strTitle);		break;
	case IDC_EDIT_DXFD:			GetDlgItemText(IDC_STATIC_DXFD,KeyNum.m_strTitle);		break;
	case IDC_EDIT_SAFEDOWN:		GetDlgItemText(IDC_STATIC_SAFEDOWN,KeyNum.m_strTitle);	break;
	default:																			break;
	}
	if(KeyNum.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	
	return 0;
}

LRESULT CDlg_CuttingSize::OnScale(WPARAM wParam, LPARAM lParam) 
{
	if(lParam==0)/* 如果是公制则不处理 */
		return 0;
	if (wParam==0)	/* 初始化，将公制转化为英制显示 */
	{
		CString	strTemp;
		strTemp.Format("%.2f", SaveNPoint(4, g_stu_pAxisB->sSpareA * MM_TO_IN));		SetDlgItemText(IDC_EDIT_SIZEA,strTemp);
		strTemp.Format("%.2f", SaveNPoint(4, g_stu_pAxisB->sSpareB * MM_TO_IN));		SetDlgItemText(IDC_EDIT_SIZEB,strTemp);
		strTemp.Format("%.2f", SaveNPoint(4, g_stu_pAxisB->sSpareC * MM_TO_IN));		SetDlgItemText(IDC_EDIT_SIZEC,strTemp);
		strTemp.Format("%.2f", SaveNPoint(4, g_stu_pAxisB->sSpareD * MM_TO_IN));		SetDlgItemText(IDC_EDIT_SIZED,strTemp);
		strTemp.Format("%.2f", SaveNPoint(4, g_stu_pAxisB->sSpareE * MM_TO_IN));		SetDlgItemText(IDC_EDIT_SIZEE,strTemp);
		
		strTemp.Format("%.2f", SaveNPoint(4, g_stu_pAxisC->sSpareA * MM_TO_IN));		SetDlgItemText(IDC_EDIT_DXFA,strTemp);
		strTemp.Format("%.2f", SaveNPoint(4, g_stu_pAxisC->sSpareB * MM_TO_IN));		SetDlgItemText(IDC_EDIT_DXFB,strTemp);
		strTemp.Format("%.2f", SaveNPoint(4, g_stu_pAxisC->sSpareC * MM_TO_IN));		SetDlgItemText(IDC_EDIT_DXFC,strTemp);
		strTemp.Format("%.2f", SaveNPoint(4, g_stu_pAxisC->sSpareD * MM_TO_IN));		SetDlgItemText(IDC_EDIT_DXFD,strTemp);
	}
	return 0;
}

void CDlg_CuttingSize::OnLanguage()
{
	CString test;
	for(int i=0;i<AR_CUTSIZE;i++)
	{
		if(strstr(g_strCuttingSize[i][g_iLanguage], "NULL"))
			SetDlgItemText(atoi(g_strCuttingSize[i][2]), "");
		else
			
		{
			SetDlgItemText(atoi(g_strCuttingSize[i][2]),g_strCuttingSize[i][g_iLanguage]);
		}
	}
}

void CDlg_CuttingSize::OnReSetCtl()
{	
	GetDlgItem(IDC_STATIC_SIZE)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_SIZEA)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_SIZEB)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_SIZEC)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_SIZED)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_SIZEE)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_DXF)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_DXFA)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_DXFB)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_DXFC)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_DXFD)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_EDIT_SIZEA)->SetFont(&g_fontEdit);
	GetDlgItem(IDC_EDIT_SIZEB)->SetFont(&g_fontEdit);
	GetDlgItem(IDC_EDIT_SIZEC)->SetFont(&g_fontEdit);
	GetDlgItem(IDC_EDIT_SIZED)->SetFont(&g_fontEdit);
	GetDlgItem(IDC_EDIT_SIZEE)->SetFont(&g_fontEdit);
	GetDlgItem(IDC_EDIT_DXFA)->SetFont(&g_fontEdit);
	GetDlgItem(IDC_EDIT_DXFB)->SetFont(&g_fontEdit);
	GetDlgItem(IDC_EDIT_DXFC)->SetFont(&g_fontEdit);
	GetDlgItem(IDC_EDIT_DXFD)->SetFont(&g_fontEdit);	
	GetDlgItem(IDC_STATIC_safedistance)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_SAFEDOWN)->SetFont(&g_fontStatic);
}
 

BOOL CDlg_CuttingSize::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->lParam==VK_RETURN||pMsg->wParam==VK_RETURN)
		return TRUE;	

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlg_CuttingSize::OnButtonF10() 
{
    g_iPassgrade = 0;
	CDialog::OnCancel();
}

void CDlg_CuttingSize::InitButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_SAVE1);

	//保存
	m_pButton[0].SetFont(&g_fontEdit);
	m_pButton[0].SetBitMapID(IDB_BITMAP_SAVE1,IDB_BITMAP_SAVE2);	
	m_pButton[0].Create(g_strCuttingSize[13][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(680, 700), c, this, IDC_BUTTON_F8); 
	//返回	
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[1].Create(g_strCuttingSize[15][g_iLanguage], WS_CHILD | WS_VISIBLE, CPoint(900, 700), c, this, IDC_BUTTON_F10); 
    
	DeleteObject(c);



}

void CDlg_CuttingSize::OnPaint() 
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

HBRUSH CDlg_CuttingSize::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
#ifdef POWERLAND
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);		
	}
#endif	
	return hbr;
}
