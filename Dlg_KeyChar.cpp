// Dlg_KeyChar.cpp : implementation file
//

#include "stdafx.h"
#include "Bender.h"
#include "Dlg_KeyChar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_KeyChar dialog


CDlg_KeyChar::CDlg_KeyChar(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_KeyChar::IDD, pParent)
{
    m_greenbrush.CreateSolidBrush(RGB(0,255,0));//绿色
    m_yollowbrush.CreateSolidBrush(RGB(0,128,128));//标准灰色
    m_redbrush.CreateSolidBrush(RGB(255,0,0));//红色
    m_bluebrush.CreateSolidBrush(RGB(0,0,255));//兰色
	//{{AFX_DATA_INIT(CDlg_KeyChar)
	m_strNew = _T("");
	m_strOld = _T("");
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
	m_bIsPsw = FALSE;
}


void CDlg_KeyChar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_KeyChar)
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_OK, m_btnOk);
	DDX_Control(pDX, IDC_BUTTON_Z, m_btnZ);
	DDX_Control(pDX, IDC_BUTTON_Y, m_btnY);
	DDX_Control(pDX, IDC_BUTTON_X, m_btnX);
	DDX_Control(pDX, IDC_BUTTON_W, m_btnW);
	DDX_Control(pDX, IDC_BUTTON_V, m_btnV);
	DDX_Control(pDX, IDC_BUTTON_U, m_btnU);
	DDX_Control(pDX, IDC_BUTTON_T, m_btnT);
	DDX_Control(pDX, IDC_BUTTON_SUB, m_btnSub);
	DDX_Control(pDX, IDC_BUTTON_SHIFTR, m_btnShiftr);
	DDX_Control(pDX, IDC_BUTTON_SHIFTL, m_btnShiftl);
	DDX_Control(pDX, IDC_BUTTON_SEMICOLON, m_btnSemicolon);
	DDX_Control(pDX, IDC_BUTTON_S, m_btnS);
	DDX_Control(pDX, IDC_BUTTON_R, m_btnR);
	DDX_Control(pDX, IDC_BUTTON_QUOTATIONMARK, m_btnQuotationMark);
	DDX_Control(pDX, IDC_BUTTON_Q, m_btnQ);
	DDX_Control(pDX, IDC_BUTTON_POINT, m_btnPoint);
	DDX_Control(pDX, IDC_BUTTON_P, m_btnP);
	DDX_Control(pDX, IDC_BUTTON_O, m_btnO);
	DDX_Control(pDX, IDC_BUTTON_N, m_btnN);
	DDX_Control(pDX, IDC_BUTTON_M, m_btnM);
	DDX_Control(pDX, IDC_BUTTON_L, m_btnL);
	DDX_Control(pDX, IDC_BUTTON_K, m_btnK);
	DDX_Control(pDX, IDC_BUTTON_J, m_btnJ);
	DDX_Control(pDX, IDC_BUTTON_INCLUDER, m_btnIncluder);
	DDX_Control(pDX, IDC_BUTTON_INCLUDEL, m_btnIncludel);
	DDX_Control(pDX, IDC_BUTTON_I, m_btnI);
	DDX_Control(pDX, IDC_BUTTON_H, m_btnH);
	DDX_Control(pDX, IDC_BUTTON_G, m_btnG);
	DDX_Control(pDX, IDC_BUTTON_F, m_btnF);
	DDX_Control(pDX, IDC_BUTTON_EQUATION, m_btnEquation);
	DDX_Control(pDX, IDC_BUTTON_ENTER, m_btnEnter);
	DDX_Control(pDX, IDC_BUTTON_E, m_btnE);
	DDX_Control(pDX, IDC_BUTTON_DIVIDE, m_btnDivide);
	DDX_Control(pDX, IDC_BUTTON_DIRECTORY, m_btnDirectory);
	DDX_Control(pDX, IDC_BUTTON_D, m_btnD);
	DDX_Control(pDX, IDC_BUTTON_COMMA, m_btnComma);
	DDX_Control(pDX, IDC_BUTTON_C, m_btnC);
	DDX_Control(pDX, IDC_BUTTON_BACKSPACE, m_btnBackspace);
	DDX_Control(pDX, IDC_BUTTON_B, m_btnB);
	DDX_Control(pDX, IDC_BUTTON_A, m_btnA);
	DDX_Control(pDX, IDC_BUTTON_9, m_btn9);
	DDX_Control(pDX, IDC_BUTTON_8, m_btn8);
	DDX_Control(pDX, IDC_BUTTON_7, m_btn7);
	DDX_Control(pDX, IDC_BUTTON_6, m_btn6);
	DDX_Control(pDX, IDC_BUTTON_5, m_btn5);
	DDX_Control(pDX, IDC_BUTTON_4, m_btn4);
	DDX_Control(pDX, IDC_BUTTON_3, m_btn3);
	DDX_Control(pDX, IDC_BUTTON_2, m_btn2);
	DDX_Control(pDX, IDC_BUTTON_1, m_btn1);
	DDX_Control(pDX, IDC_BUTTON_0, m_btn0);
	DDX_Control(pDX, IDC_EDIT_NEW, m_edtNew);
	DDX_Text(pDX, IDC_EDIT_NEW, m_strNew);
	DDX_Text(pDX, IDC_EDIT_OLD, m_strOld);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_KeyChar, CDialog)
	//{{AFX_MSG_MAP(CDlg_KeyChar)
	ON_BN_CLICKED(IDC_BUTTON_1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON_0, OnButton0)
	ON_BN_CLICKED(IDC_BUTTON_SUB, OnButtonSub)
	ON_BN_CLICKED(IDC_BUTTON_EQUATION, OnButtonEquation)
	ON_BN_CLICKED(IDC_BUTTON_BACKSPACE, OnButtonBackspace)
	ON_BN_CLICKED(IDC_BUTTON_Q, OnButtonQ)
	ON_BN_CLICKED(IDC_BUTTON_W, OnButtonW)
	ON_BN_CLICKED(IDC_BUTTON_E, OnButtonE)
	ON_BN_CLICKED(IDC_BUTTON_R, OnButtonR)
	ON_BN_CLICKED(IDC_BUTTON_T, OnButtonT)
	ON_BN_CLICKED(IDC_BUTTON_Y, OnButtonY)
	ON_BN_CLICKED(IDC_BUTTON_U, OnButtonU)
	ON_BN_CLICKED(IDC_BUTTON_I, OnButtonI)
	ON_BN_CLICKED(IDC_BUTTON_O, OnButtonO)
	ON_BN_CLICKED(IDC_BUTTON_P, OnButtonP)
	ON_BN_CLICKED(IDC_BUTTON_INCLUDEL, OnButtonIncludel)
	ON_BN_CLICKED(IDC_BUTTON_INCLUDER, OnButtonIncluder)
	ON_BN_CLICKED(IDC_BUTTON_DIRECTORY, OnButtonDirectory)
	ON_BN_CLICKED(IDC_BUTTON_A, OnButtonA)
	ON_BN_CLICKED(IDC_BUTTON_S, OnButtonS)
	ON_BN_CLICKED(IDC_BUTTON_D, OnButtonD)
	ON_BN_CLICKED(IDC_BUTTON_F, OnButtonF)
	ON_BN_CLICKED(IDC_BUTTON_G, OnButtonG)
	ON_BN_CLICKED(IDC_BUTTON_H, OnButtonH)
	ON_BN_CLICKED(IDC_BUTTON_J, OnButtonJ)
	ON_BN_CLICKED(IDC_BUTTON_K, OnButtonK)
	ON_BN_CLICKED(IDC_BUTTON_L, OnButtonL)
	ON_BN_CLICKED(IDC_BUTTON_SEMICOLON, OnButtonSemicolon)
	ON_BN_CLICKED(IDC_BUTTON_QUOTATIONMARK, OnButtonQuotationmark)
	ON_BN_CLICKED(IDC_BUTTON_ENTER, OnButtonEnter)
	ON_BN_CLICKED(IDC_BUTTON_SHIFTL, OnButtonShiftl)
	ON_BN_CLICKED(IDC_BUTTON_SHIFTR, OnButtonShiftr)
	ON_BN_CLICKED(IDC_BUTTON_Z, OnButtonZ)
	ON_BN_CLICKED(IDC_BUTTON_X, OnButtonX)
	ON_BN_CLICKED(IDC_BUTTON_C, OnButtonC)
	ON_BN_CLICKED(IDC_BUTTON_V, OnButtonV)
	ON_BN_CLICKED(IDC_BUTTON_B, OnButtonB)
	ON_BN_CLICKED(IDC_BUTTON_N, OnButtonN)
	ON_BN_CLICKED(IDC_BUTTON_M, OnButtonM)
	ON_BN_CLICKED(IDC_BUTTON_COMMA, OnButtonComma)
	ON_BN_CLICKED(IDC_BUTTON_POINT, OnButtonPoint)
	ON_BN_CLICKED(IDC_BUTTON_DIVIDE, OnButtonDivide)
	ON_BN_CLICKED(IDC_OK, OnOk)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_KeyChar message handlers

void CDlg_KeyChar::OnButton1() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X31,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X21,0);
}

void CDlg_KeyChar::OnButton2() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X32,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X40,0);
}

void CDlg_KeyChar::OnButton3() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X33,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X23,0);
}

void CDlg_KeyChar::OnButton4() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X34,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X24,0);
}

void CDlg_KeyChar::OnButton5() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X35,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X25,0);
}

void CDlg_KeyChar::OnButton6() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X36,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X5E,0);
}

void CDlg_KeyChar::OnButton7() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X37,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X26,0);
}

void CDlg_KeyChar::OnButton8() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X38,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X2A,0);
}

void CDlg_KeyChar::OnButton9() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X39,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X28,0);
}

void CDlg_KeyChar::OnButton0() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X30,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X29,0);
}

void CDlg_KeyChar::OnButtonSub() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X2D,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X5F,0);
}

void CDlg_KeyChar::OnButtonEquation() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X3D,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X2B,0);
}

void CDlg_KeyChar::OnButtonBackspace() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,VK_BACK,0);
	else		m_edtNew.SendMessage(WM_CHAR,VK_BACK,0);
}

void CDlg_KeyChar::OnButtonQ() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X51,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X71,0);
}

void CDlg_KeyChar::OnButtonW() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X57,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X77,0);
}

void CDlg_KeyChar::OnButtonE() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X45,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X65,0);
}

void CDlg_KeyChar::OnButtonR() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X52,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X72,0);
}

void CDlg_KeyChar::OnButtonT() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X54,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X74,0);
}

void CDlg_KeyChar::OnButtonY() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X59,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X79,0);
}

void CDlg_KeyChar::OnButtonU() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X55,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X75,0);
}

void CDlg_KeyChar::OnButtonI() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X49,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X69,0);
}

void CDlg_KeyChar::OnButtonO() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X4F,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X6F,0);
}

void CDlg_KeyChar::OnButtonP() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X50,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X70,0);
}

void CDlg_KeyChar::OnButtonIncludel() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X5B,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X7B,0);
}

void CDlg_KeyChar::OnButtonIncluder() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X5D,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X7D,0);
}

void CDlg_KeyChar::OnButtonDirectory() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X5C,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X7C,0);
}

void CDlg_KeyChar::OnButtonA() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X41,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X61,0);
}

void CDlg_KeyChar::OnButtonS() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X53,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X73,0);
}

void CDlg_KeyChar::OnButtonD() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X44,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X64,0);
}

void CDlg_KeyChar::OnButtonF() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X46,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X66,0);
}

void CDlg_KeyChar::OnButtonG() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X47,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X67,0);
}

void CDlg_KeyChar::OnButtonH() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X48,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X68,0);
}

void CDlg_KeyChar::OnButtonJ() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X4A,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X6A,0);
}

void CDlg_KeyChar::OnButtonK() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X4B,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X6B,0);
}

void CDlg_KeyChar::OnButtonL() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X4C,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X6C,0);
}

void CDlg_KeyChar::OnButtonSemicolon() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X3B,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X3A,0);
}

void CDlg_KeyChar::OnButtonQuotationmark() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X27,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X22,0);
}

void CDlg_KeyChar::OnButtonEnter() 
{
	CDialog::OnOK();
/*
	m_edtNew.SetFocus();
	m_edtNew.SendMessage(WM_CHAR,VK_RETURN,0);
*/
}

void CDlg_KeyChar::OnButtonShiftl() 
{
	m_edtNew.SetFocus();
	if(!iPage)
	{
		iPage = 1;
		SetDlgItemText(IDC_BUTTON_1,"!");				SetDlgItemText(IDC_BUTTON_2,"@");
		SetDlgItemText(IDC_BUTTON_3,"#");				SetDlgItemText(IDC_BUTTON_4,"$");
		SetDlgItemText(IDC_BUTTON_5,"%");				SetDlgItemText(IDC_BUTTON_6,"^");
		SetDlgItemText(IDC_BUTTON_7,"&&");				SetDlgItemText(IDC_BUTTON_8,"*");
		SetDlgItemText(IDC_BUTTON_9,"(");				SetDlgItemText(IDC_BUTTON_0,")");
		SetDlgItemText(IDC_BUTTON_SUB,"_");				SetDlgItemText(IDC_BUTTON_EQUATION,"+");
		SetDlgItemText(IDC_BUTTON_Q,"q");				SetDlgItemText(IDC_BUTTON_W,"w");
		SetDlgItemText(IDC_BUTTON_E,"e");				SetDlgItemText(IDC_BUTTON_R,"r");
		SetDlgItemText(IDC_BUTTON_T,"t");				SetDlgItemText(IDC_BUTTON_Y,"y");
		SetDlgItemText(IDC_BUTTON_U,"u");				SetDlgItemText(IDC_BUTTON_I,"i");
		SetDlgItemText(IDC_BUTTON_O,"o");				SetDlgItemText(IDC_BUTTON_P,"p");
		SetDlgItemText(IDC_BUTTON_INCLUDEL,"{");		SetDlgItemText(IDC_BUTTON_INCLUDER,"}");
		SetDlgItemText(IDC_BUTTON_DIRECTORY,"|");		SetDlgItemText(IDC_BUTTON_A,"a");
		SetDlgItemText(IDC_BUTTON_S,"s");				SetDlgItemText(IDC_BUTTON_D,"d");
		SetDlgItemText(IDC_BUTTON_F,"f");				SetDlgItemText(IDC_BUTTON_G,"g");
		SetDlgItemText(IDC_BUTTON_H,"h");				SetDlgItemText(IDC_BUTTON_J,"j");
		SetDlgItemText(IDC_BUTTON_K,"k");				SetDlgItemText(IDC_BUTTON_L,"l");
		SetDlgItemText(IDC_BUTTON_SEMICOLON,":");		SetDlgItemText(IDC_BUTTON_QUOTATIONMARK,"\"");
		SetDlgItemText(IDC_BUTTON_Z,"z");				SetDlgItemText(IDC_BUTTON_X,"x");
		SetDlgItemText(IDC_BUTTON_C,"c");				SetDlgItemText(IDC_BUTTON_V,"v");
		SetDlgItemText(IDC_BUTTON_B,"b");				SetDlgItemText(IDC_BUTTON_N,"n");
		SetDlgItemText(IDC_BUTTON_M,"m");				SetDlgItemText(IDC_BUTTON_COMMA,"<");
		SetDlgItemText(IDC_BUTTON_POINT,">");			SetDlgItemText(IDC_BUTTON_DIVIDE,"?");
	}
	else
	{
		iPage = 0;
		SetDlgItemText(IDC_BUTTON_1,"1");				SetDlgItemText(IDC_BUTTON_2,"2");
		SetDlgItemText(IDC_BUTTON_3,"3");				SetDlgItemText(IDC_BUTTON_4,"4");
		SetDlgItemText(IDC_BUTTON_5,"5");				SetDlgItemText(IDC_BUTTON_6,"6");
		SetDlgItemText(IDC_BUTTON_7,"7");				SetDlgItemText(IDC_BUTTON_8,"8");
		SetDlgItemText(IDC_BUTTON_9,"9");				SetDlgItemText(IDC_BUTTON_0,"0");
		SetDlgItemText(IDC_BUTTON_SUB,"-");				SetDlgItemText(IDC_BUTTON_EQUATION,"=");
		SetDlgItemText(IDC_BUTTON_Q,"Q");				SetDlgItemText(IDC_BUTTON_W,"W");
		SetDlgItemText(IDC_BUTTON_E,"E");				SetDlgItemText(IDC_BUTTON_R,"R");
		SetDlgItemText(IDC_BUTTON_T,"T");				SetDlgItemText(IDC_BUTTON_Y,"Y");
		SetDlgItemText(IDC_BUTTON_U,"U");				SetDlgItemText(IDC_BUTTON_I,"I");
		SetDlgItemText(IDC_BUTTON_O,"O");				SetDlgItemText(IDC_BUTTON_P,"P");
		SetDlgItemText(IDC_BUTTON_INCLUDEL,"[");		SetDlgItemText(IDC_BUTTON_INCLUDER,"]");
		SetDlgItemText(IDC_BUTTON_DIRECTORY,"\\");		SetDlgItemText(IDC_BUTTON_A,"A");
		SetDlgItemText(IDC_BUTTON_S,"S");				SetDlgItemText(IDC_BUTTON_D,"D");
		SetDlgItemText(IDC_BUTTON_F,"F");				SetDlgItemText(IDC_BUTTON_G,"G");
		SetDlgItemText(IDC_BUTTON_H,"H");				SetDlgItemText(IDC_BUTTON_J,"J");
		SetDlgItemText(IDC_BUTTON_K,"K");				SetDlgItemText(IDC_BUTTON_L,"L");
		SetDlgItemText(IDC_BUTTON_SEMICOLON,";");		SetDlgItemText(IDC_BUTTON_QUOTATIONMARK,"'");
		SetDlgItemText(IDC_BUTTON_Z,"Z");				SetDlgItemText(IDC_BUTTON_X,"X");
		SetDlgItemText(IDC_BUTTON_C,"C");				SetDlgItemText(IDC_BUTTON_V,"V");
		SetDlgItemText(IDC_BUTTON_B,"B");				SetDlgItemText(IDC_BUTTON_N,"N");
		SetDlgItemText(IDC_BUTTON_M,"M");				SetDlgItemText(IDC_BUTTON_COMMA,",");
		SetDlgItemText(IDC_BUTTON_POINT,".");			SetDlgItemText(IDC_BUTTON_DIVIDE,"/");
	}
}

void CDlg_KeyChar::OnButtonShiftr() 
{
	m_edtNew.SetFocus();
	OnButtonShiftl();
}

void CDlg_KeyChar::OnButtonZ() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X5A,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X7A,0);
}

void CDlg_KeyChar::OnButtonX() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X58,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X78,0);
}

void CDlg_KeyChar::OnButtonC() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X43,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X63,0);
}

void CDlg_KeyChar::OnButtonV() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X56,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X76,0);
}

void CDlg_KeyChar::OnButtonB() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X42,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X62,0);
}

void CDlg_KeyChar::OnButtonN() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X4E,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X6E,0);
}

void CDlg_KeyChar::OnButtonM() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X4D,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X6D,0);
}

void CDlg_KeyChar::OnButtonComma() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X2C,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X3C,0);
}

void CDlg_KeyChar::OnButtonPoint() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X2E,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X3E,0);
}

void CDlg_KeyChar::OnButtonDivide() 
{
	m_edtNew.SetFocus();
	if(!iPage)	m_edtNew.SendMessage(WM_CHAR,0X2F,0);
	else		m_edtNew.SendMessage(WM_CHAR,0X3F,0);
}

void CDlg_KeyChar::OnCancel() 
{
	CDialog::OnCancel();
}

void CDlg_KeyChar::OnOk() 
{
	CDialog::OnOK();
}

BOOL CDlg_KeyChar::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	iPage = 0;
	OnButtonFont();
	OnLanguage();	
	m_btnCancel.SetColour(RGB(255,0,0),RGB(255,255,0));
	m_btnOk.SetColour(RGB(0,255,0),RGB(255,255,0));
	m_btnZ.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnY.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnX.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnW.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnV.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnU.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnT.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnSub.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnShiftr.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnShiftl.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnSemicolon.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnS.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnR.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnQuotationMark.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnQ.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnPoint.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnP.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnO.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnN.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnM.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnL.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnK.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnJ.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnIncluder.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnIncludel.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnI.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnH.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnG.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnF.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnEquation.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnEnter.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnE.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnDivide.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnDirectory.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnD.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnComma.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnC.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnBackspace.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnB.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btnA.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn9.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn8.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn7.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn6.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn5.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn4.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn3.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn2.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn1.SetColour(RGB(0,0,0),RGB(255,255,0));
	m_btn0.SetColour(RGB(0,0,0),RGB(255,255,0));
	
	if( m_bIsPsw)
	{
		CEdit *pEdit = (CEdit*)GetDlgItem(IDC_EDIT_NEW);
		pEdit->SetPasswordChar('*');
		pEdit->ModifyStyle(NULL,ES_PASSWORD);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CDlg_KeyChar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (nCtlColor==CTLCOLOR_DLG||nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(255,255,128));//色
		pDC->SetBkColor(RGB(0,128,128));//黄色
		return (HBRUSH)m_yollowbrush.GetSafeHandle();
	}
	return hbr;
}

void CDlg_KeyChar::OnButtonFont() /* 改变窗口字体 */
{
	m_btn0.SetFont(&g_fontKey);
	m_btn1.SetFont(&g_fontKey);
	m_btn2.SetFont(&g_fontKey);
	m_btn3.SetFont(&g_fontKey);
	m_btn4.SetFont(&g_fontKey);
	m_btn5.SetFont(&g_fontKey);
	m_btn6.SetFont(&g_fontKey);
	m_btn7.SetFont(&g_fontKey);
	m_btn8.SetFont(&g_fontKey);
	m_btn9.SetFont(&g_fontKey);
	m_btnZ.SetFont(&g_fontKey);
	m_btnY.SetFont(&g_fontKey);
	m_btnX.SetFont(&g_fontKey);
	m_btnW.SetFont(&g_fontKey);
	m_btnV.SetFont(&g_fontKey);
	m_btnU.SetFont(&g_fontKey);
	m_btnT.SetFont(&g_fontKey);
	m_btnSub.SetFont(&g_fontKey);
	m_btnShiftr.SetFont(&g_fontKey);
	m_btnShiftl.SetFont(&g_fontKey);
	m_btnSemicolon.SetFont(&g_fontKey);
	m_btnS.SetFont(&g_fontKey);
	m_btnR.SetFont(&g_fontKey);
	m_btnQuotationMark.SetFont(&g_fontKey);
	m_btnQ.SetFont(&g_fontKey);
	m_btnPoint.SetFont(&g_fontKey);
	m_btnP.SetFont(&g_fontKey);
	m_btnO.SetFont(&g_fontKey);
	m_btnN.SetFont(&g_fontKey);
	m_btnM.SetFont(&g_fontKey);
	m_btnL.SetFont(&g_fontKey);
	m_btnK.SetFont(&g_fontKey);
	m_btnJ.SetFont(&g_fontKey);
	m_btnIncluder.SetFont(&g_fontKey);
	m_btnIncludel.SetFont(&g_fontKey);
	m_btnI.SetFont(&g_fontKey);
	m_btnH.SetFont(&g_fontKey);
	m_btnG.SetFont(&g_fontKey);
	m_btnF.SetFont(&g_fontKey);
	m_btnEquation.SetFont(&g_fontKey);
	m_btnEnter.SetFont(&g_fontKey);
	m_btnE.SetFont(&g_fontKey);
	m_btnDivide.SetFont(&g_fontKey);
	m_btnDirectory.SetFont(&g_fontKey);
	m_btnD.SetFont(&g_fontKey);
	m_btnComma.SetFont(&g_fontKey);
	m_btnC.SetFont(&g_fontKey);
	m_btnBackspace.SetFont(&g_fontKey);
	m_btnB.SetFont(&g_fontKey);
	m_btnA.SetFont(&g_fontKey);
	m_btnCancel.SetFont(&g_fontButton);
	m_btnOk.SetFont(&g_fontButton);
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_NEW)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_STATIC_OLD)->SetFont(&g_fontStatic);
	GetDlgItem(IDC_EDIT_NEW)->SetFont(&g_fontEdit);
	GetDlgItem(IDC_EDIT_OLD)->SetFont(&g_fontEdit);
}

void CDlg_KeyChar::OnLanguage()
{
	int   i;
	int		nIndex;
	nIndex = g_iLanguage + 1;
	for(i=0;i<AR_CNC;i++)
		CWnd::SetDlgItemText(atoi(g_arr_strCnc[i][0]),g_arr_strCnc[i][nIndex]);
}
