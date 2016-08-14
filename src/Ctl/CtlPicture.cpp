#include "Ctl/CtlPicture.h"

#include "YoukuLogger.h"

////////////////////////////////////////////////////////////
////CCtlPicture
////////////////////////////////////////////////////////////
CCtlPicture* CCtlPicture::NewL( CGulIcon* aIcon)
{
	CCtlPicture* self = CCtlPicture::NewLC(aIcon);
	CleanupStack::Pop( self );
	return self;
}

CCtlPicture* CCtlPicture::NewLC( CGulIcon* aIcon)
{
	CCtlPicture* self = new ( ELeave ) CCtlPicture( );
	CleanupStack::PushL( self );
	self->ConstructL(aIcon);
	return self;
}

CCtlPicture::~CCtlPicture()
{
	delete iGulIcon;
	iGulIcon = NULL;
}

CCtlPicture::CCtlPicture()
: iGulIcon(NULL)
, iAlignment(EVCenter)
{
}

CCtlModel* CCtlPicture::Clone()
{
	CCtlPicture* clone = CCtlPicture::NewL(Picture());
	return clone;
}

CCtlModel* CCtlPicture::Clone3D()
{
	return Clone();
}
	
void CCtlPicture::SetPicture(CGulIcon* aGulIcon)
{
	if (NULL != iGulIcon)
	{
		delete iGulIcon;
		iGulIcon = NULL;
	}
	iGulIcon = aGulIcon;
}

void CCtlPicture::Draw(CWindowGc& gc,const TRect* aRect) const
{
//	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
//	gc.SetBrushColor(KRgbRed);
//	gc.SetPenStyle(CGraphicsContext::ESolidPen);
//	gc.SetBrushColor(KRgbBlack);
//	gc.DrawRect(*aRect);
	
//	DEBUG(LOG_UI, "CCtlPicture::Draw begin");
	if (NULL != iGulIcon)
	{
		CFbsBitmap* bitmap = iGulIcon->Bitmap();
		CFbsBitmap* mask = iGulIcon->Mask();
//		gc.DrawBitmap(*aRect,bitmap);
		
//		gc.BitBlt(aRect->iTl,bitmap);
//		
//		TInt width = bitmap->SizeInPixels().iWidth;
		TInt height = bitmap->SizeInPixels().iHeight;
		TInt y = 0;
		if (EVCenter == iAlignment)
		{
			y = (aRect->Size().iHeight - height) / 2;
		}
		else if (EVTop == iAlignment)
		{
			y = 0;
		}
		
		if (mask)
		{
			gc.BitBltMasked(TPoint(aRect->iTl.iX,aRect->iTl.iY + y),bitmap,TRect(TPoint(0,0),bitmap->SizeInPixels()),mask,ETrue);
		}
		else
		{
			gc.BitBlt(TPoint(aRect->iTl.iX,aRect->iTl.iY + y),bitmap,TRect(TPoint(0,0),bitmap->SizeInPixels()));
		}
	}
//	else
//	{
//		gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
//		gc.SetBrushColor(KRgbRed);
//		gc.DrawRect(*aRect);
//	}
//	DEBUG(LOG_UI, "CCtlPicture::Draw end");
}

void CCtlPicture::ConstructL(CGulIcon* aIcon)
{
	if (NULL != aIcon)
	{
		iGulIcon = CGulIcon::NewL();	
		iGulIcon->SetBitmapsOwnedExternally(aIcon->BitmapsOwnedExternally());
		iGulIcon->SetBitmap(aIcon->Bitmap());
		iGulIcon->SetMask(aIcon->Mask());
	}
}

void CCtlPicture::SetBitmapsOwnedExternally(TBool aBitmapsOwnedExternally)
{
	if (NULL != iGulIcon)
	{
		iGulIcon->SetBitmapsOwnedExternally(aBitmapsOwnedExternally);
	}
}



