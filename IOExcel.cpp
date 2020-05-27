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
		::MessageBox( NULL, _T( "����Excel����ʧ�ܣ�" ), _T( "������ʾ��" ), MB_OK | MB_ICONERROR); 
		exit(1); 
	}
	
	//����Ϊ��ʾ
	m_oExcelApp.SetVisible(FALSE);
	m_oWorkBooks.AttachDispatch( m_oExcelApp.GetWorkbooks(), TRUE );
	
	LPDISPATCH  lpDisp = NULL;
	COleVariant covTrue((short)TRUE);
    COleVariant covFalse((short)FALSE);
    COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);  
	Range		oCurCell;

	// ���ļ�
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
	// ��û��WorkBook( ������ )
	m_oWorkBook.AttachDispatch( lpDisp, TRUE );
	// ��û��WorkSheet( ������ )
	m_oWorkSheet.AttachDispatch( m_oWorkBook.GetActiveSheet(), TRUE );
	// ���ʹ�õ�����Range( ���� )
	m_oCurrRange.AttachDispatch( m_oWorkSheet.GetUsedRange(), TRUE );

	// ���ʹ�õ�����
	long lgUsedRowNum = 0;
	m_oCurrRange.AttachDispatch( m_oCurrRange.GetRows(), TRUE );
	lgUsedRowNum = m_oCurrRange.GetCount();
	
	// ���ʹ�õ�����
	long lgUsedColumnNum = 0;
	m_oCurrRange.AttachDispatch( m_oCurrRange.GetColumns(), TRUE );
	lgUsedColumnNum = m_oCurrRange.GetCount();

	// ��ȡSheet������
	CString strSheetName = m_oWorkSheet.GetName();

	//�õ�ȫ��Cells����ʱ,CurrRange��cells�ļ��� 
	m_oCurrRange.AttachDispatch( m_oWorkSheet.GetCells(), TRUE ); 

	
	//��ȡ�������ݵ�����
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

	// ��������Excel���
	CStringArray* arrayStr = NULL;
	arrayStr = new CStringArray[lgUsedRowNum];
	for ( int i = 0; i < lgUsedRowNum; )
	{
		for ( int j = 1; j <= lgUsedColumnNum; )
		{
			oCurCell.AttachDispatch(  m_oCurrRange.GetItem( COleVariant( (long)(i + 1)), COleVariant( (long)j ) ).pdispVal, TRUE );
			VARIANT varItemName = oCurCell.GetText();
			CString strItemName = varItemName.bstrVal;
			//�������Ĭ��ֵ
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
				case 11:  strItemName.Format("%s", "ע��");	 break;
				}
			}
			arrayStr[i].Add( strItemName );
			j++;
		}
		i++;
	}
	
	//��Ӿ�����Ϣ
	for(i=0; i<lgUsedRowNum-1; i++)
	{
		m_pExcelOperDlg->AddNewRectInf();
		m_pExcelOperDlg->AddGrid();
	}
	
	//����ȡ����������
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

	// �ͷŶ�ά����
	delete[] arrayStr;

	// �ر�
	m_oWorkBook.Close( covOptional, COleVariant( strFilePath ), covOptional );
	m_oWorkBooks.Close();
	// �ͷ�
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
		::MessageBox( NULL, _T( "����Excel����ʧ�ܣ�" ), _T( "������ʾ��" ), MB_OK | MB_ICONERROR); 
		exit(1); 
	}
	
	//����Ϊ��ʾ
	m_oExcelApp.SetVisible(FALSE);
	m_oWorkBooks.AttachDispatch( m_oExcelApp.GetWorkbooks(), TRUE );
	
	LPDISPATCH  lpDisp = NULL;
	COleVariant covTrue((short)TRUE);
    COleVariant covFalse((short)FALSE);
    COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);  
	Range		oCurCell;

	// ���ļ�
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
	// ��û��WorkBook( ������ )
	m_oWorkBook.AttachDispatch( lpDisp, TRUE );
	// ��û��WorkSheet( ������ )
	m_oWorkSheet.AttachDispatch( m_oWorkBook.GetActiveSheet(), TRUE );
	m_oWorkSheet.AttachDispatch( m_oWorkSheet.GetNext() );
	m_oWorkSheet.Activate();
	// ���ʹ�õ�����Range( ���� )
	m_oCurrRange.AttachDispatch( m_oWorkSheet.GetCells(), TRUE );

	// д������
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

	// �ͷŶ�ά����
	delete[] arrayStr;

	// �ر�
	m_oWorkBook.Close( covOptional, COleVariant( strFilePath ), covOptional );
	m_oWorkBooks.Close();
	// �ͷ�
	m_oCurrRange.ReleaseDispatch();
	m_oWorkSheet.ReleaseDispatch();
	m_oWorkSheets.ReleaseDispatch();
	m_oWorkBook.ReleaseDispatch();
	m_oWorkBooks.ReleaseDispatch();
	m_oExcelApp.ReleaseDispatch();
	m_oExcelApp.Quit();

	return 0;
}