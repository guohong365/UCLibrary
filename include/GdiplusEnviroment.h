#pragma once
#include <libUC.h>
#include <GdiPlus.h>

class LIB_UC_API GdiplusEnvironment 
{
	ULONG_PTR _gdiPlusToken;
    Gdiplus::GdiplusStartupInput _gdiPlusStartupInput;
public:
	GdiplusEnvironment();
	~GdiplusEnvironment();
};