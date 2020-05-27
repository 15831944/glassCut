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
	
	// 对话框对象
	CRectOptDlg* m_pExcelOperDlg;

	// Excel应用对象
	_Application	m_oExcelApp;
	_Worksheet		m_oWorkSheet;
	_Workbook		m_oWorkBook;
	Workbooks		m_oWorkBooks;
	Worksheets		m_oWorkSheets;
	Range			m_oCurrRange;

public:
	
	// 保存视图对象的指针
	void setViewObject( CRectOptDlg* pExcelOperDlg );
	
	// 加载excel文件
	int loadExcelFile( CString strFilePath );

	// 生成excel文件
	int generateExcelFile( CString strFilePath );
	
public:
	
	CStringArray m_arrayStrColumnName;
	
};
#endif