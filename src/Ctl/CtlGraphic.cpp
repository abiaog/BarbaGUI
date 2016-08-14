#include "Ctl/CtlGraphic.h"

const TSize KCornerSize = TSize(8,9); 

///////////////////////////////////////////////////////////////////////
///CCtlGraphicHeader
///////////////////////////////////////////////////////////////////////
CCtlGraphicHeader::CCtlGraphicHeader(TRgb aBrushColor, TRgb aLineColor)
{
	iBrushColor = aBrushColor;
	iLineColor = aLineColor;
}

CCtlModel* CCtlGraphicHeader::Clone()
{
	return new (ELeave) CCtlGraphicHeader(iBrushColor,iLineColor);
}

CCtlModel* CCtlGraphicHeader::Clone3D()
{
	return new (ELeave) CCtlGraphicHeader3D(iLineColor);
}

void CCtlGraphicHeader::Draw(CWindowGc& gc,const TRect* aRect) const
{
	gc.SetPenColor(iBrushColor);
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(iBrushColor);
	gc.DrawRoundRect(*aRect,KCornerSize);
	
	TInt halfHeight = aRect->Size().iHeight / 2;
	TRect halfRect(aRect->iTl.iX,aRect->iTl.iY + halfHeight,aRect->iBr.iX,aRect->iBr.iY);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(iBrushColor);
	gc.DrawRect(halfRect);
	
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetPenColor(iLineColor);
	TInt penHeight = 1;
	TInt lineY = aRect->iBr.iY - penHeight;
	gc.DrawLine(TPoint(aRect->iTl.iX,lineY),TPoint(aRect->iBr.iX,lineY));
}

///////////////////////////////////////////////////////////////////////
///CCtlGraphicHeader3D
///////////////////////////////////////////////////////////////////////
CCtlGraphicHeader3D::CCtlGraphicHeader3D( TRgb aLineColor)
{
	iLineColor = aLineColor;
}

CCtlModel* CCtlGraphicHeader3D::Clone()
{
	return new (ELeave) CCtlGraphicHeader3D(iLineColor);
}

CCtlModel* CCtlGraphicHeader3D::Clone3D()
{
	return Clone();
}

void CCtlGraphicHeader3D::Draw(CWindowGc& gc,const TRect* aRect) const
{
	gc.SetPenColor(iLineColor);
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetBrushStyle(CGraphicsContext::ENullBrush);
//	gc.SetBrushColor(iBrushColor);
//	gc.DrawRoundRect(*aRect,KCornerSize);
	gc.DrawRect(*aRect);
	
	TRect rect(*aRect);
	rect.Move(-1,-1);
	gc.SetPenColor(KRgbWhite);
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetBrushStyle(CGraphicsContext::ENullBrush);
//	gc.DrawRoundRect(rect,KCornerSize);
	gc.DrawRect(rect);
	
//	rect.Move(-1,-1);
//	gc.SetPenColor(KRgbWhite);
//	gc.SetPenStyle(CGraphicsContext::ESolidPen);
//	gc.SetBrushStyle(CGraphicsContext::ENullBrush);
////	gc.DrawRoundRect(rect,KCornerSize);
//	gc.DrawRect(rect);
	
//	TInt halfHeight = aRect->Size().iHeight / 2;
//	TRect halfRect(aRect->iTl.iX,aRect->iTl.iY + halfHeight,aRect->iBr.iX,aRect->iBr.iY);
//	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
//	gc.SetBrushColor(iBrushColor);
//	gc.DrawRect(halfRect);
	
//	gc.SetPenStyle(CGraphicsContext::ESolidPen);
//	gc.SetPenColor(iLineColor);
//	TInt penHeight = 1;
//	TInt lineY = aRect->iBr.iY - penHeight;
//	gc.DrawLine(TPoint(aRect->iTl.iX,lineY),TPoint(aRect->iBr.iX,lineY));
}

///////////////////////////////////////////////////////////////////////
///CCtlGraphicBody
///////////////////////////////////////////////////////////////////////
CCtlGraphicBody::CCtlGraphicBody(TRgb aBrushColor, TRgb aLineColor)
{
	iBrushColor = aBrushColor;
	iLineColor = aLineColor;
}

CCtlModel* CCtlGraphicBody::Clone()
{
	return new (ELeave) CCtlGraphicBody(iBrushColor,iLineColor);
}

CCtlModel* CCtlGraphicBody::Clone3D()
{
	return new (ELeave) CCtlGraphicHeader3D(iLineColor);
}

void CCtlGraphicBody::Draw(CWindowGc& gc,const TRect* aRect) const
{
	gc.SetPenStyle(CGraphicsContext::ENullPen);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(iBrushColor);
	gc.DrawRect(*aRect);
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetPenColor(iLineColor);
	TInt penHeight = 1;
	TInt lineY = aRect->iBr.iY - penHeight;
	gc.DrawLine(TPoint(aRect->iTl.iX,lineY),TPoint(aRect->iBr.iX,lineY));
}

///////////////////////////////////////////////////////////////////////
///CCtlGraphicTrail
///////////////////////////////////////////////////////////////////////
CCtlGraphicTrail::CCtlGraphicTrail(TRgb aBrushColor, TRgb aLineColor)
{
	iBrushColor = aBrushColor;
	iLineColor = aLineColor;
}

CCtlModel* CCtlGraphicTrail::Clone()
{
	return new (ELeave) CCtlGraphicTrail(iBrushColor,iLineColor);
}

CCtlModel* CCtlGraphicTrail::Clone3D()
{
	return new (ELeave) CCtlGraphicHeader3D(iLineColor);
}

void CCtlGraphicTrail::Draw(CWindowGc& gc,const TRect* aRect) const
{
	gc.SetPenColor(iBrushColor);
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(iBrushColor);
	gc.DrawRoundRect(*aRect,KCornerSize);
	
	TInt halfHeight = aRect->Size().iHeight / 2;
	TRect halfRect(aRect->iTl.iX,aRect->iTl.iY,aRect->iBr.iX,aRect->iBr.iY - halfHeight);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.SetBrushColor(iBrushColor);
	gc.DrawRect(halfRect);
	
//	gc.SetPenStyle(CGraphicsContext::ESolidPen);
//	gc.SetPenColor(KRgbGray);
//	TInt penHeight = 1;
//	TInt lineY = aRect->iBr.iY - penHeight;
//	gc.DrawLine(TPoint(aRect->iTl.iX,lineY),TPoint(aRect->iBr.iX,lineY));
}


///////////////////////////////////////////////////////////////////////
///CCtlRect
///////////////////////////////////////////////////////////////////////
CCtlRect::CCtlRect( TRgb aPenColor)
{
	iBrushColor = aPenColor;
	iPenColor = aPenColor;
	iBrushStyle = CGraphicsContext::ENullBrush;
	iPenStyle = CGraphicsContext::ESolidPen;
	iPenSize = TSize(1,1);
}

void CCtlRect::Draw(CWindowGc& gc,const TRect* aRect) const
{
	gc.SetPenColor(iPenColor);
	gc.SetPenStyle((CGraphicsContext::TPenStyle)iPenStyle);
	gc.SetPenSize(iPenSize);
	gc.SetBrushStyle((CGraphicsContext::TBrushStyle)iBrushStyle);
	gc.SetBrushColor(iBrushColor);
	gc.DrawRect(*aRect);
}

CCtlModel* CCtlRect::Clone()
{
	return new (ELeave) CCtlRect(iPenColor);
}

CCtlModel* CCtlRect::Clone3D()
{
	return new (ELeave) CCtlRect(iPenColor);
}

///////////////////////////////////////////////////////////////////////
///CCtlRoundRect
///////////////////////////////////////////////////////////////////////
CCtlRoundRect::CCtlRoundRect( TRgb aPenColor)
: CCtlRect(aPenColor)
{
	iCornerSize = TSize(8,9);
}

CCtlModel* CCtlRoundRect::Clone()
{
	return new (ELeave) CCtlRoundRect(iPenColor);
}

CCtlModel* CCtlRoundRect::Clone3D()
{
	return new (ELeave) CCtlGraphicHeader3D(iPenColor);
}

void CCtlRoundRect::Draw(CWindowGc& gc,const TRect* aRect) const
{
	gc.SetPenColor(iPenColor);
	gc.SetPenStyle((CGraphicsContext::TPenStyle)iPenStyle);
	gc.SetPenSize(iPenSize);
	gc.SetBrushStyle((CGraphicsContext::TBrushStyle)iBrushStyle);
	gc.SetBrushColor(iBrushColor);
	gc.DrawRoundRect(*aRect,iCornerSize);	
}





