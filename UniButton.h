//Download by http://www.NewXing.com
#if !defined(AFX_UNIBUTTON_H__EBEB2EA0_A067_11D2_9E44_0020182F735A__INCLUDED_)
#define AFX_UNIBUTTON_H__EBEB2EA0_A067_11D2_9E44_0020182F735A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// CUniButton window
//
// AUTHOR: Pavel A .Simakov
// DATE: 981226
// E-MAIL: psimakov@outplay.com
// ORGANIZATION: Outplay Consulting
// HTTP: www.outplay.com
// TERM OF USE: unlimited, must cite AUTHOR
// COPYRIHT: 1998 Outplay Consulting
//
/////////////////////////////////////////////////////////////////////////////

class CUniButton : public CButton
{
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUniButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CUniButton)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int m_nPress;
	UINT m_nBorder;														// width of the border in pixels for 3D highlight
	LONG m_lfEscapement;												// orientation of the caption (in tenth of the degree as in LOGFONT)
	COLORREF m_nColor, m_sColor, m_hColor, m_dColor;					// background colors for button states: normal, selected, hover, disabled
	CBitmap *m_pNormal;												// bitmaps to hold button images
	CBitmap *m_pSelected;
	CBitmap *m_pHover;
	CBitmap *m_pDisabled;
	CPoint m_CenterPoint;												// button caption will be centered around this point
	BOOL m_bMouseDown;													// indicated that mouse is pressed down
	BOOL m_bHover;														// indicates if mouse is over the button
	BOOL m_bCapture;													// indicates that mouse is captured in the buton
	HRGN m_hRgn;														// region in screen coordinates
	BOOL m_bNeedBitmaps;												// flag idicates that state bitmaps must be rebuild
	UINT m_nUpBitMap,m_nDownBitMap,m_nSelection;
    CFont *m_pFont;
    int  m_nHaveOnly;                                                   //只有背景
	void DrawButton(CDC * pDC, CRect * pRect, UINT state);				// draws button to the screen
	void PrepareStateBitmaps(CDC * pDC, CRect * pRect);					// prepares bitmaps for button states
	BOOL HitTest(CPoint point);											// determines if point is inside the button region
	void CheckHover(CPoint point);
protected:
	void PrepareNormalState(CDC * pDC, CDC * pMemDC, CRect * pRect);	// prepare normal state button bitmap
	void PrepareSelectedState(CDC * pDC, CDC * pMemDC, CRect * pRect);	// prepare selectedstate button bitmap
	void PrepareHoverState(CDC * pDC, CDC * pMemDC, CRect * pRect);		// prepare hover state button bitmap
	void PrepareDisabledState(CDC * pDC, CDC * pMemDC, CRect * pRect);	// prepare disabled state button bitmap
	void DrawButtonCaption(HDC hDC, CRect * pRect, BOOL bEnabled, BOOL bSunken);	// draws button caption 
	void PaintRgn(CDC * pDC, CDC * pMemDC, CBitmap * pBitmap, COLORREF color, CRect * pRect, BOOL bEnabled, BOOL bSunken);	// paint button 
public:
	CUniButton();				// constructor
	virtual ~CUniButton();	// destructor
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const CPoint point, const HRGN hRgn, CWnd* pParentWnd, UINT nID);
							// constructor with default colors and border
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const CPoint point, const HRGN hRgn, CWnd* pParentWnd, UINT nID, COLORREF color);	
							// constructor with hover & selected color specified
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const CPoint point, const HRGN hRgn, CWnd* pParentWnd, UINT nID, UINT nBorder, COLORREF nColor, COLORREF sColor, COLORREF hColor, COLORREF dColor);	
							// complex parameters constructor
								// lpszCaption - window caption
								// dwStyle - window styles
								// point - position of the button on the parent window (in parent coordinates)
								// hRgn - handle to region which represents the button (in button client coordinates)
								// pParentWnd - handle to parent window
								// nID - control Id
								// nBorder - specifies width of the border in pixels for 3D highlight (allowed values are 1, 2)
								// nColor - normal color 
								// sColor - selected color
								// hColor - hover color
								// dColor - disabled color
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const CPoint point, const HRGN hRgn, CWnd* pParentWnd, UINT nID, UINT nBorder, LONG lfEscapement, COLORREF nColor, COLORREF sColor, COLORREF hColor, COLORREF dColor);

	void SetBitMapID(int nUpBitMap,int nDownBitMap);
	void SetFont(CFont *font);
	void HaveBitmap(int nHave);//1没有图标
	void RepeatDraw();
	void SelectState(UINT nID);
	// variation of above
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNIBUTTON_H__EBEB2EA0_A067_11D2_9E44_0020182F735A__INCLUDED_)
