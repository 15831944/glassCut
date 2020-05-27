#pragma once


class COrangeListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(COrangeListCtrl)

public:
	COrangeListCtrl();
	virtual ~COrangeListCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
	virtual void PreSubclassWindow();
	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
private:
	int m_nItem;//主项
	int m_nSubItem;//子项

	CFont m_FontItem;
	int m_nRowHeight;
public:
	void SetRowHeigt(int nHeight);
};


