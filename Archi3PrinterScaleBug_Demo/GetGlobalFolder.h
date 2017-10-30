#pragma once

#include "stdafx.h"

CString pascal GetRootPath()
{
	CString strModulePath;
	TCHAR szModulePath[MAX_PATH + 1];
	::GetModuleFileName(NULL, szModulePath, MAX_PATH);

	TCHAR szCanoPath[MAX_PATH + 1];
	::PathCanonicalize(szCanoPath, szModulePath);
	strModulePath = (CString)szCanoPath;

	strModulePath = strModulePath.Left(strModulePath.ReverseFind('\\') + 1);

	return strModulePath;
}