//////////////////////////////////////////////////////////////////////
// Globals.cpp: implementation of the CGlobals class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Globals.h"
#include <mmsystem.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGlobals::CGlobals()
{

}

CGlobals::~CGlobals()
{

}


////////////////////////
// �۷ι� ��Ʈ���� ����
////////////////////////

sFILE_DATA		g_sFile;


//////////////////////
// �۷ι� Ŭ���� ����
//////////////////////

//CFileOperation		g_sFILEOp;



////////////////////
// �۷ι� �Լ� ����
////////////////////
void DoEvents(DWORD dwMilliseconds)
{
	MSG msg;
	if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	Sleep(dwMilliseconds);
}

void Delay(UINT delaytime, UINT unit)
{
	// �Է°� ������ ����
	// 1->7.5~8.5u  2->9u 4->11u 5->12 7->13u 10->17u
	// 100->106u 200->206u 500->506u

	//static LONGLONG FreqQuadPart=0;
	static double FreqQuadPart=0;
	static LARGE_INTEGER Freq, ZeroCnt, CurCnt;

	// ���ػ� Ÿ�̸��� 1�ʴ� ������ ȹ��
	if(!QueryPerformanceFrequency(&Freq)) return;

	switch(unit)
	{
	case sec:
		FreqQuadPart = (double)Freq.QuadPart;
		break;

	case msec:
		FreqQuadPart = (double)Freq.QuadPart/1000.0;
		break;

	default:
	case usec:		// 1us(micro sec) �� �������� ��ȯ
		FreqQuadPart = (double)Freq.QuadPart/1000000.0;
		break;
	}
	
	//---------------------------------------------------
	// ex) delaytime=200, unit=usec(2) ���
	// 	    200 micro sec ���� DoEvents()�� �ݺ��Ͽ� �����Ѵ�.
	

#if 0		
	// Elapsed time�� ǥ���ϱ�
	__int64	startTime, endTime;
	startTime = GetMicroSecond();

	QueryPerformanceCounter(&ZeroCnt);	// ���۽����� counter �� ȹ��
	do
	{
		DoEvents();
		QueryPerformanceCounter(&CurCnt);	// DoEvents()�� ������ ������ counter �� ȹ��
	}
	while((CurCnt.QuadPart-ZeroCnt.QuadPart)/FreqQuadPart < delaytime);

	endTime = GetMicroSecond();

	MyTrace(PRT_LEVEL1, "			Delay(%d %s), Elapsed time=%d(usec)\n", delaytime,
						(unit == sec) ? "sec" :
					    (unit == msec) ? "msec":  
					    (unit == usec) ? "usec": "Logic Err?",  (endTime - startTime));

#else
	QueryPerformanceCounter(&ZeroCnt);	// ���۽����� counter �� ȹ��
	do
	{
		DoEvents();
		QueryPerformanceCounter(&CurCnt);	// DoEvents()�� ������ ������ counter �� ȹ��
	}
	while((CurCnt.QuadPart-ZeroCnt.QuadPart)/FreqQuadPart < delaytime);

	MyTrace(PRT_LEVEL1, "			Delay(%d %s)\n", delaytime,
						(unit == sec) ? "sec" :
					    (unit == msec) ? "msec":  
					    (unit == usec) ? "usec": "Logic Err?" ) ;

#endif


}

__int64 GetMicroSecond()  //sylee
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER now;

    if( !QueryPerformanceFrequency(&frequency) )
        return (__int64)GetTickCount();

    if( !QueryPerformanceCounter(&now) )
        return (__int64)GetTickCount();

	return((((__int64)now.QuadPart) * ((__int64)1000000)) / ((__int64)frequency.QuadPart));
}



BOOL FileExists(CString strFilePath)
{
	CFileFind aFile;
	BOOL IsExist = aFile.FindFile(strFilePath);
	aFile.Close();
	return IsExist;
}




//2017.11.06  TRACE�� buffer�� 512���� �ۿ� ������� �ʾƼ� �Ʒ��� ���� �ű� �Լ� ����
//  buffer size = 2048

WORD	g_wPrintState = 0x0001;		// PRT_BASIC    on 
void AFX_CDECL MyTrace(PRT_TYPE prtType, LPCTSTR lpszFormat, ...)
{
#ifdef _DEBUG // all AfxTrace output is controlled by afxTraceEnabled
	if (!afxTraceEnabled)
		return;
#endif
	WORD  bitMask = 0x01 << prtType;
	if (!(g_wPrintState & bitMask)) // check print bit_mask
		return;

	va_list args;
	va_start(args, lpszFormat);

	int nBuf;
	TCHAR szBuffer[2048];

	nBuf = _vsntprintf(szBuffer, sizeof(szBuffer), lpszFormat, args);

	// was there an error? was the expanded string too long?
	ASSERT(nBuf >= 0);

	if ((afxTraceFlags & traceMultiApp) && (AfxGetApp() != NULL))
		afxDump << AfxGetApp()->m_pszExeName << ": ";
	afxDump << szBuffer;

	va_end(args);
}


//2018.02.14  ���ɰ����� ���� print off�̸� snprintf�� �������� �ʴ� ��� �߰�.
int AFX_CDECL MySnprintf(PRT_TYPE prtType, char* pStr, int strSize, LPCTSTR lpszFormat, ...)
{
#ifdef _DEBUG // all AfxTrace output is controlled by afxTraceEnabled
	if (!afxTraceEnabled)
		return (-1);
#endif
	WORD  bitMask = 0x01 << prtType;
	if (!(g_wPrintState & bitMask)) // check print bit_mask
	{
		return (-1);
	}

	va_list args;
	va_start(args, lpszFormat);

	int nBuf = _vsnprintf((char*)pStr, strSize, lpszFormat, args);

	// was there an error? was the expanded string too long?
	ASSERT(nBuf >= 0);

	va_end(args);

	return nBuf;
}

// MyTrace�� �ٸ� ��. : pStr �����͸� �Է¹޾Ƽ� ȣ�����Ŀ� ����� str�� ������ �� �ִ�.
int AFX_CDECL MyTrace2(PRT_TYPE prtType, char *pStr, int strSize, LPCTSTR lpszFormat, ...)
{
#ifdef _DEBUG // all AfxTrace output is controlled by afxTraceEnabled
	if (!afxTraceEnabled)
		return (-1);
#endif
	WORD  bitMask = 0x01 << prtType;
	if (!(g_wPrintState & bitMask)) // check print bit_mask
	{
		return (-1);
	}

	va_list args;
	va_start(args, lpszFormat);

	//char* pStr = str.GetBuffer(2048);	// �̷��� �ϴϱ� �״´�.. 
	//int	  strSize = str.GetLength();
	int nBuf = _vsnprintf(pStr, strSize, lpszFormat, args);

	// was there an error? was the expanded string too long?
	ASSERT(nBuf >= 0);

	if ((afxTraceFlags & traceMultiApp) && (AfxGetApp() != NULL))
		afxDump << AfxGetApp()->m_pszExeName << ": ";
	afxDump << pStr;

	va_end(args);

	return nBuf;
}
