// GrEditor.cpp : implementation file
//

#include "stdafx.h"
#include "GrEditor.h"
#include "dlg_save.h"
#include "benderDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrEditor dialog


CGrEditor::CGrEditor(CWnd* pParent /*=NULL*/)
	: CDialog(CGrEditor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrEditor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	m_bDlgInitialized=FALSE;
	memset(&m_clip, 0, sizeof(GR_CLIP));
	memset(&m_picAttr, 0, sizeof(PIC_ATTR));
	m_picAttr.nPicType=GTYPE_NONE;
}


void CGrEditor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrEditor)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrEditor, CDialog)
	//{{AFX_MSG_MAP(CGrEditor)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_EN_KILLFOCUS(IDC_EDIT_PARA01, OnKillfocusEditPara01)
	ON_EN_KILLFOCUS(IDC_EDIT_PARA02, OnKillfocusEditPara02)
	ON_EN_KILLFOCUS(IDC_EDIT_PARA03, OnKillfocusEditPara03)
	ON_EN_KILLFOCUS(IDC_EDIT_PARA04, OnKillfocusEditPara04)
	ON_EN_KILLFOCUS(IDC_EDIT_PARA05, OnKillfocusEditPara05)
	ON_EN_KILLFOCUS(IDC_EDIT_PARA06, OnKillfocusEditPara06)
	ON_EN_KILLFOCUS(IDC_EDIT_PARA07, OnKillfocusEditPara07)
	ON_EN_KILLFOCUS(IDC_EDIT_PARA08, OnKillfocusEditPara08)
	ON_EN_KILLFOCUS(IDC_EDIT_PARA09, OnKillfocusEditPara09)
	ON_EN_KILLFOCUS(IDC_EDIT_PARA10, OnKillfocusEditPara10)
	ON_EN_KILLFOCUS(IDC_EDIT_PARA11, OnKillfocusEditPara11)
	ON_EN_KILLFOCUS(IDC_EDIT_PARA12, OnKillfocusEditPara12)
	ON_EN_KILLFOCUS(IDC_EDIT_PARA13, OnKillfocusEditPara13)
	ON_EN_KILLFOCUS(IDC_EDIT_PARA14, OnKillfocusEditPara14)
	ON_EN_KILLFOCUS(IDC_EDIT_PARA15, OnKillfocusEditPara15)
	ON_EN_KILLFOCUS(IDC_EDIT_ClipX1, OnKillfocusEDITClipX1)
	ON_EN_KILLFOCUS(IDC_EDIT_ClipX2, OnKillfocusEDITClipX2)
	ON_EN_KILLFOCUS(IDC_EDIT_ClipY1, OnKillfocusEDITClipY1)
	ON_EN_KILLFOCUS(IDC_EDIT_ClipY2, OnKillfocusEDITClipY2)
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrEditor message handlers

void CGrEditor::Clean()
{
	m_grPath.Reset();
	if(m_dcGraph.m_hDC)
		m_dcGraph.FillSolidRect(0,0, m_rcGraph.Width(), m_rcGraph.Height(), RGB(255,255,255));
	Invalidate(FALSE);
}

BOOL CGrEditor::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}

void CGrEditor::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if(m_bDlgInitialized)
		ResetUI();
}

BOOL CGrEditor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_bDlgInitialized=TRUE;
	if (g_iLanguage == 1)
	{
		SetDlgItemText(IDC_STATIC_ClipX1,"X1 Trim");
		SetDlgItemText(IDC_STATIC_ClipY1,"Y1 Trim");
		SetDlgItemText(IDC_STATIC_ClipX2,"X2 Trim");
		SetDlgItemText(IDC_STATIC_ClipY2,"Y2 Trim");
	}
	SetTimer(1, 10, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGrEditor::ResetUI()
{
#define CONTROL_HEIGHT		20
	int nIDs[]=
	{
		IDC_STATIC_PARA01, IDC_STATIC_PARA02, IDC_STATIC_PARA03, IDC_STATIC_PARA04, IDC_STATIC_PARA05, 
		IDC_STATIC_PARA06, IDC_STATIC_PARA07, IDC_STATIC_PARA08, IDC_STATIC_PARA09, IDC_STATIC_PARA10, 
		IDC_STATIC_PARA11, IDC_STATIC_PARA12, IDC_STATIC_PARA13, IDC_STATIC_PARA14, IDC_STATIC_PARA15, 
		IDC_EDIT_PARA01, IDC_EDIT_PARA02, IDC_EDIT_PARA03, IDC_EDIT_PARA04, IDC_EDIT_PARA05,
		IDC_EDIT_PARA06, IDC_EDIT_PARA07, IDC_EDIT_PARA08, IDC_EDIT_PARA09, IDC_EDIT_PARA10,
		IDC_EDIT_PARA11, IDC_EDIT_PARA12, IDC_EDIT_PARA13, IDC_EDIT_PARA14, IDC_EDIT_PARA15,
		IDC_STATIC_REMARK1, IDC_STATIC_REMARK2, IDC_STATIC_REMARK3, IDC_STATIC_REMARK4, IDC_STATIC_REMARK5, 
		IDC_STATIC_REMARK6, IDC_STATIC_REMARK7, IDC_STATIC_REMARK8, IDC_STATIC_REMARK9, IDC_STATIC_REMARK10, 
		IDC_STATIC_REMARK11, IDC_STATIC_REMARK12, IDC_STATIC_REMARK13, IDC_STATIC_REMARK14, IDC_STATIC_REMARK15, 
		0
	};
	CWnd *pwnd=NULL;
	int i;
	for(i=0; nIDs[i]>0; i++)
	{
		pwnd = GetDlgItem(nIDs[i]);
		if(pwnd)
			pwnd->ShowWindow(SW_HIDE);
	}
    if (m_picAttr.nPicType == GTYPE_DXF)
    {
		UpdateGraph();
		return;
    }
	int yOffset, nTitleCtrlWidth, nEditCtrlWidth, nRemarkCtrlWidth;
	CRect rect, rc;
	
	GetClientRect(&rect);
	rect.DeflateRect(4, 4, 4, 4);
	rect.top += 32;//64;

	nTitleCtrlWidth = (rect.Width()*58/100)*30/100;
	nEditCtrlWidth = (rect.Width()*58/100)*70/100;
	nRemarkCtrlWidth = rect.Width()*42/100;

	yOffset=0;

	rc = rect;
	rc.right -= (rc.Width()/10);
	rc.bottom = rc.top+CONTROL_HEIGHT;


	CUISetting *pSet=GetUISetting(m_picAttr.szPicName);
	if(pSet)
	{
		GRPARA *para=NULL;
		CString ss;
		int count=0;
		while(1)
		{
			para = pSet->GetUIPara(count++);
			if(!para)
				break;
			pwnd = GetDlgItem(para->nTitleCtrlID);
			if(pwnd)
			{
				pwnd->SetWindowText(para->szTitle);
				pwnd->MoveWindow(rc.left, rc.top, nTitleCtrlWidth*90/100, rc.Height(), FALSE);
				pwnd->ShowWindow(SW_SHOW);
			}
			pwnd = GetDlgItem(para->nEditCtrlID);
			if(pwnd)
			{
				ss.Format("%.1f", para->fValue);
				pwnd->SetWindowText(ss);
				pwnd->MoveWindow(rc.left+nTitleCtrlWidth, rc.top, nEditCtrlWidth*90/100, rc.Height(), FALSE);
				pwnd->ShowWindow(SW_SHOW);
			}
			pwnd = GetDlgItem(para->nRemarkCtrlID);
			if(pwnd)
			{
				pwnd->SetWindowText(para->szRemark);
				pwnd->MoveWindow(rc.left+nTitleCtrlWidth+nEditCtrlWidth, rc.top, nRemarkCtrlWidth, rc.Height(), FALSE);
				pwnd->ShowWindow(SW_SHOW);
			}
			rc.OffsetRect(0, CONTROL_HEIGHT);
		}
		
		yOffset = count*CONTROL_HEIGHT;
	}


	CPaintDC dc(this);
	int temp;
	m_rcGraph = rect;
	m_rcGraph.top += yOffset;
	m_rcGraph.bottom -= (4*CONTROL_HEIGHT);
	if(m_rcGraph.Width()<=m_rcGraph.Height())
	{
		temp = (m_rcGraph.Height()-m_rcGraph.Width())/2;
		m_rcGraph.top += temp;
		m_rcGraph.bottom -= temp;
	}
	else
	{
		temp = (m_rcGraph.Width()-m_rcGraph.Height())/2;
		m_rcGraph.left += temp;
		m_rcGraph.right -= temp;
	}
	CreateDC(&m_dcGraph, &dc, m_rcGraph.Width(), m_rcGraph.Height());
	if(m_dcGraph.m_hDC)
		m_dcGraph.FillSolidRect(0,0, m_rcGraph.Width(), m_rcGraph.Height(), RGB(255,255,255));

	CStatic *pTitelCtrl=NULL;
	CEdit   *pEditCtrl=NULL;

	rc = rect;
	rc.right -= (rc.Width()/10);
	rc.top = rc.bottom-CONTROL_HEIGHT;
	nTitleCtrlWidth = (rect.Width()/4);
	nEditCtrlWidth = (rect.Width()*3/4);

	pTitelCtrl = (CStatic*)GetDlgItem(IDC_STATIC_ClipY2);
	if(pTitelCtrl)
		pTitelCtrl->MoveWindow(rc.left, rc.top, nTitleCtrlWidth, rc.Height(), FALSE);
	pEditCtrl  = (CEdit*)GetDlgItem(IDC_EDIT_ClipY2);
	if(pEditCtrl)
		pEditCtrl->MoveWindow(rc.left+nTitleCtrlWidth, rc.top, nEditCtrlWidth, rc.Height(), FALSE);
	rc.OffsetRect(0, -CONTROL_HEIGHT);

	pTitelCtrl = (CStatic*)GetDlgItem(IDC_STATIC_ClipY1);
	if(pTitelCtrl)
		pTitelCtrl->MoveWindow(rc.left, rc.top, nTitleCtrlWidth, rc.Height(), FALSE);
	pEditCtrl  = (CEdit*)GetDlgItem(IDC_EDIT_ClipY1);
	if(pEditCtrl)
		pEditCtrl->MoveWindow(rc.left+nTitleCtrlWidth, rc.top, nEditCtrlWidth, rc.Height(), FALSE);
	rc.OffsetRect(0, -CONTROL_HEIGHT);
	
	pTitelCtrl = (CStatic*)GetDlgItem(IDC_STATIC_ClipX2);
	if(pTitelCtrl)
		pTitelCtrl->MoveWindow(rc.left, rc.top, nTitleCtrlWidth, rc.Height(), FALSE);
	pEditCtrl  = (CEdit*)GetDlgItem(IDC_EDIT_ClipX2);
	if(pEditCtrl)
		pEditCtrl->MoveWindow(rc.left+nTitleCtrlWidth, rc.top, nEditCtrlWidth, rc.Height(), FALSE);
	rc.OffsetRect(0, -CONTROL_HEIGHT);
	
	pTitelCtrl = (CStatic*)GetDlgItem(IDC_STATIC_ClipX1);
	if(pTitelCtrl)
		pTitelCtrl->MoveWindow(rc.left, rc.top, nTitleCtrlWidth, rc.Height(), FALSE);
	pEditCtrl  = (CEdit*)GetDlgItem(IDC_EDIT_ClipX1);
	if(pEditCtrl)
		pEditCtrl->MoveWindow(rc.left+nTitleCtrlWidth, rc.top, nEditCtrlWidth, rc.Height(), FALSE);
	rc.OffsetRect(0, -CONTROL_HEIGHT);

	UpdateGraph();
}

void CGrEditor::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);
	dc.BitBlt(m_rcGraph.left, m_rcGraph.top, m_rcGraph.Width(), m_rcGraph.Height(), &m_dcGraph, 0, 0, SRCCOPY);
	//dc.StretchBlt(m_rcGraph.left, m_rcGraph.top, m_rcGraph.Width(), m_rcGraph.Height(), &m_dcGraph, 0, 0, m_rcGraph.Width(), m_rcGraph.Height(), SRCCOPY);
}

void CGrEditor::SetGraph(const PIC_ATTR *pPicAttr)
{
	memset(&m_picAttr, 0, sizeof(PIC_ATTR));	
	if(!pPicAttr)
		return;
	memcpy(&m_picAttr, pPicAttr, sizeof(PIC_ATTR));
	Clean();
	ResetUI();
}



void CGrEditor::UpdateGraph()
{
	int ids[15]={IDC_EDIT_PARA01, IDC_EDIT_PARA02, IDC_EDIT_PARA03, IDC_EDIT_PARA04, IDC_EDIT_PARA05,
				 IDC_EDIT_PARA06, IDC_EDIT_PARA07, IDC_EDIT_PARA08, IDC_EDIT_PARA09, IDC_EDIT_PARA10,
				 IDC_EDIT_PARA11, IDC_EDIT_PARA12, IDC_EDIT_PARA13, IDC_EDIT_PARA14, IDC_EDIT_PARA15};
	int i;

	m_clip.X1 = GetEditValue((CEdit*)GetDlgItem(IDC_EDIT_ClipX1));
	m_clip.X2 = GetEditValue((CEdit*)GetDlgItem(IDC_EDIT_ClipX2));
	m_clip.Y1 = GetEditValue((CEdit*)GetDlgItem(IDC_EDIT_ClipY1));
	m_clip.Y2 = GetEditValue((CEdit*)GetDlgItem(IDC_EDIT_ClipY2));

	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA01);
	for(i=0; i<(int)(m_uiSettings[m_picAttr.nIndex].GetParaCount()); i++)
	{
		if(i>=15)
			continue;
		pEdit=(CEdit*)GetDlgItem(ids[i]);
		para = m_uiSettings[m_picAttr.nIndex].GetUIPara(i);
		para->fValue = GetEditValue(pEdit);	
	}
	
	m_grPath.Reset();
	m_grPath.SetClip(m_clip);

	m_dcGraph.FillSolidRect(0,0, m_rcGraph.Width(), m_rcGraph.Height(), RGB(255,255,255));
	switch(m_picAttr.nPicType)
	{
	case GTYPE_CIRCLE:		ProcCircle();	break;
	case GTYPE_TRIANGLE:	ProcTriangle();	break;
	case GTYPE_RECTANGLE:	ProcRectangle();break;
	case GTYPE_PENTAGON:	ProcPentagon();	break;
	case GTYPE_HEXAGON:		ProcHexagon();	break;
	case GTYPE_YIXING_1:	ProcYixing1();	break;
	case GTYPE_YIXING_2:	ProcYixing2();	break;
	case GTYPE_YIXING_3:	ProcYixing3();	break;
	case GTYPE_DXF:         ProcDxf();      break;
	case GTYPE_NONE:
	default:
		break;
	}
}

void CGrEditor::OnKillfocusEditPara01() 
{
	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA01);
	double fNewValue=GetEditValue(pEdit);
	if(!m_uiSettings[m_picAttr.nIndex].GetParaCount())
		return;
	para = (m_uiSettings[m_picAttr.nIndex].GetUIPara(0));
	if(fNewValue==para->fValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEditPara02() 
{
	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA02);
	double fNewValue=GetEditValue(pEdit);
	if(!m_uiSettings[m_picAttr.nIndex].GetParaCount())
		return;
	para = (m_uiSettings[m_picAttr.nIndex].GetUIPara(1));
	if(fNewValue==para->fValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEditPara03() 
{
	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA03);
	double fNewValue=GetEditValue(pEdit);
	if(!m_uiSettings[m_picAttr.nIndex].GetParaCount())
		return;
	para = (m_uiSettings[m_picAttr.nIndex].GetUIPara(2));
	if(fNewValue==para->fValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEditPara04() 
{
	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA04);
	double fNewValue=GetEditValue(pEdit);
	if(!m_uiSettings[m_picAttr.nIndex].GetParaCount())
		return;
	para = (m_uiSettings[m_picAttr.nIndex].GetUIPara(3));
	if(fNewValue==para->fValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEditPara05() 
{
	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA05);
	double fNewValue=GetEditValue(pEdit);
	if(!m_uiSettings[m_picAttr.nIndex].GetParaCount())
		return;
	para = (m_uiSettings[m_picAttr.nIndex].GetUIPara(4));
	if(fNewValue==para->fValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEditPara06() 
{
	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA06);
	double fNewValue=GetEditValue(pEdit);
	if(!m_uiSettings[m_picAttr.nIndex].GetParaCount())
		return;
	para = (m_uiSettings[m_picAttr.nIndex].GetUIPara(5));
	if(fNewValue==para->fValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEditPara07() 
{
	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA07);
	double fNewValue=GetEditValue(pEdit);
	if(!m_uiSettings[m_picAttr.nIndex].GetParaCount())
		return;
	para = (m_uiSettings[m_picAttr.nIndex].GetUIPara(6));
	if(fNewValue==para->fValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEditPara08() 
{
	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA08);
	double fNewValue=GetEditValue(pEdit);
	if(!m_uiSettings[m_picAttr.nIndex].GetParaCount())
		return;
	para = (m_uiSettings[m_picAttr.nIndex].GetUIPara(7));
	if(fNewValue==para->fValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEditPara09() 
{
	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA09);
	double fNewValue=GetEditValue(pEdit);
	if(!m_uiSettings[m_picAttr.nIndex].GetParaCount())
		return;
	para = (m_uiSettings[m_picAttr.nIndex].GetUIPara(8));
	if(fNewValue==para->fValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEditPara10() 
{
	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA10);
	double fNewValue=GetEditValue(pEdit);
	if(!m_uiSettings[m_picAttr.nIndex].GetParaCount())
		return;
	para = (m_uiSettings[m_picAttr.nIndex].GetUIPara(9));
	if(fNewValue==para->fValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEditPara11() 
{
	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA11);
	double fNewValue=GetEditValue(pEdit);
	if(!m_uiSettings[m_picAttr.nIndex].GetParaCount())
		return;
	para = (m_uiSettings[m_picAttr.nIndex].GetUIPara(10));
	if(fNewValue==para->fValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEditPara12() 
{
	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA12);
	double fNewValue=GetEditValue(pEdit);
	if(!m_uiSettings[m_picAttr.nIndex].GetParaCount())
		return;
	para = (m_uiSettings[m_picAttr.nIndex].GetUIPara(11));
	if(fNewValue==para->fValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEditPara13() 
{
	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA13);
	double fNewValue=GetEditValue(pEdit);
	if(!m_uiSettings[m_picAttr.nIndex].GetParaCount())
		return;
	para = (m_uiSettings[m_picAttr.nIndex].GetUIPara(12));
	if(fNewValue==para->fValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEditPara14() 
{
	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA14);
	double fNewValue=GetEditValue(pEdit);
	if(!m_uiSettings[m_picAttr.nIndex].GetParaCount())
		return;
	para = (m_uiSettings[m_picAttr.nIndex].GetUIPara(13));
	if(fNewValue==para->fValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEditPara15() 
{
	GRPARA *para=NULL;
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT_PARA15);
	double fNewValue=GetEditValue(pEdit);
	if(!m_uiSettings[m_picAttr.nIndex].GetParaCount())
		return;
	para = (m_uiSettings[m_picAttr.nIndex].GetUIPara(14));
	if(fNewValue==para->fValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEDITClipX1() 
{
	double fNewValue=GetEditValue((CEdit*)GetDlgItem(IDC_EDIT_ClipX1));
	if(m_clip.X1==fNewValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEDITClipX2() 
{
	double fNewValue=GetEditValue((CEdit*)GetDlgItem(IDC_EDIT_ClipX2));
	if(m_clip.X2==fNewValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEDITClipY1() 
{
	double fNewValue=GetEditValue((CEdit*)GetDlgItem(IDC_EDIT_ClipY1));
	if(m_clip.Y1==fNewValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnKillfocusEDITClipY2() 
{
	double fNewValue=GetEditValue((CEdit*)GetDlgItem(IDC_EDIT_ClipY2));
	if(m_clip.Y2==fNewValue)
		return;
	UpdateGraph();
}

void CGrEditor::OnButtonTest() 
{
	CString str = m_grPath.MakeGCode();
	AfxMessageBox(str);
}

double CGrEditor::GetEditValue(CEdit *pEdit)
{
	CString str;
	double fValue=0.0f;
	if(pEdit)
	{
		pEdit->GetWindowText(str);
		fValue = atof(str);
	}
	return fValue;
}

BOOL CGrEditor::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(wParam)
	{
	case IDOK:
	case IDCANCEL:
		return TRUE;
		break;
	case IDC_EDIT_PARA01:
		lParam=lParam;
		break;
	}
	return CDialog::OnCommand(wParam, lParam);
}

//处理圆形
void CGrEditor::ProcCircle()
{
	CRect rect, rcDrawing;
	CString strName=m_picAttr.szPicName;
	GR_LINE line;
	CGrPoint ptC0, ptC1, tmp[4];
	CGrPoint points[8];
	CGrArc grArc;
	CGrEllipse grEllipse;
	GR_RECT grRect;
	double fTemp;
	int i;

	//////////////////////////////////////////////////////////////////////////
	CUISetting *pSet = &m_uiSettings[m_picAttr.nIndex];
	double r = pSet->GetValue("R");
	double r1 = pSet->GetValue("R1");
	double r2 = pSet->GetValue("R2");
	double r3 = pSet->GetValue("R3");
	double d = pSet->GetValue("D");
	double d1 = pSet->GetValue("D1");
	double w = pSet->GetValue("W");
	double w1 = pSet->GetValue("W1");
	double w2 = pSet->GetValue("W2");
	double h = pSet->GetValue("H");
	double h1 = pSet->GetValue("H1");
	double A = pSet->GetValue("A");
	double s = pSet->GetValue("S");
	double N = pSet->GetValue("N");
	double b = pSet->GetValue("B");
	double c = pSet->GetValue("C");
	//////////////////////////////////////////////////////////////////////////

	m_dcGraph.GetClipBox(&rect);
	rcDrawing=rect;
	rcDrawing.DeflateRect(32,32,32,32);
	

	if("001"==strName)
	{
		r = d/2;
		ptC0.Set((m_clip.X1+r), (m_clip.Y1+r));
		
		grArc.InitCircle(r, ptC0);
		m_grPath.AddIndependentCircleNode(grArc);

		tmp[1] = tmp[0] = ptC0;
		tmp[0].Offset(-r, 0);
		tmp[1].Offset(r, 0);
		m_grPath.DimensionAppendD(tmp[0], tmp[1], "D", 0.0f);
	}
	else if("002"==strName)
	{
		ptC0.Set((m_clip.X1+r), (m_clip.Y1+r));
		
		grArc.InitCircle(r, ptC0);
		m_grPath.AddIndependentCircleNode(grArc);

		m_grPath.DimensionAppendR(ptC0, r, 0, "R");
	}
	else if("003"==strName)
	{
		ptC0.Set((m_clip.X1+r), (m_clip.Y1+r));
		ptC1 = ptC0;
		
		grArc.InitCircle(r, ptC0);
		m_grPath.AddIndependentCircleNode(grArc);
		
		grArc.InitCircle(r1, ptC1);
		m_grPath.AddIndependentCircleNode(grArc);

		m_grPath.DimensionAppendR(ptC0, r, 0, "R");		
		m_grPath.DimensionAppendR(ptC1, r1, MATH_PI*3/4, "R1");
	}
	else if("004"==strName || "005"==strName || "250"==strName || "262"==strName)
	{
		ptC0.Set((m_clip.X1+r), (m_clip.Y1+r));
		
		grArc.InitCircle(r, ptC0);
		m_grPath.AddIndependentCircleNode(grArc);
		
// 		m_grPath.DimensionAppendR(ptC0, r, MATH_PI/4, "R");
		
		tmp[1] = ptC0;
		tmp[1].Offset(d, 0);
		m_grPath.DimensionAppendD(tmp[1], ptC0, "D", 12.0f);

		int nCount;
		if("005"==strName)
			nCount=4;
		else if("250"==strName)
			nCount=6;
		else if("262"==strName)
			nCount=7;
		else
			nCount=3;

		ptC1 = ptC0;
		ptC1.Offset(d, 0);
		for(i=0; i<nCount; i++)
		{	
			grArc.InitCircle(r1, ptC1);
			m_grPath.AddIndependentCircleNode(grArc);

			if(i==2)
			{
				m_grPath.DimensionAppendR(ptC0, r, MATH_PI/4, "R");
				m_grPath.DimensionAppendR(ptC1, r1, MATH_PI/3, "R1");
			}

			LineRevolve(line, ptC0, ptC1, MATH_PI*2/nCount, d);
			ptC1 = line.pt1;
		}
	}
	else if("006"==strName)
	{
		r = ((w*w)/(8*h)) + (h/2);
		if(h>r)
			ptC0.Set((m_clip.X1+w/2), (m_clip.Y1+h-r));
		else
			ptC0.Set((m_clip.X1+w/2), (m_clip.Y1-(r-h)));
		
		tmp[0].Set((m_clip.X1), (m_clip.Y1));
		tmp[1] = tmp[0];
		tmp[1].Offset(w, 0);
		grArc.InitArc(r, ptC0, tmp[0], tmp[1], (h>r)?TRUE:FALSE);
		m_grPath.AddArcNode(grArc);

		m_grPath.DimensionAppendD(tmp[1], tmp[0], "W");
		tmp[0] = ptC0;
		tmp[0].Offset(-r, r);
		tmp[1] = tmp[0];
		tmp[1].Offset(0, -h);
		m_grPath.DimensionAppendD(tmp[1], tmp[0], "H");

		grArc.GetOutline(grRect);
		if(grRect.fX0<grArc.m_ptArcBgn.fx)
			m_grPath.Offset(grArc.m_ptArcBgn.fx-grRect.fX0, 0);
	}
	else if("007"==strName)
	{
		ptC0.Set((m_clip.X1+r), (m_clip.Y1));
		
		tmp[0] = ptC0;
		tmp[0].Offset(-r, 0);
		tmp[1] = ptC0;
		tmp[1].Offset(r, 0);
		grArc.InitArc(r, ptC0, tmp[0], tmp[1]);
		m_grPath.AddArcNode(grArc);

		m_grPath.DimensionAppendR(ptC0, r, MATH_PI/2, "R");
	}
	else if("008"==strName)
	{
		ptC0.Set((m_clip.X1+max(r1, r2)), (m_clip.Y1));
		
		tmp[1] = tmp[0] = ptC0;
		tmp[0].Offset(-r2, 0);
		tmp[1].Offset(r2, 0);
		grArc.InitArc(r2, ptC0, tmp[0], tmp[1]);
		m_grPath.AddArcNode(grArc);
		
		tmp[1] = tmp[0] = ptC0;
		tmp[0].Offset(-r1, 0);
		tmp[1].Offset(r1, 0);
		grArc.InitArc(r1, ptC0, tmp[0], tmp[1]);
		m_grPath.AddArcNode(grArc, FALSE);

		m_grPath.DimensionAppendR(ptC0, r1, (MATH_PI*3/4), "R1");
		
		m_grPath.DimensionAppendR(ptC0, r2, (MATH_PI/4), "R2");
	}
	else if("009"==strName)
	{
		ptC0.Set((m_clip.X1), (m_clip.Y1));
		
		m_grPath.AddSharpNodes(&ptC0, 1);
		
		tmp[1] = tmp[0] = ptC0;
		tmp[0].Offset(0, r);
		tmp[1].Offset(r, 0);
		grArc.InitArc(r, ptC0, tmp[0], tmp[1]);
		m_grPath.AddArcNode(grArc);
		
		
		tmp[0] = ptC0;
		tmp[1] = ptC0;
		tmp[1].Offset(r, 0);
		LineRevolve(line, tmp[0], tmp[1], MATH_PI/4, r);
		tmp[1] = line.pt1;
		LineRevolve(line, tmp[1], tmp[0], 0, r/2);
		tmp[0] = line.pt1;
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R");
	}
	else if("010"==strName)
	{
		points[0].Set((m_clip.X1), (m_clip.Y1));
		points[1] = points[0];
		points[1].Offset(w, 0);
		points[2] = points[0];
		points[2].Offset(0, h);
		
		fTemp = RetrieveAngleOfTriangle(sqrt(w*w+h*h), r, r);
		fTemp = (MATH_PI-fTemp)/2;
		LineRevolve(line, points[1], points[2], fTemp, r);
		ptC0 = line.pt1;
		
		m_grPath.AddSharpNodes(&points[0], 1);
		
		grArc.InitArc(r, ptC0, points[2], points[1]);
		m_grPath.AddArcNode(grArc);

		m_grPath.DimensionAppendD(points[1], points[0], "W");
		
		m_grPath.DimensionAppendD(points[0], points[2], "H");
		
		LineRevolve(line, ptC0, points[1], (MATH_PI-(2*fTemp))/2, r);
		tmp[1] = line.pt1;
		fTemp = r/2;
		if(fTemp>(w/2))	fTemp=(w/2);
		if(fTemp>(h/2))	fTemp=(h/2);
		LineRevolve(line, tmp[1], ptC0, 0, fTemp);
		tmp[0] = line.pt1;
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R");
	}
	else if("011"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1);
		
		w1 = sqrt(w*w+h*h);
		r = (h1/2)+((w1*w1)/(8*h1));
		fTemp = RetrieveAngleOfTriangle(r, r, w1);
		LineRevolve(line, points[2], points[1], fTemp, r);
		ptC0 = line.pt1;

		grArc.InitArc(r, ptC0, points[1], points[2]);

		m_grPath.AddSharpNodes(&points[0], 1);
		m_grPath.AddArcNode(grArc);
		
		grArc.GetArcMidpoint(tmp[0]);
		LineRevolve(line, tmp[0], grArc.m_ptC0, 0, h1);

		m_grPath.DimensionAppendD(line.pt1, tmp[0], "H1", 4);
		m_grPath.DimensionAppendD(points[2], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
	}
	else if("012"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1);
		
		fTemp = sqrt(w1*w1+h*h);
		fTemp = RetrieveAngleOfTriangle(r, r, fTemp);
		LineRevolve(line, points[1], points[0], fTemp, r);
		ptC0 = line.pt1;
		
		grArc.InitArc(r, ptC0, points[0], points[1]);
		
		m_grPath.AddArcNode(grArc);
		m_grPath.AddSharpNodes(&points[2], 1);
		
		grArc.GetArcMidpoint(tmp[0]);
		LineRevolve(line, tmp[0], grArc.m_ptC0, 0, w/2);
		
		m_grPath.DimensionAppendR(line.pt1, tmp[0], "R");
		m_grPath.DimensionAppendD(points[2], points[0], "W");
		tmp[0].Set(m_clip.X1, m_clip.Y1+h);
		m_grPath.DimensionAppendD(points[0], tmp[0], "H");
		m_grPath.DimensionAppendD(tmp[0], points[1], "W1");

		grArc.GetOutline(grRect);
		if(grRect.fX0<points[0].fx)
			m_grPath.Offset(points[0].fx-grRect.fX0, 0);
	}
	else if("013"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1);
		
		fTemp = sqrt(w1*w1+h*h);
		r = (s/2)+((fTemp*fTemp)/(8*s));
		fTemp = RetrieveAngleOfTriangle(r, r, fTemp);
		LineRevolve(line, points[1], points[0], fTemp, r);
		ptC0 = line.pt1;
		
		grArc.InitArc(r, ptC0, points[0], points[1]);
		
		m_grPath.AddArcNode(grArc);
		m_grPath.AddSharpNodes(&points[2], 1);
		
		grArc.GetArcMidpoint(tmp[0]);
		LineRevolve(line, tmp[0], grArc.m_ptC0, 0, s);
		
		m_grPath.DimensionAppendD(line.pt1, tmp[0], "S");
		m_grPath.DimensionAppendD(points[2], points[0], "W");
		tmp[0].Set(m_clip.X1, m_clip.Y1+h);
		m_grPath.DimensionAppendD(points[0], tmp[0], "H");
		m_grPath.DimensionAppendD(tmp[0], points[1], "W1");
		
		grArc.GetOutline(grRect);
		if(grRect.fX0<points[0].fx)
			m_grPath.Offset(points[0].fx-grRect.fX0, 0);
	}
	else if("014"==strName || "015"==strName)
	{
		if("014"==strName)
			w1 = w;
		A = (A*MATH_PI/180);
		h = w1*sin(A);
		w2 = w1*cos(A);
		fTemp = sqrt(h*h+(w-w2)*(w-w2));
		fTemp = RetrieveAngleOfTriangle(r, r, fTemp);

		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w2, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 3);
		
		if(fTemp>0)
		{
			LineRevolve(line, points[2], points[1], fTemp, r);
			ptC0 = line.pt1;
			grArc.InitArc(r, ptC0, points[1], points[2]);
			
			m_grPath.AddSharpNodes(&points[0], 1);
			m_grPath.AddArcNode(grArc);
			
			m_grPath.DimensionAppendD(points[2], points[0], "W");
			if("015"==strName)
				m_grPath.DimensionAppendD(points[0], points[1], "W1");
			
			grArc.GetArcMidpoint(tmp[0]);
			LineRevolve(line, tmp[0], grArc.m_ptC0, 0, w/2);
			m_grPath.DimensionAppendR(line.pt1, tmp[0], "R");
			
			LineRevolve(line, points[0], points[2], 0, w/4);
			tmp[0] = line.pt1;
			LineRevolve(line, points[0], points[2], A, w/4);
			tmp[1] = line.pt1;
			m_grPath.DimensionAppendA(points[0], tmp[1], tmp[0], "A", A>MATH_PI);
			
			if(grArc.m_ptArcBgn.fx<m_clip.X1)
				m_grPath.Offset(m_clip.X1-grArc.m_ptArcBgn.fx, 0);
			if(grArc.m_ptArcBgn.fy<m_clip.Y1)
				m_grPath.Offset(0, m_clip.Y1-grArc.m_ptArcBgn.fy);
		}
	}
	else if("016"==strName)
	{
		A = (A*MATH_PI/180);
		if(A<(MATH_PI/2))
		{
			double d1, d2;
			d1 = (h/tan(A));
			d2 = (h/sin(A));
			points[0].Set(m_clip.X1, m_clip.Y1);
			tmp[0] = points[0];
			tmp[0].Offset(w+d1, 0);
			LineRevolve(line, tmp[0], points[0], -A, w1+d2);
			points[1] = line.pt1;
			points[2].Set(m_clip.X1+w, m_clip.Y1+d1);
			points[3].Set(m_clip.X1+w, m_clip.Y1);

			LineRevolve(line, tmp[0], points[0], 0, w/3);
			tmp[1] = line.pt1;
			LineRevolve(line, tmp[0], points[1], 0, w/3);
			tmp[2] = line.pt1;
			m_grPath.DimensionAppendA(tmp[0], tmp[1], tmp[2], "A");

			fTemp = GetDistanceF(points[0], points[1]);
			fTemp = RetrieveAngleOfTriangle(r, r, fTemp);
			if(fTemp>0)
			{
				GR_RECT rc;
				LineRevolve(line, points[1], points[0], fTemp, r);
				ptC0 = line.pt1;
				
				grArc.InitArc(r, ptC0, points[0], points[1]);
				m_grPath.AddArcNode(grArc, TRUE);
				grArc.GetOutline(rc);
				grArc.GetArcMidpoint(tmp[0]);
				LineRevolve(line, tmp[0], grArc.m_ptC0, 0, w/2);
				m_grPath.DimensionAppendR(line.pt1, tmp[0], "R");
				
				m_grPath.AddSharpNodes(&points[2], 1);
				
				m_grPath.AddSharpNodes(&points[3], 1);

				m_grPath.DimensionAppendD(points[3], points[0], "W");
				m_grPath.DimensionAppendD(points[1], points[2], "W1");
				m_grPath.DimensionAppendD(points[2], points[3], "H");

				if(rc.fX0<points[0].fx)
					m_grPath.Offset(points[0].fx-rc.fX0, 0);
			}
		}
	}
	else if("017"==strName)
	{
		if(h<=w)
		{
			fTemp = asin(h/w);
			points[0].Set(m_clip.X1+w, m_clip.Y1);
			points[1].Set(m_clip.X1, m_clip.Y1);
			LineRevolve(line, points[0], points[1], -fTemp, w);
			points[2] = line.pt1;
			grArc.InitArc(w, points[0], points[1], points[2]);
			m_grPath.AddArcNode(grArc);
			m_grPath.AddSharpNodes(&points[0], 1);

			tmp[0] = points[1];
			tmp[0].Offset(0, h);
			m_grPath.DimensionAppendD(points[1], tmp[0], "H");
			m_grPath.DimensionAppendD(points[0], points[1], "W");
		}
	}
	else if("018"==strName || "032"==strName)
	{
		double fMinX, fMinY;
		GR_RECT rcOutline;

		r3 = (r1-r2)/2;
		if(r3<0)
			r3 *= -1;		
		A = (A*MATH_PI/180);

		ptC0.Set((m_clip.X1), (m_clip.Y1));
		tmp[1].Set(m_clip.X1+r2, m_clip.Y1);
		LineRevolve(line, ptC0, tmp[1], A, r2);
		tmp[0] = line.pt1;
		LineRevolve(line, ptC0, tmp[0], 0, r1);
		tmp[2] = line.pt1;
		LineRevolve(line, ptC0, tmp[1], 0, r1);
		tmp[3] = line.pt1;

		fMinX = ptC0.fx;
		fMinY = ptC0.fy;

		grArc.InitArc(r2, ptC0, tmp[0], tmp[1], A>MATH_PI);
		m_grPath.AddArcNode(grArc, FALSE);
		m_grPath.DimensionAppendD(ptC0, grArc.m_ptArcBgn, "R2");
		grArc.GetOutline(rcOutline);
		if(fMinX > rcOutline.fX0)
			fMinX = rcOutline.fX0;
		if(fMinY > rcOutline.fY0)
			fMinY = rcOutline.fY0;
		
		if("032"==strName)
		{
			LineRevolve(line, ptC0, tmp[0], 0, r2+r3);
			ptC1 = line.pt1;
			grArc.InitArc(r3, ptC1, tmp[0], tmp[2]);
			m_grPath.AddArcNode(grArc, TRUE);
			grArc.GetOutline(rcOutline);
			if(fMinX > rcOutline.fX0)
				fMinX = rcOutline.fX0;
			if(fMinY > rcOutline.fY0)
				fMinY = rcOutline.fY0;
		}

		
		grArc.InitArc(r1, ptC0, tmp[2], tmp[3], A>MATH_PI);
		m_grPath.AddArcNode(grArc, TRUE);
		m_grPath.DimensionAppendD(grArc.m_ptArcEnd, ptC0, "R1");
		grArc.GetOutline(rcOutline);
		if(fMinX > rcOutline.fX0)
			fMinX = rcOutline.fX0;
		if(fMinY > rcOutline.fY0)
			fMinY = rcOutline.fY0;

		if("032"==strName)
		{
			LineRevolve(line, ptC0, tmp[1], 0, r2+r3);
			ptC1 = line.pt1;
			grArc.InitArc(r3, ptC1, tmp[3], tmp[1]);
			m_grPath.AddArcNode(grArc, TRUE);
			grArc.GetOutline(rcOutline);
			if(fMinX > rcOutline.fX0)
				fMinX = rcOutline.fX0;
			if(fMinY > rcOutline.fY0)
				fMinY = rcOutline.fY0;
		}

		LineRevolve(line, ptC0, tmp[1], 0, r2/2);
		tmp[1] = line.pt1;
		LineRevolve(line, ptC0, tmp[1], A, r2/2);
		tmp[0] = line.pt1;
		m_grPath.DimensionAppendA(ptC0, tmp[0], tmp[1], "A", A>MATH_PI);
		
		m_grPath.Offset(m_clip.X1-fMinX, m_clip.Y1-fMinY);
	}
	else if("019"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w, m_clip.Y1);
		
		fTemp = RetrieveAngleOfTriangle(r1, r1, w);
		LineRevolve(line, points[1], points[0], fTemp, r1);
		ptC0 = line.pt1;
		
		grArc.InitArc(r1, ptC0, points[0], points[1]);
		m_grPath.AddArcNode(grArc);

		grArc.GetArcMidpoint(tmp[0]);
		LineRevolve(line, tmp[0], ptC0, 0, (r1-r2)*2/3);
		m_grPath.DimensionAppendR(line.pt1, tmp[0], "R1");
		tmp[1] = grArc.m_ptArcBgn;
		tmp[1].Offset(0, tmp[0].fy-grArc.m_ptArcBgn.fy);
		tmp[2] = grArc.m_ptArcEnd;
		tmp[2].Offset(0, tmp[0].fy-grArc.m_ptArcEnd.fy);
		m_grPath.DimensionAppendD(tmp[1], tmp[2], "W");
		
		LineRevolve(line, points[0], ptC0, 0, (r1-r2));
		tmp[0] = line.pt1;
		LineRevolve(line, points[1], ptC0, 0, (r1-r2));
		tmp[1] = line.pt1;
		
		fTemp = (grArc.m_ptArcBgn.fy-tmp[0].fy);
		
		grArc.InitArc(r2, ptC0, tmp[0], tmp[1]);
		m_grPath.AddArcNode(grArc, FALSE);

		grArc.GetArcMidpoint(tmp[0]);
		LineRevolve(line, tmp[0], ptC0, 0, (r1-r2)*2/3);
		m_grPath.DimensionAppendR(line.pt1, tmp[0], "R2");
		

		m_grPath.Offset(0, fTemp);
	}
	else if("020"==strName)
	{
		CGrArc grArc2;
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w, m_clip.Y1);
		
		fTemp = RetrieveAngleOfTriangle(r1, r1, w);
		LineRevolve(line, points[1], points[0], fTemp, r1);
		ptC0 = line.pt1;
		
		grArc.InitArc(r1, ptC0, points[0], points[1]);
		m_grPath.AddArcNode(grArc);
		
// 		LineRevolve(line, ptC0, grArc.m_ptArcEnd, grArc.m_fArc*3/4, r1);
// 		tmp[0] = line.pt1;
// 		LineRevolve(line, tmp[0], ptC0, 0, abs(r1-r2));
// 		m_grPath.DimensionAppendR(line.pt1, tmp[0], "R1");

		grArc.GetArcMidpoint(tmp[0]);
		//LineRevolve(line, tmp[0], ptC0, 0, tmp[0].fy);
// 		tmp[1].Set(tmp[0].fx, tmp[0].fy-fTemp);
// 		m_grPath.DimensionAppendR(tmp[1], tmp[0], "R1");
		tmp[1] = grArc.m_ptArcBgn;
		tmp[1].Offset(0, tmp[0].fy-grArc.m_ptArcBgn.fy);
		tmp[2] = grArc.m_ptArcEnd;
		tmp[2].Offset(0, tmp[0].fy-grArc.m_ptArcEnd.fy);
		m_grPath.DimensionAppendD(tmp[1], tmp[2], "W");
		
		ptC1.fx = r1-r2;
		if(ptC1.fx<0)
			ptC1.fx *= -1.0f;
		ptC1.Set(ptC0.fx, ptC0.fy-ptC1.fx);
		LineRevolve(line, ptC1, points[0], 0, r2);
		tmp[0] = line.pt1;
		LineRevolve(line, ptC1, points[1], 0, r2);
		tmp[1] = line.pt1;
		grArc2.InitArc(r2, ptC1, tmp[0], tmp[1]);
		m_grPath.AddArcNode(grArc2, FALSE);

// 		LineRevolve(line, points[0], ptC0, 0, (r1-r2));
// 		LineRevolve(line, points[1], ptC0, 0, (r1-r2));
// 		tmp[1] = line.pt1;
// 		
// 		fTemp = (grArc.m_ptArcBgn.fy-tmp[0].fy);
// 		
// 		grArc.InitArc(r2, ptC0, tmp[0], tmp[1]);
// 		m_grPath.AddArcNode(grArc, FALSE);
// 		
// 		grArc.GetArcMidpoint(tmp[0]);
// 		LineRevolve(line, tmp[0], ptC0, 0, (r1-r2)*2/3);
// 		m_grPath.DimensionAppendR(line.pt1, tmp[0], "R2");
		
		fTemp = grArc.m_ptArcBgn.fy-grArc2.m_ptArcBgn.fy;
		grArc.Offset(0, fTemp);
		grArc2.Offset(0, fTemp);
		m_grPath.Offset(0, fTemp);
		
		grArc.GetArcMidpoint(tmp[0]);
		tmp[0].fx=tmp[0].fx;
		fTemp = tmp[0].fy;
		LineRevolve(line, grArc.m_ptC0, grArc.m_ptArcEnd, grArc.m_fArc*3/4, r1);
		tmp[0] = line.pt1;
		LineRevolve(line, tmp[0], grArc.m_ptC0, 0, fTemp);
		m_grPath.DimensionAppendR(line.pt1, tmp[0], "R1");
		
		grArc2.GetArcMidpoint(tmp[0]);
		tmp[0].fx=tmp[0].fx;
		fTemp = tmp[0].fy;
		LineRevolve(line, grArc2.m_ptC0, grArc2.m_ptArcEnd, grArc2.m_fArc/4, r2);
		tmp[0] = line.pt1;
		LineRevolve(line, tmp[0], grArc2.m_ptC0, 0, fTemp);
		m_grPath.DimensionAppendR(line.pt1, tmp[0], "R2");
	}
	else if("021"==strName || "022"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+w);
		points[2].Set(m_clip.X1+h, m_clip.Y1+w);
		points[3].Set(m_clip.X1+h, m_clip.Y1+h);
		points[4].Set(m_clip.X1+w, m_clip.Y1+h);
		points[5].Set(m_clip.X1+w, m_clip.Y1);

		if("021"==strName)
			r1 = r2 = r;

		grArc.InitRoundCornerArc(r1, points[0], points[5], points[1]);
		m_grPath.AddArcNode(grArc);
		if("021"==strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R");
		else
		{
			grArc.GetArcMidpoint(tmp[0]);
			m_grPath.DimensionAppendR(points[0], tmp[0], "R1");
		}

		m_grPath.AddSharpNodes(&points[1], 1);

		m_grPath.AddSharpNodes(&points[2], 1);

		grArc.InitRoundCornerArc(r2, points[3], points[4], points[2]);
		m_grPath.AddArcNode(grArc, FALSE);
		if("021"!=strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, r2, -MATH_PI*3/4, "R2");

		m_grPath.AddSharpNodes(&points[4], 1);
		
		m_grPath.AddSharpNodes(&points[5], 1);

		m_grPath.DimensionAppendD(points[5], points[0], "W");
		m_grPath.DimensionAppendD(points[4], points[5], "H");
	}
	else if("023"==strName)
	{
		CGrPoint ptC2_1, ptC2_2;
		int i, count;
		double bottom1;

		fTemp = RetrieveAngleOfTriangle(r1+r2, r, r-r2);
		N = 3;

		ptC0.Set(m_clip.X1+r, m_clip.Y1+r);
		ptC1.Set(m_clip.X1+r, m_clip.Y1);
		LineRevolve(line, ptC0, ptC1, fTemp, r-r2);
		ptC2_1 = line.pt1;
		LineRevolve(line, ptC0, ptC1, -fTemp, r-r2);
		ptC2_2 = line.pt1;

		LineRevolve(line, ptC0, ptC2_1, 0, r);
		points[0] = line.pt1;
		LineRevolve(line, ptC2_1, ptC1, 0, r2);
		points[1] = line.pt1;
		LineRevolve(line, ptC2_2, ptC1, 0, r2);
		points[2] = line.pt1;
		LineRevolve(line, ptC0, ptC2_2, 0, r);
		points[3] = line.pt1;
		
		count = 0;
		bottom1 = ptC0.fy-r;
		do 
		{
			count++;

			grArc.InitArc(r2, ptC2_1, points[0], points[1]);
			m_grPath.AddArcNode(grArc, TRUE);
			if(1==count)
			{
				grArc.GetArcMidpoint(tmp[0]);
				m_grPath.DimensionAppendR(grArc.m_ptC0, tmp[0], "R2");
				bottom1 = grArc.m_ptC0.fy-r2;
			}
			grArc.InitArc(r1, ptC1, points[2], points[1]);
			m_grPath.AddArcNode(grArc, FALSE);
			if(1==count)
			{
				grArc.GetArcMidpoint(tmp[0]);
				m_grPath.DimensionAppendR(grArc.m_ptC0, tmp[0], "R1");
			}
			grArc.InitArc(r2, ptC2_2, points[2], points[3]);
			m_grPath.AddArcNode(grArc, TRUE);
			
			tmp[0] = points[3];
			
			LineRevolve(line, ptC0, ptC1, -(MATH_2PI/N), r);
			ptC1 = line.pt1;
			LineRevolve(line, ptC0, ptC2_1, -(MATH_2PI/N), r-r2);
			ptC2_1 = line.pt1;
			LineRevolve(line, ptC0, ptC2_2, -(MATH_2PI/N), r-r2);
			ptC2_2 = line.pt1;

			for(i=0; i<4; i++)
			{
				fTemp = GetDistanceF(ptC0, points[i]);
				LineRevolve(line, ptC0, points[i], -(MATH_2PI/N), fTemp);
				points[i] = line.pt1;
			}

			grArc.InitArc(r, ptC0, tmp[0], points[0]);
			m_grPath.AddArcNode(grArc, TRUE);
			if(N==count)
			{
				grArc.GetArcMidpoint(tmp[0]);
				m_grPath.DimensionAppendR(grArc.m_ptC0, tmp[0], "R");
			}
		} while (count<N);

		if(bottom1>m_clip.Y1)
			m_grPath.Offset(0, -(bottom1-m_clip.Y1));
	}
	else if("025"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		ptC0.Set(m_clip.X1+w/2, m_clip.Y1+h/2);

		grEllipse.InitEllipse(ptC0, w/2, h/2, MATH_2PI, 0);
		m_grPath.AddEllipseNode(grEllipse, TRUE);

		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[2], points[3], "H");
	}
	else if("026"==strName)
	{
// 		points[0].Set(m_clip.X1, m_clip.Y1);
// 		points[1].Set(m_clip.X1, m_clip.Y1+h);
// 		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
// 		points[3].Set(m_clip.X1+w, m_clip.Y1);
// 
// 		ptC0.Set(m_clip.X1+w/2, m_clip.Y1+h/2);
// 		grEllipse.InitEllipse(ptC0, w/2, h/2, MATH_2PI, 0);
// 
// 		ptC1.Set(m_clip.X1+w-r, m_clip.Y1+h/2);
// 
// 		double fArc, fD, fMinD, dx, dy;
// 		CGrPoint ptOfEllipse, ptCross;
// 		tmp[0].Set(m_clip.X1+w, m_clip.Y1+h/2);
// 		fMinD = r;
// 		for(fArc=MATH_PI; fArc>0; fArc-=(MATH_PI/10000.0f))
// 		{
// 			grEllipse.GetEllipsesPoint(ptOfEllipse, fArc);
// 			fD = GetDistanceF(ptOfEllipse, ptC1);
// 			fD -= r;
// 			if(fD<0)
// 				fD *= -1;
// 			if(fD<fMinD)
// 			{
// 				ptCross = ptOfEllipse;
// 				fMinD = fD;
// 			}
// 		}
// 
// 		dy = (ptCross.fy-ptC0.fy);
// 		dx = (ptCross.fx-ptC0.fx);
// 		if(dy>0 && dx>0)
// 		{
// 			tmp[0] = tmp[1] = tmp[2] = tmp[3] = ptCross;
// 			tmp[0].Offset(-(dx*2), -(dy*2));
// 			tmp[1].Offset(-(dx*2), 0);
// 			tmp[2].Offset(0, 0);
// 			tmp[3].Offset(0, -(dy*2));
// 			fArc = atan((ptCross.fy-ptC0.fy)/(ptCross.fx-ptC0.fx));
// 
// 			ptC1.Set(m_clip.X1+r, m_clip.Y1+h/2);
// 			grArc.InitArc(r, ptC1, tmp[0], tmp[1]);
// 			m_grPath.AddArcNode(grArc, TRUE);

// 			grEllipse.InitEllipse(ptC0, w/2, h/2, MATH_PI-fArc, fArc);
// 			m_grPath.AddEllipseNode(grEllipse, TRUE);
			
// 			ptC1.Set(m_clip.X1+w-r, m_clip.Y1+h/2);
// 			grArc.InitArc(r, ptC1, tmp[2], tmp[3]);
// 			m_grPath.AddArcNode(grArc, TRUE);

// 			grEllipse.InitEllipse(ptC0, w/2, h/2, (2*MATH_PI)-fArc, MATH_PI+fArc);
// 			m_grPath.AddEllipseNode(grEllipse, TRUE);
// 		}
	}
	else if("027"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		ptC0.Set(m_clip.X1+w/2, m_clip.Y1);
		
		grEllipse.InitEllipse(ptC0, w/2, h, MATH_PI, 0);
		m_grPath.AddEllipseNode(grEllipse, TRUE);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[2], points[3], "H");
	}
	else if("028"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		ptC0.Set(m_clip.X1, m_clip.Y1);

		m_grPath.AddSharpNodes(&ptC0, 1);
		
		grEllipse.InitEllipse(ptC0, w, h, MATH_PI/2, 0);
		m_grPath.AddEllipseNode(grEllipse, TRUE);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
	}
	else if("029"==strName)
	{
		r = h/2;
		points[0].Set(m_clip.X1+r, m_clip.Y1);
		points[1].Set(m_clip.X1+r, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w-r, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w-r, m_clip.Y1);
		ptC0.Set(m_clip.X1+r, m_clip.Y1+r);

		grArc.InitArc(r, ptC0, points[0], points[1]);
		m_grPath.AddArcNode(grArc);

		ptC0.Offset(w-(2*r), 0);
		grArc.InitArc(r, ptC0, points[2], points[3]);
		m_grPath.AddArcNode(grArc);

		tmp[0] = tmp[1] = points[0];
		tmp[0].Offset(-r, 0);
		tmp[1].Offset(w-r, 0);
		m_grPath.DimensionAppendD(tmp[1], tmp[0], "W");
		tmp[1] = points[0];
		tmp[1].Offset(-r, h);
		m_grPath.DimensionAppendD(tmp[0], tmp[1], "H");
	}
	else if("031"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w, m_clip.Y1);

		fTemp = RetrieveAngleOfTriangle(r2, r2, w);
		if(fTemp>0)
		{
			LineRevolve(line, points[1], points[0], fTemp, r2);
			ptC1 = line.pt1;

			grArc.InitArc(r2, ptC1, points[0], points[1]);
			m_grPath.AddArcNode(grArc);

			tmp[0] = grArc.m_ptC0;
			tmp[0].Offset(0, r2);
			tmp[1] = points[1];
			tmp[1].Offset(-w*0.4, 0);
			m_grPath.DimensionAppendR(tmp[1], tmp[0], "R2");

			grArc.GetArcMidpoint(tmp[0]);
			tmp[1] = tmp[0];
			tmp[0].Offset(-w/2, 0);
			tmp[1].Offset(w/2, 0);
			m_grPath.DimensionAppendD(tmp[0], tmp[1], "W");
		}

		fTemp = RetrieveAngleOfTriangle(r1, r1, w);
		if(fTemp>0)
		{
			LineRevolve(line, points[0], points[1], fTemp, r1);
			ptC0 = line.pt1;

			grArc.InitArc(r1, ptC0, points[1], points[0]);
			m_grPath.AddArcNode(grArc);
			
			tmp[0] = grArc.m_ptC0;
			tmp[0].Offset(0, -r1);
			tmp[1] = points[0];
			tmp[1].Offset(w*0.4, 0);
			m_grPath.DimensionAppendR(tmp[1], tmp[0], "R1");

			if(tmp[0].fy<m_clip.Y1)
				m_grPath.Offset(0, m_clip.Y1-tmp[0].fy);
		}
	}
	else if("033"==strName)
	{
		if(r2>r1)
		{
			double fArc2;

			h = sqrt((r2-r1)*(r2-r1) - (r2-(w/2))*(r2-(w/2)));
			h += r1;
			h *= 2;
			fArc2 = asin(((h/2)-r1)/(r2-r1));

			points[0].Set(m_clip.X1, m_clip.Y1);
			points[1].Set(m_clip.X1, m_clip.Y1+h);
			points[2].Set(m_clip.X1+w, m_clip.Y1+h);
			points[3].Set(m_clip.X1+w, m_clip.Y1);
			//m_grPath.AddSharpNodes(&points[0], 4);

			tmp[0].Set(m_clip.X1, m_clip.Y1+h/2);
			tmp[1].Set(m_clip.X1+w, m_clip.Y1+h/2);
			
			ptC0.Set(m_clip.X1+r2, m_clip.Y1+h/2);
			LineRevolve(line, ptC0, tmp[0], fArc2, r2);
			points[4] = line.pt1;
			LineRevolve(line, ptC0, tmp[0], -fArc2, r2);
			points[5] = line.pt1;
			ptC0.Set(m_clip.X1-(r2-w), m_clip.Y1+h/2);
			LineRevolve(line, ptC0, tmp[1], fArc2, r2);
			points[6] = line.pt1;
			LineRevolve(line, ptC0, tmp[1], -fArc2, r2);
			points[7] = line.pt1;
			//m_grPath.AddSharpNodes(&points[4], 4);

			ptC0.Set(m_clip.X1+r2, m_clip.Y1+h/2);
			grArc.InitArc(r2, ptC0, points[4], points[5]);
			m_grPath.AddArcNode(grArc, TRUE);
			grArc.GetArcMidpoint(tmp[0]);
			LineRevolve(line, tmp[0], ptC0, 0, w/3);
			m_grPath.DimensionAppendR(line.pt1, tmp[0], "R2");
			
			ptC0.Set(m_clip.X1+w/2, m_clip.Y1+h-r1);
			grArc.InitArc(r1, ptC0, points[5], points[6]);
			m_grPath.AddArcNode(grArc, TRUE);
			grArc.GetArcMidpoint(tmp[0]);
			LineRevolve(line, tmp[0], ptC0, 0, h/3);
			m_grPath.DimensionAppendR(line.pt1, tmp[0], "R1");
			
			ptC0.Set(m_clip.X1-(r2-w), m_clip.Y1+h/2);
			grArc.InitArc(r2, ptC0, points[6], points[7]);
			m_grPath.AddArcNode(grArc, TRUE);
			
			ptC0.Set(m_clip.X1+w/2, m_clip.Y1+r1);
			grArc.InitArc(r1, ptC0, points[7], points[4]);
			m_grPath.AddArcNode(grArc, TRUE);

			m_grPath.DimensionAppendD(points[3], points[0], "W");
		}
	}
	else if("034"==strName)
	{
		A = (A*MATH_PI/180);
		ptC0.Set(m_clip.X1, m_clip.Y1);
		
		if(r>w)
		{
			r1 = (r-w);
			points[1] = ptC0;
			points[1].Offset(r, 0);
			LineRevolve(line, ptC0, points[1], A, r);
			points[0] = line.pt1;
			grArc.InitArc(r, ptC0, points[0], points[1]);
			m_grPath.AddArcNode(grArc, FALSE);
			m_grPath.DimensionAppendD(points[1], ptC0, "R");

			points[2] = points[0];

			points[1] = ptC0;
			points[1].Offset(r1, 0);
			LineRevolve(line, ptC0, points[1], A, r1);
			points[0] = line.pt1;
			grArc.InitArc(r1, ptC0, points[0], points[1]);
			m_grPath.AddArcNode(grArc, TRUE);
			m_grPath.DimensionAppendD(points[0], points[2], "W");

			fTemp = (r-w)+(w/2);
			LineRevolve(line, ptC0, points[0], 0, fTemp);
			points[0] = line.pt1;
			LineRevolve(line, ptC0, points[1], 0, fTemp);
			points[1] = line.pt1;
			m_grPath.DimensionAppendA(ptC0, points[0], points[1], "A", A>MATH_PI);

			if(points[2].fx<ptC0.fx)
				m_grPath.Offset(ptC0.fx-points[2].fx, 0);
		}
	}
	else if("035"==strName)
	{
		r = (r*MATH_PI/180);	//r在这里表示角度

		points[0].Set(m_clip.X1, m_clip.Y1);
		points[3].Set(m_clip.X1+c, m_clip.Y1);
		LineRevolve(line, points[0], points[3], r, A);	//A在这里表示长度
		points[1] = line.pt1;
		fTemp = GetDistanceF(points[1], points[3]);
		fTemp = RetrieveAngleOfTriangle(d, b, fTemp);
		if(fTemp>0)
		{
			LineRevolve(line, points[1], points[3], fTemp, b);
			points[2] = line.pt1;

			fTemp = RetrieveAngleOfTriangle(r1, d, r1);
			if(fTemp>0)
			{
				LineRevolve(line, points[2], points[3], fTemp, r1);
				ptC0 = line.pt1;

				m_grPath.AddSharpNodes(&points[0], 1);
				m_grPath.AddSharpNodes(&points[1], 1);
				grArc.InitArc(r1, ptC0, points[3], points[2]);
				m_grPath.AddArcNode(grArc, FALSE);

				grArc.GetArcMidpoint(tmp[0]);
				LineRevolve(line, tmp[0], ptC0, 0, 8);//r1*2/3);
				tmp[1] = line.pt1;
				m_grPath.DimensionAppendR(tmp[1], tmp[0], "R1");

				m_grPath.DimensionAppendD(points[0], points[1], "A");
				m_grPath.DimensionAppendD(points[1], points[2], "B");
				m_grPath.DimensionAppendD(points[2], points[3], "D", 24);
				m_grPath.DimensionAppendD(points[3], points[0], "C");

				tmp[1].Set(m_clip.X1+c/3, m_clip.Y1);
				LineRevolve(line, points[0], points[1], 0, c/3);
				tmp[0] = line.pt1;
				m_grPath.DimensionAppendA(points[0], tmp[0], tmp[1], "R", r>MATH_PI);


				if(points[1].fx < points[0].fx)
					m_grPath.Offset(points[0].fx-points[1].fx, 0);
			}
		}
	}
	else if("257"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w-w1, m_clip.Y1);
		points[2].Set(m_clip.X1, m_clip.Y1+h-h1);
		points[3].Set(m_clip.X1, m_clip.Y1+h);
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(points, 4);

		if(w1<w && h1<h)
		{
			fTemp = sqrt(w*w + h*h);
			fTemp = RetrieveAngleOfTriangle(r1, r1, fTemp);
			LineRevolve(line, points[4], points[3], fTemp, r1);
			ptC0 = line.pt1;

			fTemp = sqrt((w-w1)*(w-w1) + (h-h1)*(h-h1));
			fTemp = RetrieveAngleOfTriangle(r2, r2, fTemp);
			LineRevolve(line, points[1], points[2], fTemp, r2);
			ptC1 = line.pt1;

			grArc.InitArc(r2, ptC1, points[2], points[1]);
			m_grPath.AddArcNode(grArc, FALSE);
			grArc.GetArcMidpoint(tmp[0]);
			LineRevolve(line, tmp[0], ptC1, 0, w-w1);
			m_grPath.DimensionAppendR(line.pt1, tmp[0], "R2");
			
			grArc.InitArc(r1, ptC0, points[3], points[4]);
			m_grPath.AddArcNode(grArc, TRUE);
			grArc.GetArcMidpoint(tmp[0]);
			LineRevolve(line, tmp[0], ptC1, 0, w1/2);
			m_grPath.DimensionAppendR(line.pt1, tmp[0], "R1");

			m_grPath.DimensionAppendD(points[4], points[0], "W");
			m_grPath.DimensionAppendD(points[1], points[4], "W1");
			m_grPath.DimensionAppendD(points[0], points[3], "H");
			m_grPath.DimensionAppendD(points[3], points[2], "H1");
		}
	}



	m_grPath.PaintTo(&m_dcGraph, &rcDrawing, GRAPH_COLOR_FR);
	
	//将图形由设备坐标系(Y轴向下)转换为数学平面直角坐标系(Y轴向上)
	ConvertGraphCoordinate(&m_dcGraph);
	
	Invalidate(TRUE);
}

void CGrEditor::ProcTriangle()
{
	CRect rect, rcDrawing;
	CString strName=m_picAttr.szPicName;
	GR_LINE line, lnTmp;
	CGrPoint pt, triPoints[3], tmp[3];
	double w, h, w1, w2, A, A1, A2, r, r1, r2, r3, d, g, g1;
	CGrArc grArc;
	
	//////////////////////////////////////////////////////////////////////////
	CUISetting *pSet = &m_uiSettings[m_picAttr.nIndex];
	w = pSet->GetValue("W");
	h = pSet->GetValue("H");
	w1 = pSet->GetValue("W1");
	w2 = pSet->GetValue("W2");
	A = (pSet->GetValue("A")*MATH_PI)/180;
	A1 = (pSet->GetValue("A1")*MATH_PI)/180;
	A2 = (pSet->GetValue("A2")*MATH_PI)/180;
	r = pSet->GetValue("R");
	r1 = pSet->GetValue("R1");
	r2 = pSet->GetValue("R2");
	r3 = pSet->GetValue("R3");
	d = pSet->GetValue("D");
	g = pSet->GetValue("G");
	g1 = pSet->GetValue("G1");
	//////////////////////////////////////////////////////////////////////////

	m_dcGraph.GetClipBox(&rect);
	rcDrawing=rect;
	rcDrawing.DeflateRect(32,32,32,32);	
	
	if("036"==strName)
	{
		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[2] = triPoints[0];
		triPoints[2].Offset(w, 0);
		LineRevolve(line, triPoints[0], triPoints[2], MATH_PI/3, w);
		triPoints[1] = line.pt1;

		m_grPath.AddSharpNodes(triPoints, 3);
		
		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "W");
	}
	else if("037"==strName)
	{
		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[2] = triPoints[0];
		triPoints[2].Offset(w, 0);
		triPoints[1] = triPoints[0];
		triPoints[1].Offset(0, h);

		m_grPath.AddSharpNodes(triPoints, 3);

		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "W");
		m_grPath.DimensionAppendD(triPoints[0], triPoints[1], "H");
	}
	else if("038"==strName)
	{
		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[2] = triPoints[0];
		triPoints[2].Offset(w, 0);
		triPoints[1] = triPoints[0];
		triPoints[1].Offset(w/2, h);
		
		m_grPath.AddSharpNodes(triPoints, 3);

		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "W");
		triPoints[1].Offset(-(w/2), 0);
		m_grPath.DimensionAppendD(triPoints[0], triPoints[1], "H");
	}
	else if("039"==strName)
	{
		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[2] = triPoints[0];
		triPoints[2].Offset(w, 0);
		triPoints[1] = triPoints[0];
		triPoints[1].Offset(w1, h);
		
		m_grPath.AddSharpNodes(triPoints, 3);

		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "W");
		triPoints[0].Offset(0, h);
		m_grPath.DimensionAppendD(triPoints[0], triPoints[1], "W1");
		triPoints[1].Offset(w-w1, 0);
		m_grPath.DimensionAppendD(triPoints[1], triPoints[2], "H");
	}
	else if("040"==strName)
	{
		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[1] = triPoints[0];
		triPoints[1].Offset(w, h);
		triPoints[2] = triPoints[0];
		triPoints[2].Offset(w1, 0);
		
		m_grPath.AddSharpNodes(triPoints, 3);

		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "W1");
		triPoints[2] = triPoints[0];
		triPoints[2].Offset(0, h);
		m_grPath.DimensionAppendD(triPoints[0], triPoints[2], "H");
		m_grPath.DimensionAppendD(triPoints[2], triPoints[1], "W");
	}
	else if("041"==strName)
	{
		double arc;
		arc = RetrieveAngleOfTriangle(w2, w, w1);

		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[2].Set(m_clip.X1+w, m_clip.Y1);
		LineRevolve(line, triPoints[0], triPoints[2], arc, w1);
		triPoints[1] = line.pt1;
		
		m_grPath.AddSharpNodes(triPoints, 3);
		
		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "W");
		m_grPath.DimensionAppendD(triPoints[0], triPoints[1], "W1");
		m_grPath.DimensionAppendD(triPoints[1], triPoints[2], "W2");

		if(triPoints[0].fx>triPoints[1].fx)
		{
			m_grPath.Offset((triPoints[0].fx-triPoints[1].fx), 0);
		}
	}
	else if("042"==strName)
	{
		double temp, tan1, tan2;
		tan1 = tan(A1);
		tan2 = tan(A2);
		temp = ((tan2*w)/(tan1+tan2));
		w1 = temp/cos(A1);

		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[2].Set(m_clip.X1+w, m_clip.Y1);
		LineRevolve(line, triPoints[0], triPoints[2], A1, w1);
		triPoints[1] = line.pt1;
		
		m_grPath.AddSharpNodes(triPoints, 3);

		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "W");

		temp = min(w, w1)/2;
		LineRevolve(line, triPoints[0], triPoints[1], 0, temp);
		tmp[0] = line.pt1;
		LineRevolve(line, triPoints[0], triPoints[2], 0, temp);
		tmp[1] = line.pt1;
		m_grPath.DimensionAppendA(triPoints[0], tmp[0], tmp[1], "A1", A1>MATH_PI);
		LineRevolve(line, triPoints[2], triPoints[0], 0, temp);
		tmp[0] = line.pt1;
		LineRevolve(line, triPoints[2], triPoints[1], 0, temp);
		tmp[1] = line.pt1;
		m_grPath.DimensionAppendA(triPoints[2], tmp[0], tmp[1], "A2", A2>MATH_PI);

		if(triPoints[0].fx>triPoints[1].fx)
		{
			m_grPath.Offset((triPoints[0].fx-triPoints[1].fx), 0);
		}
	}
	else if("043"==strName)
	{
		double temp;
		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[2].Set(m_clip.X1+w1, m_clip.Y1);
		LineRevolve(line, triPoints[0], triPoints[2], A, w2);
		triPoints[1] = line.pt1;
		
		m_grPath.AddSharpNodes(triPoints, 3);
		
		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "W1");
		m_grPath.DimensionAppendD(triPoints[0], triPoints[1], "W2");
		
		temp = min(w1, w2)/2;
		LineRevolve(line, triPoints[0], triPoints[1], 0, temp);
		tmp[0] = line.pt1;
		LineRevolve(line, triPoints[0], triPoints[2], 0, temp);
		tmp[1] = line.pt1;
		m_grPath.DimensionAppendA(triPoints[0], tmp[0], tmp[1], "A", A>MATH_PI);

		if(triPoints[0].fx>triPoints[1].fx)
		{
			m_grPath.Offset((triPoints[0].fx-triPoints[1].fx), 0);
		}
	}
	else if("044"==strName)
	{
		double arc;
		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[2].Set(m_clip.X1+w, m_clip.Y1);
		arc = RetrieveAngleOfTriangle(w1, w, w2);
		LineRevolve(line, triPoints[2], triPoints[0], -arc, w2);
		triPoints[1] = line.pt1;

		m_grPath.AddSharpNodes(triPoints, 2);
		
		tmp[0] = triPoints[2];
		tmp[0].Offset(-d, 0);
		LineRevolve(line, triPoints[2], tmp[0], -arc, d);
		tmp[1] = line.pt1;
		grArc.InitArc(d, triPoints[2], tmp[0], tmp[1]);
		m_grPath.AddArcNode(grArc, FALSE);
		
		m_grPath.DimensionAppendD(triPoints[2].fx, triPoints[2].fy, triPoints[2].fx-d, triPoints[2].fy, "D", 4);
		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "W");
		m_grPath.DimensionAppendD(triPoints[0], triPoints[1], "W1");
		m_grPath.DimensionAppendD(triPoints[1], triPoints[2], "W2");
		
		if(triPoints[0].fx>triPoints[1].fx)
		{
			m_grPath.Offset((triPoints[0].fx-triPoints[1].fx), 0);
		}
	}
	else if("045"==strName)
	{
		triPoints[0].Set(m_clip.X1+g1, m_clip.Y1);
		triPoints[1].Set(m_clip.X1, m_clip.Y1+h);
		triPoints[2].Set(m_clip.X1+g+g1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(triPoints, 3);

		pt.Set(m_clip.X1, m_clip.Y1);
		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "G");
		m_grPath.DimensionAppendD(triPoints[0], pt, "G1");
		m_grPath.DimensionAppendD(pt, triPoints[1], "H");
	}
	else if("046"==strName || "047"==strName)
	{
		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[2].Set(m_clip.X1+w, m_clip.Y1);
		LineRevolve(line, triPoints[0], triPoints[2], (MATH_PI/3), w);
		triPoints[1] = line.pt1;
		if("046"==strName)
			r1 = r2 = r3 = r;

		grArc.InitRoundCornerArc(r1, triPoints[0], triPoints[2], triPoints[1]);
		m_grPath.AddRoundAngleNode(triPoints[0], grArc);

		if("046"==strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, MATH_PI+(MATH_PI/6), "R");
		else
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, MATH_PI+(MATH_PI/6), "R1");
		
		grArc.InitRoundCornerArc(r3, triPoints[1], triPoints[0], triPoints[2]);
		m_grPath.AddRoundAngleNode(triPoints[1], grArc);
		if("046"!=strName)
		{
			m_grPath.DimensionAppendR(grArc.m_ptC0, r3, MATH_PI/2, "R3");
		}
		
		grArc.InitRoundCornerArc(r2, triPoints[2], triPoints[1], triPoints[0]);
		m_grPath.AddRoundAngleNode(triPoints[2], grArc);
		if("046"!=strName)
		{
			m_grPath.DimensionAppendR(grArc.m_ptC0, r2, -MATH_PI/6, "R2");
		}

		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "W");
	}
	else if("048"==strName || "049"==strName)
	{
		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[1].Set(m_clip.X1, m_clip.Y1+h);
		triPoints[2].Set(m_clip.X1+w, m_clip.Y1);
		if("048"==strName)	
		{
			r1 = r2 = r3 = r;
		}

		grArc.InitRoundCornerArc(r1, triPoints[0], triPoints[2], triPoints[1]);
		m_grPath.AddRoundAngleNode(triPoints[0], grArc);
		if("048"==strName)	
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R");
		else
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R1");
		
		grArc.InitRoundCornerArc(r3, triPoints[1], triPoints[0], triPoints[2]);
		m_grPath.AddRoundAngleNode(triPoints[1], grArc);
		if("048"!=strName)	
		{
			LineRevolve(line, grArc.m_ptC0, triPoints[1], 0, r3);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R3");
		}
		
		grArc.InitRoundCornerArc(r2, triPoints[2], triPoints[1], triPoints[0]);
		m_grPath.AddRoundAngleNode(triPoints[2], grArc);
		if("048"!=strName)	
		{
			LineRevolve(line, grArc.m_ptC0, triPoints[2], 0, r2);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R2");
		}
		
		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "W");
		m_grPath.DimensionAppendD(triPoints[0], triPoints[1], "H");
	}
	else if("050"==strName || "051"==strName)
	{
		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[1].Set(m_clip.X1+(w/2), m_clip.Y1+h);
		triPoints[2].Set(m_clip.X1+w, m_clip.Y1);
		if("050"==strName)
			r1 = r2 = r3 = r;
		
		grArc.InitRoundCornerArc(r1, triPoints[0], triPoints[2], triPoints[1]);
		m_grPath.AddRoundAngleNode(triPoints[0], grArc);
		LineRevolve(line, grArc.m_ptC0, triPoints[0], 0, r1);
		if("050"==strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R");
		else
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R1");
		
		grArc.InitRoundCornerArc(r3, triPoints[1], triPoints[0], triPoints[2]);
		m_grPath.AddRoundAngleNode(triPoints[1], grArc);
		if("050"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, triPoints[1], 0, r3);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R3");
		}
		
		grArc.InitRoundCornerArc(r2, triPoints[2], triPoints[1], triPoints[0]);
		m_grPath.AddRoundAngleNode(triPoints[2], grArc);
		if("050"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, triPoints[2], 0, r2);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R2");
		}
		
		triPoints[1].Offset(-(w/2), 0);
		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "W");
		m_grPath.DimensionAppendD(triPoints[0], triPoints[1], "H");
	}
	else if("052"==strName || "053"==strName)
	{
		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		triPoints[2].Set(m_clip.X1+w, m_clip.Y1);
		if("052"==strName)
			r1 = r2 = r3 = r;

		grArc.InitRoundCornerArc(r1, triPoints[0], triPoints[2], triPoints[1]);
		m_grPath.AddRoundAngleNode(triPoints[0], grArc);
		LineRevolve(line, grArc.m_ptC0, triPoints[0], 0, r1);
		if("052"==strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R");
		else
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R1");
		
		grArc.InitRoundCornerArc(r3, triPoints[1], triPoints[0], triPoints[2]);
		m_grPath.AddRoundAngleNode(triPoints[1], grArc);
		if(r3!=r1)
		{
			LineRevolve(line, grArc.m_ptC0, triPoints[1], 0, r3);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R3");
		}
		
		grArc.InitRoundCornerArc(r2, triPoints[2], triPoints[1], triPoints[0]);
		m_grPath.AddRoundAngleNode(triPoints[2], grArc);
		if(r2!=r1)
		{
			LineRevolve(line, grArc.m_ptC0, triPoints[2], 0, r2);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R2");
		}
		
		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "W");
		triPoints[0].Offset(0, h);
		m_grPath.DimensionAppendD(triPoints[0], triPoints[1], "W1");
		triPoints[1].Offset(w-w1, 0);
		m_grPath.DimensionAppendD(triPoints[1], triPoints[2], "H");
	}
	else if("054"==strName || "055"==strName)
	{
		double fTemp;
		CGrPoint ptArc3Mid;

		if("054"==strName)
			w1 = (w/2);

		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		triPoints[2].Set(m_clip.X1+w, m_clip.Y1);

		fTemp = GetDistanceF(triPoints[0], triPoints[1]);
		fTemp = RetrieveAngleOfTriangle(r1, r1, fTemp);
		LineRevolve(line, triPoints[1], triPoints[0], fTemp, r1);
		grArc.InitArc(r1, line.pt1, triPoints[0], triPoints[1]);
		m_grPath.AddArcNode(grArc, TRUE);
		grArc.GetArcMidpoint(tmp[0]);
		LineRevolve(line, tmp[0], grArc.m_ptC0, 0, w/4);
		m_grPath.DimensionAppendR(line.pt1, tmp[0], "R1");
		
		fTemp = GetDistanceF(triPoints[1], triPoints[2]);
		fTemp = RetrieveAngleOfTriangle(r2, r2, fTemp);
		LineRevolve(line, triPoints[2], triPoints[1], fTemp, r2);
		grArc.InitArc(r2, line.pt1, triPoints[1], triPoints[2]);
		m_grPath.AddArcNode(grArc, TRUE);
		grArc.GetArcMidpoint(tmp[0]);
		LineRevolve(line, tmp[0], grArc.m_ptC0, 0, w/4);
		m_grPath.DimensionAppendR(line.pt1, tmp[0], "R2");
		
		fTemp = GetDistanceF(triPoints[2], triPoints[0]);
		fTemp = RetrieveAngleOfTriangle(r3, r3, fTemp);
		LineRevolve(line, triPoints[0], triPoints[2], fTemp, r3);
		grArc.InitArc(r3, line.pt1, triPoints[2], triPoints[0]);
		m_grPath.AddArcNode(grArc, TRUE);
		//grArc.GetArcMidpoint(ptArc3Mid);
		ptArc3Mid = grArc.m_ptC0;
		ptArc3Mid.Offset(0, -r3);
		LineRevolve(line, ptArc3Mid, grArc.m_ptC0, 0, w/4);
		m_grPath.DimensionAppendR(line.pt1, ptArc3Mid, "R3");

		tmp[0].Set(triPoints[2].fx, ptArc3Mid.fy);
		tmp[1].Set(triPoints[0].fx, ptArc3Mid.fy);
		m_grPath.DimensionAppendD(tmp[0], tmp[1], "W");
		tmp[2] = triPoints[0];
		tmp[2].Offset(0, h);
		m_grPath.DimensionAppendD(triPoints[0], tmp[2], "H");
		if("055"==strName)
			m_grPath.DimensionAppendD(tmp[2], triPoints[1], "W1");


		if(ptArc3Mid.fy < triPoints[0].fy)
			m_grPath.Offset(0, (triPoints[0].fy-ptArc3Mid.fy));
	}	
	else if("056"==strName)
	{
		CGrPoint pt4;
		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		triPoints[2].Set(m_clip.X1+w, m_clip.Y1);
		pt4.Set(m_clip.X1+w+w1, m_clip.Y1+h);

		m_grPath.AddSharpNodes(&triPoints[2], 1);
		m_grPath.AddSharpNodes(&triPoints[0], 1);
		m_grPath.AddSharpNodes(&triPoints[1], 1);
		m_grPath.AddSharpNodes(&pt4, 1);

		m_grPath.AddSplitNode(triPoints[2]);
		m_grPath.AddSplitNode(triPoints[1]);

		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "W");
		tmp[0] = triPoints[0];
		tmp[0].Offset(0, h);
		m_grPath.DimensionAppendD(triPoints[0], tmp[0], "H");
		m_grPath.DimensionAppendD(tmp[0], triPoints[1], "W1");
	}
	else if("057"==strName)
	{
		CGrPoint pt4;
		double fTemp;
		triPoints[0].Set(m_clip.X1, m_clip.Y1);
		triPoints[2].Set(m_clip.X1+w, m_clip.Y1);
		fTemp = RetrieveAngleOfTriangle(w2, w, w1);
		LineRevolve(line, triPoints[0], triPoints[2], fTemp, w1);
		triPoints[1] = line.pt1;
		pt4 = triPoints[1];
		pt4.Offset(w, 0);
		
		m_grPath.AddSharpNodes(&triPoints[2], 1);
		m_grPath.AddSharpNodes(&triPoints[0], 1);
		m_grPath.AddSharpNodes(&triPoints[1], 1);
		m_grPath.AddSharpNodes(&pt4, 1);
		
		m_grPath.AddSplitNode(triPoints[2]);
		m_grPath.AddSplitNode(triPoints[1]);

		m_grPath.DimensionAppendD(triPoints[2], triPoints[0], "W");
		m_grPath.DimensionAppendD(triPoints[0], triPoints[1], "W1");
		m_grPath.DimensionAppendD(triPoints[1], triPoints[2], "W2");
	}
		
		
		
	m_grPath.PaintTo(&m_dcGraph, &rcDrawing, GRAPH_COLOR_FR);
	
	//将图形由设备坐标系(Y轴向下)转换为数学平面直角坐标系(Y轴向上)
	ConvertGraphCoordinate(&m_dcGraph);
	
	Invalidate(TRUE);
}

//处理矩形
void CGrEditor::ProcRectangle()
{
	GR_NODE grNode;
	double temp;
	CRect rect, rcDrawing;
	CString strName=m_picAttr.szPicName;
	CGrPoint points[8], tmp;
	GR_LINE line;
	
	//////////////////////////////////////////////////////////////////////////
	CUISetting *pSet = &m_uiSettings[m_picAttr.nIndex];
	double w = pSet->GetValue("W");
	double h = pSet->GetValue("H");
	double w1 = pSet->GetValue("W1");
	double w2 = pSet->GetValue("W2");
	double w3 = pSet->GetValue("W3");
	double w4 = pSet->GetValue("W4");
	double h1 = pSet->GetValue("H1");
	double h2 = pSet->GetValue("H2");
	double h3 = pSet->GetValue("H3");
	double A = (pSet->GetValue("A")*MATH_PI)/180;
	double A1 = (pSet->GetValue("A1")*MATH_PI)/180;
	double A2 = (pSet->GetValue("A2")*MATH_PI)/180;
	double s1 = pSet->GetValue("S1");
	double s2 = pSet->GetValue("S2");
	double d = pSet->GetValue("D");
	double d1 = pSet->GetValue("D1");
	double d2 = pSet->GetValue("D2");
	double l = pSet->GetValue("L");
	double l1 = pSet->GetValue("L1");
	double l2 = pSet->GetValue("L2");
	//////////////////////////////////////////////////////////////////////////
	
	
	m_dcGraph.GetClipBox(&rect);
	rcDrawing=rect;
	rcDrawing.DeflateRect(32,32,32,32);
	
	
	memset(&grNode, 0, sizeof(GR_NODE));


	if("059"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1] = points[0];
		points[1].Offset(0, h);
		points[2] = points[1];
		points[2].Offset(w, 0);
		points[3] = points[0];
		points[3].Offset(w, 0);

		m_grPath.AddSharpNodes(points, 4);

		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
	}
	else if("060"==strName)
	{
		grNode.nNodeType = GNT_SHARP_ANGLE;

		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1] = points[0];
		points[1].Offset(0, h);
		points[2] = points[1];
		points[2].Offset(w, -(h-h1));
		points[3] = points[2];
		points[3].Offset(0, -h1);

		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
		m_grPath.DimensionAppendD(points[2], points[3], "H1");
	}
	else if("061"==strName)
	{
		grNode.nNodeType = GNT_SHARP_ANGLE;
		
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1] = points[0];
		points[1].Offset((w-w1)/2, h);
		points[2] = points[1];
		points[2].Offset(w1, 0);
		points[3] = points[2];
		points[3].Offset((w-w1)/2, -h);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp = points[0];
		tmp.Offset(0, h);
		m_grPath.DimensionAppendD(points[0], tmp, "H");
		m_grPath.DimensionAppendD(points[1], points[2], "W1");
	}
	else if("062"==strName)
	{		
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1] = points[0];
		points[1].Offset(w2, h);
		points[2] = points[1];
		points[2].Offset((w-w1), 0);
		points[3] = points[2];
		points[3].Offset(w1, -h);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp = points[0];
		tmp.Offset(0, h);
		m_grPath.DimensionAppendD(points[0], tmp, "H");
		m_grPath.DimensionAppendD(tmp, points[1], "W2");
		tmp = points[3];
		tmp.Offset(0, h);
		m_grPath.DimensionAppendD(points[2], tmp, "W1");
	}
	else if("063"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1] = points[0];
		points[1].Offset(w1, h);
		points[2] = points[1];
		points[2].Offset((w-w1), 0);
		points[3] = points[2];
		points[3].Offset(-(w-w1), -h);
		
		m_grPath.AddSharpNodes(points, 4);
			
		tmp = points[0];
		tmp.Offset(w, 0);
		m_grPath.DimensionAppendD(tmp, points[0], "W");
		tmp = points[0];
		tmp.Offset(0, h);
		m_grPath.DimensionAppendD(points[0], tmp, "H");
		m_grPath.DimensionAppendD(tmp, points[1], "W1");
	}
	else if("064"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1] = points[0];
		points[1].Offset(w1, h);
		points[2] = points[1];
		points[2].Offset(w, 0);
		points[3] = points[2];
		points[3].Offset(-w1, -h);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp = points[0];
		tmp.Offset(0, h);
		m_grPath.DimensionAppendD(points[0], tmp, "H");
		m_grPath.DimensionAppendD(tmp, points[1], "W1");
	}
	else if("065"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1] = points[0];
		points[1].Offset(w1, h);
		points[2] = points[1];
		points[2].Offset((w+w2-w1), 0);
		points[3] = points[2];
		points[3].Offset(-w2, -h);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp = points[0];
		tmp.Offset(0, h);
		m_grPath.DimensionAppendD(tmp, points[1], "W1");
		tmp = points[3];
		tmp.Offset(w2, 0);
		m_grPath.DimensionAppendD(tmp, points[3], "W2");
		m_grPath.DimensionAppendD(points[2], tmp, "H");
	}
	else if("066"==strName)
	{
		points[1].Set(m_clip.X1, m_clip.Y1);
		points[3].Set(m_clip.X1+10, m_clip.Y1);	//假设
		LineRevolve(line, points[1], points[3], -(MATH_PI/4), w);
		points[0] = line.pt1;
		points[1].Offset(0, -points[0].fy+m_clip.Y1);
		points[0].Offset(0, -points[0].fy+m_clip.Y1);
		LineRevolve(line, points[1], points[0], (MATH_PI/2), w);
		points[2] = line.pt1;
		LineRevolve(line, points[2], points[1], (MATH_PI/2), w);
		points[3] = line.pt1;
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
	}
	else if("067"==strName)
	{
		points[1].Set(m_clip.X1, m_clip.Y1);
		points[3].Set(m_clip.X1+10, m_clip.Y1);	//假设
		LineRevolve(line, points[1], points[3], -((MATH_PI-A)/2), w);
		points[0] = line.pt1;
		points[1].Offset(0, -points[0].fy+m_clip.Y1);
		points[0].Offset(0, -points[0].fy+m_clip.Y1);
		LineRevolve(line, points[1], points[0], (MATH_PI-A), w);
		points[2] = line.pt1;
		LineRevolve(line, points[2], points[1], A, w);
		points[3] = line.pt1;
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		LineRevolve(line, points[0], points[1], 0, w/2);
		tmp = line.pt1;
		LineRevolve(line, points[0], points[3], 0, w/2);
		m_grPath.DimensionAppendA(points[0], tmp, line.pt1, "A", A>MATH_PI);
	}
	else if("068"==strName)
	{		
		points[0].Set(m_clip.X1, m_clip.Y1+(h/2));
		points[1].Set(m_clip.X1+(w/2), m_clip.Y1+(h));
		points[2].Set(m_clip.X1+(w), m_clip.Y1+(h/2));
		points[3].Set(m_clip.X1+(w/2), m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 4);
		
		points[2].Offset(0, -(h/2));
		points[0].Offset(0, -(h/2));
		m_grPath.DimensionAppendD(points[2], points[0], "W");
		points[1].Offset(w/2, 0);
		points[3].Offset(w/2, 0);
		m_grPath.DimensionAppendD(points[1], points[3], "H");
	}
	else if("069"==strName)
	{		
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+(h1));
		points[2].Set(m_clip.X1+(w1), m_clip.Y1+(h));
		points[3].Set(m_clip.X1+(w), m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H1");
		tmp = points[1];
		tmp.Offset(0, h-h1);
		m_grPath.DimensionAppendD(tmp, points[2], "W1");
		tmp = points[2];
		tmp.Offset(w-w1, 0);
		m_grPath.DimensionAppendD(tmp, points[3], "H");
	}
	else if("070"==strName)
	{		
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+(h));
		points[2].Set(m_clip.X1+(w), m_clip.Y1+(h1));
		points[3].Set(m_clip.X1+(w1), m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W1");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
		tmp = points[1];
		tmp.Offset(w, 0);
		m_grPath.DimensionAppendD(points[1], tmp, "W");
		tmp.Offset(0, -(h-h1));
		points[3].Offset(w-w1, 0);
		m_grPath.DimensionAppendD(tmp, points[3], "H1");
	}
	else if("071"==strName)
	{		
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+(h));
		points[2].Set(m_clip.X1+(w1), m_clip.Y1+(h1));
		points[3].Set(m_clip.X1+(w), m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
		tmp = points[1];
		tmp.Offset(w1, 0);
		m_grPath.DimensionAppendD(points[1], tmp, "W1");
		tmp = points[3];
		tmp.Offset(0, h1);
		m_grPath.DimensionAppendD(tmp, points[3], "H1");
	}
	else if("072"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+(h));
		points[3].Set(m_clip.X1+(w), m_clip.Y1);
		temp = sqrt(w*w+h*h);
		temp = RetrieveAngleOfTriangle(s2, temp, s1);
		LineRevolve(line, points[1], points[3], temp, s1);
		points[2] = line.pt1;
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
		m_grPath.DimensionAppendD(points[1], points[2], "S1");
		m_grPath.DimensionAppendD(points[2], points[3], "S2");
	}
	else if("073"==strName)
	{
		points[0].Set(m_clip.X1+(w-w1), m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+(h));
		points[2].Set(m_clip.X1+w, m_clip.Y1+(h1));
		points[3].Set(m_clip.X1+(w), m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W1");
		tmp.Set(m_clip.X1, m_clip.Y1);
		m_grPath.DimensionAppendD(tmp, points[1], "H");
		tmp = points[1];
		tmp.Offset(w, 0);
		m_grPath.DimensionAppendD(points[1], tmp, "W");
		m_grPath.DimensionAppendD(points[2], points[3], "H1");
	}
	else if("074"==strName)
	{
		double arc;
	
		if(w1>w3)
		{
			temp = (w1-w3);
			points[0].Set(m_clip.X1, m_clip.Y1);
			points[3].Set(m_clip.X1+(temp), m_clip.Y1);
			arc = RetrieveAngleOfTriangle(w4, temp, w2);
			LineRevolve(line, points[0], points[3], arc, w2);
			points[2] = points[1] = line.pt1;

			points[2].Offset(w3, 0);
			points[3].Offset(w3, 0);
		}
		else if(w1<w3)
		{
			temp = (w3-w1);
			points[1].Set(m_clip.X1, m_clip.Y1);
			points[2].Set(m_clip.X1+(temp), m_clip.Y1);
			arc = RetrieveAngleOfTriangle(w2, temp, w4);
			LineRevolve(line, points[2], points[1], arc, w4);
			points[3] = points[0] = line.pt1;
			
			points[2].Offset(w3, 0);
			points[3].Offset(w3, 0);

			temp = points[1].fy-points[0].fy;
			points[0].Offset(0, temp);
			points[1].Offset(0, temp);
			points[2].Offset(0, temp);
			points[3].Offset(0, temp);
		}
		else //if(w1==w3)
		{
			if(w2!=w4)
			{
				AfxMessageBox("参数错误：当W1==W3时，必须W2==W4!", MB_OK|MB_ICONERROR);
				return;
			}
			points[0].Set(m_clip.X1, m_clip.Y1);
			points[1].Set(m_clip.X1, m_clip.Y1+(w2));
			points[2].Set(m_clip.X1+w1, m_clip.Y1+(w4));
			points[3].Set(m_clip.X1+(w1), m_clip.Y1);
		}
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W1");
		m_grPath.DimensionAppendD(points[0], points[1], "W2");
		m_grPath.DimensionAppendD(points[1], points[2], "W3");
		m_grPath.DimensionAppendD(points[2], points[3], "W4");
		
		if(points[0].fx > points[1].fx)
		{
			m_grPath.Offset((points[0].fx-points[1].fx), 0);
		}
	}
	else if("075"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h1);
		points[2].Set(m_clip.X1+w1+w2, m_clip.Y1+h);
		points[3] = points[0];
		points[3].Offset(w, 0);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp = points[0];
		tmp.Offset(0, h1);
		m_grPath.DimensionAppendD(points[0], tmp, "H1");
		tmp.Offset(0, h-h1);
		points[1].Offset(0, h-h1);
		m_grPath.DimensionAppendD(tmp, points[1], "W1");
		m_grPath.DimensionAppendD(points[1], points[2], "W2");
		tmp = points[3];
		tmp.Offset(0, h);
		m_grPath.DimensionAppendD(tmp, points[3], "H");
	}
	else if("076"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w1+w2, m_clip.Y1+h);
		points[3] = points[0];
		points[3].Offset(w, 0);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp = points[0];
		tmp.Offset(0, h);
		m_grPath.DimensionAppendD(points[0], tmp, "H");
		m_grPath.DimensionAppendD(tmp, points[1], "w1");
		m_grPath.DimensionAppendD(points[1], points[2], "w2");
	}
	else if("077"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[3] = points[0];
		points[3].Offset(w, 0);
		LineRevolve(line, points[0], points[3], A1, h1);
		points[1] = line.pt1;
		LineRevolve(line, points[3], points[0], -A2, h2);
		points[2] = line.pt1;
		
		m_grPath.AddSharpNodes(points, 4);

		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H1");
		m_grPath.DimensionAppendD(points[2], points[3], "H2");

		LineRevolve(line, points[0], points[1], 0, min(w,h1)/3);
		tmp = line.pt1;
		LineRevolve(line, points[0], points[3], 0, min(w,h1)/3);
		m_grPath.DimensionAppendA(points[0], tmp, line.pt1, "A1", A1>MATH_PI);
		
		LineRevolve(line, points[3], points[0], 0, min(w,h2)/3);
		tmp = line.pt1;
		LineRevolve(line, points[3], points[2], 0, min(w,h2)/3);
		m_grPath.DimensionAppendA(points[3], tmp, line.pt1, "A2", A2>MATH_PI);
		

		if(points[0].fx > points[1].fx)
		{
			m_grPath.Offset((points[0].fx-points[1].fx), 0);
		}
	}
	else if("078"==strName)
	{
		points[0].Set(m_clip.X1+w1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h1);
		points[2].Set(m_clip.X1+w1+w+w2, m_clip.Y1+h2);
		points[3] = points[0];
		points[3].Offset(w, 0);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp = points[0];
		tmp.Offset(-w1, 0);
		m_grPath.DimensionAppendD(points[0], tmp, "W1");
		m_grPath.DimensionAppendD(tmp, points[1], "H1");
		tmp = points[3];
		tmp.Offset(w2, 0);
		m_grPath.DimensionAppendD(tmp, points[3], "W2");
		m_grPath.DimensionAppendD(points[2], tmp, "H2");
	}
	else if("079"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h1);
		points[2].Set(m_clip.X1+(w-w2), m_clip.Y1+h2);
		points[3] = points[0];
		points[3].Offset(w, 0);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp = points[1];
		tmp.Offset(-w1, 0);
		m_grPath.DimensionAppendD(points[0], tmp, "H1");
		m_grPath.DimensionAppendD(tmp, points[1], "W1");
		tmp = points[2];
		tmp.Offset(w2, 0);
		m_grPath.DimensionAppendD(points[2], tmp, "W2");
		m_grPath.DimensionAppendD(tmp, points[3], "H2");
	}
	else if("080"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h1);
		points[2].Set(m_clip.X1+(w+w2), m_clip.Y1+h2);
		points[3] = points[0];
		points[3].Offset(w, 0);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp = points[1];
		tmp.Offset(-w1, 0);
		m_grPath.DimensionAppendD(points[0], tmp, "H1");
		m_grPath.DimensionAppendD(tmp, points[1], "W1");
		tmp = points[3];
		tmp.Offset(w2, 0);
		m_grPath.DimensionAppendD(tmp, points[3], "W2");
		m_grPath.DimensionAppendD(points[2], tmp, "H2");
	}
	else if("081"==strName)
	{
		points[0].Set(m_clip.X1+w1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h1);
		points[2].Set(m_clip.X1+w1+(w-w2), m_clip.Y1+h2);
		points[3] = points[0];
		points[3].Offset(w, 0);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp = points[0];
		tmp.Offset(-w1, 0);
		m_grPath.DimensionAppendD(points[0], tmp, "W1");
		m_grPath.DimensionAppendD(tmp, points[1], "H1");
		tmp = points[2];
		tmp.Offset(w2, 0);
		m_grPath.DimensionAppendD(points[2], tmp, "W2");
		m_grPath.DimensionAppendD(tmp, points[3], "H2");
	}
	else if("082"==strName)
	{
		points[0].Set(m_clip.X1+w1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[3] = points[0];
		points[3].Offset(w, 0);
		temp = GetDistanceF(points[1], points[3]);
		temp = RetrieveAngleOfTriangle(s2, temp, s1);
		LineRevolve(line, points[1], points[3], temp, s1);
		points[2] = line.pt1;
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp = points[0];
		tmp.Offset(-w1, 0);
		m_grPath.DimensionAppendD(points[0], tmp, "W1");
		m_grPath.DimensionAppendD(tmp, points[1], "H");
		m_grPath.DimensionAppendD(points[1], points[2], "S1");
		m_grPath.DimensionAppendD(points[2], points[3], "S2");
	}
	else if("083"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[3] = points[0];
		points[3].Offset(w, 0);
		temp = GetDistanceF(points[1], points[3]);
		temp = RetrieveAngleOfTriangle(s2, temp, s1);
		LineRevolve(line, points[1], points[3], temp, s1);
		points[2] = line.pt1;
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp = points[1];
		tmp.Offset(-w1, 0);
		m_grPath.DimensionAppendD(points[0], tmp, "H");
		m_grPath.DimensionAppendD(tmp, points[1], "W1");
		m_grPath.DimensionAppendD(points[1], points[2], "S1");
		m_grPath.DimensionAppendD(points[2], points[3], "S2");
	}
	else if("084"==strName)
	{
		points[0].Set(m_clip.X1+w1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w2, m_clip.Y1);
		points[2] = points[3];
		points[2].Offset(w-w2, h1);
		
		m_grPath.AddSharpNodes(points, 4);
		
		tmp = points[0];
		tmp.Offset(-w1, 0);
		m_grPath.DimensionAppendD(points[3], tmp, "W2", 24);
		m_grPath.DimensionAppendD(points[0], tmp, "W1", 4);
		m_grPath.DimensionAppendD(tmp, points[1], "H");
		tmp = points[1];
		tmp.Offset(w, 0);
 		m_grPath.DimensionAppendD(points[1], tmp, "W");
		tmp = points[2];
		tmp.Offset(0, -h1);
		m_grPath.DimensionAppendD(points[2], tmp, "H1");
	}
	else if("085"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w2, m_clip.Y1);
		points[2] = points[3];
		points[2].Offset(w-w2, h1);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W2", 8);
		tmp = points[1];
		tmp.Offset(-w1, 0);
		m_grPath.DimensionAppendD(points[0], tmp, "H");
		m_grPath.DimensionAppendD(tmp, points[1], "W1");
		tmp = points[0];
		tmp.Offset(w, 0);
		m_grPath.DimensionAppendD(tmp, points[0], "W", 24);
		m_grPath.DimensionAppendD(points[2], tmp, "H1");
	}
	else if("086"==strName)
	{
		points[0].Set(m_clip.X1+w2, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w1, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w2+w, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 4);
		
		tmp = points[0];
		tmp.Offset(-w2, 0);
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], tmp, "W2");
		m_grPath.DimensionAppendD(tmp, points[1], "H");
		tmp.Offset(0, h1);
		m_grPath.DimensionAppendD(tmp, points[2], "W1");
		tmp.Offset(w2+w, 0);
		m_grPath.DimensionAppendD(tmp, points[3], "H1");
	}
	else if("087"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w2, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w-w1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 4);
		
		tmp = points[1];
		tmp.Offset(-w2, 0);
		m_grPath.DimensionAppendD(points[0], tmp, "H");
		m_grPath.DimensionAppendD(tmp, points[1], "W2");
		tmp = points[3];
		tmp.Offset(w1, 0);
		m_grPath.DimensionAppendD(tmp, points[3], "W1", 4);
		m_grPath.DimensionAppendD(tmp, points[0], "W", 24);
		m_grPath.DimensionAppendD(points[2], tmp, "H1");
	}
	else if("088"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[3].Set(m_clip.X1+w4, m_clip.Y1);
		LineRevolve(line, points[0], points[3], A, w1);
		points[1] = line.pt1;
		temp = sqrt(w1*w1+w4*w4-(2*cos(A)*w1*w4));
		if(temp>=0.0f)
		{
			temp = RetrieveAngleOfTriangle(w3, temp, w2);
			LineRevolve(line, points[1], points[3], temp, w2);
			points[2] = line.pt1;
			
			m_grPath.AddSharpNodes(points, 4);
			
			m_grPath.DimensionAppendD(points[0], points[1], "W1");
			m_grPath.DimensionAppendD(points[1], points[2], "W2");
			m_grPath.DimensionAppendD(points[2], points[3], "W3");
			m_grPath.DimensionAppendD(points[3], points[0], "W4");
			
			LineRevolve(line, points[0], points[1], 0, min(w4,w1)/3);
			tmp = line.pt1;
			LineRevolve(line, points[0], points[3], 0, min(w4,w1)/3);
			m_grPath.DimensionAppendA(points[0], tmp, line.pt1, "A", A>MATH_PI);
			
			if(points[0].fx > points[1].fx)
			{
				m_grPath.Offset((points[0].fx-points[1].fx), 0);
			}
		}
	}
	else if("089"==strName)
	{

	}
	else if("090"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		temp = RetrieveAngleOfTriangle(d1, w, h1);
		LineRevolve(line, points[0], points[3], temp, h1);
		points[1] = line.pt1;
		temp = RetrieveAngleOfTriangle(d2, w, h2);
		LineRevolve(line, points[3], points[0], -temp, h2);
		points[2] = line.pt1;
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H1");
		m_grPath.DimensionAppendD(points[2], points[3], "H2");
		m_grPath.DimensionAppendD(points[0], points[2], "D2", 0);
		m_grPath.DimensionAppendD(points[1], points[3], "D1", 0);
		
		if(points[0].fx > points[1].fx)
		{
			m_grPath.Offset((points[0].fx-points[1].fx), 0);
		}
	}
	else if("091"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h1);
		points[2].Set(m_clip.X1+w-w2, m_clip.Y1+h2);
		points[3].Set(m_clip.X1+w, m_clip.Y1);

		m_grPath.AddSharpNodes(points, 4);

		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp = points[1];
		tmp.Offset(-w1, 0);
		m_grPath.DimensionAppendD(points[0], tmp, "H1");
		m_grPath.DimensionAppendD(tmp, points[1], "W1");
		tmp = points[2];
		tmp.Offset(w2, 0);
		m_grPath.DimensionAppendD(points[2], tmp, "W2");
		m_grPath.DimensionAppendD(tmp, points[3], "H2");
	}
	else if("092"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+l, m_clip.Y1+h);
		points[3].Set(m_clip.X1+l, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 4);

		m_grPath.DimensionAppendD(points[3], points[0], "L");
		m_grPath.DimensionAppendD(points[0], points[1], "H", 32);

		tmp = points[1];
		tmp.Offset(0, -h2);
		m_grPath.AddSplitNode(tmp);
		m_grPath.DimensionAppendD(tmp, points[1], "H2", 8);

		tmp = points[3];
		tmp.Offset(0, h1);
		m_grPath.AddSplitNode(tmp);
		m_grPath.DimensionAppendD(tmp, points[3], "H1");

	}
	else if("093"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+l1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+l, m_clip.Y1+h);
		points[3].Set(m_clip.X1+l-l1, m_clip.Y1);

		m_grPath.AddSharpNodes(points, 4);

		tmp = points[2];
		tmp.Offset(0, -h);
		m_grPath.DimensionAppendD(tmp, points[0], "L");
		tmp = points[1];
		tmp.Offset(-l1, 0);
		m_grPath.DimensionAppendD(points[0], tmp, "H");
		m_grPath.DimensionAppendD(tmp, points[1], "L1");

		tmp = points[1];
		tmp.Offset((l-l1)/2, 0);
		points[5] = points[4] = tmp;
		points[4].Offset(-l2, 0);
		points[5].Offset(0, -h);
		m_grPath.AddSplitNode(points[4]);
		m_grPath.AddSplitNode(points[5]);
		
		m_grPath.DimensionAppendD(points[4], tmp, "L2");
	}
	else if("094"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+l1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w+l1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 4);

		m_grPath.DimensionAppendD(points[3], points[0], "W");

		tmp = points[1];
		tmp.Offset(-l1, 0);
		m_grPath.DimensionAppendD(points[0], tmp, "H");
		m_grPath.DimensionAppendD(tmp, points[1], "L1");
		
		tmp = points[0];
		tmp.Offset(w/2, 0);
		m_grPath.AddSplitNode(tmp);
		tmp.Offset(l1, h);
		m_grPath.AddSplitNode(tmp);
	}
	else if("095"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+(3*w)+w1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+(3*w), m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 4);

		tmp = points[1];
		tmp.Offset(-w1, 0);
		m_grPath.DimensionAppendD(points[0], tmp, "H");
		m_grPath.DimensionAppendD(tmp, points[1], "W1");

		tmp = points[0];
		tmp.Offset(w, 0);
		m_grPath.DimensionAppendD(tmp, points[0], "W");

		m_grPath.AddSplitNode(tmp);
		tmp.Offset(w1, h);
		m_grPath.AddSplitNode(tmp);
		tmp.Offset(w, 0);
		m_grPath.AddSplitNode(tmp);
		tmp.Offset(-w1, -h);
		m_grPath.AddSplitNode(tmp);
	}
	else if("255"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		temp = RetrieveAngleOfTriangle(d2, w, h1);
		LineRevolve(line, points[0], points[3], temp, h1);
		points[1] = line.pt1;
		temp = RetrieveAngleOfTriangle(h2, d2, w1);
		LineRevolve(line, points[1], points[3], temp, w1);
		points[2] = line.pt1;
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H1");
		m_grPath.DimensionAppendD(points[1], points[2], "W1");
		m_grPath.DimensionAppendD(points[2], points[3], "H2");
		m_grPath.DimensionAppendD(points[1], points[3], "D2", 0);
		
		if(points[0].fx > points[1].fx)
		{
			m_grPath.Offset((points[0].fx-points[1].fx), 0);
		}
	}
	else if("259"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		temp = h1*tan(A1);
		points[1].Set(m_clip.X1+temp, m_clip.Y1+h1);
		temp = h2*tan(A2);
		points[2].Set(m_clip.X1+w+temp, m_clip.Y1+h2);
		
		m_grPath.AddSharpNodes(points, 4);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");

		tmp = points[0];
		tmp.Offset(0, h1);
		m_grPath.DimensionAppendD(points[0], tmp, "H1");
		tmp.Offset(0, -h1/2);
		LineRevolve(line, points[0], points[1], 0, h1/2);
		m_grPath.DimensionAppendA(points[0], tmp, line.pt1, "A1", A1>MATH_PI);

		tmp = points[2];
		tmp.Offset(0, -h2);
		m_grPath.DimensionAppendD(points[2], tmp, "H2");
		tmp.Offset(0, h2/2);
		LineRevolve(line, points[2], points[3], 0, h2/2);
		m_grPath.DimensionAppendA(points[2], tmp, line.pt1, "A2", A2>MATH_PI);
		
		if(points[0].fx > points[1].fx)
		{
			m_grPath.Offset((points[0].fx-points[1].fx), 0);
		}
	}
	else if("260"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		if(A<=(MATH_PI/2))
		{
			temp = w*tan((MATH_PI/2)-A);
			points[3].Set(m_clip.X1+w, m_clip.Y1+temp);
			points[2] = points[3];
			points[2].Offset(0, h);
			
			m_grPath.AddSharpNodes(points, 4);
			
			tmp = points[0];
			tmp.Offset(w, 0);
			m_grPath.DimensionAppendD(tmp, points[0], "W");
			m_grPath.DimensionAppendD(points[0], points[1], "H");
		}
		else
		{
			temp = w*tan(A-(MATH_PI/2));
			points[3].Set(m_clip.X1+w, m_clip.Y1-temp);
			points[2] = points[3];
			points[2].Offset(0, h);
			
			m_grPath.AddSharpNodes(points, 4);
			
			tmp = points[3];
			tmp.Offset(-w, 0);
			m_grPath.DimensionAppendD(points[3], tmp, "W");
			m_grPath.DimensionAppendD(points[0], points[1], "H");
		}
		
		LineRevolve(line, points[0], points[1], 0, min(w,h)/2);
		tmp = line.pt1;
		LineRevolve(line, points[0], points[3], 0, min(w,h)/2);
		m_grPath.DimensionAppendA(points[0], tmp, line.pt1, "A", A>MATH_PI);
		
		if(points[0].fy > points[3].fy)
		{
			m_grPath.Offset(0, (points[0].fy-points[3].fy));
		}
	}
	else if("261"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		if(A<=(MATH_PI/2))
		{
			temp = w*cos((MATH_PI/2)-A);
			tmp.Set(m_clip.X1+temp, m_clip.Y1);
			LineRevolve(line, points[0], tmp, ((MATH_PI/2)-A), w);
			points[3] = line.pt1;
			points[2] = points[3];
			points[2].Offset(0, h);
			
			m_grPath.AddSharpNodes(points, 4);
			
			m_grPath.DimensionAppendD(points[3], points[0], "W");
			m_grPath.DimensionAppendD(points[0], points[1], "H");
		}
		else
		{
			temp = w*cos(A-(MATH_PI/2));
			tmp.Set(m_clip.X1+temp, m_clip.Y1);
			LineRevolve(line, points[0], tmp, -(A-(MATH_PI/2)), w);
			points[3] = line.pt1;
			points[2] = points[3];
			points[2].Offset(0, h);
			
			m_grPath.AddSharpNodes(points, 4);
			
			m_grPath.DimensionAppendD(points[3], points[0], "W");
			m_grPath.DimensionAppendD(points[0], points[1], "H");
		}
		
		LineRevolve(line, points[0], points[1], 0, min(w,h)/2);
		tmp = line.pt1;
		LineRevolve(line, points[0], points[3], 0, min(w,h)/2);
		m_grPath.DimensionAppendA(points[0], tmp, line.pt1, "A", A>MATH_PI);
		
		if(points[0].fy > points[3].fy)
		{
			m_grPath.Offset(0, (points[0].fy-points[3].fy));
		}
	}
	else if("272"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);

		m_grPath.AddSharpNodes(&points[0], 4);

		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
		m_grPath.DimensionAppendD(points[2], points[3], "H1");

		points[0].Set(m_clip.X1+d, m_clip.Y1+d1);
		points[1].Set(m_clip.X1+d, m_clip.Y1+d1+h2);
		points[2].Set(m_clip.X1+d+w2, m_clip.Y1+d1+h3);
		points[3].Set(m_clip.X1+d+w2, m_clip.Y1+d1);

		m_grPath.AddSplitNode(points[0]);
		m_grPath.AddSplitNode(points[1]);
		m_grPath.AddSplitNode(points[1]);
		m_grPath.AddSplitNode(points[2]);
		m_grPath.AddSplitNode(points[2]);
		m_grPath.AddSplitNode(points[3]);
		m_grPath.AddSplitNode(points[3]);
		m_grPath.AddSplitNode(points[0]);

		tmp = points[0];
		tmp.Offset(0, -d1);
		m_grPath.DimensionAppendD(tmp, points[0], "D1", 0);
		tmp = points[0];
		tmp.Offset(-d, 0);
		m_grPath.DimensionAppendD(tmp, points[0], "D", 0);
		m_grPath.DimensionAppendD(points[3], points[0], "W2");
		m_grPath.DimensionAppendD(points[0], points[1], "H2");
		m_grPath.DimensionAppendD(points[2], points[3], "H3");
	}




	m_grPath.PaintTo(&m_dcGraph, &rcDrawing, GRAPH_COLOR_FR);
	
	//将图形由设备坐标系(Y轴向下)转换为数学平面直角坐标系(Y轴向上)
	ConvertGraphCoordinate(&m_dcGraph);
	
	Invalidate(TRUE);
}

void CGrEditor::ProcPentagon()
{
	CRect rect, rcDrawing;
	CString strName=m_picAttr.szPicName;
	CGrPoint points[8], tmp;
	CGrArc grArc;
	GR_LINE line;
	double fTemp;
	
	//////////////////////////////////////////////////////////////////////////
	CUISetting *pSet = &m_uiSettings[m_picAttr.nIndex];
	double w = pSet->GetValue("W");
	double w1 = pSet->GetValue("W1");
	double w2 = pSet->GetValue("W2");
	double w3 = pSet->GetValue("W3");
	double h = pSet->GetValue("H");
	double h1 = pSet->GetValue("H1");
	double h2 = pSet->GetValue("H2");
	double A = pSet->GetValue("A");
	double A1 = pSet->GetValue("A1");
	double A2 = pSet->GetValue("A2");
	double b = pSet->GetValue("B");
	double l = pSet->GetValue("L");
	double r = pSet->GetValue("R");
	double r1 = pSet->GetValue("R1");
	double r2 = pSet->GetValue("R2");
	double r3 = pSet->GetValue("R3");
	double r4 = pSet->GetValue("R4");
	double r5 = pSet->GetValue("R5");
	double t = pSet->GetValue("T");
	double s1 = pSet->GetValue("S1");
	double d1 = pSet->GetValue("D1");
	//////////////////////////////////////////////////////////////////////////
	
	m_dcGraph.GetClipBox(&rect);
	rcDrawing=rect;
	rcDrawing.DeflateRect(32,32,32,32);
	
	
	if("120"==strName)
	{
		A = (108*MATH_PI/180);
		
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		LineRevolve(line, points[0], points[4], A, w);
 		points[1] = line.pt1;
		points[0].Offset(-points[1].fx+m_clip.X1, 0);
		points[4].Offset(-points[1].fx+m_clip.X1, 0);
		points[1].Offset(-points[1].fx+m_clip.X1, 0);
		LineRevolve(line, points[1], points[0], A, w);
		points[2] = line.pt1;
		LineRevolve(line, points[2], points[1], A, w);
		points[3] = line.pt1;

		m_grPath.AddSharpNodes(points, 5);

		m_grPath.DimensionAppendD(points[4], points[0], "W");
	}
	else if("121"==strName)
	{

	}
	else if("122"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h1);
		points[1].Set(m_clip.X1+(w/2), m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+(w/2)+(w1/2), m_clip.Y1);
		points[4].Set(m_clip.X1+((w-w1)/2), m_clip.Y1);

		m_grPath.AddSharpNodes(points, 5);

		line.pt1 = points[2];
		line.pt1.Offset(0, -h1);
		line.pt2 = points[0];
		line.pt2.Offset(0, -h1);
		m_grPath.DimensionAppendD(line, "W");
		m_grPath.DimensionAppendD(points[4], points[3], "W1");
		line.pt1 = points[4];
		line.pt1.Offset(-(w-w1)/2, 0);
		line.pt2 = points[1];
		line.pt2.Offset(-w/2, 0);
		m_grPath.DimensionAppendD(line, "H");
		line.pt1 = points[2];
		line.pt2 = points[3];
		line.pt2.Offset((w-w1)/2, 0);
		m_grPath.DimensionAppendD(line, "H1");
	}
	else if("123"==strName || "124"==strName)
	{
		if("123"==strName)
			t = b/2;
		points[0].Set(m_clip.X1, m_clip.Y1+r);
		points[1].Set(m_clip.X1+t, m_clip.Y1+l);
		points[2].Set(m_clip.X1+b, m_clip.Y1+r);
		points[3].Set(m_clip.X1+b, m_clip.Y1);
		points[4].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 5);
		
		m_grPath.DimensionAppendD(points[3], points[4], "B");
		tmp = points[1];
		tmp.Offset(-t, 0);
		m_grPath.DimensionAppendD(points[4], tmp, "L");
		if("124"==strName)
			m_grPath.DimensionAppendD(tmp, points[1], "T");
		m_grPath.DimensionAppendD(points[2], points[3], "R");
	}
	else if("125"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+s1);
		points[1].Set(m_clip.X1+t, m_clip.Y1+l);
		points[2].Set(m_clip.X1+b, m_clip.Y1+r);
		points[3].Set(m_clip.X1+b, m_clip.Y1);
		points[4].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 5);
		
		m_grPath.DimensionAppendD(points[3], points[4], "B");
		m_grPath.DimensionAppendD(points[0], points[4], "S1");
		tmp = points[1];
		tmp.Offset(-t, 0);
		m_grPath.DimensionAppendD(points[4], tmp, "L");
		m_grPath.DimensionAppendD(tmp, points[1], "T");
		m_grPath.DimensionAppendD(points[2], points[3], "R");
	}
	else if("126"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h2);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		points[4].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 5);
		
		m_grPath.DimensionAppendD(points[3], points[4], "W");
		m_grPath.DimensionAppendD(points[0], points[4], "H1");
		tmp = points[1];
		tmp.Offset(-w1, 0);
		m_grPath.DimensionAppendD(points[4], tmp, "H");
		m_grPath.DimensionAppendD(tmp, points[1], "W1");
		m_grPath.DimensionAppendD(points[2], points[3], "H2");
	}
	else if("127"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h1);
		//points[1]
		points[2].Set(m_clip.X1+w, m_clip.Y1+h2);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		points[4].Set(m_clip.X1, m_clip.Y1);
		fTemp = h1-h2;
		fTemp = sqrt(fTemp*fTemp+w*w);
		fTemp = RetrieveAngleOfTriangle(w2, fTemp, w1);
		LineRevolve(line, points[0], points[2], fTemp, w1);
		points[1] = line.pt1;
		
		m_grPath.AddSharpNodes(points, 5);
		
		m_grPath.DimensionAppendD(points[3], points[4], "W");
		m_grPath.DimensionAppendD(points[4], points[0], "H1");
		m_grPath.DimensionAppendD(points[0], points[1], "W1");
		m_grPath.DimensionAppendD(points[1], points[2], "W2");
		m_grPath.DimensionAppendD(points[2], points[3], "H2");
	}
	else if("128"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h);
		points[1] = points[0];
		points[1].Offset(w-A1, 0);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		points[2] = points[3];
		points[2].Offset(0, h-A2);
		points[4].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 5);
		
		m_grPath.DimensionAppendD(points[3], points[4], "W");
		m_grPath.DimensionAppendD(points[4], points[0], "H");
		tmp = points[1];
		tmp.Offset(A1, 0);
		m_grPath.DimensionAppendD(points[1], tmp, "A1");
		m_grPath.DimensionAppendD(tmp, points[2], "A2");
	}
	else if("129"==strName)
	{
		fTemp = sqrt(0.5)*d1;
		points[0].Set(m_clip.X1, m_clip.Y1+h);
		points[1] = points[0];
		points[1].Offset(w-fTemp, 0);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		points[2] = points[3];
		points[2].Offset(0, h-fTemp);
		points[4].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 5);
		
		m_grPath.DimensionAppendD(points[3], points[4], "W");
		m_grPath.DimensionAppendD(points[4], points[0], "H");
		m_grPath.DimensionAppendD(points[1], points[2], "D1");
	}
	else if("130"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h);
		points[1] = points[0];
		points[1].Offset(w1, 0);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		points[2] = points[3];
		points[2].Offset(0, h1);
		points[4].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 5);
		
		m_grPath.DimensionAppendD(points[3], points[4], "W");
		m_grPath.DimensionAppendD(points[4], points[0], "H");
		m_grPath.DimensionAppendD(points[0], points[1], "W1");
		m_grPath.DimensionAppendD(points[2], points[3], "H1");
	}
	else if("131"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h1);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h2);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		points[4].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 5);
		
		m_grPath.DimensionAppendD(points[3], points[4], "W");
		m_grPath.DimensionAppendD(points[4], points[0], "H");
		tmp = points[0];
		tmp.Offset(w1, 0);
		m_grPath.DimensionAppendD(points[0], tmp, "W1");
		m_grPath.DimensionAppendD(points[3], points[2], "H2");
		tmp = points[3];
		tmp.Offset(0, h1);
		m_grPath.DimensionAppendD(tmp, points[3], "H1");
	}
	else if("132"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h1+h2);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		points[4].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 5);
		
		m_grPath.DimensionAppendD(points[3], points[4], "W");
		m_grPath.DimensionAppendD(points[4], points[0], "H");
		tmp = points[0];
		tmp.Offset(w1, 0);
		m_grPath.DimensionAppendD(points[0], tmp, "W1");
		tmp = points[2];
		tmp.Offset(0, h2);
		m_grPath.DimensionAppendD(tmp, points[2], "H2");
		m_grPath.DimensionAppendD(points[2], points[3], "H1");
	}
	else if("133"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w+w2-w3, m_clip.Y1+h2);
		points[3].Set(m_clip.X1+w+w2, m_clip.Y1);
		points[4].Set(m_clip.X1+w2, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 5);
		
		m_grPath.DimensionAppendD(points[3], points[4], "W");
		tmp = points[4];
		tmp.Offset(-w2, 0);
		m_grPath.DimensionAppendD(points[4],tmp, "W2");
		m_grPath.DimensionAppendD(tmp, points[0], "H1", 0);
		line.pt1 = tmp;
		line.pt2 = points[1];
		line.pt2.Offset(-w1, 0);
		m_grPath.DimensionAppendD(line, "H", 30);
		m_grPath.DimensionAppendD(line.pt2, points[1], "W1");
		line.pt1 = points[2];
		line.pt2 = points[3];
		line.pt2.Offset(0, h2);
		m_grPath.DimensionAppendD(line, "W3");
		m_grPath.DimensionAppendD(line.pt2, points[3], "H2");
	}
	else if("134"==strName)
	{
		points[0].Set(m_clip.X1+w2, m_clip.Y1+h);
		points[1].Set(m_clip.X1+w-w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		points[4].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 5);

		m_grPath.DimensionAppendD(points[3], points[4], "W");
		tmp = points[0];
		tmp.Offset(-w2, 0);
		m_grPath.DimensionAppendD(points[4], tmp, "H");
		m_grPath.DimensionAppendD(tmp, points[0], "W2");
		tmp = points[1];
		tmp.Offset(w1, 0);
		m_grPath.DimensionAppendD(points[1], tmp, "W1");
		m_grPath.DimensionAppendD(points[2], points[3], "H1");
	}	
	else if("135"==strName)
	{
		A = (A*MATH_PI/180);
		points[4].Set(m_clip.X1, m_clip.Y1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		LineRevolve(line, points[4], points[3], A, l);
		points[0] = line.pt1;
		points[1] = points[0];
		points[1].Offset(0, h);
		points[2] = points[1];
		points[2].Offset(w1, 0);
		
		m_grPath.AddSharpNodes(points, 5);

		m_grPath.DimensionAppendD(points[3], points[4], "W");
		m_grPath.DimensionAppendD(points[4], points[0], "L");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
		m_grPath.DimensionAppendD(points[1], points[2], "W1");

		LineRevolve(line, points[4], points[0], 0, min(w, l)/2);
		tmp = line.pt1;
		LineRevolve(line, points[4], points[3], 0, min(w, l)/2);
		m_grPath.DimensionAppendA(points[4], tmp, line.pt1, "A", A>MATH_PI);

		if(points[4].fx>points[0].fx)
			m_grPath.Offset(points[4].fx-points[0].fx, 0);
	}	
	else if("136"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h);
		points[1].Set(m_clip.X1+w, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w1+w2+w3, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w1+w2, m_clip.Y1);
		points[4].Set(m_clip.X1+w1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 5);
		
		m_grPath.DimensionAppendD(points[0], points[1], "W");
		tmp = points[3];
		tmp.Offset(w3, 0);
		m_grPath.DimensionAppendD(points[2], tmp, "H1");
		m_grPath.DimensionAppendD(tmp, points[3], "W3");
		m_grPath.DimensionAppendD(points[3], points[4], "W2");
		tmp = points[4];
		tmp.Offset(-w1, 0);
		m_grPath.DimensionAppendD(points[4], tmp, "W1");
		m_grPath.DimensionAppendD(tmp, points[0], "H");
	}	
	else if("137"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w2, m_clip.Y1);
		points[4].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 5);
		
		tmp = points[4];
		tmp.Offset(w, 0);
		m_grPath.DimensionAppendD(points[2], tmp, "H");
		m_grPath.DimensionAppendD(tmp, points[4], "W");
		m_grPath.DimensionAppendD(points[4], points[3], "W2");
		m_grPath.DimensionAppendD(points[4], points[0], "H1");
		tmp = points[1];
		tmp.Offset(-w1, 0);
		m_grPath.DimensionAppendD(tmp, points[1], "W1");
	}
	else if("138"==strName)
	{
	}
	else if("139"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		points[4].Set(m_clip.X1, m_clip.Y1);
//		m_grPath.AddSharpNodes(points, 5);
		
		grArc.InitRoundCornerArc(r1, points[4], points[3], points[0]);
		m_grPath.AddRoundAngleNode(points[4], grArc);
		m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R1");
		
		grArc.InitRoundCornerArc(r5, points[0], points[4], points[1]);
		m_grPath.AddRoundAngleNode(points[0], grArc);
		m_grPath.DimensionAppendR(grArc.m_ptC0, r5, MATH_PI*3/4, "R5");
		
		grArc.InitRoundCornerArc(r4, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		LineRevolve(line, grArc.m_ptC0, points[1], 0, r4);
		m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R4");
		
		grArc.InitRoundCornerArc(r3, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		LineRevolve(line, grArc.m_ptC0, points[2], 0, r3);
		m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R3");
		
		grArc.InitRoundCornerArc(r2, points[3], points[2], points[4]);
		m_grPath.AddRoundAngleNode(points[3], grArc);
		LineRevolve(line, grArc.m_ptC0, points[3], 0, r2);
		m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R2");

		m_grPath.DimensionAppendD(points[3], points[4], "W");
		m_grPath.DimensionAppendD(points[4], points[0], "H");
		m_grPath.DimensionAppendD(points[0], points[1], "W1");
		m_grPath.DimensionAppendD(points[2], points[3], "H1");
	}
	else if("140"==strName || "141"==strName)
	{
		points[0].Set(m_clip.X1+w2, m_clip.Y1+h);
		points[1].Set(m_clip.X1+w-w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		points[4].Set(m_clip.X1, m_clip.Y1);
		//m_grPath.AddSharpNodes(points, 5);
		if("140"==strName)
			r1 = r2 = r3 = r4 = r5 = r;

		grArc.InitRoundCornerArc(r1, points[4], points[3], points[0]);
		m_grPath.AddRoundAngleNode(points[4], grArc);
		if("140"==strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R");
		else
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R1");
		
		grArc.InitRoundCornerArc(r5, points[0], points[4], points[1]);
		m_grPath.AddRoundAngleNode(points[0], grArc);
		if("140"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[0], 0, r5);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R5");
		}
		
		grArc.InitRoundCornerArc(r4, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		if("140"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[1], 0, r4);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R4");
		}
		
		grArc.InitRoundCornerArc(r3, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		if("140"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[2], 0, r3);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R3");
		}
		
		grArc.InitRoundCornerArc(r2, points[3], points[2], points[4]);
		m_grPath.AddRoundAngleNode(points[3], grArc);
		if("140"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[3], 0, r2);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R2");
		}
		
		m_grPath.DimensionAppendD(points[3], points[4], "W");
		tmp = points[0];
		tmp.Offset(-w2, 0);
		m_grPath.DimensionAppendD(points[4], tmp, "H");
		m_grPath.DimensionAppendD(tmp, points[0], "W2");
		tmp = points[1];
		tmp.Offset(w1, 0);
		m_grPath.DimensionAppendD(points[1], tmp, "W1");
		m_grPath.DimensionAppendD(points[2], points[3], "H1");
	}
	else if("142"==strName || "143"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h2);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		points[4].Set(m_clip.X1, m_clip.Y1);
		//m_grPath.AddSharpNodes(points, 5);
		if("142"==strName)
			r1 = r2 = r3 = r4 = r5 = r;

		grArc.InitRoundCornerArc(r1, points[4], points[3], points[0]);
		m_grPath.AddRoundAngleNode(points[4], grArc);
		if("142"==strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R");
		else
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R1");
		
		grArc.InitRoundCornerArc(r5, points[0], points[4], points[1]);
		m_grPath.AddRoundAngleNode(points[0], grArc);
		if("142"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[0], 0, r5);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R5");
		}
		
		grArc.InitRoundCornerArc(r4, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		if("142"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[1], 0, r4);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R4");
		}
		
		grArc.InitRoundCornerArc(r3, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		if("142"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[2], 0, r3);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R3");
		}
		
		grArc.InitRoundCornerArc(r2, points[3], points[2], points[4]);
		m_grPath.AddRoundAngleNode(points[3], grArc);
		if("142"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[3], 0, r2);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R2");
		}
		
		m_grPath.DimensionAppendD(points[3], points[4], "W");
		tmp = points[1];
		tmp.Offset(-w1, 0);
		m_grPath.DimensionAppendD(points[4], tmp, "H", 30);
		m_grPath.DimensionAppendD(points[4], points[0], "H1", 3);
		m_grPath.DimensionAppendD(tmp, points[1], "W1");
		m_grPath.DimensionAppendD(points[2], points[3], "H1");
	}
	

	m_grPath.PaintTo(&m_dcGraph, &rcDrawing, GRAPH_COLOR_FR);

	//将图形由设备坐标系(Y轴向下)转换为数学平面直角坐标系(Y轴向上)
	ConvertGraphCoordinate(&m_dcGraph);

	Invalidate(TRUE);
}


void CGrEditor::ProcHexagon()
{
	GR_NODE grNode;
	CRect rect, rcDrawing;
	CString strName=m_picAttr.szPicName;
	GR_DIMENSION dimension;
	CGrPoint points[12];
	GR_LINE line;
	CGrArc grArc;
	
	
	//////////////////////////////////////////////////////////////////////////
	CUISetting *pSet = &m_uiSettings[m_picAttr.nIndex];
	double w = pSet->GetValue("W");
	double w1 = pSet->GetValue("W1");
	double w2 = pSet->GetValue("W2");
	double w3 = pSet->GetValue("W3");
	double h = pSet->GetValue("H");
	double h1 = pSet->GetValue("H1");
	double h2 = pSet->GetValue("H2");
	double A = pSet->GetValue("A");
	double A1 = pSet->GetValue("A1");
	double A2 = pSet->GetValue("A2");
	double r = pSet->GetValue("R");
	double r1 = pSet->GetValue("R1");
	double r2 = pSet->GetValue("R2");
	double r3 = pSet->GetValue("R3");
	double r4 = pSet->GetValue("R4");
	double r5 = pSet->GetValue("R5");
	double r6 = pSet->GetValue("R6");
	double r7 = pSet->GetValue("R7");
	double r8 = pSet->GetValue("R8");
	double B1 = pSet->GetValue("B1");
	double B2 = pSet->GetValue("B2");
	double C1 = pSet->GetValue("C1");
	double C2 = pSet->GetValue("C2");
	double D1 = pSet->GetValue("D1");
	double D2 = pSet->GetValue("D2");
	double D3 = pSet->GetValue("D3");
	double D4 = pSet->GetValue("D4");
	double bm = pSet->GetValue("BM");
	double s1 = pSet->GetValue("S1");
	double s2 = pSet->GetValue("S2");
	double s3 = pSet->GetValue("S3");
	double s4 = pSet->GetValue("S4");
	double s5 = pSet->GetValue("S5");
	double s6 = pSet->GetValue("S6");
	double s7 = pSet->GetValue("S7");
	double s8 = pSet->GetValue("S8");
	//////////////////////////////////////////////////////////////////////////
	
	m_dcGraph.GetClipBox(&rect);
	rcDrawing=rect;
	rcDrawing.DeflateRect(32,32,32,32);
	
	
	memset(&grNode, 0, sizeof(GR_NODE));
	
	
	if("144"==strName)
	{
		A = (120*MATH_PI/180);
		
		points[5].Set(m_clip.X1, m_clip.Y1);
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		LineRevolve(line, points[5], points[4], A, w);
		points[0] = line.pt1;
		points[5].Offset(-points[0].fx+m_clip.X1, 0);
		points[4].Offset(-points[0].fx+m_clip.X1, 0);
		points[0].Offset(-points[0].fx+m_clip.X1, 0);
		LineRevolve(line, points[0], points[5], A, w);
		points[1] = line.pt1;
		LineRevolve(line, points[1], points[0], A, w);
		points[2] = line.pt1;
		LineRevolve(line, points[2], points[1], A, w);
		points[3] = line.pt1;

		m_grPath.AddSharpNodes(points, 6);
		
		m_grPath.DimensionAppendD(points[4], points[5], "W");
	}
	else if("145"==strName)
	{
		A = (120*MATH_PI/180);

		points[5].Set(m_clip.X1+w/4, m_clip.Y1);
		points[4].Set(m_clip.X1+w*3/4, m_clip.Y1);
		LineRevolve(line, points[5], points[4], A, w/2);
		points[0] = line.pt1;
		points[1] = points[0];
		points[1].Offset(w/4, points[0].fy);
		points[2] = points[1];
		points[2].Offset(w/2, 0);
		points[3] = points[0];
		points[3].Offset(w, 0);
		
		m_grPath.AddSharpNodes(points, 6);
		
		line.pt1 = points[4];
		line.pt2 = points[5];
		line.pt1.Offset(w/4, 0);
		line.pt2.Offset(-w/4, 0);
		m_grPath.DimensionAppendD(line, "W");
	}
	else if("146"==strName || "147"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+(h/2));
		points[1].Set(m_clip.X1+((w-w1)/2), m_clip.Y1+h);
		points[2] = points[1];
		points[2].Offset(w1, 0);
		points[3] = points[0];
		points[3].Offset(w, 0);
		points[4] = points[2];
		points[4].Offset(0, -h);
		points[5] = points[4];
		points[5].Offset(-w1, 0);
		
		m_grPath.AddSharpNodes(points, 6);

		line.pt1 = points[3];
		line.pt1.Offset(0, -h/2);
		line.pt2 = points[0];
		line.pt2.Offset(0, -h/2);
		m_grPath.DimensionAppendD(line, "W");
		line.pt1 = points[5];
		line.pt1.Offset(-(w-w1)/2, 0);
		line.pt2 = points[1];
		line.pt2.Offset(-(w-w1)/2, 0);
		m_grPath.DimensionAppendD(line, "H");
		m_grPath.DimensionAppendD(points[1], points[2], "W1");
	}
	else if("148"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h1);
		points[1].Set(m_clip.X1+((w-w1)/2), m_clip.Y1+h);
		points[5].Set(m_clip.X1+((w-w2)/2), m_clip.Y1);
		points[2] = points[1];
		points[2].Offset(w1, 0);
		points[3] = points[0];
		points[3].Offset(w, 0);
		points[4] = points[5];
		points[4].Offset(w2, 0);
		
		m_grPath.AddSharpNodes(points, 6);

		line.pt1 = points[3];
		line.pt1.Offset(0, -h1);
		line.pt2 = points[0];
		line.pt2.Offset(0, -h1);
		m_grPath.DimensionAppendD(line, "W");
		m_grPath.DimensionAppendD(points[5], points[4], "W2");
		m_grPath.DimensionAppendD(points[3], line.pt1, "H1");
		line.pt1 = points[5];
		line.pt1.Offset(-(w-w2)/2, 0);
		line.pt2 = points[1];
		line.pt2.Offset(-(w-w1)/2, 0);
		m_grPath.DimensionAppendD(line, "H");
		m_grPath.DimensionAppendD(points[1], points[2], "W1");
	}
	else if("149"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h1);
		points[1].Set(m_clip.X1+((w-w1)/2), m_clip.Y1+h);
		points[5].Set(m_clip.X1, m_clip.Y1);
		points[2] = points[1];
		points[2].Offset(w1, 0);
		points[3] = points[0];
		points[3].Offset(w, 0);
		points[4] = points[5];
		points[4].Offset(w, 0);
		
		m_grPath.AddSharpNodes(points, 6);

		m_grPath.DimensionAppendD(points[4], points[5], "W");
		line.pt2 = points[5];
		line.pt2.Offset(0, h);
		m_grPath.DimensionAppendD(points[5], line.pt2, "H");
		m_grPath.DimensionAppendD(points[1], points[2], "W1");
		m_grPath.DimensionAppendD(points[3], points[4], "H1");
	}
	else if("150"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+(h-A2));
		points[1].Set(m_clip.X1+A1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w-A1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1+(h-A2));
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		points[5].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 6);
		
		m_grPath.DimensionAppendD(points[4], points[5], "W");
		line.pt1 = points[5];
		line.pt1.Offset(0, h);
		m_grPath.DimensionAppendD(points[5], line.pt1, "H", 24);
		m_grPath.DimensionAppendD(points[0], line.pt1, "A2", 4);
		m_grPath.DimensionAppendD(line.pt1, points[1], "A1");
	}
	else if("151"==strName)
	{
		A1 = sin(MATH_PI/4)*D1;
		A2 = A1;
		points[0].Set(m_clip.X1, m_clip.Y1+(h-A2));
		points[1].Set(m_clip.X1+A1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w-A1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1+(h-A2));
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		points[5].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 6);

		m_grPath.DimensionAppendD(points[4], points[5], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "D1");
		line.pt1 = points[4];
		line.pt1.Offset(0, h);
		m_grPath.DimensionAppendD(line.pt1, points[4], "H");
	}	
	else if("152"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+A2);
		points[1].Set(m_clip.X1+A1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w1+A1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		points[5].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 6);
		
		m_grPath.DimensionAppendD(points[4], points[5], "W");
		m_grPath.DimensionAppendD(points[0], points[5], "A2");
		line.pt1 = points[5];
		line.pt1.Offset(0, h);
		m_grPath.DimensionAppendD(points[5], line.pt1, "H");
		m_grPath.DimensionAppendD(line.pt1, points[1], "A1");
		m_grPath.DimensionAppendD(points[1], points[2], "W1");
		m_grPath.DimensionAppendD(points[3], points[4], "H1");
	}	
	else if("153"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h);
		points[1].Set(m_clip.X1+A1, m_clip.Y1+h1);
		points[2].Set(m_clip.X1+w1+A1, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w, m_clip.Y1+0);
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		points[5].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 6);
		
		m_grPath.DimensionAppendD(points[4], points[5], "W");
		m_grPath.DimensionAppendD(points[5], points[0], "H");
		line.pt1 = points[1];
		line.pt1.Offset(-A1, 0);
		m_grPath.DimensionAppendD(line.pt1, points[1], "A1");
		m_grPath.DimensionAppendD(points[1], points[2], "W1");
		line.pt1 = points[4];
		line.pt1.Offset(0, h1);
		m_grPath.DimensionAppendD(line.pt1, points[4], "H1");
	}	
	else if("154"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w-w2, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1+h2);
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		points[5].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 6);
		
		m_grPath.DimensionAppendD(points[4], points[5], "W");
		m_grPath.DimensionAppendD(points[5], points[0], "H1");
		line.pt1 = points[1];
		line.pt1.Offset(-w1, 0);
		m_grPath.DimensionAppendD(line.pt1, points[1], "W1");
		line.pt1 = points[2];
		line.pt1.Offset(w2, 0);
		m_grPath.DimensionAppendD(points[2], line.pt1, "W2");
		m_grPath.DimensionAppendD(line.pt1, points[4], "H", 28);
		m_grPath.DimensionAppendD(points[3], points[4], "H2", 8);
	}	
	else if("155"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w1+w2, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w+w3, m_clip.Y1+h2);
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		points[5].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 6);
		
		m_grPath.DimensionAppendD(points[4], points[5], "W");
		m_grPath.DimensionAppendD(points[0], points[5], "H1");
		line.pt1 = points[1];
		line.pt1.Offset(-w1, 0);
		m_grPath.DimensionAppendD(points[5], line.pt1, "H");
		m_grPath.DimensionAppendD(line.pt1, points[1], "W1");
		m_grPath.DimensionAppendD(points[1], points[2], "W2");
		line.pt1 = points[4];
		line.pt1.Offset(w3, 0);
		m_grPath.DimensionAppendD(points[3], line.pt1, "H2");
		m_grPath.DimensionAppendD(line.pt1, points[4], "W3");
	}	
	else if("156"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h);
		points[1].Set(m_clip.X1+A1, m_clip.Y1+h1+A2);
		points[2].Set(m_clip.X1+A1+w1, m_clip.Y1+h1+A2);
		points[3].Set(m_clip.X1+A1+w1, m_clip.Y1+A2);
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		points[5].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 6);
		
		m_grPath.DimensionAppendD(points[4], points[5], "W");
		m_grPath.DimensionAppendD(points[5], points[0], "H");
		line.pt1 = points[1];
		line.pt1.Offset(-A1, 0);
		m_grPath.DimensionAppendD(line.pt1, points[1], "A1");
		m_grPath.DimensionAppendD(points[1], points[2], "W1");
		m_grPath.DimensionAppendD(points[2], points[3], "H1");
		line.pt1 = points[3];
		line.pt1.Offset(0, -A2);
		m_grPath.DimensionAppendD(points[3], line.pt1, "A2");
	}	
	else if("157"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h-h1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1+h2);
		points[4].Set(m_clip.X1+w-w2, m_clip.Y1);
		points[5].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 6);
		
		line.pt1 = points[5];
		line.pt1.Offset(0, h);
		m_grPath.DimensionAppendD(points[5], line.pt1, "H", 28);
		m_grPath.DimensionAppendD(points[0], line.pt1, "H1", 4);
		m_grPath.DimensionAppendD(line.pt1, points[1], "W1");
		line.pt1 = points[4];
		line.pt1.Offset(w2, 0);
		m_grPath.DimensionAppendD(points[3], line.pt1, "H2");
		m_grPath.DimensionAppendD(line.pt1, points[4], "W2", 4);
		m_grPath.DimensionAppendD(line.pt1, points[5], "W", 28);
	}
	else if("158"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w2, m_clip.Y1+h2);
		points[3].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		points[5].Set(m_clip.X1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 6);
		
		m_grPath.DimensionAppendD(points[4], points[5], "W");
		m_grPath.DimensionAppendD(points[5], points[0], "H");
		m_grPath.DimensionAppendD(points[1], points[0], "W1");
		line.pt1 = points[0];
		line.pt1.Offset(w2, 0);
		m_grPath.DimensionAppendD(points[0], line.pt1, "W2");
		m_grPath.DimensionAppendD(points[4], points[3], "H1");
		line.pt1 = points[4];
		line.pt1.Offset(0, h2);
		m_grPath.DimensionAppendD(line.pt1, points[4], "H2");
	}
	else if("159"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w-w1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1+h-h1);
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		points[5].Set(m_clip.X1+w-w1, m_clip.Y1+h1);
		
		m_grPath.AddSharpNodes(points, 6);

		points[6] = points[0];
		points[6].Offset(0, -h1);
		m_grPath.DimensionAppendD(points[4], points[6], "W");
		m_grPath.DimensionAppendD(points[6], points[0], "H1");
		points[6] = points[4];
		points[6].Offset(0, h);
		m_grPath.DimensionAppendD(points[2], points[6], "W1");
		m_grPath.DimensionAppendD(points[6], points[4], "H");
	}
	else if("160"==strName)
	{
		double temp;
		A = ((7-2)*MATH_PI)/7;

		points[6].Set(m_clip.X1, m_clip.Y1);
		points[5].Set(m_clip.X1+w, m_clip.Y1);
		LineRevolve(line, points[6], points[5], A, w);
		points[0] = line.pt1;
		temp = (points[6].fx-points[0].fx);
		points[5].Offset(temp, 0);
		points[6].Offset(temp, 0);
		points[0].Offset(temp, 0);
		LineRevolve(line, points[0], points[6], A, w);
		points[1] = line.pt1;
		LineRevolve(line, points[1], points[0], A, w);
		points[2] = line.pt1;
		LineRevolve(line, points[2], points[1], A, w);
		points[3] = line.pt1;
		LineRevolve(line, points[3], points[2], A, w);
		points[4] = line.pt1;

		m_grPath.AddSharpNodes(points, 7);

		m_grPath.DimensionAppendD(points[5], points[6], "W");
	}	
	else if("161"==strName)
	{
		double temp;

		temp = sqrt(0.5f)*w;

		points[0].Set(m_clip.X1, m_clip.Y1+temp);
		points[1] = points[0];
		points[1].Offset(0, w);
		points[2] = points[1];
		points[2].Offset(temp, temp);
		points[3] = points[2];
		points[3].Offset(w, 0);
		points[4] = points[3];
		points[4].Offset(temp, -temp);
		points[5] = points[4];
		points[5].Offset(0, -w);
		points[6] = points[5];
		points[6].Offset(-temp, -temp);
		points[7].Set(m_clip.X1+temp, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 8);
		
		m_grPath.DimensionAppendD(points[6], points[7], "W");
	}	
	else if("162"==strName)
	{
		double a, b;

		a = w/(1+sqrt(2));
		b = (w-a);
		
		points[0].Set(m_clip.X1, m_clip.Y1+a);
		points[1] = points[0];
		points[1].Offset(0, b);
		points[2] = points[1];
		points[2].Offset(a, a);
		points[3] = points[2];
		points[3].Offset(b, 0);
		points[4] = points[3];
		points[4].Offset(a, -a);
		points[5] = points[4];
		points[5].Offset(0, -b);
		points[6] = points[5];
		points[6].Offset(-a, -a);
		points[7].Set(m_clip.X1+a, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 8);
		
		line.pt1 = points[5];
		line.pt1.Offset(0, -a);
		line.pt2 = points[0];
		line.pt2.Offset(0, -a);
		m_grPath.DimensionAppendD(line, "W");
	}	
	else if("163"==strName)
	{
		double a, b;
		
		b = w*sqrt((1-cos(MATH_PI/4))/2);
		if(b>=0.0f)
		{
			a = sqrt(0.5f)*b;
			
			points[0].Set(m_clip.X1, m_clip.Y1+a);
			points[1] = points[0];
			points[1].Offset(0, b);
			points[2] = points[1];
			points[2].Offset(a, a);
			points[3] = points[2];
			points[3].Offset(b, 0);
			points[4] = points[3];
			points[4].Offset(a, -a);
			points[5] = points[4];
			points[5].Offset(0, -b);
			points[6] = points[5];
			points[6].Offset(-a, -a);
			points[7].Set(m_clip.X1+a, m_clip.Y1);
			
			m_grPath.AddSharpNodes(points, 8);
			
			m_grPath.DimensionAppendD(points[0], points[4], "W");
		}
	}	
	else if("164"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1+h2);
		points[1].Set(m_clip.X1, m_clip.Y1+h1);
		points[2].Set(m_clip.X1+((w-w2)/2), m_clip.Y1+h);
		points[3].Set(m_clip.X1+((w-w2)/2)+w2, m_clip.Y1+h);
		points[4].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[5].Set(m_clip.X1+w, m_clip.Y1+h2);
		points[6].Set(m_clip.X1+((w-w1)/2)+w1, m_clip.Y1);
		points[7].Set(m_clip.X1+((w-w1)/2), m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 8);

		line.pt1.Set(m_clip.X1+w, m_clip.Y1);
		line.pt2.Set(m_clip.X1, m_clip.Y1);
		m_grPath.DimensionAppendD(line, "W");
		m_grPath.DimensionAppendD(points[7], points[6], "W1");
		line.pt1.Set(m_clip.X1, m_clip.Y1);
		line.pt2.Set(m_clip.X1, m_clip.Y1+h);
		m_grPath.DimensionAppendD(line, "H");
		m_grPath.DimensionAppendD(points[2], points[3], "W2");
		line.pt1.Set(m_clip.X1+w, m_clip.Y1+h2);
		line.pt2.Set(m_clip.X1+w, m_clip.Y1);
		m_grPath.DimensionAppendD(line, "H2", 2);
		m_grPath.DimensionAppendD(points[4], line.pt2, "H1", 28);
	}	
	else if("165"==strName)
	{
		h2 = (h-h1)/2;
		w2 = (w-w1)/2;
		points[0].Set(m_clip.X1, m_clip.Y1+h2);
		points[1].Set(m_clip.X1, m_clip.Y1+h2+h1);
		points[2].Set(m_clip.X1+w2, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w2+w1, m_clip.Y1+h);
		points[4].Set(m_clip.X1+w, m_clip.Y1+h2+h1);
		points[5].Set(m_clip.X1+w, m_clip.Y1+h2);
		points[6].Set(m_clip.X1+w2+w1, m_clip.Y1);
		points[7].Set(m_clip.X1+w2, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 8);

		line.pt1.Set(m_clip.X1+w, m_clip.Y1);
		line.pt2.Set(m_clip.X1, m_clip.Y1);
		m_grPath.DimensionAppendD(line, "W");
		m_grPath.DimensionAppendD(points[2], points[3], "W1");
		line.pt1.Set(m_clip.X1, m_clip.Y1);
		line.pt2.Set(m_clip.X1, m_clip.Y1+h);
		m_grPath.DimensionAppendD(line, "H");
		m_grPath.DimensionAppendD(points[4], points[5], "H1");
	}
	else if("166"==strName || "167"==strName)
	{
		double d1, d2, d3, d4;
		if("166"==strName)
		{
			d1 = sqrt(0.5f)*D1;
			d2 = sqrt(0.5f)*D2;
			d3 = sqrt(0.5f)*D3;
			d4 = sqrt(0.5f)*D4;
		}
		else
		{
			d1 = sqrt(0.5f)*D1;
			d4 = d3 = d2 = d1;
		}
		points[0].Set(m_clip.X1, m_clip.Y1+d4);
		points[1].Set(m_clip.X1, m_clip.Y1+h-d1);
		points[2].Set(m_clip.X1+d1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w-d2, m_clip.Y1+h);
		points[4].Set(m_clip.X1+w, m_clip.Y1+h-d2);
		points[5].Set(m_clip.X1+w, m_clip.Y1+d3);
		points[6].Set(m_clip.X1+w-d3, m_clip.Y1);
		points[7].Set(m_clip.X1+d4, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 8);
		
		line.pt1.Set(m_clip.X1+w, m_clip.Y1);
		line.pt2.Set(m_clip.X1, m_clip.Y1);
		m_grPath.DimensionAppendD(line, "W", 12);
		line.pt1.Set(m_clip.X1+w, m_clip.Y1+h);
		line.pt2.Set(m_clip.X1+w, m_clip.Y1);
		m_grPath.DimensionAppendD(line, "H", 12);
		m_grPath.DimensionAppendD(points[1], points[2], "D1", 12);
		if("166"==strName)
		{
			m_grPath.DimensionAppendD(points[3], points[4], "D2", 12);
			m_grPath.DimensionAppendD(points[5], points[6], "D3", 12);
			m_grPath.DimensionAppendD(points[7], points[0], "D4", 12);
		}
	}
	else if("168"==strName || "169"==strName)
	{
		if("169"==strName)
		{
			D1 = C1 = B1 = A1;
			D2 = C2 = B2 = A2;
		}
		points[0].Set(m_clip.X1, m_clip.Y1+D2);
		points[1].Set(m_clip.X1, m_clip.Y1+h-A2);
		points[2].Set(m_clip.X1+A1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w-B1, m_clip.Y1+h);
		points[4].Set(m_clip.X1+w, m_clip.Y1+h-B2);
		points[5].Set(m_clip.X1+w, m_clip.Y1+C2);
		points[6].Set(m_clip.X1+w-C1, m_clip.Y1);
		points[7].Set(m_clip.X1+D1, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 8);
		
		line.pt1.Set(m_clip.X1+w, m_clip.Y1);
		line.pt2.Set(m_clip.X1, m_clip.Y1);
		m_grPath.DimensionAppendD(line, "W", 28);
		line.pt1.Set(m_clip.X1, m_clip.Y1);
		line.pt2.Set(m_clip.X1, m_clip.Y1+h);
		m_grPath.DimensionAppendD(line, "H", 28);
		line.pt1 = points[1];
		line.pt1.Offset(0, A2);
		m_grPath.DimensionAppendD(points[1], line.pt1, "A2", 4);
		m_grPath.DimensionAppendD(line.pt1, points[2], "A1");
		if("168"==strName)
		{
			line.pt1 = points[3];
			line.pt1.Offset(B1, 0);
			m_grPath.DimensionAppendD(points[3], line.pt1, "B1");
			m_grPath.DimensionAppendD(line.pt1, points[4], "B2");
			line.pt1 = points[6];
			line.pt1.Offset(C1, 0);
			m_grPath.DimensionAppendD(points[5], line.pt1, "C2");
			m_grPath.DimensionAppendD(line.pt1, points[6], "C1");
			line.pt1.Set(m_clip.X1, m_clip.Y1);
			m_grPath.DimensionAppendD(points[7], line.pt1, "D1", 4);
			m_grPath.DimensionAppendD(line.pt1, points[0], "D2", 4);
		}
	}
	else if("170"==strName)
	{
		CGrPoint ptC0;
		D1 = sqrt(r*r-(w/2)*(w/2));
		if(D1>=0.0f)
		{
			D1 = (w/2) - D1;
			points[0].Set(m_clip.X1, m_clip.Y1+D1);
			points[1].Set(m_clip.X1, m_clip.Y1+w-D1);
			points[2].Set(m_clip.X1+D1, m_clip.Y1+w);
			points[3].Set(m_clip.X1+w-D1, m_clip.Y1+w);
			points[4].Set(m_clip.X1+w, m_clip.Y1+w-D1);
			points[5].Set(m_clip.X1+w, m_clip.Y1+D1);
			points[6].Set(m_clip.X1+w-D1, m_clip.Y1);
			points[7].Set(m_clip.X1+D1, m_clip.Y1);
			ptC0.Set(m_clip.X1+w/2, m_clip.Y1+w/2);
			//m_grPath.AddSharpNodes(points, 8);

			grArc.InitArc(r, ptC0, points[7], points[0]);
			m_grPath.AddArcNode(grArc);

			grArc.InitArc(r, ptC0, points[1], points[2]);
			m_grPath.AddArcNode(grArc);

			grArc.InitArc(r, ptC0, points[3], points[4]);
			m_grPath.AddArcNode(grArc);

			grArc.InitArc(r, ptC0, points[5], points[6]);
			m_grPath.AddArcNode(grArc);
			m_grPath.DimensionAppendR(grArc.m_ptC0, r, -MATH_PI/4, "R");

			line.pt1.Set(m_clip.X1+w, m_clip.Y1);
			line.pt2.Set(m_clip.X1, m_clip.Y1);
			m_grPath.DimensionAppendD(line, "W");
		}
	}
	else if("171"==strName)
	{
		w = bm;
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+D1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w-D2, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		
		m_grPath.AddSharpNodes(points, 4);

		points[4].Set(m_clip.X1+s1, m_clip.Y1);
		LineRevolve(line, points[0], points[1], 0, s2);
		points[5] = line.pt1;

		LineRevolve(line, points[1], points[0], 0, s3);
		points[6] = line.pt1;
		points[7].Set(m_clip.X1+D1+s4, m_clip.Y1+h);

		points[8].Set(m_clip.X1+w-D2-s5, m_clip.Y1+h);
		LineRevolve(line, points[2], points[3], 0, s6);
		points[9] = line.pt1;

		LineRevolve(line, points[3], points[2], 0, s7);
		points[10] = line.pt1;
		points[11].Set(m_clip.X1+w-s8, m_clip.Y1);

		m_grPath.AddSplitNode(points[4]);
		m_grPath.AddSplitNode(points[5]);
		m_grPath.AddSplitNode(points[6]);
		m_grPath.AddSplitNode(points[7]);
		m_grPath.AddSplitNode(points[8]);
		m_grPath.AddSplitNode(points[9]);
		m_grPath.AddSplitNode(points[10]);
		m_grPath.AddSplitNode(points[11]);

		m_grPath.DimensionAppendD(points[3], points[0], "BM", 32);
		line.pt1 = points[1];
		line.pt1.Offset(-D1, 0);
		m_grPath.DimensionAppendD(points[0], line.pt1, "H", 32);
		m_grPath.DimensionAppendD(line.pt1, points[1], "D1");
		line.pt1 = points[2];
		line.pt1.Offset(D2, 0);
		m_grPath.DimensionAppendD(points[2], line.pt1, "D2");

		m_grPath.DimensionAppendD(points[4], points[0], "S1", 12);
		m_grPath.DimensionAppendD(points[0], points[5], "S2", 16);
		m_grPath.DimensionAppendD(points[6], points[1], "S3", 16);
		m_grPath.DimensionAppendD(points[1], points[7], "S4", 16);
		m_grPath.DimensionAppendD(points[8], points[2], "S5", 16);
		m_grPath.DimensionAppendD(points[2], points[9], "S6", 16);
		m_grPath.DimensionAppendD(points[10], points[3], "S7", 16);
		m_grPath.DimensionAppendD(points[3], points[11], "S8", 12);
	}
	else if("172"==strName)
	{
		double temp;
		A = ((9-2)*MATH_PI)/9;
		points[6].Set(m_clip.X1+w, m_clip.Y1);
		points[7].Set(m_clip.X1, m_clip.Y1);
		LineRevolve(line, points[7], points[6], A, w);
		points[8] = line.pt1;
		LineRevolve(line, points[8], points[7], A, w);
		points[0] = line.pt1;
		temp = points[7].fx-points[0].fx;
		points[6].Offset(temp, 0);
		points[7].Offset(temp, 0);
		points[8].Offset(temp, 0);
		points[0].Offset(temp, 0);
		LineRevolve(line, points[0], points[8], A, w);
		points[1] = line.pt1;
		LineRevolve(line, points[1], points[0], A, w);
		points[2] = line.pt1;
		LineRevolve(line, points[2], points[1], A, w);
		points[3] = line.pt1;
		LineRevolve(line, points[3], points[2], A, w);
		points[4] = line.pt1;
		LineRevolve(line, points[4], points[3], A, w);
		points[5] = line.pt1;
		
		m_grPath.AddSharpNodes(points, 9);

		m_grPath.DimensionAppendD(points[6], points[7], "W");
	}
	else if("173"==strName || "174"==strName)
	{
		if("173"==strName)
		{
			r6 = r5 = r4 = r3 = r2 = r1 = r;
		}

		points[0].Set(m_clip.X1, m_clip.Y1+h1);
		points[1].Set(m_clip.X1+w2, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w-w1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1+h2);
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		points[5].Set(m_clip.X1, m_clip.Y1);
		
		//m_grPath.AddSharpNodes(points, 6);

		grArc.InitRoundCornerArc(r1, points[5], points[4], points[0]);
		m_grPath.AddRoundAngleNode(points[5], grArc);
		if("173"==strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R");
		else
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R1");
		
		grArc.InitRoundCornerArc(r6, points[0], points[5], points[1]);
		m_grPath.AddRoundAngleNode(points[0], grArc);
		if("173"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[0], 0, r6);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R6");
		}
		
		grArc.InitRoundCornerArc(r5, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		if("173"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[1], 0, r5);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R5");
		}
		
		grArc.InitRoundCornerArc(r4, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		if("173"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[2], 0, r4);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R4");
		}
		
		grArc.InitRoundCornerArc(r3, points[3], points[2], points[4]);
		m_grPath.AddRoundAngleNode(points[3], grArc);
		if("173"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[3], 0, r3);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R3");
		}
		
		grArc.InitRoundCornerArc(r2, points[4], points[3], points[5]);
		m_grPath.AddRoundAngleNode(points[4], grArc);
		if("173"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[4], 0, r2);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R2");
		}

		m_grPath.DimensionAppendD(points[4], points[5], "W");
		m_grPath.DimensionAppendD(points[5], points[0], "H1", 4);
		line.pt1.Set(m_clip.X1, m_clip.Y1+h);
		m_grPath.DimensionAppendD(points[5], line.pt1, "H", 28);
		m_grPath.DimensionAppendD(line.pt1, points[1], "W2");
		line.pt1.Set(m_clip.X1+w, m_clip.Y1+h);
		m_grPath.DimensionAppendD(points[2], line.pt1, "W1");
		m_grPath.DimensionAppendD(points[3], points[4], "H2");
	}
	else if("175"==strName || "176"==strName)
	{
		if("175"==strName)
		{
			r8 = r7 = r6 = r5 = r4 = r3 = r2 = r1 = r;
		}
		
		points[0].Set(m_clip.X1, m_clip.Y1+h1);
		points[1].Set(m_clip.X1, m_clip.Y1+h-h1);
		points[2].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w-w1, m_clip.Y1+h);
		points[4].Set(m_clip.X1+w, m_clip.Y1+h-h1);
		points[5].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[6].Set(m_clip.X1+w-w1, m_clip.Y1);
		points[7].Set(m_clip.X1+w1, m_clip.Y1);
		
		//m_grPath.AddSharpNodes(points, 8);
		
		grArc.InitRoundCornerArc(r1, points[7], points[6], points[0]);
		m_grPath.AddRoundAngleNode(points[7], grArc);
		if("175"==strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R");
		else
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R1");
		
		grArc.InitRoundCornerArc(r8, points[0], points[7], points[1]);
		m_grPath.AddRoundAngleNode(points[0], grArc);
		LineRevolve(line, grArc.m_ptC0, points[0], 0, r8);
		if("175"==strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R");
		else
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R8");
		
		grArc.InitRoundCornerArc(r7, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		if("175"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[1], 0, r7);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R7");
		}
		
		grArc.InitRoundCornerArc(r6, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		if("175"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[2], 0, r6);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R6");
		}
		
		grArc.InitRoundCornerArc(r5, points[3], points[2], points[4]);
		m_grPath.AddRoundAngleNode(points[3], grArc);
		if("175"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[3], 0, r5);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R5");
		}
		
		grArc.InitRoundCornerArc(r4, points[4], points[3], points[5]);
		m_grPath.AddRoundAngleNode(points[4], grArc);
		if("175"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[4], 0, r4);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R4");
		}
		
		grArc.InitRoundCornerArc(r3, points[5], points[4], points[6]);
		m_grPath.AddRoundAngleNode(points[5], grArc);
		if("175"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[5], 0, r3);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R3");
		}
		
		grArc.InitRoundCornerArc(r2, points[6], points[5], points[7]);
		m_grPath.AddRoundAngleNode(points[6], grArc);
		if("175"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[6], 0, r2);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R2");
		}
		
		line.pt1.Set(m_clip.X1+w, m_clip.Y1);
		line.pt2.Set(m_clip.X1, m_clip.Y1);
		m_grPath.DimensionAppendD(line, "W");
		m_grPath.DimensionAppendD(points[5], line.pt1, "H1");
		line.pt1.Set(m_clip.X1, m_clip.Y1);
		line.pt2.Set(m_clip.X1, m_clip.Y1+h);
		m_grPath.DimensionAppendD(line, "H");
		m_grPath.DimensionAppendD(line.pt2, points[2], "W1");
		line.pt1.Set(m_clip.X1+w, m_clip.Y1+h);
		m_grPath.DimensionAppendD(points[3], line.pt1, "W1");
		m_grPath.DimensionAppendD(line.pt1, points[4], "H1");
	}
	else if("268"==strName)
	{
		double hs = pSet->GetValue("HS");
		double hd = pSet->GetValue("HD");

		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+hs);
		points[2].Set(m_clip.X1+w1, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w-w2, m_clip.Y1+h2);
		points[4].Set(m_clip.X1+w, m_clip.Y1+hd);
		points[5].Set(m_clip.X1+w, m_clip.Y1);

		m_grPath.AddSharpNodes(points, 6);

		m_grPath.DimensionAppendD(points[5], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "HS");
		line.pt1 = points[2];
		line.pt1.Offset(-w1, 0);
		m_grPath.DimensionAppendD(line.pt1, points[2], "W1");
		line.pt1 = points[3];
		line.pt1.Offset(w2, 0);
		m_grPath.DimensionAppendD(points[3], line.pt1, "W2");
		m_grPath.DimensionAppendD(points[4], points[5], "HD");
		m_grPath.DimensionAppendD(points[4], points[5], "HD");
		line.pt1 = points[2];
		line.pt1.Offset(0, -h1);
		m_grPath.DimensionAppendD(points[2], line.pt1, "H1", 0);
		line.pt1 = points[3];
		line.pt1.Offset(0, -h2);
		m_grPath.DimensionAppendD(points[3], line.pt1, "H2", 0);
	}
	


	m_grPath.PaintTo(&m_dcGraph, &rcDrawing, GRAPH_COLOR_FR);
	
	//将图形由设备坐标系(Y轴向下)转换为数学平面直角坐标系(Y轴向上)
	ConvertGraphCoordinate(&m_dcGraph);
	
	Invalidate(TRUE);
}

void CGrEditor::ProcYixing1()
{
	GR_NODE grNode;
	CRect rect, rcDrawing;
	CString strName=m_picAttr.szPicName;
	CGrPoint points[8], tmp[4];
	GR_LINE line;
	CGrArc grArc;
	
	//////////////////////////////////////////////////////////////////////////
	CUISetting *pSet = &m_uiSettings[m_picAttr.nIndex];
	double w = pSet->GetValue("W");
	double w1 = pSet->GetValue("W1");
	double w2 = pSet->GetValue("W2");
	double h = pSet->GetValue("H");
	double h1 = pSet->GetValue("H1");
	double h2 = pSet->GetValue("H2");
	double r = pSet->GetValue("R");
	double r1 = pSet->GetValue("R1");
	double r2 = pSet->GetValue("R2");
	double r3 = pSet->GetValue("R3");
	double r4 = pSet->GetValue("R4");
	double A = pSet->GetValue("A");
	double l = pSet->GetValue("L");
	//////////////////////////////////////////////////////////////////////////
	
	m_dcGraph.GetClipBox(&rect);
	rcDrawing=rect;
	rcDrawing.DeflateRect(32,32,32,32);
	
	
	memset(&grNode, 0, sizeof(GR_NODE));
	
	
	if("096"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		
		m_grPath.AddSharpNodes(&points[0], 2);

		grArc.InitRoundCornerArc(r, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		m_grPath.DimensionAppendR(grArc.m_ptC0, r, MATH_PI/4, "R");

		m_grPath.AddSharpNodes(&points[3], 1);

		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
	}
	else if("097"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		r = h-h1;
		
		m_grPath.AddSharpNodes(&points[0], 2);
		
		grArc.InitRoundCornerArc(r, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		
		m_grPath.AddSharpNodes(&points[3], 1);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
		points[2].Offset(0, -r);
		m_grPath.DimensionAppendD(points[2], points[3], "H1");
	}
	else if("099"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		
		m_grPath.AddSharpNodes(&points[0], 1);
		
		grArc.InitRoundCornerArc(r1, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		m_grPath.DimensionAppendR(grArc.m_ptC0, r1, MATH_PI*3/4, "R1");
		
		grArc.InitRoundCornerArc(r2, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		m_grPath.DimensionAppendR(grArc.m_ptC0, r2, MATH_PI/4, "R2");
		
		m_grPath.AddSharpNodes(&points[3], 1);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
	}
	else if("100"==strName || "101"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		if("100"==strName)
		{
			r4 = r3 = r2 = r1 = r;
		}
		
		grArc.InitRoundCornerArc(r1, points[0], points[3], points[1]);
		m_grPath.AddRoundAngleNode(points[0], grArc);
		if("100"==strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R");
		else
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R1");
		
		grArc.InitRoundCornerArc(r4, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		if("100"!=strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, r4, MATH_PI*3/4, "R4");
		
		grArc.InitRoundCornerArc(r3, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		if("100"!=strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, r3, MATH_PI/4, "R3");
		
		grArc.InitRoundCornerArc(r2, points[3], points[2], points[0]);
		m_grPath.AddRoundAngleNode(points[3], grArc);
		if("100"!=strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, r2, -MATH_PI/4, "R2");
		
// 		m_grPath.AddSharpNodes(&points[3], 1);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
	}
	else if("102"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);

		grArc.InitRoundCornerArc(r, points[0], points[3], points[1]);
		m_grPath.AddRoundAngleNode(points[0], grArc);
		m_grPath.DimensionAppendR(grArc.m_ptC0, r, -MATH_PI*3/4, "R");

		grArc.InitRoundCornerArc(r, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		
		grArc.InitRoundCornerArc(r, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		
		grArc.InitRoundCornerArc(r, points[3], points[2], points[0]);
		m_grPath.AddRoundAngleNode(points[3], grArc);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
		m_grPath.DimensionAppendD(points[2], points[3], "H1");
	}	
	else if("104"==strName || "105"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		if("104"==strName)
		{
			r4 = r3 = r2 = r1 = r;
		}
		
		grArc.InitRoundCornerArc(r1, points[0], points[3], points[1]);
		m_grPath.AddRoundAngleNode(points[0], grArc);		
		LineRevolve(line, grArc.m_ptC0, points[0], 0, r1);
		if("104"==strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R");
		else
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R1");
		

		grArc.InitRoundCornerArc(r4, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		if("104"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[1], 0, r1);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R4");
		}
		

		grArc.InitRoundCornerArc(r3, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		if("104"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[2], 0, r1);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R3");
		}
	
		grArc.InitRoundCornerArc(r2, points[3], points[2], points[0]);
		m_grPath.AddRoundAngleNode(points[3], grArc);
		if("104"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[3], 0, r2);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R2");
		}
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp[0] = points[1];
		tmp[0].Offset(-w1, 0);
		m_grPath.DimensionAppendD(points[0], tmp[0], "H");
		m_grPath.DimensionAppendD(tmp[0], points[1], "W1");
	}	
	else if("106"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h1);
		points[2].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		
		grArc.InitRoundCornerArc(r, points[0], points[3], points[1]);
		m_grPath.AddRoundAngleNode(points[0], grArc);
		m_grPath.DimensionAppendR(grArc.m_ptC0, r, -MATH_PI*3/4, "R");
		
		grArc.InitRoundCornerArc(r, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		
		grArc.InitRoundCornerArc(r, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		
		grArc.InitRoundCornerArc(r, points[3], points[2], points[0]);
		m_grPath.AddRoundAngleNode(points[3], grArc);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H1");
		tmp[0] = points[2];
		tmp[0].Offset(-w1, 0);
		m_grPath.DimensionAppendD(tmp[0], points[2], "W1");
		tmp[0] = points[3];
		tmp[0].Offset(0, h);
		m_grPath.DimensionAppendD(tmp[0], points[3], "H");
	}	
	else if("108"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w1, m_clip.Y1);
		
		grArc.InitRoundCornerArc(r, points[0], points[3], points[1]);
		m_grPath.AddRoundAngleNode(points[0], grArc);
		m_grPath.DimensionAppendR(grArc.m_ptC0, r, -MATH_PI*3/4, "R");
		
		grArc.InitRoundCornerArc(r, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		
		grArc.InitRoundCornerArc(r, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		
		grArc.InitRoundCornerArc(r, points[3], points[2], points[0]);
		m_grPath.AddRoundAngleNode(points[3], grArc);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W1");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
		tmp[0] = points[1];
		tmp[0].Offset(w, 0);
		m_grPath.DimensionAppendD(points[1], tmp[0], "W");
		tmp[0] = points[2];
		tmp[0].Offset(0, -h1);
		m_grPath.DimensionAppendD(points[2], tmp[0], "H1");
	}	
	else if("110"==strName || "111"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w1, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		if("110"==strName)
			r4 = r3 = r2 = r1 = r;	
		grArc.InitRoundCornerArc(r1, points[0], points[3], points[1]);
		m_grPath.AddRoundAngleNode(points[0], grArc);
		if("110"==strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R");
		else
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R1");
		
		grArc.InitRoundCornerArc(r4, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		if("110"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[1], 0, r4);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R4");
		}
		
		grArc.InitRoundCornerArc(r3, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		if("110"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[2], 0, r3);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R3");
		}
		
		grArc.InitRoundCornerArc(r2, points[3], points[2], points[0]);
		m_grPath.AddRoundAngleNode(points[3], grArc);
		if("110"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[3], 0, r2);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R2");
		}
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
		tmp[0] = points[1];
		tmp[0].Offset(w1, 0);
		m_grPath.DimensionAppendD(points[1], tmp[0], "W1");
		tmp[0] = points[3];
		tmp[0].Offset(0, h1);
		m_grPath.DimensionAppendD(tmp[0], points[3], "H1");
	}	
	else if("112"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w2, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w-w1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);

		grArc.InitRoundCornerArc(r, points[0], points[3], points[1]);
		m_grPath.AddRoundAngleNode(points[0], grArc);
		LineRevolve(line, grArc.m_ptC0, points[0], 0, r);
		m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R");

		grArc.InitRoundCornerArc(r, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		
		grArc.InitRoundCornerArc(r, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		
		grArc.InitRoundCornerArc(r, points[3], points[2], points[0]);
		m_grPath.AddRoundAngleNode(points[3], grArc);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp[0] = points[0];
		tmp[0].Offset(0, h);
		m_grPath.DimensionAppendD(points[0], tmp[0], "H");
		m_grPath.DimensionAppendD(tmp[0], points[1], "W2");
		tmp[0] = points[2];
		tmp[0].Offset(w1, 0);
		m_grPath.DimensionAppendD(points[2], tmp[0], "W1");
	}
	else if("114"==strName || "115"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+((w-w1)/2), m_clip.Y1+h);
		points[2].Set(m_clip.X1+((w-w1)/2)+w1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		if("114"==strName)
			r4 = r3 = r2 = r1 = r;	
		grArc.InitRoundCornerArc(r1, points[0], points[3], points[1]);
		m_grPath.AddRoundAngleNode(points[0], grArc);
		if("114"==strName)
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R");
		else
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R1");
		
		grArc.InitRoundCornerArc(r4, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		if("114"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[1], 0, r4);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R4");
		}
		
		grArc.InitRoundCornerArc(r3, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		if("114"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[2], 0, r3);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R3");
		}
		
		grArc.InitRoundCornerArc(r2, points[3], points[2], points[0]);
		m_grPath.AddRoundAngleNode(points[3], grArc);
		if("114"!=strName)
		{
			LineRevolve(line, grArc.m_ptC0, points[3], 0, r2);
			m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R2");
		}
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp[0] = points[1];
		tmp[0].Offset(-(w-w1)/2, 0);
		m_grPath.DimensionAppendD(points[0], tmp[0], "H");
		m_grPath.DimensionAppendD(points[1], points[2], "W1");
	}	
	else if("119"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1+w1, m_clip.Y1+h1);
		points[2].Set(m_clip.X1+w1+w2, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);

		//m_grPath.AddSharpNodes(points, 4);

		grArc.InitRoundCornerArc(r1, points[0], points[3], points[1]);
		m_grPath.AddRoundAngleNode(points[0], grArc);
		LineRevolve(line, grArc.m_ptC0, points[0], 0, r1);
		m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R1");
		
		grArc.InitRoundCornerArc(r4, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		LineRevolve(line, grArc.m_ptC0, points[1], 0, r4);
		m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R4");
	
		grArc.InitRoundCornerArc(r3, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		LineRevolve(line, grArc.m_ptC0, points[2], 0, r3);
		m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R3");
		
		grArc.InitRoundCornerArc(r2, points[3], points[2], points[0]);
		m_grPath.AddRoundAngleNode(points[3], grArc);
		LineRevolve(line, grArc.m_ptC0, points[3], 0, r2);
		m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R2");
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp[0] = points[0];
		tmp[0].Offset(0, h1);
		m_grPath.DimensionAppendD(points[0], tmp[0], "H1");
		tmp[1] = tmp[0] = points[2];
		tmp[0].Offset(-w2-w1, 0);
		tmp[1].Offset(-w2, 0);
		m_grPath.DimensionAppendD(tmp[0], tmp[1], "W1");
		m_grPath.DimensionAppendD(tmp[1], points[2], "W2");
		tmp[0] = points[3];
		tmp[0].Offset(0, h);
		m_grPath.DimensionAppendD(tmp[0], points[3], "H");
	}
	else if("265"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);

		grArc.InitRoundCornerArc(r, points[0], points[3], points[1]);
		m_grPath.AddRoundAngleNode(points[0], grArc);
		m_grPath.DimensionAppendR(grArc.m_ptC0, r, MATH_PI/4, "R");

		grArc.InitRoundCornerArc(r, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		
		grArc.InitRoundCornerArc(r, points[2], points[1], points[3]);
		m_grPath.AddRoundAngleNode(points[2], grArc);
		
		grArc.InitRoundCornerArc(r, points[3], points[2], points[0]);
		m_grPath.AddRoundAngleNode(points[3], grArc);

		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");

		CGrPoint ptC0;
		double d = pSet->GetValue("D");
		double s = pSet->GetValue("S");
		double temp;
		ptC0.Set(m_clip.X1+w-d, m_clip.Y1+(h/2)+(s/2));
		grArc.InitCircle(r1, ptC0);
		m_grPath.AddSplitCircle(grArc);
		temp = r1*2;
		if(temp<80)
			temp=80;
		points[5] = grArc.m_ptC0;
		points[5].Offset(-temp, 16);
		m_grPath.DimensionAppendR(points[5], r1, MATH_PI, "R1");
		points[5] = grArc.m_ptC0;
		points[5].Offset(d, 0);
		m_grPath.DimensionAppendD(grArc.m_ptC0, points[5], "D", 40);

		ptC0.Offset(0, -s);
		grArc.InitCircle(r1, ptC0);
		m_grPath.AddSplitCircle(grArc);
		points[5] = grArc.m_ptC0;
		points[5].Offset(0, s/2);
		m_grPath.DimensionAppendD(points[5], grArc.m_ptC0, "S", 40);
	}
	else if("280"==strName)
	{
		double d;
		A = (A*MATH_PI/180);
		if(A>(MATH_PI/2))
		{
			d = sin(A-(MATH_PI/2))*l;
			h = cos(A-(MATH_PI/2))*l;
			points[2].Set(m_clip.X1+w+d, m_clip.Y1+h);
		}
		else
		{
			d = sin((MATH_PI/2)-A)*l;
			h = cos((MATH_PI/2)-A)*l;
			points[2].Set(m_clip.X1+w-d, m_clip.Y1+h);
		}
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);

		m_grPath.AddSharpNodes(&points[0], 1);
		
		grArc.InitRoundCornerArc(r, points[1], points[0], points[2]);
		m_grPath.AddRoundAngleNode(points[1], grArc);
		LineRevolve(line, grArc.m_ptC0, points[1], 0, r);
		m_grPath.DimensionAppendR(grArc.m_ptC0, line.pt1, "R");
		
		m_grPath.AddSharpNodes(&points[2], 1);
		
		m_grPath.AddSharpNodes(&points[3], 1);

		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[2], points[3], "H");

		points[4] = points[3];
		points[4].Offset(-min(w, h)/3, 0);
		LineRevolve(line, points[3], points[2], 0, min(w,h)/3);
		points[5] = line.pt1;
		m_grPath.DimensionAppendA(points[3], points[4], points[5], "A", A>MATH_PI);
	}


	
	m_grPath.PaintTo(&m_dcGraph, &rcDrawing, GRAPH_COLOR_FR);
	
	//将图形由设备坐标系(Y轴向下)转换为数学平面直角坐标系(Y轴向上)
	ConvertGraphCoordinate(&m_dcGraph);
	
	Invalidate(TRUE);
}

void CGrEditor::ProcYixing2()
{
	GR_NODE grNode;
	CRect rect, rcDrawing;
	CString strName=m_picAttr.szPicName;
	CGrPoint points[8], tmp[4];
	GR_LINE line;
	CGrArc grArc;
	
	//////////////////////////////////////////////////////////////////////////
	CUISetting *pSet = &m_uiSettings[m_picAttr.nIndex];
	double w = pSet->GetValue("W");
	double w1 = pSet->GetValue("W1");
	double w2 = pSet->GetValue("W2");
	double h = pSet->GetValue("H");
	double h1 = pSet->GetValue("H1");
	double h2 = pSet->GetValue("H2");
	double r = pSet->GetValue("R");
	double r1 = pSet->GetValue("R1");
	double r2 = pSet->GetValue("R2");
	double r3 = pSet->GetValue("R3");
	double r4 = pSet->GetValue("R4");
	double A = pSet->GetValue("A");
	double l = pSet->GetValue("L");
	double d = pSet->GetValue("D");
	double s1 = pSet->GetValue("S1");
	double s2 = pSet->GetValue("S2");
	//////////////////////////////////////////////////////////////////////////
	
	m_dcGraph.GetClipBox(&rect);
	rcDrawing=rect;
	rcDrawing.DeflateRect(32,32,32,32);
	
	
	memset(&grNode, 0, sizeof(GR_NODE));
	
	
	
	if("177"==strName)
	{
		r = (w/2);
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h-r);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h-r);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		

		m_grPath.AddSharpNodes(&points[0], 1);

		tmp[0].Set(m_clip.X1+r, m_clip.Y1+h-r);
		grArc.InitArc(r, tmp[0], points[1], points[2]);
		m_grPath.AddArcNode(grArc);
		
		m_grPath.AddSharpNodes(&points[3], 1);

		m_grPath.DimensionAppendD(points[3], points[0], "W");
		points[1] = points[0];
		points[1].Offset(0, h);
		m_grPath.DimensionAppendD(points[0], points[1], "H");
	}
	else if("177"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		
		
		m_grPath.AddSharpNodes(&points[0], 1);
		
		tmp[0].Set(m_clip.X1+r, m_clip.Y1+h-r);
		grArc.InitArc(r, tmp[0], points[1], points[2]);
		m_grPath.AddArcNode(grArc);
		
		m_grPath.AddSharpNodes(&points[3], 1);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		points[1] = points[0];
		points[1].Offset(0, h);
		m_grPath.DimensionAppendD(points[0], points[1], "H");
	}
	else if("178"==strName)
	{
		double d;
		d = sqrt(r*r-(w*w/4));
		if(d>=0.0f)
		{
			points[0].Set(m_clip.X1, m_clip.Y1);
			points[1].Set(m_clip.X1, m_clip.Y1+h);
			points[2].Set(m_clip.X1+w, m_clip.Y1+h);
			points[3].Set(m_clip.X1+w, m_clip.Y1);
			
			m_grPath.AddSharpNodes(&points[0], 1);
			
			tmp[0].Set(m_clip.X1+(w/2), m_clip.Y1+h-d);		
			grArc.InitArc(r, tmp[0], points[1], points[2]);
			m_grPath.AddArcNode(grArc);
			
			m_grPath.AddSharpNodes(&points[3], 1);
			
			m_grPath.DimensionAppendD(points[3], points[0], "W");
			points[1] = points[0];
			points[1].Offset(0, h);
			m_grPath.DimensionAppendD(points[0], points[1], "H");
			m_grPath.DimensionAppendR(grArc.m_ptC0, r, MATH_PI/2, "R");
		}
	}
	else if("179"==strName)
	{
		double d;
		d = h2-h1;
		if(d>0.0f)
		{
			r = (d/2)+((w*w)/(8*d));
			points[0].Set(m_clip.X1, m_clip.Y1);
			points[1].Set(m_clip.X1, m_clip.Y1+h1);
			points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
			points[3].Set(m_clip.X1+w, m_clip.Y1);
			
			m_grPath.AddSharpNodes(&points[0], 1);
			
			tmp[0].Set(m_clip.X1+(w/2), m_clip.Y1+h2-r);		
			grArc.InitArc(r, tmp[0], points[1], points[2]);
			m_grPath.AddArcNode(grArc);
			
			m_grPath.AddSharpNodes(&points[3], 1);
			
			m_grPath.DimensionAppendD(points[3], points[0], "W");
			m_grPath.DimensionAppendD(points[2], points[3], "H1");
			points[1] = points[0];
			points[1].Offset(0, h2);
			m_grPath.DimensionAppendD(points[0], points[1], "H2");
		}
	}
	else if("180"==strName)
	{
		double d;
		d = sqrt(r*r-(w*w/4));
		if(d>=0.0f)
		{
			d = r-d;
			points[0].Set(m_clip.X1, m_clip.Y1);
			points[1].Set(m_clip.X1, m_clip.Y1+h-d);
			points[2].Set(m_clip.X1+w, m_clip.Y1+h-d);
			points[3].Set(m_clip.X1+w, m_clip.Y1);
			
			m_grPath.AddSharpNodes(&points[0], 1);
			
			tmp[0].Set(m_clip.X1+(w/2), m_clip.Y1+h-r);
			grArc.InitArc(r, tmp[0], points[1], points[2]);
			m_grPath.AddArcNode(grArc);
			
			m_grPath.AddSharpNodes(&points[3], 1);
			
			m_grPath.DimensionAppendD(points[3], points[0], "W");
			points[2] = points[3];
			points[2].Offset(0, h);
			m_grPath.DimensionAppendD(points[2], points[3], "H");
			m_grPath.DimensionAppendR(grArc.m_ptC0, r, MATH_PI/2, "R");
		}
	}
	else if("181"==strName)
	{
		double d;
		d = h-h1;
		if(d>0.0f)
		{
			r = (d/2)+((w1*w1)/(8*d));
			points[0].Set(m_clip.X1+((w1-w)/2), m_clip.Y1);
			points[1].Set(m_clip.X1, m_clip.Y1+h1);
			points[2].Set(m_clip.X1+w1, m_clip.Y1+h1);
			points[3].Set(m_clip.X1+((w1-w)/2)+w, m_clip.Y1);
			//m_grPath.AddSharpNodes(&points[0], 4);
			
			m_grPath.AddSharpNodes(&points[0], 1);
			
			tmp[0].Set(m_clip.X1+(w1/2), m_clip.Y1+h-r);
			grArc.InitArc(r, tmp[0], points[1], points[2]);
			m_grPath.AddArcNode(grArc);
			
			m_grPath.AddSharpNodes(&points[3], 1);
			
			m_grPath.DimensionAppendD(points[3], points[0], "W");
			line.pt1 = line.pt2 = points[2];
			line.pt1.Offset(0, (h-h1));
			line.pt2.Offset(0, -h1);
			m_grPath.DimensionAppendD(line, "H");
			line.pt1 = line.pt2 = points[1];
			line.pt1.Offset(0, -h1);
			m_grPath.DimensionAppendD(line, "H1");
			line.pt1 = points[1];
			line.pt2 = points[2];
			line.pt1.Offset(0, (h-h1));
			line.pt2.Offset(0, (h-h1));
			m_grPath.DimensionAppendD(line, "W1");
		}
	}
	else if("182"==strName)
	{
		double d;
		d = sqrt(r*r-(w*w/4));
		if(d>=0.0f)
		{
			points[0].Set(m_clip.X1, m_clip.Y1);
			points[1].Set(m_clip.X1, m_clip.Y1+h);
			points[2].Set(m_clip.X1+w, m_clip.Y1+h);
			points[3].Set(m_clip.X1+w, m_clip.Y1);
			
			grArc.InitRoundCornerArc(r1, points[0], points[3], points[1]);
			m_grPath.AddRoundAngleNode(points[0], grArc);
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R1");
			
			tmp[0].Set(m_clip.X1+(w/2), m_clip.Y1+h-d);
			grArc.InitArc(r, tmp[0], points[1], points[2]);
			m_grPath.AddArcNode(grArc);
			m_grPath.DimensionAppendR(grArc.m_ptC0, r, MATH_PI/2, "R");
			
			grArc.InitRoundCornerArc(r2, points[3], points[2], points[0]);
			m_grPath.AddRoundAngleNode(points[3], grArc);
			m_grPath.DimensionAppendR(grArc.m_ptC0, r2, -MATH_PI/4, "R2");
		
			m_grPath.DimensionAppendD(points[3], points[0], "W");
			points[2] = points[3];
			points[2].Offset(0, h);
			m_grPath.DimensionAppendD(points[0], points[1], "H");
		}
	}
	else if("183"==strName)
	{
		double d;
		d = h2-h1;
		if(d>0.0f)
		{
			r = (d/2)+((w*w)/(8*d));
			points[0].Set(m_clip.X1, m_clip.Y1);
			points[1].Set(m_clip.X1, m_clip.Y1+h1);
			points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
			points[3].Set(m_clip.X1+w, m_clip.Y1);
			
			grArc.InitRoundCornerArc(r1, points[0], points[3], points[1]);
			m_grPath.AddRoundAngleNode(points[0], grArc);
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R1");
			
			tmp[0].Set(m_clip.X1+(w/2), m_clip.Y1+h2-r);		
			grArc.InitArc(r, tmp[0], points[1], points[2]);
			m_grPath.AddArcNode(grArc);
			
			grArc.InitRoundCornerArc(r2, points[3], points[2], points[0]);
			m_grPath.AddRoundAngleNode(points[3], grArc);
			m_grPath.DimensionAppendR(grArc.m_ptC0, r2, -MATH_PI/4, "R2");
			
			m_grPath.DimensionAppendD(points[3], points[0], "W");
			m_grPath.DimensionAppendD(points[2], points[3], "H1");
			points[1] = points[0];
			points[1].Offset(0, h2);
			m_grPath.DimensionAppendD(points[0], points[1], "H2");
		}
	}
	else if("184"==strName)
	{
		double d;

		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);

		m_grPath.DimensionAppendD(points[0], points[1], "H");

		d = sqrt(r1*r1-(w*w/4));
		if(d>=0.0f)
		{
			tmp[0].Set(m_clip.X1+(w/2), m_clip.Y1+h-d);
			grArc.InitArc(r1, tmp[0], points[1], points[2]);
			m_grPath.AddArcNode(grArc);
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, MATH_PI/2, "R1");
		}

		d = sqrt(r2*r2-(w*w/4));
		if(d>=0.0f)
		{
			tmp[0].Set(m_clip.X1+(w/2), m_clip.Y1+d);
			grArc.InitArc(r2, tmp[0], points[3], points[0]);
			m_grPath.AddArcNode(grArc);
			m_grPath.DimensionAppendR(grArc.m_ptC0, r2, -MATH_PI/2, "R2");
		}
		line.pt1 = points[3];
		line.pt1.Offset(0, -(r2-d));
		line.pt2 = points[0];
		line.pt2.Offset(0, -(r2-d));
		m_grPath.DimensionAppendD(line, "W");

		m_grPath.Offset(0, r2-d);
	}
	else if("188"==strName)
	{
		double d;
		
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);

		d = (h1-h)/2;
		if(d>0.0f)
		{
			r = (d/2)+((w*w)/(8*d));
			
			tmp[0].Set(m_clip.X1+(w/2), m_clip.Y1+h-(r-d));		
			grArc.InitArc(r, tmp[0], points[1], points[2]);
			m_grPath.AddArcNode(grArc);

			tmp[0].Set(m_clip.X1+(w/2), m_clip.Y1+r-d);
			grArc.InitArc(r, tmp[0], points[3], points[0]);
			m_grPath.AddArcNode(grArc);
			
			m_grPath.DimensionAppendD(points[0], points[1], "H");
			line.pt1.Set(m_clip.X1+w, m_clip.Y1-d+h1);
			line.pt2.Set(m_clip.X1+w, m_clip.Y1-d);
			m_grPath.DimensionAppendD(line, "H1");
			line.pt1 = line.pt2;
			line.pt2.Set(m_clip.X1, m_clip.Y1-d);
			m_grPath.DimensionAppendD(line, "W");


			m_grPath.Offset(0, d);
		}
	}
	else if("189"==strName)
	{
		CGrPoint c1, c2, c3, c4;
		c1.Set(m_clip.X1+w/2, m_clip.Y1+r1);
		c2.Set(m_clip.X1+w-r2, m_clip.Y1+(h/2));
		c3.Set(m_clip.X1+w/2, m_clip.Y1+h-r3);
		c4.Set(m_clip.X1+r4, m_clip.Y1+(h/2));

		tmp[0].Set(m_clip.X1+r4, m_clip.Y1+(h/2)-r4);
		tmp[1].Set(m_clip.X1+r4, m_clip.Y1+(h/2)+r4);
		grArc.InitArc(r4, c4, tmp[0], tmp[1]);
		points[0] = grArc.RetrieveCrossPoint(c1, r1, TRUE);
		points[1] = grArc.RetrieveCrossPoint(c3, r3, TRUE);

		tmp[0].Set(m_clip.X1+w-r2, m_clip.Y1+(h/2)+r2);
		tmp[1].Set(m_clip.X1+w-r2, m_clip.Y1+(h/2)-r2);
		grArc.InitArc(r2, c2, tmp[0], tmp[1]);		
		points[2] = grArc.RetrieveCrossPoint(c3, r3, TRUE);
		points[3] = grArc.RetrieveCrossPoint(c1, r1, TRUE);

		//m_grPath.AddSharpNodes(&points[0], 4);

		grArc.InitArc(r4, c4, points[0], points[1]);
		m_grPath.AddArcNode(grArc);
		
		grArc.InitArc(r3, c3, points[1], points[2]);
		m_grPath.AddArcNode(grArc);
		
		grArc.InitArc(r2, c2, points[2], points[3]);
		m_grPath.AddArcNode(grArc);
		
		grArc.InitArc(r1, c1, points[3], points[0]);
		m_grPath.AddArcNode(grArc);

		tmp[1] = tmp[0] = c4;
		tmp[1].Offset(-r4, 0);
		tmp[0].Offset(-r4+(w/3), 0);
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R4");
		tmp[1] = tmp[0] = c3;
		tmp[1].Offset(0, r3);
		tmp[0].Offset(0, r3-(h/3));
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R3");
		tmp[1] = tmp[0] = c2;
		tmp[1].Offset(r2, 0);
		tmp[0].Offset(r4-(w/3), 0);
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R2");
		tmp[1] = tmp[0] = c1;
		tmp[1].Offset(0, -r1);
		tmp[0].Offset(0, -r3+(h/3));
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R1");
	}
	else if("190"==strName)
	{
		double d;
		
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h1);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 4);
		
		d = h;
		if(d>0.0f)
		{
			r = (d/2)+((w*w)/(8*d));
			
			m_grPath.AddSharpNodes(&points[0], 1);
			
			tmp[0].Set(m_clip.X1+(w/2), m_clip.Y1+h1-(r-d));
			grArc.InitArc(r, tmp[0], points[1], points[2]);
			m_grPath.AddArcNode(grArc);
			
			m_grPath.AddSharpNodes(&points[3], 1);

			m_grPath.DimensionAppendD(points[3], points[0], "W");
			m_grPath.DimensionAppendD(points[0], points[1], "H1");
			tmp[0] = points[2];
			tmp[0].Offset(0, h);
			m_grPath.DimensionAppendD(tmp[0], points[2], "H");
		}
	}
	else if("193"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h2);
		points[2].Set(m_clip.X1+w/2, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		if(h1<h && h2<h)
		{
			double fTemp;

			m_grPath.AddSharpNodes(&points[0], 1);

			w1 = sqrt((w/2)*(w/2)+(h-h2)*(h-h2));
			w2 = sqrt((w/2)*(w/2)+(h-h1)*(h-h1));

			fTemp = RetrieveAngleOfTriangle(r1, r1, w1);
			LineRevolve(line, points[2], points[1], fTemp, r1);
			tmp[0] = line.pt1;
			grArc.InitArc(r1, tmp[0], points[1], points[2]);
			m_grPath.AddArcNode(grArc);
			grArc.GetArcMidpoint(tmp[1]);
			LineRevolve(line, tmp[1], tmp[0], 0, w/2);
			m_grPath.DimensionAppendR(line.pt1, tmp[1], "R1");
			
			fTemp = RetrieveAngleOfTriangle(r2, r2, w2);
			LineRevolve(line, points[3], points[2], fTemp, r2);
			tmp[0] = line.pt1;
			grArc.InitArc(r2, tmp[0], points[2], points[3]);
			m_grPath.AddArcNode(grArc);
			grArc.GetArcMidpoint(tmp[1]);
			LineRevolve(line, tmp[1], tmp[0], 0, w/2);
			m_grPath.DimensionAppendR(line.pt1, tmp[1], "R2");
			
			m_grPath.AddSharpNodes(&points[4], 1);

			m_grPath.DimensionAppendD(points[4], points[0], "W");
			m_grPath.DimensionAppendD(points[0], points[1], "H2");
			m_grPath.DimensionAppendD(points[3], points[4], "H1", 12);
			tmp[0] = points[4];
			tmp[0].Offset(0, h);
			m_grPath.DimensionAppendD(tmp[0], points[4], "H", 24);
		}
	}
	else if("195"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);

		tmp[0].Set(m_clip.X1+w/2, m_clip.Y1+h2);
	}	
	else if("197"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);

		w1 = sqrt(w*w+(h-h1)*(h-h1));
		r = (d/2)+((w1*w1)/(8*d));

		LineRevolve(line, points[1], points[2], 0, w1/2);
		tmp[0] = line.pt1;
		LineRevolve(line, tmp[0], points[1], MATH_PI/2, (r-d));
		tmp[1] = line.pt1;
		LineRevolve(line, tmp[0], points[2], MATH_PI/2, d);
		tmp[2] = line.pt1;

		grArc.InitArc(r, tmp[1], points[1], points[2]);

		m_grPath.AddSharpNodes(&points[0], 1);

		m_grPath.AddArcNode(grArc);

		m_grPath.AddSharpNodes(&points[3], 1);

		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
		m_grPath.DimensionAppendD(points[2], points[3], "H1");
		m_grPath.DimensionAppendD(tmp[0], tmp[2], "D", 8);
	}	
	else if("199"==strName)
	{
		r = w;
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h-r);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		
		tmp[0] = points[0];
		tmp[0].Offset(0, (h-r));
		grArc.InitArc(r, tmp[0], points[1], points[2]);

		m_grPath.AddSharpNodes(&points[0], 1);
		
		m_grPath.AddArcNode(grArc);

		m_grPath.AddSharpNodes(&points[3], 1);

		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
	}
	else if("203"==strName)
	{
	}
	else if("204"==strName)
	{
		double temp;
		GR_RECT grRect;
		r = w;
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h+s2);
		points[3].Set(m_clip.X1+w, m_clip.Y1-s1);
		//m_grPath.AddSharpNodes(&points[0], 4);

		w1 = sqrt(w*w+s1*s1);
		w2 = sqrt(w*w+s2*s2);

		temp = acos((w2/2)/r2);
		LineRevolve(line, points[1], points[2], -temp, r2);
		tmp[2] = line.pt1;

		temp = acos((w1/2)/r1);
		LineRevolve(line, points[0], points[3], temp, r1);
		tmp[1] = line.pt1;

		grArc.InitArc(r2, tmp[2], points[1], points[2]);
		m_grPath.AddArcNode(grArc);
		grArc.GetArcMidpoint(tmp[0]);
		LineRevolve(line, tmp[0], grArc.m_ptC0, 0, r2/3);
		m_grPath.DimensionAppendR(line.pt1, tmp[0], "R2");

		grArc.InitArc(r1, tmp[1], points[3], points[0]);
		m_grPath.AddArcNode(grArc);
		grArc.GetArcMidpoint(tmp[0]);
		LineRevolve(line, tmp[0], grArc.m_ptC0, 0, r1/3);
		m_grPath.DimensionAppendR(line.pt1, tmp[0], "R1");
		grArc.GetOutline(grRect);

		temp = (m_clip.Y1-grRect.fY0);

		m_grPath.DimensionAppendD(points[0], points[1], "H");
		tmp[1] = tmp[0] = points[0];
		tmp[0].Offset(0, -max(s1, temp));
		tmp[1].Offset(w, -max(s1, temp));
		m_grPath.DimensionAppendD(tmp[1], tmp[0], "W");
		tmp[0] = points[3];
		tmp[0].Offset(0, s1);
		m_grPath.DimensionAppendD(tmp[0], points[3], "S1");
		tmp[0] = points[2];
		tmp[0].Offset(0, -s2);
		m_grPath.DimensionAppendD(points[2], tmp[0], "S2");

		if(temp>0)
			m_grPath.Offset(0, temp);
	}
	else if("208"==strName)
	{
		double temp;
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 5);

		temp = sqrt((h-h1)*(h-h1)+(w-w1)*(w-w1));
		temp = RetrieveAngleOfTriangle(r, r, temp);
		LineRevolve(line, points[3], points[2], temp, r);
		grArc.InitArc(r, line.pt1, points[2], points[3]);
		
		m_grPath.AddSharpNodes(&points[0], 1);
		m_grPath.AddSharpNodes(&points[1], 1);
		m_grPath.AddArcNode(grArc);
		m_grPath.AddSharpNodes(&points[4], 1);

		m_grPath.DimensionAppendD(points[4], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
		m_grPath.DimensionAppendD(points[1], points[2], "W1");
		m_grPath.DimensionAppendD(points[3], points[4], "H1");
		grArc.GetArcMidpoint(tmp[0]);
		LineRevolve(line, tmp[0], grArc.m_ptC0, 0, w/2);
		m_grPath.DimensionAppendR(line.pt1, tmp[0], "R");
	}
	else if("209"==strName)
	{
		double temp;
		A = (A*MATH_PI/180);
		temp = (h-h1)/tan(A);
		w1 = w-temp;

		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w1, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[4].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 5);

		grArc.InitRoundCornerArc(r, points[2], points[1], points[3]);
		
		m_grPath.AddSharpNodes(&points[0], 1);
		m_grPath.AddSharpNodes(&points[1], 1);
		m_grPath.AddArcNode(grArc);
		m_grPath.AddSharpNodes(&points[3], 1);
		m_grPath.AddSharpNodes(&points[4], 1);

		grArc.GetArcMidpoint(tmp[0]);
		m_grPath.DimensionAppendR(grArc.m_ptC0, tmp[0], "R");

		temp = (w-w1);//*3/4;
		LineRevolve(line, points[3], points[2], A, temp);
		tmp[0] = line.pt1;
		LineRevolve(line, points[3], points[2], 0, temp);
		tmp[1] = line.pt1;
		m_grPath.DimensionAppendA(points[3], tmp[0], tmp[1], "A", A>MATH_PI);

		m_grPath.DimensionAppendD(points[4], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
		m_grPath.DimensionAppendD(points[3], points[4], "H1");
	}


	m_grPath.PaintTo(&m_dcGraph, &rcDrawing, GRAPH_COLOR_FR);
	
	//将图形由设备坐标系(Y轴向下)转换为数学平面直角坐标系(Y轴向上)
	ConvertGraphCoordinate(&m_dcGraph);
	
	Invalidate(TRUE);
}

void CGrEditor::ProcYixing3()
{
	GR_NODE grNode;
	CRect rect, rcDrawing;
	CString strName=m_picAttr.szPicName;
	CGrPoint points[8], tmp[4], ptC0, ptC1;
	GR_LINE line;
	CGrArc grArc;
	double rx;
	
	//////////////////////////////////////////////////////////////////////////
	CUISetting *pSet = &m_uiSettings[m_picAttr.nIndex];
	double w = pSet->GetValue("W");
	double w1 = pSet->GetValue("W1");
	double w2 = pSet->GetValue("W2");
	double h = pSet->GetValue("H");
	double h1 = pSet->GetValue("H1");
	double h2 = pSet->GetValue("H2");
	double r = pSet->GetValue("R");
	double r1 = pSet->GetValue("R1");
	double r2 = pSet->GetValue("R2");
	double r3 = pSet->GetValue("R3");
	double r4 = pSet->GetValue("R4");
	double A = pSet->GetValue("A");
	double a1 = pSet->GetValue("A1");
	double a2 = pSet->GetValue("A2");
	double b = pSet->GetValue("B");
	double b1 = pSet->GetValue("B1");
	double b2 = pSet->GetValue("B2");
	double l = pSet->GetValue("L");
	double d = pSet->GetValue("D");
	double s1 = pSet->GetValue("S1");
	double s2 = pSet->GetValue("S2");
	//////////////////////////////////////////////////////////////////////////
	
	m_dcGraph.GetClipBox(&rect);
	rcDrawing=rect;
	rcDrawing.DeflateRect(32,32,32,32);
	
	
	memset(&grNode, 0, sizeof(GR_NODE));

	
	if("211"==strName || "214"==strName || "218"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		
		if("214"==strName)
		{
			grArc.InitRoundCornerArc(r1, points[0], points[3], points[1]);
			m_grPath.AddRoundAngleNode(points[0], grArc);
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, -MATH_PI*3/4, "R1");
		}
		else if("218"==strName)
		{
			tmp[1] = tmp[0] = points[0];
			tmp[0].Offset(0, r1);
			tmp[1].Offset(r1, 0);
			grArc.InitArc(r1, points[0], tmp[0], tmp[1]);
			m_grPath.AddArcNode(grArc, FALSE);
			m_grPath.DimensionAppendR(grArc.m_ptC0, r1, MATH_PI/4, "R1");
		}
		else
		{
			m_grPath.AddSharpNodes(&points[0], 1);
		}
		
		ptC0 = points[1];
		ptC0.Offset(0, r);
		
		rx = ((w*w)/(8*r)) - (r/2);
		
		ptC1 = ptC0;
		ptC1.Offset(w/2, -rx);
		
		LineRevolve(line, ptC0, ptC1, 0, r);
		tmp[0] = line.pt1;
		grArc.InitArc(r, ptC0, tmp[0], points[1]);
		m_grPath.AddArcNode(grArc, FALSE);
		grArc.GetArcMidpoint(tmp[1]);
		m_grPath.DimensionAppendR(ptC0, tmp[1], "R");
		
		ptC0.Offset(w, 0);
		
		LineRevolve(line, ptC0, ptC1, 0, r);
		tmp[2] = line.pt1;
		grArc.InitArc(rx, ptC1, tmp[0], tmp[2]);
		m_grPath.AddArcNode(grArc, TRUE);
		
		grArc.InitArc(r, ptC0, points[2], tmp[2]);
		m_grPath.AddArcNode(grArc, FALSE);
		
		if("214"==strName)
		{
			grArc.InitRoundCornerArc(r2, points[3], points[2], points[0]);
			m_grPath.AddRoundAngleNode(points[3], grArc);
			m_grPath.DimensionAppendR(grArc.m_ptC0, r2, -MATH_PI/4, "R2");
		}
		else if("218"==strName)
		{
			tmp[1] = tmp[0] = points[3];
			tmp[0].Offset(-r2, 0);
			tmp[1].Offset(0, r2);
			grArc.InitArc(r2, points[3], tmp[0], tmp[1]);
			m_grPath.AddArcNode(grArc, FALSE);
			m_grPath.DimensionAppendR(grArc.m_ptC0, r2, MATH_PI*3/4, "R2");
		}
		else
		{
			m_grPath.AddSharpNodes(&points[3], 1);
		}
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
	}
	if("212"==strName || "215"==strName || "217"==strName || "219"==strName)
	{
		double fTemp;
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);

		if("215"==strName)
		{
			grArc.InitRoundCornerArc(r2, points[0], points[3], points[1]);
			m_grPath.AddRoundAngleNode(points[0], grArc);
			m_grPath.DimensionAppendR(grArc.m_ptC0, r2, -MATH_PI*3/4, "R2");
		}
		else if("217"==strName)
		{
			tmp[0] = tmp[1] = points[0];
			tmp[0].Offset(w1, 0);
			tmp[1].Offset(0, h1);
			m_grPath.AddSharpNodes(&tmp[0], 1);
			m_grPath.AddSharpNodes(&tmp[1], 1);
		}
		else
		{
			m_grPath.AddSharpNodes(&points[0], 1);
		}
	
		ptC0 = points[1];
		ptC0.Offset(0, r1);

		fTemp = sqrt((r+r1)*(r+r1)-(w*w/4));
		if(fTemp>0)
		{
			ptC1 = ptC0;
			ptC1.Offset(w/2, -fTemp);

			LineRevolve(line, ptC0, ptC1, 0, r1);
			tmp[0] = line.pt1;
			grArc.InitArc(r1, ptC0, tmp[0], points[1]);
			m_grPath.AddArcNode(grArc, FALSE);
			
			ptC0.Offset(w, 0);
			
			LineRevolve(line, ptC0, ptC1, 0, r1);
			tmp[2] = line.pt1;
			grArc.InitArc(r, ptC1, tmp[0], tmp[2]);
			m_grPath.AddArcNode(grArc, TRUE);
			grArc.GetArcMidpoint(tmp[1]);
			m_grPath.DimensionAppendR(ptC1, tmp[1], "R");
			
			grArc.InitArc(r1, ptC0, points[2], tmp[2]);
			m_grPath.AddArcNode(grArc, FALSE);
			grArc.GetArcMidpoint(tmp[1]);
			m_grPath.DimensionAppendR(ptC0, tmp[1], "R1");
		}


		if("215"==strName)
		{
			grArc.InitRoundCornerArc(r3, points[3], points[2], points[0]);
			m_grPath.AddRoundAngleNode(points[3], grArc);
			m_grPath.DimensionAppendR(grArc.m_ptC0, r3, -MATH_PI/4, "R3");
		}
		else if("217"==strName)
		{
			tmp[0] = tmp[1] = points[3];
			tmp[0].Offset(0, h1);
			tmp[1].Offset(-w1, 0);
			m_grPath.AddSharpNodes(&tmp[0], 1);
			m_grPath.AddSharpNodes(&tmp[1], 1);
			m_grPath.DimensionAppendD(tmp[0], points[3], "H1");
			m_grPath.DimensionAppendD(points[3], tmp[1], "W1", 0);
		}
		else
		{
			m_grPath.AddSharpNodes(&points[3], 1);
		}

		if("219"==strName)
		{
			r2 = (h1/2)+((w1*w1)/(8*h1));
			tmp[0].Set(m_clip.X1+(w/2), m_clip.Y1+h1-r2);
			tmp[1].Set(m_clip.X1+(w/2)-(w1/2), m_clip.Y1);
			tmp[2].Set(m_clip.X1+(w/2)+(w1/2), m_clip.Y1);
			grArc.InitArc(r2, tmp[0], tmp[1], tmp[2]);
			m_grPath.AddArcNode(grArc, FALSE);
			m_grPath.DimensionAppendD(tmp[2], tmp[1], "W1", 8);
			tmp[1].Offset(w1/2, 0);
			tmp[2] = tmp[1];
			tmp[2].Offset(0, h1);
			m_grPath.DimensionAppendD(tmp[2], tmp[1], "H1", 0);
		}
		
		m_grPath.DimensionAppendD(points[3], points[0], "W", 24);
		tmp[0] = points[0];
		tmp[0].Offset(0, h);
		m_grPath.DimensionAppendD(points[0], tmp[0], "H");
	}
	else if("213"==strName)
	{
		double fTemp;
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h1);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 4);
		
		m_grPath.AddSharpNodes(&points[0], 1);
		
		ptC0 = points[1];
		ptC0.Offset(0, r);
		
		fTemp = (h-h1);
		if(fTemp)
		{
			if(ptC0.fy>h)
				rx = ((w*w/4)+(fTemp*fTemp)-(r*r))/(2*r-2*fTemp);
			else
				rx = ((w*w/4)+(fTemp*fTemp)-(r*r))/(2*r+2*fTemp);

			ptC1.Set(m_clip.X1+w/2, m_clip.Y1+h-rx);

			LineRevolve(line, ptC0, ptC1, 0, r);
			tmp[0] = line.pt1;
			grArc.InitArc(r, ptC0, tmp[0], points[1]);
			m_grPath.AddArcNode(grArc, FALSE);

			ptC0.Offset(w, 0);

			LineRevolve(line, ptC0, ptC1, 0, r);
			tmp[2] = line.pt1;
			grArc.InitArc(rx, ptC1, tmp[0], tmp[2]);
			m_grPath.AddArcNode(grArc, TRUE);
			//grArc.GetArcMidpoint(tmp[1]);
			//m_grPath.DimensionAppendR(ptC1, tmp[1], "R1");

			grArc.InitArc(r, ptC0, points[2], tmp[2]);
			m_grPath.AddArcNode(grArc, FALSE);
			grArc.GetArcMidpoint(tmp[1]);
			m_grPath.DimensionAppendR(ptC0, tmp[1], "R");
		}
		
		m_grPath.AddSharpNodes(&points[3], 1);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp[0] = points[0];
		tmp[0].Offset(0, h);
		m_grPath.DimensionAppendD(points[0], tmp[0], "H");
	}
	else if("223"==strName)
	{
		h2 = (h-(w/2));
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h2);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h2);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 4);

		m_grPath.AddSharpNodes(&points[0], 1);

		ptC0.Set(m_clip.X1+(w/2), m_clip.Y1+h2);
		grArc.InitArc((w/2), ptC0, points[1], points[2]);
		m_grPath.AddArcNode(grArc, TRUE);

		m_grPath.AddSharpNodes(&points[3], 1);

		r2 = (h1/2)+((w1*w1)/(8*h1));
		ptC1.Set(m_clip.X1+(w/2), m_clip.Y1+h1-r2);
		tmp[0].Set(m_clip.X1+(w/2)-(w1/2), m_clip.Y1);
		tmp[1].Set(m_clip.X1+(w/2)+(w1/2), m_clip.Y1);
		grArc.InitArc(r2, ptC1, tmp[0], tmp[1]);
		m_grPath.AddArcNode(grArc, FALSE);
		m_grPath.DimensionAppendD(tmp[1], tmp[0], "W1", 8);
		grArc.GetArcMidpoint(tmp[0]);
		tmp[1].Set(m_clip.X1+(w/2), m_clip.Y1);
		m_grPath.DimensionAppendD(tmp[0], tmp[1], "H1", 0);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W", 24);
		tmp[0] = points[0];
		tmp[0].Offset(0, h);
		m_grPath.DimensionAppendD(points[0], tmp[0], "H");
	}
	else if("224"==strName)
	{
		double fTemp;
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 4);

		fTemp = (h1-h);
		if(fTemp>0)
		{
			r = (fTemp/2)+((w*w)/(8*fTemp));
			
			m_grPath.AddSharpNodes(&points[0], 1);
			
			ptC0.Set(m_clip.X1+(w/2), m_clip.Y1+h1-r);
			grArc.InitArc(r, ptC0, points[1], points[2]);
			m_grPath.AddArcNode(grArc, TRUE);

			m_grPath.AddSharpNodes(&points[3], 1);

			r2 = (h2/2)+((w1*w1)/(8*h2));
			ptC1.Set(m_clip.X1+(w/2), m_clip.Y1+h2-r2);
			tmp[0].Set(m_clip.X1+(w/2)-(w1/2), m_clip.Y1);
			tmp[1].Set(m_clip.X1+(w/2)+(w1/2), m_clip.Y1);
			grArc.InitArc(r2, ptC1, tmp[0], tmp[1]);
			m_grPath.AddArcNode(grArc, FALSE);
			m_grPath.DimensionAppendD(tmp[1], tmp[0], "W1", 8);
			grArc.GetArcMidpoint(tmp[0]);
			tmp[1].Set(m_clip.X1+(w/2), m_clip.Y1);
			m_grPath.DimensionAppendD(tmp[0], tmp[1], "H2", 0);

			m_grPath.DimensionAppendD(points[3], points[0], "W", 24);

			tmp[0] = points[0];
			tmp[0].Offset(0, h1);
			m_grPath.DimensionAppendD(points[0], tmp[0], "H1");

			m_grPath.DimensionAppendD(points[2], points[3], "H");
		}
	}
	else if("225"==strName || "231"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);

		m_grPath.AddSharpNodes(&points[0], 1);

		tmp[0].Set(m_clip.X1+w1, m_clip.Y1+h+h1);
		tmp[1].Set(m_clip.X1+w-w1, m_clip.Y1+h+h1);

		RetrieveArcCenter(ptC0, r1, tmp[0], points[1]);
		grArc.InitArc(r1, ptC0, tmp[0], points[1]);
		m_grPath.AddArcNode(grArc, FALSE);
		grArc.GetArcMidpoint(tmp[2]);
		LineRevolve(line, tmp[2], grArc.m_ptC0, 0, h1);
		m_grPath.DimensionAppendR(line.pt1, tmp[2], "R1");


		RetrieveArcCenter(ptC1, r, tmp[0], tmp[1]);
		grArc.InitArc(r, ptC1, tmp[0], tmp[1]);
		m_grPath.AddArcNode(grArc, TRUE);
		grArc.GetArcMidpoint(tmp[2]);
		LineRevolve(line, tmp[2], grArc.m_ptC0, 0, h/2);
		m_grPath.DimensionAppendR(line.pt1, tmp[2], "R");

		
		RetrieveArcCenter(ptC0, r1, points[2], tmp[1]);
		grArc.InitArc(r1, ptC0, points[2], tmp[1]);
		m_grPath.AddArcNode(grArc, FALSE);
		
		m_grPath.AddSharpNodes(&points[3], 1);
		
		if("231"==strName)
		{
			r2 = (h2/2)+((w2*w2)/(8*h2));
			ptC1.Set(m_clip.X1+(w/2), m_clip.Y1+h2-r2);
			tmp[2].Set(m_clip.X1+(w/2)-(w2/2), m_clip.Y1);
			tmp[3].Set(m_clip.X1+(w/2)+(w2/2), m_clip.Y1);
			grArc.InitArc(r2, ptC1, tmp[2], tmp[3]);
			m_grPath.AddArcNode(grArc, FALSE);
			m_grPath.DimensionAppendD(tmp[3], tmp[2], "W2", 8);
			grArc.GetArcMidpoint(tmp[2]);
			tmp[3].Set(m_clip.X1+(w/2), m_clip.Y1);
			m_grPath.DimensionAppendD(tmp[2], tmp[3], "H2", 0);
		}
		

		tmp[2] = points[2];
		tmp[2].Offset(0, h1);
		m_grPath.DimensionAppendD(points[3], points[0], "W", 24);
		m_grPath.DimensionAppendD(points[0], points[1], "H");
		m_grPath.DimensionAppendD(tmp[1], tmp[2], "W1");
		m_grPath.DimensionAppendD(tmp[2], points[2], "H1");
	}
	else if("232"==strName || "233"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 4);
		
		
		double fTemp=sqrt(w2*w2+h2*h2);
		fTemp = RetrieveAngleOfTriangle(r, r, fTemp);
		if("233"==strName)
		{
			tmp[0] = tmp[1] = points[0];
			tmp[0].Offset(0, h2);
			tmp[1].Offset(w2, 0);
			LineRevolve(line, tmp[1], tmp[0], fTemp, r);
			ptC0 = line.pt1;
			grArc.InitArc(r, ptC0, tmp[0], tmp[1]);
			m_grPath.AddArcNode(grArc, FALSE);
			m_grPath.DimensionAppendD(tmp[1], points[0], "W2", 4);
			m_grPath.DimensionAppendD(points[0], tmp[0], "H2");
		}
		else
		{
			m_grPath.AddSharpNodes(&points[0], 1);
		}
		
		m_grPath.AddSharpNodes(&points[1], 1);

		r1 = (h1/2)+((w1*w1)/(8*h1));
		tmp[0].Set(m_clip.X1+(w/2)-(w1/2), m_clip.Y1+h);
		tmp[1].Set(m_clip.X1+(w/2)+(w1/2), m_clip.Y1+h);
		ptC0.Set(m_clip.X1+(w/2), m_clip.Y1+h-h1+r1);
		grArc.InitArc(r1, ptC0, tmp[1], tmp[0]);
		m_grPath.AddArcNode(grArc, FALSE);
		m_grPath.DimensionAppendD(tmp[0], tmp[1], "W1");
		tmp[0].Offset(w1/2, 0);
		grArc.GetArcMidpoint(tmp[1]);
		m_grPath.DimensionAppendD(tmp[0], tmp[1], "H1", 0);

		m_grPath.AddSharpNodes(&points[2], 1);

		if("233"==strName)
		{
			tmp[0] = tmp[1] = points[3];
			tmp[0].Offset(-w2, 0);
			tmp[1].Offset(0, h2);
			LineRevolve(line, tmp[1], tmp[0], fTemp, r);
			ptC0 = line.pt1;
			grArc.InitArc(r, ptC0, tmp[0], tmp[1]);
			m_grPath.AddArcNode(grArc, FALSE);
			grArc.GetArcMidpoint(tmp[0]);
			m_grPath.DimensionAppendR(points[3], tmp[0], "R");
		}
		else
		{
			m_grPath.AddSharpNodes(&points[3], 1);
		}

		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[2], points[3], "H");

	}
	else if("235"==strName)
	{
		double fTemp;
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 4);

		fTemp = RetrieveAngleOfTriangle(r1, r1, w);
		LineRevolve(line, points[3], points[0], fTemp, r1);
		ptC0 = line.pt1;
		grArc.InitArc(r1, ptC0, points[0], points[3]);
		m_grPath.AddArcNode(grArc, FALSE);
		tmp[0] = points[0];
		tmp[0].Offset(w/2, 0);
		grArc.GetArcMidpoint(tmp[1]);
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R1");
		
		fTemp = RetrieveAngleOfTriangle(r2, r2, w);
		LineRevolve(line, points[1], points[2], fTemp, r2);
		ptC0 = line.pt1;
		grArc.InitArc(r1, ptC0, points[2], points[1]);
		m_grPath.AddArcNode(grArc, FALSE);
		tmp[0] = points[1];
		tmp[0].Offset(w/2, 0);
		grArc.GetArcMidpoint(tmp[1]);
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R2");

		m_grPath.DimensionAppendD(points[3], points[0], "W", 24);
		m_grPath.DimensionAppendD(points[2], points[3], "H", 24);
	}
	else if("236"==strName)
	{
		double fTemp;
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 4);
		
		fTemp = RetrieveAngleOfTriangle(r3, r3, w);
		LineRevolve(line, points[3], points[0], fTemp, r3);
		ptC0 = line.pt1;
		grArc.InitArc(r1, ptC0, points[0], points[3]);
		m_grPath.AddArcNode(grArc, FALSE);
		tmp[0] = points[0];
		tmp[0].Offset(w/2, 0);
		grArc.GetArcMidpoint(tmp[1]);
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R3");
		
		fTemp = RetrieveAngleOfTriangle(r4, r4, w);
		LineRevolve(line, points[0], points[1], fTemp, r4);
		ptC0 = line.pt1;
		grArc.InitArc(r1, ptC0, points[1], points[0]);
		m_grPath.AddArcNode(grArc, FALSE);
		tmp[0] = points[0];
		tmp[0].Offset(0, h/2);
		grArc.GetArcMidpoint(tmp[1]);
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R4");
		
		fTemp = RetrieveAngleOfTriangle(r1, r1, w);
		LineRevolve(line, points[1], points[2], fTemp, r1);
		ptC0 = line.pt1;
		grArc.InitArc(r1, ptC0, points[2], points[1]);
		m_grPath.AddArcNode(grArc, FALSE);
		tmp[0] = points[1];
		tmp[0].Offset(w/2, 0);
		grArc.GetArcMidpoint(tmp[1]);
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R1");

		fTemp = RetrieveAngleOfTriangle(r2, r2, w);
		LineRevolve(line, points[2], points[3], fTemp, r2);
		ptC0 = line.pt1;
		grArc.InitArc(r1, ptC0, points[3], points[2]);
		m_grPath.AddArcNode(grArc, FALSE);
		tmp[0] = points[2];
		tmp[0].Offset(0, -h/2);
		grArc.GetArcMidpoint(tmp[1]);
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R2");
		
		m_grPath.DimensionAppendD(points[3], points[0], "W", 24);
		m_grPath.DimensionAppendD(points[2], points[3], "H", 24);
	}
	else if("237"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+l, m_clip.Y1+h);
		points[3].Set(m_clip.X1+l, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 4);

		ptC0 = points[0];
		tmp[0] = tmp[1] = ptC0;
		tmp[0].Offset(0, r);
		tmp[1].Offset(r, 0);
		grArc.InitArc(r, ptC0, tmp[0], tmp[1]);
		m_grPath.AddArcNode(grArc, FALSE);
		m_grPath.DimensionAppendR(ptC0, r, MATH_PI/4, "R");
		
		ptC0 = points[1];
		tmp[0] = tmp[1] = ptC0;
		tmp[0].Offset(r1, 0);
		tmp[1].Offset(0, -r1);
		grArc.InitArc(r1, ptC0, tmp[0], tmp[1]);
		m_grPath.AddArcNode(grArc, FALSE);
		m_grPath.DimensionAppendR(ptC0, r1, -MATH_PI/4, "R1");
		
		ptC0 = points[2];
		tmp[0] = tmp[1] = ptC0;
		tmp[0].Offset(0, -r2);
		tmp[1].Offset(-r2, 0);
		grArc.InitArc(r2, ptC0, tmp[0], tmp[1]);
		m_grPath.AddArcNode(grArc, FALSE);
		m_grPath.DimensionAppendR(ptC0, r1, -MATH_PI*3/4, "R2");
		
		ptC0 = points[3];
		tmp[0] = tmp[1] = ptC0;
		tmp[0].Offset(-r3, 0);
		tmp[1].Offset(0, r3);
		grArc.InitArc(r2, ptC0, tmp[0], tmp[1]);
		m_grPath.AddArcNode(grArc, FALSE);
		m_grPath.DimensionAppendR(ptC0, r1, MATH_PI*3/4, "R3");

		
		m_grPath.DimensionAppendD(points[3], points[0], "L", 24);
		m_grPath.DimensionAppendD(points[2], points[3], "H", 24);
	}
	else if("238"==strName)
	{
		double fTemp;
		
		tmp[0].Set(m_clip.X1+w/2, m_clip.Y1+h);
		ptC0.Set(m_clip.X1+w/2, m_clip.Y1+h-r1);
		fTemp = asin((w1/2)/r1);
		LineRevolve(line, ptC0, tmp[0], fTemp, r1);
		points[1] = line.pt1;
		points[2] = points[1];
		points[2].Offset(w1, 0);
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		
		grArc.InitArc(r1, ptC0, points[1], points[2]);
		m_grPath.AddArcNode(grArc, TRUE);
		tmp[1] = tmp[0];
		tmp[1].Offset(0, -h/2);
		m_grPath.DimensionAppendR(tmp[1], tmp[0], "R1");

		fTemp = GetDistanceF(points[2], points[3]);
		fTemp = RetrieveAngleOfTriangle(r2, r2, fTemp);
		if(fTemp)
		{
			LineRevolve(line, points[2], points[3], fTemp, r2);
			grArc.InitArc(r2, line.pt1, points[3], points[2]);
			m_grPath.AddArcNode(grArc, FALSE);
			grArc.GetArcMidpoint(tmp[0]);
			LineRevolve(line, tmp[0], grArc.m_ptC0, 0, (points[3].fx-tmp[0].fx));
			m_grPath.DimensionAppendR(line.pt1, tmp[0], "R2");
		}

		fTemp = GetDistanceF(points[0], points[1]);
		fTemp = RetrieveAngleOfTriangle(r3, r3, fTemp);
		if(fTemp)
		{
			LineRevolve(line, points[0], points[1], fTemp, r3);
			grArc.InitArc(r3, line.pt1, points[1], points[0]);
			m_grPath.AddArcNode(grArc, FALSE);
			grArc.GetArcMidpoint(tmp[0]);
			LineRevolve(line, tmp[0], grArc.m_ptC0, 0, (tmp[0].fx-points[0].fx));
			m_grPath.DimensionAppendR(line.pt1, tmp[0], "R3");
		}

		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp[0] = points[3];
		tmp[0].Offset(0, h);
		m_grPath.DimensionAppendD(tmp[0], points[3], "H");
		tmp[0].Offset(-(w-w1)/2, 0);
		tmp[1] = tmp[0];
		tmp[1].Offset(-w1, 0);
		m_grPath.DimensionAppendD(tmp[1], tmp[0], "W1");
	}
	else if("239"==strName)
	{
		double fTemp;

		tmp[0].Set(m_clip.X1+w/2, m_clip.Y1+h);
		ptC0.Set(m_clip.X1+w/2, m_clip.Y1+h-r1);
		fTemp = asin((w1/2)/r1);
		LineRevolve(line, ptC0, tmp[0], fTemp, r1);
		points[1] = line.pt1;
		points[2] = points[1];
		points[2].Offset(w1, 0);
		tmp[2].Set(m_clip.X1+w/2, m_clip.Y1);
		ptC1.Set(m_clip.X1+w/2, m_clip.Y1+r2);
		fTemp = asin((w/2)/r2);
		LineRevolve(line, ptC1, tmp[2], fTemp, r2);
		points[3] = line.pt1;
		points[0] = points[3];
		points[0].Offset(-w, 0);

		grArc.InitArc(r1, ptC0, points[1], points[2]);
		m_grPath.AddArcNode(grArc, TRUE);
		tmp[1] = tmp[0];
		tmp[1].Offset(0, -h/3);
		m_grPath.DimensionAppendR(tmp[1], tmp[0], "R1");


		fTemp = GetDistanceF(points[2], points[3]);
		fTemp = RetrieveAngleOfTriangle(r4, r4, fTemp);
		if(fTemp)
		{
			LineRevolve(line, points[2], points[3], fTemp, r4);
			grArc.InitArc(r4, line.pt1, points[3], points[2]);
			m_grPath.AddArcNode(grArc, FALSE);
			grArc.GetArcMidpoint(tmp[0]);
			LineRevolve(line, tmp[0], grArc.m_ptC0, 0, (points[3].fx-tmp[0].fx));
			m_grPath.DimensionAppendR(line.pt1, tmp[0], "R4");
		}
		

		grArc.InitArc(r2, ptC1, points[3], points[0]);
		m_grPath.AddArcNode(grArc, TRUE);
		tmp[3] = tmp[2];
		tmp[3].Offset(0, h/3);
		m_grPath.DimensionAppendR(tmp[3], tmp[2], "R2");
		
		fTemp = GetDistanceF(points[0], points[1]);
		fTemp = RetrieveAngleOfTriangle(r3, r3, fTemp);
		if(fTemp)
		{
			LineRevolve(line, points[0], points[1], fTemp, r3);
			grArc.InitArc(r3, line.pt1, points[1], points[0]);
			m_grPath.AddArcNode(grArc, FALSE);
			grArc.GetArcMidpoint(tmp[0]);
			LineRevolve(line, tmp[0], grArc.m_ptC0, 0, (tmp[0].fx-points[0].fx));
			m_grPath.DimensionAppendR(line.pt1, tmp[0], "R3");
		}
		
		tmp[0].Set(m_clip.X1, m_clip.Y1);
		tmp[1].Set(m_clip.X1+w, m_clip.Y1);
		m_grPath.DimensionAppendD(tmp[1], tmp[0], "W");
		tmp[0].Set(m_clip.X1+w, m_clip.Y1+h);
		m_grPath.DimensionAppendD(tmp[0], tmp[1], "H");
		tmp[0].Set(m_clip.X1, m_clip.Y1+h);
		tmp[1].Set(m_clip.X1+w1, m_clip.Y1+h);
		m_grPath.DimensionAppendD(tmp[0], tmp[1], "W1");
	}
	else if("240"==strName)
	{
		double fArc, fTemp;
		CGrArc arc1, arc2, arc3;

		ptC0.Set(m_clip.X1+r2, m_clip.Y1);
		fArc = acos(((w/2)-r2)/(r1+r2));
		fArc = (MATH_PI-fArc)/2;
		fTemp = tan(fArc)*r2;
		ptC0.Offset(0, fTemp);
		points[0].Set(ptC0.fx-r2, ptC0.fy-fTemp);

		tmp[0].Set(ptC0.fx-r2, ptC0.fy);
		LineRevolve(line, ptC0, points[0], fArc, r2);
		tmp[1]=line.pt1;
		arc1.InitRoundCornerArc(r2, points[0], tmp[1], tmp[0]);
		
		LineRevolve(line, arc1.m_ptC0, tmp[1], 0, r1+r2);
		ptC1 = line.pt1;

		points[3] = points[0];
		points[3].Offset(w, 0);

		ptC0.Offset(w-(r2*2), 0);
		tmp[0].Offset(w, 0);
		tmp[1].Offset(w-2*(tmp[1].fx-points[0].fx), 0);
		arc3.InitRoundCornerArc(r3, points[3], tmp[0], tmp[1]);

		arc2.InitArc(r1, ptC1, arc1.m_ptArcBgn, arc3.m_ptArcEnd);

		tmp[0].Set(m_clip.X1+w/2, m_clip.Y1+h);
		ptC0 = tmp[0];
		ptC0.Offset(0, -r);
		fArc = asin((w/2)/r);
		LineRevolve(line, ptC0, tmp[0], fArc, r);
		tmp[2] = tmp[1] = line.pt1;
		tmp[2].Offset(w, 0);
		grArc.InitArc(r, ptC0, tmp[1], tmp[2]);

		m_grPath.AddRoundAngleNode(points[0], arc1, TRUE);		
		m_grPath.AddArcNode(grArc, TRUE);
		m_grPath.AddRoundAngleNode(points[3], arc3, TRUE);
		m_grPath.AddArcNode(arc2, FALSE);
		
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		tmp[0] = points[3];
		tmp[0].Offset(0, h);
		m_grPath.DimensionAppendD(tmp[0], points[3], "H");

		grArc.GetArcMidpoint(tmp[1]);
		tmp[0] = tmp[1];
		tmp[0].Offset(0, -h/2);
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R");

		arc2.GetArcMidpoint(tmp[1]);
		tmp[0] = tmp[1];
		tmp[0].Offset(0, -(tmp[0].fy-m_clip.Y1));
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R1");

		m_grPath.DimensionAppendR(arc1.m_ptC0, r2, -MATH_PI*3/4, "R2");
		m_grPath.DimensionAppendR(arc3.m_ptC0, r3, -MATH_PI/4, "R3");
	}
	else if("244"==strName)
	{
		double fArc, fTemp;
		points[0].Set(m_clip.X1, m_clip.Y1+s1);
		points[1].Set(m_clip.X1, m_clip.Y1+s1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+s1+h+s2);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 4);

		fTemp = sqrt(w*w+s1*s1);
		fArc = RetrieveAngleOfTriangle(r1, r1, fTemp);
		LineRevolve(line, points[3], points[0], fArc, r1);
		ptC0 = line.pt1;

		fTemp = sqrt(w*w+s2*s2);
		fArc = RetrieveAngleOfTriangle(r2, r2, fTemp);
		LineRevolve(line, points[1], points[2], fArc, r2);
		ptC1 = line.pt1;

		grArc.InitArc(r1, ptC0, points[0], points[3]);
		m_grPath.AddArcNode(grArc, FALSE);
		grArc.GetArcMidpoint(tmp[1]);
		LineRevolve(line, ptC0, tmp[1], 0, r1+(h/3));
		tmp[0]=line.pt1;
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R1");
		
		grArc.InitArc(r2, ptC1, points[2], points[1]);
		m_grPath.AddArcNode(grArc, FALSE);
		grArc.GetArcMidpoint(tmp[1]);
		LineRevolve(line, ptC1, tmp[1], 0, r2+(h/3));
		tmp[0]=line.pt1;
		m_grPath.DimensionAppendR(tmp[0], tmp[1], "R2");

		tmp[0] = points[0];
		tmp[0].Offset(0, -s1);
		m_grPath.DimensionAppendD(points[3], tmp[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");
		tmp[0] = points[2];
		tmp[0].Offset(0, -s2);
		m_grPath.DimensionAppendD(points[2], tmp[0], "S2");
		tmp[0] = points[3];
		tmp[0].Offset(0, s1);
		m_grPath.DimensionAppendD(tmp[0], points[3], "S1");
	}
	else if("247"==strName)
	{
		double fTemp;
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+(2*h));
		points[2].Set(m_clip.X1+w, m_clip.Y1+(2*h));
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 4);

		tmp[0].Set(m_clip.X1, m_clip.Y1+h);
		fTemp = RetrieveAngleOfTriangle(r, r, h);
		if(fTemp)
		{
			LineRevolve(line, tmp[0], points[0], fTemp, r);
			ptC0 = line.pt1;
			grArc.InitArc(r, ptC0, points[0], tmp[0]);
			m_grPath.AddArcNode(grArc, TRUE);
			m_grPath.DimensionAppendR(ptC0, r, MATH_PI, "R");

			LineRevolve(line, ptC0, tmp[0], 0, r*2);
			ptC1 = line.pt1;
			grArc.InitArc(r, ptC1, points[1], tmp[0]);
			m_grPath.AddArcNode(grArc, FALSE);

			ptC1.Offset(w, 0);
			tmp[1] = tmp[0];
			tmp[1].Offset(w, 0);
			grArc.InitArc(r, ptC1, points[2], tmp[1]);
			m_grPath.AddArcNode(grArc, TRUE);

			ptC1 = ptC0;
			ptC1.Offset(w, 0);
			grArc.InitArc(r, ptC1, points[3], tmp[1]);
			m_grPath.AddArcNode(grArc, FALSE);

			m_grPath.DimensionAppendD(tmp[1], points[3], "H", 24);
			m_grPath.DimensionAppendD(points[3], points[0], "W", 24);

			tmp[0]=ptC0;
			tmp[0].Offset(-r, 0);
			if(tmp[0].fx<points[0].fx)
				m_grPath.Offset(points[0].fx-tmp[0].fx, 0);
		}
	}
	else if("249"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 4);

		m_grPath.AddSharpNodes(&points[0], 1);

		if(h>h1)
		{
			r = ((h-h1)/2)+((w*w)/(8*(h-h1)));
			tmp[0].Set(m_clip.X1+w/2, m_clip.Y1+h1);
			ptC0 = tmp[0];
			ptC0.Offset(0, r);
			grArc.InitArc(r, ptC0, points[2], points[1]);
			m_grPath.AddArcNode(grArc, FALSE);
			tmp[1] = tmp[0];
			tmp[1].Offset(0, -h1);
			m_grPath.DimensionAppendD(tmp[0], tmp[1], "H1", 0);
		}

		m_grPath.AddSharpNodes(&points[3], 1);

		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H");

	}
	else if("263"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h1);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h1);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 4);

		if(h>h1)
		{
			r = ((h-h1)/2)+((w*w)/(8*(h-h1)));
			ptC0.Set(m_clip.X1+w/2, m_clip.Y1+(h-h1-r));
			grArc.InitArc(r, ptC0, points[0], points[3]);
			m_grPath.AddArcNode(grArc, FALSE);
			ptC0.Set(m_clip.X1+w/2, m_clip.Y1+(h-r));
			grArc.InitArc(r, ptC0, points[1], points[2]);
			m_grPath.AddArcNode(grArc, TRUE);

			m_grPath.DimensionAppendD(points[3], points[0], "W");
			m_grPath.DimensionAppendD(points[2], points[3], "H1");
			tmp[0] = points[0];
			tmp[0].Offset(0, h);
			m_grPath.DimensionAppendD(points[0], tmp[0], "H");
		}
	}
	else if("270"==strName)
	{
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h-b2);
		points[2].Set(m_clip.X1+b1, m_clip.Y1+h-b2);
		points[3].Set(m_clip.X1+b1, m_clip.Y1+h);
		points[4].Set(m_clip.X1+w-a1, m_clip.Y1+h);
		points[5].Set(m_clip.X1+w, m_clip.Y1+h-a2);
		points[6].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 7);

		m_grPath.AddSharpNodes(&points[0], 1);
		m_grPath.AddSharpNodes(&points[1], 1);

		grArc.InitRoundCornerArc(r, points[2], points[3], points[1]);
		m_grPath.AddArcNode(grArc, FALSE);

		m_grPath.AddSharpNodes(&points[3], 1);
		m_grPath.AddSharpNodes(&points[4], 1);
		m_grPath.AddSharpNodes(&points[5], 1);
		m_grPath.AddSharpNodes(&points[6], 1);

		m_grPath.DimensionAppendD(points[6], points[0], "W");
		tmp[0]=points[0];
		tmp[0].Offset(0, h);
		m_grPath.DimensionAppendD(points[0], tmp[0], "H", 24);
		m_grPath.DimensionAppendD(points[1], tmp[0], "B2", 4);
		m_grPath.DimensionAppendD(tmp[0], points[3], "B1");
		m_grPath.DimensionAppendR(grArc.m_ptC0, r, -MATH_PI/4, "R");
		tmp[0]=points[6];
		tmp[0].Offset(0, h);
		m_grPath.DimensionAppendD(points[4], tmp[0], "A1");
		m_grPath.DimensionAppendD(tmp[0], points[5], "A2");
	}
	else if("273"==strName || "278"==strName)
	{
		double fTemp, fArc;
		fTemp = w-w1;
		if(fTemp>=0)
		{
			points[0].Set(m_clip.X1, m_clip.Y1);
			points[1].Set(m_clip.X1+fTemp, m_clip.Y1+h);
			points[2].Set(m_clip.X1+w, m_clip.Y1+h);
			points[3].Set(m_clip.X1+w1, m_clip.Y1);
			//m_grPath.AddSharpNodes(&points[0], 4);

			fTemp = sqrt(fTemp*fTemp+h*h);

			if("273"==strName)
			{
				fArc = RetrieveAngleOfTriangle(r, r, fTemp);
				LineRevolve(line, points[1], points[0], fArc, r);
				ptC0 = line.pt1;
				grArc.InitArc(r, ptC0, points[0], points[1]);
				m_grPath.AddArcNode(grArc, TRUE);
				grArc.GetArcMidpoint(tmp[0]);
				LineRevolve(line, tmp[0], ptC0, 0, min(w1,h)/2);
				m_grPath.DimensionAppendR(line.pt1, tmp[0], "R");
			}
			else
			{
				fArc = RetrieveAngleOfTriangle(r, r, fTemp);
				LineRevolve(line, points[0], points[1], fArc, r);
				ptC0 = line.pt1;
				grArc.InitArc(r, ptC0, points[1], points[0]);
				m_grPath.AddArcNode(grArc, FALSE);
				grArc.GetArcMidpoint(tmp[0]);
				LineRevolve(line, tmp[0], ptC0, 0, min(w1,h)/2);
				m_grPath.DimensionAppendR(line.pt1, tmp[0], "R");
			}
			
			fArc = RetrieveAngleOfTriangle(r2, r2, fTemp);
			LineRevolve(line, points[2], points[3], fArc, r2);
			ptC0 = line.pt1;
			grArc.InitArc(r2, ptC0, points[3], points[2]);
			m_grPath.AddArcNode(grArc, FALSE);
			grArc.GetArcMidpoint(tmp[0]);
			LineRevolve(line, tmp[0], ptC0, 0, min(w1,h)/2);
			m_grPath.DimensionAppendR(line.pt1, tmp[0], "R2");

			m_grPath.DimensionAppendD(points[3], points[0], "W1");
			tmp[0]=points[0];
			tmp[0].Offset(0, h);
			m_grPath.DimensionAppendD(points[0], tmp[0], "H");
			m_grPath.DimensionAppendD(tmp[0], points[2], "W");
		}

	}
	else if("295"==strName)
	{
		double fTemp;
		points[0].Set(m_clip.X1, m_clip.Y1);
		points[1].Set(m_clip.X1, m_clip.Y1+h1);
		points[2].Set(m_clip.X1+w, m_clip.Y1+h);
		points[3].Set(m_clip.X1+w, m_clip.Y1);
		//m_grPath.AddSharpNodes(&points[0], 4);

		m_grPath.AddSharpNodes(&points[0], 1);

		tmp[0].Set(m_clip.X1+A, m_clip.Y1+h1+b);

		fTemp = GetDistanceF(points[1], tmp[0]);
		fTemp = RetrieveAngleOfTriangle(r1, r1, fTemp);
		LineRevolve(line, points[1], tmp[0], fTemp, r1);
		ptC0 = line.pt1;
		grArc.InitArc(r1, ptC0, tmp[0], points[1]);
		m_grPath.AddArcNode(grArc, FALSE);
		grArc.GetArcMidpoint(tmp[1]);
		LineRevolve(line, tmp[1], grArc.m_ptC0, 0, b);
		m_grPath.DimensionAppendR(line.pt1, tmp[1], "R1");

#if 1
		fTemp = GetDistanceF(tmp[0], points[2]);
		fTemp = RetrieveAngleOfTriangle(r2, r2, fTemp);
		LineRevolve(line, points[2], tmp[0], fTemp, r2);
#else
		LineRevolve(line, ptC0, tmp[0], 0, r1+r2);
#endif
		ptC1 = line.pt1;
		grArc.InitArc(r2, ptC1, tmp[0], points[2]);
		m_grPath.AddArcNode(grArc, TRUE);
		grArc.GetArcMidpoint(tmp[1]);
		LineRevolve(line, tmp[1], grArc.m_ptC0, 0, b);
		m_grPath.DimensionAppendR(line.pt1, tmp[1], "R2");

		m_grPath.AddSharpNodes(&points[3], 1);

		tmp[1] = tmp[0];
		tmp[1].Offset(0, -b);
		m_grPath.DimensionAppendD(tmp[0], tmp[1], "B");
		m_grPath.DimensionAppendD(tmp[1], points[1], "A");
		m_grPath.DimensionAppendD(points[2], points[3], "H");
		m_grPath.DimensionAppendD(points[3], points[0], "W");
		m_grPath.DimensionAppendD(points[0], points[1], "H1");
	}


	m_grPath.PaintTo(&m_dcGraph, &rcDrawing, GRAPH_COLOR_FR);
	
	//将图形由设备坐标系(Y轴向下)转换为数学平面直角坐标系(Y轴向上)
	ConvertGraphCoordinate(&m_dcGraph);
	
	Invalidate(TRUE);
}


void CGrEditor::OnDestroy() 
{
	CDialog::OnDestroy();
}
CString CGrEditor::MakeNestCode()
{
	return m_grPath.MakeNestData();
}
//0保存;1发送
void CGrEditor::MakeGCodeFile(int nStyle)
{

	CString		strFilename;
	if (nStyle==0)//保存
	{
		dlg_save  dlgSave;
		dlgSave.strExtName = ".g";
		if (IDCANCEL == dlgSave.DoModal())	return;
		if(g_strSavefile.IsEmpty())				return;
	} 
	else//发送
	{
		g_strSavefile = "Graph.g";
	}
	strFilename = g_strOriginalPathD+"gcode\\"+g_strSavefile;
	g_strShowName = g_strSavefile;
	g_strGfile = strFilename;
    g_strSavefile = "";		
	int len;
	CFile file;
	const char *pszGCode=NULL;
	
	if(!file.Open(strFilename, CFile::modeCreate+CFile::modeWrite))
	{
		if(g_iLanguage==0)
			AfxMessageBox("打开文件失败！", MB_OK|MB_ICONERROR);
		else
            AfxMessageBox("Open file fail!", MB_OK|MB_ICONERROR);
		return;
	}
	pszGCode=m_grPath.MakeGCode();
	len = strlen(pszGCode);
	file.Write(pszGCode, len);
	file.Close();

}

BOOL CGrEditor::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		switch(pMsg->wParam)
		{
		case VK_RETURN:
			UpdateGraph();
			return TRUE;
			break;
		}
		break;
	default: break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}



void CGrEditor::InitUISetting(LPCTSTR lpszIndex)
{
	UINT nIndex, nCtrlIndex;
	CUISetting *item=NULL;
	GRPARA *para=NULL;

	while(lpszIndex[0]=='0')
	{	lpszIndex++;	}
	nIndex = atol(lpszIndex);
	if(nIndex>MAX_UI_SETTINGs)
		return;

	item = &m_uiSettings[nIndex];
	if(item->m_nIndex<MAX_UI_SETTINGs)
		return;	//已经初始化过

	nCtrlIndex = 0;
	item->Reset();

	//////////////////////////////////////////////////////////////////////////
	// Circle
	//////////////////////////////////////////////////////////////////////////
	switch (nIndex)
	{
	case 1:
		item->AddParaCtrl("D", nCtrlIndex++, "(D>0)", 1000.0f);
		break;
	case 2:
	case 7:
	case 9:
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 500.0f);
        break;
    case 3:
		item->AddParaCtrl("R", nCtrlIndex++, "(R>R1)", 500.0f);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 100.0f);
		break;
	case 4:
	case 5:
		item->AddParaCtrl("R", nCtrlIndex++, "(R>R1)", 500.0f);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 100.0f);
		item->AddParaCtrl("D", nCtrlIndex++, "(D>R)", 300.0f);
		break;
	case 6:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		break;
	case 8:
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 500.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 1000.0);
		break;
	case 10:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("R", nCtrlIndex++, "((2*R)>(SQR(W*W+H*H))", 800.0);
		break;
    case 11:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 200.0);
		break;
    case 12:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>W)", 1000.0);
		break;
	case 13:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 700.0);
		item->AddParaCtrl("S", nCtrlIndex++, "(S>0)", 200.0);
		break;
	case 14:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 700.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>W, >W1)", 800.0);
		item->AddParaCtrl("A", nCtrlIndex++, "(A>0)", 45.0);
		break;
	case 15:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 700.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 740.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>W, >W1)", 800.0);
		item->AddParaCtrl("A", nCtrlIndex++, "(A>0)", 45.0);
		break;
	case 16:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 50.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 750.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>W, >W1)", 600.0);
		item->AddParaCtrl("A", nCtrlIndex++, "(A>0, <90)", 45.0);
		break;
	case 17:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>=0, <W)", 500.0);
		break;
	case 18:
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>R2)", 1000.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 600.0);
		item->AddParaCtrl("A", nCtrlIndex++, "(A>0)", 60.0);
		break;
	case 19:
	case 20:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1600.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 2000.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 1800.0);
		break;
	case 21:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(R+H))", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 500.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R<W)", 300.0);
		break;
	case 22:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(H+R2))", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H<(W-R2))", 500.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>=0; <W)", 300.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>=0; <(W+H))", 200.0);
		break;
	case 23:
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 500.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 200.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 50.0);
		break;
	case 24:
		item->AddParaCtrl("D1", nCtrlIndex++, "(D1)", 500.0);
		item->AddParaCtrl("D", nCtrlIndex++, "(D)", 600.0);
		item->AddParaCtrl("N", nCtrlIndex++, "(N)", 12.0);
		break;
	case 26:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1200.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, <(H/2))", 300.0);
		break;
	case 25:
	case 27:
	case 28:
	case 29:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 500.0);      
		break;
	case 30:
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>W)", 1000.0);
		item->AddParaCtrl("W", nCtrlIndex++, "(W>R)", 800.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>H)", 500.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 400.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 100.0);
		break;
	case 31:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>(W/2))", 600.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>(W/2))", 800.0);
		break;
	case 32:
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>R2)", 1000.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 600.0);
		item->AddParaCtrl("A", nCtrlIndex++, "(A>0)", 60.0);
		break;
	case 33:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(2*R1))", 1400.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1<(W/2))", 600.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>R1)", 2000.0);
		break;
    case 34:
		item->AddParaCtrl("R", nCtrlIndex++, "(R<W)", 500.0);
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 400.0);
		item->AddParaCtrl("A", nCtrlIndex++, "(A>=0, <180)", 45.0);
		break;
    case 35:
		item->AddParaCtrl("A", nCtrlIndex++, "(A>0)", 600.0);
		item->AddParaCtrl("B", nCtrlIndex++, "(B>0)", 1100.0);
		item->AddParaCtrl("C", nCtrlIndex++, "(C>0)", 900.0);
		item->AddParaCtrl("D", nCtrlIndex++, "(D>0)", 300.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, <180)", 100.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>(D/2))", 200.0);
		break;
    case 250:
		item->AddParaCtrl("R", nCtrlIndex++, "(R>R1)", 1000.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 100.0);
		item->AddParaCtrl("D", nCtrlIndex++, "(D<R)", 700.0);
		break;
    case 262:
		item->AddParaCtrl("R", nCtrlIndex++, "(R>R1)", 1000.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 100.0);
		item->AddParaCtrl("D", nCtrlIndex++, "(D<R)", 700.0);
		item->AddParaCtrl("NF", nCtrlIndex++, "(NF 1-360)", 7);
		break;
    case 257:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(W1+R2))", 900.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(R1>(H1+R1))", 900.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1<R1)", 700.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1<R1)", 700.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1<R2)", 1000.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 300.0);
		break;
    case 36:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		break;
    case 37:
	case 38:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		break;
    case 39:
    case 40:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1<W)", 400.0);
		break;
    case 41:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 800.0);
		break;
    case 42:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("A1", nCtrlIndex++, "(A1>0; <90)", 60);
		item->AddParaCtrl("A2", nCtrlIndex++, "(A2>0; <90)", 40.0);
		break;
	case 43:
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 1000.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 600.0);
		item->AddParaCtrl("A", nCtrlIndex++, "(A>0; <90)", 40.0);
		break;
	case 44:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 800.0);
		item->AddParaCtrl("D", nCtrlIndex++, "(D>=0)", 200.0);
		break;
    case 45:
		item->AddParaCtrl("G", nCtrlIndex++, "(G>0)", 1000.0);
		item->AddParaCtrl("G1", nCtrlIndex++, "(G1>=0)", 200.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		break;
	case 46:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 100.0);
		break;
	case 47:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 100.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 120.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0)", 150.0);
		break;
	case 48:		
    case 50:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 100.0);
		break;
	case 49:		
    case 51:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 50.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 100.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0)", 150.0);
		break;
    case 52:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 600.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 400.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 100.0);
		break;
	case 53:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 600.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 400.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 50.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 100.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0)", 150.0);
		break;
	case 54:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1400.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 1200.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 1200.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0)", 1200.0);
		break;
	case 55:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 600.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 300.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 700.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 1000.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0)", 900.0);
		break;
	case 56:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 500.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 300.0);
		break;
	case 57:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 900.0);
		break;
	case 59:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		break;
	case 60:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 500.0);
		break;
	case 61:
	case 63:
	case 64:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 500.0);
		break;
	case 62:
	case 65:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>w1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 400.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 300.0);
		break;
	case 66:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		break;
	case 67:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("A", nCtrlIndex++, "(A>0)", 60.0);
		break;
    case 68:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		break;
	case 69:
	case 70:
	case 71:
	case 73:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 800.0);
		break;
	case 72:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("S1", nCtrlIndex++, "(S1>0)", 600.0);
		item->AddParaCtrl("S2", nCtrlIndex++, "(S2>0)", 700.0);
		break;
	case 74:
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 1000.0);
		item->AddParaCtrl("W3", nCtrlIndex++, "(W3>0)", 200.0);
		item->AddParaCtrl("W4", nCtrlIndex++, "(W4>0)", 800.0);
		break;
	case 75:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(W1+W2))", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 200.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 600.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 800.0);
		break;
	case 76:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 400.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 200.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 600.0);
		break;
	case 77:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 600.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 800.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 700.0);
		item->AddParaCtrl("A1", nCtrlIndex++, "(A1>0, A1<180)", 80.0);
		item->AddParaCtrl("A2", nCtrlIndex++, "(A2>0, A2<180)", 75.0);
		break;
	case 78:
	case 79:
	case 80:
	case 81:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 200.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 300.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 800.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 700.0);
		break;
	case 82:
	case 83:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>=0)", 200.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 600.0);
		item->AddParaCtrl("S1", nCtrlIndex++, "(S1>0)", 800.0);
		item->AddParaCtrl("S2", nCtrlIndex++, "(S2>0)", 700.0);
		break;
	case 84:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W2)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>=0)", 200.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>W1)", 400.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 500.0);
		break;
	case 85:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1, W>W2)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>=0)", 200.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 400.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 500.0);
		break;
	case 86:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 600.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1<(W2+W)", 200.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 400.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H<H1)", 500.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 1000.0);
		break;
	case 87:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0", 200.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 200.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H<H1)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 500.0);
		break;
	case 88:
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 700.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0", 1000.0);
		item->AddParaCtrl("W3", nCtrlIndex++, "(W3>0)", 500.0);
		item->AddParaCtrl("W4", nCtrlIndex++, "(W4<0)", 900.0);
		item->AddParaCtrl("A", nCtrlIndex++, "(A>0, A<180)", 100.0);
		break;
	case 90:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0", 900.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 800.0);
		item->AddParaCtrl("D1", nCtrlIndex++, "(Diag 1)", 1500.0);
		item->AddParaCtrl("D2", nCtrlIndex++, "(Diag 2)", 1500.0);
		break;
	case 91:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(W1+W2))", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0", 1500.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 1500.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 200.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 200.0);
		break;
	case 92:
		item->AddParaCtrl("L", nCtrlIndex++, "(L>0)", 600.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1, >H2)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0", 400.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 400.0);
		break;
	case 93:
		item->AddParaCtrl("L", nCtrlIndex++, "(L>(L1+L2))", 1200.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 600.0);
		item->AddParaCtrl("L1", nCtrlIndex++, "(L1>0", 300.0);
		item->AddParaCtrl("L2", nCtrlIndex++, "(L2>0)", 200.0);
		break;
	case 94:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>L1)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("L1", nCtrlIndex++, "(L1>0", 200.0);
		break;
	case 95:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 400.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 100.0);
		break;
	case 255:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(D2-H1))", 750.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>(W-H2))", 900.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>(D2-W))", 500.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>(D2-W1))", 500.0);
		item->AddParaCtrl("D2", nCtrlIndex++, "(D2>(W-H1), <(W+H1))", 900.0);
		break;
	case 259:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 600.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0", 900.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 800.0);
		item->AddParaCtrl("A1", nCtrlIndex++, "(A1>0, A1<90)", 30.0);
		item->AddParaCtrl("A2", nCtrlIndex++, "(A2>0, A2<90)", 40.0);
		break;
	case 260:
	case 261:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H1>0)", 1000.0);
		item->AddParaCtrl("A", nCtrlIndex++, "(A>0, A<180)", 40.0);
		break;
	case 272:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H1>0)", 800.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 600.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 600.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 400.0);
		item->AddParaCtrl("H3", nCtrlIndex++, "(H3>0)", 300.0);
		item->AddParaCtrl("D", nCtrlIndex++, "(D>0)", 200.0);
		item->AddParaCtrl("D1", nCtrlIndex++, "(D1>0)", 200.0);
		break;
	case 120:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		break;
	case 121:
		item->AddParaCtrl("L", nCtrlIndex++, "(L>0)", 1000.0);
		item->AddParaCtrl("L1", nCtrlIndex++, "(L1>0)", 900.0);
		item->AddParaCtrl("L2", nCtrlIndex++, "(L2>0)", 800.0);
		break;
	case 122:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 500.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 500.0);
		break;
	case 123:
		item->AddParaCtrl("B", nCtrlIndex++, "(B>0)", 700.0);
		item->AddParaCtrl("L", nCtrlIndex++, "(L>R)", 1000.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 900.0);
		break;
	case 124:
		item->AddParaCtrl("B", nCtrlIndex++, "(B>T)", 1000.0);
		item->AddParaCtrl("L", nCtrlIndex++, "(L>R)", 1000.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 600.0);
		item->AddParaCtrl("T", nCtrlIndex++, "(T>0)", 300.0);
		break;
	case 125:
		item->AddParaCtrl("B", nCtrlIndex++, "(B>T)", 1000.0);
		item->AddParaCtrl("L", nCtrlIndex++, "(L>R)", 1000.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 600.0);
		item->AddParaCtrl("T", nCtrlIndex++, "(T>0)", 300.0);
		item->AddParaCtrl("S1", nCtrlIndex++, "(S1>0)", 400.0);
		break;
	case 126:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1<H)", 600.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2<H)", 400.0);
		break;
	case 127:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 600.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 400.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 700.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 500.0);
		break;
	case 128:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("A1", nCtrlIndex++, "(A1>=0)", 400.0);
		item->AddParaCtrl("A2", nCtrlIndex++, "(A2>=0)", 300.0);
		break;
	case 129:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("D1", nCtrlIndex++, "(D1>=0)", 300.0);
		break;
	case 130:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>=0)", 600.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>=0)", 400.0);
		break;
	case 131:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1<H)", 700.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2<H)", 400.0);
		break;
	case 132:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>(H1+H2))", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 800.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 350.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 300.0);
		break;
	case 133:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>=0)", 200.0);
		item->AddParaCtrl("W3", nCtrlIndex++, "(W3>=0)", 200.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1, H>H2)", 800.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 500.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 300.0);
		break;
	case 134:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(W1+W2))", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1, H>H2)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0, W1<W)", 200.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0, W2<W)", 400.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 400.0);
		break;
	case 135:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 500.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1200.0);
		item->AddParaCtrl("L", nCtrlIndex++, "(L>0)", 500.0);
		item->AddParaCtrl("A", nCtrlIndex++, "(A>0)", 130.0);
		break;
	case 136:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1400.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 900.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>=0)", 300.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 1100.0);
		item->AddParaCtrl("W3", nCtrlIndex++, "(W3>0)", 300.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>=0)", 400.0);
		break;
	case 137:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W2)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 200.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 800.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>W)", 800.0);
		break;
	case 139:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 400.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0, <(W1/2), <(H1/2))", 200.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0, <(W1/2), <(H1/2))", 150.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0, <(W1/2), <(H1/2))", 100.0);
		item->AddParaCtrl("R4", nCtrlIndex++, "(R4>0, <(W1/2), <(H1/2))", 150.0);
		item->AddParaCtrl("R5", nCtrlIndex++, "(R5>0, <(W1/2), <(H1/2))", 250.0);
		break;
	case 140:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(W1+W2))", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 400.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W1>0)", 200.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 400.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, <(W1/2), <(H1/2))", 100.0);
		break;
	case 141:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(W1+W2))", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 400.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W1>0)", 200.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 400.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 200.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 150.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0)", 100.0);
		item->AddParaCtrl("R4", nCtrlIndex++, "(R4>0)", 150.0);
		item->AddParaCtrl("R5", nCtrlIndex++, "(R5>0)", 250.0);
		break;
	case 142:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(W1+W2))", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1, >H2)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 800.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 600.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 400.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, <(H1/2), <(H2/2))", 150.0);
		break;
	case 143:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(W1+W2))", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1, >H2)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 800.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 600.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 400.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0", 200.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0", 150.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0", 100.0);
		item->AddParaCtrl("R4", nCtrlIndex++, "(R4>0", 150.0);
		item->AddParaCtrl("R5", nCtrlIndex++, "(R5>0", 250.0);
		break;
	case 144:
	case 145:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		break;
	case 146:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 500.0);
		break;
	case 147:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 500.0);
		break;
	case 148:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>W2)", 600.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 400.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 500.0);
		break;
	case 149:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 500.0);
		break;
	case 150:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("A1", nCtrlIndex++, "(A1>=0)", 200.0);
		item->AddParaCtrl("A2", nCtrlIndex++, "(A2>=0)", 150.0);
		break;
	case 151:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("D1", nCtrlIndex++, "(D1>=0)", 200.0);
		break;
	case 152:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(A1+W1))", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 500.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 300.0);
		item->AddParaCtrl("A1", nCtrlIndex++, "(A1>0)", 200.0);
		item->AddParaCtrl("A2", nCtrlIndex++, "(A2>0)", 300.0);
		break;
	case 153:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(A1+W1))", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 500.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 300.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>H)", 1000.0);
		item->AddParaCtrl("A1", nCtrlIndex++, "(A1>0)", 200.0);
		break;
	case 154:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(W1+W2))", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1, >H2)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 300.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 300.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>H)", 400.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 300.0);
		break;
	case 155:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>=0)", 700.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1, >H2)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 200.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 500.0);
		item->AddParaCtrl("W3", nCtrlIndex++, "(W3>0)", 300.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>H)", 400.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 300.0);
		break;
	case 156:
		item->AddParaCtrl("W", nCtrlIndex++, "(W<(A1+W1))", 400.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 400.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 400.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 500.0);
		item->AddParaCtrl("A1", nCtrlIndex++, "(A1>0)", 500.0);
		item->AddParaCtrl("A2", nCtrlIndex++, "(A2>0)", 300.0);
		break;
	case 157:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1, >W2)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1, >H2)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 300.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 300.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>H)", 400.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 300.0);
		break;
	case 158:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W2)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H2)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 300.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>W1)", 700.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 400.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>H1)", 700.0);
		break;
	case 159:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1200.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 100.0);
		break;
	case 160:
	case 161:
	case 162:
	case 163:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		break;
	case 164:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1, >W2)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1, >H2)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 300.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 300.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>H)", 400.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 300.0);
		break;
	case 165:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 300.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>H)", 400.0);
		break;
	case 166:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("D1", nCtrlIndex++, "(D1>=0)", 300.0);
		item->AddParaCtrl("D2", nCtrlIndex++, "(D2>H)", 300.0);
		item->AddParaCtrl("D3", nCtrlIndex++, "(D3>H)", 300.0);
		item->AddParaCtrl("D4", nCtrlIndex++, "(D4>H)", 300.0);
		break;
	case 167:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("D1", nCtrlIndex++, "(D1>=0)", 300.0);
		break;
	case 168:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("A1", nCtrlIndex++, "(A1>=0)", 300.0);
		item->AddParaCtrl("A2", nCtrlIndex++, "(A2>=0)", 300.0);
		item->AddParaCtrl("B1", nCtrlIndex++, "(B1>=0)", 300.0);
		item->AddParaCtrl("B2", nCtrlIndex++, "(B2>=0)", 300.0);
		item->AddParaCtrl("C1", nCtrlIndex++, "(C1>=0)", 300.0);
		item->AddParaCtrl("C2", nCtrlIndex++, "(C2>=0)", 300.0);
		item->AddParaCtrl("D1", nCtrlIndex++, "(D1>=0)", 300.0);
		item->AddParaCtrl("D2", nCtrlIndex++, "(D2>=0)", 300.0);
		break;
	case 169:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("A1", nCtrlIndex++, "(A1>=0)", 300.0);
		item->AddParaCtrl("A2", nCtrlIndex++, "(A2>=0)", 300.0);
		break;
	case 170:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>(W/2))", 600.0);
		break;
	case 171:
		item->AddParaCtrl("BM", nCtrlIndex++, "(BM>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("D1", nCtrlIndex++, "(D1>=0)", 200.0);
		item->AddParaCtrl("D2", nCtrlIndex++, "(D2>=0)", 300.0);
		item->AddParaCtrl("S1", nCtrlIndex++, "(S1>=0)", 200.0);
		item->AddParaCtrl("S2", nCtrlIndex++, "(S2>=0)", 200.0);
		item->AddParaCtrl("S3", nCtrlIndex++, "(S3>=0)", 200.0);
		item->AddParaCtrl("S4", nCtrlIndex++, "(S4>=0)", 200.0);
		item->AddParaCtrl("S5", nCtrlIndex++, "(S5>=0)", 200.0);
		item->AddParaCtrl("S6", nCtrlIndex++, "(S6>=0)", 200.0);
		item->AddParaCtrl("S7", nCtrlIndex++, "(S7>=0)", 200.0);
		item->AddParaCtrl("S8", nCtrlIndex++, "(S8>=0)", 200.0);
		break;
	case 172:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		break;
	case 173:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(W1+W2))", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1, >H2)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 200.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 100.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>H)", 500.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 600.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 150.0);
		break;
	case 174:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(W1+W2))", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1, >H2)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 200.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 100.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>H)", 500.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 600.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 100.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 150.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0)", 200.0);
		item->AddParaCtrl("R4", nCtrlIndex++, "(R4>0)", 150.0);
		item->AddParaCtrl("R5", nCtrlIndex++, "(R5>0)", 200.0);
		item->AddParaCtrl("R6", nCtrlIndex++, "(R6>0)", 150.0);
		break;
	case 175:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(W1+W2))", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>(H1+H2))", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 150.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 200.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 10.0);
		break;
	case 176:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(W1+W2))", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>(H1+H2))", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 150.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 200.0);		
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 150.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 200.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0)", 100.0);
		item->AddParaCtrl("R4", nCtrlIndex++, "(R4>0)", 200.0);
		item->AddParaCtrl("R5", nCtrlIndex++, "(R5>0)", 150.0);
		item->AddParaCtrl("R6", nCtrlIndex++, "(R6>0)", 100.0);
		item->AddParaCtrl("R7", nCtrlIndex++, "(R7>0)", 200.0);
		item->AddParaCtrl("R8", nCtrlIndex++, "(R8>0)", 150.0);		
		break;
	case 268:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(W1+W2))", 900.0);
		item->AddParaCtrl("HS", nCtrlIndex++, "(HS>0)", 800.0);
		item->AddParaCtrl("HD", nCtrlIndex++, "(HD>0)", 800.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 900.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 950.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 300.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 300.0);
		break;
	case 96:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 200.0);
		break;
	case 97:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(H-H1))", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 800.0);
		break;
	case 98:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, <(H/2), <(w/2))", 100.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 100.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 100.0);
		break;
	case 99:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>=0, <(H/2), <(w/2))", 200.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>=0, <(H/2), <(w/2))", 250.0);
		break;
	case 100:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, <(H/2), <(w/2))", 100.0);
		break;
	case 101:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0, <(H/2), <(w/2))", 100.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0, <(H/2), <(w/2))", 100.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0, <(H/2), <(w/2))", 100.0);
		item->AddParaCtrl("R4", nCtrlIndex++, "(R4>0, <(H/2), <(w/2))", 100.0);
		break;
	case 102:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 600.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, <(H/2), <(w/2))", 100.0);
		break;
	case 104:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 300.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 200.0);
		break;
	case 105:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 300.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 100.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 100.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0)", 100.0);
		item->AddParaCtrl("R4", nCtrlIndex++, "(R4>0)", 100.0);
		break;
	case 106:
	case 108:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 600.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 200.0);
		break;
	case 110:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 900.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 800.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 100.0);
		break;
	case 111:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 900.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 800.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 100.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 100.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0)", 100.0);
		item->AddParaCtrl("R4", nCtrlIndex++, "(R4>0)", 100.0);
		break;
	case 112:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0, <(W-W2))", 400.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0, <(W-W1))", 300.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, <(W-W1-W2))", 100.0);
		break;
	case 114:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, <(W1/2), <(H/2))", 100.0);
		break;
	case 115:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0, <(W1/2), <(H/2))", 100.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0, <(W1/2), <(H/2))", 100.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0, <(W1/2), <(H/2))", 100.0);
		item->AddParaCtrl("R4", nCtrlIndex++, "(R4>0, <(W1/2), <(H/2))", 100.0);
		break;
	case 119:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(W1+W2))", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 700.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 250.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0)", 500.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 500.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0, <(W2/2), <(H/2))", 100.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0, <(W2/2), <(H/2))", 100.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0, <(W2/2), <(H/2))", 100.0);
		item->AddParaCtrl("R4", nCtrlIndex++, "(R4>0, <(W2/2), <(H/2))", 100.0);
		break;
	case 265:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 400.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 900.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 60.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 21.0);
		item->AddParaCtrl("D", nCtrlIndex++, "(D>0)", 38.0);
		item->AddParaCtrl("S", nCtrlIndex++, "(S>0)", 80.0);
		break;
	case 280:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("L", nCtrlIndex++, "(L>0)", 800.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 400.0);
		item->AddParaCtrl("A", nCtrlIndex++, "(A>0)", 90.0);
		break;
	case 177:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		break;
	case 178:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 500.0);
		break;
	case 179:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 800.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>H1)", 1000.0);
		break;
	case 180:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 500.0);
		break;
	case 181:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>W)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 800.0);
		break;
	case 182:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 600.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 300.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 200.0);
		break;
	case 183:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 800.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>H1)", 1000.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 200.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 250.0);
		break;
	case 184:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>(w/2))", 500.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>(w/2))", 500.0);
		break;
	case 188:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 500.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0, >H)", 800.0);
		break;
	case 189:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1200.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>W)", 2000.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>H)", 1400.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>W)", 2000.0);
		item->AddParaCtrl("R4", nCtrlIndex++, "(R4>H)", 1400.0);
		break;
	case 190:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1200.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 500.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 400.0);
		break;
	case 193:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1, >H2)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 600.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 600.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 600.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 600.0);
		break;
	case 197:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 700.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 600.0);
		item->AddParaCtrl("D", nCtrlIndex++, "(D>0)", 150.0);
		break;
	case 199:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 600.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>W)", 1000.0);
		break;
	case 203:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 600.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 800.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 150.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>(W*2))", 2000.0);
		break;
	case 204:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 600.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>(W/2))", 1000.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>(W/2))", 1000.0);
		item->AddParaCtrl("S1", nCtrlIndex++, "(S1>0)", 50.0);
		item->AddParaCtrl("S2", nCtrlIndex++, "(S2>0)", 100.0);
		break;
	case 208:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 200.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 300.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>(W/2))", 2000.0);
		break;
	case 209:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 600.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 200.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>(W/2))", 100.0);
		item->AddParaCtrl("A", nCtrlIndex++, "(A>(W/2))", 60.0);
		break;
	case 211:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 700.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, <(W/4))", 180.0);
		break;
	case 212:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 900.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, >(W-R1))", 400.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1<0, >(W-R))", 200.0);
		break;
	case 213:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 900.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 750.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 300.0);
		break;
	case 214:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 700.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, <(W/4))", 200.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0, <(W/2))", 200.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0, <(W/2))", 150.0);
		break;
	case 215:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 900.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, >(W-R1))", 400.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0, >(W-R))", 200.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0, <(W/2))", 100.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0, <(W/2))", 150.0);
		break;
	case 217:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 900.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, >(W-R1))", 400.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0, >(W-R))", 200.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 200.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 200.0);
		break;
	case 218:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 700.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, <(W/4))", 200.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0, <(W/2))", 150.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0, <(W/2))", 200.0);
		break;
	case 219:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 900.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, >(W-R1))", 400.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0, >(W-R))", 200.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 400.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 150.0);
		break;
	case 223:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 400.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 150.0);
		break;
	case 224:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 400.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>H)", 1000.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0)", 150.0);
		break;
	case 225:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 700.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0, <(W/2))", 150.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0, <H)", 150.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, >(W/2))", 600.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0, >(W/2))", 600.0);
		break;
	case 231:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 700.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0, <(W/2))", 150.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0, <H)", 150.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, >(W/2))", 600.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0, >(W/2))", 600.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W1>0)", 400.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H1>0)", 150.0);
		break;
	case 232:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 200.0);
		break;
	case 233:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 600.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 200.0);
		item->AddParaCtrl("W2", nCtrlIndex++, "(W2>0,<(W/2))", 300.0);
		item->AddParaCtrl("H2", nCtrlIndex++, "(H2>0,<(W/2))", 300.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 600.0);
		break;
	case 235:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>(W/2))", 500.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>(W/2))", 500.0);
		break;
	case 236:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1000.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>(W/2))", 800.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>(H/2))", 800.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>(W/2))", 800.0);
		item->AddParaCtrl("R4", nCtrlIndex++, "(R4>(H/2))", 800.0);
		break;
	case 237:
		item->AddParaCtrl("L", nCtrlIndex++, "(L>(R+R3), >(R1+R2))", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>(R+R1), >(R3+R2))", 800.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R4>0)", 150.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 150.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 150.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0)", 150.0);
		break;
	case 238:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>W1)", 1200.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 1100.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 1200.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 500.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0)", 500.0);
		break;
	case 239:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1200.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 1100.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>(W/2))", 1000.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>(W1/2))", 1000.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>(H/2))", 500.0);
		item->AddParaCtrl("R4", nCtrlIndex++, "(R4>(H/2))", 500.0);
		break;
	case 240:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1200.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 1200.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0, <(W/2))", 800.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 1600.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>0)", 100.0);
		item->AddParaCtrl("R3", nCtrlIndex++, "(R3>0)", 100.0);
		break;
	case 244:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 600.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 800.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>(W/2))", 1000.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2>(W/2))", 1000.0);
		item->AddParaCtrl("S1", nCtrlIndex++, "(S1>0)", 500.0);
		item->AddParaCtrl("S2", nCtrlIndex++, "(S2>0)", 100.0);
		break;
	case 247:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 250.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 75.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 50.0);
		break;
	case 249:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>2*(H-H1))", 800.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 800.0);
		break;
	case 263:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>(H-H1))", 600.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>H1)", 1000.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1<H)", 800.0);
		break;
	case 270:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 600.0);
		item->AddParaCtrl("A1", nCtrlIndex++, "(A1>=0)", 60.0);
		item->AddParaCtrl("A2", nCtrlIndex++, "(A2>=0)", 120.0);
		item->AddParaCtrl("B1", nCtrlIndex++, "(B1>=0)", 140.0);
		item->AddParaCtrl("B2", nCtrlIndex++, "(B2>=0)", 100.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R>0)", 40.0);
		break;
	case 273:
	case 278:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 1000.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>0)", 600.0);
		item->AddParaCtrl("W1", nCtrlIndex++, "(W1>0)", 622.0);
		item->AddParaCtrl("R", nCtrlIndex++, "(R)", 711.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2)", 1002.0);
		break;
	case 295:
		item->AddParaCtrl("W", nCtrlIndex++, "(W>0)", 900.0);
		item->AddParaCtrl("H", nCtrlIndex++, "(H>(W*2))", 1200.0);
		item->AddParaCtrl("H1", nCtrlIndex++, "(H1>0)", 800.0);
		item->AddParaCtrl("R1", nCtrlIndex++, "(R1>0)", 1000.0);
		item->AddParaCtrl("R2", nCtrlIndex++, "(R2)", 500.0);
		item->AddParaCtrl("A", nCtrlIndex++, "(A>0)", 400.0);
		item->AddParaCtrl("B", nCtrlIndex++, "(B>0)", 200.0);
		break;
	default:
		break;
	}	
	item->m_nIndex = nIndex;
}

CUISetting* CGrEditor::GetUISetting(LPCTSTR lpszIndex)
{
	UINT nIndex;
	while(lpszIndex[0]=='0')
	{	lpszIndex++;	}
	nIndex = atol(lpszIndex);
	if(nIndex>MAX_UI_SETTINGs)
		return NULL;
	return &(m_uiSettings[nIndex]);
}



void CGrEditor::OnTimer(UINT nIDEvent) 
{
	if(1==nIDEvent)
	{
		KillTimer(1);
		SetDlgItemText(IDC_EDIT_ClipX1, "0.0");
		SetDlgItemText(IDC_EDIT_ClipX2, "0.0");
		SetDlgItemText(IDC_EDIT_ClipY1, "0.0");
		SetDlgItemText(IDC_EDIT_ClipY2, "0.0");
		ResetUI();
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CGrEditor::ProcDxf()
{
	CRect rect, rcDrawing;
	CString strName=m_picAttr.szPicName;
	
	
	m_dcGraph.GetClipBox(&rect);
	rcDrawing=rect;
	rcDrawing.DeflateRect(5,5,5,5);	
	CGrPoint points[8], tmp;


	if (strstr(m_picAttr.szFilePath,".dxf")||strstr(m_picAttr.szFilePath,".DXF"))
	{
		CBenderDlg* dlg = NULL;
		dlg = (CBenderDlg *)AfxGetMainWnd();
		if (dlg != NULL)
		{
			g_strGfile = m_picAttr.szFilePath;
			dlg->ConvertDxfToGcode();
			OpenFileG(g_strGfile);	

		}
	}		
		
	m_grPath.PaintTo(&m_dcGraph, &rcDrawing, GRAPH_COLOR_FR);
		
	//将图形由设备坐标系(Y轴向下)转换为数学平面直角坐标系(Y轴向上)
	ConvertGraphCoordinate(&m_dcGraph);
		
	Invalidate(TRUE);
}

BOOL CGrEditor::OpenFileG(CString strOpenFile)
{
	FILE*			fileGlass;
	char			szBuffer[512];
	CString			sztemp;
	bool			bCut = FALSE;
	CGrArc grArc;
    GR_LINE ln1;
    if (!(fileGlass = fopen((char*)((const char*)strOpenFile), "r")))      
		return FALSE;
	int nNum = 0;
	CGrPoint dPoint,dPrePoint,dFirstPoint;	
    BOOL bFirstPoint = TRUE;
	int nG00 = 0;//标记是第二个以后的图形的开始
    while (fgets(szBuffer, sizeof(szBuffer), fileGlass))
	{				
		
		sztemp.Format("%s",szBuffer);
		int nLength = sztemp.GetLength();
		if(strstr(sztemp,"G00"))
		{
			nNum = sztemp.FindOneOf("X");
			if (nLength>nNum)
			{
				dPoint.fx = atof(sztemp.Mid(nNum+1));
			}
			nNum = sztemp.FindOneOf("Y");
			if (nLength>nNum)
			{
				dPoint.fy = atof(sztemp.Mid(nNum+1));
			}
			dPoint.Offset(m_clip.X1, m_clip.Y1);
			ln1.pt1 = dPrePoint;//直线起点
			ln1.pt2 = dPoint;//直线终点
            dFirstPoint = dPoint;//vm的起点
			dPrePoint = dPoint;//终点
			nG00++;
			if (nG00 >= 2)
			{
				nG00 = 2;
			}
		}		
		else if(strstr(sztemp,"G01"))//只保存切割直线的起点
		{
			nNum = sztemp.FindOneOf("X");
			if (nLength>nNum)
			{
				dPoint.fx = atof(sztemp.Mid(nNum+1));
			}
			nNum = sztemp.FindOneOf("Y");
			if (nLength>nNum)
			{
				dPoint.fy = atof(sztemp.Mid(nNum+1));
			}
            dPoint.Offset(m_clip.X1, m_clip.Y1);
			ln1.pt1 = dPrePoint;//直线起点
			ln1.pt2 = dPoint;//直线终点
            
            if (nG00 == 2)
            {
				m_grPath.m_bG00 = TRUE;
				nG00 = 1;
            }
			m_grPath.AddSharpNodes(&dPrePoint, 1);            
			dPrePoint = dPoint;//终点
		
		}
		else if(strstr(sztemp,"G02") || strstr(sztemp,"G03"))
		{
			DOUBLEPOINT l_dIJ;
			l_dIJ.x = 0.0;
			l_dIJ.y = 0.0;
            CGrPoint pdStart,pdCenter;
			nNum = sztemp.FindOneOf("X");
			if (nLength>nNum)
			{
				dPoint.fx = atof(sztemp.Mid(nNum+1));
			}
			nNum = sztemp.FindOneOf("Y");
			if (nLength>nNum)
			{
				dPoint.fy = atof(sztemp.Mid(nNum+1));
			}
			nNum = sztemp.FindOneOf("I");
			if (nLength>nNum)
			{
				l_dIJ.x = atof(sztemp.Mid(nNum+1));
			}
			nNum = sztemp.FindOneOf("J");
			if (nLength>nNum)
			{
				l_dIJ.y = atof(sztemp.Mid(nNum+1));
			}
            dPoint.Offset(m_clip.X1, m_clip.Y1);
            pdStart = dPrePoint;
            pdCenter = pdStart;
			pdCenter.Offset(l_dIJ.x,l_dIJ.y);
			double r = hypot(l_dIJ.x,l_dIJ.y);
			
			if (fabs(pdStart.fx-dPoint.fx)>0.05||fabs(pdStart.fy-dPoint.fy)>0.05)
			{
				if (nG00 == 2)
				{
					m_grPath.m_bG00 = TRUE;
					nG00 = 1;
				}
				grArc.InitArc(r, pdCenter, pdStart,dPoint);
				m_grPath.AddArcNode(grArc);
			}
			else//整圆
			{
				grArc.InitCircle(r, pdCenter);
				m_grPath.AddIndependentCircleNode(grArc);
			}
			dPrePoint = dPoint;
		}
// 		else if (strstr(sztemp,"M14"))
// 		{
// 			if (fabs(dFirstPoint.fx-dPoint.fx)>0.05 
// 				|| fabs(dFirstPoint.fy-dPoint.fy)>0.05)
// 			{
// 				dPoint.Offset(m_clip.X1, m_clip.Y1);
// 				m_grPath.AddSharpNodes(&dPoint, 1);
// 			}
// 		}
	}
	fclose(fileGlass);
	return TRUE;
}