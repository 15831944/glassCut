// RectOptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "RectOptDlg.h"
#include "GraphDlg.h"/* ͼ����� */
#include "dlg_save.h"
#include <assert.h>
#include "PrintFrame.h"
#include "TabDlg.h"
#include "IOExcel.h"
#include "Dlg_KeyNumber.h"
#include "Dlg_KeyChar.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//ԭƬ��Ϣini�ļ�
#define INIFILE_OPTIMA           "D:\\program files\\GlassCutter\\Optima.ini"

/////////////////////////////////////////////////////////////////////////////
// CRectOptDlg dialog


CRectOptDlg::CRectOptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRectOptDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRectOptDlg)
	//}}AFX_DATA_INIT
	p_FirstRectInf = NULL;
	p_CurrentRectInf = NULL;
	m_nIndexCurrDgm = 0;
	m_rtDisplay = CRect(0,0,0,0);
	m_bkBrush.CreateSolidBrush(RGB(203, 211, 237));
}

CRectOptDlg::~CRectOptDlg()
{
	//DeleRectInf();
	if (m_bkBrush.GetSafeHandle())
	{
		m_bkBrush.DeleteObject();
	}
	DeleAllRectInf();
}

void CRectOptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRectOptDlg)
	DDX_Control(pDX, IDC_EDIT8, m_DEdit8);
	DDX_Control(pDX, IDC_EDIT7, m_DEdit7);
	DDX_Control(pDX, IDC_EDIT6, m_DEdit6);
	DDX_Control(pDX, IDC_EDIT5, m_DEdit5);
	DDX_Control(pDX, IDC_EDIT4, m_DEdit4);
	DDX_Control(pDX, IDC_EDIT3, m_DEdit3);
	DDX_Control(pDX, IDC_EDIT2, m_DEdit2);
	DDX_Control(pDX, IDC_EDIT12, m_DEdit12);
	DDX_Control(pDX, IDC_EDIT11, m_DEdit11);
	DDX_Control(pDX, IDC_EDIT10, m_DEdit10);
	DDX_Control(pDX, IDC_EDIT1, m_DEdit1);
	DDX_Control(pDX, IDC_BTN_EXCEL, m_ClrBtnExcel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRectOptDlg, CDialog)
	//{{AFX_MSG_MAP(CRectOptDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_F1, OnButtonF1)
	ON_BN_CLICKED(IDC_BUTTON_F2, OnButtonF2)
	ON_BN_CLICKED(IDC_BUTTON_F3, OnButtonF3)
	ON_BN_CLICKED(IDC_BUTTON_F4, OnButtonF4)
	ON_BN_CLICKED(IDC_BUTTON_F5, OnButtonF5)
	ON_BN_CLICKED(IDC_BUTTON_F6, OnBtnDisplay)
	ON_BN_CLICKED(IDC_BUTTON_F7, OnBtnNext)
	ON_BN_CLICKED(IDC_BUTTON_F8, OnBtnPrev)
	ON_BN_CLICKED(IDC_BUTTON_F9, OnBtnGrap)
	ON_BN_CLICKED(IDC_BUTTON_F10,OnBtnSend)
	ON_EN_CHANGE(IDC_EDIT10, OnChangeEdit10)
	ON_BN_CLICKED(IDC_BTN_EXCEL, OnBtnExcel)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRectOptDlg message handlers

BOOL CRectOptDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// �������弰Ĭ����Ϣ
	((CStatic *)GetDlgItem(IDC_STATIC_NO))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_STATIC_COUNT))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_STATIC_LIGHT))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_STATIC_HEIGHT))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_STATIC_SAFE))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_STATIC_UTILITY))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_TRIM_LEFT))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_TRIM_TOP))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_TRIM_RIGHT))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_TRIM_BOTTOM))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_MIN_EDGE))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_GRIND))->SetFont(&g_fontStatic);
	((CStatic *)GetDlgItem(IDC_PROJECT))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_EDIT1))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_EDIT2))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_EDIT3))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_EDIT4))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_EDIT5))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_EDIT6))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_EDIT7))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_EDIT8))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_EDIT9))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_EDIT10))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_EDIT11))->SetFont(&g_fontEdit);
	((CStatic *)GetDlgItem(IDC_EDIT12))->SetFont(&g_fontEdit);
	((CButton *)GetDlgItem(IDC_BTN_EXCEL))->SetFont(&g_fontEdit);	
	InitSheetPar();
	//��ʼ���ؼ�
	InitButton();
	AddNewRectInf();    
	OnInitGrid();	
	AddGrid();
	OnLanguage();
	SetWindowPos(&CWnd::wndTop,0,0,1024,768,SWP_SHOWWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRectOptDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CDC DCMenu;
	CRect rcBounds;
	GetClientRect(rcBounds);
	CPen penG01,*pOldPen;
	penG01.CreatePen(PS_SOLID,2,RGB(79,167,214));//RGB(0,200,0)
	
	CBitmap bitmap;
	DCMenu.CreateCompatibleDC(&dc);
    bitmap.LoadBitmap(IDB_BITMAP_BLACK);//717*464
	CBitmap *oldBit = DCMenu.SelectObject(&bitmap);	
	pOldPen = DCMenu.SelectObject(&penG01);
	DCMenu.SetBkMode(TRANSPARENT);
	CString strLen, strWid;
	GetDlgItemText(IDC_EDIT1, strLen);
	GetDlgItemText(IDC_EDIT2, strWid);
	m_dScale = atof(strLen)/fabs(m_rtDisplay.Width()) > atof(strWid)/fabs(m_rtDisplay.Height())? \
		atof(strLen)/fabs(m_rtDisplay.Width()) : atof(strWid)/fabs(m_rtDisplay.Height());
	//ԭƬ�ߴ�
	CPoint  cOrigin(4,50);
    DrawRect(&DCMenu,0,0,atoi(strLen),atoi(strWid),0);
	//DrawRectEdit(&DCMenu);
	m_rtDisplay = CRect(cOrigin.x,cOrigin.y,cOrigin.x+717,cOrigin.y+464);
	dc.BitBlt(cOrigin.x,cOrigin.y,rcBounds.Width(),rcBounds.Height(),&DCMenu,0,0,SRCCOPY);
	DCMenu.SelectObject(oldBit);
	DCMenu.SelectObject(pOldPen);
	penG01.DeleteObject();
	DeleteObject(DCMenu);
}

/*
 *	�������ƣ�DrawRect
 *  �������ܣ��������кõľ���
 *	����ֵ  ��void
 *	����˵����CDC *pDCMenu�����ƾ��ε�ָ�룬����������δʹ��
 */
void CRectOptDlg::DrawRect(CDC* pDCMenu,int ox,int oy,int x,int y,int nFill)
{	
	//�����ֵĶ��䷽ʽΪ����
	pDCMenu->SetTextAlign(TA_CENTER);
	CList<CRptDgm*,  CRptDgm*>* pLstDgm = m_RtOptDll.GetDgmList();
	POSITION posDgm = pLstDgm->GetHeadPosition();
	CRptDgm *pDgm = NULL;
	while (posDgm != NULL) 
	{
		pDgm = (CRptDgm*)pLstDgm->GetAt(pLstDgm->FindIndex(m_nIndexCurrDgm));
		//��ԭƬ
		pDCMenu->Rectangle(CRect(static_cast<int>(pDgm->rtRaw.rt.left/m_dScale), static_cast<int>(pDgm->rtRaw.rt.top/m_dScale), \
			static_cast<int>(pDgm->rtRaw.rt.right/m_dScale), static_cast<int>(pDgm->rtRaw.rt.bottom/m_dScale))); 
		//������ɫ����,�����и�·������ɫ��������
		CPen bluPen(PS_SOLID, 1, RGB(0, 0, 255));
		CPen *pOldPen = NULL;
		pOldPen = pDCMenu->SelectObject(&bluPen);
		CRptLine *pLine = NULL;
		POSITION posLnTack = pDgm->pLnTrack->GetHeadPosition();
		while (posLnTack != NULL) 
		{
			pLine = (CRptLine*)pDgm->pLnTrack->GetAt(posLnTack);
			
			CGrPoint ptBgn, ptEnd;	//����ͷ���߶�
			CPoint ptPnt;
			ptPnt.x = pLine->ptStart.x/m_dScale;
			ptPnt.y = pLine->ptStart.y/m_dScale;
			ptBgn.Set(ptPnt.x, ptPnt.y);
			pDCMenu->MoveTo(ptPnt);
			ptPnt.x = pLine->ptEnd.x/m_dScale;
			ptPnt.y = pLine->ptEnd.y/m_dScale;
			ptEnd.Set(ptPnt.x, ptPnt.y);
			pDCMenu->LineTo(ptPnt);			
			//��ptEnd������ͷ
			DrawArrowhead(pDCMenu,ptEnd,ptBgn);
			
			pDgm->pLnTrack->GetNext(posLnTack);
		}
		pDCMenu->SelectObject(&pOldPen);
		//��ԭƬ�ӱ��
		//static int nRawRectNo = 1;
		CString strRaw;
		strRaw.Format("%d/%d", pDgm->nDgmNo, pLstDgm->GetCount());
		SetDlgItemText(IDC_EDIT9, strRaw);
		//�������о��μ����ϱ��
		//int no = 1;
		CNoRect *pNoRect = NULL;
		POSITION posRtLay = pDgm->pRtLay->GetHeadPosition();
		pDgm->pRtLay->GetCount();
		while (posRtLay != NULL) 
		{
			pNoRect = pDgm->pRtLay->GetAt(posRtLay);

			//��������Σ���������ε�ͼ����Ϣ
			if ( pNoRect->bShape == TRUE) 
			{
				if ( pNoRect->shape.bChanged != FALSE )
				{
					//��ת����
					CString strRes = RotateSelect(0, 90, pNoRect->rt, pNoRect->shape.strShape);
					DrawShape(pDCMenu, strRes, pNoRect->rt);
				}
				else
				{
					//��������ת
					DrawShape(pDCMenu, pNoRect->shape.strShape, pNoRect->rt);
				}
			}
			
			CString str;
			str.Format("#%d", pNoRect->nLocNo);
			pDCMenu->TextOut(static_cast<int>(pNoRect->rt.left/m_dScale+fabs(pNoRect->rt.Width())/(2*m_dScale)), \
				static_cast<int>(pNoRect->rt.top/m_dScale-fabs(pNoRect->rt.Height())/(2*m_dScale)), str);
			pDgm->pRtLay->GetNext(posRtLay);
		}
		
		//��ʾ������
		CString strUtilization;
		strUtilization.Format("�����ʣ�%.2f%% / %.2f%%",  pDgm->GetUtilization()*100, m_RtOptDll.GetUtil()*100 );
		((CWnd*)GetDlgItem(IDC_STATIC_UTILITY))->SetWindowText(strUtilization);
		
		//"posDgm=NULL"��������ȷ��ֻ��ʾһƬԭƬ��ͼ��
		posDgm = NULL;
	}
}

//��ʼ����ť
void CRectOptDlg::InitButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_EDITSET1);
	CString strName[10];
	if (g_iLanguage == 0)
	{
		strName[0] = "��Ӿ���";
		strName[1] = "ɾ������";
		strName[2] = "G CODE";
		strName[3] = "��ӡ";
		strName[4] = "����";
		strName[5] = "�Ż�";
		strName[6] = "��һ��";
		strName[7] = "��һ��";
		strName[8] = "ͼ��";
		strName[9] = "����";			
	}
	else
	{
		strName[0] = "Add";
		strName[1] = "Delete";
		strName[2] = "G CODE";
		strName[3] = "Print";
		strName[4] = "Back";
		strName[5] = "Optima";
		strName[6] = "Next";
		strName[7] = "Pre";
		strName[8] = "Grap";
		strName[9] = "Send";
	}
	//�½�
	m_pButton[0].SetFont(&g_fontEdit);
	m_pButton[0].SetBitMapID(IDB_BITMAP_NEW1,IDB_BITMAP_NEW2);
	m_pButton[0].Create(strName[0], WS_CHILD | WS_VISIBLE, CPoint(130, 700), c, this, IDC_BUTTON_F1); 
	//ɾ��
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_DELETE1,IDB_BITMAP_DELETE2);
	m_pButton[1].Create(strName[1], WS_CHILD | WS_VISIBLE, CPoint(260, 700), c, this, IDC_BUTTON_F2); 


	
	//����G
	m_pButton[2].SetFont(&g_fontEdit);
	m_pButton[2].SetBitMapID(IDB_BITMAP_SAVEG1,IDB_BITMAP_SAVEG2);	
	m_pButton[2].Create(strName[2], WS_CHILD | WS_VISIBLE, CPoint(650, 700), c, this, IDC_BUTTON_F3); 	
	//��ӡ
	m_pButton[3].SetFont(&g_fontEdit);
	m_pButton[3].SetBitMapID(IDB_BITMAP_PRINT1,IDB_BITMAP_PRINT2);	
	m_pButton[3].Create(strName[3], WS_CHILD | WS_VISIBLE, CPoint(780, 700), c, this, IDC_BUTTON_F4); 
	//����	
	m_pButton[4].SetFont(&g_fontEdit);
	m_pButton[4].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[4].Create(strName[4], WS_CHILD | WS_VISIBLE, CPoint(910, 700), c, this, IDC_BUTTON_F5); 

	//�Ż�
	m_pButton[5].SetFont(&g_fontEdit);
	m_pButton[5].SetBitMapID(IDB_BITMAP_POPTIMA1,IDB_BITMAP_POPTIMA2);	
	m_pButton[5].Create(strName[5], WS_CHILD | WS_VISIBLE, CPoint(390, 700), c, this, IDC_BUTTON_F6);

	//ͼ��
	m_pButton[6].SetFont(&g_fontEdit);
	m_pButton[6].SetBitMapID(IDB_BITMAP_NEST1,IDB_BITMAP_NEST2);	
	m_pButton[6].Create(strName[8], WS_CHILD | WS_VISIBLE, CPoint(0, 700), c, this, IDC_BUTTON_F9);

	//����
	m_pButton[7].SetFont(&g_fontEdit);
	m_pButton[7].SetBitMapID(IDB_BITMAP_SAVEPAR1,IDB_BITMAP_SAVEPAR2);	
	m_pButton[7].Create(strName[9], WS_CHILD | WS_VISIBLE, CPoint(520, 700), c, this, IDC_BUTTON_F10);

	DeleteObject(c);
	

	HRGN g;
	
	g = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),g,IDB_BITMAP_PNEXT1);

	//��һ��
	m_pButton[8].SetFont(&g_fontList);
	m_pButton[8].SetBitMapID(IDB_BITMAP_PNEXT1,IDB_BITMAP_PNEXT2);	
	m_pButton[8].Create(strName[6], WS_CHILD | WS_VISIBLE, CPoint(620, 28), g, this, IDC_BUTTON_F7);

	//ǰһ��	
	m_pButton[9].SetFont(&g_fontList);
	m_pButton[9].SetBitMapID(IDB_BITMAP_PPRE1,IDB_BITMAP_PPRE2);	
	m_pButton[9].Create(strName[7], WS_CHILD | WS_VISIBLE, CPoint(520, 28), g, this, IDC_BUTTON_F8);
	DeleteObject(g);

	
}
//����һ�о�����Ϣ
void CRectOptDlg::AddNewRectInf()
{
	p_stuRectEdit pRectInf = NULL;
    pRectInf = new stuRectEdit;
	if (pRectInf != NULL)
	{
		memset(pRectInf,0,sizeof(stuRectEdit));
		if (p_FirstRectInf == NULL)
		{
			pRectInf->nIndex = 1;
			p_FirstRectInf = pRectInf;
			p_CurrentRectInf = pRectInf;
		}
		else
		{
			pRectInf->nIndex = p_CurrentRectInf->nIndex+1;
			pRectInf->Prev = p_CurrentRectInf;
			p_CurrentRectInf->Next = pRectInf;
			p_CurrentRectInf = pRectInf;
		}
	}
}
//��ʼ��GridCtrl
void CRectOptDlg::OnInitGrid() 
{	
	m_Grid.SubclassDlgItem(IDC_RECTEDIT, this);
	m_Grid.SetFont(&g_fontList);	
	m_Grid.SetEditable(TRUE);
	m_Grid.SetListMode(TRUE);
	m_Grid.SetHeaderSort(FALSE);
	m_Grid.SetRowResize(FALSE);
	m_Grid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));
	
	TRY {
		m_Grid.SetRowCount(1);
		//m_Grid.SetColumnCount(11);
		m_Grid.SetColumnCount(12);
		m_Grid.SetFixedRowCount(1);
		m_Grid.SetFixedColumnCount(1);
	}
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		e->Delete();
		return;
	}
    END_CATCH

	DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
#ifndef _WIN32_WCE
    dwTextStyle |= DT_END_ELLIPSIS;
#endif	
	int			row, col;
	GV_ITEM Item;
	row = 0;
	for (col = 0; col < m_Grid.GetColumnCount(); col++)
	{
		Item.mask = GVIF_TEXT|GVIF_FORMAT;
		Item.row = row;
		Item.col = col;
		Item.nFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
		if(!g_iLanguage)
		{
			switch(col) 
			{
			case 0:		Item.szText.Format(_T("���"));		break;
			case 1:		Item.szText.Format(_T("����"));		break;
			case 2:		Item.szText.Format(_T("���"));		break;
			case 3:		Item.szText.Format(_T("����"));		break;			
			case 4:		Item.szText.Format(_T("��ĥ����"));	break;
			case 5:		Item.szText.Format(_T("��ĥ����"));	break;
			case 6:		Item.szText.Format(_T("��ĥ����"));	break;
			case 7:		Item.szText.Format(_T("��ĥ����"));	break;
			case 8:		Item.szText.Format(_T("�ͻ���"));	break;
			case 9:		Item.szText.Format(_T("����"));		break;
			case 10:	Item.szText.Format(_T("ע��"));		break;
			case 11:	Item.szText.Format(_T("����"));		break;
			default:	break;
			}
		}
		else
		{
			switch(col) 
			{
			case 0:		Item.szText.Format(_T("Index"));		break;
			case 1:		Item.szText.Format(_T("Length"));		break;
			case 2:		Item.szText.Format(_T("Height"));		break;
			case 3:		Item.szText.Format(_T("Count"));		break;	
			case 4:		Item.szText.Format(_T("EdgingLeft"));	break;
			case 5:		Item.szText.Format(_T("EdgingRight"));	break;
			case 6:		Item.szText.Format(_T("EdgingTop"));	break;
			case 7:		Item.szText.Format(_T("EdgingBottom"));	break;
			case 8:		Item.szText.Format(_T("CustName"));		break;
			case 9:		Item.szText.Format(_T("OrderNo"));		break;
			case 10:	Item.szText.Format(_T("Explntn"));		break;
			case 11:	Item.szText.Format(_T("Shape"));		break;
			default:	break;
			}
		}
		m_Grid.SetItem(&Item);
	}	
	//m_Grid.AutoSize();
	for(int i=0; i<m_Grid.GetColumnCount(); i++)
	{
		if (i == 0)
		{
			m_Grid.SetColumnWidth(i, static_cast<int>(m_Grid.GetColumnWidth(i)*0.6));
		}
		else
		{
			//m_Grid.SetColumnWidth(i, static_cast<int>(m_Grid.GetColumnWidth(i)*0.83));
			m_Grid.SetColumnWidth(i, static_cast<int>(m_Grid.GetColumnWidth(i)*0.74));
		}
	}
	m_Grid.SetFocus();
}
//��Ӿ���
void CRectOptDlg::AddGrid()
{
	if (p_CurrentRectInf != NULL)
	{
		m_Grid.SetRowCount(p_CurrentRectInf->nIndex+1);
		GV_ITEM Item;
		DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
#ifndef _WIN32_WCE
		dwTextStyle |= DT_END_ELLIPSIS;
#endif
		for (int col = 0; col < m_Grid.GetColumnCount(); col++)//��
		{ 
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = p_CurrentRectInf->nIndex;
			Item.col = col;
			
			Item.nFormat = dwTextStyle;
			switch(col) 
			{
			case 0:
				Item.szText.Format(_T("%d"),p_CurrentRectInf->nIndex);	
				break;
			case 1:
				Item.szText.Format(_T("%.2f"),p_CurrentRectInf->nNumX*p_CurrentRectInf->nNumY);		
				break;
			case 2:
				Item.szText.Format(_T("%.2f"),p_CurrentRectInf->dpStart.x);		
				break;
			case 3:
				Item.szText.Format(_T("%d"),p_CurrentRectInf->dpStart.y);		
				break;			
			case 4:
				Item.szText.Format(_T("%.2f"),0.0);		
				break;
			case 5:
				Item.szText.Format(_T("%.2f"),0.0);		
				break;
			case 6:
				Item.szText.Format(_T("%.2f"),0.0);		
				break;
			case 7:
				Item.szText.Format(_T("%.2f"),0.0);		
				break;
			case 8:
				Item.szText.Format(_T("%s"), "GLASS");		
				break;
			case 9:
				Item.szText.Format(_T("%s"), "GLASS");		
				break;
			case 10:
				Item.szText.Format(_T("%s"), m_Grid.GetItemText(p_CurrentRectInf->nIndex, 0));		
				break;
			case 11:
				Item.szText.Format(_T("%s"), "");		
				break;
			default:
				break;
			}		
			m_Grid.SetItem(&Item);	
		}
		m_Grid.RedrawRow(p_CurrentRectInf->nIndex);
		m_Grid.SetFocus();
        m_Grid.SetFocusCell(Item.row,1);
	}
}

//�½�
void CRectOptDlg::OnButtonF1()
{
    AddNewRectInf();
	AddGrid();
}

//ɾ��
void CRectOptDlg::OnButtonF2()
{
	DeleRectInf();
	CRect rect(4,50,721,504);
	InvalidateRect(rect,FALSE);
}

//����G
void CRectOptDlg::OnButtonF3()
{
	if(m_RtOptDll.GetDgmList() == NULL)
		return;
	dlg_save  dlgSave;
	dlgSave.strExtName = "";
	if (IDCANCEL == dlgSave.DoModal())	return;
	if(g_strSavefile.IsEmpty())			return;
	m_RtOptDll.WriteGCode(g_strSavefile);
}

//��ӡ
void CRectOptDlg::OnButtonF4()
{	
	CTabDlg dlg;
	dlg.DoModal();
	/*
	CPrintFrame *pFrame = new CPrintFrame;
	pFrame->m_pCallerDlg = this;
	pFrame->Create(NULL,"Curve Print Preview",WS_OVERLAPPEDWINDOW,CRect(0,0,0,0));
	pFrame->m_pView->OnMyPrintPreview();
	*/
}

//����
void CRectOptDlg::OnButtonF5()
{
	WriteEditInf();
	CDialog::OnCancel();
}

//ɾ�����о�����Ϣ
void CRectOptDlg::DeleAllRectInf()
{
	p_stuRectEdit pTemp = NULL;
	for(p_CurrentRectInf=p_FirstRectInf;p_CurrentRectInf;)
	{
		pTemp = p_CurrentRectInf->Next;
		delete(p_CurrentRectInf);
		p_CurrentRectInf = pTemp;
	}
	p_FirstRectInf = NULL;
}

//ɾ����ǰָ��ľ�����Ϣ
void CRectOptDlg::DeleRectInf()
{
	if (p_CurrentRectInf != NULL)
	{
        if (p_CurrentRectInf == p_FirstRectInf)
        {
			delete(p_CurrentRectInf);
			p_CurrentRectInf = NULL;
			p_FirstRectInf = NULL;
			m_Grid.SetRowCount(1);			
        }
		else
		{
			p_stuRectEdit pTemp;
			pTemp = p_CurrentRectInf;
			p_CurrentRectInf = pTemp->Prev;
			p_CurrentRectInf->Next = NULL;
			delete pTemp;
			pTemp = NULL;
			m_Grid.SetRowCount(p_CurrentRectInf->nIndex+1);			
		}
	}
	//�����и��������Ϊ��ʱ��ˢ��
	if (m_Grid.GetRowCount() == 1) 
	{
		//m_PLGCDll.ClearLastArrange();	//��������������кõ���Ϣ
		InvalidateRect(m_rtDisplay);
		((CWnd*)GetDlgItem(IDC_STATIC_UTILITY))->SetWindowText("������:");
	}
}

void CRectOptDlg::OnBtnDisplay() 
{
	//����������֮��Ҫ��ͼ��������Ϊ0
	m_nIndexCurrDgm = 0;
	//��������
	if ( FALSE == InitData() )
	{
		return;
	}
	int nRes = m_RtOptDll.Arrange();

	if ( nRes == 1 )  
	{
		CDlg_AfxMessage  Message;
		Message.bYesNo = FALSE;
		Message.strAfxYES ="ȷ��";
		Message.strAfxTitle ="��ʾ";
		Message.strAfxMessage = _T("ԭƬ��������");
		Message.DoModal();
		//���������Ϣ
		m_RtOptDll.Clear();
		return;
	}
	InvalidateRect(m_rtDisplay);
}

void CRectOptDlg::OnBtnNext() 
{
	//��ȡ���кõ���һƬԭƬ
	if (m_RtOptDll.GetDgmList() != NULL) 
	{
		if (m_nIndexCurrDgm >= 0 && m_nIndexCurrDgm < m_RtOptDll.GetDgmList()->GetCount()-1) 
		{
			m_nIndexCurrDgm++;
			InvalidateRect(m_rtDisplay);
		}
	}
}

void CRectOptDlg::OnBtnPrev() 
{
	//��ȡ���кõ�ǰһƬԭƬ 
	if (m_nIndexCurrDgm > 0 && m_nIndexCurrDgm < m_RtOptDll.GetDgmList()->GetCount()) 
	{
		m_nIndexCurrDgm--;
		InvalidateRect(m_rtDisplay);
	}
}

/*
*  �������ƣ�InitData
*  �������ܣ����Ż��㷨����Ҫ�ı�����ʼ��
*  ����ֵ  ��BOOL 
*  ����˵������
*/
BOOL CRectOptDlg::InitData()
{
	//��ʼ��ԭƬ��Ϣ
	CString strLen, strWid, strNum, strSafeDis, strTrimLeft, strTrimTop, strTrimRight, strTrimBottom, strMinDis, strProName;
	GetDlgItemText(IDC_EDIT1, strLen);
	GetDlgItemText(IDC_EDIT2, strWid);
	GetDlgItemText(IDC_EDIT3, strSafeDis);
	GetDlgItemText(IDC_EDIT4, strNum);
	GetDlgItemText(IDC_EDIT5, strTrimLeft);
	GetDlgItemText(IDC_EDIT6, strTrimRight);
	GetDlgItemText(IDC_EDIT7, strTrimBottom);
	GetDlgItemText(IDC_EDIT8, strTrimTop);
	GetDlgItemText(IDC_EDIT11, strMinDis);
	GetDlgItemText(IDC_EDIT12, strProName);
	//���������Ϣ�Ƿ�ϸ�
	CDlg_AfxMessage  Message;
	Message.bYesNo = FALSE;
	Message.strAfxYES ="ȷ��";
	Message.strAfxTitle ="��ʾ";
	
	if (atof(strLen) <= 0) //ԭƬ���ȱ���Ϊ����
	{
		Message.strAfxMessage = _T("ԭƬ����Ӧ����0.00");
		Message.DoModal();
		return FALSE;
	}
	if (atof(strWid) <= 0)  //ԭƬ��ȱ���Ϊ����
	{
		Message.strAfxMessage = _T("ԭƬ���Ӧ����0.00");
		Message.DoModal();
		return FALSE;
	}
	if (atoi(strNum) <= 0)  //ԭƬ����Ӧ����0
	{
		Message.strAfxMessage = _T("ԭƬ����Ӧ����0");
		Message.DoModal();
		return FALSE;
	}
	if (atof(strSafeDis) < 0) //��ȫ�µ�����Ӧ���ڻ����0.00
	{
		Message.strAfxMessage = _T("��ȫ�µ�����Ӧ���ڻ����0.00");
		Message.DoModal();
		return FALSE;
	}
	if (atof(strTrimLeft)<0 || atof(strTrimRight)<0 || atof(strTrimTop)<0 || atof(strTrimBottom)<0) //�ޱ�Ӧ�Ǹ�
	{
		Message.strAfxMessage = _T("�ޱ�Ӧ���ڻ����0.00");
		Message.DoModal();
		return FALSE;
	}
	if (atof(strMinDis) < 0) //��С����Ӧ���ڻ����0.00
	{
		Message.strAfxMessage = _T("��С����Ӧ���ڻ����0.00");
		Message.DoModal();
		return FALSE;
	}
	//��Ŀ���Ʋ���Ϊ��
	strProName.TrimLeft("\t ");
	if (strProName == "") 
	{
		Message.strAfxMessage = _T("��Ŀ���Ʋ���Ϊ�գ�����������");
		Message.DoModal();
		return FALSE;
	}

	CRptTrim trmm(atof(strTrimLeft), atof(strTrimTop), atof(strTrimRight), atof(strTrimBottom));
	CRptRaw *pRaw = new CRptRaw(atof(strLen), atof(strWid), atoi(strNum), trmm, atof(strMinDis), atof(strSafeDis));
	CList<CRptRaw*, CRptRaw*> lstRaw;
	lstRaw.AddTail(pRaw);
	m_RtOptDll.InitRawList(lstRaw);
	pRaw = NULL;
	//////////////////////////////////////////////////////////
	//�ͷ�lstRaw�ռ�
	while( !lstRaw.IsEmpty() )
	{
		delete lstRaw.RemoveHead();
	}
	lstRaw.RemoveAll();
	//////////////////////////////////////////////////////////
	

	//��ʼ����Ʒ������Ϣ
	int loopNum = m_Grid.GetRowCount();	//��ȡ����������������һ��
	if (loopNum <= 1) 
	{
		return FALSE;
	}
	CString strRtLocNo, strRtLen, strRtWid, strRtNum, strRtEdgeL, strRtEdgeT, strRtEdgeR, strRtEdgeB, \
		strCustName, strOrderNo, strExplntn, strShape;
	CList<CRptDmsn*, CRptDmsn*> lstPro;
	for(int i=1; i<loopNum; i++)
	{
		strRtLocNo  = m_Grid.GetItemText(i, 0);
		strRtLen	= m_Grid.GetItemText(i, 1);
		strRtWid	= m_Grid.GetItemText(i, 2);
		strRtNum    = m_Grid.GetItemText(i, 3);
		strRtEdgeL  = m_Grid.GetItemText(i, 4);
		strRtEdgeR  = m_Grid.GetItemText(i, 5);
		strRtEdgeT  = m_Grid.GetItemText(i, 6);
		strRtEdgeB  = m_Grid.GetItemText(i, 7);
		strCustName = m_Grid.GetItemText(i, 8);
		strOrderNo  = m_Grid.GetItemText(i, 9);
		strExplntn  = m_Grid.GetItemText(i, 10);
		strShape	= m_Grid.GetItemText(i, 11);
		//���������Ϣ�Ƿ�ϸ�
		/*
		if (atof(strRtLen) > atof(strLen) || atof(strRtLen)<=0 || atof(strRtLen) > atof(strLen)-atof(strTrimLeft)-atof(strTrimRight) || \
			atof(strRtLen)+atof(strRtEdgeL)+atof(strRtEdgeR) > atof(strLen)-atof(strTrimLeft)-atof(strTrimRight)) 
		{
			Message.strAfxMessage = _T("���γ������벻�ϸ�����������");
			Message.DoModal();
			return FALSE;
		}
		if (atof(strRtLen) < atof(strLen)) 
		{
			if (atof(strRtLen)+atof(strRtEdgeL)+atof(strRtEdgeR) > atof(strLen)-atof(strTrimLeft)-atof(strTrimRight)-atof(strMinDis)) 
			{
				Message.strAfxMessage = _T("���γ������벻�ϸ�����������");
				Message.DoModal();
				return FALSE;
			}
		}
		if (atof(strRtWid) > atof(strWid) || atof(strRtWid)<=0 || atof(strRtWid) > atof(strWid)-atof(strTrimTop)-atof(strTrimBottom) || \
			atof(strRtWid)+atof(strRtEdgeT)+atof(strRtEdgeB) > atof(strWid)-atof(strTrimTop)-atof(strTrimBottom)) 
		{
			Message.strAfxMessage = _T("���ο�����벻�ϸ�����������");
			Message.DoModal();
			return FALSE;
		}
		if (atof(strRtWid) < atof(strWid)) 
		{
			if (atof(strRtWid)+atof(strRtEdgeT)+atof(strRtEdgeB) > atof(strWid)-atof(strTrimTop)-atof(strTrimBottom)-atof(strMinDis)) 
			{
				Message.strAfxMessage = _T("���ο�����벻�ϸ�����������");
				Message.DoModal();
				return FALSE;
			}
		}
		*/
		if ( atof(strRtLen)<=0 || atof(strRtWid)<=0 ) 
		{
			Message.strAfxMessage = _T("���γߴ����벻���ʣ�����������");
			Message.DoModal();
			return FALSE;
		}
		if ( !(atof(strRtLen)+atof(strRtEdgeL)+atof(strRtEdgeR) <= atof(strLen)-atof(strTrimLeft)-atof(strTrimRight) && \
			atof(strRtWid)+atof(strRtEdgeT)+atof(strRtEdgeB) <= atof(strWid)-atof(strTrimTop)-atof(strTrimBottom) ||
			atof(strRtLen)+atof(strRtEdgeL)+atof(strRtEdgeR) <= atof(strWid)-atof(strTrimTop)-atof(strTrimBottom) && \
			atof(strRtWid)+atof(strRtEdgeT)+atof(strRtEdgeB) <= atof(strLen)-atof(strTrimLeft)-atof(strTrimRight))  ) 
		{
			Message.strAfxMessage = _T("���γߴ����벻���ʣ�����������");
			Message.DoModal();
			return FALSE;
		}
		
		if (atoi(strRtNum) <= 0) //��Ʒ���θ���Ӧ����0
		{
			Message.strAfxMessage = _T("���θ���Ӧ����0������������");
			Message.DoModal();
			return FALSE;
		}
		//ȥ���û����������š�ע����ߵĿո�
		strCustName.TrimLeft("\t ");
		strOrderNo.TrimLeft("\t ");
		strExplntn.TrimLeft("\t ");
		if (strCustName == "" || strOrderNo == "" || strExplntn == "")	//�û����������š�ע�����벻��Ϊ��
		{
			Message.strAfxMessage = _T("�û����������š�ע����Ϣ���벻��Ϊ�գ�����������");
			Message.DoModal();
			return FALSE;
		}
	

		//��ȡ�������Ʊ��
		CString shpname, shpno;		
		int nPos = strShape.FindOneOf("-");
		shpname = strShape.Left( nPos );
		strShape = strShape.Mid(nPos+1);
		nPos = strShape.FindOneOf("-");
		shpno   = strShape.Left( nPos );
		strShape = strShape.Mid(nPos+1);
		//strShape.TrimLeft("\t ");

		//��ȡ�����ޱ�
		double dTrmLeft, dTrmRight, dTrmTop, dTrmBottom;
		nPos = strShape.FindOneOf("-");
		dTrmLeft = atof(strShape.Left( nPos ));
		strShape = strShape.Mid(nPos+1);
		
		nPos = strShape.FindOneOf("-");
		dTrmRight = atof(strShape.Left( nPos ));
		strShape = strShape.Mid(nPos+1);
		
		nPos = strShape.FindOneOf("-");
		dTrmTop = atof(strShape.Left( nPos ));
		strShape = strShape.Mid(nPos+1);
		
		nPos = strShape.FindOneOf("-");
		dTrmBottom = atof(strShape.Left( nPos ));
		strShape = strShape.Mid(nPos+1);
		
		if (strShape != "")		//�������,˵��������
		{
			CString strName;
			strName.Format("%s-%s", shpname, shpno); 
			
			CRptEdge edge(atof(strRtEdgeL), atof(strRtEdgeT), atof(strRtEdgeR), atof(strRtEdgeB));
			if ( atof(strRtLen) >= atof(strRtWid) ) 
			{
				CRptTrim trm( dTrmLeft, dTrmRight, dTrmTop, dTrmBottom );
				CRptShpDmsn shpDmsn(atof(strRtLen), atof(strRtWid), trm, strName, strShape, FALSE, FALSE );
				CRptDmsn *pDmsn = new CRptDmsn(atoi(strRtLocNo), atof(strRtLen), atof(strRtWid), atoi(strRtNum), edge, \
					TRUE, shpDmsn, strCustName, strOrderNo, strExplntn);		
				lstPro.AddTail(pDmsn);
			}
			else
			{
				CRptTrim trm( dTrmLeft, dTrmRight, dTrmTop, dTrmBottom );
				CRptShpDmsn shpDmsn(atof(strRtLen), atof(strRtWid), trm, strName, strShape, TRUE, TRUE );
				CRptDmsn *pDmsn = new CRptDmsn(atoi(strRtLocNo), atof(strRtLen), atof(strRtWid), atoi(strRtNum), edge, \
					TRUE, shpDmsn, strCustName, strOrderNo, strExplntn);		
				lstPro.AddTail(pDmsn);
			}
		}
		else
		{
			//��lstPro�������Ԫ��
			CRptEdge edge(atof(strRtEdgeL), atof(strRtEdgeT), atof(strRtEdgeR), atof(strRtEdgeB));
			CRptShpDmsn shpDmsn;
			CRptDmsn *pDmsn = new CRptDmsn(atoi(strRtLocNo), atof(strRtLen), atof(strRtWid), atoi(strRtNum), edge, \
				FALSE, shpDmsn, strCustName, strOrderNo, strExplntn);
			lstPro.AddTail(pDmsn);
		}
	}
	m_RtOptDll.InitProList(lstPro);

	///////////////////////////////////////////////////////////
	//�ͷ�lstPro�ռ�
	while( !lstPro.IsEmpty() )
	{
		delete lstPro.RemoveHead();
	}
	lstPro.RemoveAll();
	///////////////////////////////////////////////////////////////

	return TRUE;
}


void CRectOptDlg::OnChangeEdit10() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	if (p_CurrentRectInf != NULL) 
	{
		CString str;
		GetDlgItemText(IDC_EDIT10, str);
		str.Format("%.2f", atof(str));
		if (str != "") 
		{
			for(int j=4; j<8; j++)
			{
				if (p_CurrentRectInf->nIndex != 0) 
				{
					CString str;
					GetDlgItemText(IDC_EDIT10, str);
					m_Grid.SetItemText(m_Grid.GetFocusCell().row, j, str);
					m_Grid.RedrawRow(m_Grid.GetFocusCell().row);
				}
			}
		}
	}
}

BOOL CRectOptDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CWnd			*pWnd=NULL;
		char			cClassName[50]={0};
		pWnd = GetFocus();
		GetClassName(pWnd->GetSafeHwnd(), cClassName, 50);//��ȡ�ؼ�������    
		
		CWnd *pWndFocus = GetFocus();
		if (pWndFocus != NULL)
		{
			UINT nID = pWndFocus->GetDlgCtrlID();
			if (nID == IDC_RECTEDIT
				||(strstr(cClassName, "Edit") && (nID>IDC_EDIT12 || nID < IDC_EDIT1)))
			{
// 				CCellID cel = m_Grid.GetFocusCell();
// 				if (cel.col<10)
// 				{
// 					m_Grid.SetFocusCell(cel.row,cel.col+1);
// 				}
				keybd_event(VK_RIGHT, 0, 0, 0);
				return TRUE;
			}
			else 				
				return TRUE;
		}
	}
	else if( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F4)//����СƬ
	{
		OnButtonF1();
        return TRUE;
	}	
	return CDialog::PreTranslateMessage(pMsg);
}


void CRectOptDlg::OnBtnExcel() 
{	
	//��������ÿ�
	((CWnd*)GetDlgItem(IDC_EDIT9))->SetWindowText("");
	//���������ÿ�
	((CWnd*)GetDlgItem(IDC_STATIC_UTILITY))->SetWindowText("");
	//ɾ�����еľ�����Ϣ
	int nRow = m_Grid.GetRowCount();
	for(int i=1; i<nRow; i++)
		DeleRectInf();
	//��ȡExcel������
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrFilter = _T( "Microsoft Excel Files(*.xls)\0*.xls" );
	dlg.m_ofn.lpstrTitle = _T( "��Excel�ļ�" );
	int nRetVal = dlg.DoModal();
	if ( nRetVal == IDOK )
	{
		// ��ȡExcel�ļ��е�����
		CString strFilePath = dlg.GetPathName();
		CIOExcel oIOExcel;
		oIOExcel.setViewObject( this );

		oIOExcel.loadExcelFile( strFilePath );
	}
}

BOOL CRectOptDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	//��Ӵ���ʵ�ֵ��grid���һ�о͵���ͼ�ⴰ��
	{
		CString			strCell;
		CCellID			*pCell=NULL;
		CWnd			*pWnd=NULL;
		char			cClassName[50]={0};
		CString			strShape;
		
		pWnd = GetFocus();
		GetClassName(pWnd->GetSafeHwnd(), cClassName, 50);//��ȡ�ؼ�������    
		
		if(strstr(cClassName, "MFCGridCtrl"))
		{
			pCell = &(m_Grid.GetFocusCell());

			if (pCell->col == 11 && pCell->row != 0)
			{
				CGraphDlg dlg;
				dlg.m_bRtOpt = true;
				if(IDOK == dlg.DoModal())//��ͼ�ⴰ��
				{
					strShape = CString(dlg.m_cShape);

					//��m_strShape����Ϣ��ȡ����
					double dLen, dWid;
					int nNum;
					
					GV_ITEM ItemLen;
					DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
				#ifndef _WIN32_WCE
					dwTextStyle |= DT_END_ELLIPSIS;
				#endif
					ItemLen.mask = GVIF_TEXT|GVIF_FORMAT;
					ItemLen.row = pCell->row;
					ItemLen.col = 1;
					ItemLen.nFormat = dwTextStyle;
					int nPos = strShape.FindOneOf("-");
					dLen = atof(strShape.Left(nPos));
					strShape = strShape.Mid(nPos+1);
					ItemLen.szText.Format(_T("%.6g"), dLen);
					m_Grid.SetItem(&ItemLen);
					m_Grid.RedrawRow(ItemLen.row);

					GV_ITEM ItemWid;
					dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
				#ifndef _WIN32_WCE
					dwTextStyle |= DT_END_ELLIPSIS;
				#endif
					ItemWid.mask = GVIF_TEXT|GVIF_FORMAT;
					ItemWid.row = pCell->row;
					ItemWid.col = 2;
					ItemWid.nFormat = dwTextStyle;
					nPos = strShape.FindOneOf("-");
					dWid = atof(strShape.Left(nPos));
					strShape = strShape.Mid(nPos+1);
					ItemWid.szText.Format(_T("%.6g"), dWid);
					m_Grid.SetItem(&ItemWid);
					m_Grid.RedrawRow(ItemWid.row);

					GV_ITEM ItemNum;
					dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
				#ifndef _WIN32_WCE
					dwTextStyle |= DT_END_ELLIPSIS;
				#endif
					ItemNum.mask = GVIF_TEXT|GVIF_FORMAT;
					ItemNum.row = pCell->row;
					ItemNum.col = 3;
					ItemNum.nFormat = dwTextStyle;
					nPos = strShape.FindOneOf("-");
					nNum = atoi(strShape.Left(nPos));
					strShape = strShape.Mid(nPos+1);
					ItemNum.szText.Format(_T("%d"), nNum);
					m_Grid.SetItem(&ItemNum);
					m_Grid.RedrawRow(ItemNum.row);
		
					GV_ITEM ItemShape;
					dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
				#ifndef _WIN32_WCE
					dwTextStyle |= DT_END_ELLIPSIS;
				#endif
					ItemShape.mask = GVIF_TEXT|GVIF_FORMAT;
					ItemShape.row = pCell->row;
					ItemShape.col = 11;
					ItemShape.nFormat = dwTextStyle;
					ItemShape.szText.Format(_T("%s"), strShape);//���һ����ʾ���α��+����ͼ�ε�������Ϣ
					m_Grid.SetItem(&ItemShape);
					m_Grid.RedrawRow(ItemShape.row);
				}
			m_Grid.SetFocusCell(-1, -1);
			}
		}
	}
	// TODO: Add your specialized code here and/or call the base class
	if(g_stu_pAxisC->bSpareA==0)
		return CDialog::OnCommand(wParam, lParam);
	if (wParam != MAKELONG(IDC_RECTEDIT, BN_CLICKED))
	{
		return CDialog::OnCommand(wParam, lParam);
	}
	CString			strCell;
	CCellID			*pCell=NULL;
	CWnd			*pWnd=NULL;
	char			cClassName[50]={0};
	
	pWnd = GetFocus();
	GetClassName(pWnd->GetSafeHwnd(), cClassName, 50);//��ȡ�ؼ�������    
	
	if(strstr(cClassName, "MFCGridCtrl") || strstr(cClassName, "Edit"))
	{
		pCell = &(m_Grid.GetFocusCell());
		strCell = m_Grid.GetItemText(pCell->row, pCell->col);
		if (pCell->col >= 8)
		{
			CDlg_KeyChar CharDlg;
			CharDlg.m_strNew = CharDlg.m_strOld = strCell;
			if(CharDlg.DoModal()==IDOK)
			{
				m_Grid.SetItemText(pCell->row, pCell->col, CharDlg.m_strNew);
				m_Grid.RedrawCell(pCell->row, pCell->col);
			}
		}
		else
		{
			CDlg_KeyNumber	KeyNum;
			KeyNum.m_strNew = KeyNum.m_strOld = strCell;
			if(KeyNum.DoModal()==IDOK)
			{
				m_Grid.SetItemText(pCell->row, pCell->col, KeyNum.m_strNew);
				m_Grid.RedrawCell(pCell->row, pCell->col);
			}
		}
	}				
	return CDialog::OnCommand(wParam, lParam);
}

void CRectOptDlg::OnBtnGrap()
{
	CGraphDlg dlg;			
	if(IDOK == dlg.DoModal())//ͼ�ⷢ��
	{
		CDialog::OnOK();		
	}
}

void CRectOptDlg::OnBtnSend()
{
	if(m_RtOptDll.GetDgmList() == NULL)
		return;
	CString strProName;
   	((CEdit*)GetDlgItem(IDC_EDIT12))->GetWindowText(strProName);
	g_strSavefile = strProName;
	if(g_strSavefile.IsEmpty())			return;
	//��Ҫ�����Ż����һƬ���ļ���ȫ��
	BSTR str;
	str = m_RtOptDll.WriteGCode(g_strSavefile);
	strProName = g_strOriginalPathD+"gcode\\"+(CString)str;
	g_strShowName = (CString)str;
	g_strGfile = strProName;
    g_strSavefile = "";
	WriteEditInf();
	
	CDialog::OnOK();
}

LRESULT CRectOptDlg::OnEditDouble(WPARAM wParam, LPARAM lParam) 
{
	CString				strTmp;
	
	if(lParam==1)/* �д����� */
	{
		((CEdit *)GetDlgItem(wParam))->SetSel(0,-1);
		return 0;
	}
	
	CWnd::GetDlgItemText(wParam,strTmp);
	if ((UINT)wParam == IDC_EDIT12)
	{
		CDlg_KeyChar KeyNum;
		KeyNum.m_strNew = KeyNum.m_strOld = strTmp;
		if(KeyNum.DoModal()==IDOK)
			CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	}
	else
	{
		CDlg_KeyNumber		KeyNum;
		KeyNum.m_strNew = KeyNum.m_strOld = strTmp;
		if(KeyNum.DoModal()==IDOK)
			CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	}	
	return 0;
}

void CRectOptDlg::OnLanguage()
{
	if (g_iLanguage == 1)
	{
		SetDlgItemText(IDC_DEMO10CTRL1,"Optima");
		SetDlgItemText(IDC_STATIC_NO,"NO.");
		SetDlgItemText(IDC_STATIC_LIGHT,"Width");
		SetDlgItemText(IDC_STATIC_HEIGHT,"Height");
		SetDlgItemText(IDC_STATIC_COUNT,"       Count");
		SetDlgItemText(IDC_STATIC_SAFE,"Safe Dis");
		SetDlgItemText(IDC_TRIM_LEFT,"TripLeft");
		SetDlgItemText(IDC_TRIM_BOTTOM,"TripBottom");
		SetDlgItemText(IDC_TRIM_RIGHT,"TripRight");
		SetDlgItemText(IDC_TRIM_TOP,"TripTop");
		SetDlgItemText(IDC_MIN_EDGE,"Min Dis");
		SetDlgItemText(IDC_GRIND,"Edging");
		SetDlgItemText(IDC_PROJECT,"Project");
		SetDlgItemText(IDC_STATIC_UTILITY,"Utility");
		SetDlgItemText(IDC_BTN_EXCEL,"ExcelInput");
	}
}

//����ԭƬ��Ϣ
void CRectOptDlg::WriteEditInf()
{
	CString strEdit;
	GetDlgItemText(IDC_EDIT1,strEdit);//������
	strEdit.Format("%.2f",atof(strEdit));
	WritePrivateProfileString("SHEET","LENGTH",strEdit,INIFILE_OPTIMA);
	GetDlgItemText(IDC_EDIT2,strEdit);//������
	strEdit.Format("%.2f",atof(strEdit));
	WritePrivateProfileString("SHEET","WIDTH",strEdit,INIFILE_OPTIMA);
	GetDlgItemText(IDC_EDIT4,strEdit);//����
	strEdit.Format("%.0f",atof(strEdit));
	WritePrivateProfileString("SHEET","COUNT",strEdit,INIFILE_OPTIMA);
	GetDlgItemText(IDC_EDIT3,strEdit);//��ȫ�µ�����
	strEdit.Format("%.2f",atof(strEdit));
	WritePrivateProfileString("SHEET","SAFEDIS",strEdit,INIFILE_OPTIMA);
	GetDlgItemText(IDC_EDIT5,strEdit);//�ޱ���
	strEdit.Format("%.2f",atof(strEdit));
	WritePrivateProfileString("SHEET","TRIMLEFT",strEdit,INIFILE_OPTIMA);
	GetDlgItemText(IDC_EDIT7,strEdit);//�ޱ���
	strEdit.Format("%.2f",atof(strEdit));
	WritePrivateProfileString("SHEET","TRIPMDOWN",strEdit,INIFILE_OPTIMA);
	GetDlgItemText(IDC_EDIT6,strEdit);//�ޱ���
	strEdit.Format("%.2f",atof(strEdit));
	WritePrivateProfileString("SHEET","TRIMRIGHT",strEdit,INIFILE_OPTIMA);
	GetDlgItemText(IDC_EDIT8,strEdit);//�ޱ���
	strEdit.Format("%.2f",atof(strEdit));
	WritePrivateProfileString("SHEET","TRIMUP",strEdit,INIFILE_OPTIMA);
	GetDlgItemText(IDC_EDIT11,strEdit);//��С����
	strEdit.Format("%.2f",atof(strEdit));
	WritePrivateProfileString("SHEET","MINDIS",strEdit,INIFILE_OPTIMA);
	GetDlgItemText(IDC_EDIT10,strEdit);//�ı�ĥ
	strEdit.Format("%.2f",atof(strEdit));
	WritePrivateProfileString("SHEET","EDGING",strEdit,INIFILE_OPTIMA);
	GetDlgItemText(IDC_EDIT12,strEdit);//��Ŀ��
	WritePrivateProfileString("SHEET","PROJECT",strEdit,INIFILE_OPTIMA);
}

//��ʼ��ԭƬ��Ϣ
void CRectOptDlg::InitSheetPar()
{
	CString strPara;		
	GetPrivateProfileString("SHEET","LENGTH","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_OPTIMA);
	strPara.Format("%.2f",atof(strPara));
	SetDlgItemText(IDC_EDIT1,strPara);
	GetPrivateProfileString("SHEET","WIDTH","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_OPTIMA);
	strPara.Format("%.2f",atof(strPara));
	SetDlgItemText(IDC_EDIT2,strPara);
	GetPrivateProfileString("SHEET","COUNT","1000",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_OPTIMA);
	strPara.Format("%.0f",atof(strPara));
	SetDlgItemText(IDC_EDIT4,strPara);
	GetPrivateProfileString("SHEET","SAFEDIS","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_OPTIMA);
	strPara.Format("%.2f",atof(strPara));
	SetDlgItemText(IDC_EDIT3,strPara);
	GetPrivateProfileString("SHEET","TRIMLEFT","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_OPTIMA);
	strPara.Format("%.2f",atof(strPara));
	SetDlgItemText(IDC_EDIT5,strPara);
	GetPrivateProfileString("SHEET","TRIPMDOWN","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_OPTIMA);
	strPara.Format("%.2f",atof(strPara));
	SetDlgItemText(IDC_EDIT7,strPara);
	GetPrivateProfileString("SHEET","TRIMRIGHT","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_OPTIMA);
	strPara.Format("%.2f",atof(strPara));
	SetDlgItemText(IDC_EDIT6,strPara);
	GetPrivateProfileString("SHEET","TRIMUP","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_OPTIMA);
	strPara.Format("%.2f",atof(strPara));
	SetDlgItemText(IDC_EDIT8,strPara);
	GetPrivateProfileString("SHEET","MINDIS","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_OPTIMA);
	strPara.Format("%.2f",atof(strPara));
	SetDlgItemText(IDC_EDIT11,strPara);
	GetPrivateProfileString("SHEET","EDGING","0.00",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_OPTIMA);
	strPara.Format("%.2f",atof(strPara));
	SetDlgItemText(IDC_EDIT10,strPara);
	GetPrivateProfileString("SHEET","PROJECT","RtOpt",strPara.GetBuffer(MAX_PATH),MAX_PATH,INIFILE_OPTIMA);
	SetDlgItemText(IDC_EDIT12,strPara);
}

//����ͷ,���յ��ϻ�
//pDC��ͼdc������յ�
void CRectOptDlg::DrawArrowhead(CDC *pDC, CGrPoint &ptBgn, CGrPoint &ptEnd)
{
	GR_LINE ln1, ln2;
	CPoint points[3];	
	CRgn rgn;
	CBrush br;
	br.CreateSolidBrush(RGB(79,167,214));
	if(pDC)
	{
		LineRevolve(ln1, ptBgn, ptEnd, (MATH_PI*2)-(MATH_PI/12),12.0);
		LineRevolve(ln2, ptBgn, ptEnd, MATH_PI/12, 12.0);
		ln1.pt1.ToCPoint(&points[0]);
		ln2.pt1.ToCPoint(&points[1]);
		ptBgn.ToCPoint(&points[2]);
		rgn.CreatePolygonRgn(points, 3, RGN_OR);
		pDC->FillRgn(&rgn, &br);
		pDC->MoveTo(points[2]);
		pDC->LineTo(points[0]);
		pDC->MoveTo(points[2]);
		pDC->LineTo(points[1]);		
	}
	if(rgn.m_hObject)
		rgn.DeleteObject();
	if(br.m_hObject)
		br.DeleteObject();
}

//��һ���߶���ʱ��ת��һ���ǶȺ󣬵õ�һ���µ��߶Σ�
//ptCenter��	Ϊת�������ĵ㣻
//ptRef��		ת���Ĳο��㣻
//fSweepArc��	��ʱ��ת���ĽǶȣ�
//fRadius��		��output.ptCenterһ��ȷ�����߶εĶ˵㵽output.ptCenter�ľ��룻
//output��		�µ��߶Σ������У�output.ptCenter����ptCenter, output.pt1ΪptRef��ʱ��ת���������߶����Ҿ���output.ptCenterΪ
//				fRadius�Ķ˵㣬output.pt2Ϊoutput.pt1��output.ptCenterΪ���ĵľ���㣩��
void CRectOptDlg::LineRevolve(GR_LINE &output, CGrPoint ptCenter, CGrPoint ptRef, double fSweepArc, double fRadius)
{
	CGrPoint pt0, pt1;
	double fArcBgn, fArc, fFx, fFy, bakSweepArc;
	int nQuadrant;
	
	memset(&output, 0, sizeof(GR_LINE));
	
	bakSweepArc = fSweepArc;
	
	while(fSweepArc<0)
	{ fSweepArc += (MATH_PI*2); }
	
	pt0 = ptCenter;
	
	ptCenter.fx -= pt0.fx;
	ptCenter.fy -= pt0.fy;
	ptRef.fx -= pt0.fx;
	ptRef.fy -= pt0.fy;
	
	nQuadrant = GetPointQuadrant(ptRef);
	fFx = (ptRef.fx<0)? (-1) : (1);	
	fFy = (ptRef.fy<0)? (-1) : (1);	
	fArcBgn = atan((ptRef.fy*fFy)/(ptRef.fx*fFx));
	switch(nQuadrant)
	{
	case 0:	fArcBgn = fArcBgn;				break;
	case 1:	fArcBgn = MATH_PI-fArcBgn;		break;
	case 2:	fArcBgn = MATH_PI+fArcBgn;		break;
	case 3:	fArcBgn = (MATH_PI*2)-fArcBgn;	break;
	default:	break;
	}
	
	fArc = (fArcBgn+fSweepArc);
	while(fArc>=(MATH_PI*2))
	{	fArc-=(MATH_PI*2);	}	
	nQuadrant = GetArcQuadrant(fArc);
	switch(nQuadrant)
	{
	case 0:
		fArc = fArc;
		fFx = 1;	fFy = 1;
		break;
	case 1:
		fArc = MATH_PI-fArc;
		fFx = -1;	fFy = 1;
		break;
	case 2:
		fArc = fArc-MATH_PI;
		fFx = -1;	fFy = -1;
		break;
	case 3:
		fArc = (MATH_PI*2)-fArc;
		fFx = 1;	fFy = -1;
		break;
	default:	break;
	}
	
	output.pt1.fx = fRadius*cos(fArc);
	output.pt1.fy = fRadius*sin(fArc);
	output.pt1.fx *= fFx;
	output.pt1.fy *= fFy;
	
	output.pt2.fx = output.pt1.fx*(-1);
	output.pt2.fy = output.pt1.fy*(-1);
	
	output.ptCenter = ptCenter;
	
	output.pt1.Offset(pt0);
	output.pt2.Offset(pt0);
	output.ptCenter.Offset(pt0);
}

//��ת����
CString CRectOptDlg::RotateSelect(double fBeginAngle, double fRotateAngel, CRptRect rt, CString strCmd)		
{
	int nPos;
	CString strLine;		//��������
	CString strResult = "";		//������
	CString strLineResult = "";	

	CRptPoint ptCenter;
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
	
	return strResult;
}

void CRectOptDlg::DrawShape( CDC *pDC, CString strCmd, CRptRect rt )
{
	pDC->MoveTo(rt.left/m_dScale, rt.top/m_dScale);
	CPen pensel[3];
	pensel[0].CreatePen(PS_DOT,1,RGB(0,255,0));
	pensel[1].CreatePen(PS_SOLID,2,RGB(0,0,200));
	pensel[2].CreatePen(PS_SOLID,2,RGB(255,0,0));

	CStdioFile paraf;
	CString strPath,sqr1,pdcstr;
	CRptPoint ptCur;			//���浱ǰ������

	int nPos;		
	pDC->SelectObject(&pensel[1]);
	
	double dOffsetX, dOffsetY;
	dOffsetX = rt.left/m_dScale;	
	dOffsetY = rt.top/m_dScale;	

	ptCur.x = rt.left;
	ptCur.y = rt.top;

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
			CRptLine line(ptCur, CRptPoint(rt.left+pointx,rt.top-pointy));
			if ( rt.LnOnDownRect(line) ) 
			{
				pDC->MoveTo(dOffsetX+pointx/m_dScale,dOffsetY-pointy/m_dScale);	
			}
			else
			{
				pDC->LineTo(dOffsetX+pointx/m_dScale,dOffsetY-pointy/m_dScale);
			}
			ptCur.x = rt.left+pointx;
			ptCur.y = rt.top-pointy;
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
			CRptLine line(ptCur, CRptPoint(rt.left+pointx,rt.top-pointy));	

			if ( rt.LnOnDownRect(line) ) 
			{
				pDC->MoveTo(dOffsetX+pointx/m_dScale,dOffsetY-pointy/m_dScale);	
			}
			else
			{
				pDC->LineTo(dOffsetX+pointx/m_dScale,dOffsetY-pointy/m_dScale);
			}
			
			ptCur.x = rt.left+pointx;
			ptCur.y = rt.top-pointy;
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
			

			double Gendx=pointR*cos((pointQ+pointD)*PI/180)+rt.left+pointx;
			double Gendy=-pointR*sin((pointQ+pointD)*PI/180)+rt.top-pointy;
			pDC->AngleArc(dOffsetX+pointx/m_dScale, 
				dOffsetY-pointy/m_dScale,(int)(pointR/m_dScale),(float)pointQ,(float)pointD);
			
			ptCur.x = Gendx;
			ptCur.y = Gendy;
		}
	}
	
	pDC->SelectObject(&pensel[1]);

	pensel[0].DeleteObject();
	pensel[1].DeleteObject();
	pensel[2].DeleteObject();
}
