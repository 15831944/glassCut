#ifndef _IOExcel_H_
#define _IOExcel_H_

//#include "Resource.h"
#include "excel.h"
#include "RectOptDlg.h"

class CIOExcel
{
public:

	CIOExcel();

	~CIOExcel();

private:
	
	// �Ի������
	CRectOptDlg* m_pExcelOperDlg;

	// ExcelӦ�ö���
	_Application	m_oExcelApp;
	_Worksheet		m_oWorkSheet;
	_Workbook		m_oWorkBook;
	Workbooks		m_oWorkBooks;
	Worksheets		m_oWorkSheets;
	Range			m_oCurrRange;

public:
	
	// ������ͼ�����ָ��
	void setViewObject( CRectOptDlg* pExcelOperDlg );
	
	// ����excel�ļ�
	int loadExcelFile( CString strFilePath );

	// ����excel�ļ�
	int generateExcelFile( CString strFilePath );
	
public:
	
	CStringArray m_arrayStrColumnName;
	
};
#endif