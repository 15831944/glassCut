// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__B6E3D091_8299_4DE1_9340_BF1EC180E338__INCLUDED_)
#define AFX_STDAFX_H__B6E3D091_8299_4DE1_9340_BF1EC180E338__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "ClrButton.h"
#include "Dmcwin.h"
#include <stdio.h>
#include "CadBase.h"
#include "Dmcgc.h"
#include "HandDll.h"
#pragma   warning   (disable:4146)
#import "C:\Program Files\Common Files\System\Ado\msado15.dll" no_namespace rename ("EOF","adoEOF") rename ("BOF","adoBOF")
#include <adoid.h>
#include "ICRSINT.H"
#include "odbcinst.h"       //注册数据库用
#include "SHLWAPI.H"        //检查目录是否存在用
#include "ewfapi.h"         //写保护的头文件

#include "SystemDll.h"
#include "MachineDll.h"
#include "Dxf2G.h"
#include "CuttingPress.h"
#include "UniButton.h"
#include ".\Alarm\AlarmDll.h"
#include "DataStruct.h"
#include <iostream.h>
#include <fstream.h>
#include "grMath.h"
#define UM_PICWND_MSG			(WM_USER + 100)
#define UM_LISTWND_MSG			(WM_USER + 101)

#define GRAPH_COLOR_FR			RGB(0,240,240)
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_STDAFX_H__B6E3D091_8299_4DE1_9340_BF1EC180E338__INCLUDED_)
