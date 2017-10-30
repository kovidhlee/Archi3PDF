#pragma once

namespace CStringUtils
{
	//  CString::Format, CString::FormatMessage ÇïÆÛ ÇÔ¼ö
	CString FormattedString(LPCTSTR lpszFormat, ...);
	CString FormattedMessage(LPCTSTR lpszFormat, ...);
}