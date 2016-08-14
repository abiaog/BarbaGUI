#ifndef CTLPICTURE_H_
#define CTLPICTURE_H_

#include "Ctl/CtlModel.h"

class CCtlPicture : public CCtlModel //, public MImagePlayerObserver
{
public:
	enum TAlignment
	{
		EVCenter = 1,
		EVTop = 2
//		EHCenter = 2
	};
	
	static CCtlPicture* NewL( CGulIcon* aIcon);
	static CCtlPicture* NewLC(CGulIcon* aIcon);
	virtual ~CCtlPicture();
	
	virtual CCtlModel* Clone();
	virtual CCtlModel* Clone3D();
	virtual void Draw(CWindowGc& gc,const TRect* aRect) const;
	
	CGulIcon* Picture() {return iGulIcon;}
	void SetPicture(CGulIcon* aGulIcon);
	
	void SetAlignment(TInt aAlignment) {iAlignment = aAlignment;}
	void SetBitmapsOwnedExternally(TBool aBitmapsOwnedExternally);
//	void SetPlayer(CImagePlayer* aPlayer) { iPlayer = aPlayer; }
//	virtual void SetBitmap(CFbsBitmap * aBitmap);
//	virtual void NotifyRedraw();
	
private:
	void ConstructL(CGulIcon* aIcon);
	CCtlPicture();

private:
	CGulIcon* iGulIcon;
	TInt iAlignment;
};



#endif /*CTLPICTURE_H_*/


