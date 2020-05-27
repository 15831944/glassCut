#if !defined(AFX_DISPLAYCTRL_H__B2C43726_9A4B_40C5_BC97_4E2A28CC5ADE__INCLUDED_)
#define AFX_DISPLAYCTRL_H__B2C43726_9A4B_40C5_BC97_4E2A28CC5ADE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class COleFont;

/////////////////////////////////////////////////////////////////////////////
// CDisplayCtrl wrapper class

class CDisplayCtrl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CDisplayCtrl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x81b9117e, 0x72b5, 0x4de3, { 0x96, 0x3b, 0xa, 0x3f, 0x5b, 0x6, 0xf6, 0x6b } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:
	long GetDisplayCount();
	void SetDisplayCount(long);
	long GetDisplayData();
	void SetDisplayData(long);
	COleFont GetFont();
	void SetFont(LPDISPATCH);
	short GetBorderStyle();
	void SetBorderStyle(short);
	short GetAppearance();
	void SetAppearance(short);
	OLE_COLOR GetForeColor();
	void SetForeColor(OLE_COLOR);
	BOOL GetShapeCircle();
	void SetShapeCircle(BOOL);
	OLE_COLOR GetBackColor();
	void SetBackColor(OLE_COLOR);
	BOOL GetCouldSelect();
	void SetCouldSelect(BOOL);
	unsigned long GetTextColor();
	void SetTextColor(unsigned long);

// Operations
public:
	void SetDisplayName(long nIndex, LPCTSTR strName);
	short GetDbClickNum();
	void MoveNext();
	void MovePrior();
	void ShowPrefix(BOOL bShow);
	void AboutBox();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYCTRL_H__B2C43726_9A4B_40C5_BC97_4E2A28CC5ADE__INCLUDED_)
