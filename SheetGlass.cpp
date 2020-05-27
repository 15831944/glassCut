// SheetGlass.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_SheetGlass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSheetGlass dialog


CDlg_SheetGlass::CDlg_SheetGlass(CWnd* pParent /*=NULL*/)
	: CDialog(CSheetGlass::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSheetGlass)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlg_SheetGlass::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSheetGlass)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_SheetGlass, CDialog)
	//{{AFX_MSG_MAP(CDlg_SheetGlass)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSheetGlass message handlers
void CDlg_SheetGlass::OnInitGrid()
{

}
