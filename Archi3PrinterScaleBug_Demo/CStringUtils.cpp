#include "stdafx.h"
#include "CStringUtils.h"

using namespace CStringUtils;
/* ===============================================================================================
�Լ�����:
    c# string.Format() �޼���� ���
�����:
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
�Լ�����:
    c# string.FormatedMessage() �޼���� ���
�����:
	AfxMessageBox(FormattedMessage(_T("%1!d!�� %2!d!�� %3��(%1!02d!:%2!02d!:%3)"), 12, 3, _T("20")));
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