#if !defined(AFX_BTNCTL_H__7036740C_DD7E_41B7_B818_825F3B76DB35__INCLUDED_)
#define AFX_BTNCTL_H__7036740C_DD7E_41B7_B818_825F3B76DB35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class COleFont;
class CPicture;

/////////////////////////////////////////////////////////////////////////////
// CBtnCtl wrapper class

class CBtnCtl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CBtnCtl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xc06ea015, 0xe48a, 0x4ff2, { 0x88, 0x62, 0x28, 0x92, 0x5c, 0x24, 0x8b, 0x46 } };
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
	OLE_COLOR GetBackColor();
	void SetBackColor(OLE_COLOR);
	CString GetCaption();
	void SetCaption(LPCTSTR);
	short GetBorderStyle();
	void SetBorderStyle(short);
	OLE_COLOR GetForeColor();
	void SetForeColor(OLE_COLOR);
	COleFont GetFont();
	void SetFont(LPDISPATCH);
	long GetAlign();
	void SetAlign(long);
	BOOL GetBackgroundStyle();
	void SetBackgroundStyle(BOOL);
	CPicture GetBmpNormal();
	void SetBmpNormal(LPDISPATCH);
	CPicture GetBmpFocus();
	void SetBmpFocus(LPDISPATCH);
	CPicture GetBmpHot();
	void SetBmpHot(LPDISPATCH);
	CPicture GetBmpDisable();
	void SetBmpDisable(LPDISPATCH);
	BOOL GetBorderShape();
	void SetBorderShape(BOOL);
	CString GetTipMsg();
	void SetTipMsg(LPCTSTR);

// Operations
public:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BTNCTL_H__7036740C_DD7E_41B7_B818_825F3B76DB35__INCLUDED_)
