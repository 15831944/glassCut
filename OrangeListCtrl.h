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
	int m_nItem;//����
	int m_nSubItem;//����

	CFont m_FontItem;
	int m_nRowHeight;
public:
	void SetRowHeigt(int nHeight);
};


