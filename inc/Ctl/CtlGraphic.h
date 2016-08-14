/*
 * CtlGraphic.h
 *
 *  Created on: Jun 5, 2009
 *      Author: biaozhang
 */

#ifndef CTLGRAPHIC_H_
#define CTLGRAPHIC_H_

#include <gdi.h>
#include "Ctl/CtlModel.h"

class CCtlGraphic : public CCtlModel
{
public:
	enum TGraphicType
	{
		EHeader,
		EBody,
		ETrail,
		ERoundRect
	};
};

class CCtlGraphicHeader : public CCtlGraphic
{
public:
	virtual ~CCtlGraphicHeader() {}
	virtual CCtlModel* Clone();
	virtual CCtlModel* Clone3D();
	virtual void Draw(CWindowGc& gc,const TRect* aRect) const;
	
	CCtlGraphicHeader(TRgb aBrushColor, TRgb aLineColor);
	
private:
	TRgb iBrushColor;
	TRgb iLineColor;
};

class CCtlGraphicHeader3D : public CCtlGraphic
{
public:
	virtual ~CCtlGraphicHeader3D() {}
	virtual CCtlModel* Clone();
	virtual CCtlModel* Clone3D();
	virtual void Draw(CWindowGc& gc,const TRect* aRect) const;
	
	CCtlGraphicHeader3D(TRgb aLineColor);
	
private:
	TRgb iLineColor;
};

class CCtlGraphicBody : public CCtlGraphic
{
public:
	CCtlGraphicBody(TRgb aBrushColor, TRgb aLineColor);
	virtual ~CCtlGraphicBody() {}
	virtual CCtlModel* Clone();
	virtual CCtlModel* Clone3D();
	virtual void Draw(CWindowGc& gc,const TRect* aRect) const;
	
//	CCtlGraphicBody() {}
	
private:
	TRgb iBrushColor;
	TRgb iLineColor;
};

class CCtlGraphicTrail : public CCtlGraphic
{
public:
	virtual ~CCtlGraphicTrail() {}
	virtual CCtlModel* Clone();
	virtual CCtlModel* Clone3D();
	virtual void Draw(CWindowGc& gc,const TRect* aRect) const;
	
	CCtlGraphicTrail(TRgb aBrushColor, TRgb aLineColor);
	
private:
	TRgb iBrushColor;
	TRgb iLineColor;
};

class CCtlRect : public CCtlGraphic
{
public:
	virtual ~CCtlRect() {}
	virtual CCtlModel* Clone();
	virtual CCtlModel* Clone3D();
	virtual void Draw(CWindowGc& gc,const TRect* aRect) const;
	
	CCtlRect(TRgb aPenColor);
	
	void SetBrushColor(TRgb aBrushColor) {iBrushColor = aBrushColor;}
	void SetBrushStyle(TInt aBrushStyle) {iBrushStyle = aBrushStyle;}
	void SetPenStyle(TInt aPenStyle) {iPenStyle = aPenStyle;}
	void SetPenColor(TRgb aPenColor) {iPenColor = aPenColor;}
	void SetPenSize(TSize aSize) {iPenSize = aSize;}
	
protected:
	TRgb iBrushColor;
	TInt iBrushStyle;
	TInt iPenStyle;
	TRgb iPenColor;
	TSize iPenSize;
};

class CCtlRoundRect : public CCtlRect
{
public:
	virtual ~CCtlRoundRect() {}
	virtual CCtlModel* Clone();
	virtual CCtlModel* Clone3D();
	virtual void Draw(CWindowGc& gc,const TRect* aRect) const;
	
	CCtlRoundRect(TRgb aPenColor);	
	void SetCornerSize(TSize aSize) {iCornerSize = aSize;}
	
private:
	TSize iCornerSize;
};

#endif /* CTLGRAPHIC_H_ */
