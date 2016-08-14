#ifndef CTLCOLUMN_H_
#define CTLCOLUMN_H_

#include "Ctl/CtlModel.h"

class CColumnLayout;

class CCtlColumn : public CCtlModel
{
public:
	static CCtlColumn* NewL();
	static CCtlColumn* NewLC();
	virtual ~CCtlColumn();
	
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
	void SetLayout(CColumnLayout* aLayout) {iLayout = aLayout;}
	CColumnFormat* Format() {return iFormat;}
	void SetFormat(CColumnFormat* aFormat) {iFormat = aFormat;}
	
	TInt Selection() {return iSelectedIndex;}
	TInt GetSelection(const TPoint& aPoint);
	void SetSelection(TInt aIndex);
	
	virtual void DoSelect(CCtlModel* aSource,CWindowGc& gc,const TRect* aRect) const;
	
	TInt ComponentsCount();
	virtual TInt VisibleTopLine();
	virtual TInt VisibleBottomLine();
				
protected:
	void ConstructL();
	CCtlColumn();
	
protected:
	RPointerArray<CCtlModel>* iComponents;
	CColumnFormat* iFormat;
	CColumnLayout* iLayout;
	TBool iVisible;
	TInt iSelectedIndex;
};

#endif /*CTLCOLUMN_H_*/
