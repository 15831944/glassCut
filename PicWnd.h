#if !defined(AFX_PICWND_H__6CEFE403_4DFA_4092_B274_1ED30E4A3F10__INCLUDED_)
#define AFX_PICWND_H__6CEFE403_4DFA_4092_B274_1ED30E4A3F10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PicWnd.h : header file
//

#define BK_CORLOR	RGB(255,255,255)

enum picwnd_msg
{
	PICWND_LBUTTONDOWN=0,
	PICWND_LBUTTONDBCLK,
	PICWND_RBUTTONDOWN,
};

enum graph_type
{
	GTYPE_NONE=0,
	GTYPE_CIRCLE,
	GTYPE_TRIANGLE,
	GTYPE_RECTANGLE,
	GTYPE_PENTAGON,
	GTYPE_HEXAGON,
	GTYPE_YIXING_1,
	GTYPE_YIXING_2,
	GTYPE_YIXING_3,
	GTYPE_DXF,
	N_TOTAL_GTYPEs,
};

typedef struct tagPictureAttribute
{
	UINT nPicType;
	UINT nIndex;
	char szPicName[64];
	char szFilePath[MAX_PATH];
} PIC_ATTR;

/////////////////////////////////////////////////////////////////////////////
// CPicWnd window

class CPicWnd : public CWnd
{
// Construction
public:
	CPicWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPicWnd)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT GetPicType();
	const PIC_ATTR* GetPicAttribute();
	UINT GetWndIndex();
	BOOL LoadBmpFile(PIC_ATTR &attr);
	void SetWndFocus(BOOL bFocus);
	void Clean(BOOL bInvalidate);
	void SetWndIndex(UINT nIndex);
	virtual ~CPicWnd();

	// Generated message map functions
protected:
	PIC_ATTR m_picAttr;
	void ReleaseResource();
	BITMAPINFO *m_bi;
	BYTE *m_bits;
	void RefreshImage();
	BOOL m_bFocus;
	CDC m_mDC;
	UINT m_nIndex;
	//{{AFX_MSG(CPicWnd)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICWND_H__6CEFE403_4DFA_4092_B274_1ED30E4A3F10__INCLUDED_)
