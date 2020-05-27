// MyFrame.cpp : implementation file
//

#include "stdafx.h"
#include "MyFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SCROLL_BAR_WIDTH 18

/////////////////////////////////////////////////////////////////////////////
// CMyFrame

CMyFrame::CMyFrame()
{
	memset(&m_siV, 0, sizeof(SCROLLINFO));
}

CMyFrame::~CMyFrame()
{
}


BEGIN_MESSAGE_MAP(CMyFrame, CWnd)
	//{{AFX_MSG_MAP(CMyFrame)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFrame message handlers
BOOL CMyFrame::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd) 
{
	static UINT s_nInstCount=0;
	LPCTSTR lpszClassName=NULL;
	char szWindowName[64];
	UINT nID=10000+s_nInstCount;
	CCreateContext* pContext=NULL;	
	sprintf(szWindowName, "MyFrame-%d", s_nInstCount);
	if(!CWnd::Create(lpszClassName, szWindowName, dwStyle, rect, pParentWnd, nID, pContext))
		return FALSE;
	return TRUE;
}

void CMyFrame::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	CRect rt;
	GetClientRect(&rt);
	if(!rt.IsRectEmpty())
	{
		if(m_wndPicList.m_hWnd)
			m_wndPicList.MoveWindow(rt.left, rt.top, rt.right, rt.bottom);
	}
	ResetVScrollbar();
}

CPicWnd *CMyFrame::PicWndAddNew(PIC_ATTR &attr)
{
	CPicWnd *pWnd=NULL;
	if(m_wndPicList.m_hWnd)
		pWnd = m_wndPicList.ListPicWndAddNew(attr);
	ResetVScrollbar();
	return pWnd;
}

void CMyFrame::PicWndRemoveAll()
{
	CRect rt;
	if(m_wndPicList.m_hWnd)
	{
		m_wndPicList.ListPicWndRemoveAll();
		GetClientRect(&rt);
		m_wndPicList.SetWindowPos(NULL, rt.left, rt.top, rt.right, rt.bottom, SWP_NOMOVE);
	}
	ResetVScrollbar();
}

void CMyFrame::PicWndSetFocus(UINT nWndIndex)
{
	if(m_wndPicList.m_hWnd)
	{
		m_wndPicList.ListPicWndSetFocus(nWndIndex);
	}
}

int  CMyFrame::PicWndGetFocus()
{
	if(!m_wndPicList.m_hWnd)
		return -1;
	return m_wndPicList.ListPicWndGetFocus();
}

CPicWnd* CMyFrame::PicWndGetAt(int nWndIndex)
{
	if(!m_wndPicList.m_hWnd)
		return NULL;
	return m_wndPicList.ListPicWndGetAt(nWndIndex);
}

BOOL CMyFrame::Initialize(UINT nColumns/*=1*/)
{
	CRect rt;
	GetClientRect(&rt);	
	if(!m_wndPicList.m_hWnd)
		m_wndPicList.Create(WS_VISIBLE|WS_CHILD, rt, this);
	if(!m_wndPicList.m_hWnd)
		return FALSE;
	m_wndPicList.Initialize(nColumns);
	ResetVScrollbar();
	return TRUE;
}

void CMyFrame::SetVScrollPos(int nPos)
{
	if(nPos < 0)
		nPos = 0;

	CRect rt, rtListWnd=CRect(0,0,0,0);
	GetClientRect(&rt);
	
	if(m_wndPicList.m_hWnd)
	{
		m_wndPicList.GetClientRect(&rtListWnd);
		m_wndPicList.SetWindowPos(NULL, rt.left, rt.top, 0,0,SWP_NOSIZE);
		m_wndPicList.GetClientRect(&rtListWnd);
		if(nPos>0)
			m_wndPicList.SetWindowPos(NULL, rt.left, rt.top-nPos, 0,0,SWP_NOSIZE);
	}

	//设定滚动条垂直滚动范围及页面大小
	memset(&m_siV, 0, sizeof(SCROLLINFO));
	GetScrollInfo(SB_VERT, &m_siV) ;
	m_siV.fMask  = SIF_RANGE|SIF_PAGE|SIF_POS;
	m_siV.nPos   = nPos;
	m_siV.nMax   = rtListWnd.Height();	//内容的高度
	if(!m_siV.nMax)
		m_siV.nMax=rt.Height();
	m_siV.nPage  = rt.Height();			//页面的高度
	SetScrollInfo(SB_VERT, &m_siV, TRUE);
}

void CMyFrame::ResetVScrollbar()
{
	SetVScrollPos(0);
}

void CMyFrame::Clean()
{
	PicWndRemoveAll();
}


void CMyFrame::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_siV.cbSize = sizeof (m_siV) ;
	m_siV.fMask  = SIF_ALL ;
	GetScrollInfo(SB_VERT, &m_siV);
	
	int iVertPos = m_siV.nPos ;
	switch(nSBCode)
	{
	case SB_TOP:
		m_siV.nPos = m_siV.nMin;	break;
	case SB_BOTTOM:
		m_siV.nPos = m_siV.nMax;	break;
	case SB_LINEUP:
		m_siV.nPos -= m_wndPicList.GetItemHeight()/2;	break;
	case SB_LINEDOWN:
		m_siV.nPos += m_wndPicList.GetItemHeight()/2;	break;
	case SB_PAGEUP:
		m_siV.nPos -= m_siV.nPage;	break;
	case SB_PAGEDOWN:
		m_siV.nPos += m_siV.nPage;	break;
	case SB_THUMBTRACK:
		m_siV.nPos = m_siV.nTrackPos; break;
	case SB_THUMBPOSITION:
		m_siV.nPos = nPos; break;
	}
	
	m_siV.fMask = SIF_POS ;
	SetScrollInfo(SB_VERT, &m_siV, TRUE) ;
	GetScrollInfo(SB_VERT, &m_siV) ;
	if(m_siV.nPos != iVertPos)
	{
		ScrollWindow(0, iVertPos - m_siV.nPos, NULL, NULL);
		UpdateWindow();
		::UpdateWindow(GetParent()->m_hWnd);
	}
	
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}



BOOL CMyFrame::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if(zDelta>0)	OnVScroll(SB_LINEUP, 0, NULL);
	else			OnVScroll(SB_LINEDOWN, 0, NULL);
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}



void CMyFrame::ItemEnsureVisable(UINT nWnd)
{
	if(!m_wndPicList.m_hWnd)
		return;
	//nWnd是否有效
	if(!m_wndPicList.ListPicWndGetAt(nWnd))
		return;

	SCROLLINFO siv;
	memset(&siv, 0, sizeof(SCROLLINFO));
	GetScrollInfo(SB_VERT, &siv) ;

	int cyItem = m_wndPicList.GetItemHeight();
	int yWndInList = m_wndPicList.RetrieveItemRow(nWnd)*cyItem;
	CRect rc, rtThis;

	if(cyItem<=0)	return;
	GetClientRect(&rtThis);

	//Item在this窗口中的上下中点
	POINT ptTop = {rtThis.Width()/2, yWndInList-siv.nPos};
	POINT ptBot = {ptTop.x, ptTop.y+cyItem-1};

	if(rtThis.PtInRect(ptTop) && rtThis.PtInRect(ptBot))
		return;

	int yPos = (yWndInList+cyItem)-siv.nPage;
	if(yPos < 0)	yPos = 0;

	SetVScrollPos(yPos);
}

UINT CMyFrame::PicWndGetCount()
{
	if(!m_wndPicList.m_hWnd)
		return 0;
	return m_wndPicList.ListPicWndGetCount();
}


BOOL CMyFrame::PreTranslateMessage(MSG* pMsg) 
{
	int nFocusItem;
	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		switch(pMsg->wParam)
		{
		case VK_DOWN:
		case VK_RIGHT:
			if(!m_wndPicList.m_hWnd)	break;
			nFocusItem = PicWndGetFocus();
			if(nFocusItem>=0 && (++nFocusItem)<(int)PicWndGetCount())
			{
				PicWndSetFocus(nFocusItem);
				ItemEnsureVisable(nFocusItem);
				//发送一个左键单击图片的消息
				m_wndPicList.PostMessage(UM_PICWND_MSG, PICWND_LBUTTONDOWN, (LPARAM)m_wndPicList.ListPicWndGetFocusWnd());
			}
			return TRUE;
			break;
		case VK_UP:
		case VK_LEFT:
			if(!m_wndPicList.m_hWnd)	break;
			nFocusItem = PicWndGetFocus();
			if(--nFocusItem>=0)
			{
				PicWndSetFocus(nFocusItem);
				ItemEnsureVisable(nFocusItem);
				//发送一个左键单击图片的消息
				m_wndPicList.PostMessage(UM_PICWND_MSG, PICWND_LBUTTONDOWN, (LPARAM)m_wndPicList.ListPicWndGetFocusWnd());
			}
			return TRUE;
			break;
		}
		break;
	default: break;
	}
	return CWnd::PreTranslateMessage(pMsg);
}

void CMyFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}


CPicListWnd* CMyFrame::GetPicListWnd()
{
	return &m_wndPicList;
}
