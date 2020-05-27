// Dlg_Calculator.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_Calculator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_Calculator dialog


CDlg_Calculator::CDlg_Calculator(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_Calculator::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Calculator)
	m_nCalCode = 0;
	m_nCode = 2048;
	m_nCalDenominator = 1;
	m_nCalMolecule = 1;
	m_dDistance = 10.0;
	m_dPulse = 100.0;
	m_nMode = 0;
	m_strHit = _T("");
	strCode = "伺服电机实际编码器的线数。";
	strDistance = "直线方式：电机转一圈对应的距离(用户单位：毫米或英寸)；圆台方式：电机一圈对应的角度";
	strPulse = "脉冲当量，即每个用户单位的脉冲数，根据设备精度设置，一般是整数。(例如：分辨率为1u，脉冲当量为1000)";
	strBtnCal = "脉冲当量设置过高，计算编码器线数超过编码器物理刻线。";
	strRotate = "设置电机每分钟转速，用于计算此转速时，对应的设备速度；输入电机最大转速时，计算设备最大速度；输入电机额定转速时，计算设备的额定速度。";
	strBtnOk = "计算成功！";
	m_nMachineSp = 0;
	m_nServoSp = 2000;
	//}}AFX_DATA_INIT
    m_brush.CreateSolidBrush(RGB(0, 64, 128));//红色
}

CDlg_Calculator::~CDlg_Calculator()
{
	if (m_brush.GetSafeHandle())
	{
		m_brush.DeleteObject();
	}
}

void CDlg_Calculator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Calculator)
	DDX_Control(pDX, IDC_EDIT_SERVOSP, m_edtServoSp);
	DDX_Control(pDX, IDC_EDIT_MACHINESP, m_edtMachineSp);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_EDIT_CALCODE, m_edtCalCode);
	DDX_Control(pDX, IDC_EDIT_CODE, m_edtCode);
	DDX_Control(pDX, IDC_EDIT_CALMOLECULE, m_edtCalMo);
	DDX_Control(pDX, IDC_EDIT_CALDENOMINATOR, m_edtCalDe);
	DDX_Text(pDX, IDC_EDIT_CALCODE, m_nCalCode);
	DDX_Text(pDX, IDC_EDIT_CODE, m_nCode);
	DDX_Text(pDX, IDC_EDIT_CALDENOMINATOR, m_nCalDenominator);
	DDX_Text(pDX, IDC_EDIT_CALMOLECULE, m_nCalMolecule);
	DDX_Text(pDX, IDC_EDIT_DISTANCE, m_dDistance);
	DDX_Text(pDX, IDC_EDIT_PULSE, m_dPulse);
	DDX_Radio(pDX, IDC_RADIO1, m_nMode);
	DDX_Text(pDX, IDC_STATIC_HIT, m_strHit);
	DDX_Text(pDX, IDC_EDIT_MACHINESP, m_nMachineSp);
	DDX_Text(pDX, IDC_EDIT_SERVOSP, m_nServoSp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_Calculator, CDialog)
	//{{AFX_MSG_MAP(CDlg_Calculator)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_EN_SETFOCUS(IDC_EDIT_CODE, OnSetfocusEditCode)
	ON_EN_SETFOCUS(IDC_EDIT_DISTANCE, OnSetfocusEditDistance)
	ON_EN_SETFOCUS(IDC_EDIT_PULSE, OnSetfocusEditPulse)
	ON_WM_CTLCOLOR()
	ON_EN_SETFOCUS(IDC_EDIT_SERVOSP, OnSetfocusEditServosp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_Calculator message handlers

BOOL CDlg_Calculator::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();
	
	m_btnOK.SetIconOption(IDI_ICON_CAL);
	m_btnCancel.SetIconOption(IDI_ICON_QUIT);
	
	// TODO: Add extra initialization here
	m_edtCalMo.SetReadOnly();
	m_edtCalDe.SetReadOnly();
	m_edtCalCode.SetReadOnly();
	m_edtMachineSp.SetReadOnly();
	OnOK();
	OnLanguage();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg_Calculator::OnOK() 
{
	Radio	stuRadio;

	memset(&stuRadio, 0, sizeof(Radio));
	UpdateData(TRUE);
	if(m_nMode==0)	/* 位置方式 */
	{
		m_nCalCode = (long)((m_dDistance * m_dPulse) / 4);
		stuRadio.dDeno = m_dDistance * m_dPulse;
		stuRadio.dMole = m_nCode * 4;
		OnToLong(&stuRadio);
		OnToLowestTerms(&stuRadio);
		m_nCalDenominator = stuRadio.nDeno;
		m_nCalMolecule = stuRadio.nMole;
		m_nMachineSp = (long)(m_nServoSp * m_dDistance / 1000);
	}
	else			/* 速度方式 */
	{
		m_nCalCode = (long)((m_dDistance * m_dPulse) / 4);
		m_nCalDenominator = 1;
		m_nCalMolecule = 1;
		m_nMachineSp = (long)(m_nServoSp * m_dDistance / 1000);
	}
	if(m_nCalCode>m_nCode)
		m_strHit = strBtnCal;
	else
		m_strHit = strBtnOk;
	UpdateData(FALSE);
}

void CDlg_Calculator::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnOK();
}

void CDlg_Calculator::OnRadio1() 
{
	UpdateData(TRUE);
	if(m_nMode==0)	/* 位置方式 */
	{
		m_edtCode.SetReadOnly(FALSE);
	}
	else			/* 速度方式 */
	{
		m_edtCode.SetReadOnly(TRUE);
	}
	OnOK();
}

void CDlg_Calculator::OnRadio2() 
{
	UpdateData(TRUE);
	if(m_nMode==0)	/* 位置方式 */
	{
		m_edtCode.SetReadOnly(FALSE);
	}
	else			/* 速度方式 */
	{
		m_edtCode.SetReadOnly(TRUE);
	}
	OnOK();
}

void CDlg_Calculator::OnToLong(PRadio pVar) 
{
	int	n = 0;
	while (((pVar->dMole - (long)pVar->dMole)>0.0 || (pVar->dDeno - (long)pVar->dDeno)>0.0 ) && n<4) 
	{
		n++;
		pVar->dMole = pVar->dMole * 10.0;
		pVar->dDeno = pVar->dDeno * 10.0;
	}
	pVar->nDeno = (long)pVar->dDeno;
	pVar->nMole = (long)pVar->dMole;
}

void CDlg_Calculator::OnToLowestTerms(PRadio pVar) 
{
	while (pVar->nDeno%2==0 && pVar->nMole%2==0 ) 
	{
		pVar->nMole = pVar->nMole / 2;
		pVar->nDeno = pVar->nDeno / 2;
	}

	while (pVar->nDeno%3==0 && pVar->nMole%3==0 ) 
	{
		pVar->nMole = pVar->nMole / 3;
		pVar->nDeno = pVar->nDeno / 3;
	}

	while (pVar->nDeno%5==0 && pVar->nMole%5==0 ) 
	{
		pVar->nMole = pVar->nMole / 5;
		pVar->nDeno = pVar->nDeno / 5;
	}
}

void CDlg_Calculator::OnSetfocusEditCode() 
{
	UpdateData(TRUE);
	m_strHit = strCode;
	UpdateData(FALSE);
}

void CDlg_Calculator::OnSetfocusEditDistance() 
{
	UpdateData(TRUE);
	m_strHit = strDistance;
	UpdateData(FALSE);
}

void CDlg_Calculator::OnSetfocusEditPulse() 
{
	UpdateData(TRUE);
	m_strHit = strPulse;
	UpdateData(FALSE);
}

HBRUSH CDlg_Calculator::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (nCtlColor==CTLCOLOR_STATIC)
	{
		if((pWnd->GetDlgCtrlID()==IDC_STATIC_TITLE))
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkColor(RGB(0, 64, 128));
			return (HBRUSH)m_brush.GetSafeHandle();
		}
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CDlg_Calculator::OnSetfocusEditServosp() 
{
	UpdateData(TRUE);
	m_strHit = strRotate;
	UpdateData(FALSE);
}

void CDlg_Calculator::OnLanguage()
{
	if (g_iLanguage == 1)
	{
		strCode = "The actual encoder servo motor lines.";
		strDistance = "Linear mode: Electric switch circle the corresponding distance (user units: mm or inches); round table by: circle corresponds to the angle of motor";
		strPulse = "Pulse equivalent, that is, the number of pulses for each user unit, set up according to the precision equipment, usually an integer. (Example: resolution of 1u, pulse equivalent to 1000)";
		strBtnCal = "Pulse equivalent set too high, calculate the number of encoder lines more than the physical encoder groove.";
		strRotate = "Set the motor speed per minute, used to calculate the speed, the corresponding device speed; enter the maximum motor speed when the maximum speed of computing devices; enter the motor rated speed, rated speed of computing devices.";
		strBtnOk = "Succeed";
		SetDlgItemText(IDC_STATICA,"Encoder groove");
		SetDlgItemText(IDC_STATICD,"Encoder lines parameters");
		SetDlgItemText(IDC_STATICB,"Distance per revolution motor");
		SetDlgItemText(IDC_STATICE,"Molecular electronic gear ratio");
		SetDlgItemText(IDC_STATICC,"Pulse equivalent required");
		SetDlgItemText(IDC_STATICF,"Electronic gear score mother");
		SetDlgItemText(IDC_STATICG,"Motor speed");
		SetDlgItemText(IDC_STATICH,"Equipment Speed");
		SetDlgItemText(IDC_RADIO1,"Position  mode");
		SetDlgItemText(IDC_RADIO2,"Speed mode");
		SetDlgItemText(IDC_STATIC_TITLE," Powerland——Servo Calculator");
		m_btnOK.SetWindowText("Calc");
		m_btnCancel.SetWindowText("Close");
		UpdateData(FALSE);
	}
}