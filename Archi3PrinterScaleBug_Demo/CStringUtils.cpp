#include "stdafx.h"
#include "CStringUtils.h"

using namespace CStringUtils;
/* ===============================================================================================
함수설명:
    c# string.Format() 메서드와 비슷
사용방법:
	AfxMessageBox(FormattedString(_T("ErrorCode: %d"), GetLastError()));
=============================================================================================== */
CString CStringUtils::FormattedString(LPCTSTR lpszFormat, ...)
{
	CString sResult;

	va_list args = NULL;
	va_start(args, lpszFormat);

	sResult.FormatV(lpszFormat, args);

	va_end(args);

	return sResult;
}

/* ===============================================================================================
함수설명:
    c# string.FormatedMessage() 메서드와 비슷
사용방법:
	AfxMessageBox(FormattedMessage(_T("%1!d!시 %2!d!분 %3초(%1!02d!:%2!02d!:%3)"), 12, 3, _T("20")));
=============================================================================================== */
CString CStringUtils::FormattedMessage(LPCTSTR lpszFormat, ...)
{
	CString sResult;

	va_list args = NULL;
	va_start(args, lpszFormat);

	sResult.FormatMessageV(lpszFormat, &args);

	va_end(args);

	return sResult;
}