// Globals.h: interface for the CGlobals class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLOBALS_H__FDA16379_4221_4970_8471_B8FBD39D2C1E__INCLUDED_)
#define AFX_GLOBALS_H__FDA16379_4221_4970_8471_B8FBD39D2C1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <direct.h>
#include <io.h>
#include "stdafx.h"
#include <stdarg.h>



class CGlobals  
{
public:
	CGlobals();
	virtual ~CGlobals();

};




///////////////////
// �۷ι� ��Ʈ����
///////////////////

typedef struct sFILE_DATA
{
	CString	SystemDir;					// ACE400Statistics ���α׷��� ������ ���丮
	CString ParameterDir;
	CString MeasureDir;					


	CString ACE400_4WDataDir;			// ACE400�� 4W data Dir ("D:\\log4w");

	CString SystemFileName; 
	CString SystemFile; 

	sFILE_DATA()
	{
		SystemFileName		= "System.";

		ACE400_4WDataDir    = "D:\\log4w";
	}

	void Init()
	{
		// ���� ACE400Cal�� ������ ���丮 ��ġ�� �����´�.
		char buffer[_MAX_PATH];
		if(_getcwd( buffer, _MAX_PATH ) == NULL)
		{
			AfxMessageBox("Root directory not found.");
			return;
		}

		SystemDir.Format("%s", buffer);
		ParameterDir	= SystemDir + "\\" + "Parameter";
		MeasureDir		= SystemDir + "\\" + "Measure";

		//if( (_access(ParameterDir, 0 )) == -1 )	_mkdir(ParameterDir);
		//if( (_access(MeasureDir, 0 )) == -1 )	_mkdir(MeasureDir);

		SystemFile		= ParameterDir	+ "\\" + SystemFileName;
	}

} sFILE_DATA;

extern sFILE_DATA g_sFile;


///////////////
// �۷ι� ���� 
///////////////

enum UNIT			{ sec=0, msec=1, usec=2, mA, uA, Mohm, Kohm, ohm, mohm, uohm };// sec=0, msec=1, usec=2 ����
enum UNIT_CONVERT_TYPE	{ 
	MM_TO_UM, UM_TO_MM, SEC_TO_MSEC, MSEC_TO_SEC
};

enum PRT_TYPE { PRT_BASIC, PRT_LEVEL1, PRT_LEVEL2, PRT_LEVEL3, PRT_DEVICE, PRT_DEV_D64 };

extern WORD	g_wPrintState;


////////////////
// �۷ι� �Լ�
////////////////


extern	void		DoEvents(DWORD dwMilliseconds=0);
extern  void		Delay(UINT delaytime=0, UINT unit=usec);
extern  __int64 	GetMicroSecond();  //sylee
extern  BOOL		FileExists(CString strFilePath);

extern  void AFX_CDECL MyTrace(PRT_TYPE prtType, LPCTSTR lpszFormat, ...);
extern  int  AFX_CDECL MyTrace2(PRT_TYPE prtType, char* pStr, int strSize, LPCTSTR lpszFormat, ...);

extern  int  AFX_CDECL MySnprintf(PRT_TYPE prtType, char* pStr, int strSize, LPCTSTR lpszFormat, ...);
//extern  BOOL		CreateFolder(LPCTSTR szFolder);
//extern  BOOL		DeleteSubDir(const TCHAR* sPath);
//extern  void		DeleteFolder(char *strDirectory);



#endif // !defined(AFX_GLOBALS_H__FDA16379_4221_4970_8471_B8FBD39D2C1E__INCLUDED_)
