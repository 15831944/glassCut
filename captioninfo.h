#if !defined(AFX_CAPTIONINFO_H__37770714_420C_4FF8_9A4F_F42A6D2B7FDD__INCLUDED_)
#define AFX_CAPTIONINFO_H__37770714_420C_4FF8_9A4F_F42A6D2B7FDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class COleFont;

/////////////////////////////////////////////////////////////////////////////
// CCaptionInfo wrapper class

class CCaptionInfo : public CWnd
{
protected:
	DECLARE_DYNCREATE(CCaptionInfo)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x8c236c62, 0x832c, 0x441e, { 0xba, 0x96, 0x9f, 0xdb, 0x8, 0xc, 0x5, 0x9e } };
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
	short GetAppearance();
	void SetAppearance(short);
	OLE_COLOR GetBackColor();
	void SetBackColor(OLE_COLOR);
	short GetBorderStyle();
	void SetBorderStyle(short);
	CString GetCaption();
	void SetCaption(LPCTSTR);
	COleFont GetFont();
	void SetFont(LPDISPATCH);
	OLE_COLOR GetForeColor();
	void SetForeColor(OLE_COLOR);
	long GetAlign();
	void SetAlign(long);
	long GetStyle();
	void SetStyle(long);
	long GetDistance();
	void SetDistance(long);
	BOOL GetBackgroudStyle();
	void SetBackgroudStyle(BOOL);
	CString GetBmpPathName();
	void SetBmpPathName(LPCTSTR);

// Operations
public:
	void AboutBox();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAPTIONINFO_H__37770714_420C_4FF8_9A4F_F42A6D2B7FDD__INCLUDED_)
