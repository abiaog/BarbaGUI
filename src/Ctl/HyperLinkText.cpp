#include "Ctl/HyperLinkText.h"

CHyperLinkText* CHyperLinkText::NewL(const TDesC& aText, TInt aStyleIndex, TInt aClickedStyleIndex)
{
	CHyperLinkText* self = CHyperLinkText::NewLC(aText,aStyleIndex,aClickedStyleIndex);
	CleanupStack::Pop( self );
	return self;
}

CHyperLinkText* CHyperLinkText::NewLC(const TDesC& aText, TInt aStyleIndex, TInt aClickedStyleIndex)
{
	CHyperLinkText* self = new ( ELeave ) CHyperLinkText();
	CleanupStack::PushL( self );
	self->ConstructL(aText,aStyleIndex,aClickedStyleIndex);
	return self;
}

CHyperLinkText::~CHyperLinkText()
{
	delete iData;
	iData = NULL;
}

void CHyperLinkText::Draw(CWindowGc& gc,const TRect* aRect) const
{	
//	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
//	gc.SetBrushColor(KRgbRed);
//	gc.SetPenStyle(CGraphicsContext::ESolidPen);
//	gc.SetBrushColor(KRgbBlack);
//	gc.DrawRect(*aRect);
	
	CFont* fontUsed = NULL;
	TRgb colorUsed;
	if (ESelectNone == iState)
	{
		colorUsed = CMWLookAndFeelStyle::Instance()->GetFontColor( iStyleIndex );
		fontUsed = CMWLookAndFeelStyle::Instance()->GetFont( iStyleIndex );
	}
	else
	{
		colorUsed = CMWLookAndFeelStyle::Instance()->GetFontColor( iSelectedStyleIndex );
		fontUsed = CMWLookAndFeelStyle::Instance()->GetFont( iSelectedStyleIndex );
	}
	gc.SetPenStyle(CGraphicsContext::ESolidPen);
	gc.SetPenColor(colorUsed);
	gc.UseFont(fontUsed);
	gc.SetUnderlineStyle(EUnderlineOff);
	
	TInt heightOfFont = fontUsed->HeightInPixels();
	TInt ascentOfFont = fontUsed->AscentInPixels();
	TRect rect(aRect->iTl, aRect->Size());
	if (aRect->Size().iHeight >= heightOfFont)
	{
		rect.iBr.iY = aRect->iTl.iY + (aRect->Size().iHeight - heightOfFont) / 2 + ascentOfFont;
	}
		
	RBuf text;
	text.Create(iText);
	TextUtils::ClipToFit(text,*fontUsed,rect.Width());
	
	if (EHCenter == iAlignment)
	{
		TInt widthOfText = fontUsed->TextWidthInPixels(text);
		rect.iTl.iX += (rect.Width() / 2 - widthOfText / 2); 
	}
	
	gc.DrawText(text,TPoint(rect.iTl.iX,rect.iBr.iY));
	
	gc.DiscardFont();
	text.Close();
}

void CHyperLinkText::ConstructL(const TDesC& aText, TInt aStyleIndex, TInt aClickedStyleIndex)
{
	CCtlText::ConstructL( aText, aStyleIndex);
	iSelectedStyleIndex = aClickedStyleIndex;
}

CHyperLinkText::CHyperLinkText()
: iState(ESelectNone)
, iData(NULL)
{
	iAlignment = EHLeft;
}

void CHyperLinkText::SetData(HBufC* aData)
{
	delete iData;
	iData = aData;
}


