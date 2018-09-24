#pragma once
#include <libUC.h>
class LIB_UC_API UICoordinateHelper
{
	bool _canRelease;
public:
	int HorizontalSize;
	int VerticalSize;
	int HorizontalRes;
	int VerticalRes;
	double HorizontalLmPerDeviceUnit;
	double VerticalLmPerDeviceUnit;
	int Separate;

	explicit UICoordinateHelper(HDC hdc);
	static UICoordinateHelper& GetHelper(HDC hdc= nullptr);
	 void Release();
	 int DPtoLP(POINT* pPoints, int count, int scale=100) const;
	 int DPtoLP(RECT* pRects, int count, int scale=100) const;
	 int LPtoDP(POINT* pPoints, int count, int scale=100) const;
	 int LPtoDP(RECT* pRects, int count, int scale=100) const;
	 int DHLtoLHL(int length /*in 0.1 mm unit*/, int scale=100) const;
	 int DVLtoLVL(int length, int scale=100) const;
	 int LHLtoDHL(int length, int scale = 100) const;
	 int LVLtoDVL(int length, int scale = 100) const;
	 int DPtoLP(SIZE* pSize, int count, int scale=100) const;
	 int LPtoDP(SIZE* pSize, int count , int scale=100) const;
};