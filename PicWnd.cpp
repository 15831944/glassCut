// PicWnd.cpp : implementation file
//

#include "stdafx.h"
#include "PicWnd.h"
#include "bender.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicWnd

CPicWnd::CPicWnd()
{
	m_nIndex=0;
	m_bFocus=FALSE;
	m_bi=NULL;
	m_bits=NULL;
}

CPicWnd::~CPicWnd()
{
	ReleaseResource();
}


BEGIN_MESSAGE_MAP(CPicWnd, CWnd)
	//{{AFX_MSG_MAP(CPicWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPicWnd message handlers

BOOL CPicWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd) 
{
	static UINT s_nInstCount=0;
	LPCTSTR lpszClassName=NULL;
	char szWindowName[64];
	UINT nID=14000+s_nInstCount;
	CCreateContext* pContext=NULL;	
	sprintf(szWindowName, "PicWnd-%d", s_nInstCount);
	if(!CWnd::Create(lpszClassName, szWindowName, dwStyle, rect, pParentWnd, nID, pContext))
		return FALSE;
	PostMessage(WM_SIZE, 0,0);
	return TRUE;
}

void CPicWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect(&rc);
	dc.BitBlt(0,0, rc.Width(), rc.Height(), &m_mDC, 0, 0, SRCCOPY);
}

void CPicWnd::SetWndIndex(UINT nIndex)
{
	m_nIndex=nIndex;
}

void CPicWnd::Clean(BOOL bInvalidate)
{
	ReleaseResource();
}

void CPicWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	CDC *pDC=GetDC();
	CBitmap bmp;
	CRect rc;
	GetClientRect(&rc);
	if(pDC && !rc.IsRectEmpty())
	{
		if(m_mDC.m_hDC)		m_mDC.DeleteDC();
		bmp.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
		m_mDC.CreateCompatibleDC(pDC);
		if(m_mDC.m_hDC)
		{
			m_mDC.SelectObject(&bmp);
			if(bmp.m_hObject)
				bmp.DeleteObject();
			m_mDC.FillSolidRect(0, 0, rc.Width(), rc.Height(), RGB(0,0,0));
			RefreshImage();
		}
	}
	if(pDC)
		ReleaseDC(pDC);
}

void CPicWnd::SetWndFocus(BOOL bFocus)
{
	if(m_bFocus==bFocus)
		return;
	m_bFocus = bFocus;
	RefreshImage();
	Invalidate(FALSE);
}

void CPicWnd::RefreshImage()
{
	CRect rt;
	CString str;
	CBrush br;
	GetClientRect(&rt);

	if(m_mDC.m_hDC)
	{
		m_mDC.FillSolidRect(&rt, BK_CORLOR);
        if (m_picAttr.nIndex != 301)
		{
			if(m_bi && m_bits)
			{
				CRect rc=rt;
				SIZE size={rc.Width()/8, rc.Height()/8};
				rc.DeflateRect(size);
				StretchDIBits(m_mDC.GetSafeHdc(),
					size.cx, size.cy, rc.Width(), rc.Height(),
					0,0, m_bi->bmiHeader.biWidth, m_bi->bmiHeader.biHeight,
					m_bits, m_bi, 
					DIB_RGB_COLORS,SRCCOPY);
			}
		}
		if(m_bFocus)
			ReplaceColor(&m_mDC, RGB(220,220,220), RGB(255,255,255), RGB(220,220,220));
		br.CreateSolidBrush(RGB(0,0,160));
		rt.DeflateRect(1,1,1,1);
		m_mDC.FrameRect(&rt, &br);
		str.Format("%s", m_picAttr.szPicName);
		m_mDC.SetTextColor(RGB(255,0,0));
		if (m_picAttr.nIndex == 301)
		{
			m_mDC.SetTextAlign(TA_CENTER);
			m_mDC.TextOut(rt.Width()/2,rt.Height()/2-5, str);
		}
		else
		{
			m_mDC.TextOut(2,2, str);
		}
	}
}

void CPicWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd *pParent = GetParent();
	if(pParent)
		pParent->PostMessage(UM_PICWND_MSG, PICWND_LBUTTONDOWN, (LPARAM)this);
	CWnd::OnLButtonDown(nFlags, point);
}

BOOL CPicWnd::LoadBmpFile(PIC_ATTR &attr)
{
	CFile file;
	BITMAPFILEHEADER bfh;
	BOOL bFine;
	UINT length;

	ReleaseResource();  
	if (attr.nIndex == 301)
	{
		memcpy(&m_picAttr, &attr, sizeof(PIC_ATTR));
		RefreshImage();
		return TRUE;
	}
	bFine=FALSE;
	do 
	{
		BYTE *ptr=NULL;
		if(!file.Open(attr.szFilePath, CFile::modeRead))
			break;
		length = file.GetLength();
		file.Read(&bfh, sizeof(BITMAPFILEHEADER));
		if(bfh.bfType!=0x4D42)
			break;
		if(length<bfh.bfSize)
			break;
		length = (bfh.bfSize-bfh.bfOffBits);
		ptr = new BYTE[sizeof(BITMAPINFOHEADER)+length];
		file.Read(ptr, sizeof(BITMAPINFOHEADER)+length);
		m_bi = (BITMAPINFO *)ptr;
		m_bits = ptr+sizeof(BITMAPINFOHEADER);
		if(m_bi->bmiHeader.biSizeImage>length)
			m_bi->bmiHeader.biSizeImage=length;
		memcpy(&m_picAttr, &attr, sizeof(PIC_ATTR));
		bFine=TRUE;
	} while (0);
	if(file.m_hFile!=(UINT)-1)
		file.Close();

	if(bFine)
	{
		RefreshImage();
		Invalidate(FALSE);
	}
	else
	{
		ReleaseResource();
	}
	if(file.m_hFile!=(UINT)(-1))
		file.Close();
	return bFine;
}

void CPicWnd::ReleaseResource()
{
	if(m_bi)
		delete m_bi;
	m_bi=NULL;
	m_bits=NULL;
	memset(&m_picAttr, 0, sizeof(PIC_ATTR));
}

UINT CPicWnd::GetWndIndex()
{
	return m_nIndex;
}

const PIC_ATTR* CPicWnd::GetPicAttribute()
{
	return &m_picAttr;
}

UINT CPicWnd::GetPicType()
{
	return m_picAttr.nPicType;
}
