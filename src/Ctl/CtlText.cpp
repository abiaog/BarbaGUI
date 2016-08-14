#include "Ctl/CtlText.h"

#include <eikenv.h>
#include "YoukuLogger.h"

CCtlText* CCtlText::NewL(const TDesC& aText, TInt aStyleIndex)
{
	CCtlText* self = CCtlText::NewLC(aText,aStyleIndex);
	CleanupStack::Pop( self );
	return self;
}

CCtlText* CCtlText::NewLC(const TDesC& aText, TInt aStyleIndex)
{
	CCtlText* self = new ( ELeave ) CCtlText( );
	CleanupStack::PushL( self );
	self->ConstructL(aText,aStyleIndex);
	return self;
}

CCtlText::~CCtlText()
{
	iText.Close();
}

CCtlModel* CCtlText::Clone()
{
	TPtrC text;
	CCtlText* clone = CCtlText::NewL(iText, iStyleIndex);
	return clone;
}
	
CCtlModel* CCtlText::Clone3D()
{
	TPtrC text;
	CCtlText* clone = CCtlText::NewL(iText, iStyleIndex);
	return clone;
}

void CCtlText::Draw(CWindowGc& gc,const TRect* aRect) const
{	
	CFont* fontUsed = NULL;
	TRgb colorUsed;
	colorUsed = CMWLookAndFeelStyle::Instance()->GetFontColor( iStyleIndex );
	fontUsed = CMWLookAndFeelStyle::Instance()->GetFont( iStyleIndex );
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
	
	gc.DrawText(text,TPoint(rect.iTl.iX,rect.iBr.iY));
	
	gc.DiscardFont();
	text.Close();
	
//	DEBUG(LOG_UI, text);
}

void CCtlText::GetText(TPtrC& aText)
{
	aText.Set(iText);
}

void CCtlText::SetText(const TDesC& aText)
{
	iText.Close();
	iText.Create(aText);
}

void CCtlText::ConstructL(const TDesC& aText, TInt aStyleIndex)
{
	iText.Create(aText);
	iStyleIndex = aStyleIndex;
}

CCtlText::CCtlText()
{
}
