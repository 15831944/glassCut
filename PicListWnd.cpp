// PicListWnd.cpp : implementation file
//

#include "stdafx.h"
#include "PicListWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicListWnd

CPicListWnd::CPicListWnd()
{
	m_nFocusIndex = -1;
	m_nColumns=1;
	memset(&m_sizeItem, 0, sizeof(SIZE));
}

CPicListWnd::~CPicListWnd()
{
}


BEGIN_MESSAGE_MAP(CPicListWnd, CWnd)
	//{{AFX_MSG_MAP(CPicListWnd)
	ON_WM_DESTROY()
	ON_MESSAGE(UM_PICWND_MSG, UsermsgPicWndMsg)
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPicListWnd message handlers
BOOL CPicListWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd) 
{
	static UINT s_nInstCount=0;
	LPCTSTR lpszClassName=NULL;
	char szWindowName[64];
	UINT nID=12000+s_nInstCount;
	CCreateContext* pContext=NULL;	
	sprintf(szWindowName, "PicListWnd-%d", s_nInstCount);
	if(!CWnd::Create(lpszClassName, szWindowName, dwStyle, rect, pParentWnd, nID, pContext))
		return FALSE;
	return TRUE;
}

void CPicListWnd::OnDestroy() 
{
	CWnd::OnDestroy();
	
	ListPicWndRemoveAll();
}

void CPicListWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	CRect rt;
	GetClientRect(&rt);

	if(!rt.IsRectEmpty())
	{
		m_sizeItem.cx = rt.Width()/m_nColumns;
		m_sizeItem.cy = m_sizeItem.cx;
		
		POSITION pos = m_lstPicWnd.GetHeadPosition();
		UINT index=0;
		CPicWnd *pNode=NULL;
		while(pos)
		{
			pNode = (CPicWnd*)m_lstPicWnd.GetNext(pos);
			if(pNode)
				ListPicWndPlace(index, pNode);
			index++;
		}
	}
}

CPicWnd *CPicListWnd::ListPicWndAddNew(PIC_ATTR &attr)
{
	CWnd *parent = GetParent();
	UINT nNewPicWndIndex;
	CPicWnd *pNode=NULL, *pNewWnd=NULL;
	POSITION pos=NULL;
	
	nNewPicWndIndex = m_lstPicWnd.GetCount();	
	pNewWnd = new CPicWnd();
	if(!pNewWnd)	return NULL;

	CString strIndex;
	strIndex.Format(_T("%d"), nNewPicWndIndex);
	if(!pNewWnd->Create(WS_CHILD|WS_VISIBLE|WS_EX_CLIENTEDGE, CRect(0, 0, 0, 0), this))
	{
		delete pNewWnd;
		pNewWnd=NULL;
		return NULL;
	}
	if(!pNewWnd->LoadBmpFile(attr))
	{
		delete pNewWnd;
		pNewWnd=NULL;
		return NULL;
	}

	UINT nRows = RetrieveItemRow((nNewPicWndIndex+1)+(m_nColumns-1));

	//检查是否需要加大窗口高度
	int nTotalHeight;
	CRect rect;
	GetClientRect(&rect);
	nTotalHeight	= nRows*(m_sizeItem.cy);
	if(nTotalHeight>rect.Height())
	{
		CRect rwm;
		this->GetWindowRect(&rwm);
		SetWindowPos(NULL, 0, 0, rwm.Width(), nTotalHeight, SWP_NOMOVE);
	}
	DWORD dwTemp = (DWORD)pNewWnd;
	pNewWnd->SetWndIndex(nNewPicWndIndex);
	m_lstPicWnd.AddTail(dwTemp);
	ListPicWndPlace(nNewPicWndIndex, pNewWnd);
	return pNewWnd;
}

void CPicListWnd::ListPicWndPlace(UINT nPicWndIndex, CPicWnd *pPicWnd)
{
	CRect rect, rc;
	if( !(pPicWnd && nPicWndIndex<(UINT)m_lstPicWnd.GetCount()) )
		return;
	
	UINT nRow = RetrieveItemRow(nPicWndIndex);
	UINT nCol = RetrieveItemColumn(nPicWndIndex);

	GetClientRect(&rect);
	rc.left		= rect.left+(m_sizeItem.cx*nCol);
	rc.top		= rect.top + (m_sizeItem.cy*nRow);
	rc.right	= rc.left + m_sizeItem.cx;
	rc.bottom	= rc.top + m_sizeItem.cy;
	pPicWnd->MoveWindow(&rc);
}

void CPicListWnd::ListPicWndRemoveAll()
{
	DWORD node;
	CPicWnd *pPicWnd=NULL;
	while(m_lstPicWnd.GetCount())
	{
		node = m_lstPicWnd.GetTail();
		pPicWnd = (CPicWnd*)node;
		if(pPicWnd)	pPicWnd->Clean(FALSE);
		delete pPicWnd;
		m_lstPicWnd.RemoveTail();
	}
	m_nFocusIndex = -1;
	Invalidate();
}

LRESULT CPicListWnd::UsermsgPicWndMsg(WPARAM wParam, LPARAM lParam)
{
	CPicWnd *pWnd=NULL;
	UINT nWndIndex;
	CWnd *parpar=NULL;

	pWnd=(CPicWnd*)lParam;
	if(!pWnd)
		return 0;
	nWndIndex = pWnd->GetWndIndex();
	parpar = this->GetParent()->GetParent();

	switch(wParam)
	{
	case PICWND_LBUTTONDOWN:
		{
			ListPicWndSetFocus(nWndIndex);
			this->SetFocus();
			if(parpar)
				parpar->PostMessage(UM_LISTWND_MSG, PICWND_LBUTTONDOWN, (LPARAM)this);
		}
		break;
	case PICWND_LBUTTONDBCLK:
		{
			this->SetFocus();
		}
		break;
	case PICWND_RBUTTONDOWN:
		{
			ListPicWndSetFocus(nWndIndex);
			this->SetFocus();
		}
	}
	return 0;
}

void CPicListWnd::ListPicWndSetFocus(UINT nWndIndex)
{
	CPicWnd *pNode=NULL;
	POSITION pos=NULL;

	//取消原焦点
	if(m_nFocusIndex>=0)
	{
		pos = m_lstPicWnd.FindIndex(m_nFocusIndex);
		if(pos)
		{
			pNode = (CPicWnd*)m_lstPicWnd.GetAt(pos);
			if(pNode)
			{
				pNode->SetWndFocus(FALSE);
				m_nFocusIndex = -1;
			}
		}
	}

	//设置新焦点
	if(m_lstPicWnd.GetCount() < 1)
		return;
	if(nWndIndex >= (UINT)m_lstPicWnd.GetCount())
		nWndIndex = (UINT)m_lstPicWnd.GetCount()-1;
	pos = m_lstPicWnd.FindIndex(nWndIndex);
	if(pos)
	{
		pNode = (CPicWnd*)m_lstPicWnd.GetAt(pos);
		if(pNode)
		{
			pNode->SetWndFocus(TRUE);
			m_nFocusIndex = nWndIndex;
		}
	}
}


int CPicListWnd::ListPicWndGetFocus()
{
	return m_nFocusIndex;
}


BOOL CPicListWnd::Initialize(UINT nColumns/*=1*/)
{
	if(!this->m_hWnd)
		return FALSE;
	m_nColumns=nColumns;
	if(!m_nColumns)
		m_nColumns=1;
	PostMessage(WM_SIZE, 0,0);
	return TRUE;
}


UINT CPicListWnd::GetItemHeight()
{
	return m_sizeItem.cy;
}

CPicWnd* CPicListWnd::ListPicWndGetAt(int nWndIndex)
{
	POSITION pos = m_lstPicWnd.FindIndex(nWndIndex);
	if(!pos)		return NULL;
	return ((CPicWnd*)m_lstPicWnd.GetAt(pos));
}

UINT CPicListWnd::ListPicWndGetCount()
{
	return m_lstPicWnd.GetCount();
}

void CPicListWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CWnd *parent = GetParent();
	CRect rtPar, rect;
#if 0
	if(parent)
	{
		parent->GetClientRect(rtPar);

		int nTotalHeight = RetrieveItemRow(m_lstPicWnd.GetCount())*m_sizeItem.cy;
 		if(nTotalHeight < rtPar.Height())
		{
			GetClientRect(&rect);
			CRect rc = CRect(rect.left, rect.top+nTotalHeight, rect.Width(), rect.Height());
			dc.FillSolidRect(&rc, RGB(255,255,255));
		}
	}
#else
	CRect rc;
	GetClientRect(&rect);
	rc = rect;
// 	if(rect.Height()>=(m_sizeItem.cy*2))
// 		rc.top = rc.right-(m_sizeItem.cy*2);
	dc.FillSolidRect(&rc, RGB(255,255,255));
#endif
}


UINT CPicListWnd::RetrieveItemColumn(UINT nIndex)
{
	return (nIndex%m_nColumns);
}

UINT CPicListWnd::RetrieveItemRow(UINT nIndex)
{
	return (nIndex/m_nColumns);
}

CPicWnd* CPicListWnd::ListPicWndGetFocusWnd()
{
	if(m_nFocusIndex<0)
		return NULL;
	return ListPicWndGetAt(m_nFocusIndex);
}

