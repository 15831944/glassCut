// TabDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "TabDlg.h"
#include "PrintFrame.h"
#include <assert.h>
#include <afxdlgs.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabDlg dialog


CTabDlg::CTabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabDlg)
	m_nFont = 140;
	m_nTabLen = 0;
	m_nTabWid = 0;
	m_nRow = 0;
	m_nCol = 0;
	m_dLen = 0.0;
	m_dWid = 0.0;
	m_dMarinL = 0.0;
	m_dMarinT = 0.0;
	m_dRowSpace = 0.0;
	m_dColSpace = 0.0;
	m_dMarinB = 0.0;
	m_dMarinR = 0.0;
	//}}AFX_DATA_INIT

	m_bBtnState = FALSE;
	m_szA4.cx = 201;
	m_szA4.cy = 288;
	m_nPage = 0;
	m_nSelect = 0;
	m_nLineHeight = 0;
	m_nReportPage = 0;
	m_lDgmCnt = 0;

	//在标签纸上打印标签
	//标签纸大小
	m_nTabLen = 60;
	m_nTabWid = 40;
	//标签的大小
	m_szTab.cx = 60;
	m_szTab.cy = 40;

	m_dAcc = 0;

	m_nCnt = 0;
}


void CTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabDlg)
	DDX_Control(pDX, IDC_TAB_PREVIEW, m_clrBtnTabPreView);
	DDX_Control(pDX, IDC_PARAM_SAVE, m_clrBtnSave);
	DDX_Control(pDX, IDC_EXIT, m_clrBtnExit);
	DDX_Control(pDX, IDC_TAB_PNT, m_clrBtnTabPnt);
	DDX_Control(pDX, IDC_BTN_DISPLAY, m_clrBtnDisplay);
	DDX_Control(pDX, IDC_REP_PNT, m_clrBtnPNT);
	DDX_Control(pDX, IDC_REP_PREVIEW, m_clrBtnPreView);
	DDX_Control(pDX, IDC_A4, m_btnA4);
	DDX_Text(pDX, IDC_FONT, m_nFont);
	DDX_Text(pDX, IDC_ROW, m_nRow);
	DDX_Text(pDX, IDC_COL, m_nCol);
	DDX_Text(pDX, IDC_LEN, m_dLen);
	DDX_Text(pDX, IDC_WID, m_dWid);
	DDX_Text(pDX, IDC_MARIN_L, m_dMarinL);
	DDX_Text(pDX, IDC_MARIN_T, m_dMarinT);
	DDX_Text(pDX, IDC_ROWSPACE, m_dRowSpace);
	DDX_Text(pDX, IDC_COLSPACE, m_dColSpace);
	DDX_Text(pDX, IDC_MARIN_B, m_dMarinB);
	DDX_Text(pDX, IDC_MARIN_R, m_dMarinR);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabDlg, CDialog)
	//{{AFX_MSG_MAP(CTabDlg)
	ON_BN_CLICKED(IDC_BTN_DISPLAY, OnBtnDisplay)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_TAB_PREVIEW, OnTabPreview)
	ON_BN_CLICKED(IDC_REP_PREVIEW, OnRepPreview)
	ON_BN_CLICKED(IDC_REP_PNT, OnRepPnt)
	ON_BN_CLICKED(IDC_TAB_PNT, OnTabPnt)
	ON_BN_CLICKED(IDC_A4, OnA4)
	ON_BN_CLICKED(IDC_RADIO_TAB, OnTab)
	ON_BN_CLICKED(IDC_PARAM_SAVE, OnParamSave)
	//}}AFX_MSG_MAP

	ON_MESSAGE(WM_BEGIN_PRINTING,OnBeginPrinting)
	ON_MESSAGE(WM_END_PRINTING,OnEndPrinting)
	ON_MESSAGE(WM_MY_PRINT,OnMyPrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabDlg message handlers

void CTabDlg::OnBtnDisplay() 
{	
	//计算将要刷新的区域
	if (m_btnA4.GetCheck() == TRUE) 
	{
		CPoint ptOri;
		ptOri.x = (m_rtDisplay.Width() - m_szA4.cx)/2 + m_rtDisplay.left;
		ptOri.y = (m_rtDisplay.Height() - m_szA4.cy)/2 + m_rtDisplay.top;
		m_rtA4 = CRect(ptOri.x, ptOri.y, ptOri.x+m_szA4.cx, ptOri.y+m_szA4.cy);
		TRACE("A4长：%d, A4宽：%d", m_rtA4.Width(), m_rtA4.Height());
		
		UpdateData(TRUE);
		m_bBtnState = TRUE;
		InvalidateRect(m_rtDisplay);
	}
	else
	{
		UpdateData(TRUE);
		if (m_dMarinL >= (double)m_dLen/2.0 || m_dMarinR >= (double)m_dLen/2.0 || \
				m_dMarinT >= (double)m_dWid/2.0 || m_dMarinB >= (double)m_dWid/2.0)
			return;
		m_bBtnState = TRUE;
		InvalidateRect(m_rtDisplay);
	}
}

BOOL CTabDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//设置默认字体
	
	((CStatic*)GetDlgItem(IDC_TAB_PARAM))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_STATIC_LEN))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_STATIC_WID))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_STATIC_FONT))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_STATIC_VERSP))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_STATIC_HORSP))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_SP_LEFT))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_SP_RIGHT))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_SP_TOP))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_SP_BOTTOM))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_STATIC_ROW))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_STATIC_COL))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_STATIC_TAB_PREVIEW))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_STATIC_REP_PNT))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_A4))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_RADIO_TAB))->SetFont(&g_fontEdit);
	((CStatic*)GetDlgItem(IDC_STATIC_TABHORSP))->SetFont(&g_fontEdit);

	((CEdit*)GetDlgItem(IDC_LEN))->SetFont(&g_fontEdit);
	((CEdit*)GetDlgItem(IDC_WID))->SetFont(&g_fontEdit);
	((CEdit*)GetDlgItem(IDC_FONT))->SetFont(&g_fontEdit);
	((CEdit*)GetDlgItem(IDC_ROWSPACE))->SetFont(&g_fontEdit);
	((CEdit*)GetDlgItem(IDC_COLSPACE))->SetFont(&g_fontEdit);
	((CEdit*)GetDlgItem(IDC_MARIN_L))->SetFont(&g_fontEdit);
	((CEdit*)GetDlgItem(IDC_MARIN_R))->SetFont(&g_fontEdit);
	((CEdit*)GetDlgItem(IDC_MARIN_T))->SetFont(&g_fontEdit);
	((CEdit*)GetDlgItem(IDC_MARIN_B))->SetFont(&g_fontEdit);
	((CEdit*)GetDlgItem(IDC_ROW))->SetFont(&g_fontEdit);
	((CEdit*)GetDlgItem(IDC_COL))->SetFont(&g_fontEdit);
	((CEdit*)GetDlgItem(IDC_TABCOLSPACE))->SetFont(&g_fontEdit);

	//给按钮设默认字体
	((CButton*)GetDlgItem(IDC_REP_PNT))->SetFont(&g_fontEdit);
	((CButton*)GetDlgItem(IDC_REP_PREVIEW))->SetFont(&g_fontEdit);
	((CButton*)GetDlgItem(IDC_BTN_DISPLAY))->SetFont(&g_fontEdit);
	((CButton*)GetDlgItem(IDC_TAB_PREVIEW))->SetFont(&g_fontEdit);
	((CButton*)GetDlgItem(IDC_TAB_PNT))->SetFont(&g_fontEdit);
	((CButton*)GetDlgItem(IDC_EXIT))->SetFont(&g_fontEdit);
	((CButton*)GetDlgItem(IDC_PARAM_SAVE))->SetFont(&g_fontEdit);
	
    OnLanguage();
	//获取static控件的区域
	((CWnd*)GetDlgItem(IDC_STATIC_TAB))->GetWindowRect(m_rtDisplay);
	TRACE("static控件：长：%d	宽：%d\n", m_rtDisplay.Width(), m_rtDisplay.Height());

	//给标签设置默认值
//	SetDlgItemText(IDC_LEN, _T("49"));
//	SetDlgItemText(IDC_WID, _T("31"));
//	SetDlgItemText(IDC_ROW, _T("8"));
//	SetDlgItemText(IDC_COL, _T("4"));
//	SetDlgItemText(IDC_MARIN_L, _T("2"));
//	//SetDlgItemText(IDC_MARIN_R, _T("2"));
//	SetDlgItemText(IDC_MARIN_T, _T("2"));
//	SetDlgItemText(IDC_ROWSPACE, _T("0"));
//	SetDlgItemText(IDC_COLSPACE, _T("0"));
	OnA4();

	//设置默认单选按钮
	((CButton*)GetDlgItem(IDC_A4))->SetCheck(TRUE);

	//隐藏右边距和下边距的Edit框
	((CStatic*)GetDlgItem(IDC_SP_RIGHT))->ShowWindow(FALSE);
	((CStatic*)GetDlgItem(IDC_SP_BOTTOM))->ShowWindow(FALSE);
	((CStatic*)GetDlgItem(IDC_STATIC_TABHORSP))->ShowWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_MARIN_R))->ShowWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_MARIN_B))->ShowWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_TABCOLSPACE))->ShowWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTabDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	int x = dc.GetDeviceCaps(LOGPIXELSX);
	int y = dc.GetDeviceCaps(LOGPIXELSY);

	//绘制预览区域
	dc.FillSolidRect(m_rtDisplay, RGB(255, 255, 255));
	if (m_bBtnState == TRUE) 
	{
		if (m_btnA4.GetCheck() == TRUE) 
		{
			//计算A4在static纸上的起点位置
			m_ptOri.x = (m_rtDisplay.Width() - m_szA4.cx)/2 + m_rtDisplay.left;
			m_ptOri.y = (m_rtDisplay.Height() - m_szA4.cy)/2 + m_rtDisplay.top;
			dc.Rectangle(m_ptOri.x, m_ptOri.y, m_ptOri.x+m_szA4.cx, m_ptOri.y+m_szA4.cy);
			
			double dMarinLTmp = m_dMarinL;
			double dMarinTTmp = m_dMarinT;
			//绘制标签
			m_ptOri.x += dMarinLTmp;
			m_ptOri.y += dMarinTTmp;
			
			for(int i=0; i<m_nRow; i++)
			{
				for(int j=0; j<m_nCol; j++)
				{
					dc.Rectangle(j*(m_dColSpace+m_dLen)+m_ptOri.x, i*(m_dRowSpace+m_dWid)+m_ptOri.y, \
						j*(m_dColSpace+m_dLen)+m_ptOri.x+m_dLen, i*(m_dRowSpace+m_dWid)+m_ptOri.y+m_dWid);
					dc.MoveTo(j*(m_dColSpace+m_dLen)+m_ptOri.x+m_dLen/2, i*(m_dRowSpace+m_dWid)+m_ptOri.y);
					dc.LineTo(j*(m_dColSpace+m_dLen)+m_ptOri.x+m_dLen/2, i*(m_dRowSpace+m_dWid)+m_ptOri.y+m_dWid/3);
					dc.MoveTo(j*(m_dColSpace+m_dLen)+m_ptOri.x, i*(m_dRowSpace+m_dWid)+m_ptOri.y+m_dWid/3);
					dc.LineTo(j*(m_dColSpace+m_dLen)+m_ptOri.x+m_dLen, i*(m_dRowSpace+m_dWid)+m_ptOri.y+m_dWid/3);
					dc.MoveTo(j*(m_dColSpace+m_dLen)+m_ptOri.x, i*(m_dRowSpace+m_dWid)+m_ptOri.y+m_dWid/3*2);
					dc.LineTo(j*(m_dColSpace+m_dLen)+m_ptOri.x+m_dLen, i*(m_dRowSpace+m_dWid)+m_ptOri.y+m_dWid/3*2);
				}
			}
			//将画出static控件框的部分以背景色填充
			CRect client;
			this->GetClientRect(&client);
			dc.FillSolidRect(CRect(m_ptOri.x+m_szA4.cx-m_dMarinL, m_ptOri.y, m_rtDisplay.right, m_rtDisplay.bottom), RGB(255, 255, 255));
			dc.FillSolidRect(CRect(m_rtDisplay.right, m_rtDisplay.top, client.right, client.bottom), RGB(214, 226, 247));
			dc.FillSolidRect(CRect(m_rtDisplay.left, m_rtDisplay.bottom, client.right, client.bottom), RGB(214, 226, 247));
			//m_bBtnState = FALSE;
			//重画依次A4纸的框
			//dc.Rectangle(m_ptOri.x, m_ptOri.y, m_ptOri.x+m_szA4.cx, m_ptOri.y+m_szA4.cy);
		}
		if (((CButton*)GetDlgItem(IDC_RADIO_TAB))->GetCheck() == TRUE) 
		{
			//放大比例
			double zoom = (double)280/m_dLen > (double)296/m_dWid? (double)296/m_dWid:(double)280/m_dLen;	//标签纸和显示区域的比例
			double ratex = (m_dLen-m_dMarinL-m_dMarinR) / (double)m_dLen;
			double ratey = (m_dWid-m_dMarinT-m_dMarinB) / (double)m_dWid;

			//计算Tab纸在static控件上的起点位置
			m_ptOri.x = (m_rtDisplay.Width() - m_dLen*zoom)/2 + m_rtDisplay.left;
			m_ptOri.y = (m_rtDisplay.Height() - m_dWid*zoom)/2 + m_rtDisplay.top;
			dc.Rectangle(m_ptOri.x, m_ptOri.y, m_ptOri.x+m_dLen*zoom, m_ptOri.y+m_dWid*zoom);

			//绘制标签
			m_ptOri.x += m_dMarinL*zoom*ratex;
			m_ptOri.y += m_dMarinT*zoom*ratey;	
			
			dc.Rectangle(m_ptOri.x, m_ptOri.y, m_ptOri.x+(m_dLen-m_dMarinL-m_dMarinR)*zoom, m_ptOri.y+(m_dWid-m_dMarinT-m_dMarinB)*zoom);
			dc.MoveTo(m_ptOri.x+m_dLen/2*zoom*ratex, m_ptOri.y);
			dc.LineTo(m_ptOri.x+m_dLen/2*zoom*ratex, m_ptOri.y+m_dWid/3*zoom*ratey);
			dc.MoveTo(m_ptOri.x, m_ptOri.y+m_dWid/3*zoom*ratey);
			dc.LineTo(m_ptOri.x+m_dLen*zoom*ratex, m_ptOri.y+m_dWid/3*zoom*ratey);
			dc.MoveTo(m_ptOri.x, m_ptOri.y+m_dWid/3*2*zoom*ratey);
			dc.LineTo(m_ptOri.x+m_dLen*zoom*ratex, m_ptOri.y+m_dWid/3*2*zoom*ratey);
			CFont font;
			CFont *pOldFont;
			font.CreateFont(20, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,\
				DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, "Arail");
			pOldFont = dc.SelectObject(&font);
			dc.TextOut((m_dLen-m_dMarinL-m_dMarinR)/20.0*zoom*ratex+m_ptOri.x, (m_dWid-m_dMarinT-m_dMarinB)/15.0*zoom*ratey+m_ptOri.y, "客户名");
			dc.TextOut(m_ptOri.x+m_dLen/2.0*zoom*ratex+(m_dLen-m_dMarinL-m_dMarinR)/20.0, (m_dWid-m_dMarinT-m_dMarinB)/15.0*zoom*ratey+m_ptOri.y, "订单号");
			dc.TextOut((m_dLen-m_dMarinL-m_dMarinR)/3.0*zoom*ratex+m_ptOri.x, (m_dWid-m_dMarinT-m_dMarinB)/6.0*zoom*ratey+m_ptOri.y+(m_dWid-m_dMarinT-m_dMarinB)/3.0*zoom*ratey, "1000 x 1000");
			dc.TextOut((m_dLen-m_dMarinL-m_dMarinR)/15.0*zoom*ratex+m_ptOri.x, (m_dWid-m_dMarinT-m_dMarinB)/4.0*zoom*ratey+m_ptOri.y+(m_dWid-m_dMarinT-m_dMarinB)/3.0*2.0*zoom*ratey, "注释");
			dc.SelectObject(pOldFont);
	
			//将画出static控件框的部分以背景色填充
			/*
			CRect client;
			this->GetClientRect(&client);
			dc.FillSolidRect(CRect(m_ptOri.x+(m_szTab.cx-m_dMarinL)*2, m_ptOri.y, m_rtDisplay.right, m_rtDisplay.bottom), RGB(255, 255, 255));
			dc.FillSolidRect(CRect(m_rtDisplay.right, m_rtDisplay.top, client.right, client.bottom), RGB(203, 213, 237));
			dc.FillSolidRect(CRect(m_ptOri.x, m_szTab.cy*2+m_ptOri.y, m_rtDisplay.right, m_rtDisplay.bottom), RGB(255, 255, 255));
			dc.FillSolidRect(CRect(m_rtDisplay.left, m_rtDisplay.bottom, client.right, client.bottom), RGB(203, 213, 237));*/
			//m_bBtnState = FALSE;
		}
	}
	// Do not call CDialog::OnPaint() for painting messages
}

void CTabDlg::OnExit() 
{
	CDialog::OnOK();
}

//打印之前的设置函数(如打印页数的设置)
LRESULT CTabDlg::OnBeginPrinting(WPARAM wParam,LPARAM lParam)
{
	CDC* pDC			= (CDC*)wParam;
	CPrintInfo* pInfo	= (CPrintInfo *)lParam;

	int nLen = pDC->GetDeviceCaps(HORZRES);
	int nWid = pDC->GetDeviceCaps(VERTRES);
	
	//将所有的矩形成品放入一个链表
	CList<CNoRect, CNoRect> lstNoRt;
	SubTractNoRect(lstNoRt);
	
	//int nPixel = pDC->GetDeviceCaps(HORZSIZE);
	TRACE("屏幕长宽：%d %d", nLen, nWid);
	if (((CButton*)GetDlgItem(IDC_RADIO_TAB))->GetCheck()==TRUE && m_nSelect==1) 
	{	
		int nLogPixelHor = pDC->GetDeviceCaps(LOGPIXELSX);
		int nLogPixelVer = pDC->GetDeviceCaps(LOGPIXELSY);

		//获取列间距
		CString strHorSep;
		((CWnd*)GetDlgItem(IDC_TABCOLSPACE))->GetWindowText(strHorSep);
		int nHorSep = atoi(strHorSep);
		//当标签纸大小和所设不一致时，弹出提示框
		if (fabs((double)nLen/nLogPixelHor*25.4 - m_dLen*m_nCol - nHorSep*(m_nCol-1)) > 2) 
		{
			CDlg_AfxMessage  Message;
			Message.bYesNo = FALSE;
			Message.strAfxYES ="确定";
			Message.strAfxTitle ="提示";
			Message.strAfxMessage = "您默认打印机所选纸张不合适";
			Message.DoModal();
			return 0L;
		}
		
		//设置比例
		//m_dRatio = (double)nLen/((double)m_dLen*m_nCol+(double)nHorSep*(m_nCol-1)) < (double)nWid/(double)m_dWid? \
			//(double)nLen/((double)m_dLen*m_nCol+(double)nHorSep*(m_nCol-1)) : (double)nWid/(double)m_dWid;
		m_dRatio = (double)nLen/((double)m_dLen*m_nCol+(double)nHorSep*(m_nCol-1));
		//m_dRatio = double(((int)m_dRatio*100)/100);
		//创建字体
		//m_nFont = 30/5*m_dScale;
		m_fntContent.CreateFont(m_nFont, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,\
			DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, "Arail");
		//设置打印的页数
		if (lstNoRt.GetCount()%m_nCol != 0) 
		{
			m_nPage = lstNoRt.GetCount()/m_nCol+1;
		}
		else
		{
			m_nPage = lstNoRt.GetCount()/m_nCol;
		}
		pInfo->SetMaxPage(m_nPage);
	}
	if (m_btnA4.GetCheck() == TRUE) 
	{
		if (m_nSelect == 0) 
		{	
			m_dZoom = (double)nLen / 200.0 - 1;
			//m_dZoom = double(((int)m_dZoom*100)/100);
			//设置表格的大小
			int nLen = pDC->GetDeviceCaps(HORZRES);
			int nWid = pDC->GetDeviceCaps(VERTRES);
			m_szGrid.cx = 206;
			m_szGrid.cy = 206 / 15;
			m_nLineHeight = m_szGrid.cy / 2.0;
			//创建字体
			m_fntTitle.CreateFont(m_nLineHeight*m_dZoom, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,\
				DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, "Arail");
			m_fntWord.CreateFont((m_nLineHeight)*m_dZoom, 0, 0, 0, 300, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,\
				DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, "Arail");
			m_fntRepDigit.CreateFont(/*(m_nLineHeight-6)*/3.5*m_dZoom, 0, 0, 0, (m_nLineHeight-6)*m_dZoom*3, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,\
				DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, "Arail");
			//设置打印的页数

			//////////////////////////////////////////////////////////////////////////
			CRptDgm *pDgm = NULL;
			CList<CRptDgm*, CRptDgm*>* pLstDgm = ((CRectOptDlg*)(this->GetParent()))->m_RtOptDll.GetDgmList();
			POSITION posDgm = pLstDgm->GetHeadPosition();
			while (posDgm != NULL) 
			{
				pDgm = pLstDgm->GetAt(posDgm);
				m_lDgmCnt += pDgm->nCutTimes;
				pLstDgm->GetNext(posDgm);
			}
			//////////////////////////////////////////////////////////////////////////

			//计算成品矩形行数
			//////////////////////////////////////////////////////////////////////////
			memset(m_num, 0, sizeof(m_num));
			m_nCnt = statProdCount(m_num, *pLstDgm);
			memset(m_num, 0, sizeof(m_num));
			//////////////////////////////////////////////////////////////////////////
			int nPageData;
			int nPageNoRt = m_nCnt / 84;
			int nRestNoRt = m_nCnt % 84;
			if ( nRestNoRt > 0 ) 
			{
				nPageData = nPageNoRt + 1;
			}
			else
			{
				nPageData = nPageNoRt;
			}
			
			int nPageDgm;
			int nPageFull = m_lDgmCnt / 4;
			int nRestDgm  = m_lDgmCnt % 4;
			if ( nRestDgm > 0) 
			{
				nPageDgm = nPageFull + 1;
			}
			else
			{
				nPageDgm = nPageFull;
			}
			m_nReportPage = nPageData + nPageDgm;
			pInfo->SetMaxPage(m_nReportPage);
			//pInfo->SetMaxPage(4);
		}		
		if (m_nSelect == 1) 
		{
			//设置比例
			m_dScale = (double)nLen / 200/*m_szA4.cx*/;
			//m_dScale = double(((int)m_dScale*100)/100);
			//创建字体
			//m_nFont = 30/5*m_dScale;
			m_fntContent.CreateFont(m_nFont, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,\
				DEFAULT_QUALITY, DEFAULT_PITCH|FF_SWISS, "Arail");
			//设置打印的页数
			int nRet = lstNoRt.GetCount() / (m_nRow*m_nCol);
			int nReminder = lstNoRt.GetCount() % (m_nRow*m_nCol);
			int m_nPage = nReminder > 0? nRet + 1 : nRet;
			pInfo->SetMaxPage(m_nPage);
		}
	}	
	return TRUE;
}
//打印之后释放资源
LRESULT CTabDlg::OnEndPrinting(WPARAM wParam,LPARAM lParam)
{
	//将打印页数置0
	m_nPage = 0;
	//报表
	if (m_fntTitle.m_hObject != NULL) 
		m_fntTitle.DeleteObject();
	if (m_fntWord.m_hObject != NULL) 
		m_fntWord.DeleteObject();
	if (m_fntRepDigit.m_hObject != NULL) 
		m_fntRepDigit.DeleteObject();
	//标签
	if (m_fntContent.m_hObject) 
		m_fntContent.DeleteObject();
	return TRUE;
}
//打印函数，打印页面的东西都是从这绘制出来的
LRESULT CTabDlg::OnMyPrint(WPARAM wParam,LPARAM lParam)
{
	CDC* pDC			= (CDC*)wParam;
	CPrintInfo* pInfo	= (CPrintInfo *)lParam;
	int nPageNumber = pInfo->m_nCurPage;
	if (m_nSelect == 1) 
	{
		CList<CNoRect, CNoRect> lstNoRt;
		SubTractNoRect(lstNoRt);
		if (m_btnA4.GetCheck() == TRUE) 
		{
			DrawTab(pDC, (nPageNumber-1)*m_nRow*m_nCol, lstNoRt.GetCount(), lstNoRt);	
		}
		if (((CButton*)GetDlgItem(IDC_RADIO_TAB))->GetCheck() == TRUE) 
		{
			DrawTab(pDC, (nPageNumber-1)*m_nCol, lstNoRt);	
		}
	}
	if (m_nSelect == 0) 
	{
		int nPage = m_nCnt%84 > 0? m_nCnt/84+1 : m_nCnt/84;
		if (nPageNumber == 1) 
		{
			DrawReport(pDC, pInfo);	
		}
		else if (nPageNumber >1 && nPageNumber <= nPage) 
		{
			DrawThrdGrid(pDC, pInfo, m_nCnt, nPageNumber);
		}
		else
		{	
			CRectOptDlg *pDlg = (CRectOptDlg*)this->GetParent();
			DrawThumbNail(pDC, CPoint(2, 2), (nPageNumber-nPage-1)*4, pDlg, pInfo);
		}
	}
	return TRUE;
}

//Tab预览
void CTabDlg::OnTabPreview() 
{
	m_nSelect = 1;
	UpdateData(TRUE);
	CPrintDialog dlg(FALSE);
	if (!dlg.GetDefaults()) 
	{
		CDlg_AfxMessage  Message;
		Message.bYesNo = FALSE;
		Message.strAfxYES ="确定";
		Message.strAfxTitle ="提示";
		Message.strAfxMessage = "您未设置默认打印机";
		Message.DoModal(); 	
	}
	else
	{
		//标签打印预览
		CPrintFrame *pFrame = new CPrintFrame;
		pFrame->m_pCallerDlg = this;
		pFrame->Create(NULL,"Curve Print Preview",WS_OVERLAPPEDWINDOW,CRect(0,0,0,0));
		pFrame->m_pView->OnMyPrintPreview();
	}
}

//Report预览
void CTabDlg::OnRepPreview() 
{
	m_nSelect = 0;
	UpdateData(TRUE);
	CPrintDialog dlg(FALSE);
	if (!dlg.GetDefaults()) 
	{
		CDlg_AfxMessage  Message;
		Message.bYesNo = FALSE;
		Message.strAfxYES ="确定";
		Message.strAfxTitle ="提示";
		Message.strAfxMessage = "您未设置默认打印机";
		Message.DoModal(); 	
	}
	else
	{
		//报表打印预览
		CPrintFrame *pFrame = new CPrintFrame;
		pFrame->m_pCallerDlg = this;
		pFrame->Create(NULL,"Curve Print Preview",WS_OVERLAPPEDWINDOW,CRect(0,0,0,0));
		pFrame->m_pView->OnMyPrintPreview();
	}
}

//Report打印
void CTabDlg::OnRepPnt() 
{
	m_nSelect = 0;
	UpdateData(TRUE);
	CPrintDialog dlg(FALSE);
	if (!dlg.GetDefaults()) 
	{
		CDlg_AfxMessage  Message;
		Message.bYesNo = FALSE;
		Message.strAfxYES ="确定";
		Message.strAfxTitle ="提示";
		Message.strAfxMessage = "您未设置默认打印机";
		Message.DoModal(); 	
	}
	else
	{
		//报表打印
		CPrintFrame *pFrame = new CPrintFrame;
		pFrame->m_pCallerDlg = this;
		pFrame->Create(NULL,"Curve Print",WS_OVERLAPPEDWINDOW,CRect(0,0,0,0));
		pFrame->m_pView->OnMyPrint();
	}
}

//Tab打印
void CTabDlg::OnTabPnt() 
{
	m_nSelect = 1;
	UpdateData(TRUE);
	CPrintDialog dlg(FALSE);
	if (!dlg.GetDefaults()) 
	{
		CDlg_AfxMessage  Message;
		Message.bYesNo = FALSE;
		Message.strAfxYES ="确定";
		Message.strAfxTitle ="提示";
		Message.strAfxMessage = "您未设置默认打印机";
		Message.DoModal(); 	
	}
	else
	{
		//标签打印
		CPrintFrame *pFrame = new CPrintFrame;
		pFrame->m_pCallerDlg = this;
		pFrame->Create(NULL,"Curve Print",WS_OVERLAPPEDWINDOW,CRect(0,0,0,0));
		pFrame->m_pView->OnMyPrint();
	}
}

//绘制Report
void CTabDlg::DrawReport(CDC *pDC, CPrintInfo* pInfo)
{
	CRectOptDlg *pRtOptDlg = (CRectOptDlg*)(this->GetParent());
	assert(pRtOptDlg != NULL);
	CFont *pOldFont = NULL;
	CPen pen(PS_SOLID, 0.3*m_dZoom, RGB(0, 0, 0));
	CPen *pOldPen = pDC->SelectObject(&pen);
	//定义在A4纸上report开始的起点
	CPoint ptOri(2, 1);
	//画第一个表格
	pDC->Rectangle(ptOri.x*m_dZoom,  ptOri.y*m_dZoom, (m_szGrid.cx+ptOri.x)*m_dZoom, (m_szGrid.cy+ptOri.y)*m_dZoom);
	pDC->MoveTo(ptOri.x*m_dZoom,  (m_szGrid.cy/2+ptOri.y)*m_dZoom);
	pDC->LineTo((m_szGrid.cx+ptOri.x)*m_dZoom, (m_szGrid.cy/2+ptOri.y)*m_dZoom);
	for(int i=0; i<3; i++)
	{
		pDC->MoveTo((i+1)*(m_szGrid.cx/4+ptOri.x)*m_dZoom,  ptOri.y*m_dZoom);
		pDC->LineTo((i+1)*(m_szGrid.cx/4+ptOri.x)*m_dZoom,  (m_szGrid.cy+ptOri.y)*m_dZoom);
	}
	//填写项目名
	pDC->SelectObject(&m_fntWord);
	CString str;
	((CWnd*)pRtOptDlg->GetDlgItem(IDC_EDIT12))->GetWindowText(str);
	pDC->TextOut((m_szGrid.cx/4+m_nLineHeight/10+ptOri.x)*m_dZoom,  (m_nLineHeight/10+ptOri.y)*m_dZoom, str);
	//填写当前日期
	CTime time = CTime::GetCurrentTime();
	str.Format("%d-%d-%d", time.GetYear(), time.GetMonth(), time.GetDay());
	pDC->TextOut((3.1*m_szGrid.cx/4+m_nLineHeight/10*2+ptOri.x)*m_dZoom,  (m_nLineHeight/10+ptOri.y)*m_dZoom, str);
	pDC->TextOut((m_nLineHeight/10+ptOri.x)*m_dZoom,  (m_nLineHeight/10+m_nLineHeight+ptOri.y)*m_dZoom, "制样:");
	pDC->TextOut((m_nLineHeight/10+m_szGrid.cx/4+ptOri.x)*m_dZoom,  (m_nLineHeight/10+m_nLineHeight+ptOri.y)*m_dZoom, "核准:");
	pDC->TextOut((m_nLineHeight/10+m_szGrid.cx/4*2.1+ptOri.x)*m_dZoom,  (m_nLineHeight/10+m_nLineHeight+ptOri.y)*m_dZoom, "领料:");
	pDC->TextOut((m_nLineHeight/10+m_szGrid.cx/4*3.1+ptOri.x)*m_dZoom,  (m_nLineHeight/10+m_nLineHeight+ptOri.y)*m_dZoom, "开料:");
	
	pDC->SelectObject(pOldFont);
	//画标题（方案汇总：（切成成品：9片， 总周长：31.2米））
	pOldFont = pDC->SelectObject(&m_fntTitle);
	//获取成品片数

	//////////////////////////////////////////////////////////////////////////
	int nProCnt = 0;
	CRptDgm *pDgmPro = NULL;
	CList<CRptDgm*, CRptDgm*>* pLstDgm = pRtOptDlg->m_RtOptDll.GetDgmList();
	POSITION posPro = pLstDgm->GetHeadPosition();
	while (posPro != NULL) 
	{
		pDgmPro = pLstDgm->GetAt(posPro);
		nProCnt += pDgmPro->nCutTimes * pDgmPro->pRtLay->GetCount();
		pLstDgm->GetNext(posPro);
	}
	str.Format("方案汇总(切成成品:%d片)", nProCnt);
	//////////////////////////////////////////////////////////////////////////
	
	pDC->TextOut((ptOri.x+m_szGrid.cx/3)*m_dZoom, (m_nLineHeight*2+ptOri.y)*m_dZoom, str);
	pDC->SelectObject(pOldFont);
	//画第二个表格
	pDC->Rectangle(ptOri.x*m_dZoom,  (m_nLineHeight*3+ptOri.y)*m_dZoom, (m_szGrid.cx+ptOri.x)*m_dZoom, (m_nLineHeight*5+ptOri.y)*m_dZoom);
	pDC->MoveTo(ptOri.x*m_dZoom,  (m_nLineHeight*4+ptOri.y)*m_dZoom);
	pDC->LineTo((m_szGrid.cx+ptOri.x)*m_dZoom, (m_nLineHeight*4+ptOri.y)*m_dZoom);
	pDC->MoveTo((m_szGrid.cx/5+ptOri.x)*m_dZoom, (m_nLineHeight*3+ptOri.y)*m_dZoom);
	pDC->LineTo((m_szGrid.cx/5+ptOri.x)*m_dZoom, (m_nLineHeight*5+ptOri.y)*m_dZoom);
	pOldFont = pDC->SelectObject(&m_fntWord);
	pDC->TextOut((m_szGrid.cx/5/4+ptOri.x)*m_dZoom,  (m_nLineHeight/10+m_nLineHeight*3+ptOri.y)*m_dZoom, "原片尺寸");
	int nCellWid = m_szGrid.cx/5*4/5;
	for(i=0; i<4; i++)
	{
		pDC->MoveTo((nCellWid*(i+1)+m_szGrid.cx/5+ptOri.x)*m_dZoom,  (m_nLineHeight*3+ptOri.y)*m_dZoom);
		pDC->LineTo((nCellWid*(i+1)+m_szGrid.cx/5+ptOri.x)*m_dZoom,  (m_nLineHeight*5+ptOri.y)*m_dZoom);
	}
	pDC->TextOut(( nCellWid/3+m_szGrid.cx/5+ptOri.x)*m_dZoom,  (m_nLineHeight/10+m_nLineHeight*3+ptOri.y)*m_dZoom, "用量");
	pDC->TextOut(( nCellWid+nCellWid/5+m_szGrid.cx/5+ptOri.x)*m_dZoom,  (m_nLineHeight/10+m_nLineHeight*3+ptOri.y)*m_dZoom, "耗用面积");
	pDC->TextOut(( 2*nCellWid+nCellWid/4+m_szGrid.cx/5+ptOri.x)*m_dZoom,  (m_nLineHeight/10+m_nLineHeight*3+ptOri.y)*m_dZoom, "出材率");
	pDC->TextOut(( 3*nCellWid+nCellWid/5+m_szGrid.cx/5+ptOri.x)*m_dZoom,  (m_nLineHeight/10+m_nLineHeight*3+ptOri.y)*m_dZoom, "实用面积");
	pDC->TextOut(( 4*nCellWid+nCellWid/5+m_szGrid.cx/5+ptOri.x)*m_dZoom,  (m_nLineHeight/10+m_nLineHeight*3+ptOri.y)*m_dZoom, "用料成本");
	pDC->SelectObject(pOldFont);
	//获取原片尺寸
	pOldFont = pDC->SelectObject(&m_fntRepDigit);
	double zoom = 1;
	if (pLstDgm->GetHeadPosition() == NULL) 
	{
		return;
	}
	CRptDgm *pDgm = pLstDgm->GetHead();
	CString strRtLen, strRtWid;
	strRtLen.Format("%.2f", pDgm->rtRaw.rt.Width() > pDgm->rtRaw.rt.Height()? pDgm->rtRaw.rt.Width():pDgm->rtRaw.rt.Height());
	strRtWid.Format("%.2f", pDgm->rtRaw.rt.Width() > pDgm->rtRaw.rt.Height()? pDgm->rtRaw.rt.Height():pDgm->rtRaw.rt.Width());
	str.Format("%g x %g", atof(strRtLen), atof(strRtWid));
	pDC->TextOut((m_szGrid.cx/5/20+ptOri.x)*m_dZoom,  (m_nLineHeight/10+m_nLineHeight*4+ptOri.y)*m_dZoom, str);
	//获取原片数量
	
	//////////////////////////////////////////////////////////////////////////
	int nRawCnt = 0;
	CRptDgm *pDgmRaw = NULL;
	POSITION posRaw = pLstDgm->GetHeadPosition();
	while (posRaw != NULL) 
	{
		pDgmRaw = pLstDgm->GetAt(posRaw);
		nRawCnt += pDgmRaw->nCutTimes;
		pLstDgm->GetNext(posRaw);
	}
	str.Format("%d片", nRawCnt);
	//////////////////////////////////////////////////////////////////////////
	
	pDC->TextOut(( nCellWid/3+m_szGrid.cx/5+ptOri.x)*m_dZoom,  (m_nLineHeight/10+m_nLineHeight*4+ptOri.y)*m_dZoom, str);

	//////////////////////////////////////////////////////////////////////////
	str.Format("%.2fm2", nRawCnt*fabs(pDgm->rtRaw.rt.Width()*pDgm->rtRaw.rt.Height())/1000000);
	//////////////////////////////////////////////////////////////////////////
	
	pDC->TextOut(( nCellWid+nCellWid/5+m_szGrid.cx/5+ptOri.x)*m_dZoom,  (m_nLineHeight/10+m_nLineHeight*4+ptOri.y)*m_dZoom, str);
	
	str.Format("%.2f%%", pRtOptDlg->m_RtOptDll.GetUtil()*100);
	pDC->TextOut(( 2*nCellWid+nCellWid/4+m_szGrid.cx/5+ptOri.x)*m_dZoom,  (m_nLineHeight/10+m_nLineHeight*4+ptOri.y)*m_dZoom, str);

	//////////////////////////////////////////////////////////////////////////
	str.Format("%.2fm2", pRtOptDlg->m_RtOptDll.GetUtil()*nRawCnt*pDgm->rtRaw.rt.Width()*pDgm->rtRaw.rt.Height()/1000000);
	//////////////////////////////////////////////////////////////////////////
	
	pDC->TextOut(( 3*nCellWid+nCellWid/5+m_szGrid.cx/5+ptOri.x)*m_dZoom,  (m_nLineHeight/10+m_nLineHeight*4+ptOri.y)*m_dZoom, str);
	pDC->SelectObject(pOldFont);
	
	//画第三个表格
	//获取成品尺寸和数量
	memset(m_num, 0, sizeof(m_num));
	statProdCount(m_num, *pLstDgm);
	//int cnt = statProdCount(num, *pLstDgm);//cnt：成品种类数
	int cnt = 84;
	pDC->SelectObject(&m_fntWord);
	CPoint ptThdGrd(ptOri.x, m_nLineHeight/10+m_nLineHeight*5+ptOri.y);

	DrawThrdGrid(pDC, ptThdGrd, pRtOptDlg, cnt, m_num, 0);

	//DrawThumbNail(pDC, ptThdGrd, cnt, 0, pRtOptDlg, pInfo);
	
	//将原来的font选回设备
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);
}

void CTabDlg::DrawThrdGrid(CDC *pDC, CPoint ptThdGrd, CRectOptDlg *pRtOptDlg, int cnt, int* num, int nPage)
{
	pDC->Rectangle(ptThdGrd.x*m_dZoom, ptThdGrd.y*m_dZoom, (m_szGrid.cx+ptThdGrd.x)*m_dZoom, (((cnt+1)/2+1)*m_nLineHeight+ptThdGrd.y)*m_dZoom);
	for(int i=0+nPage*42; i<(cnt+1)/2 && i<42+nPage*42; i++)
	{
		pDC->MoveTo(ptThdGrd.x*m_dZoom,  ((i+1)*m_nLineHeight+ptThdGrd.y)*m_dZoom);
		pDC->LineTo((m_szGrid.cx+ptThdGrd.x)*m_dZoom, ((i+1)*m_nLineHeight+ptThdGrd.y)*m_dZoom);
	}
	
	int nCountWid = m_szGrid.cx/2/7*3;
	int nNameWid = m_szGrid.cx/2/7*4;
	pDC->TextOut((nCountWid/40+ptThdGrd.x)*m_dZoom, (m_nLineHeight/10+ptThdGrd.y)*m_dZoom, "成品尺寸和数量");
	pDC->TextOut((nCountWid/3+nCountWid+ptThdGrd.x)*m_dZoom, (m_nLineHeight/10+ptThdGrd.y)*m_dZoom, "成品名称");
	pDC->TextOut((nCountWid/15+nCountWid+nNameWid+ptThdGrd.x)*m_dZoom, (m_nLineHeight/10+ptThdGrd.y)*m_dZoom, "成品尺寸和数量");
	pDC->TextOut((nCountWid/2+2*nCountWid+nNameWid+ptThdGrd.x)*m_dZoom, (m_nLineHeight/10+ptThdGrd.y)*m_dZoom, "成品名称");
	for(int j=0; j<3; j++)
	{
		if (j==0) 
		{
			pDC->MoveTo((nCountWid+ptThdGrd.x)*m_dZoom,  ptThdGrd.y*m_dZoom);
			pDC->LineTo((nCountWid+ptThdGrd.x)*m_dZoom,  (((cnt+1)/2+1)*m_nLineHeight+ptThdGrd.y)*m_dZoom);
		}
		if (j==1) 
		{
			pDC->MoveTo((nCountWid+nNameWid+ptThdGrd.x-1)*m_dZoom,  ptThdGrd.y*m_dZoom);
			pDC->LineTo((nCountWid+nNameWid+ptThdGrd.x-1)*m_dZoom,  (((cnt+1)/2+1)*m_nLineHeight+ptThdGrd.y)*m_dZoom);
		}
		if (j==2) 
		{
			pDC->MoveTo((m_szGrid.cx/2+nCountWid+ptThdGrd.x)*m_dZoom,  ptThdGrd.y*m_dZoom);
			pDC->LineTo((m_szGrid.cx/2+nCountWid+ptThdGrd.x)*m_dZoom,  (((cnt+1)/2+1)*m_nLineHeight+ptThdGrd.y)*m_dZoom);
		}
	}
	CFont *pOldFont = pDC->SelectObject(&m_fntRepDigit);
	CString str;
	for(i=1; i<=cnt; i++)
	{
		if (i%2 != 0) 
		{
			if ( num[i] != 0 ) 
			{
				str.Format("%d)%sx%s=%d", i, pRtOptDlg->m_Grid.GetItemText(i, 1), pRtOptDlg->m_Grid.GetItemText(i, 2), num[i]);
				pDC->TextOut((nCountWid/40+ptThdGrd.x)*m_dZoom, ((i+1)/2*m_nLineHeight+m_nLineHeight/10+ptThdGrd.y)*m_dZoom, str);
				str.Format("%d", i);
				pDC->TextOut((nCountWid/2+nCountWid+ptThdGrd.x)*m_dZoom, ((i+1)/2*m_nLineHeight+m_nLineHeight/10+ptThdGrd.y)*m_dZoom, str);
			}
		}
		else
		{
			if ( num[i] != 0 ) 
			{
				str.Format("%d)%sx%s=%d", i, pRtOptDlg->m_Grid.GetItemText(i, 1), pRtOptDlg->m_Grid.GetItemText(i, 2), num[i]);
				pDC->TextOut(((nCountWid+nNameWid)+nCountWid/40+ptThdGrd.x)*m_dZoom, ((i+1)/2*m_nLineHeight+m_nLineHeight/10+ptThdGrd.y)*m_dZoom, str);
				str.Format("%d", i);
				pDC->TextOut(((nCountWid+nNameWid)+1.7*nCountWid+ptThdGrd.x)*m_dZoom, ((i+1)/2*m_nLineHeight+m_nLineHeight/10+ptThdGrd.y)*m_dZoom, str);
			}
		}
	}
	
	int nThumbLen = m_szGrid.cx/2;		
	int nThumbWid = nThumbLen*4/3;
}

void CTabDlg::DrawThrdGrid(CDC *pDC, CPrintInfo *pInfo, int cnt, int nPage)
{
	//TRACE(" \n%d\n", m_nLineHeight);
	CPoint ptThdGrd(1, 10);
	pDC->Rectangle(ptThdGrd.x*m_dZoom, ptThdGrd.y*m_dZoom, (m_szGrid.cx+ptThdGrd.x)*m_dZoom, (43*m_nLineHeight+ptThdGrd.y)*m_dZoom);
	for(int i=0; i<(cnt+1)/2 && i<43; i++)
	{
		pDC->MoveTo(ptThdGrd.x*m_dZoom,  ((i+1)*m_nLineHeight+ptThdGrd.y)*m_dZoom);
		pDC->LineTo((m_szGrid.cx+ptThdGrd.x)*m_dZoom, ((i+1)*m_nLineHeight+ptThdGrd.y)*m_dZoom);
	}
	
	int nCountWid = m_szGrid.cx/2/7*3;
	int nNameWid = m_szGrid.cx/2/7*4;
	pDC->TextOut((nCountWid/40+ptThdGrd.x)*m_dZoom, (m_nLineHeight/10+ptThdGrd.y)*m_dZoom, "成品尺寸和数量");
	pDC->TextOut((nCountWid/3+nCountWid+ptThdGrd.x)*m_dZoom, (m_nLineHeight/10+ptThdGrd.y)*m_dZoom, "成品名称");
	pDC->TextOut((nCountWid/15+nCountWid+nNameWid+ptThdGrd.x)*m_dZoom, (m_nLineHeight/10+ptThdGrd.y)*m_dZoom, "成品尺寸和数量");
	pDC->TextOut((nCountWid/2+2*nCountWid+nNameWid+ptThdGrd.x)*m_dZoom, (m_nLineHeight/10+ptThdGrd.y)*m_dZoom, "成品名称");
	for(int j=0; j<3; j++)
	{
		if (j==0) 
		{
			pDC->MoveTo((nCountWid+ptThdGrd.x)*m_dZoom,  ptThdGrd.y*m_dZoom);
			pDC->LineTo((nCountWid+ptThdGrd.x)*m_dZoom,  (43*m_nLineHeight+ptThdGrd.y)*m_dZoom);
		}
		if (j==1) 
		{
			pDC->MoveTo((nCountWid+nNameWid+ptThdGrd.x-1)*m_dZoom,  ptThdGrd.y*m_dZoom);
			pDC->LineTo((nCountWid+nNameWid+ptThdGrd.x-1)*m_dZoom,  (43*m_nLineHeight+ptThdGrd.y)*m_dZoom);
		}
		if (j==2) 
		{
			pDC->MoveTo((m_szGrid.cx/2+nCountWid+ptThdGrd.x)*m_dZoom,  ptThdGrd.y*m_dZoom);
			pDC->LineTo((m_szGrid.cx/2+nCountWid+ptThdGrd.x)*m_dZoom,  (43*m_nLineHeight+ptThdGrd.y)*m_dZoom);
		}
	}
	CFont *pOldFont = pDC->SelectObject(&m_fntRepDigit);
	CRectOptDlg *pRtOptDlg = (CRectOptDlg*)(this->GetParent());
	CString str;
	for(i=1; i<85 && i+(nPage-1)*84 <= cnt; i++)
	{
		//TRACE("%d", 1+(nPage-1)*84);
		if ((i+(nPage-1)*84)%2 != 0) 
		{
			if ( m_num[1+(nPage-1)*84] != 0) 
			{
				str.Format("%d)%sx%s=%d", i+(nPage-1)*84, pRtOptDlg->m_Grid.GetItemText(i+(nPage-1)*84, 1), pRtOptDlg->m_Grid.GetItemText(i+(nPage-1)*84, 2), m_num[i+(nPage-1)*84]);
				pDC->TextOut((nCountWid/40+ptThdGrd.x)*m_dZoom, ((i+1)/2*m_nLineHeight+m_nLineHeight/10+ptThdGrd.y)*m_dZoom, str);
				str.Format("%d", i+(nPage-1)*84);
				pDC->TextOut((nCountWid/2+nCountWid+ptThdGrd.x)*m_dZoom, ((i+1)/2*m_nLineHeight+m_nLineHeight/10+ptThdGrd.y)*m_dZoom, str);
			}
		}
		else
		{
			if ( m_num[i+(nPage-1)*84] != 0 ) 
			{
				str.Format("%d)%sx%s=%d", i+(nPage-1)*84, pRtOptDlg->m_Grid.GetItemText(i+(nPage-1)*84, 1), pRtOptDlg->m_Grid.GetItemText(i+(nPage-1)*84, 2), m_num[i+(nPage-1)*84]);
				pDC->TextOut(((nCountWid+nNameWid)+nCountWid/40+ptThdGrd.x)*m_dZoom, ((i+1)/2*m_nLineHeight+m_nLineHeight/10+ptThdGrd.y)*m_dZoom, str);
				str.Format("%d", i+(nPage-1)*84);
				pDC->TextOut(((nCountWid+nNameWid)+1.7*nCountWid+ptThdGrd.x)*m_dZoom, ((i+1)/2*m_nLineHeight+m_nLineHeight/10+ptThdGrd.y)*m_dZoom, str);
			}
		}
	}
	
	int nThumbLen = m_szGrid.cx/2;		
	int nThumbWid = nThumbLen*4/3;
}

//绘制标签
void CTabDlg::DrawTab(CDC *pDC, int nStart, int nEnd, CList<CNoRect, CNoRect>& lstRt)
{
	CFont *pOldFont;
	pOldFont = pDC->SelectObject(&m_fntContent);
	CPen pen(PS_SOLID, 0.40*m_dScale, RGB(0, 0, 0));
	CPen *pOldPen = pDC->SelectObject(&pen);
	//设置标签在A4纸上的起点
	CPoint ptOri(0, 0);
	//绘制标签
	double dMarinLTmp = m_dMarinL;
	double dMarinTTmp = m_dMarinT;
	if (dMarinLTmp < 3) 
	{
		dMarinLTmp = 0;
	}
	if (dMarinLTmp >= 3) 
	{
		dMarinLTmp -= 3;
	}
	if (dMarinTTmp < 4) 
	{
		dMarinTTmp = 0;
	}
	if (dMarinTTmp >= 4) 
	{
		dMarinTTmp -= 4;
	}
	ptOri.x += dMarinLTmp;
	ptOri.y += dMarinTTmp;
	for(int i=0; i<m_nRow; i++)
	{
		for(int j=0; j<m_nCol && (i*m_nCol+j+nStart)<lstRt.GetCount(); j++)
		{ 
			CString str;
			POSITION posNoRt = lstRt.FindIndex(i*m_nCol+j+nStart);
			
			if(posNoRt != NULL) 
			{
				CNoRect  noRt = lstRt.GetAt(posNoRt);
				TRACE("Tab:%d x %d", noRt.rt.Width(), noRt.rt.Height());
				
				pDC->Rectangle((j*(m_dColSpace+m_dLen)+ptOri.x)*m_dScale, (i*(m_dRowSpace+m_dWid)+ptOri.y)*m_dScale, \
					(j*(m_dColSpace+m_dLen)+ptOri.x+m_dLen)*m_dScale, (i*(m_dRowSpace+m_dWid)+ptOri.y+m_dWid)*m_dScale);
				pDC->MoveTo((j*(m_dColSpace+m_dLen)+ptOri.x+m_dLen/2)*m_dScale, (i*(m_dRowSpace+m_dWid)+ptOri.y)*m_dScale);
				pDC->LineTo((j*(m_dColSpace+m_dLen)+ptOri.x+m_dLen/2)*m_dScale, (i*(m_dRowSpace+m_dWid)+ptOri.y+m_dWid/3)*m_dScale);
				pDC->MoveTo((j*(m_dColSpace+m_dLen)+ptOri.x)*m_dScale, (i*(m_dRowSpace+m_dWid)+ptOri.y+m_dWid/3)*m_dScale);
				pDC->LineTo((j*(m_dColSpace+m_dLen)+ptOri.x+m_dLen)*m_dScale, (i*(m_dRowSpace+m_dWid)+ptOri.y+m_dWid/3)*m_dScale);
				pDC->MoveTo((j*(m_dColSpace+m_dLen)+ptOri.x)*m_dScale, (i*(m_dRowSpace+m_dWid)+ptOri.y+m_dWid/3*2)*m_dScale);
				pDC->LineTo((j*(m_dColSpace+m_dLen)+ptOri.x+m_dLen)*m_dScale, (i*(m_dRowSpace+m_dWid)+ptOri.y+m_dWid/3*2)*m_dScale);
				//TRACE("Tab:%d x %d", abs(noRt.rect->Width()/zoom)*m_dScale, abs(noRt.rect->Height()/zoom)*m_dScale);
				//显示用户名
				str.Format("%s", noRt.strCustName);
				TRACE("\n用户名：%s\n", noRt.strCustName);
				pDC->TextOut((j*(m_dColSpace+m_dLen)+ptOri.x)*m_dScale+m_dLen/30*m_dScale, (i*(m_dRowSpace+m_dWid)+ptOri.y)*m_dScale+m_dWid/9*m_dScale, str);
				//显示订单号
				str.Format("%s", noRt.strOrderNo);
				pDC->TextOut((j*(m_dColSpace+m_dLen)+ptOri.x+m_dLen/2)*m_dScale+m_dLen/30*m_dScale, (i*(m_dRowSpace+m_dWid)+ptOri.y)*m_dScale+m_dWid/9*m_dScale, str);
				//显示矩形尺寸
				CString strRtLen, strRtWid;
				strRtLen.Format("%.2f", noRt.rt.Width()>=noRt.rt.Height()? noRt.rt.Width():noRt.rt.Height());
				strRtWid.Format("%.2f", noRt.rt.Width()<noRt.rt.Height()? noRt.rt.Width():noRt.rt.Height());
				str.Format("%g x %g", atof(strRtLen), atof(strRtWid));
				pDC->TextOut((j*(m_dColSpace+m_dLen)+ptOri.x)*m_dScale+m_dLen/8*m_dScale, (i*(m_dRowSpace+m_dWid)+ptOri.y+m_dWid/3)*m_dScale+m_dWid/9*m_dScale, str);
				//显示注释
				str.Format("%s", noRt.strExplntn);	
				pDC->TextOut((j*(m_dColSpace+m_dLen)+ptOri.x)*m_dScale+m_dLen/20*m_dScale, (i*(m_dRowSpace+m_dWid)+ptOri.y+m_dWid/3*2)*m_dScale+m_dWid/9*m_dScale, str);
			}
			else
			{
				goto end;
			}
		}
	}
end:
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);
}

/*
*	函数名称：SubTractNoRect
*	函数功能：将成品矩形从每张Diagram中提取到lstRt中
*	返回值：void
*	参数说明：CList<CNoRect, CNoRect>& lstRt：将提取出来的成品矩形放入lstRt中
*/
void CTabDlg::SubTractNoRect(CList<CNoRect, CNoRect>& lstRt)
{
	//POSITION posDgm = m_dlg.m_PLGCDll.m_lstDgm.GetHeadPosition();
	CList<CRptDgm*, CRptDgm*>* pLstDgm = ((CRectOptDlg*)this->GetParent())->m_RtOptDll.GetDgmList();
	POSITION posDgm = pLstDgm->GetHeadPosition();
	CRptDgm *pDgm = NULL;
	while (posDgm != NULL) 
	{
		pDgm = pLstDgm->GetAt(posDgm);
		
		//////////////////////////////////////////////////////////////////////////
		int nCnt = pDgm->nCutTimes;
		for(int i=0; i<nCnt; i++)
		{
			POSITION posNoRt = pDgm->pRtLay->GetHeadPosition();
			CNoRect *pNoRt = NULL;
			while(posNoRt != NULL)
			{
				pNoRt = (CNoRect*)pDgm->pRtLay->GetAt(posNoRt);
				
				//TRACE("\nLen：%d Wid: %d 用户名：%s\n", pNoRt->rt.GetWidth(), pNoRt->rt.GetHeight(), pNoRt->strCustName);
				
				lstRt.AddTail((*pNoRt));
				
				pDgm->pRtLay->GetNext(posNoRt);
			}
		}
		//////////////////////////////////////////////////////////////////////////
		
		pLstDgm->GetNext(posDgm);
	}
}

/*
*	函数名称：statProdCount
*	函数功能：计算每种类别的成品矩形有多少个
*	返回值：成品矩形的类别数
*	参数说明：int* num：存放每种类别成品矩形的个数(索引为1的里面存的是mfcGriCtrl中序号为1的矩形)
CList<Diagram*, Diagram*>& lstDgm：动态库中所生成Diagram的链表
*/
int CTabDlg::statProdCount(int* num, CList<CRptDgm*, CRptDgm*>& lstDgm)
{
	CList<CNoRect*, CNoRect*> lstNoRt;
	POSITION posDgm = lstDgm.GetHeadPosition();
	CRptDgm *pDgm = NULL;
	while (posDgm != NULL) 
	{
		pDgm = (CRptDgm*)lstDgm.GetAt(posDgm);
		
		//////////////////////////////////////////////////////////////////////////
		int nCutTimes = pDgm->nCutTimes;
		for(int i=0; i<nCutTimes; i++)
		{
			lstNoRt.AddTail(pDgm->pRtLay);
		}
		//////////////////////////////////////////////////////////////////////////
		
		lstDgm.GetNext(posDgm);
	}
	memset(num, 0, sizeof(num));
	for(int i=0; i<lstNoRt.GetCount(); i++)
	{
		POSITION pos = lstNoRt.FindIndex(i);
		CNoRect *pNoRt = (CNoRect*)lstNoRt.GetAt(pos);
		num[pNoRt->nLocNo]++;
	}
	for(int nRet=1; nRet<1000; nRet++)
	{
		if (num[nRet] == 0) 
		{
			nRet--;
			break;
		}
	}
	return nRet;
}

//画Report中的缩略图
void CTabDlg::DrawThumbNail(CDC *pDC, CPoint ptThdGrd, int cnt, int nDgmIndex, CRectOptDlg *pRtOptDlg, CPrintInfo* pInfo)
{
	//设置字的对其方式为居中
	pDC->SetTextAlign(TA_CENTER);
	
	//画缩略图(表格之间的距离为1)
	int nThumbLen = m_szGrid.cx/2;		
	int nThumbWid = nThumbLen*4/3;
	
	//////////////////////////////////////////////////////////////////////////
	for(int j=0; j<2 && (j+nDgmIndex)<m_lDgmCnt; j++)
	{
		//数据结构中轨迹相同的图存储的是同一份，所以这里nDgmIndex需要进行转换
		int nDgmIdxRes = 0;
		int nDgmIdxNew = 0;
		CRptDgm *pIdxDgm = NULL;
		CList<CRptDgm*, CRptDgm*>* pLstDgm = pRtOptDlg->m_RtOptDll.GetDgmList();
		POSITION posIdxDgm = pLstDgm->GetHeadPosition();
		while (posIdxDgm != NULL) 
		{
			pIdxDgm = pLstDgm->GetAt(posIdxDgm);
			nDgmIdxNew += pIdxDgm->nCutTimes;
			if ((j+nDgmIndex) <= nDgmIdxNew-1) 
			{
				break;
			}
			else
			{
				nDgmIdxRes++;
			}
			pLstDgm->GetNext(posIdxDgm);
		}
	//////////////////////////////////////////////////////////////////////////
	
		CPoint ptThumb((j*nThumbLen)+ptThdGrd.x, (1+(cnt+1)/2)*m_nLineHeight+ptThdGrd.y);
		pDC->Rectangle((ptThumb.x)*m_dZoom, ptThumb.y*m_dZoom, \
			(nThumbLen+ptThumb.x)*m_dZoom, (nThumbWid+ptThumb.y)*m_dZoom);
		
		CPoint ptOri(4+ptThumb.x, ptThumb.y+nThumbWid/5);
		double g_dZoom = 1.0;//m_cxWidth*4.5/2;
		POSITION posDgm = pLstDgm->GetHeadPosition();
		CRptDgm *pDgm = NULL;
		while (posDgm != NULL) 
		{

			//////////////////////////////////////////////////////////////////////////
			pDgm = pLstDgm->GetAt(pLstDgm->FindIndex(nDgmIdxRes));
			//////////////////////////////////////////////////////////////////////////

			g_dZoom = pDgm->rtRaw.rt.Width()/(m_szGrid.cx/2)+2;
			
			double rate = pDgm->GetUtilization();

			//设置字的对其方式为左对齐
			pDC->SetTextAlign(TA_LEFT);

			//填写Diagram左上角信息
			CString str;
			CString strRtLen, strRtWid;
			strRtLen.Format("%.2f", pDgm->rtRaw.rt.Width());
			strRtWid.Format("%.2f", pDgm->rtRaw.rt.Height());

			//////////////////////////////////////////////////////////////////////////
			str.Format("%d# %.2f%%, %gx%g=%d($%d)", 1+j+nDgmIndex, /*pRtOptDlg->m_PLGCDll.GetUtilization()*/rate*100, \
				atof(strRtLen), atof(strRtWid), 1/*pRtOptDlg->m_PLGCDll.m_lstDgm.GetCount()*/, 1+j+nDgmIndex);
			//////////////////////////////////////////////////////////////////////////
			
			pDC->TextOut((1+ptThumb.x)*m_dZoom, (1+ptThumb.y)*m_dZoom, str);
			//画原片
			pDC->Rectangle(CRect((pDgm->rtRaw.rt.left/g_dZoom+ptOri.x)*m_dZoom, \
				(pDgm->rtRaw.rt.top/g_dZoom+ptOri.y)*m_dZoom, \
				(pDgm->rtRaw.rt.right/g_dZoom+ptOri.x)*m_dZoom, \
				(pDgm->rtRaw.rt.bottom/g_dZoom+ptOri.y)*m_dZoom)); 
			//画矩形
			CRptLine *pLine = NULL;
			POSITION posLnTrack = pDgm->pLnTrack->GetHeadPosition();
			while (posLnTrack != NULL) 
			{
				pLine = pDgm->pLnTrack->GetAt(posLnTrack);
				//计算点在图中的坐标
				CPoint ptPnt;
				ptPnt.x = (pLine->ptStart.x/g_dZoom+ptOri.x)*m_dZoom;
				ptPnt.y = (pLine->ptStart.y/g_dZoom+ptOri.y)*m_dZoom;
				pDC->MoveTo(ptPnt);
				ptPnt.x = (pLine->ptEnd.x/g_dZoom+ptOri.x)*m_dZoom;
				ptPnt.y = (pLine->ptEnd.y/g_dZoom+ptOri.y)*m_dZoom;
				pDC->LineTo(ptPnt);			
				
				pDgm->pLnTrack->GetNext(posLnTrack);
			}
			//设置字的对其方式为居中
			pDC->SetTextAlign(TA_CENTER);
			//给矩形内填数据
			CNoRect *pNoRect = NULL;
			POSITION posNoRect = pDgm->pRtLay->GetHeadPosition();
			while (posNoRect != NULL) 
			{
				pNoRect = pDgm->pRtLay->GetAt(posNoRect);
				
				//如果是异形，则绘制异形的图形信息
				if ( pNoRect->bShape == TRUE) 
				{
					if ( pNoRect->shape.bChanged != FALSE )
					{
						//旋转异形
						CString strRes = RotateSelect(0, 90, pNoRect->rt, pNoRect->shape.strShape);
						DrawShape(pDC, strRes, pNoRect->rt, ptOri, pDgm, g_dZoom);
					}
					else
					{
						//不进行旋转
						DrawShape(pDC, pNoRect->shape.strShape, pNoRect->rt, ptOri, pDgm, g_dZoom);
					}
				}
			
				//定位号
				CString strLocNo;
				strLocNo.Format("%d", pNoRect->nLocNo);
				pDC->TextOut(((pNoRect->rt.left+pNoRect->rt.Width()/2)/g_dZoom+ptOri.x)*m_dZoom, \
					((pNoRect->rt.top-pNoRect->rt.Height()*2/3)/g_dZoom+ptOri.y)*m_dZoom, strLocNo);
				CFont *pOldFont;
				CFont font;
				VERIFY(font.CreateFont(
					2.5*m_dZoom,           // nHeight
					0,                         // nWidth
					0,                         // nEscapement
					0,                         // nOrientation
					FW_NORMAL,                 // nWeight
					FALSE,                     // bItalic
					FALSE,                     // bUnderline
					0,                         // cStrikeOut
					ANSI_CHARSET,              // nCharSet
					OUT_DEFAULT_PRECIS,        // nOutPrecision
					CLIP_DEFAULT_PRECIS,       // nClipPrecision
					DEFAULT_QUALITY,           // nQuality
					DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
					_T("Arial")));             // lpszFacename
				pOldFont = pDC->SelectObject(&font);
				//长
				CString strLen;
				strLen.Format("%g", pNoRect->rt.Width());
				pDC->TextOut(((pNoRect->rt.left+pNoRect->rt.Width()/2)/g_dZoom+ptOri.x)*m_dZoom, \
					(pNoRect->rt.top/g_dZoom-2+ptOri.y)*m_dZoom, strLen);
				pDC->SelectObject(pOldFont);
				//宽
				CFont fontWid;
				VERIFY(fontWid.CreateFont(
					2.5*m_dZoom,           // nHeight
					0,                         // nWidth
					900,                       // nEscapement
					0,                         // nOrientation
					FW_NORMAL,                 // nWeight
					FALSE,                     // bItalic
					FALSE,                     // bUnderline
					0,                         // cStrikeOut
					ANSI_CHARSET,              // nCharSet
					OUT_DEFAULT_PRECIS,        // nOutPrecision
					CLIP_DEFAULT_PRECIS,       // nClipPrecision
					DEFAULT_QUALITY,           // nQuality
					DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
					_T("Arial")));             // lpszFacename
				pOldFont = pDC->SelectObject(&fontWid);
				CString strWid;
				strWid.Format("%g", pNoRect->rt.Height());
				pDC->TextOut((1+pNoRect->rt.left/g_dZoom+ptOri.x)*m_dZoom, \
					((pNoRect->rt.top-pNoRect->rt.Height()/10)/g_dZoom-3+ptOri.y)*m_dZoom, strWid);
				
				pDC->SelectObject(pOldFont);
				
				pDgm->pRtLay->GetNext(posNoRect);
			}
			//pLstDgm->GetNext(posDgm);
			break;
		}	
	}
}

//**********************画缩略图******************
void CTabDlg::DrawThumbNail(CDC *pDC, CPoint ptThdGrd, int nDgmIndex, CRectOptDlg *pRtOptDlg, CPrintInfo* pInfo)
{
	//画缩略图(表格之间的距离为1)
	int nThumbLen = m_szGrid.cx/2;		
	int nThumbWid = nThumbLen*4/3;
	CPen pen(PS_SOLID, 0.1*m_dZoom, RGB(0, 0, 0));
	CPen *pOldPen = pDC->SelectObject(&pen);
	CFont *pOldFont;
	pOldFont = pDC->SelectObject(&m_fntRepDigit);
	for(int i=0; i<2; i++)
	{
		//////////////////////////////////////////////////////////////////////////
		for(int j=0; j<2 && (i*2+j+nDgmIndex)<m_lDgmCnt; j++)
		{
			//数据结构中轨迹相同的图存储的是同一份，所以这里nDgmIndex需要进行转换
			int nDgmIdxRes = 0;
			int nDgmIdxNew = 0;
			CRptDgm *pIdxDgm = NULL;
			CList<CRptDgm*, CRptDgm*>* pLstDgm = pRtOptDlg->m_RtOptDll.GetDgmList();
			POSITION posIdxDgm = pLstDgm->GetHeadPosition();
			while (posIdxDgm != NULL) 
			{
				pIdxDgm = pLstDgm->GetAt(posIdxDgm);
				nDgmIdxNew += pIdxDgm->nCutTimes;
				if ((i*2+j+nDgmIndex) <= nDgmIdxNew-1) 
				{
					break;
				}
				else
				{
					nDgmIdxRes++;
				}
				pLstDgm->GetNext(posIdxDgm);
			}
		//////////////////////////////////////////////////////////////////////////
		
			CPoint ptThumb((j*nThumbLen)+ptThdGrd.x, i*nThumbWid+ptThdGrd.y);
			pDC->Rectangle((ptThumb.x)*m_dZoom, ptThumb.y*m_dZoom, \
				(nThumbLen+ptThumb.x)*m_dZoom, (nThumbWid+ptThumb.y)*m_dZoom);
			
			CPoint ptOri(4+ptThumb.x, ptThumb.y+nThumbWid/5);
			double g_dZoom = 1.0;//m_cxWidth*4.5/2;
			POSITION posDgm = pLstDgm->GetHeadPosition();
			CRptDgm *pDgm = NULL;
			while (posDgm != NULL) 
			{
				//////////////////////////////////////////////////////////////////////////
				pDgm = pLstDgm->GetAt(pLstDgm->FindIndex(/*i*2+j+*/nDgmIdxRes));
				//////////////////////////////////////////////////////////////////////////
				
				g_dZoom = pDgm->rtRaw.rt.Width()/(m_szGrid.cx/2)+2;
				double rate = pDgm->GetUtilization();

				//设置字的对其方式为左对齐
				pDC->SetTextAlign(TA_LEFT);
				
				//填写Diagram左上角信息
				CString str;
				CString strRtLen, strRtWid;
				strRtLen.Format("%.2f", pDgm->rtRaw.rt.Width());
				strRtWid.Format("%.2f", pDgm->rtRaw.rt.Height());

				//////////////////////////////////////////////////////////////////////////
				str.Format("%d# %.2f%%, %gx%g=%d($%d)", 1+i*2+j+nDgmIndex, /*pRtOptDlg->m_PLGCDll.GetUtilization()*/rate*100, \
					atof(strRtLen), atof(strRtWid), 1/*pRtOptDlg->m_PLGCDll.m_lstDgm.GetCount()*/, 1+i*2+j+nDgmIndex);
				//////////////////////////////////////////////////////////////////////////
				
				pDC->TextOut((1+ptThumb.x)*m_dZoom, (1+ptThumb.y)*m_dZoom, str);
				//画原片
				pDC->Rectangle(CRect((pDgm->rtRaw.rt.left/g_dZoom+ptOri.x)*m_dZoom, \
					(pDgm->rtRaw.rt.top/g_dZoom+ptOri.y)*m_dZoom, \
					(pDgm->rtRaw.rt.right/g_dZoom+ptOri.x)*m_dZoom, \
					(pDgm->rtRaw.rt.bottom/g_dZoom+ptOri.y)*m_dZoom)); 
				//画矩形
				CRptLine *pLine = NULL;
				POSITION posLnTrack = pDgm->pLnTrack->GetHeadPosition();
				while (posLnTrack != NULL) 
				{
					pLine = pDgm->pLnTrack->GetAt(posLnTrack);
					//计算点在图中的坐标
					CPoint ptPnt;
					ptPnt.x = (pLine->ptStart.x/g_dZoom+ptOri.x)*m_dZoom;
					ptPnt.y = (pLine->ptStart.y/g_dZoom+ptOri.y)*m_dZoom;
					pDC->MoveTo(ptPnt);
					ptPnt.x = (pLine->ptEnd.x/g_dZoom+ptOri.x)*m_dZoom;
					ptPnt.y = (pLine->ptEnd.y/g_dZoom+ptOri.y)*m_dZoom;
					pDC->LineTo(ptPnt);			
					
					pDgm->pLnTrack->GetNext(posLnTrack);
				}

				//设置字的对其方式为居中
				pDC->SetTextAlign(TA_CENTER);
				//给矩形内填数据
				CNoRect *pNoRect = NULL;
				POSITION posNoRect = pDgm->pRtLay->GetHeadPosition();
				while (posNoRect != NULL) 
				{
					pNoRect = pDgm->pRtLay->GetAt(posNoRect);

					//测试
					/*
					pDC->MoveTo( (pNoRect->rt.left/g_dZoom+ptOri.x)*m_dZoom, (pNoRect->rt.top/g_dZoom+ptOri.y)*m_dZoom );
					pDC->LineTo( (pNoRect->rt.right/g_dZoom+ptOri.x)*m_dZoom, (pNoRect->rt.bottom/g_dZoom+ptOri.y)*m_dZoom );
					*/

					//如果是异形，则绘制异形的图形信息
					if ( pNoRect->bShape == TRUE) 
					{
						if ( pNoRect->shape.bChanged != FALSE )
						{
							//旋转异形
							CString strRes = RotateSelect(0, 90, pNoRect->rt, pNoRect->shape.strShape);
							DrawShape(pDC, strRes, pNoRect->rt, ptOri, pDgm, g_dZoom);
						}
						else
						{
							//不进行旋转
							DrawShape(pDC, pNoRect->shape.strShape, pNoRect->rt, ptOri, pDgm, g_dZoom);
						}
					}

					//定位号
					CString strLocNo;
					strLocNo.Format("%d", pNoRect->nLocNo);
					pDC->TextOut(((pNoRect->rt.left+pNoRect->rt.Width()/2)/g_dZoom+ptOri.x)*m_dZoom, \
						((pNoRect->rt.top-pNoRect->rt.Height()*2/3)/g_dZoom+ptOri.y)*m_dZoom, strLocNo);
					CFont *pOldFont;
					CFont font;
					VERIFY(font.CreateFont(
						2.5*m_dZoom,				// nHeight
						0,                         // nWidth
						0,                         // nEscapement
						0,                         // nOrientation
						FW_NORMAL,                 // nWeight
						FALSE,                     // bItalic
						FALSE,                     // bUnderline
						0,                         // cStrikeOut
						ANSI_CHARSET,              // nCharSet
						OUT_DEFAULT_PRECIS,        // nOutPrecision
						CLIP_DEFAULT_PRECIS,       // nClipPrecision
						DEFAULT_QUALITY,           // nQuality
						DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
						_T("Arial")));             // lpszFacename
					pOldFont = pDC->SelectObject(&font);
					//长
					CString strLen;
					strLen.Format("%g", pNoRect->rt.Width());
					pDC->TextOut(((pNoRect->rt.left+pNoRect->rt.Width()/2)/g_dZoom+ptOri.x)*m_dZoom, \
						(pNoRect->rt.top/g_dZoom-2+ptOri.y)*m_dZoom, strLen);
					pDC->SelectObject(pOldFont);
					//宽
					CFont fontWid;
					VERIFY(fontWid.CreateFont(
						2.5*m_dZoom,           // nHeight
						0,                         // nWidth
						900,                       // nEscapement
						0,                         // nOrientation
						FW_NORMAL,                 // nWeight
						FALSE,                     // bItalic
						FALSE,                     // bUnderline
						0,                         // cStrikeOut
						ANSI_CHARSET,              // nCharSet
						OUT_DEFAULT_PRECIS,        // nOutPrecision
						CLIP_DEFAULT_PRECIS,       // nClipPrecision
						DEFAULT_QUALITY,           // nQuality
						DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
						_T("Arial")));             // lpszFacename
					pOldFont = pDC->SelectObject(&fontWid);
					CString strWid;
					strWid.Format("%g", pNoRect->rt.Height());
					pDC->TextOut((1+pNoRect->rt.left/g_dZoom+ptOri.x)*m_dZoom, \
						((pNoRect->rt.top-pNoRect->rt.Height()/10)/g_dZoom-3+ptOri.y)*m_dZoom, strWid);
					
					pDC->SelectObject(pOldFont);
					
					pDgm->pRtLay->GetNext(posNoRect);
				}
				//pLstDgm->GetNext(posDgm);
				break;
			}	
		}		
	}
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);
}

void CTabDlg::OnA4() 
{
	//选中A4
	((CButton*)GetDlgItem(IDC_A4))->SetCheck(BST_CHECKED);
	//显示需要的控件
	((CStatic*)GetDlgItem(IDC_STATIC_VERSP))->ShowWindow(TRUE);
	((CStatic*)GetDlgItem(IDC_STATIC_HORSP))->ShowWindow(TRUE);
	((CStatic*)GetDlgItem(IDC_SP_LEFT))->ShowWindow(TRUE);
	((CStatic*)GetDlgItem(IDC_SP_TOP))->ShowWindow(TRUE);
	((CStatic*)GetDlgItem(IDC_STATIC_ROW))->ShowWindow(TRUE);
	((CStatic*)GetDlgItem(IDC_STATIC_COL))->ShowWindow(TRUE);
	
	((CEdit*)GetDlgItem(IDC_ROWSPACE))->ShowWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_COLSPACE))->ShowWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_MARIN_L))->ShowWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_MARIN_T))->ShowWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_ROW))->ShowWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_ROW))->SetReadOnly(FALSE);
	((CEdit*)GetDlgItem(IDC_COL))->ShowWindow(TRUE);

	//隐藏右边距和下边距的Edit框
	((CStatic*)GetDlgItem(IDC_SP_RIGHT))->ShowWindow(FALSE);
	((CStatic*)GetDlgItem(IDC_SP_BOTTOM))->ShowWindow(FALSE);
	((CStatic*)GetDlgItem(IDC_STATIC_TABHORSP))->ShowWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_MARIN_R))->ShowWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_MARIN_B))->ShowWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_TABCOLSPACE))->ShowWindow(FALSE);

	//给标签设置默认值
//	SetDlgItemText(IDC_LEN, _T("50"));
	//	SetDlgItemText(IDC_WID, _T("31"));
	//	SetDlgItemText(IDC_ROW, _T("8"));
	//	SetDlgItemText(IDC_COL, _T("4"));
	//	SetDlgItemText(IDC_ROWSPACE, _T("2"));
	//	SetDlgItemText(IDC_COLSPACE, _T("2"));
	//	SetDlgItemText(IDC_MARIN_L, _T("2"));
	//	//SetDlgItemText(IDC_MARIN_R, _T("2"));
	//	SetDlgItemText(IDC_MARIN_T, _T("2"));
	//	SetDlgItemText(IDC_FONT, _T("140"));
	

	CString l_strKeyName;	//保存用的中间数据一个是数据，一个是键名
	char l_chDataName[20];
	memset(l_chDataName,0,sizeof(l_chDataName));
	for(int i=14022;i<14033;i++)
	{
		l_strKeyName.Format("m_dKeyName[%d]",i);
		GetPrivateProfileString("TabPramA4",l_strKeyName,"-1",l_chDataName,20,	\
			"D:\\Program Files\\GlassCutter\\TabPram.ini");
		SetDlgItemText(i,l_chDataName);
	}
}

void CTabDlg::OnTab() 
{
	//选中标签纸
	((CButton*)GetDlgItem(IDC_RADIO_TAB))->SetCheck(BST_CHECKED);
	//隐藏不需要的控件
	/*
	((CStatic*)GetDlgItem(IDC_STATIC_VERSP))->ShowWindow(FALSE);
	((CStatic*)GetDlgItem(IDC_STATIC_HORSP))->ShowWindow(FALSE);
	((CStatic*)GetDlgItem(IDC_SP_LEFT))->ShowWindow(FALSE);
	((CStatic*)GetDlgItem(IDC_SP_TOP))->ShowWindow(FALSE);
	((CStatic*)GetDlgItem(IDC_STATIC_ROW))->ShowWindow(FALSE);
	((CStatic*)GetDlgItem(IDC_STATIC_COL))->ShowWindow(FALSE);

	((CEdit*)GetDlgItem(IDC_ROWSPACE))->ShowWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_COLSPACE))->ShowWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_MARIN_L))->ShowWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_MARIN_T))->ShowWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_ROW))->ShowWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_COL))->ShowWindow(FALSE);
	*/
	((CStatic*)GetDlgItem(IDC_STATIC_VERSP))->ShowWindow(FALSE);
	((CStatic*)GetDlgItem(IDC_STATIC_HORSP))->ShowWindow(FALSE);
	//((CStatic*)GetDlgItem(IDC_STATIC_ROW))->ShowWindow(FALSE);
	//((CStatic*)GetDlgItem(IDC_STATIC_COL))->ShowWindow(FALSE);

	//((CEdit*)GetDlgItem(IDC_ROW))->ShowWindow(FALSE);
	//((CEdit*)GetDlgItem(IDC_COL))->ShowWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_ROW))->SetReadOnly(TRUE);
	((CEdit*)GetDlgItem(IDC_ROWSPACE))->ShowWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_COLSPACE))->ShowWindow(FALSE);

	//显示右边距和下边距的Edit框
	((CStatic*)GetDlgItem(IDC_SP_RIGHT))->ShowWindow(TRUE);
	((CStatic*)GetDlgItem(IDC_SP_BOTTOM))->ShowWindow(TRUE);
	((CStatic*)GetDlgItem(IDC_STATIC_TABHORSP))->ShowWindow(TRUE);
	
	((CEdit*)GetDlgItem(IDC_MARIN_R))->ShowWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_MARIN_B))->ShowWindow(TRUE);
	((CEdit*)GetDlgItem(IDC_TABCOLSPACE))->ShowWindow(TRUE);

//	//给标签设置默认值
//	SetDlgItemText(IDC_LEN, _T("60"));
//	SetDlgItemText(IDC_WID, _T("40"));
//	SetDlgItemText(IDC_FONT, _T("40"));
//	SetDlgItemText(IDC_MARIN_L, _T("2"));
//	SetDlgItemText(IDC_MARIN_T, _T("2"));
//	SetDlgItemText(IDC_MARIN_R, _T("2"));
//	SetDlgItemText(IDC_MARIN_B, _T("2"));
//	SetDlgItemText(IDC_ROW, _T("1"));
//	SetDlgItemText(IDC_COL, _T("1"));
//	SetDlgItemText(IDC_MARIN_B, _T("2"));
//	SetDlgItemText(IDC_TABCOLSPACE, _T("2"));

	CString l_strKeyName;	//保存用的中间数据一个是数据，一个是键名
	char l_chDataName[20];
	memset(l_chDataName,0,sizeof(l_chDataName));
	for(int i=14022;i<14034;i++)
	{
		l_strKeyName.Format("m_dKeyName[%d]",i);
		GetPrivateProfileString("TabPramRoll",l_strKeyName,"-1",l_chDataName,20,	\
			"D:\\Program Files\\GlassCutter\\TabPram.ini");
		SetDlgItemText(i,l_chDataName);
	}
}

//在标签纸上画标签
void CTabDlg::DrawTab(CDC *pDC, int nStart, CList<CNoRect, CNoRect>& lstRt)
{
	CFont *pOldFont;
	pOldFont = pDC->SelectObject(&m_fntContent);
	CPen pen(PS_SOLID, 0.4*m_dRatio, RGB(0, 0, 0));
	CPen *pOldPen = pDC->SelectObject(&pen);
	//设置标签在标签纸上的起点
	CPoint ptOri(0, 0);
	//绘制标签
	ptOri.x += m_dMarinL;
	ptOri.y += m_dMarinT;
	//获取列间距
	CString strHorSep;
	((CWnd*)GetDlgItem(IDC_TABCOLSPACE))->GetWindowText(strHorSep);
	int nHorSep = atoi(strHorSep);
	
	CString str;
	for(int i=0; i<m_nCol && nStart+i<lstRt.GetCount(); i++)	//(i*2+j+nDgmIndex)<m_lDgmCnt
	{
		POSITION posNoRt = lstRt.FindIndex(nStart+i);
		CNoRect  noRt = lstRt.GetAt(posNoRt);
		TRACE("Tab:%d x %d", noRt.rt.Width(), noRt.rt.Height());
		
		//pDC->Rectangle(((m_nLen+nHorSep)*i+0)*m_dRatio, 0*m_dRatio, (m_nLen+(m_nLen+nHorSep)*i+0)*m_dRatio, (m_nWid+0)*m_dRatio);
		
		if(posNoRt != NULL) 
		{
			pDC->Rectangle((m_dLen+nHorSep)*i*m_dRatio+ptOri.x*m_dRatio, ptOri.y*m_dRatio, 	\
				(m_dLen-m_dMarinL-m_dMarinR+(m_dLen+nHorSep)*i)*m_dRatio+ptOri.x*m_dRatio, (m_dWid-m_dMarinT-m_dMarinB+ptOri.y)*m_dRatio);
			pDC->MoveTo(((m_dLen+nHorSep)*i+ptOri.x+(m_dLen-m_dMarinL-m_dMarinR)/2)*m_dRatio, ptOri.y*m_dRatio);
			pDC->LineTo(((m_dLen+nHorSep)*i+ptOri.x+(m_dLen-m_dMarinL-m_dMarinR)/2)*m_dRatio, (ptOri.y+(m_dWid-m_dMarinT-m_dMarinB)/3.0)*m_dRatio);
			pDC->MoveTo((m_dLen+nHorSep)*i*m_dRatio+ptOri.x*m_dRatio, (ptOri.y+(m_dWid-m_dMarinT-m_dMarinB)/3.0)*m_dRatio);
			pDC->LineTo((m_dLen-m_dMarinL-m_dMarinR+(m_dLen+nHorSep)*i)*m_dRatio+ptOri.x*m_dRatio, (ptOri.y+(m_dWid-m_dMarinT-m_dMarinB)/3.0)*m_dRatio);
			pDC->MoveTo((m_dLen+nHorSep)*i*m_dRatio+ptOri.x*m_dRatio, (ptOri.y+(m_dWid-m_dMarinT-m_dMarinB)/3.0*2)*m_dRatio);
			pDC->LineTo((m_dLen-m_dMarinL-m_dMarinR+(m_dLen+nHorSep)*i)*m_dRatio+ptOri.x*m_dRatio, (ptOri.y+(m_dWid-m_dMarinT-m_dMarinB)/3.0*2)*m_dRatio);
			//显示用户名
			str.Format("%s", noRt.strCustName);
			TRACE("\n用户名：%s\n", noRt.strCustName);
			pDC->TextOut((m_dLen-m_dMarinL-m_dMarinR)/30*m_dRatio+m_dMarinL+(m_dLen+nHorSep)*i*m_dRatio+ptOri.x*m_dRatio, ptOri.y*m_dRatio+(m_dWid-m_dMarinT-m_dMarinB)/10*m_dRatio, str);
			//显示订单号
			str.Format("%s", noRt.strOrderNo);
			pDC->TextOut(((m_dLen-m_dMarinL-m_dMarinR)/30+(m_dLen-m_dMarinL-m_dMarinR)/2+m_dMarinL+(m_dLen+nHorSep)*i+ptOri.x)*m_dRatio, ptOri.y*m_dRatio+(m_dWid-m_dMarinT-m_dMarinB)/10*m_dRatio, str);
			//显示矩形尺寸
			CString strRtLen, strRtWid;
			strRtLen.Format("%.2f", noRt.rt.Width()>=noRt.rt.Height()? noRt.rt.Width():noRt.rt.Height());
			strRtWid.Format("%.2f", noRt.rt.Width()<noRt.rt.Height()? noRt.rt.Width():noRt.rt.Height());
			str.Format("%g x %g", atof(strRtLen), atof(strRtWid));
			pDC->TextOut(((m_dLen-m_dMarinL-m_dMarinR)/8.0+m_dMarinL+(m_dLen+nHorSep)*i+ptOri.x)*m_dRatio, (ptOri.y+(double)(m_dWid-m_dMarinT-m_dMarinB)/3.0)*m_dRatio+m_dWid/10*m_dRatio, str);
			//显示注释
			str.Format("%s", noRt.strExplntn);	
			pDC->TextOut(((m_dLen-m_dMarinL-m_dMarinR)/8.0+m_dMarinL+(m_dLen+nHorSep)*i+ptOri.x)*m_dRatio, (ptOri.y+(double)(m_dWid-m_dMarinT-m_dMarinB)/3.0*2)*m_dRatio+m_dWid/10*m_dRatio, str);	
		}
	}
	
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);
}


//dAddOffSetX和dAddOffSetY为X方向和Y方向的修边
void CTabDlg::DrawShape(CDC *pDC, CString strCmd, CRptRect rt, CPoint ptOri, CRptDgm *pDgm, double g_dZoom)
{
	CPen pensel[3];
	pensel[0].CreatePen(PS_DOT,1,RGB(0,255,0));
	pensel[1].CreatePen(PS_SOLID,2,RGB(0,0,128));
	pensel[2].CreatePen(PS_SOLID,2,RGB(255,0,0));

	CStdioFile paraf;
	CString strPath,sqr1,pdcstr;

	int nPos;		
	pDC->SelectObject(&pensel[1]);
	
	double dOffsetX, dOffsetY;
	dOffsetX = rt.left;	
	dOffsetY = rt.top;	

	nPos = strCmd.FindOneOf(";");
	strCmd = strCmd.Mid(nPos+1);
	nPos = strCmd.FindOneOf(";");
	while( nPos != -1)
	{
		CString pdcpoint;
		pdcstr = strCmd.Left(nPos);
		strCmd = strCmd.Mid(nPos+1);
		nPos = strCmd.FindOneOf(";");
		if(pdcstr.GetAt(0)=='0')
		{
			pdcpoint = pdcstr.Mid(1);
			int nPos;
			double pointx,pointy;
			nPos = pdcpoint.FindOneOf(",");
			pointx = atof(pdcpoint.Left(nPos));
			pointy = atof(pdcpoint.Mid(nPos+1));
			CPen *OldPen = pDC->SelectObject(&pensel[0]);
			
			pDC->LineTo( ((dOffsetX+pointx)/g_dZoom+ptOri.x)*m_dZoom, ((dOffsetY-pointy)/g_dZoom+ptOri.y)*m_dZoom );
			pDC->SelectObject(OldPen);
		}
		if(pdcstr.GetAt(0)=='1')
		{
			pdcpoint = pdcstr.Mid(1);
			int nPos;
			double pointx,pointy;
			nPos = pdcpoint.FindOneOf(",");
			pointx = atof(pdcpoint.Left(nPos));
			pointy = atof(pdcpoint.Mid(nPos+1));
			pDC->LineTo( ((dOffsetX+pointx)/g_dZoom+ptOri.x)*m_dZoom, ((dOffsetY-pointy)/g_dZoom+ptOri.y)*m_dZoom );
		}
		if(pdcstr.GetAt(0)=='2')
		{
			pdcpoint = pdcstr.Mid(1); 
			int nPos;
			double pointx,pointy,pointR,pointQ,pointD;
			nPos = pdcpoint.FindOneOf(",");
			pointx = atof(pdcpoint.Left(nPos));
			pdcpoint = pdcpoint.Mid(nPos+1);
			nPos = pdcpoint.FindOneOf(",");
			pointy = atof(pdcpoint.Left(nPos));
			pdcpoint = pdcpoint.Mid(nPos+1);
			nPos = pdcpoint.FindOneOf(",");
			pointR = atof(pdcpoint.Left(nPos));
			pdcpoint = pdcpoint.Mid(nPos+1);
			nPos = pdcpoint.FindOneOf(",");
			pointQ = atof(pdcpoint.Left(nPos));
			pointD = atof(pdcpoint.Mid(nPos+1));
			pDC->AngleArc( ((dOffsetX+pointx)/g_dZoom+ptOri.x)*m_dZoom, 
				((dOffsetY-pointy)/g_dZoom+ptOri.y)*m_dZoom, (int)(pointR/g_dZoom*m_dZoom),(float)pointQ,(float)pointD);
		}
	}
	
	pDC->SelectObject(&pensel[1]);

	pensel[0].DeleteObject();
	pensel[1].DeleteObject();
	pensel[2].DeleteObject();
}

//新添加函数
CString CTabDlg::RotateSelect(double fBeginAngle, double fRotateAngel, CRptRect rt, CString strCmd)		//旋转异形
{
	int nPos;
	CString strLine;		//单个命令
	CString strResult = "";		//运算结果
	CString strLineResult = "";	

	CRptPoint ptCenter;
	//ptCenter.x = rt.left + rt.GetWidth() / 2;
	//ptCenter.y = rt.top - rt.GetHeight() / 2;
	
	ptCenter.x = rt.Height()/2;
	ptCenter.y = rt.Width()/2;

	double dAccX = (rt.Height()-rt.Width()) / 2;
	double dAccY = (rt.Width()-rt.Height()) / 2;

	nPos = strCmd.FindOneOf(";");
	strLine = strCmd.Left(nPos);
	strCmd = strCmd.Mid(nPos+1);
	
	strResult += strLine+";";
	
	double fDeltaAngle = 90;//fRotateAngel - fBeginAngle;
	while(nPos != -1)
	{
		nPos = strCmd.FindOneOf(";");
		strLine = strCmd.Left(nPos);
		strCmd = strCmd.Mid(nPos+1);
		if(strLine.GetAt(0)=='0')
		{
			strLine = strLine.Mid(1);
			int point;
			double pointx,pointy,pointx01,pointy01;
			point = strLine.FindOneOf(",");
			pointx = atof(strLine.Left(point));
			pointy = atof(strLine.Mid(point+1));
			double fDeltaX, fDeltaY;
			fDeltaY = pointy - ptCenter.y;
			fDeltaX = pointx - ptCenter.x;
			if( fDeltaX == 0)
			{
				if( fDeltaY > 0)
					fBeginAngle = 90.0;
				else
					fBeginAngle = 270.0;
			}
			else if( fDeltaX < 0)
			{
				fBeginAngle = atan(fDeltaY*1.0/fDeltaX)*180.0/PI + 180.0;
			}
			else
			{
				fBeginAngle = atan(fDeltaY*1.0/fDeltaX)*180.0/PI;
			}
			fRotateAngel = fBeginAngle + fDeltaAngle;
			double fLenth;
			fLenth = sqrt((pointx-ptCenter.x)*(pointx-ptCenter.x)+(pointy-ptCenter.y)*(pointy-ptCenter.y));
			
			pointx01 = fLenth*cos(fRotateAngel*PI/180)-fLenth*cos(fBeginAngle*PI/180) - dAccX;
			pointy01 = fLenth*sin(fRotateAngel*PI/180)-fLenth*sin(fBeginAngle*PI/180) - dAccY;			
			strLineResult.Format("0 %f,%f",pointx01+pointx,pointy01+pointy);

			strResult += strLineResult;
		}
		if(strLine.GetAt(0)=='1')
		{
			strLine = strLine.Mid(1);
			int point;
			double pointx,pointy,pointx01,pointy01;
			point = strLine.FindOneOf(",");
			pointx = atof(strLine.Left(point));
			pointy = atof(strLine.Mid(point+1));
						
			double fDeltaX, fDeltaY;
			fDeltaY = pointy - ptCenter.y;
			fDeltaX = pointx - ptCenter.x;
			if( fDeltaX == 0)
			{
				if( fDeltaY > 0)
					fBeginAngle = 90.0;
				else
					fBeginAngle = 270.0;
			}
			else if( fDeltaX < 0)
			{
				fBeginAngle = atan(fDeltaY*1.0/fDeltaX)*180.0/PI + 180.0;
			}
			else
			{
				fBeginAngle = atan(fDeltaY*1.0/fDeltaX)*180.0/PI;
			}
			fRotateAngel = fBeginAngle + fDeltaAngle;

			double fLenth;
			fLenth = sqrt((pointx-ptCenter.x)*(pointx-ptCenter.x)+(pointy-ptCenter.y)*(pointy-ptCenter.y));
			pointx01 = fLenth*cos(fRotateAngel*PI/180)-fLenth*cos(fBeginAngle*PI/180) - dAccX;
			pointy01 = fLenth*sin(fRotateAngel*PI/180)-fLenth*sin(fBeginAngle*PI/180) - dAccY;				
			strLineResult.Format("1 %f,%f",pointx01+pointx,pointy01+pointy);
			
			strResult += strLineResult;
		}
		if(strLine.GetAt(0)=='2')
		{
			strLine = strLine.Mid(1);
			int point;
			double pointx,pointy,pointR,pointQ,pointD,pointx01,pointy01;
			point = strLine.FindOneOf(",");
			pointx = atof(strLine.Left(point));
			strLine = strLine.Mid(point+1);
			point = strLine.FindOneOf(",");
			pointy = atof(strLine.Left(point));
			strLine = strLine.Mid(point+1);
			point = strLine.FindOneOf(",");
			pointR = atof(strLine.Left(point));
			strLine = strLine.Mid(point+1);
			point = strLine.FindOneOf(",");
			pointQ = atof(strLine.Left(point));
			pointD = atof(strLine.Mid(point+1));

			double fDeltaX, fDeltaY;
			fDeltaY = pointy - ptCenter.y;
			fDeltaX = pointx - ptCenter.x;
			if( fDeltaX == 0)
			{
				if( fDeltaY > 0)
					fBeginAngle = 90.0;
				else
					fBeginAngle = 270.0;
			}
			else if( fDeltaX < 0)
			{
				fBeginAngle = atan(fDeltaY*1.0/fDeltaX)*180.0/PI + 180.0;
			}
			else
			{
				fBeginAngle = atan(fDeltaY*1.0/fDeltaX)*180.0/PI;
			}
			fRotateAngel = fBeginAngle + fDeltaAngle;

			double fLenth;
			fLenth = sqrt((pointx-ptCenter.x)*(pointx-ptCenter.x)+(pointy-ptCenter.y)*(pointy-ptCenter.y));
			pointx01 = fLenth*cos(fRotateAngel*PI/180)-fLenth*cos(fBeginAngle*PI/180) - dAccX;
			pointy01 = fLenth*sin(fRotateAngel*PI/180)-fLenth*sin(fBeginAngle*PI/180) - dAccY;		
			
			strLineResult.Format("2 %f,%f,%f,%f,%f",pointx01+pointx,pointy01+pointy,pointR,pointQ+fDeltaAngle,pointD);
			
			strResult += strLineResult;
		}
		if( strstr(strLine,"@") != NULL )
		{
			nPos = strLine.FindOneOf("@");
			strLineResult = strLine.Mid(nPos);
			strResult += strLineResult;
		}
		strResult += ";";
		nPos = strCmd.FindOneOf(";");
	}
	
//	MessageBox(strResult);
	return strResult;
}


void CTabDlg::OnParamSave() 
{
	// TODO: Add your control notification handler code here
	CString l_strDataName,l_strKeyName;	 //保存用的中间数据一个是数据，一个是键名
	if (m_btnA4.GetCheck() == TRUE)
	{
		for(int i=14022;i<14034;i++)
		{
			l_strKeyName.Format("m_dKeyName[%d]",i);
			GetDlgItemText(i,l_strDataName);
			WritePrivateProfileString("TabPramA4",l_strKeyName,l_strDataName,	\
				"D:\\Program Files\\GlassCutter\\TabPram.ini");
		}
	}
	else
	{
		for(int i=14022;i<14034;i++)
		{
			l_strKeyName.Format("m_dKeyName[%d]",i);
			GetDlgItemText(i,l_strDataName);
			WritePrivateProfileString("TabPramRoll",l_strKeyName,l_strDataName,	\
				"D:\\Program Files\\GlassCutter\\TabPram.ini");
		}
	}
	
}

void CTabDlg::OnLanguage()
{
	if (g_iLanguage == 1)
	{
		SetDlgItemText(IDC_CAPTIONINFOCTRL1,"Label Print");
		SetDlgItemText(IDC_TAB_PARAM,"Param");
		SetDlgItemText(IDC_A4,"A4");
		SetDlgItemText(IDC_RADIO_TAB,"Continue");
		SetDlgItemText(IDC_STATIC_LEN,"Lenght");
		SetDlgItemText(IDC_STATIC_WID,"Width");
		SetDlgItemText(IDC_STATIC_FONT,"Font");
		SetDlgItemText(IDC_SP_LEFT,"Left");
		SetDlgItemText(IDC_SP_TOP,"Top");
		SetDlgItemText(IDC_STATIC_VERSP,"VerSp");
		SetDlgItemText(IDC_STATIC_HORSP,"HorSp");
		SetDlgItemText(IDC_STATIC_ROW,"Row");
		SetDlgItemText(IDC_STATIC_COL,"Col");
		SetDlgItemText(IDC_STATIC_TABHORSP,"HorSp");
		SetDlgItemText(IDC_SP_RIGHT,"Right");
		SetDlgItemText(IDC_SP_BOTTOM,"Bottom");
        SetDlgItemText(IDC_STATIC_REP_PNT,"Report");
		SetDlgItemText(IDC_REP_PNT,"Report");
		SetDlgItemText(IDC_REP_PREVIEW,"PreView");
		SetDlgItemText(IDC_STATIC_TAB_PREVIEW,"Label Preview");
		SetDlgItemText(IDC_PARAM_SAVE,"Save");
		SetDlgItemText(IDC_BTN_DISPLAY,"Display");
		SetDlgItemText(IDC_TAB_PREVIEW,"PreView");
		SetDlgItemText(IDC_TAB_PNT,"Print");
		SetDlgItemText(IDC_EXIT,"Exit");
	}
}