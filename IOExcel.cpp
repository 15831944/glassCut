#include "StdAfx.h"
#include "IOExcel.h"


CIOExcel::CIOExcel()
: m_pExcelOperDlg( NULL )
{

}


CIOExcel::~CIOExcel()
{

}


void CIOExcel::setViewObject( CRectOptDlg* pExcelOperDlg )
{
	m_pExcelOperDlg = pExcelOperDlg;
}


int CIOExcel::loadExcelFile( CString strFilePath )
{
	if (!m_oExcelApp.CreateDispatch( _T( "Excel.Application" ), NULL ) ) 
	{
		::MessageBox( NULL, _T( "创建Excel服务失败！" ), _T( "错误提示！" ), MB_OK | MB_ICONERROR); 
		exit(1); 
	}
	
	//设置为显示
	m_oExcelApp.SetVisible(FALSE);
	m_oWorkBooks.AttachDispatch( m_oExcelApp.GetWorkbooks(), TRUE );
	
	LPDISPATCH  lpDisp = NULL;
	COleVariant covTrue((short)TRUE);
    COleVariant covFalse((short)FALSE);
    COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);  
	Range		oCurCell;

	// 打开文件
	lpDisp = m_oWorkBooks.Open( strFilePath, 
					   _variant_t(vtMissing), 
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing) );
	// 获得活动的WorkBook( 工作簿 )
	m_oWorkBook.AttachDispatch( lpDisp, TRUE );
	// 获得活动的WorkSheet( 工作表 )
	m_oWorkSheet.AttachDispatch( m_oWorkBook.GetActiveSheet(), TRUE );
	// 获得使用的区域Range( 区域 )
	m_oCurrRange.AttachDispatch( m_oWorkSheet.GetUsedRange(), TRUE );

	// 获得使用的行数
	long lgUsedRowNum = 0;
	m_oCurrRange.AttachDispatch( m_oCurrRange.GetRows(), TRUE );
	lgUsedRowNum = m_oCurrRange.GetCount();
	
	// 获得使用的列数
	long lgUsedColumnNum = 0;
	m_oCurrRange.AttachDispatch( m_oCurrRange.GetColumns(), TRUE );
	lgUsedColumnNum = m_oCurrRange.GetCount();

	// 读取Sheet的名称
	CString strSheetName = m_oWorkSheet.GetName();

	//得到全部Cells，此时,CurrRange是cells的集合 
	m_oCurrRange.AttachDispatch( m_oWorkSheet.GetCells(), TRUE ); 

	
	//获取填入数据的行数
	for(int k=0; k<lgUsedRowNum; k++)
	{
		oCurCell.AttachDispatch(  m_oCurrRange.GetItem( COleVariant( (long)(k + 1)), COleVariant( (long)1 ) ).pdispVal, TRUE );
		VARIANT varItemName = oCurCell.GetText();
		CString strItemName;
		strItemName = varItemName.bstrVal;
		strItemName.TrimLeft("\t ");
		if (strItemName == CString("") ) 
		{
			lgUsedRowNum = k;
			break;
		}
	}

	// 遍历整个Excel表格
	CStringArray* arrayStr = NULL;
	arrayStr = new CStringArray[lgUsedRowNum];
	for ( int i = 0; i < lgUsedRowNum; )
	{
		for ( int j = 1; j <= lgUsedColumnNum; )
		{
			oCurCell.AttachDispatch(  m_oCurrRange.GetItem( COleVariant( (long)(i + 1)), COleVariant( (long)j ) ).pdispVal, TRUE );
			VARIANT varItemName = oCurCell.GetText();
			CString strItemName = varItemName.bstrVal;
			//给表格填默认值
			strItemName.TrimLeft("\t ");
			if (strItemName == CString("") ) 
			{
				switch(j) 
				{
				case 1:	 									//break;
				case 2:										//break;
				case 3:										//break;
				case 4:										//break;
				case 5:										//break;
				case 6:										//break;
				case 7:										//break;
				case 8:	  strItemName.Format("%d", 0);	 	 break;
				case 9:	  strItemName.Format("%s", "PW");	 break;
				case 10:  strItemName.Format("%s", "GLASS"); break;
				case 11:  strItemName.Format("%s", "注释");	 break;
				}
			}
			arrayStr[i].Add( strItemName );
			j++;
		}
		i++;
	}
	
	//添加矩形信息
	for(i=0; i<lgUsedRowNum-1; i++)
	{
		m_pExcelOperDlg->AddNewRectInf();
		m_pExcelOperDlg->AddGrid();
	}
	
	//将读取数据填入表格
	int	row, col;
	GV_ITEM Item;
	DWORD dwTextStyle = DT_RIGHT|DT_VCENTER|DT_SINGLELINE;
#ifndef _WIN32_WCE
	dwTextStyle |= DT_END_ELLIPSIS;
#endif
	for(row=1; row<lgUsedRowNum; row++)
	{
		for (col = 0; col<lgUsedColumnNum; col++)
		{
			Item.mask = GVIF_TEXT|GVIF_FORMAT;
			Item.row = row;
			Item.col = col;
			Item.nFormat = dwTextStyle;
			
			Item.szText.Format(arrayStr[row].GetAt(col));
			
			m_pExcelOperDlg->m_Grid.SetItem(&Item);
			m_pExcelOperDlg->m_Grid.RedrawRow(row);
		}
	}

	// 释放二维数组
	delete[] arrayStr;

	// 关闭
	m_oWorkBook.Close( covOptional, COleVariant( strFilePath ), covOptional );
	m_oWorkBooks.Close();
	// 释放
	m_oCurrRange.ReleaseDispatch();
	m_oWorkSheet.ReleaseDispatch();
	m_oWorkSheets.ReleaseDispatch();
	m_oWorkBook.ReleaseDispatch();
	m_oWorkBooks.ReleaseDispatch();
	m_oExcelApp.ReleaseDispatch();
	m_oExcelApp.Quit();

	return 0;
}


int CIOExcel::generateExcelFile( CString strFilePath )
{
	if (!m_oExcelApp.CreateDispatch( _T( "Excel.Application" ), NULL ) ) 
	{
		::MessageBox( NULL, _T( "创建Excel服务失败！" ), _T( "错误提示！" ), MB_OK | MB_ICONERROR); 
		exit(1); 
	}
	
	//设置为显示
	m_oExcelApp.SetVisible(FALSE);
	m_oWorkBooks.AttachDispatch( m_oExcelApp.GetWorkbooks(), TRUE );
	
	LPDISPATCH  lpDisp = NULL;
	COleVariant covTrue((short)TRUE);
    COleVariant covFalse((short)FALSE);
    COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);  
	Range		oCurCell;

	// 打开文件
	lpDisp = m_oWorkBooks.Open( _T( "K:\\VoiceS_Excel\\09_Backup\\02_Test\\SourceFile.xls" ), 
					   _variant_t(vtMissing), 
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing),
					   _variant_t(vtMissing) );
	// 获得活动的WorkBook( 工作簿 )
	m_oWorkBook.AttachDispatch( lpDisp, TRUE );
	// 获得活动的WorkSheet( 工作表 )
	m_oWorkSheet.AttachDispatch( m_oWorkBook.GetActiveSheet(), TRUE );
	m_oWorkSheet.AttachDispatch( m_oWorkSheet.GetNext() );
	m_oWorkSheet.Activate();
	// 获得使用的区域Range( 区域 )
	m_oCurrRange.AttachDispatch( m_oWorkSheet.GetCells(), TRUE );

	// 写入数据
	int nRowNum = 0;
	//m_pExcelOperDlg->getRowNumInListCtrl( nRowNum );
	CStringArray* arrayStr;
	arrayStr = new CStringArray[nRowNum];
	//m_pExcelOperDlg->getAllDataInListCtrl( arrayStr );
	for ( int i = 0; i < nRowNum; i++ )
	{
		for ( int j = 0; j < arrayStr[i].GetSize(); j++ )
		{
			m_oCurrRange.SetItem( _variant_t( (long)(i+1) ), 
								  _variant_t( (long)(j+1) ),
								  COleVariant( arrayStr[i].GetAt( j ) ) );
		}
	}

	m_oWorkBook.SaveAs( COleVariant( strFilePath ),
						_variant_t(vtMissing),
						_variant_t(vtMissing),
						_variant_t(vtMissing),
						_variant_t(vtMissing),
						_variant_t(vtMissing),
						0,
						_variant_t(vtMissing),
						_variant_t(vtMissing),
						_variant_t(vtMissing),
						_variant_t(vtMissing),
						_variant_t(vtMissing) );

	// 释放二维数组
	delete[] arrayStr;

	// 关闭
	m_oWorkBook.Close( covOptional, COleVariant( strFilePath ), covOptional );
	m_oWorkBooks.Close();
	// 释放
	m_oCurrRange.ReleaseDispatch();
	m_oWorkSheet.ReleaseDispatch();
	m_oWorkSheets.ReleaseDispatch();
	m_oWorkBook.ReleaseDispatch();
	m_oWorkBooks.ReleaseDispatch();
	m_oExcelApp.ReleaseDispatch();
	m_oExcelApp.Quit();

	return 0;
}