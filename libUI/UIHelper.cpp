#include "stdafx.h"
#include <UIHelper.h>

class CoordsHelperHolder
{
	UICoordinateHelper *helper;
	friend class UICoordinateHelper;
public:
	CoordsHelperHolder();

	void UpdateHelper()
	{
		HDC hDC=::GetDC(nullptr);
		helper=&UICoordinateHelper::GetHelper(hDC);
		::ReleaseDC(nullptr, hDC);
	}
	~CoordsHelperHolder()
	{
		delete helper;
	}
};

CoordsHelperHolder::CoordsHelperHolder()
{
	UpdateHelper();
}

static CoordsHelperHolder TheCoordsHelper;

UICoordinateHelper::UICoordinateHelper(HDC hdc)
{
	//_horzSize=GetDeviceCaps(hdc, HORZSIZE);
	//_vertSize=GetDeviceCaps(hdc, VERTSIZE);
	HorizontalRes=GetDeviceCaps(hdc, HORZRES);
	VerticalRes=GetDeviceCaps(hdc, VERTRES);
	Separate=10; 
	_canRelease=true;
	//_horzLMPerDeviceUnit= (double)_horzSize / _horzRes  *  _seperate;    //0.1mm per pixel align x
	//_vertLMPerDeviceUnit = (double)_vertSize / _vertRes * _seperate;   //0.1mm per pixel align y

	HorizontalSize=GetDeviceCaps(hdc, LOGPIXELSX);
	VerticalSize=GetDeviceCaps(hdc, LOGPIXELSY);

	HorizontalLmPerDeviceUnit= static_cast<double>(25.4) / HorizontalSize * Separate;    //0.1mm per pixel align x
	VerticalLmPerDeviceUnit = static_cast<double>(25.4) /VerticalSize * Separate;   //0.1mm per pixel align y
}

int UICoordinateHelper::DPtoLP(POINT* pPoints, const int count, const int scale/*=100*/ ) const
{
	int i;
	for(i =0; i< count; i++)
	{
		pPoints[i].x=static_cast<int>(HorizontalLmPerDeviceUnit * pPoints[i].x / scale * 100); 
		pPoints[i].y=static_cast<int>(VerticalLmPerDeviceUnit * pPoints[i].y / scale * 100);
	}
	return i;
}

int UICoordinateHelper::DPtoLP(RECT* pRects, const int count, const int scale/*=100*/) const
{
	int i;
	for(i =0; i< count; i++)
	{
		pRects[i].left= static_cast<int>(HorizontalLmPerDeviceUnit * pRects[i].left / scale * 100); 
		pRects[i].right= static_cast<int>(HorizontalLmPerDeviceUnit * pRects[i].right / scale * 100); 
		pRects[i].top= static_cast<int>(VerticalLmPerDeviceUnit * pRects[i].top / scale * 100);
		pRects[i].bottom= static_cast<int>(VerticalLmPerDeviceUnit * pRects[i].bottom / scale * 100);
	}
	return i;
}

int UICoordinateHelper::DPtoLP( SIZE* pSize, int count, int scale/*=100*/ ) const
{
	int i;
	for(i =0; i< count; i++)
	{
		pSize[i].cx= static_cast<int>(HorizontalLmPerDeviceUnit * pSize[i].cx / scale * 100); 
		pSize[i].cy= static_cast<int>(VerticalLmPerDeviceUnit * pSize[i].cy / scale * 100);
	}
	return i;

}
int UICoordinateHelper::LPtoDP( RECT* pRects, int count, int scale/*=100*/ ) const
{
	int i;
	for(i =0; i< count; i++)
	{
		pRects[i].left= static_cast<int>(pRects[i].left / HorizontalLmPerDeviceUnit * scale / 100); 
		pRects[i].right= static_cast<int>(pRects[i].right / HorizontalLmPerDeviceUnit * scale / 100); 
		pRects[i].top= static_cast<int>(pRects[i].top / VerticalLmPerDeviceUnit * scale / 100);
		pRects[i].bottom= static_cast<int>(pRects[i].bottom / VerticalLmPerDeviceUnit * scale / 100);
	}
	return i;
}

int UICoordinateHelper::LPtoDP( POINT* pPoints, int count, int scale/*=100*/ ) const
{
	for (int i = 0; i< count; i++)
	{
		pPoints[i].x= static_cast<int>(pPoints[i].x / HorizontalLmPerDeviceUnit * scale / 100);
		pPoints[i].y= static_cast<int>(pPoints[i].y / VerticalLmPerDeviceUnit * scale / 100);
	}
	return 0;
}

int UICoordinateHelper::LPtoDP( SIZE* pSize, int count , int scale/*=100*/ ) const
{
	for (int i = 0; i< count; i++)
	{
		pSize[i].cx= static_cast<int>(pSize[i].cx / HorizontalLmPerDeviceUnit * scale / 100);
		pSize[i].cy= static_cast<int>(pSize[i].cy / VerticalLmPerDeviceUnit * scale / 100);
	}
	return 0;

}
int UICoordinateHelper::DHLtoLHL( int length /*in 0.1 mm unit*/, int scale/*=100*/ ) const
{
	return static_cast<int>(length * HorizontalLmPerDeviceUnit / scale * 100);
}

int UICoordinateHelper::DVLtoLVL( int length, int scale/*=100*/ ) const
{
	return static_cast<int>(length * VerticalLmPerDeviceUnit / scale * 100);
}

int UICoordinateHelper::LHLtoDHL( int length, int scale /*= 100*/ ) const
{
	return static_cast<int>(length / HorizontalLmPerDeviceUnit * scale / 100);
}

int UICoordinateHelper::LVLtoDVL( int length, int scale /*= 100*/ ) const
{
	return static_cast<int>(length / VerticalLmPerDeviceUnit * scale / 100);
}

UICoordinateHelper& UICoordinateHelper::GetHelper( HDC hdc )
{
	if(hdc== nullptr)
	{
		return *(TheCoordsHelper.helper);
	}
	UICoordinateHelper *pHelper=new UICoordinateHelper(hdc);
	return *pHelper;
}

void UICoordinateHelper::Release()
{
	if(this!=TheCoordsHelper.helper)
		delete this;
}