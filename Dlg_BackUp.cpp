// Dlg_BackUp.cpp : implementation file
//

#include "stdafx.h"
#include "bender.h"
#include "Dlg_BackUp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_BackUp dialog


CDlg_BackUp::CDlg_BackUp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_BackUp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_BackUp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_strParaCopyPath = "D:\\program files\\GlassCutter";
	m_strParaBuckupPath = "D:\\program files\\ParaBackup";

}


void CDlg_BackUp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_BackUp)
	DDX_Control(pDX, IDC_BUTTON2, m_clrBtn2);
	DDX_Control(pDX, IDCANCEL, m_clrBtnCancel);
	DDX_Control(pDX, IDC_BUTTON14, m_clrBtn4);
	DDX_Control(pDX, IDC_BUTTON3, m_clrBtn3);
	DDX_Control(pDX, IDC_BUTTON1, m_clrBtn1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_BackUp, CDialog)
	//{{AFX_MSG_MAP(CDlg_BackUp)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON14, OnButton14)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_BackUp message handlers

BOOL CDlg_BackUp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CStatic*)(GetDlgItem(IDC_STATIC1)))->SetFont(&g_fontButton);
	if (g_iLanguage == 0)
	{
		SetWindowText("��������");
	}
	else
	{
		SetWindowText("Para BackUp");
		SetDlgItemText(IDC_BUTTON1,"Disk Backup ");
		SetDlgItemText(IDC_BUTTON2,"Disk Recovery");
		SetDlgItemText(IDC_BUTTON3,"USB Backup");
		SetDlgItemText(IDC_BUTTON14,"USB Recovery");
		SetDlgItemText(IDCANCEL,"Back");
		SetDlgItemText(IDC_STATIC1,"Note:parameters reduction,u disk after reduction need to restart the software");
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/* ���������ݵ����ص��ļ��� */
void CDlg_BackUp::OnParaBuckup() 
{
	if(!FolderExist(m_strParaBuckupPath))
		BOOL re = CreateDirectory(m_strParaBuckupPath, NULL);
	else
		DeleteDirectoryContext(m_strParaBuckupPath);
	if(g_iLanguage==0)
		SetDlgItemText(IDC_STATIC2,"���ڱ�����......");
	else
		SetDlgItemText(IDC_STATIC2,"BackUping......");
	SetFileAttributes(m_strParaBuckupPath, GetFileAttributes(m_strParaBuckupPath) | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY);
	CopyDirectory(m_strParaCopyPath, m_strParaBuckupPath);
	if(g_iLanguage==0)
		SetDlgItemText(IDC_STATIC2,"�������");
	else 
		SetDlgItemText(IDC_STATIC2,"BackUp Completed");
}

/* �����������ص��ļ��н��лָ� */
void CDlg_BackUp::OnParaRenew() 
{
	if(FolderExist(m_strParaBuckupPath))
	{
		if(g_iLanguage==0)
			SetDlgItemText(IDC_STATIC2,"���ڻָ���......");
		else
			SetDlgItemText(IDC_STATIC2,"Recovering......");
		DeleteDirectoryContext(m_strParaCopyPath);
		CopyDirectory(m_strParaBuckupPath, m_strParaCopyPath);
		if(g_iLanguage==0)
			SetDlgItemText(IDC_STATIC2,"�ָ����");
		else 
			SetDlgItemText(IDC_STATIC2,"Recover Completed");
	}
	else
	{
		if (g_iLanguage==0)
		{
			MessageBox("û���ҵ������ļ�");
		}
		else
		{
			MessageBox("No Find the Backup");
		}
	}
}

/* ���������ݵ�USB�豸 */
void CDlg_BackUp::OnUsbParaBuckup() 
{
	CString		strMoveDir;
	
	strMoveDir = movediskdir();
	if(strMoveDir.IsEmpty())
	{
		if(!g_iLanguage)    	MessageBox("�Ҳ������ƶ����̣�","ʧ��!!!",MB_OK|MB_ICONINFORMATION);
		else  		            MessageBox("Can not find USB disk��","Failure!!!",MB_OK|MB_ICONINFORMATION);
		return;
	}
	else
	{
		if(g_iLanguage==0)
			SetDlgItemText(IDC_STATIC2,"���ڱ�����......");
		else
			SetDlgItemText(IDC_STATIC2,"BackUping......");
		strMoveDir = strMoveDir + "ParaBackup";
		if(!FolderExist(strMoveDir))
			BOOL re = CreateDirectory(strMoveDir, NULL);
		else
			DeleteDirectoryContext(strMoveDir);		
		CopyDirectory(m_strParaCopyPath, strMoveDir);
		if(g_iLanguage==0)
			SetDlgItemText(IDC_STATIC2,"�������");
		else 
			SetDlgItemText(IDC_STATIC2,"BackUp Completed");
	}
}

/* ��������USB�豸���лָ� */
void CDlg_BackUp::OnUsbParaRenew() 
{
	CString		strMoveDir;
	
	strMoveDir = movediskdir();
	if(strMoveDir.IsEmpty())
	{
		if(!g_iLanguage)    	MessageBox("�Ҳ������ƶ����̣�","ʧ��!!!",MB_OK|MB_ICONINFORMATION);
		else  		            MessageBox("Can not find USB disk��","Failure!!!",MB_OK|MB_ICONINFORMATION);
		return;
	}
	else
	{
		strMoveDir = strMoveDir + "ParaBackup";
		if(FolderExist(strMoveDir))
		{
			if(g_iLanguage==0)
				SetDlgItemText(IDC_STATIC2,"���ڻָ���......");
			else
				SetDlgItemText(IDC_STATIC2,"Recovering......");
			DeleteDirectoryContext(m_strParaCopyPath);
			CopyDirectory(strMoveDir, m_strParaCopyPath);
			if(g_iLanguage==0)
				SetDlgItemText(IDC_STATIC2,"�ָ����");
			else 
				SetDlgItemText(IDC_STATIC2,"Recover Completed");
		}
		else
		{
			if (g_iLanguage==0)
			{
				MessageBox("û���ҵ������ļ�");
			}
			else
			{
				MessageBox("No Find the Backup");
			}
		}
	}
}

/* �ж��ļ����Ƿ���� */
BOOL CDlg_BackUp::FolderExist(CString strPath) 
{
    WIN32_FIND_DATA wfd;
    BOOL rValue = FALSE;
    HANDLE hFind = FindFirstFile(strPath, &wfd);
    if ((hFind!=INVALID_HANDLE_VALUE) && 
		(wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))
    {
        rValue = TRUE;
    }
    FindClose(hFind);
    return rValue; 
}

/* ���Ŀ¼�е����� */
void CDlg_BackUp::DeleteDirectoryContext(CString strPath)
{
	CFileFind find;
	BOOL re;
	re = find.FindFile(strPath + "\\*.*");
	while (re)
	{
		re = find.FindNextFile();
		if (find.IsDirectory())
		{
			if (!find.IsDots())
			{
				DeleteDirectory(find.GetFilePath());
			}
		}
		else
		{
			::DeleteFile(find.GetFilePath());
		}
	}
	find.Close();//һ���ȹر����,���Ƴ�ɾ���ļ���
}

void CDlg_BackUp::OnButton1() 
{
	// TODO: Add your control notification handler code here
	OnParaBuckup();
}


void CDlg_BackUp::OnButton2() 
{
	// TODO: Add your control notification handler code here
	OnParaRenew(); 
}

void CDlg_BackUp::OnButton3() 
{
	// TODO: Add your control notification handler code here
	OnUsbParaBuckup(); 
}

void CDlg_BackUp::OnButton14() 
{
	// TODO: Add your control notification handler code here
	OnUsbParaRenew(); 
}
