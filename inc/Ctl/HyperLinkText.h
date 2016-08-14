/*
 * HyperLinkText.h
 *
 *  Created on: Jun 5, 2009
 *      Author: biaozhang
 */

#ifndef HYPERLINKTEXT_H_
#define HYPERLINKTEXT_H_

#include "Ctl/CtlText.h"

class CHyperLinkText : public CCtlText
{
public:
	enum
	{
		ESelectNone,
		ESelected
	};
	
	enum TAlignment
	{
		EHCenter = 1,
		EHLeft = 2
	};
	
	static CHyperLinkText* NewL(const TDesC& aText, TInt aStyleIndex, TInt aClickedStyleIndex);
	static CHyperLinkText* NewLC(const TDesC& aText, TInt aStyleIndex, TInt aClickedStyleIndex);
	virtual ~CHyperLinkText();
	
	virtual void Draw(CWindowGc& gc,const TRect* aRect) const;
	
	void SetState(TInt aState) {iState = aState;}
	TInt State() {return iState;}
	void SetData(HBufC* aData);
	HBufC* Data() {return iData;}
	void SetAlignment(TInt aAlignment) {iAlignment = aAlignment;}
	
private:
	void ConstructL(const TDesC& aText, TInt aStyleIndex, TInt aClickedStyleIndex);
	CHyperLinkText();
	
private:
	TInt iSelectedStyleIndex;
	TInt iState;
	HBufC* iData;
	TInt iAlignment;
};

#endif /* HYPERLINKTEXT_H_ */
