// IniTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	IniFile iniFile;
	iniFile.OpenIniFile(_T("zn3000.ini"));
	iniFile.DumpIni(stdout);

	const TCHAR *pValue=iniFile.GetConfigString(_T("��������"),_T("ҽԺ"), _T("X"));
	if(pValue!=nullptr)
	{
		_ftprintf(stdout, _T("%s\n"), pValue);
	}
	_getch();
	return 0;
}

