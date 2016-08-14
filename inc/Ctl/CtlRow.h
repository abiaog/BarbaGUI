#ifndef CTLROW_H_
#define CTLROW_H_

#include "Ctl/CtlModel.h"

class CFbsBitmap;
class CBannerPlayer;
class CHistoryManipulator;
class CHistoryColumnManipulator;
class CColumnLayout;
class CRowLayout;

class CCtlRow : public CCtlModel
{
public:
	static CCtlRow* NewL();
	static CCtlRow* NewLC();
	virtual ~CCtlRow();
	
	virtual void Add(CCtlModel* aCtlModel);
	virtual void Remove(TInt anIndex);
	virtual TInt Insert(CCtlModel* aCtlModel, TInt aPos);
	virtual void Reset();
	virtual TInt Count() {return iComponents->Count();}
	virtual void Draw(CWindowGc& gc,const TRect* aRect) const;
	virtual void MakeVisible(TBool aVisible);
	virtual CCtlModel* At(TInt aIndex);
	virtual CCtlModel* Clone();
	virtual CCtlModel* Clone3D();
	virtual TRect* Rect() const;
		
	void SetRect(const TRect& aRect);
	void SetViewRect(const TRect& aRect);
	const TRect& ViewRect() const;
	void SetLayout(CRowLayout* aLayout) {iLayout = aLayout;}
	CRowFormat* Format() {return iFormat;}
	void SetFormat(CRowFormat* aFormat) {iFormat = aFormat;}
	
	TInt GetSelection(const TPoint& aPoint,TBool aIsTopFirst = ETrue);
	
protected:
	void ConstructL();
	CCtlRow();
		
protected:
	RPointerArray<CCtlModel>* iComponents;
	CRowLayout* iLayout;
	TBool iVisible;
	
	CRowFormat* iFormat;	
};


#endif /*CTLROW_H_*/
