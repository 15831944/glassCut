// dlg_galil.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "dlg_galil.h"
#include "Dlg_KeyNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// dlg_galil dialog


dlg_galil::dlg_galil(CWnd* pParent /*=NULL*/)
	: CDialog(dlg_galil::IDD, pParent)
{
	//{{AFX_DATA_INIT(dlg_galil)
	//}}AFX_DATA_INIT
}


void dlg_galil::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dlg_galil)
	DDX_Control(pDX, IDC_EDIT_KSE, m_edtKSE);
	DDX_Control(pDX, IDC_EDIT_KPE, m_edtKPE);
	DDX_Control(pDX, IDC_EDIT_KIE, m_edtKIE);
	DDX_Control(pDX, IDC_EDIT_KDE, m_edtKDE);
	DDX_Control(pDX, IDC_COMBO_OEE, m_oee);
	DDX_Control(pDX, IDC_COMBO_MTE, m_mte);
	DDX_Control(pDX, IDC_COMBO_MOE, m_moe);
	DDX_Control(pDX, IDC_COMBO_CEE, m_cee);
	DDX_Control(pDX, IDC_COMBO_CE2E, m_ce2e);
	DDX_Control(pDX, IDC_EDIT_KSZ, m_edtKSZ);
	DDX_Control(pDX, IDC_EDIT_KSY, m_edtKSY);
	DDX_Control(pDX, IDC_EDIT_KSX, m_edtKSX);
	DDX_Control(pDX, IDC_EDIT_KSW, m_edtKSW);
	DDX_Control(pDX, IDC_EDIT_KPZ, m_edtKPZ);
	DDX_Control(pDX, IDC_EDIT_KPY, m_edtKPY);
	DDX_Control(pDX, IDC_EDIT_KPX, m_edtKPX);
	DDX_Control(pDX, IDC_EDIT_KPW, m_edtKPW);
	DDX_Control(pDX, IDC_EDIT_KIZ, m_edtKIZ);
	DDX_Control(pDX, IDC_EDIT_KIY, m_edtKIY);
	DDX_Control(pDX, IDC_EDIT_KIX, m_edtKIX);
	DDX_Control(pDX, IDC_EDIT_KIW, m_edtKIW);
	DDX_Control(pDX, IDC_EDIT_KDZ, m_edtKDZ);
	DDX_Control(pDX, IDC_EDIT_KDY, m_edtKDY);
	DDX_Control(pDX, IDC_EDIT_KDX, m_edtKDX);
	DDX_Control(pDX, IDC_EDIT_KDW, m_edtKDW);
	DDX_Control(pDX, IDC_COMBO_MOZ, m_moz);
	DDX_Control(pDX, IDC_COMBO_MOY, m_moy);
	DDX_Control(pDX, IDC_COMBO_MOX, m_mox);
	DDX_Control(pDX, IDC_COMBO_MOW, m_mow);
	DDX_Control(pDX, IDC_COMBO_OEZ, m_oez);
	DDX_Control(pDX, IDC_COMBO_OEY, m_oey);
	DDX_Control(pDX, IDC_COMBO_OEX, m_oex);
	DDX_Control(pDX, IDC_COMBO_OEW, m_oew);
	DDX_Control(pDX, IDC_COMBO_MTZ, m_mtz);
	DDX_Control(pDX, IDC_COMBO_MTY, m_mty);
	DDX_Control(pDX, IDC_COMBO_MTX, m_mtx);
	DDX_Control(pDX, IDC_COMBO_MTW, m_mtw);
	DDX_Control(pDX, IDC_COMBO_CE2Z, m_ce2z);
	DDX_Control(pDX, IDC_COMBO_CE2Y, m_ce2y);
	DDX_Control(pDX, IDC_COMBO_CE2X, m_ce2x);
	DDX_Control(pDX, IDC_COMBO_CE2W, m_ce2w);
	DDX_Control(pDX, IDC_COMBO_CEZ, m_cez);
	DDX_Control(pDX, IDC_COMBO_CEY, m_cey);
	DDX_Control(pDX, IDC_COMBO_CEX, m_cex);
	DDX_Control(pDX, IDC_COMBO_CEW, m_cew);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dlg_galil, CDialog)
	//{{AFX_MSG_MAP(dlg_galil)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_MESSAGE(WM_EDITDOUBLE,OnEditDouble)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dlg_galil message handlers

BOOL dlg_galil::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetCtlFont(this);
    OnLanguage();
	InitButton();
	SetWindowPos(CWnd::GetOwner(),0,0,g_screen.x,g_screen.y,SWP_SHOWWINDOW);
	


	g_systemdll.GetSysinfo();							/* �忨����ϵͳ���ӿ�,��ð忨��Ϣ */
	g_stu_pSysA = g_systemdll.GetGalilPointAxis(1);			/* ��ȡ���������Ϣָ�� */
	g_stu_pSysB = g_systemdll.GetGalilPointAxis(2);
	g_stu_pSysC = g_systemdll.GetGalilPointAxis(3);
	g_stu_pSysD = g_systemdll.GetGalilPointAxis(4);
	/* ����ͬ����ʽ�趨 */
	if(g_stu_pAxisF->bSpareA==FALSE)
	{
		m_edtKSE.EnableWindow(FALSE);
		m_edtKPE.EnableWindow(FALSE);
		m_edtKIE.EnableWindow(FALSE);
		m_edtKDE.EnableWindow(FALSE);
		m_oee.EnableWindow(FALSE);
		m_mte.EnableWindow(FALSE);
		m_moe.EnableWindow(FALSE);
		m_cee.EnableWindow(FALSE);
		m_ce2e.EnableWindow(FALSE);
	}
	
//*****************************************************************

	CString      strTemp;
	if(!g_lRc)	{	if(g_stu_pSysA->l_MotorType==1)            m_mtx.SetCurSel(0);
		else if(g_stu_pSysA->l_MotorType==-1)              m_mtx.SetCurSel(1);
		else if(g_stu_pSysA->l_MotorType==-2)              m_mtx.SetCurSel(2);
		else if(g_stu_pSysA->l_MotorType==2)               m_mtx.SetCurSel(3);
		else if(g_stu_pSysA->l_MotorType==-2.5)            m_mtx.SetCurSel(4);
		else if(g_stu_pSysA->l_MotorType==2.5)             m_mtx.SetCurSel(5);
		else                        m_mtx.SetCurSel(0);}
	if(!g_lRc)	{	if(g_stu_pSysB->l_MotorType==1)            m_mty.SetCurSel(0);
		else if(g_stu_pSysB->l_MotorType==-1)              m_mty.SetCurSel(1);
		else if(g_stu_pSysB->l_MotorType==-2)              m_mty.SetCurSel(2);
		else if(g_stu_pSysB->l_MotorType==2)               m_mty.SetCurSel(3);
		else if(g_stu_pSysB->l_MotorType==-2.5)            m_mty.SetCurSel(4);
		else if(g_stu_pSysB->l_MotorType==2.5)             m_mty.SetCurSel(5);
		else                        m_mty.SetCurSel(0);}
	if(!g_lRc)	{	if(g_stu_pSysC->l_MotorType==1)            m_mtz.SetCurSel(0);
		else if(g_stu_pSysC->l_MotorType==-1)              m_mtz.SetCurSel(1);
		else if(g_stu_pSysC->l_MotorType==-2)              m_mtz.SetCurSel(2);
		else if(g_stu_pSysC->l_MotorType==2)               m_mtz.SetCurSel(3);
		else if(g_stu_pSysC->l_MotorType==-2.5)            m_mtz.SetCurSel(4);
		else if(g_stu_pSysC->l_MotorType==2.5)             m_mtz.SetCurSel(5);
		else                        m_mtz.SetCurSel(0);}
	if(!g_lRc)	{	if(g_stu_pSysD->l_MotorType==1)            m_mtw.SetCurSel(0);
		else if(g_stu_pSysD->l_MotorType==-1)              m_mtw.SetCurSel(1);
		else if(g_stu_pSysD->l_MotorType==-2)              m_mtw.SetCurSel(2);
		else if(g_stu_pSysD->l_MotorType==2)               m_mtw.SetCurSel(3);
		else if(g_stu_pSysD->l_MotorType==-2.5)            m_mtw.SetCurSel(4);
		else if(g_stu_pSysD->l_MotorType==2.5)             m_mtw.SetCurSel(5);
		else                        m_mtw.SetCurSel(0);}
	
	if(!g_lRc)	{	if(g_stu_pSysA->l_MainEncoder==0)   {         m_cex.SetCurSel(0);       m_ce2x.SetCurSel(0);}
    	else if(g_stu_pSysA->l_MainEncoder==2)      {         m_cex.SetCurSel(1);       m_ce2x.SetCurSel(0);}
    	else if(g_stu_pSysA->l_MainEncoder==8)      {         m_cex.SetCurSel(0);       m_ce2x.SetCurSel(1);}
    	else if(g_stu_pSysA->l_MainEncoder==10)     {         m_cex.SetCurSel(1);       m_ce2x.SetCurSel(1);}
		else if(g_stu_pSysA->l_MainEncoder==6)     {         m_cex.SetCurSel(1);       m_ce2x.SetCurSel(0);}
		else if(g_stu_pSysA->l_MainEncoder==4)     {         m_cex.SetCurSel(0);       m_ce2x.SetCurSel(0);}
		else               {         m_cex.SetCurSel(0);       m_ce2x.SetCurSel(0);}}
	if(!g_lRc)	{	if(g_stu_pSysB->l_MainEncoder==0)   {         m_cey.SetCurSel(0);       m_ce2y.SetCurSel(0);}
    	else if(g_stu_pSysB->l_MainEncoder==2)      {         m_cey.SetCurSel(1);       m_ce2y.SetCurSel(0);}
    	else if(g_stu_pSysB->l_MainEncoder==8)      {         m_cey.SetCurSel(0);       m_ce2y.SetCurSel(1);}
    	else if(g_stu_pSysB->l_MainEncoder==10)     {         m_cey.SetCurSel(1);       m_ce2y.SetCurSel(1);}
		else if(g_stu_pSysB->l_MainEncoder==6)     {         m_cey.SetCurSel(1);       m_ce2y.SetCurSel(0);}
		else if(g_stu_pSysB->l_MainEncoder==4)     {         m_cey.SetCurSel(0);       m_ce2y.SetCurSel(0);} 	
		else               {         m_cey.SetCurSel(0);       m_ce2y.SetCurSel(0);}}
	if(!g_lRc)	{	if(g_stu_pSysC->l_MainEncoder==0)   {         m_cez.SetCurSel(0);       m_ce2z.SetCurSel(0);}
    	else if(g_stu_pSysC->l_MainEncoder==2)      {         m_cez.SetCurSel(1);       m_ce2z.SetCurSel(0);}
    	else if(g_stu_pSysC->l_MainEncoder==8)      {         m_cez.SetCurSel(0);       m_ce2z.SetCurSel(1);}
    	else if(g_stu_pSysC->l_MainEncoder==10)     {         m_cez.SetCurSel(1);       m_ce2z.SetCurSel(1);}
		else if(g_stu_pSysC->l_MainEncoder==6)     {         m_cez.SetCurSel(1);       m_ce2z.SetCurSel(0);}
		else if(g_stu_pSysC->l_MainEncoder==4)     {         m_cez.SetCurSel(0);       m_ce2z.SetCurSel(0);}
    	else               {         m_cez.SetCurSel(0);       m_ce2z.SetCurSel(0);}}
	if(!g_lRc)	{	if(g_stu_pSysD->l_MainEncoder==0)   {         m_cew.SetCurSel(0);       m_ce2w.SetCurSel(0);}
    	else if(g_stu_pSysD->l_MainEncoder==2)      {         m_cew.SetCurSel(1);       m_ce2w.SetCurSel(0);}
    	else if(g_stu_pSysD->l_MainEncoder==8)      {         m_cew.SetCurSel(0);       m_ce2w.SetCurSel(1);}
		else if(g_stu_pSysD->l_MainEncoder==10)     {         m_cew.SetCurSel(1);       m_ce2w.SetCurSel(1);}
		else if(g_stu_pSysD->l_MainEncoder==6)     {         m_cew.SetCurSel(1);       m_ce2w.SetCurSel(0);}
		else if(g_stu_pSysD->l_MainEncoder==4)     {         m_cew.SetCurSel(0);       m_ce2w.SetCurSel(0);}
		else               {         m_cew.SetCurSel(0);       m_ce2w.SetCurSel(0);}}

	m_oex.SetCurSel(g_stu_pSysA->l_OffOnError);
	m_oey.SetCurSel(g_stu_pSysB->l_OffOnError);	
	m_oez.SetCurSel(g_stu_pSysC->l_OffOnError);
	m_oew.SetCurSel(g_stu_pSysD->l_OffOnError);
    m_mox.SetCurSel(g_stu_pSysA->l_MotorState);
    m_moy.SetCurSel(g_stu_pSysB->l_MotorState);	
    m_moz.SetCurSel(g_stu_pSysC->l_MotorState);	
    m_mow.SetCurSel(g_stu_pSysD->l_MotorState);
//*************************************************************************************	
	strTemp.Format("%.2f",g_stu_pSysA->d_DerivativeConstant);    CWnd::SetDlgItemText(IDC_EDIT_KDX,strTemp);
	strTemp.Format("%.2f",g_stu_pSysB->d_DerivativeConstant);    CWnd::SetDlgItemText(IDC_EDIT_KDY,strTemp);
	strTemp.Format("%.2f",g_stu_pSysC->d_DerivativeConstant);    CWnd::SetDlgItemText(IDC_EDIT_KDZ,strTemp);
	strTemp.Format("%.2f",g_stu_pSysD->d_DerivativeConstant);    CWnd::SetDlgItemText(IDC_EDIT_KDW,strTemp);

	strTemp.Format("%.2f",g_stu_pSysA->d_ProportionalConstant);  CWnd::SetDlgItemText(IDC_EDIT_KPX,strTemp);
	strTemp.Format("%.2f",g_stu_pSysB->d_ProportionalConstant);  CWnd::SetDlgItemText(IDC_EDIT_KPY,strTemp);
	strTemp.Format("%.2f",g_stu_pSysC->d_ProportionalConstant);  CWnd::SetDlgItemText(IDC_EDIT_KPZ,strTemp);
	strTemp.Format("%.2f",g_stu_pSysD->d_ProportionalConstant);  CWnd::SetDlgItemText(IDC_EDIT_KPW,strTemp);

	strTemp.Format("%.2f",g_stu_pSysA->d_Inteqrator);            CWnd::SetDlgItemText(IDC_EDIT_KIX,strTemp);
	strTemp.Format("%.2f",g_stu_pSysB->d_Inteqrator);            CWnd::SetDlgItemText(IDC_EDIT_KIY,strTemp);
	strTemp.Format("%.2f",g_stu_pSysC->d_Inteqrator);            CWnd::SetDlgItemText(IDC_EDIT_KIZ,strTemp);
	strTemp.Format("%.2f",g_stu_pSysD->d_Inteqrator);            CWnd::SetDlgItemText(IDC_EDIT_KIW,strTemp);

	strTemp.Format("%.2f",g_stu_pSysA->d_StepMotorSmoothing);            CWnd::SetDlgItemText(IDC_EDIT_KSX,strTemp);
	strTemp.Format("%.2f",g_stu_pSysB->d_StepMotorSmoothing);            CWnd::SetDlgItemText(IDC_EDIT_KSY,strTemp);
	strTemp.Format("%.2f",g_stu_pSysC->d_StepMotorSmoothing);            CWnd::SetDlgItemText(IDC_EDIT_KSZ,strTemp);
	strTemp.Format("%.2f",g_stu_pSysD->d_StepMotorSmoothing);            CWnd::SetDlgItemText(IDC_EDIT_KSW,strTemp);
//*****************************************************************

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL dlg_galil::PreTranslateMessage(MSG* pMsg) 
{
	return CDialog::PreTranslateMessage(pMsg);
}

void dlg_galil::OnButton8() 
{
	// TODO: Add extra validation here
	int i,j;
	CString strTemp;
    i =m_mtx.GetCurSel();	g_systemdll.SetMotorType('A',comMT(i));             
    i =m_mty.GetCurSel();	g_systemdll.SetMotorType('B',comMT(i));             
    i =m_mtz.GetCurSel();	g_systemdll.SetMotorType('C',comMT(i));             
    i =m_mtw.GetCurSel();	g_systemdll.SetMotorType('D',comMT(i));             
	//*******************************************************************************************
	j =m_cex.GetCurSel();         i =m_ce2x.GetCurSel();	g_systemdll.SetMainEncoder('A',comCE(i,j));         
	j =m_cey.GetCurSel();         i =m_ce2y.GetCurSel();	g_systemdll.SetMainEncoder('B',comCE(i,j));
	j =m_cez.GetCurSel();         i =m_ce2z.GetCurSel();	g_systemdll.SetMainEncoder('C',comCE(i,j));
	j =m_cew.GetCurSel();         i =m_ce2w.GetCurSel();	g_systemdll.SetMainEncoder('D',comCE(i,j));
	//*******************************************************************************************
	j =m_oex.GetCurSel();         g_systemdll.SetOffOnError('A',j);
	j =m_oey.GetCurSel();         g_systemdll.SetOffOnError('B',j);
	j =m_oez.GetCurSel();         g_systemdll.SetOffOnError('C',j);
	j =m_oew.GetCurSel();         g_systemdll.SetOffOnError('D',j);

	j =m_mox.GetCurSel();         g_systemdll.SetMotorState('A',j);
	j =m_moy.GetCurSel();         g_systemdll.SetMotorState('B',j);          
	j =m_moz.GetCurSel();         g_systemdll.SetMotorState('C',j);          
	j =m_mow.GetCurSel();         g_systemdll.SetMotorState('D',j);          
	//*******************************************************************************************
	GetDlgItemText(IDC_EDIT_KDX,strTemp);     	g_systemdll.SetDerivativeConstant('A',atof(strTemp));            
	GetDlgItemText(IDC_EDIT_KDY,strTemp);     	g_systemdll.SetDerivativeConstant('B',atof(strTemp));            
	GetDlgItemText(IDC_EDIT_KDZ,strTemp);     	g_systemdll.SetDerivativeConstant('C',atof(strTemp));            
	GetDlgItemText(IDC_EDIT_KDW,strTemp);     	g_systemdll.SetDerivativeConstant('D',atof(strTemp));  
	
	GetDlgItemText(IDC_EDIT_KPX,strTemp);     	g_systemdll.SetProportionalConstant('A',atof(strTemp));            
	GetDlgItemText(IDC_EDIT_KPY,strTemp);     	g_systemdll.SetProportionalConstant('B',atof(strTemp));            
	GetDlgItemText(IDC_EDIT_KPZ,strTemp);     	g_systemdll.SetProportionalConstant('C',atof(strTemp));            
	GetDlgItemText(IDC_EDIT_KPW,strTemp);     	g_systemdll.SetProportionalConstant('D',atof(strTemp));  
	
	GetDlgItemText(IDC_EDIT_KIX,strTemp);     	g_systemdll.SetInteqrator('A',atof(strTemp));            
	GetDlgItemText(IDC_EDIT_KIY,strTemp);     	g_systemdll.SetInteqrator('B',atof(strTemp));            
	GetDlgItemText(IDC_EDIT_KIZ,strTemp);     	g_systemdll.SetInteqrator('C',atof(strTemp));            
	GetDlgItemText(IDC_EDIT_KIW,strTemp);     	g_systemdll.SetInteqrator('D',atof(strTemp));   
	
	
	GetDlgItemText(IDC_EDIT_KSX,strTemp);     	g_systemdll.SetStepMotorSmoothing('A',atof(strTemp));            
	GetDlgItemText(IDC_EDIT_KSY,strTemp);     	g_systemdll.SetStepMotorSmoothing('B',atof(strTemp));            
	GetDlgItemText(IDC_EDIT_KSZ,strTemp);     	g_systemdll.SetStepMotorSmoothing('C',atof(strTemp));            
	GetDlgItemText(IDC_EDIT_KSW,strTemp);     	g_systemdll.SetStepMotorSmoothing('D',atof(strTemp));  
	g_Controller.Command("BN");
	g_systemdll.SetSysinfo(4);
	OnShowMessageBox(36,g_iLanguage,TRUE);
}

float dlg_galil::comMT(int i)
{
	float  f;
	if(i==0)                	f = 1;             
	else if(i==1)              	f = -1;
	else if(i==2)              	f = -2;
	else if(i==3)              	f = 2;
	else if(i==4)              	f = -2.5;
	else if(i==5)              	f = 2.5;
	return f;
}

long dlg_galil::comCE(int i,int j)
{
	long  l;
	if(j==0)                    l = 4;         
   	else if(j==1)               l = 6;         	
	return l;
}

void dlg_galil::OnLanguage()
{
	int   i;
	m_mox.ResetContent();
	m_moy.ResetContent();
	m_moz.ResetContent();
	m_mow.ResetContent();
	m_oex.ResetContent();
	m_oey.ResetContent();
	m_oez.ResetContent();
	m_oew.ResetContent();
	m_mtx.ResetContent();
	m_mty.ResetContent();
	m_mtz.ResetContent();
	m_mtw.ResetContent();
	m_ce2x.ResetContent();
	m_ce2y.ResetContent();
	m_ce2z.ResetContent();
	m_ce2w.ResetContent();
	m_cex.ResetContent();
	m_cey.ResetContent();
	m_cez.ResetContent();
	m_cew.ResetContent();
	if(!g_iLanguage)
	{
		m_mtx.AddString("�ŷ����");		
		m_mtx.AddString("�������ŷ����");		
		m_mtx.AddString("�߲������岽�����");		
		m_mtx.AddString("�Ͳ������岽�����");		
		m_mtx.AddString("����߲������岽�����");		
		m_mtx.AddString("����Ͳ������岽�����");		
		m_mty.AddString("�ŷ����");		
		m_mty.AddString("�������ŷ����");		
		m_mty.AddString("�߲������岽�����");		
		m_mty.AddString("�Ͳ������岽�����");		
		m_mty.AddString("����߲������岽�����");		
		m_mty.AddString("����Ͳ������岽�����");		
		m_mtz.AddString("�ŷ����");		
		m_mtz.AddString("�������ŷ����");		
		m_mtz.AddString("�߲������岽�����");		
		m_mtz.AddString("�Ͳ������岽�����");		
		m_mtz.AddString("����߲������岽�����");		
		m_mtz.AddString("����Ͳ������岽�����");		
		m_mtw.AddString("�ŷ����");		
		m_mtw.AddString("�������ŷ����");		
		m_mtw.AddString("�߲������岽�����");		
		m_mtw.AddString("�Ͳ������岽�����");		
		m_mtw.AddString("����߲������岽�����");		
		m_mtw.AddString("����Ͳ������岽�����");		
		m_mte.AddString("�ŷ����");		
		m_mte.AddString("�������ŷ����");		
		m_mte.AddString("�߲������岽�����");		
		m_mte.AddString("�Ͳ������岽�����");		
		m_mte.AddString("����߲������岽�����");		
		m_mte.AddString("����Ͳ������岽�����");		
		
		m_oex.AddString("���� (OFF)");
		m_oex.AddString("���� (ON)");
		m_oey.AddString("���� (OFF)");
		m_oey.AddString("���� (ON)");
		m_oez.AddString("���� (OFF)");
		m_oez.AddString("���� (ON)");
		m_oew.AddString("���� (OFF)");
		m_oew.AddString("���� (ON)");
		m_oee.AddString("���� (OFF)");
		m_oee.AddString("���� (ON)");
		
		m_mox.AddString("��");
		m_mox.AddString("��");
		m_moy.AddString("��");
		m_moy.AddString("��");
		m_moz.AddString("��");
		m_moz.AddString("��");
		m_mow.AddString("��");
		m_mow.AddString("��");
		m_moe.AddString("��");
		m_moe.AddString("��");
		
		m_ce2x.AddString("����");
		m_ce2x.AddString("����");
		m_ce2y.AddString("����");
		m_ce2y.AddString("����");
		m_ce2z.AddString("����");
		m_ce2z.AddString("����");
		m_ce2w.AddString("����");
		m_ce2w.AddString("����");
		m_ce2e.AddString("����");
		m_ce2e.AddString("����");
		
		m_cex.AddString("����");
		m_cex.AddString("����");
		m_cey.AddString("����");
		m_cey.AddString("����");
		m_cez.AddString("����");
		m_cez.AddString("����");
		m_cew.AddString("����");
		m_cew.AddString("����");
		m_cee.AddString("����");
		m_cee.AddString("����");
		
		for(i=0;i<AR_GALIL;i++)
		{
			if (g_arr_strGalil[i][1] == "NULL")
				g_arr_strGalil[i][1] = "";			
			CWnd::SetDlgItemText(atoi(g_arr_strGalil[i][0]),g_arr_strGalil[i][1]);
		}
	}
	else
	{
		m_mtx.AddString("Servo motor");		
		m_mtx.AddString("Servo motor with reversed polarity");		
		m_mtx.AddString("Step motor with active high step pulses");		
		m_mtx.AddString("Step motor with active low step pulses");		
		m_mtx.AddString("Step motor with reversed direction and active high step pulses");		
		m_mtx.AddString("Step motor with reversed direction and active low step pulses");		
		m_mty.AddString("Servo motor");		
		m_mty.AddString("Servo motor with reversed polarity");		
		m_mty.AddString("Step motor with active high step pulses");		
		m_mty.AddString("Step motor with active low step pulses");		
		m_mty.AddString("Step motor with reversed direction and active high step pulses");		
		m_mty.AddString("Step motor with reversed direction and active low step pulses");		
		m_mtz.AddString("Servo motor");		
		m_mtz.AddString("Servo motor with reversed polarity");		
		m_mtz.AddString("Step motor with active high step pulses");		
		m_mtz.AddString("Step motor with active low step pulses");		
		m_mtz.AddString("Step motor with reversed direction and active high step pulses");		
		m_mtz.AddString("Step motor with reversed direction and active low step pulses");		
		m_mtw.AddString("Servo motor");		
		m_mtw.AddString("Servo motor with reversed polarity");		
		m_mtw.AddString("Step motor with active high step pulses");		
		m_mtw.AddString("Step motor with active low step pulses");		
		m_mtw.AddString("Step motor with reversed direction and active high step pulses");		
		m_mtw.AddString("Step motor with reversed direction and active low step pulses");		
		m_mte.AddString("Servo motor");		
		m_mte.AddString("Servo motor with reversed polarity");		
		m_mte.AddString("Step motor with active high step pulses");		
		m_mte.AddString("Step motor with active low step pulses");		
		m_mte.AddString("Step motor with reversed direction and active high step pulses");		
		m_mte.AddString("Step motor with reversed direction and active low step pulses");		
		
		m_oex.AddString("Disabled (OFF)");
		m_oex.AddString("Enabled  (ON)");
		m_oey.AddString("Disabled (OFF)");
		m_oey.AddString("Enabled  (ON)");
		m_oez.AddString("Disabled (OFF)");
		m_oez.AddString("Enabled  (ON)");
		m_oew.AddString("Disabled (OFF)");
		m_oew.AddString("Enabled  (ON)");
		m_oee.AddString("Disabled (OFF)");
		m_oee.AddString("Enabled  (ON)");
		
		m_mox.AddString("ON");
		m_mox.AddString("OFF");
		m_moy.AddString("ON");
		m_moy.AddString("OFF");
		m_moz.AddString("ON");
		m_moz.AddString("OFF");
		m_mow.AddString("ON");
		m_mow.AddString("OFF");
		m_moe.AddString("ON");
		m_moe.AddString("OFF");
		
		m_ce2x.AddString("Normal");
		m_ce2x.AddString("Reverse");
		m_ce2y.AddString("Normal");
		m_ce2y.AddString("Reverse");
		m_ce2z.AddString("Normal");
		m_ce2z.AddString("Reverse");
		m_ce2w.AddString("Normal");
		m_ce2w.AddString("Reverse");
		m_ce2e.AddString("Normal");
		m_ce2e.AddString("Reverse");
		
		m_cex.AddString("Normal");
		m_cex.AddString("Reverse");
		m_cey.AddString("Normal");
		m_cey.AddString("Reverse");
		m_cez.AddString("Normal");
		m_cez.AddString("Reverse");
		m_cew.AddString("Normal");
		m_cew.AddString("Reverse");
		m_cee.AddString("Normal");
		m_cee.AddString("Reverse");
		for(i=0;i<AR_GALIL;i++)
		{
			if (g_arr_strGalil[i][2] == "NULL")
				g_arr_strGalil[i][2] = "";	
			CWnd::SetDlgItemText(atoi(g_arr_strGalil[i][0]),g_arr_strGalil[i][2]);
		}
	}
}

LRESULT dlg_galil::OnEditDouble(WPARAM wParam, LPARAM lParam) 
{
	CString				strTmp;
	CDlg_KeyNumber		KeyNum;
	
	if(lParam==1)/* �д����� */
	{
		((CEdit *)GetDlgItem(wParam))->SetSel(0,-1);
		return 0;
	}
	
	CWnd::GetDlgItemText(wParam,strTmp);
	KeyNum.m_strNew = KeyNum.m_strOld = strTmp;
	switch(wParam) 
	{
	case IDC_EDIT_KDX:				GetDlgItemText(IDC_STATICt4,KeyNum.m_strTitle);		KeyNum.m_strTitle = "X " + KeyNum.m_strTitle;		break;
	case IDC_EDIT_KDY:				GetDlgItemText(IDC_STATICt4,KeyNum.m_strTitle);		KeyNum.m_strTitle = "Y " + KeyNum.m_strTitle;		break;
	case IDC_EDIT_KDZ:				GetDlgItemText(IDC_STATICt4,KeyNum.m_strTitle);		KeyNum.m_strTitle = "Z " + KeyNum.m_strTitle;		break;
	case IDC_EDIT_KDW:				GetDlgItemText(IDC_STATICt4,KeyNum.m_strTitle);		KeyNum.m_strTitle = "W " + KeyNum.m_strTitle;		break;
	case IDC_EDIT_KPX:				GetDlgItemText(IDC_STATICt7,KeyNum.m_strTitle);		KeyNum.m_strTitle = "X " + KeyNum.m_strTitle;		break;
	case IDC_EDIT_KPY:				GetDlgItemText(IDC_STATICt7,KeyNum.m_strTitle);		KeyNum.m_strTitle = "Y " + KeyNum.m_strTitle;		break;
	case IDC_EDIT_KPZ:				GetDlgItemText(IDC_STATICt7,KeyNum.m_strTitle);		KeyNum.m_strTitle = "Z " + KeyNum.m_strTitle;		break;
	case IDC_EDIT_KPW:				GetDlgItemText(IDC_STATICt7,KeyNum.m_strTitle);		KeyNum.m_strTitle = "W " + KeyNum.m_strTitle;		break;
	case IDC_EDIT_KIX:				GetDlgItemText(IDC_STATICt8,KeyNum.m_strTitle);		KeyNum.m_strTitle = "X " + KeyNum.m_strTitle;		break;
	case IDC_EDIT_KIY:				GetDlgItemText(IDC_STATICt8,KeyNum.m_strTitle);		KeyNum.m_strTitle = "Y " + KeyNum.m_strTitle;		break;
	case IDC_EDIT_KIZ:				GetDlgItemText(IDC_STATICt8,KeyNum.m_strTitle);		KeyNum.m_strTitle = "Z " + KeyNum.m_strTitle;		break;
	case IDC_EDIT_KIW:				GetDlgItemText(IDC_STATICt8,KeyNum.m_strTitle);		KeyNum.m_strTitle = "W " + KeyNum.m_strTitle;		break;
	case IDC_EDIT_KSX:				GetDlgItemText(IDC_STATICt10,KeyNum.m_strTitle);	KeyNum.m_strTitle = "X " + KeyNum.m_strTitle;		break;
	case IDC_EDIT_KSY:				GetDlgItemText(IDC_STATICt10,KeyNum.m_strTitle);	KeyNum.m_strTitle = "Y " + KeyNum.m_strTitle;		break;
	case IDC_EDIT_KSZ:				GetDlgItemText(IDC_STATICt10,KeyNum.m_strTitle);	KeyNum.m_strTitle = "Z " + KeyNum.m_strTitle;		break;
	case IDC_EDIT_KSW:				GetDlgItemText(IDC_STATICt10,KeyNum.m_strTitle);	KeyNum.m_strTitle = "W " + KeyNum.m_strTitle;		break;
	default:
		break;
	}
	if(KeyNum.DoModal()==IDOK)
		CWnd::SetDlgItemText(wParam,KeyNum.m_strNew);
	
	return 0;
}

void dlg_galil::OnButton10() 
{
	CDialog::OnOK();
}

void dlg_galil::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//������ͼƬ
	CDC  MemDc;
	CBitmap bitmap;	
	MemDc.CreateCompatibleDC(&dc);
	bitmap.LoadBitmap(IDB_BITMAP_DIALOG);
	CBitmap *pOldBit = MemDc.SelectObject(&bitmap);
	dc.BitBlt(0,0,1024,768,&MemDc,0,0,SRCCOPY);
	MemDc.SelectObject(pOldBit);
	bitmap.DeleteObject();
	MemDc.DeleteDC();
	CDialog::OnPaint();		
	// Do not call CDialog::OnPaint() for painting messages
}

void dlg_galil::InitButton()
{
	HRGN c;
	
	c = CreateRectRgn(0, 0, 0, 0);	
	GetBitMapRgn(GetDC(),c,IDB_BITMAP_ZEOR1);
	//����
	m_pButton[0].SetFont(&g_fontEdit);
	m_pButton[0].SetBitMapID(IDB_BITMAP_SAVE1,IDB_BITMAP_SAVE2);	
	m_pButton[0].Create(g_arr_strSuper[12][g_iLanguage + 1], WS_CHILD | WS_VISIBLE, CPoint(700, 705), c, this, IDC_BUTTON8); 
	
	//����	
	m_pButton[1].SetFont(&g_fontEdit);
	m_pButton[1].SetBitMapID(IDB_BITMAP_BACK1,IDB_BITMAP_BACK2);	
	m_pButton[1].Create(g_arr_strSuper[13][g_iLanguage + 1], WS_CHILD | WS_VISIBLE, CPoint(870, 705), c, this, IDC_BUTTON10); 
    
	DeleteObject(c); 	
}

HBRUSH dlg_galil::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
#ifdef POWERLAND
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return (HBRUSH)GetStockObject(NULL_BRUSH);		
	}
#endif
	return hbr;
}
