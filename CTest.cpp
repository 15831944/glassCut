// CTest.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "CTest.h"
#include "benderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCTest dialog


CCTest::CCTest(CWnd* pParent /*=NULL*/)
	: CDialog(CCTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCTest)
	//}}AFX_DATA_INIT
	m_nTestType = 0;
}

CCTest::~CCTest()
{

}

void CCTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCTest)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCTest, CDialog)
	//{{AFX_MSG_MAP(CCTest)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO9, OnRadio9)
	ON_BN_CLICKED(IDC_RADIO10, OnRadio10)
	ON_BN_CLICKED(IDC_RADIO11, OnRadio11)
	ON_BN_CLICKED(IDC_RADIO12, OnRadio12)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCTest message handlers

void CCTest::OnOK() 
{
	// TODO: Add extra validation here
}

void CCTest::OnCancel() 
{
	// TODO: Add extra cleanup here
//	CDialog::OnCancel();
}

BOOL CCTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  	// TODO: Add extra initialization here
	Onlanguge();
	OnRadio1(); 
	UpdateData(FALSE);
	SetWindowPos(CWnd::GetOwner(),722,365,294,342,SWP_SHOWWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CCTest::Onlanguge()
{
	if (g_iLanguage == 1)
	{
		SetDlgItemText(IDC_RADIO1,"X axis Angle of 90 degrees");
		SetDlgItemText(IDC_RADIO2,"Y axis Angle of 90 degrees");
		SetDlgItemText(IDC_RADIO3,"Diagonal adjustment");
		SetDlgItemText(IDC_RADIO9,"Precision of X axis");
		SetDlgItemText(IDC_RADIO10,"Precision of X axis");
		SetDlgItemText(IDC_RADIO11,"Eccentric adjustment");
		SetDlgItemText(IDC_RADIO12,"Photoelectric register ");
	}
	else
	{
		CString str;
		str.Format("对角线调整(%.0f*%.0f)",g_stu_pAxisA->dSpareA-385,g_stu_pAxisB->dSpareA-385);
		SetDlgItemText(IDC_RADIO3,str);

	}
}

//X轴90度
void CCTest::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)AfxGetMainWnd();
    if(pDlg != NULL)
	{
		m_nTestType = 0;
		g_strShowName = "test1.g";
		g_strGfile = "D:\\program files\\GlassCutter\\gcode\\test\\test1.g";
		pDlg->FileOpen();  
	}
}

void CCTest::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)AfxGetMainWnd();
    if(pDlg != NULL)
	{
		m_nTestType = 1;
		g_strShowName = "test2.g";
		g_strGfile = "D:\\program files\\GlassCutter\\gcode\\test\\test2.g";
		pDlg->FileOpen();  
	}
}

void CCTest::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)AfxGetMainWnd();
    if(pDlg != NULL)
	{
		m_nTestType = 2;
		WriteCatercorner();
		g_strShowName = "test3.g";
		g_strGfile = "D:\\program files\\GlassCutter\\gcode\\test\\test3.g";
		pDlg->FileOpen();  
	}	
}

void CCTest::OnRadio9() 
{
	// TODO: Add your control notification handler code here
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)AfxGetMainWnd();
    if(pDlg != NULL)
	{
		m_nTestType = 3;
		g_strShowName = "test4.g";
		g_strGfile = "D:\\program files\\GlassCutter\\gcode\\test\\test4.g";
		pDlg->FileOpen();  
	}		
}

void CCTest::OnRadio10() 
{
	// TODO: Add your control notification handler code here
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)AfxGetMainWnd();
    if(pDlg != NULL)
	{
		m_nTestType = 4;
		g_strShowName = "test5.g";
		g_strGfile = "D:\\program files\\GlassCutter\\gcode\\test\\test5.g";
		pDlg->FileOpen();  
	}		
}

void CCTest::OnRadio11() 
{
	// TODO: Add your control notification handler code here
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)AfxGetMainWnd();
    if(pDlg != NULL)
	{
		m_nTestType = 5;
		g_strShowName = "test6.g";
		g_strGfile = "D:\\program files\\GlassCutter\\gcode\\test\\test6.g";
		pDlg->FileOpen();  
	}	
}

void CCTest::OnRadio12() 
{
	// TODO: Add your control notification handler code here
	CBenderDlg *pDlg;
	pDlg = (CBenderDlg *)AfxGetMainWnd();
    if(pDlg != NULL)
	{
		m_nTestType = 6;
		g_strShowName = "test7.g";
		g_strGfile = "D:\\program files\\GlassCutter\\gcode\\test\\test7.g";
		pDlg->FileOpen();  
	}		
}

void CCTest::WriteCatercorner()//根据机床尺寸写对角线测试的g代码
{
	FILE		*fileSetup;
	
	CString		strFileName = "D:\\program files\\GlassCutter\\gcode\\test\\test3.g";
	
	if (!(fileSetup = fopen((char *)((const char*)strFileName), "w")))
		return;
	double dOrigen = 15.0;//开始点
	double dDis = 15;//切割的lenght
	double dXMax = g_stu_pAxisA->dSpareA - 400;
	double dYMax = g_stu_pAxisB->dSpareA - 400;
    CString strGCode;
	fprintf(fileSetup, "G90\nG21\nM25\nM10\n");
	
	fprintf(fileSetup, "G00 X%.0f Y%.0f\nM09\n",dOrigen,dOrigen-dDis);	
	fprintf(fileSetup, "G01 X%.0f Y%.0f\nM10\n",dOrigen,dOrigen+dDis);	
	fprintf(fileSetup, "G00 X%.0f Y%.0f\nM09\n",dOrigen,dYMax-dDis);	
	fprintf(fileSetup, "G01 X%.0f Y%.0f\nM10\n",dOrigen,dYMax+dDis);
	
	fprintf(fileSetup, "G00 X%.0f Y%.0f\nM09\n",dXMax,dOrigen-dDis);	
	fprintf(fileSetup, "G01 X%.0f Y%.0f\nM10\n",dXMax,dOrigen+dDis);	
	fprintf(fileSetup, "G00 X%.0f Y%.0f\nM09\n",dXMax,dYMax-dDis);	
	fprintf(fileSetup, "G01 X%.0f Y%.0f\nM10\n",dXMax,dYMax+dDis);	

	fprintf(fileSetup, "G00 X%.0f Y%.0f\nM09\n",dOrigen-dDis,dOrigen);	
	fprintf(fileSetup, "G01 X%.0f Y%.0f\nM10\n",dOrigen+dDis,dOrigen);	
	fprintf(fileSetup, "G00 X%.0f Y%.0f\nM09\n",dXMax-dDis,dOrigen);	
	fprintf(fileSetup, "G01 X%.0f Y%.0f\nM10\n",dXMax+dDis,dOrigen);
	
	fprintf(fileSetup, "G00 X%.0f Y%.0f\nM09\n",dOrigen-dDis,dYMax);	
	fprintf(fileSetup, "G01 X%.0f Y%.0f\nM10\n",dOrigen+dDis,dYMax);	
	fprintf(fileSetup, "G00 X%.0f Y%.0f\nM09\n",dXMax-dDis,dYMax);	
	fprintf(fileSetup, "G01 X%.0f Y%.0f\nM10\n",dXMax+dDis,dYMax);	
	
	fprintf(fileSetup, "M26\nG90G00X0Y0Z0\nM30\nM30\n");
	
	fclose(fileSetup); 	
}

