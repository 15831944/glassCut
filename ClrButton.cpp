// ClrButton.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "ClrButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const COLORREF CLR_BTN_WHITE  = RGB(255, 255, 255);
const COLORREF CLR_BTN_BLACK  = RGB(0, 0, 0);
const COLORREF CLR_BTN_DGREY  = RGB(128, 128, 128);
const COLORREF CLR_BTN_GREY   = RGB(192, 192, 192);
const COLORREF CLR_BTN_LLGREY = RGB(223, 223, 223);

const int BUTTON_IN			  = 0x00;
const int BUTTON_OUT		  = 0x01;
const int BUTTON_BLACK_BORDER = 0x04;
const int m_borderIn          = 3;

/////////////////////////////////////////////////////////////////////////////
// CClrButton

CClrButton::CClrButton()
{
	text_colour					= GetSysColor(COLOR_BTNTEXT);
	background_colour			= GetSysColor(COLOR_BTNFACE); 
	disabled_background_colour	= background_colour;
	light						= GetSysColor(COLOR_3DLIGHT);
	highlight					= GetSysColor(COLOR_BTNHIGHLIGHT);
	shadow						= GetSysColor(COLOR_BTNSHADOW);
	dark_shadow					= GetSysColor(COLOR_3DDKSHADOW);
	focus_colour				= RGB(0, 128, 0);
	stateA = 1;
	wParam = 0;
	lParam = 0;
	nIcon = 0;
}

CClrButton::~CClrButton()
{
}

void CClrButton::SetColour(COLORREF new_text_colour)
{
	text_colour					= new_text_colour;
	background_colour			= GetSysColor(COLOR_BTNFACE); 
	disabled_background_colour	= GetSysColor(COLOR_BTNFACE); 
	
	Invalidate(FALSE);
}

void CClrButton::SetState(int style)
{
	stateA = style;
	Invalidate(FALSE);
}

int CClrButton::GetState()
{
	return stateA;
}

void CClrButton::SetIconOption(UINT nUseIcon)
{
	nIcon = nUseIcon;
	Invalidate(FALSE);
}

UINT CClrButton::GetIconOption()
{
	return nIcon;
}

void CClrButton::SetColour(COLORREF new_text_colour, COLORREF new_background_colour)
{
	text_colour					= new_text_colour;
	background_colour			= new_background_colour; 
	disabled_background_colour	= GetSysColor(COLOR_BTNFACE); 

	Invalidate(FALSE);
}

void CClrButton::SetColour(COLORREF new_text_colour, COLORREF new_background_colour, COLORREF new_disabled_background_colour)
{
	text_colour					= new_text_colour;
	background_colour			= new_background_colour; 
	disabled_background_colour	= new_disabled_background_colour; 

	Invalidate(FALSE);
}

void CClrButton::ResetColour()
{
	text_colour					= GetSysColor(COLOR_BTNTEXT);
	background_colour			= GetSysColor(COLOR_BTNFACE); 
	disabled_background_colour	= background_colour;
	light						= GetSysColor(COLOR_3DLIGHT);
	highlight					= GetSysColor(COLOR_BTNHIGHLIGHT);
	shadow						= GetSysColor(COLOR_BTNSHADOW);
	dark_shadow					= GetSysColor(COLOR_3DDKSHADOW);

	Invalidate(FALSE);
}

BEGIN_MESSAGE_MAP(CClrButton, CButton)
	//{{AFX_MSG_MAP(CClrButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClrButton message handlers

void CClrButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC		*dc;
	CRect	focus_rect, button_rect, text_rect, offset_text_rect;
	UINT	state;
	
	dc    = CDC::FromHandle(lpDrawItemStruct->hDC);
	state = lpDrawItemStruct->itemState;

	focus_rect.CopyRect(&lpDrawItemStruct->rcItem); 
	button_rect.CopyRect(&lpDrawItemStruct->rcItem); 

	text_rect = button_rect;
	text_rect.OffsetRect(-1, -1); 
	offset_text_rect = text_rect;
	offset_text_rect.OffsetRect(1, 1);

	// Set the focus rectangle to just past the border decoration
	focus_rect.left   += 4;
    focus_rect.right  -= 4;
    focus_rect.top    += 4;
    focus_rect.bottom -= 4;
      
	// Retrieve the button's caption
    const int bufSize = 512;
    TCHAR buffer[bufSize];
    GetWindowText(buffer, bufSize);

	if (state & ODS_DISABLED)
    {
		DrawFilledRect(dc, button_rect, disabled_background_colour);
	}
	else
	{
		DrawFilledRect(dc, button_rect, background_colour);
	}
		
	if (state & ODS_SELECTED)
	{
    	DrawFrame(dc, button_rect, BUTTON_IN ,stateA);//
	}
	else
	{
		DrawFrame(dc, button_rect, BUTTON_OUT,stateA);
	}

	if (state & ODS_DISABLED)
	{
		DrawButtonTextA(dc, offset_text_rect, buffer, CLR_BTN_WHITE);
		DrawButtonTextA(dc, text_rect,		 buffer, CLR_BTN_DGREY);
	}
	else
	{
		if (state & ODS_SELECTED)
		{
			DrawButtonTextA(dc, offset_text_rect, buffer, text_colour);
			lParam = 1;
			if(wParam < lParam)			
//				GetParentOwner()->PostMessage(WM_MOUSEDN,GetDlgCtrlID(),lParam);
			if(nIcon>0)
				DrawButtonIcon(dc, offset_text_rect/*focus_rect*/);
		}
		else
		{
			lParam = 0;
			DrawButtonTextA(dc, text_rect, buffer, text_colour);
			if(nIcon>0)
				DrawButtonIcon(dc, text_rect/*focus_rect*/);
		}
		wParam = lParam;
	}	
} 

void CClrButton::DrawFrame(CDC *dc, CRect r, int state, int style)
{ 
	COLORREF colour;
	
	light						= GetSysColor(COLOR_3DLIGHT);
	highlight					= GetSysColor(COLOR_BTNHIGHLIGHT);
	shadow						= GetSysColor(COLOR_BTNSHADOW);
	dark_shadow					= GetSysColor(COLOR_3DDKSHADOW);
	if (!state)
	{
		colour = dark_shadow;
		DrawLine(dc, 1 , r, colour); // Across top
		colour = highlight;
		DrawLine(dc, 0 , r, colour); // Down left
		
		r.InflateRect(m_borderIn, m_borderIn);
	}
	else
	{
		if(style)      /* 1为正常，0为模态按钮 */
		{
			colour = highlight;
			DrawLine(dc, 1 , r, colour); // Across top
			colour = dark_shadow;
			DrawLine(dc, 0 , r, colour); // Down left
		}
		else
		{
			colour = dark_shadow;
			DrawLine(dc, 1 , r, colour); // Across top
			colour = highlight;
			DrawLine(dc, 0 , r, colour); // Down left
		}
		
		r.InflateRect(m_borderIn, m_borderIn);
	}
	
}

void CClrButton::DrawFilledRect(CDC *dc, CRect r, COLORREF colour)
{ 
	CBrush B;
	B.CreateSolidBrush(colour);
	dc->FillRect(r, &B);
}

void CClrButton::DrawLine(CDC *dc, int pos, CRect r, COLORREF colour)
{ 
	CRgn    polyRgn;
	CPoint  ptVertex[6];
    CBrush  pBrush;
	pBrush.CreateSolidBrush(colour);  
	if(pos)
	{
		ptVertex[0].x = r.left;
		ptVertex[0].y = r.bottom;
		ptVertex[1].x = ptVertex[0].x;
		ptVertex[1].y = r.top;
		ptVertex[2].x = r.right;
		ptVertex[2].y = ptVertex[1].y;
		ptVertex[3].x = r.right - m_borderIn;
		ptVertex[3].y = r.top + m_borderIn;
		ptVertex[4].x = r.left + m_borderIn;
		ptVertex[4].y = ptVertex[3].y;
		ptVertex[5].x = ptVertex[4].x;
		ptVertex[5].y = r.bottom - m_borderIn;
	}
	else
	{
		ptVertex[0].x = r.left;
		ptVertex[0].y = r.bottom;
		ptVertex[1].x = r.right;
		ptVertex[1].y = ptVertex[0].y;
		ptVertex[2].x = ptVertex[1].x;
		ptVertex[2].y = r.top;
		ptVertex[3].x = r.right - m_borderIn;
		ptVertex[3].y = r.top + m_borderIn;
		ptVertex[4].x = ptVertex[3].x;
		ptVertex[4].y = r.bottom - m_borderIn;
		ptVertex[5].x = r.left + m_borderIn;
		ptVertex[5].y = ptVertex[4].y;
	}
	polyRgn.CreatePolygonRgn(ptVertex, 6, WINDING);//ALTERNATE
    dc->FillRgn( &polyRgn, &pBrush );
}


void CClrButton::DrawButtonText(CDC *dc, CRect r, const char *Buf, COLORREF text_colour)
{
    COLORREF previous_colour;

	previous_colour = dc->SetTextColor(text_colour);
    dc->SetBkMode(TRANSPARENT);
	dc->DrawText(Buf, strlen(Buf), r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc->SetTextColor(previous_colour);
}

void CClrButton::DrawButtonTextA(CDC *dc, CRect r, const char *Buf, COLORREF text_colour)
{
	if(nIcon>0)	
		return;
    COLORREF previous_colour;
	CString  szbuf;
	long     szLong;
	char     *pch,*pbuf;
	CRect    r1,r2;

	szbuf.Format("%s",Buf);
	szLong = szbuf.GetLength();
	previous_colour = dc->SetTextColor(text_colour);
    dc->SetBkMode(TRANSPARENT);
	pbuf = szbuf.GetBuffer(0);
	pch = strchr(szbuf,' ');
	if(pch)
	{
		*pch = '\0';
		pch++;
		r1.left = r2.left = r.left;
		r1.right = r2.right = r.right;
		r1.top = r.top;
		r1.bottom = r2.top = r.bottom/2;
		r2.bottom = r.bottom;
		r1.top = r1.top + (long)(10/**g_dScale.y*/);
		r2.bottom = r2.bottom - (long)(10/**g_dScale.y*/);
		dc->DrawText(pbuf, strlen(pbuf), r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);  //DT_VCENTER
		dc->DrawText(pch, strlen(pch), r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);       //DT_VCENTER
	}
	else
		dc->DrawText(pbuf, strlen(pbuf), r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc->SetTextColor(previous_colour);
}

void CClrButton::DrawButtonIcon(CDC *dc, CRect r)
{
//    dc->SetBkMode(TRANSPARENT);
 	if(r.Width()>80)
	{
		CString str;
		GetWindowText(str);
        int nPre = dc->SetBkMode(TRANSPARENT);
		dc->TextOut(r.right/2,r.bottom/2-10,str);
	    dc->DrawIcon(10, r.bottom/2-12, /*LoadOEMIcon*/theApp.LoadIcon(nIcon));
		dc->SetBkMode(nPre);
	}
	else
	{
		dc->DrawIcon(r.right/2-12, r.bottom/2-12, /*LoadOEMIcon*/theApp.LoadIcon(nIcon));
	}
}

void CClrButton::DrawFocusRectA(CDC *dc, CRect r)
{
	CPen	*pOldPen, pNewPen;
	int		nBordX, nBordY;
	
	nBordX = r.right/4;
	nBordY = r.bottom/4;
	
	pNewPen.CreatePen(PS_SOLID, 3, focus_colour);
	pOldPen = dc->GetCurrentPen();
	
	dc->SelectObject(&pNewPen);
	r.InflateRect(-1, -1);
	dc->MoveTo(r.left, r.top + nBordY);
	dc->LineTo(r.left, r.top);
	dc->LineTo(r.left + nBordX, r.top);
	
	dc->MoveTo(r.left, r.bottom - nBordY);
	dc->LineTo(r.left, r.bottom);
	dc->LineTo(r.left + nBordX, r.bottom);
	
	dc->MoveTo(r.right, r.top + nBordY);
	dc->LineTo(r.right, r.top);
	dc->LineTo(r.right - nBordX, r.top);
	
	dc->MoveTo(r.right, r.bottom - nBordY);
	dc->LineTo(r.right, r.bottom);
	dc->LineTo(r.right - nBordX, r.bottom);
	dc->SelectObject(&pOldPen);
}
