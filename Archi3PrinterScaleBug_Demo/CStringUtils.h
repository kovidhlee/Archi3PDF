#pragma once

namespace CStringUtils
{
	//  CString::Format, CString::FormatMessage ���� �Լ�
	CString FormattedString(LPCTSTR lpszFormat, ...);
	CString FormattedMessage(LPCTSTR lpszFormat, ...);
}