#ifndef CTLTEXT_H_
#define CTLTEXT_H_

#include "Ctl/CtlModel.h"
#include "MWLookAndFeelStyle.h"

class CCtlText : public CCtlModel
{
public:
	static CCtlText* NewL(const TDesC& aText, TInt aStyleIndex);
	static CCtlText* NewLC(const TDesC& aText, TInt aStyleIndex);
	virtual ~CCtlText();
	
	virtual CCtlModel* Clone();
	virtual CCtlModel* Clone3D();
	virtual void Draw(CWindowGc& gc,const TRect* aRect) const;

	void GetText(TPtrC& aText);
	void SetText(const TDesC& aText);
	
protected:
	void ConstructL(const TDesC& aText, TInt aStyleIndex);
	CCtlText();

protected:
	RBuf iText;
	TInt iStyleIndex;
};



#endif /*CTLTEXT_H_*/
