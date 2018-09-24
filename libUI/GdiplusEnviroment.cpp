#include "stdafx.h"

#include <GdiplusEnviroment.h>

GdiplusEnvironment::GdiplusEnvironment()
{
	GdiplusStartup(&_gdiPlusToken, &_gdiPlusStartupInput, nullptr);
}

GdiplusEnvironment::~GdiplusEnvironment()
{
	Gdiplus::GdiplusShutdown(_gdiPlusToken);
}
