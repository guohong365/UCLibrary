// IniTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	IniFile iniFile;
	iniFile.OpenIniFile(_T("zn3000.ini"));
	iniFile.DumpIni(stdout);

	const TCHAR *pValue=iniFile.GetConfigString(_T("基础配置"),_T("医院"), _T("X"));
	if(pValue!=nullptr)
	{
		_ftprintf(stdout, _T("%s\n"), pValue);
	}
	_getch();
	return 0;
}

